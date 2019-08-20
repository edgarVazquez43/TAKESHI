#include "QtRosNode.h"

QtRosNode::QtRosNode()
{
    this->gui_closed = false;
}

QtRosNode::~QtRosNode()
{
}

void QtRosNode::run()
{
    ros::Rate loop(10);
    while(ros::ok() && !this->gui_closed)
    {
        //std::cout << "Ros node running..." << std::endl;
        emit updateGraphics();
        loop.sleep();
        ros::spinOnce();
    }
    emit onRosNodeFinished();
}

void QtRosNode::setNodeHandle(ros::NodeHandle* nh)
{
    this->n = nh;
    TakeshiHardware::setNodeHandle(nh);
    TakeshiNavigation::setNodeHandle(nh);
    TakeshiHRI::setNodeHandle(nh);
    TakeshiManip::setNodeHandle(nh);
    TakeshiVision::setNodeHandle(nh);
    TakeshiTools::setNodeHandle(nh);
    TakeshiKnowledge::setNodeHandle(nh);
    TakeshiRepresentation::setNodeHandle(nh);
}
