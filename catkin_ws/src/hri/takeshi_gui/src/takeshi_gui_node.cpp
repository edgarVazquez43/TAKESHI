#include <iostream>
#include <QApplication>
#include "takeshi_tools/TakeshiHardware.h"
#include "MainWindow.h"
#include "QtRosNode.h"

int main(int argc, char** argv)
{
    std::cout << "INITIALIZING Takeshi GUI BY MARCOSOFT" << std::endl;
    ros::init(argc, argv, "takeshi_gui");
    ros::NodeHandle n;

    std::string locationsPath = "";
    for (int i = 0; i < argc; i++) {
      std::string strParam(argv[i]);
      if (strParam.compare("-p") == 0)
        locationsPath = argv[++i];
    }

    QtRosNode qtRosNode;
    qtRosNode.setNodeHandle(&n);
    qtRosNode.start();

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setRosNode(&qtRosNode);
    mainWindow.setPathKnownLoc(locationsPath);

    mainWindow.show();
    return app.exec();
}
