#include "sat_segmentation.h"

satSegmentation::satSegmentation(ros::NodeHandle nh) :
        nh_(nh), it_(nh_)
{
        printf("Starting saturation detector, for IKEA Kalas\n");
        nh_.param<int>("minSat",minSat,150);
        nh_.param<int>("maxSat",maxSat,255);
        nh_.param<bool>("debug",dbg,false);
        // <param name="y_center" value="180"/>
        // <param name="x_center" value="120"/>
        nh_.param<float>("x_center",img_center.x,120);
        nh_.param<float>("y_center",img_center.y,180);

        image_sub_ = it_.subscribe("/image", 1,
                                   &satSegmentation::callBack, this);
        en_sub = nh_.subscribe("/en_sat_seg",1,
                               &satSegmentation::enable_cb,this);
        obj_publisher = nh_.advertise<std_msgs::Float32MultiArray>("/hand/object",1);
        this->enable=false;

        if(dbg) {
                cv::namedWindow(OPENCV_WINDOW);

        }
        return;
}

satSegmentation::~satSegmentation(){
        if (dbg) {
                cv::destroyAllWindows();
        }
}

void satSegmentation::enable_cb(const std_msgs::Bool& en)
{
        enable=en.data;
        std::cout << "Setting sat_segmentation enable as " << enable<<'\n';
        return;
}


void satSegmentation::callBack(const sensor_msgs::ImageConstPtr& msg)
{
        if (enable)
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
                cv::Mat tmp =cv_ptr->image;
                cv::Mat masked=  Convert(tmp);
                std::vector<cv::RotatedRect> RR;
                Contouring(masked,RR);
                if (RR.size()>0)
                {
                        findClosestAndPublish(RR);

                        if (dbg)
                        {
                                // cv::Mat splitted[3];
                                // cv::split(hsv,splitted);
                                // cv::imshow("Canal H",splitted[0]);
                                // cv::imshow("Canal S",splitted[1]);
                                // cv::imshow("Canal V",splitted[2]);
                                drawRotatedRects(RR);
                                cv::imshow(OPENCV_WINDOW,bgr);
                                cv::waitKey(20);
                        }
                }

        }
        return;
}

void satSegmentation::findClosestAndPublish(std::vector<cv::RotatedRect> &rRects)
{
        //  std::sort(rRects.begin(),rRects.end(),satSegmentation::closestToCenter);
        cv::RotatedRect closer = closestToCenter(rRects);
        cv::Point2f centerCloser=closer.center;
        float angleCloser=closer.angle;
        if (dbg) {
                cv::circle(bgr,centerCloser,5,cv::Scalar(255,0,0),2);
        }
        std_msgs::Float32MultiArray msg;
        msg.data.push_back(centerCloser.x);
        msg.data.push_back(centerCloser.y);
        msg.data.push_back(angleCloser);
        obj_publisher.publish(msg);
        return;

}

cv::Mat satSegmentation::Convert(cv::Mat &tmp)
{
        cv::Mat msk;
        cv::Rect roi(tmp.cols/4,tmp.rows/8,tmp.cols*3/4,tmp.rows*3/4);
        bgr=tmp(roi);
        cv::cvtColor(bgr,hsv,40);
        cv::inRange(hsv,cv::Scalar(0,minSat,30),cv::Scalar(255,maxSat,220),msk);
        cv::Mat element = getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(7,7), cv::Point( 5,5));
        cv::morphologyEx( msk, msk, cv::MORPH_OPEN, element );
        return msk;
}

void satSegmentation::Contouring(cv::Mat mask,  std::vector<cv::RotatedRect> & rotatedRects)
{
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours( mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
        // Find the rotated rectangles for each contour
        //rotatedRects.resize( contours.size() );
        for( int i = 0; i < contours.size(); i++ )
        {
                cv::RotatedRect tmpRec;
                tmpRec = cv::minAreaRect( cv::Mat(contours[i]) );
                cv::Size2f tmpSize= tmpRec.size;
                double mskSize = mask.rows*mask.cols;
                //eliminate speckles in mask
                if (tmpSize.height*tmpSize.width>=0.01*mskSize)
                {

                        rotatedRects.push_back(tmpRec);
                }
        }
        return;
}



cv::RotatedRect satSegmentation::closestToCenter ( std::vector<cv::RotatedRect> &r) {
        //returns rotated rectangle closest to center
        //cv::Point2f img_center(bgr.cols/2,bgr.rows/2);
        int minIdx = 0;
        int n=0;
        double minD = cv::norm(r[0].center-img_center);
        for ( n = 1; n < r.size(); n++)
        {
                cv::Point2f p1(r[n].center);
                double D =  cv::norm(p1-img_center);
                if(D<minD)
                {
                        minIdx=n;
                        minD=D;
                }
        }
        //std::cout << minIdx << '\n';
        return r[minIdx];
}

void satSegmentation::drawRotatedRects(std::vector<cv::RotatedRect> &rotated)
{
        for (size_t i = 0; i < rotated.size(); i++)
        {
                cv::Point2f pts[4];
                rotated[i].points(pts);
                for (size_t j = 0; j < 4; j++)
                {
                        cv::line(bgr, pts[j], pts[(j+1)%4], cv::Scalar(0,255,0));
                }
        }
        return;
}
