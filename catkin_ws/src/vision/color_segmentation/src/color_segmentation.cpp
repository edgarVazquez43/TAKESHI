#include "color_segmentation.h"

color_segmentation::color_segmentation(float termDistance, float epsilon,
                                       int codebookSize, unsigned int maxIter,
                                       float mx_dst, float mn_dst,
                                       bool dbg) : it_(nh),
        debug(dbg), max_distance(mx_dst), min_distance(mn_dst)
{
        //image_pub_ = it_.advertise("/image_converter/output_video", 1);
        printf("Starting LBG color segmentation by Coyo \n" );
        image_sub_ = it_.subscribe("/image", 1,
                                   &color_segmentation::callBack, this);
        load_sub = nh.subscribe("/seg_reg",1, &color_segmentation::load_cb,this);
        this->termDistance=termDistance;
        this->epsilon=epsilon;
        this->codebookSize=codebookSize;
        this->maxIter = maxIter;
        train=true;
        // this->cacheImages=0;
        // this->imgToUse=1;
        this->regToSegment=0;
        if(debug) {
                cv::namedWindow(OPENCV_WINDOW_D);
                cv::namedWindow(OPENCV_WINDOW_S);
        }
        return;
}
color_segmentation::~color_segmentation(){
        if (debug) {
                cv::destroyAllWindows();
        }
}

void color_segmentation::enable_cb(const std_msgs::Bool& en)
{
        enable=en.data;
        std::cout << "Setting color_segmentation enable as " << enable<<'\n';
        return;
}

void color_segmentation::load_cb(const std_msgs::Int16& msg)
{
        regToSegment=msg.data;
        return;
}

void color_segmentation::callBack(const sensor_msgs::ImageConstPtr& msg)
{
        cv::Mat segImage;
        cv::Mat paintImg;
        Converter(msg);
        //toVector(image_lab);
        // if (cacheImages<imgToUse)
        // {
        //         cacheImages++;
        // }

        if(train)
        {
                std::cout << "Starting quantization" << '\n';
                //LBG(optimalCodebook,optimalLabels);
                k_medias(optimalCodebook,optimalLabels);
                segImage= cv::Mat(optimalLabels).reshape(1,image_lab.rows);
                segImage.convertTo(segImage,CV_8UC1);
                train=false;
                color_space.clear();
                dropWhitesAndBlacks();
        }
        else
        {
                //segImage=quantize(image_lab,optimalCodebook);
                cv::Mat3f float_img;
                image_lab.convertTo(float_img,CV_32FC3);
                std::vector<cv::Rect> bounding_boxes;
                cv::Mat3f difference_map = float_img-optimalCodebook[regToSegment];
                cv::Mat1f distance_map = getNorm(difference_map);
                cv::inRange(distance_map,min_distance,max_distance,segImage );
                getContours(segImage,bounding_boxes);

                //cv::normalize(distance_map, paintImg, 0, 255,cv::NORM_MINMAX,CV_8UC1);
                paintImg = quantize(image_lab,optimalCodebook);
                if (debug)
                {

                        for (size_t i = 0; i < bounding_boxes.size(); i++) {
                                cv::Mat colorBGR;
                                cv::Mat tmpLab(1,1,CV_8UC3,cv::Vec3b(optimalCodebook[regToSegment]));
                                cv::cvtColor(tmpLab,colorBGR,56);                           //COLOR_Lab2BGR);
                                cv::Scalar scalarColor(colorBGR.data[0],colorBGR.data[1],colorBGR.data[2]);
                                cv::rectangle(image_bgr,bounding_boxes[i].tl(),bounding_boxes[i].br(),scalarColor,4);
                        }
                }
        }

        if(!segImage.empty() && !paintImg.empty() &&  debug)
        {
                // segImage*=(255/optimalCodebook.size());
                // cv::applyColorMap(segImage,coloredLabeled,cv::COLORMAP_HSV);
                //segImage*=(255);/optimalCodebook.size());
                cv::imshow(OPENCV_WINDOW_D,image_bgr);

                cv::imshow(OPENCV_WINDOW_S,paintImg*255/optimalCodebook.size());
                cv::waitKey(10);
        }
        return;
}

void color_segmentation::dropWhitesAndBlacks()
{
        //A lot of colors are actually shades of white. Remove all colors close
        //to white. Lightness channel >100
        //Same with blacks <50
        for (size_t i = 0; i < optimalCodebook.size(); i++) {
                if (optimalCodebook[i][0]>100 || optimalCodebook[i][0]<40) {
                        optimalCodebook.erase(optimalCodebook.begin()+i);
                }
        }
        std::cout << "Size after eliminating whites" << optimalCodebook.size()<< '\n';
}


void color_segmentation::getContours(cv::Mat &segImg,std::vector<cv::Rect> &outContours)
{
        cv::Mat element = getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(11,11), cv::Point( 5,5));
        cv::dilate(segImg,segImg, element);
        cv::erode(segImg,segImg, element);

        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours( segImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
        //std::sort(contours.begin(),contours.end(),color_segmentation::compareContourAreas);
        double min_area=image_lab.rows*image_lab.cols*0.01;
        double max_area=image_lab.rows*image_lab.cols*0.5;
        for (size_t i = 0; i < contours.size(); i++)
        {
                double area = cv::contourArea(cv::Mat(contours[i]));
                if (area > min_area && area < max_area)
                {
                        outContours.push_back(cv::boundingRect( cv::Mat(contours[i]) ));
                }
        }


        return;
}

void color_segmentation::Converter(const sensor_msgs::ImageConstPtr& msg)
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

        image_bgr =cv_ptr->image;
        //image_lab = cv::Mat(bgr.rows,bgr.cols,CV_32FC3);
        cv::GaussianBlur( image_bgr, image_bgr, cv::Size( 11, 11 ), 0, 0 );
        cv::cvtColor(image_bgr,image_lab,44);
        // else
        // {
        //         cv::Mat distorted=cv_ptr->image;
        //         undistort(distorted,this->image,cameraMatrix,rectCoeff  );
        // }

        return;
}

cv::Mat color_segmentation::quantize(const cv::Mat & img, const std::vector<cv::Vec3f> codebook)
{
        cv::Mat labeledImage = cv::Mat(img.rows,img.cols, CV_8UC1);
        for (size_t y = 0; y < img.rows; y++)
        {
                const cv::Vec3b * sample = img.ptr<cv::Vec3b>(y);
                uchar * label = labeledImage.ptr<uchar>(y);

                for (size_t x = 0; x < img.cols; x++)
                {
                        cv::Vec3f smp(sample[x]);
                        double minDistance=cv::norm(codebook[0],smp,cv::NORM_L2);
                        label[x]=0;
                        //std::cout << sample[x] << std::endl;
                        for (size_t j = 1; j < codebook.size(); j++)
                        {
                                //std::cout << codebook[j] << '\n';
                                double distance=cv::norm(codebook[j],smp,cv::NORM_L2);
                                if(distance<minDistance)
                                {
                                        minDistance = distance;
                                        label[x]=j;
                                }
                                //std::cout << label[x] << '\n';

                        }
                }
        }

        return labeledImage;
}

cv::Mat1f color_segmentation::getNorm(const cv::Mat3f &inputImg)
{
        //Calculates the L2 norm for every 3 element pixels in image
        cv::Mat1f normImage(inputImg.rows, inputImg.cols,CV_32F);
        for (size_t y = 0; y < inputImg.rows; y++)
        {
                const cv::Vec3f * sample = inputImg.ptr<cv::Vec3f>(y);
                float* output_row = normImage.ptr<float>(y);
                for (size_t x = 0; x < inputImg.cols; x++)
                {
                        output_row[x]=cv::norm(sample[x],cv::NORM_L2);
                        //std::cout << output_row[x] << ',';
                }
                //std::cout<< '\n';
        }

        return normImage;
}



void color_segmentation::toVector(const cv ::Mat &img)
{
        //color_space.clear();
        for (size_t y = 0; y < img.rows; y++)
        {
                const cv::Vec3b * ptr = img.ptr<cv::Vec3b>(y);
                for (size_t x = 0; x < img.cols; x++)
                {
                        this->color_space.push_back(ptr[x]);
                }
        }
        //this code is equivalent to the snippet before
        //color_space.assign(image_lab.begin<cv::Vec3b>(),image_lab.end<cv::Vec3b>());
        return;
}

void color_segmentation::toVector(const cv ::Mat &img, std::vector<cv::Vec3f> &v)
{
        v.clear();
        for (size_t y = 0; y < img.rows; y++)
        {
                const cv::Vec3f * ptr = img.ptr<cv::Vec3f>(y);
                for (size_t x = 0; x < img.cols; x++)
                {
                        std::cout << ptr[x] << '\n';
                        v.push_back(ptr[x]);
                }
        }
        //this code is equivalent to the snippet before
        //color_space.assign(image_lab.begin<cv::Vec3b>(),image_lab.end<cv::Vec3b>());
        return;
}

void color_segmentation::k_medias(std::vector<cv::Vec3f> &codebook, std::vector<int> &labels)
{
        // Cluster
        labels.clear();
        codebook.clear();
        int n = image_lab.rows * image_lab.cols;
        cv::Mat data = image_lab.reshape(3, n);
        data.convertTo(data, CV_32FC3);

        cv::Mat centers;

        cv::kmeans(data, codebookSize, labels,
                   cv::TermCriteria( cv::TermCriteria::EPS+cv::TermCriteria::COUNT, maxIter, termDistance),
                   1, cv::KMEANS_PP_CENTERS, centers);
        toVector(centers.reshape(3,codebook.size()),codebook);
        return;

}

void color_segmentation::LBG(std::vector<cv::Vec3f> &codebook, std::vector<int> &labels)
{
        //uses Linde-Buzo-Gray to segment
        //Convert to lab
        //cv::COLOR_COLOR_BGR2lab);
        //color_samples = image_lab.reshape(1, image_lab.cols*image_lab.rows);
        //cv::Mat centroid= getCentroid(color_samples);
        //convert to std::vector
        color_space.assign(image_lab.begin<cv::Vec3b>(),image_lab.end<cv::Vec3b>());
        cv::Vec3f centroid= getCentroid(color_space);
        std::vector<cv::Vec3f> prevCodebook;
        prevCodebook.push_back(centroid);
        std::vector<std::vector<cv::Vec3f> > regions;

        while (prevCodebook.size()<codebookSize)
        {
                codebook.clear();
                for (size_t i = 0; i < prevCodebook.size(); i++)
                {
                        codebook.push_back(prevCodebook[i]+cv::Vec3f(epsilon,epsilon,epsilon));
                        codebook.push_back(prevCodebook[i]-cv::Vec3f(epsilon,epsilon,epsilon));
                }
                double globalDistancePrev=0, globalDistance=0;
                unsigned int iter=0;
                while (iter<maxIter)
                {
                        globalDistance=getDistances(codebook,color_space,regions,labels);

                        for (size_t i = 0; i < codebook.size(); i++)
                        {
                                codebook[i]=getCentroid(regions[i]);

                        }

                        if(fabs(globalDistance-globalDistancePrev)<termDistance)
                        {
                                break;
                        }
                        iter++;
                        globalDistancePrev=globalDistance;
                }
                printf(" Error %lf-%lf= %lf \n", globalDistancePrev,globalDistance,(globalDistancePrev-globalDistance));
                prevCodebook=codebook;
        }
        printf("Optimal Codebook Codebook\n" );
        printCodebook(codebook);


        // std::cout << centroid << '\n';
        return;
}



cv::Vec3f color_segmentation::getCentroid(const std::vector<cv::Vec3f> & region)
{
        std::vector<cv::Vec3f> centroid;
        cv::reduce(region,centroid,1,CV_REDUCE_AVG);
        cv::Vec3f cnt(centroid[0] );
        return cnt;

}

cv::Mat color_segmentation::getCentroid(const cv::Mat &region)
{
        cv::Mat centroid;
        cv::reduce(region,centroid,0,CV_REDUCE_AVG);
        return centroid;

}

void color_segmentation::printCodebook(const std::vector<cv::Vec3f> & codebook)
{
        for (size_t i = 0; i < codebook.size(); i++) {
                std::cout << codebook[i] << '\n';
        }
        std::cout << '\n';
        return;
}

double color_segmentation::getDistances(std::vector<cv::Vec3f> &codebook,
                                        const std::vector<cv::Vec3f> &color_samples,
                                        std::vector<std::vector<cv::Vec3f> > &regions,
                                        std::vector<int> &labels)
{
        regions.resize(codebook.size());
        clearRegions(regions);
        double minDistance;
        double minGlobalDistance=0;
        int reg;
        labels.clear();
        for (size_t i = 0; i < color_samples.size(); i++)
        {
                minDistance=cv::norm(codebook[0],color_samples[i],cv::NORM_L1);
                reg=0;
                for (size_t j = 1; j < codebook.size(); j++)
                {
                        double distance=cv::norm(codebook[j],color_samples[i],cv::NORM_L1);
                        if(distance<minDistance)
                        {
                                minDistance = distance;
                                reg = j;
                        }

                }
                regions[reg].push_back(color_samples[i]);
                labels.push_back(reg);
                //std::cout << "Vector: " << color_samples[i] <<" belongs to reg "<< reg <<'\n';
                minGlobalDistance+=minDistance;
        }
        return minGlobalDistance;
}

void color_segmentation::clearRegions(std::vector<std::vector<cv::Vec3f> > &regions)
{
        for (size_t i = 0; i < regions.size(); i++)
        {
                regions[i].clear();
        }
        return;
}
