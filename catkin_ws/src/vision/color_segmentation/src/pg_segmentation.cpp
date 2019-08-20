#include "pg_segmentation/pg_segmentation.h"

pgSegmentation::pgSegmentation(ros::NodeHandle &nodeHandle_, bool debug) : nh_(nodeHandle_), it_(nodeHandle_  )
{

        ROS_INFO("Starting: P&G color segmentation port by Abel, feat Coyo");
        loadKnowledgeBase();
        printKnowledgeBase();
        this->debug = debug;
        this->enable = false;
        image_sub_ = it_.subscribe("/image", 1,
                                   &pgSegmentation::callBack, this);
        // enable_sub = nh_.subscribe("/enable_surf",1,&surf_detector::enable_cb,this);
        // load_sub = nh_.subscribe("/load_surf_recog",1,&surf_detector::load_cb,this);
        // point_pub=nh_.advertise<std_msgs::Float32MultiArray>("/hand/object", 1);
        if(this->debug) {
                cv::namedWindow(win_name);
        }
        return;
}

pgSegmentation::~pgSegmentation(){
        if(debug) {
                cv::destroyWindow(win_name);
        }
}

void pgSegmentation::callBack(const sensor_msgs::ImageConstPtr& msg)
{
        enable=true;
        if (enable)
        {
                Converter(msg);
                cv::Mat element = getStructuringElement( cv::MORPH_ELLIPSE, cv::Size(11,11), cv::Point( 5,5));
                std::vector<cv::Rect> boxes(color_models.size());
                cv::Rect box;
                for (size_t j = 0; j < color_models.size(); j++)
                {
                        //loop over all color models and return when one is found;
                        cv::Mat segmented=  segmentColor(color_models[j],frame,element);
                        box= contouring(segmented);
                        boxes[j]= box;

                }
                if (debug)
                {
                        for (size_t i = 0; i < boxes.size(); i++) {
                                rectangle( frame, boxes[i].tl(), boxes[i].br(), color_models[i].min, 2, 8, 0 );
                                cv::putText(frame,color_models[i].name,boxes[i].tl(), cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(250,250,250));
                        }
                        cv::imshow(win_name,frame);
                        cv::waitKey(10);
                }
        }
        return;
}

cv::Mat pgSegmentation::segmentColor(models model,cv::Mat &bgr,cv::Mat &element)
{
        cv::Mat input;
        switch (model.mtd) {
        case METHOD_BGR:
                input = bgr;
                break;
        case METHOD_HSV:
                cvtColor(bgr, input, CV_BGR2HSV);
                break;
        case METHOD_HLS:
                cvtColor(bgr, input, CV_BGR2HLS);
                break;
        }

        cv::Mat mask;

        cv::inRange(input,model.min,model.max,mask);
        cv::dilate(mask,mask, element);
        cv::erode(mask,mask, element);
        return mask;
}

void pgSegmentation::printKnowledgeBase()
{
        for (size_t i = 0; i < color_models.size(); i++) {
                std::cout << "Name [" <<i<<"] " << color_models[i].name << "\t";
                std::cout << " Min Color " << color_models[i].min<< "\t";
                std::cout << " Max Color " << color_models[i].max<< "\t";
                std::cout << " Method " <<color_models[i].mtd << '\n';
        }
        return;
}
void pgSegmentation::setObject(std::string name, segMethod methodSegmentation,
                               cv::Scalar minScalarSegmentation,cv::Scalar maxScalarSegmentation, float averageAreaPixels)
{
        models mod;
        mod.name =name;
        mod.mtd = methodSegmentation;
        mod.min = minScalarSegmentation;
        mod.max = maxScalarSegmentation;
        mod.avgArea = averageAreaPixels;
        color_models.push_back(mod);
}

void pgSegmentation::Converter(const sensor_msgs::ImageConstPtr& msg)
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
        this->frame=cv_ptr->image;
        return;
}

cv::Rect pgSegmentation::contouring(cv::Mat mask)
{
        //mask:segmented binary mask.
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours( mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
        std::vector<cv::Rect> boundRect;
        std::sort(contours.begin(),contours.end(),pgSegmentation::compareContourAreas);
        for (size_t i = 0; i < contours.size(); i++)
        {
                boundRect.push_back(cv::boundingRect( cv::Mat(contours[i]) ));
        }


        if (boundRect.size()==0)
        {
                boundRect.push_back(cv::Rect(0,0,0,0)); //emtpy rect
        }
        return boundRect[0];
}

bool pgSegmentation::compareContourAreas ( std::vector<cv::Point> contour1, std::vector<cv::Point> contour2 ) {

        double i = fabs( cv::contourArea(cv::Mat(contour1)) );
        double j = fabs( cv::contourArea(cv::Mat(contour2)) );
        return ( i > j );
}
//
// bool pgSegmentation::loadKnowledgeBase(string path_file){
//         loadKnowledgeBase();
// }

void pgSegmentation::loadKnowledgeBase(int i){
        //shameles hardcoded HSV values
        cv::Scalar minScalar;
        cv::Scalar maxScalar;
        color_models.clear();

        //AZULES --- HSV
        minScalar = cv::Scalar(100, 162, 130);
        maxScalar = cv::Scalar(107, 239, 219);
        setObject("dish", METHOD_HSV, minScalar,maxScalar,14000 );
        setObject("bowl", METHOD_HSV, minScalar, maxScalar,6000 );
        setObject("glass", METHOD_HSV, minScalar, maxScalar,3800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,1600 );
        //NARANJAS TRANSPARENTES --- HSV
        minScalar = cv::Scalar(3, 119, 184);
        maxScalar = cv::Scalar(16, 189, 255);
        setObject("dish", METHOD_HSV, minScalar,maxScalar, 14000 );
        setObject("bowl", METHOD_HSV, minScalar, maxScalar,6000 );
        setObject("glass", METHOD_HSV, minScalar, maxScalar,3800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,1600 );
        //NARANJAS --- BGR
        minScalar = cv::Scalar(0, 0, 206);
        maxScalar = cv::Scalar(8, 53, 243);
        setObject("dish", METHOD_BGR, minScalar,maxScalar, 14000 );
        setObject("bowl", METHOD_BGR, minScalar, maxScalar,6000 );
        setObject("glass", METHOD_BGR, minScalar, maxScalar,3800 );
        setObject("cutlery", METHOD_BGR, minScalar, maxScalar,800 );
        setObject("cutlery", METHOD_BGR, minScalar, maxScalar,1600 );

        //ROJO transparentes --- HSV
        minScalar = cv::Scalar(165, 235, 162);
        maxScalar = cv::Scalar(172, 255, 198);
        setObject("dish", METHOD_HSV, minScalar,maxScalar,14000 );
        setObject("bowl", METHOD_HSV, minScalar, maxScalar,6000);
        setObject("glass", METHOD_HSV, minScalar, maxScalar,3800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,1600 );
        //ROJOS BGR
        minScalar = cv::Scalar(0, 0, 143);
        maxScalar = cv::Scalar(112, 14, 204);
        setObject("dish", METHOD_BGR, minScalar,maxScalar,14000 );
        setObject("bowl", METHOD_BGR, minScalar, maxScalar,6000);
        setObject("glass", METHOD_BGR, minScalar, maxScalar,3800 );
        setObject("cutlery", METHOD_BGR, minScalar, maxScalar,800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,1600 );

        //MORADOS --- HSV
        minScalar = cv::Scalar(150, 119, 84);
        maxScalar = cv::Scalar(165, 255, 169);
        setObject("dish", METHOD_HSV, minScalar,maxScalar,14000 );
        setObject("bowl", METHOD_HSV, minScalar, maxScalar,6000);
        setObject("glass", METHOD_HSV, minScalar, maxScalar,3800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,1600 );
        //AMARILLOS --- HSV
        minScalar = cv::Scalar(26, 244, 154);
        maxScalar = cv::Scalar(28, 255, 255);
        setObject("dish", METHOD_HSV, minScalar,maxScalar,14000 );
        setObject("bowl", METHOD_HSV, minScalar, maxScalar,6000);
        setObject("glass", METHOD_HSV, minScalar, maxScalar,3800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,800 );
        setObject("cutlery", METHOD_HSV, minScalar, maxScalar,1600 );

}

void pgSegmentation::loadKnowledgeBase(){
        //shameles hardcoded HSV values
        cv::Scalar minScalar;
        cv::Scalar maxScalar;
        color_models.clear();

        //AZULES --- HSV
        minScalar = cv::Scalar(100, 162, 130);
        maxScalar = cv::Scalar(107, 239, 219);
        setObject("azul", METHOD_HSV, minScalar,maxScalar,14000 );
        //NARANJAS TRANSPARENTES --- HSV
        minScalar = cv::Scalar(3, 119, 184);
        maxScalar = cv::Scalar(16, 189, 255);
        setObject("oranges_light", METHOD_HSV, minScalar,maxScalar, 14000 );
        //NARANJAS --- BGR
        minScalar = cv::Scalar(0, 0, 206);
        maxScalar = cv::Scalar(8, 53, 243);
        setObject("orange", METHOD_BGR, minScalar,maxScalar, 14000 );

        //ROJO transparentes --- HSV
        minScalar = cv::Scalar(165, 235, 162);
        maxScalar = cv::Scalar(172, 255, 198);
        setObject("red_hsv", METHOD_HSV, minScalar,maxScalar,14000 );
        //ROJOS BGR
        minScalar = cv::Scalar(0, 0, 143);
        maxScalar = cv::Scalar(112, 14, 204);
        setObject("red", METHOD_BGR, minScalar,maxScalar,14000 );
        //was a bug here

        //MORADOS --- HSV
        minScalar = cv::Scalar(150, 119, 84);
        maxScalar = cv::Scalar(165, 255, 169);
        setObject("morados", METHOD_HSV, minScalar,maxScalar,14000 );
        //AMARILLOS --- HSV
        minScalar = cv::Scalar(26, 244, 154);
        maxScalar = cv::Scalar(28, 255, 255);
        setObject("yellow", METHOD_HSV, minScalar,maxScalar,14000 );


}
