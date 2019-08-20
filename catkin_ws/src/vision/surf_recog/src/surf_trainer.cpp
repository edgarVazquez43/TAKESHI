#include "surf_trainer.h"


surf_trainer::surf_trainer() : it_(nh_)
{
        image_sub_ = it_.subscribe("/image", 1,
                                   &surf_trainer::surfCallBack, this);
        //image_pub_ = it_.advertise("/image_converter/output_video", 1);
        counter=0;

        std::string configDir = ros::package::getPath("surf_recog") + "/config";
        // if( !boost::filesystem::exists(configDir ) )
        //         boost::filesystem::create_directory(configDir);
        filename =configDir+"/trained.xml";
        //printf("Saving to %s\n", filename.c_str() );
        cv::namedWindow(OPENCV_WINDOW);
        cv::setMouseCallback(OPENCV_WINDOW,surf_trainer::onClick,this);
}

surf_trainer::surf_trainer(std::string file, int minHessian) : it_(nh_)
{
        image_sub_ = it_.subscribe("/image", 1,
                                   &surf_trainer::surfCallBack, this);
        //image_pub_ = it_.advertise("/image_converter/output_video", 1);
        counter=0;
        this->filename=file;
        this->minHessian=minHessian;
        printf("Saving to %s\n", filename.c_str() );
        cv::namedWindow(OPENCV_WINDOW);
        cv::setMouseCallback(OPENCV_WINDOW,surf_trainer::onClick,this);
}


surf_trainer::~surf_trainer(){

        cv::destroyWindow(OPENCV_WINDOW);
}

void surf_trainer::surfCallBack(const sensor_msgs::ImageConstPtr& msg)
{

        this->surfConverter(msg);
        this->surf_extractor();
        return;
}

void surf_trainer::surfConverter(const sensor_msgs::ImageConstPtr& msg)
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


        return;
}

void surf_trainer::surf_extractor()
{
        cv::Ptr<cv::Feature2D> surf = cv::xfeatures2d::SURF::create(minHessian);

        if (counter<2)
        {
                surf->detect(this->image,keypoints);
                cv::drawKeypoints(this->image,keypoints,this->image,cv::Scalar(255,0,0));
        }
        else if(counter >= 2)
        {
                //cv::Mat mask = cv::Mat::zeros(image.size,cv::CV_8UC1 );
                cv::Mat mask;

                mask = cv::Mat::zeros(image.size(), 0); //cv::CV_8UC1 ); No idea why can't parse the constant

                // std::vector<std::vector<cv::Point> > poly_fill;
                // poly_fill.push_back(roi_corners);
                // cv::fillPoly(mask,poly_fill,cv::Scalar(200,200,200));
                cv::Rect roi(roi_corners[0],roi_corners[1]);
                cv::rectangle(mask,roi,cv::Scalar(250,250,250),-1);

                surf->detect(this->image,keypoints,mask);
                surf->compute(this->image,keypoints,descriptors);
                cv::drawKeypoints(this->image,keypoints,this->image,cv::Scalar(0,250,0),1); //not rich keypoints

                //draw corner
                // for (int i = 1; i < roi_corners.size(); i++) {
                //         cv::line(this->image,roi_corners[i],roi_corners[i-1],cv::Scalar(0,255,0));
                // }
                // int last=roi_corners.size();
                // cv::line(this->image,roi_corners[0],roi_corners[last-1],cv::Scalar(0,255,0));

                cv::rectangle(this->image,roi,cv::Scalar(250,250,0));


        }

        cv::imshow(OPENCV_WINDOW, image);
        if(27==cv::waitKey(3)) //Scape key
        {
                save_keypoints();
        }
}

void surf_trainer::save_keypoints(  )
{

        printf("Saving to %s\n", filename.c_str() );
        cv::FileStorage fs(filename, cv::FileStorage::WRITE);
        cv::write(fs,"roi_corners",roi_corners);
        cv::write(fs, "keypoints", keypoints);
        cv::write(fs, "descriptors", descriptors);
        fs.release();
        return;

}

void surf_trainer::onClick(int event, int x, int y,int, void* ptr)
{
        if( event != cv::EVENT_LBUTTONDOWN )
                return;
        surf_trainer *that = (surf_trainer*)ptr;
        that->set_ROI_points(x,y);
        return;
}

void surf_trainer::set_ROI_points( int x, int y)
{
        if(counter >= 2)
        {
                roi_corners.clear();
                counter=0;
        }

        roi_corners.push_back(cv::Point(x,y));
        counter++;
        printf("Point: [%d, %d]\n",x,y);
}
