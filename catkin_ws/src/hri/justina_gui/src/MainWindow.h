#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <ros/package.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "takeshi_tools/TakeshiHardware.h"
#include "takeshi_tools/TakeshiNavigation.h"
#include "takeshi_tools/TakeshiHRI.h"
#include "takeshi_tools/TakeshiManip.h"
#include "takeshi_tools/TakeshiVision.h"
#include "takeshi_tools/TakeshiTools.h"
#include "takeshi_tools/TakeshiRepresentation.h"

#include "QtRosNode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QtRosNode* qtRosNode;
    float robotX;
    float robotY;
    float robotTheta;
    float headPan;
    float headTilt;
    float trsCurrentPos;

    std::vector<float> ikResponse_articular;
    float ikResponse_torso;
    geometry_msgs::Pose2D ikResponse_base_correction;

    std::vector<float> leftArmPoses;
    std::vector<float> leftArmTorques;
    std::vector<float> rightArmPoses;
    std::vector<float> rightArmTorques;
    bool laIgnoreValueChanged;
    bool raIgnoreValueChanged;
    int laLastRadioButton;
    int raLastRadioButton;
    nav_msgs::Path calculatedPath;
    bool recSavingVideo;
    bool sktRecognizing;
    bool facRecognizing;
    bool hriFollowing;
    bool hriFindingLegs;
    bool navDetectingObstacles;
    bool initKnownLoacations;
    bool defInitKnownLoacations;
    bool updateKnownLoacations;
    bool enableInteractiveEdit;

    std::map<std::string, std::vector<std::string> > locations;
    std::map<std::string, std::vector<std::string> > objects;

    void setRosNode(QtRosNode* qtRosNode);
    void closeEvent(QCloseEvent *event);
    void setPathKnownLoc(const std::string pathKnownLoc);

private:
    bool strToFloatArray(std::string str, std::vector<float>& result);

public slots:
    //Slots for signals emitted in this window (e.g.: pressing buttons)
    void stopRobot();
    //Navigation
    void navBtnCalcPath_pressed();
    void navBtnExecPath_pressed();
    void navMoveChanged();
    void navObsDetectionEnableClicked();
    //Hardware
    void hdPanTiltChanged(double d);
    //void laAnglesChanged(double);
    void laValuesChanged();
    void laOpenGripperChanged(double d);
    void raOpenGripperChanged(double d);
    void laCloseGripperChanged(double d);
    void raCloseGripperChanged(double d);
    void raRadioButtonClicked();
    void torsoPoseChanged(double d);
    void torsoLocChanged();
    void ikBtnCalc_pressed();
    void ikBtnExecute_pressed();

    //Takeshi Arm
    void armAnglesChanged(double);

    //Speech synthesis and recog
    void spgSayChanged();
    void sprFakeRecognizedChanged();
    //Vision
    void sktBtnStartClicked();
    void facBtnStartClicked();
    void facRecogPressed();
    void facTrainPressed();
    void facClearPressed();
    void objRecogObjectChanged();
    void vsnFindLinesClicked();
    //HRI
    void hriBtnFollowClicked();
    void hriBtnLegsClicked();
    //Slots for signals emitted in the QtRosNode (e.g. a topic is received)
    void updateGraphicsReceived();
    //Slots for signad to tab knowledge
    void on_enInteractiveEdit_clicked();
    void on_removeLoc_clicked();
    void on_locTableWidget_itemSelectionChanged();
    void on_addLoc_clicked();
    void on_GetRobotPose_clicked();
    void on_loadFromFile_clicked();
    void on_SaveInFile_clicked();
    void quesReqChanged();
    //slots for knowledge representation
    void enterCommandChanged();
    void loadCommandChanged();
    void on_runCLIPS_clicked();
    void setPathKR();
    void setlocClips();

private slots:


    void on_resetCLIPS_clicked();

    void on_factsCLIPS_clicked();

    void on_rulesCLIPS_clicked();

    void on_agendaCLIPS_clicked();

    void on_openFileCommand_clicked();

    void on_addCLIPSloc_clicked();

    void on_addCLIPSobj_clicked();

    void on_locCLIPStab_itemSelectionChanged();

    void on_objCLIPStab_itemSelectionChanged();

    void on_trainObjButton_clicked();

private:
    Ui::MainWindow *ui;
    std::string pathKnownLoc;

    enum Column{
        NAME, X, Y, A, C1, C2, C3, C4
    };
};

#endif // MAINWINDOW_H
