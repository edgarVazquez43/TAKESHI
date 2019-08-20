/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "obj_reco_flattened/ControlerFlattenedObjects.h"



/*TODO cambiar el tipo de mensajes para usar imagenes comprimidas al envío*/
bool ControlerFlattenedObjects::cb_srv_FindPlaneObjects(vision_msgs::RecognizeFlattenedObjects::Request &req, vision_msgs::RecognizeFlattenedObjects::Response &resp)
{
	cv::Mat bgrImg;
	cv::Mat xyzCloud;

	vision_msgs::VisionFlattenedObjectList response_msg;

	point_cloud_manager::GetRgbd srv;

	while(!clt_RgbdRobot.call(srv))
	{
		ROS_INFO_STREAM("Cannot get point cloud");
	}

	JustinaTools::PointCloud2Msg_ToCvMat(srv.response.point_cloud, bgrImg, xyzCloud);

	// imshow("pcl",  xyzCloud);
	// waitKey(10);

	response_msg = cb_searchObjects( bgrImg, xyzCloud);

	resp.recog_objects = response_msg;

	return true;
}


ControlerFlattenedObjects::ControlerFlattenedObjects(ros::NodeHandle &nodeHandle_, bool debug):nodeHandle(nodeHandle_) {

	ROS_INFO_STREAM("Starting: Flattened Object detector NODE");

	this->debug = debug;
	this->minAceptableArea = 350;
	this->maxAceptableArea = 20000;
	this->threshold_avgPixelsAreaOnImage = .3; //it takes 30% more or less to determine that is the same object

	this->models.loadKnowledgeBase();

	this->srv_FindPlaneObjects = nodeHandle.advertiseService("/vision/obj_reco/flattened_object", &ControlerFlattenedObjects::cb_srv_FindPlaneObjects, this) ;
	this->clt_RgbdRobot        = nodeHandle.serviceClient<point_cloud_manager::GetRgbd>("/hardware/point_cloud_man/get_rgbd_wrt_robot");


	//ros::Subscriber subscriber = nodeHandle.subscribe("/hardware/point_cloud_man/rgbd_wrt_robot",30, &ControlerFlattenedObjects::cb_searchObjectsOnTopic, this);

	ROS_INFO_STREAM("Ready: Flattened Object detector NODE");

	ros::spin();
}


void
ControlerFlattenedObjects::cb_searchObjectsOnTopic(const sensor_msgs::PointCloud2ConstPtr& cloud_msg){

	cv::Mat imgSrc;
	cv::Mat xyzCloud;

	JustinaTools::PointCloud2Msg_ToCvMat(cloud_msg, imgSrc, xyzCloud);

	cb_searchObjects(imgSrc, xyzCloud);

}



vision_msgs::VisionFlattenedObjectList
ControlerFlattenedObjects::cb_searchObjects(cv::Mat imgSrc, cv::Mat xyzCloud){

	cv::Mat bgr;
	cv::Mat founds;
	cv::Mat element;
	cv::Mat partialMaskColor, wholeMaskColor, ouputMask;
	Scalar minScalar;
	Scalar maxScalar;
	float averageAreaPixels;

	vector<Point> largest_contour;
	cv::Rect bounding_rect;
	string name;

	char str[400];
	int  largest_area;

	ROS_INFO_STREAM("Searching: Flattened object detector");



	//imshow("pcl",  xyzCloud);
	//waitKey(10);

	cv::Mat (* fptr) (cv::Mat,cv::Mat, Scalar, Scalar);

	element = getStructuringElement( MORPH_ELLIPSE, Size(11,11), Point( 5,5));


	bgr = imgSrc.clone();
	bgr.copyTo(founds);

	vision_msgs::VisionFlattenedObjectList response_msg;


	response_msg.header.frame_id = "base_link";
	response_msg.header.stamp    = ros::Time();

	ouputMask = Mat::zeros(bgr.rows, bgr.cols, CV_8UC1);

	for(int i = 0; i < models.size() ; i++){
		vector<vector<Point> > contours;

		name             = models.names[i];
		minScalar        = models.min_maxScalarsSegmentation[i][0];
		maxScalar        = models.min_maxScalarsSegmentation[i][1];
		fptr             = models.methodsSegmentation[i];
		averageAreaPixels= models.averagesAreasPixels[i];

		wholeMaskColor        = segmentColor(fptr, bgr, element, minScalar, maxScalar);
		partialMaskColor      = wholeMaskColor.clone();

		do{

			partialMaskColor = wholeMaskColor;
			contours         = getContours(partialMaskColor);
			largest_contour  = getLargestContourArea(partialMaskColor);
			if(largest_contour.size()==0) break;
			largest_area     = contourArea(largest_contour,false);
			bounding_rect    = boundingRect(largest_contour);
			partialMaskColor = getMaskLargestCountour(partialMaskColor, largest_contour);

			if( largest_area > minAceptableArea && largest_area < maxAceptableArea){

				partialMaskColor = getMaskLargestCountour(partialMaskColor, largest_contour);
				wholeMaskColor   = updateSearchingArea(wholeMaskColor, partialMaskColor,bounding_rect);

				if ( averageAreaPixels == -1 ||
					( largest_area < averageAreaPixels+averageAreaPixels*threshold_avgPixelsAreaOnImage
					&& largest_area > averageAreaPixels-averageAreaPixels*threshold_avgPixelsAreaOnImage)){ //si el valor es -1 quiere decir que es el único objeto con ese color y no vale la pena saber tamaños

						//////////Its was found an object//////////
						vision_msgs::VisionFlattenedObject object_msg;

						object_msg =  createVisionFlattenedObject(xyzCloud, partialMaskColor, bounding_rect, name );

						//response_msg.objectList.push_back(object_msg);
						response_msg.objectList = insertObjectMessaje(response_msg.objectList, object_msg);

						bgr = blindSpotOnInput( bgr, partialMaskColor, bounding_rect );
						ouputMask = ouputMask | partialMaskColor;

						sprintf(str,"%s: %i",name.c_str(), largest_area);
						markFound(largest_contour,bounding_rect, str, founds);

						i--;

						break;

					}

			}
			if(largest_area > maxAceptableArea){
				ROS_ERROR_STREAM("Bad Color Segmentation");
				break;
			}

		}while( largest_area > minAceptableArea );
	}

	sensor_msgs::Image container;
	cv_bridge::CvImage cvi_ouputMask;
	cvi_ouputMask.encoding = sensor_msgs::image_encodings::MONO8;
	cvi_ouputMask.image = ouputMask;
	cvi_ouputMask.toImageMsg(container);
	response_msg.maskOfObjects = container;

	sensor_msgs::Image container_founds;
	cv_bridge::CvImage cvi_founds;
	cvi_founds.encoding = sensor_msgs::image_encodings::BGR8;
	cvi_founds.image = founds;
	cvi_founds.toImageMsg(container_founds);
	response_msg.imgOutput = container_founds;

	stringstream ss;
	ss << response_msg.objectList.size()<<" objectos detectados"<<endl;
	ROS_INFO_STREAM(ss.str());
	ROS_INFO_STREAM("Finished searching: Flattened object detector");

	if( debug ){
		//imshow("Input", imgSrc);
		imshow("Output", founds);
		waitKey(15);
		imshow("Blinded", bgr);
		waitKey(15);

	}

	return response_msg;
}

vector<vision_msgs::VisionFlattenedObject> ControlerFlattenedObjects::insertObjectMessaje(vector<vision_msgs::VisionFlattenedObject> object_list, vision_msgs::VisionFlattenedObject object_msg){


	int indiceCorrecto=0;

	float distanciaObjeto;

	vector <vision_msgs::VisionFlattenedObject> tmpFlattenedObjectList;

	vector <vision_msgs::VisionFlattenedObject> flattenedObjectList;

	cv::Point3f point;

	point               =  cv::Point3f(object_msg.nearest_point.x, object_msg.nearest_point.y, object_msg.nearest_point.z);
	distanciaObjeto     = cv::norm( point );
	flattenedObjectList = object_list;

	for(int i=0; i < flattenedObjectList.size() ; i++){
		tmpFlattenedObjectList.push_back(flattenedObjectList[i]);
	}
	flattenedObjectList.clear();

	int i;
	for(i=0; i < tmpFlattenedObjectList.size() ; i++){
		vision_msgs::VisionFlattenedObject objectMsgOnList;
		cv::Point3f pointOnList;
		float distanceObjectMsgOnList;

		objectMsgOnList = tmpFlattenedObjectList[i];
		pointOnList      = cv::Point3f(objectMsgOnList.nearest_point.x,
		    						objectMsgOnList.nearest_point.y,
									objectMsgOnList.nearest_point.z);
		distanceObjectMsgOnList = cv::norm( pointOnList );

		if(distanciaObjeto < distanceObjectMsgOnList){
			flattenedObjectList.push_back(object_msg);
			break;
		}
		flattenedObjectList.push_back(tmpFlattenedObjectList[i]);

	}
	for(; i < tmpFlattenedObjectList.size() ; i++){
		flattenedObjectList.push_back(tmpFlattenedObjectList[i]);
	}


	if(flattenedObjectList.size()==0){
		flattenedObjectList.push_back(object_msg);
	}



	return flattenedObjectList;
}



vision_msgs::VisionFlattenedObject ControlerFlattenedObjects::createVisionFlattenedObject(cv::Mat xyzCloud, cv::Mat mask,cv::Rect bounding_rect, string name){
	vision_msgs::VisionFlattenedObject object_msg;

	cv::Point3f nearestPoint;
	cv::Point3f size;
	cv::Point3f cntr;

	vector<cv::Point3f>  eigen_vecs(3);
	vector<float>        eigen_val(3);
	vector <cv::Point3f> valid_masked_points;
	geometry_msgs::Vector3 eigenVector1, eigenVector2, eigenVector3;


	valid_masked_points = getMasked3DPOints(xyzCloud, mask);

	getOrientation( valid_masked_points ,cntr, eigen_vecs, eigen_val);
	size          = calculateSize( valid_masked_points );
	nearestPoint  = calculateNearest3Dpoint( valid_masked_points );

	eigenVector1.x    = eigen_vecs[0].x;
	eigenVector1.y    = eigen_vecs[0].y;
	eigenVector1.z    = eigen_vecs[0].z;
	eigenVector2.x    = eigen_vecs[1].x;
	eigenVector2.y    = eigen_vecs[1].y;
	eigenVector2.z    = eigen_vecs[1].z;
	eigenVector3.x    = eigen_vecs[2].x;
	eigenVector3.y    = eigen_vecs[2].y;
	eigenVector3.z    = eigen_vecs[2].z;

	object_msg.header.stamp         = ros::Time();
	object_msg.header.frame_id      = "base_link";
	object_msg.id                   = name;
	object_msg.category             = "tableware";
	object_msg.size.x               = size.x;
	object_msg.size.y               = size.y;
	object_msg.size.z               = size.z;
	object_msg.eigen_vectors.push_back(eigenVector1);
	object_msg.eigen_vectors.push_back(eigenVector2);
	object_msg.eigen_vectors.push_back(eigenVector3);
	object_msg.eigen_values.x      = eigen_val[0];
	object_msg.eigen_values.y      = eigen_val[1];
	object_msg.eigen_values.z      = eigen_val[2];
	object_msg.xi                   = bounding_rect.x;
	object_msg.yi                   = bounding_rect.y;
	object_msg.widthi               = bounding_rect.width;
	object_msg.heighti              = bounding_rect.height;
	object_msg.nearest_point.x      = nearestPoint.x;
	object_msg.nearest_point.y      = nearestPoint.y;
	object_msg.nearest_point.z      = nearestPoint.z;
	object_msg.center_point.x       =cntr.x;
	object_msg.center_point.y       =cntr.y;
	object_msg.center_point.z       =cntr.z;

	return object_msg;
}


cv::Point3f ControlerFlattenedObjects::calculateSize( vector<cv::Point3f> validPoints ){

	float min_x = std::numeric_limits<float>::max();
	float min_y = std::numeric_limits<float>::max();
	float min_z = std::numeric_limits<float>::max();

	float max_x = std::numeric_limits<float>::min();
	float max_y = std::numeric_limits<float>::min();
	float max_z = std::numeric_limits<float>::min();

	cv::Point3f  size;

	for( int i = 0; i < validPoints.size(); i++ ) {

		cv::Point3f point = validPoints[i];

		if( min_x > point.x)  min_x = point.x;
		if( min_y > point.y)  min_y = point.y;
		if( min_z > point.z)  min_z = point.z;
		if( max_x < point.x)  max_x = point.x;
		if( max_y < point.y)  max_y = point.y;
		if( max_z < point.z)  max_z = point.z;

	}
	size.x = max_x - min_x;
	size.y = max_y - min_y;
	size.z = max_z - min_z;

	return size;

}


cv::Point3f ControlerFlattenedObjects::calculateNearest3Dpoint( vector<cv::Point3f> validPoints ){

	float min_distance = std::numeric_limits<float>::max();

	cv::Point3f nearestPoint;

	for( int i = 0; i < validPoints.size(); i++ ) {

		cv::Point3f point = validPoints[i];
		float distance = cv::norm( point );

		if ( min_distance >  distance ){
			min_distance = distance;
			nearestPoint = point;
		}
	}
	return nearestPoint;
}



vector<cv::Point3f> ControlerFlattenedObjects::getMasked3DPOints(cv::Mat XYZimg, cv::Mat mask){
	vector <cv::Point3f> validPoints;


	for( int y = 0; y < XYZimg.rows; y++ ) {
		for( int x = 0; x < XYZimg.cols; x++ ) {
			if ( mask.at<uchar>(y,x) != 0 ) {
				Point3f point3D= XYZimg.at<cv::Vec3f>(y,x);
				if( !(point3D.x==0 && point3D.y==0 && point3D.z==0) ){
					validPoints.push_back(point3D);
				}
			}
		}
	}
	return validPoints;
}


void ControlerFlattenedObjects::getOrientation( vector<cv::Point3f> validPoints, cv::Point3f& cntr, vector<cv::Point3f>& eigen_vecs, vector<float>& eigen_val)
{

	if(validPoints.size()==0){
		return;
	}

	//Construct a buffer used by the pca analysis
	int sz = validPoints.size();
	cv::Mat data_pts = cv::Mat(sz, 3, CV_32FC1);

	for (int i = 0; i < data_pts.rows; ++i)
	{
		data_pts.at<float>(i, 0) = validPoints[i].x;
		data_pts.at<float>(i, 1) = validPoints[i].y;
		data_pts.at<float>(i, 2) = validPoints[i].z;
	}
	//Perform PCA analysis
	PCA pca_analysis(data_pts, cv::Mat(), CV_PCA_DATA_AS_ROW);
	//Store the center of the object
	cntr = cv::Point3f(pca_analysis.mean.at<float>(0, 0),
				   pca_analysis.mean.at<float>(0, 1),
				   pca_analysis.mean.at<float>(0, 2));

	for (int i = 0; i < 3; ++i)
	{
		eigen_vecs[i] = cv::Point3f(pca_analysis.eigenvectors.row(i));
		eigen_val[i] = pca_analysis.eigenvalues.at<float>(0, i);
	}

	return ;
}


vector<Point> ControlerFlattenedObjects::getLargestContourArea(cv::Mat mask){
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours( mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	int largest_area=0;
	vector<Point> largest_contour;
	int largest_contour_index=0;
	cv::Rect bounding_rect;
	for( int i = 0; i< contours.size(); i++ )
	{
		//  Find the area of contour
		double a=contourArea( contours[i],false);
		if(a>largest_area){
			largest_area=a;
			// Store the index of largest contour
			largest_contour_index=i;
			// store largest contour
			largest_contour = contours[i];
		}
	}
	return largest_contour;
}



vector<vector<Point> > ControlerFlattenedObjects::getContours(cv::Mat mask){
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours( mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	return contours;
}


cv::Mat ControlerFlattenedObjects::updateSearchingArea( cv::Mat wholeMask, cv::Mat subMask, cv::Rect bounding_rect ){
	cv::Mat tmp = wholeMask.clone();
	cv::Mat ROI=tmp(bounding_rect);
	cv::Mat ROI2=subMask(bounding_rect);
	ROI = ROI & ~ROI2;

	return tmp;
}

cv::Mat ControlerFlattenedObjects::blindSpotOnInput( cv::Mat bgrInput, cv::Mat maskSpot, cv::Rect bounding_rect ){

	cv::Mat tmp = bgrInput.clone();

	cvtColor(maskSpot, maskSpot, CV_GRAY2BGR);

	cv::Mat ROI=tmp(bounding_rect);
	cv::Mat ROI2=maskSpot(bounding_rect);
	ROI = ROI & ~ROI2;

	return tmp;

}

cv::Mat ControlerFlattenedObjects::getMaskLargestCountour(cv::Mat mask, vector<Point>contour){

	cv::Mat maskUpdate=cv::Mat::zeros(mask.rows,mask.cols,mask.type());

	vector<vector<Point> > contours;
	contours.push_back(contour);
	vector<vector<Point> >hull(1);
	convexHull( cv::Mat(contour), hull[0], false );
	cv::drawContours( maskUpdate, hull, 0, cv::Scalar(255,255,255), cv::FILLED);

	//cv::drawContours( maskUpdate, contours, 0, cv::Scalar(255,255,255), cv::FILLED);

	return maskUpdate;
}

cv::Mat ControlerFlattenedObjects::segmentColor(cv::Mat (* segmetationFunction)(cv::Mat,cv::Mat, Scalar, Scalar),cv::Mat bgr,cv::Mat element, Scalar minHSV, Scalar maxHSV){

	return (* segmetationFunction)(bgr, element, minHSV, maxHSV);
}

void ControlerFlattenedObjects::markFound(vector<Point>contour, cv::Rect bounding_rect,string name, cv::Mat& output){

    rectangle(output, bounding_rect,  Scalar(0,255,0),2, 8,0);
    putText(output, name, Point2f(bounding_rect.x,bounding_rect.y), FONT_HERSHEY_PLAIN, 0.9,  Scalar(017,070,244,255));


    return;
}
