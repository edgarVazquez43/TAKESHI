#include "surf_detector.h"


surf_detector::surf_detector(std::string file, std::string camera_parameters,int minHessian, float gr, int ransacTHR) : it_(nh_)
{
        //image_pub_ = it_.advertise("/image_converter/output_video", 1);
        counter=0;
        this->minHessian=minHessian;
        this->filename =file;
        this->good_ratio=gr;
        this->ransacTHR=ransacTHR;
        printf("Using %s\n", camera_parameters.c_str() );
        cv::FileStorage fs(filename,cv::FileStorage::READ);
        fs["roi_corners"]>>train_corners;
        fs["keypoints"]>>keypoints_train;
        fs["descriptors"]>>descriptors_train;
        if(descriptors_train.empty())
        {
                std::cout << "Error no descriptors loaded" << '\n';
                fs.release();
                return;
        }
        fs.release();

        cv::FileStorage cf(camera_parameters,cv::FileStorage::READ);
        cf["camera_matrix"]>>cameraMatrix;
        cf["distortion_coefficients"]>>rectCoeff;
        cf.release();
        image_sub_ = it_.subscribe("/image", 1,
                                   &surf_detector::callBack, this);
        point_pub=nh_.advertise<std_msgs::Float32MultiArray>("/hand/object", 1);

        cv::namedWindow(OPENCV_WINDOW);
        return;
        //cv::setMouseCallback(OPENCV_WINDOW,surf_trainer::onClick,this);
}

surf_detector::surf_detector(std::string file, int minHessian, float gr, int ransacTHR, bool show_img) : it_(nh_)
{
        //image_pub_ = it_.advertise("/image_converter/output_video", 1);
        counter=0;
        this->minHessian=minHessian;
        this->filename =file;
        this->good_ratio=gr;
        this->ransacTHR=ransacTHR;
        printf("Using %s\n", file.c_str() );
        cv::FileStorage fs(filename,cv::FileStorage::READ);
        fs["roi_corners"]>>train_corners;
        fs["keypoints"]>>keypoints_train;
        fs["descriptors"]>>descriptors_train;
        if(descriptors_train.empty())
        {
                std::cout << "Error no descriptors loaded" << '\n';
                fs.release();
                return;
        }
        fs.release();

        image_sub_ = it_.subscribe("/image", 1,
                                   &surf_detector::callBack, this);
        enable_sub = nh_.subscribe("/enable_surf",1,&surf_detector::enable_cb,this);
        load_sub = nh_.subscribe("/load_surf_recog",1,&surf_detector::load_cb,this);
        point_pub=nh_.advertise<std_msgs::Float32MultiArray>("/hand/object", 1);

        this->show_img=show_img;

        if(show_img) {
                cv::namedWindow(OPENCV_WINDOW);
        }
        return;
        //cv::setMouseCallback(OPENCV_WINDOW,surf_trainer::onClick,this);
}

surf_detector::~surf_detector(){
        if(show_img) {
                cv::destroyWindow(OPENCV_WINDOW);
        }
}

void surf_detector::enable_cb(const std_msgs::Bool& en)
{
        enable=en.data;
        std::cout << "Setting surf enable as " << enable<<'\n';
        return;
}

void surf_detector::load_cb(const std_msgs::String& filename)
{
        std::string file = ros::package::getPath("surf_recog") + "/config/"+filename.data;
        printf("Using %s\n", file.c_str() );
        cv::FileStorage fs(file,cv::FileStorage::READ);
        if (!fs.isOpened())
        {
                std::cout << "Failed to load" << '\n';
                return;
        }
        fs["roi_corners"]>>train_corners;
        fs["keypoints"]>>keypoints_train;
        fs["descriptors"]>>descriptors_train;
        if(descriptors_train.empty())
        {
                std::cout << "Error no descriptors loaded" << '\n';
                fs.release();
                return;
        }
        fs.release();
}

void surf_detector::Converter(const sensor_msgs::ImageConstPtr& msg)
{
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
                cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
                ROS_ERROR("cv_bridge exception: %s", e.what());
                return;
        }
        this->image=cv_ptr->image;
        // else
        // {
        //         cv::Mat distorted=cv_ptr->image;
        //         undistort(distorted,this->image,cameraMatrix,rectCoeff  );
        // }
        return;
}

void surf_detector::surf_extractor()
{
        cv::Ptr<cv::Feature2D> surf = cv::xfeatures2d::SURF::create(minHessian);

        surf->detect(this->image,keypoints_query);
        surf->compute( this->image,keypoints_query, descriptors_query);

        return;
}

void surf_detector::match()
{
        cv::FlannBasedMatcher matcher;
        std::vector<std::vector< cv::DMatch> > matches;
        if(keypoints_query.size()>=2 && keypoints_train.size()>=2)
        { //program crashes if program finds to litttle descriptors
                matcher.knnMatch( descriptors_train, descriptors_query, matches,2);
        }
        else
        {
                matches.clear();
        }
        good_matches.clear();
        for (int k = 0; k < matches.size(); k++)
        {
                if ( (matches[k][0].distance < good_ratio*(matches[k][1].distance)) )
                {
                        // take the first result only if its distance is smaller than 0.6*second_best_dist
                        // that means this descriptor is ignored if the second distance is bigger or of similar
                        good_matches.push_back( matches[k][0] );
                }

        }

        // double max_dist = 0; double min_dist = 100;
        // //-- Quick calculation of max and min distances between keypoints
        // for( int i = 0; i < descriptors_train.rows; i++ )
        // {
        //         double dist = matches[i].distance;
        //         if( dist < min_dist ) min_dist = dist;
        //         if( dist > max_dist ) max_dist = dist;
        // }
        //
        // for( int i = 0; i < descriptors_train.rows; i++ )
        // {
        //         if( matches[i].distance <= std::max(1.5*min_dist, 0.02) )
        //         {
        //                 good_matches.push_back( matches[i]);
        //         }
        // }

        //printf("Found %ld good matches from %ld\n",good_matches.size(), matches.size() );
        return;
}

void surf_detector::locate()
{
        //-- Localize the object
        std::vector<cv::Point2f> obj;
        std::vector<cv::Point2f> scene;
        for( int i = 0; i < good_matches.size(); i++ )
        {
                //-- Get the keypoints from the good matches
                obj.push_back( keypoints_train[ good_matches[i].queryIdx ].pt );
        }
        if (good_matches.size()>=10)
        {
                for( int i = 0; i < good_matches.size(); i++ )
                {
                        //-- Get the keypoints from the good matches
                        scene.push_back( keypoints_query[ good_matches[i].trainIdx ].pt );
                }

                std::vector<cv::Point2f> obj_corner(4);

                obj_corner[0] = train_corners[0];
                obj_corner[1] = cv::Point2f(train_corners[1].x,train_corners[0].y);
                obj_corner[3] = cv::Point2f(train_corners[0].x,train_corners[1].y);
                obj_corner[2] = train_corners[1];

                cv::Mat H =cv::findHomography(obj,scene,cv::RANSAC,ransacTHR);
                if(!H.empty())
                {
                        //std::cout << H << '\n';

                        std::vector<cv::Point2f> scene_corners(4);
                        cv::perspectiveTransform( obj_corner, scene_corners, H);
                        cv::Point2f centroid=get_center(scene_corners);
                        // for(int i = 0; i< 4; i++)
                        // {
                        //         std::cout << scene_corners[i] << '\n';
                        // }
                        if(show_img)
                        {
                                cv::line( image, scene_corners[0], scene_corners[1], cv::Scalar(0, 255, 0), 4 );
                                cv::line( image, scene_corners[1], scene_corners[2], cv::Scalar( 0, 255, 0), 4 );
                                cv::line( image, scene_corners[2], scene_corners[3], cv::Scalar( 0, 255, 0), 4 );
                                cv::line( image, scene_corners[3], scene_corners[0], cv::Scalar( 0, 255, 0), 4 );

                                cv::circle(image,centroid,4,cv::Scalar(0,0,255),8,0);
                        }
                }
        }

        //cv::drawKeypoints(this->image,keypoints_query,this->image,cv::Scalar(255,0,0));

        if (show_img) {
                for (int i=0; i<scene.size(); i++)
                {
                        cv::circle(image,cv::Point(scene[i].x,scene[i].y),2,cv::Scalar(0,255,0),8,0);

                }
                cv::imshow(OPENCV_WINDOW, image);
                cv::waitKey(3);

        }
        return;
}

void surf_detector::callBack(const sensor_msgs::ImageConstPtr& msg)
{
        if (this->enable) {
                this->Converter(msg);
                this->surf_extractor();
                this->match();
                this->locate();
        }
        return;
}

cv::Point2f surf_detector::get_center(std::vector<cv::Point2f> scene_corners)
{
        cv::Mat centroid;
        std_msgs::Float32MultiArray cnt_msg;
        cv::reduce(scene_corners, centroid, 01, CV_REDUCE_AVG);
        double area=get_area(scene_corners);
        cnt_msg.data.push_back(centroid.at<float>(0,0)); //x
        cnt_msg.data.push_back(centroid.at<float>(0,1)); //y
        cnt_msg.data.push_back(area); //area
        double img_area=image.rows*image.cols;
        if(cnt_msg.data[0]<image.rows && cnt_msg.data[1]<image.cols
           && cnt_msg.data[0]>0 && cnt_msg.data[1]>0 && area>0 && area < img_area)
        {
                //theyr were backwards
                std::cout << "Sending ";
                point_pub.publish(cnt_msg);
        }

        cv::Point2f mean(centroid.at<float>(0,0), centroid.at<float>(0,1));
        printf("Centroid @ (%f,%f) with area: %lf \n",mean.x,mean.y,area);
        return mean;
}


double surf_detector::get_area(std::vector<cv::Point2f> scene_corners)
{
        double area = 0;
        int last = scene_corners.size();
        int j = last - 1;
        for (int i = 0; i < last; i++)
        {
                area += (scene_corners[j].x + scene_corners[i].x) * (scene_corners[j].y - scene_corners[i].y);
                j = i; // j is previous vertex to i
        }

        return abs(area/2);
}
