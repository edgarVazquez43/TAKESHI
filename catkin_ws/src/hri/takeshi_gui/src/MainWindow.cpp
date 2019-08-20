#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtWidgets/QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->ui->laRbArticular->setChecked(true);
    this->laLastRadioButton = 0;
    this->raLastRadioButton = 0;
    this->recSavingVideo = false;
    this->facRecognizing = false;
    this->sktRecognizing = false;
    this->hriFollowing = false;
    this->hriFindingLegs = false;
    this->navDetectingObstacles = false;
    this->enableInteractiveEdit = false;
    setPathKR();

    //QObject::connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(stopRobot()));

    //Navigation
    QObject::connect(ui->navTxtStartPose, SIGNAL(returnPressed()), this, SLOT(navBtnCalcPath_pressed()));
    QObject::connect(ui->navTxtGoalPose, SIGNAL(returnPressed()), this, SLOT(navBtnCalcPath_pressed()));
    QObject::connect(ui->navBtnCalcPath, SIGNAL(clicked()), this, SLOT(navBtnCalcPath_pressed()));
    QObject::connect(ui->navBtnExecPath, SIGNAL(clicked()), this, SLOT(navBtnExecPath_pressed()));
    QObject::connect(ui->navTxtMove, SIGNAL(returnPressed()), this, SLOT(navMoveChanged()));
    QObject::connect(ui->navBtnStartObsDetection, SIGNAL(clicked()), this, SLOT(navObsDetectionEnableClicked()));
    //Hardware
    QObject::connect(ui->hdTxtPan, SIGNAL(valueChanged(double)), this, SLOT(hdPanTiltChanged(double)));
    QObject::connect(ui->hdTxtTilt, SIGNAL(valueChanged(double)), this, SLOT(hdPanTiltChanged(double)));
    QObject::connect(ui->laTxtAngles0, SIGNAL(valueChanged(double)), this, SLOT(armAnglesChanged(double)));
    QObject::connect(ui->laTxtAngles1, SIGNAL(valueChanged(double)), this, SLOT(armAnglesChanged(double)));
    QObject::connect(ui->laTxtAngles2, SIGNAL(valueChanged(double)), this, SLOT(armAnglesChanged(double)));
    QObject::connect(ui->laTxtAngles3, SIGNAL(valueChanged(double)), this, SLOT(armAnglesChanged(double)));
    QObject::connect(ui->laTxtOpenGripper, SIGNAL(valueChanged(double)), this, SLOT(laOpenGripperChanged(double)));
    QObject::connect(ui->laTxtCloseGripper, SIGNAL(valueChanged(double)), this, SLOT(laCloseGripperChanged(double)));
    //QObject::connect(ui->laTxtXYZ, SIGNAL(returnPressed()), this, SLOT(laValuesChanged()));
    //QObject::connect(ui->laTxtRPY, SIGNAL(returnPressed()), this, SLOT(laValuesChanged()));
    //QObject::connect(ui->laTxtElbow, SIGNAL(returnPressed()), this, SLOT(laValuesChanged()));
    //QObject::connect(ui->laRbCartesian, SIGNAL(clicked()), this, SLOT(laRadioButtonClicked()));
    //QObject::connect(ui->laRbCartesianRobot, SIGNAL(clicked()), this, SLOT(laRadioButtonClicked()));
    //QObject::connect(ui->laRbArticular, SIGNAL(clicked()), this, SLOT(laRadioButtonClicked()));

    //Torso
    QObject::connect(ui->trsTxtSpine, SIGNAL(valueChanged(double)), this, SLOT(torsoPoseChanged(double)));
    //QObject::connect(ui->trsTxtLoc, SIGNAL(returnPressed()), this, SLOT(torsoLocChanged()));

    //Speech synthesis and recog
    QObject::connect(ui->spgTxtSay, SIGNAL(returnPressed()), this, SLOT(spgSayChanged()));
    QObject::connect(ui->sprTxtFakeRecog, SIGNAL(returnPressed()), this, SLOT(sprFakeRecognizedChanged()));

    //Vision
    //QObject::connect(ui->recBtnSaveVideo, SIGNAL(clicked()), this, SLOT(recSaveVideoChanged()));
    QObject::connect(ui->recTxtImgFile, SIGNAL(returnPressed()), this, SLOT(recSaveImageChanged()));
    QObject::connect(ui->recBtnSaveImg, SIGNAL(clicked()), this, SLOT(recSaveImageChanged()));
    QObject::connect(ui->sktBtnStartRecog, SIGNAL(clicked()), this, SLOT(sktBtnStartClicked()));
    //QObject::connect(ui->facBtnStartRecog, SIGNAL(clicked()), this, SLOT(facBtnStartClicked()));
    //QObject::connect(ui->facTxtRecog, SIGNAL(returnPressed()), this, SLOT(facRecogPressed()));
    //QObject::connect(ui->facTxtTrain, SIGNAL(returnPressed()), this, SLOT(facTrainPressed()));
    //QObject::connect(ui->facTxtClear, SIGNAL(returnPressed()), this, SLOT(facClearPressed()));
    QObject::connect(ui->objTxtGoalObject, SIGNAL(returnPressed()), this, SLOT(objRecogObjectChanged()));
    QObject::connect(ui->vsnBtnFindLines, SIGNAL(clicked()), this, SLOT(vsnFindLinesClicked()));
    //HRI
    QObject::connect(ui->hriBtnStartFollow, SIGNAL(clicked()), this, SLOT(hriBtnFollowClicked()));
    QObject::connect(ui->hriBtnStartLegs, SIGNAL(clicked()), this, SLOT(hriBtnLegsClicked()));
    //Knowledge
    QObject::connect(ui->locTableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_removeLoc_clicked()));
    QObject::connect(ui->quesReq, SIGNAL(returnPressed()), this, SLOT(quesReqChanged()));
    //K_representation
    QObject::connect(ui->enterCommand, SIGNAL(returnPressed()), this, SLOT(enterCommandChanged()));
    QObject::connect(ui->loadCommand, SIGNAL(returnPressed()), this, SLOT(loadCommandChanged()));

    this->robotX = 0;
    this->robotY = 0;
    this->robotTheta = 0;
    this->trsCurrentPos = 0.0;
    this->laIgnoreValueChanged = false;
    this->raIgnoreValueChanged = false;
    this->initKnownLoacations = false                                                                   ;
    this->defInitKnownLoacations = true;
    this->updateKnownLoacations = false;

    QStringList titles;
    titles << "Name" << "X" << "Y" << "A";
    this->ui->locTableWidget->setColumnCount(4);
    this->ui->locTableWidget->setHorizontalHeaderLabels(titles);

    QStringList locClipsTitles;
    locClipsTitles << "Type" << "Name" << "Quantity" << "Room";
    this->ui->locCLIPStab->setColumnCount(4);
    this->ui->locCLIPStab->setHorizontalHeaderLabels(locClipsTitles);

     QStringList objClipsTitles;
     objClipsTitles << "NAME" << "CATEGORY" << "LOCATION" << "ROOM" << "WEIGHT" << "SIZE" << "COLOR" << "QUANTITY";
     this->ui->objCLIPStab->setColumnCount(8);
     this->ui->objCLIPStab->setHorizontalHeaderLabels(objClipsTitles);

     setlocClips();

    /*QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(this->ui->labelAnswerResp);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRosNode(QtRosNode* qtRosNode)
{
    this->qtRosNode = qtRosNode;

    //Connect signals from QtRosNode to MainWindow
    //For example, when ros finishes or when a rostopic is received
    QObject::connect(qtRosNode, SIGNAL(onRosNodeFinished()), this, SLOT(close()));
    QObject::connect(qtRosNode, SIGNAL(updateGraphics()), this, SLOT(updateGraphicsReceived()));
}

//
//SLOTS FOR SIGNALS EMITTED IN THE MAINWINDOW
//
void MainWindow::closeEvent(QCloseEvent *event)
{
    this->qtRosNode->gui_closed = true;
    this->qtRosNode->wait();
    //event->accept();
}

void MainWindow::setPathKnownLoc(const std::string pathKnownLoc){
  this->pathKnownLoc = pathKnownLoc;
}

bool MainWindow::strToFloatArray(std::string str, std::vector<float>& result)
{
    result.clear();
    std::vector<std::string> parts;
    boost::algorithm::to_lower(str);
    boost::split(parts, str, boost::is_any_of(" ,\t\r\n"), boost::token_compress_on);
    for(size_t i=0; i < parts.size(); i++)
    {
        std::stringstream ssValue(parts[i]);
        float value;
        if(!(ssValue >> value))
            return false;
        result.push_back(value);
    }
    return true;
}

void MainWindow::stopRobot()
{
    TakeshiHardware::stopRobot();
}

void MainWindow::navBtnCalcPath_pressed()
{
    float startX, startY, startTheta;
    float goalX = 0;
    float goalY = 0;
    float goalTheta;
    std::string start_location = "";
    std::string goal_location = "";
    std::vector<std::string> parts;

    std::string str = this->ui->navTxtStartPose->text().toStdString();
    boost::algorithm::to_lower(str);
    boost::split(parts, str, boost::is_any_of(" ,\t\r\n"), boost::token_compress_on);
    if(str.compare("") == 0 || str.compare("robot") == 0) //take robot pose as start position
    {
        this->ui->navTxtStartPose->setText("Robot");
        TakeshiNavigation::getRobotPose(this->robotX, this->robotY, this->robotTheta);
        startX = this->robotX;
        startY = this->robotY;
        startTheta = this->robotTheta;
    }
    else if(parts.size() >= 2) //Given data correspond to numbers
    {
        std::stringstream ssStartX(parts[0]);
        std::stringstream ssStartY(parts[1]);
        if(!(ssStartX >> startX) || !(ssStartY >> startY))
        {
            this->ui->navTxtStartPose->setText("Invalid format");
            return;
        }
    }
    else //Given data correspond to location
        start_location = parts[0];

    str = this->ui->navTxtGoalPose->text().toStdString();
    boost::algorithm::to_lower(str);
    boost::split(parts, str, boost::is_any_of(" ,\t\r\n"), boost::token_compress_on);
    if(parts.size() >= 2)
    {
        std::stringstream ssGoalX(parts[0]);
        std::stringstream ssGoalY(parts[1]);
        if(!(ssGoalX >> goalX) || !(ssGoalY >> goalY))
        {
            this->ui->navTxtStartPose->setText("Invalid format");
            return;
        }
    }
    else
        goal_location = parts[0];

    if(start_location.compare("") == 0 && goal_location.compare("") == 0)
        TakeshiNavigation::planPath(startX, startY, goalX, goalY, this->calculatedPath);
    else if(start_location.compare("") == 0 && goal_location.compare("") != 0)
        TakeshiNavigation::planPath(startX, startY, goal_location, this->calculatedPath);
    else if(start_location.compare("") != 0 && goal_location.compare("") == 0)
        TakeshiNavigation::planPath(start_location, goalX, goalY, this->calculatedPath);
    else
        TakeshiNavigation::planPath(start_location, goal_location, this->calculatedPath);
}

void MainWindow::navBtnExecPath_pressed()
{
    float goalX = 0;
    float goalY = 0;
    float goalTheta;
    std::string goal_location = "";
    std::vector<std::string> parts;

    std::string str = this->ui->navTxtGoalPose->text().toStdString();
    boost::algorithm::to_lower(str);
    boost::split(parts, str, boost::is_any_of(" ,\t\r\n"), boost::token_compress_on);
    if(parts.size() >= 2)
    {
        std::stringstream ssGoalX(parts[0]);
        std::stringstream ssGoalY(parts[1]);
        if(!(ssGoalX >> goalX) || !(ssGoalY >> goalY))
        {
            this->ui->navTxtStartPose->setText("Invalid format");
            return;
        }
        if(parts.size() > 2)
        {
            std::stringstream ssGoalAngle(parts[2]);
            if(!(ssGoalAngle >> goalTheta))
            {
                this->ui->navTxtStartPose->setText("Invalid format");
                return;
            }
            //this->ui->navLblStatus->setText("Base Status: Moving to goal point...");
            TakeshiNavigation::startGetClose(goalX, goalY, goalTheta);
        }

        else
        {
            // this->ui->navLblStatus->setText("Base Status: Moving to goal point...");
            TakeshiNavigation::startGetClose(goalX, goalY);
        }
        return;
    }
    else
    {
        goal_location = parts[0];
        //this->ui->navLblStatus->setText("Base Status: Moving to goal point...");
        TakeshiNavigation::startGetClose(goal_location);
    }
}

void MainWindow::navMoveChanged()
{
    std::vector<std::string> parts;
    std::string str = this->ui->navTxtMove->text().toStdString();
    boost::algorithm::to_lower(str);
    boost::split(parts, str, boost::is_any_of(" ,\t\r\n"), boost::token_compress_on);
    if(parts.size() < 1)
        return;

    if(parts[0].compare("l") == 0)
    {
        if(parts.size() < 2)
            return;
        std::stringstream ssLateral(parts[1]);
        float lateral;
        if(!(ssLateral >> lateral))
            return;
        TakeshiNavigation::startMoveLateral(lateral);
        return;
    }

    float dist = 0;
    float angle = 0;
    std::stringstream ssDist(parts[0]);
    if(!(ssDist >> dist))
        return;
    if(parts.size() > 1)
    {
        std::stringstream ssAngle(parts[1]);
        if(!(ssAngle >> angle))
            return;
    }
    TakeshiNavigation::startMoveDistAngle(dist, angle);
}

void MainWindow::navObsDetectionEnableClicked()
{
    if(this->navDetectingObstacles)
    {
        TakeshiNavigation::enableObstacleDetection(false);
        this->navDetectingObstacles = false;
        this->ui->navBtnStartObsDetection->setText("Enable");
    }
    else
    {
        TakeshiNavigation::enableObstacleDetection(true);
        this->navDetectingObstacles = true;
        this->ui->navBtnStartObsDetection->setText("Disable");
    }
}

void MainWindow::hdPanTiltChanged(double)
{
    float goalPan = this->ui->hdTxtPan->value();
    float goalTilt = this->ui->hdTxtTilt->value();
    std::cout << "QMainWindow.->Setting new head goal pose: " << goalPan << "  " << goalTilt  << std::endl;
    //TakeshiHardware::setHeadGoalPose(goalPan, goalTilt);
    TakeshiManip::startHdGoTo(goalPan, goalTilt);
}

void MainWindow::laAnglesChanged(double d)
{
    if(this->laIgnoreValueChanged)
        return;

    std::vector<float> goalAngles;
    goalAngles.push_back(this->ui->laTxtAngles0->value());
    goalAngles.push_back(this->ui->laTxtAngles1->value());
    goalAngles.push_back(this->ui->laTxtAngles2->value());
    goalAngles.push_back(this->ui->laTxtAngles3->value());
    //TakeshiManip::startLaGoToArticular(goalAngles);
}

void MainWindow::armAnglesChanged(double d)
{
    if(this->laIgnoreValueChanged)
        return;

    std::vector<float> goalAngles;
    goalAngles.push_back(this->ui->laTxtAngles0->value());
    goalAngles.push_back(this->ui->laTxtAngles1->value());
    goalAngles.push_back(this->ui->laTxtAngles2->value());
    goalAngles.push_back(this->ui->laTxtAngles3->value());
    TakeshiManip::startArmGoToArticular(goalAngles);
}


/*
void MainWindow::laValuesChanged()
{
    std::vector<float> xyz;
    std::vector<float> rpy;
    std::vector<float> elbow;
    std::vector<float> values;
    this->strToFloatArray(this->ui->laTxtXYZ->text().toStdString(), xyz);
    this->strToFloatArray(this->ui->laTxtRPY->text().toStdString(), rpy);
    this->strToFloatArray(this->ui->laTxtElbow->text().toStdString(), elbow);
    values.insert(values.end(), xyz.begin(), xyz.end());
    values.insert(values.end(), rpy.begin(), rpy.end());
    values.insert(values.end(), elbow.begin(), elbow.end());
    bool success = values.size() == 7 || values.size() == 6 || values.size() == 3;
    if(!success) //If cannot get floats, then it is assumed that a predefined position is given
    {
        std::string goalLoc = this->ui->laTxtXYZ->text().toStdString();
        if(goalLoc.compare("") != 0)
        {
            //TakeshiManip::startLaGoTo(goalLoc);
            //TakeshiManip::laGoTo(goalLoc, 5000);
        }
    }
    else
    {
        if(this->ui->laRbCartesianRobot->isChecked())
            //TakeshiManip::startLaGoToCartesianWrtRobot(values);
        else if(this->ui->laRbCartesian->isChecked())
            //TakeshiManip::startLaGoToCartesian(values);
        else if(this->ui->laRbArticular->isChecked())
            //TakeshiManip::startLaGoToArticular(values);
    }
}
*/

void MainWindow::laOpenGripperChanged(double d)
{
    TakeshiManip::openGripper((float)d);
}

void MainWindow::raOpenGripperChanged(double d)
{
    //TakeshiManip::startRaOpenGripper((float)d);
}

void MainWindow::laCloseGripperChanged(double d)
{
    TakeshiManip::closeGripper((float)d);
}

void MainWindow::raCloseGripperChanged(double d)
{
    //TakeshiManip::startRaCloseGripper((float)d);
}


/*
void MainWindow::laRadioButtonClicked()
{
    int currentRb = -1;
    if(this->ui->laRbArticular->isChecked()) currentRb = 0;
    else if(this->ui->laRbCartesian->isChecked()) currentRb = 1;
    else if(this->ui->laRbCartesianRobot->isChecked()) currentRb = 2;
    else return;

    if(currentRb == this->laLastRadioButton)
        return;

    this->laIgnoreValueChanged = true;

    std::vector<float> xyz;
    std::vector<float> rpy;
    std::vector<float> elbow;
    std::vector<float> oldValues;
    std::vector<float> newValues;
    this->strToFloatArray(this->ui->laTxtXYZ->text().toStdString(), xyz);
    this->strToFloatArray(this->ui->laTxtRPY->text().toStdString(), rpy);
    this->strToFloatArray(this->ui->laTxtElbow->text().toStdString(), elbow);
    oldValues.insert(oldValues.end(), xyz.begin(), xyz.end());
    oldValues.insert(oldValues.end(), rpy.begin(), rpy.end());
    oldValues.insert(oldValues.end(), elbow.begin(), elbow.end());
    bool success = oldValues.size() == 7;

    if(!success)
    {
        this->laIgnoreValueChanged = false;
        if(this->laLastRadioButton == 0) this->ui->laRbArticular->setChecked(true);
        if(this->laLastRadioButton == 1) this->ui->laRbCartesian->setChecked(true);
        if(this->laLastRadioButton == 2) this->ui->laRbCartesianRobot->setChecked(true);
        return;
    }

    if(this->ui->laRbArticular->isChecked())
    {
        this->ui->laLblGoalValues->setText("Angles:");
        if(this->laLastRadioButton == 2)
            TakeshiTools::transformPose("base_link", oldValues, "left_arm_link0", oldValues);
        success = TakeshiManip::inverseKinematics(oldValues, newValues);
    }
    else if(this->ui->laRbCartesian->isChecked())
    {
        this->ui->laLblGoalValues->setText("XYZ  RPY  Elbow:");
        if(this->laLastRadioButton == 0)
            success = TakeshiManip::directKinematics(newValues, oldValues);
        else
            success = TakeshiTools::transformPose("base_link", oldValues, "left_arm_link1", newValues);
    }
    else
    {
        this->ui->laLblGoalValues->setText("XYZ  RPY  Elbow:");
        if(this->laLastRadioButton == 0)
            success = TakeshiManip::directKinematics(oldValues, oldValues);

        success = TakeshiTools::transformPose("left_arm_link1", oldValues, "base_link", newValues);
    }
    if(!success)
    {
        this->laIgnoreValueChanged = false;
        if(this->laLastRadioButton == 0) this->ui->laRbArticular->setChecked(true);
        if(this->laLastRadioButton == 1) this->ui->laRbCartesian->setChecked(true);
        if(this->laLastRadioButton == 2) this->ui->laRbCartesianRobot->setChecked(true);
        return;
    }

    QString str = QString::number(newValues[0],'f',3)+"  "+QString::number(newValues[1],'f',3)+"  "+QString::number(newValues[2],'f',3);
    this->ui->laTxtXYZ->setText(str);
    str = QString::number(newValues[3],'f',3)+"  "+QString::number(newValues[4],'f',3)+"  "+QString::number(newValues[5],'f',3);
    this->ui->laTxtRPY->setText(str);
    str = QString::number(newValues[6],'f',3);
    this->ui->laTxtElbow->setText(str);

    this->laLastRadioButton = currentRb;
    this->laIgnoreValueChanged = false;
}
*/

void MainWindow::raRadioButtonClicked()
{
    int currentRb = -1;
    if(currentRb == this->raLastRadioButton)
        return;

    this->raIgnoreValueChanged = true;

    std::vector<float> xyz;
    std::vector<float> rpy;
    std::vector<float> elbow;
    std::vector<float> oldValues;
    std::vector<float> newValues;
    oldValues.insert(oldValues.end(), xyz.begin(), xyz.end());
    oldValues.insert(oldValues.end(), rpy.begin(), rpy.end());
    oldValues.insert(oldValues.end(), elbow.begin(), elbow.end());
    bool success = oldValues.size() == 7;

    if(!success)
    {
        this->raIgnoreValueChanged = false;
        return;
    }

    this->raLastRadioButton = currentRb;
    this->raIgnoreValueChanged = false;
}

void MainWindow::torsoPoseChanged(double d)
{
    float goalSpine = this->ui->trsTxtSpine->value();
    //std::cout << "QMainWindow.->Setting new torso pose: " << goalSpine << std::endl;
    TakeshiManip::startTorsoGoTo(goalSpine);
    this->ui->trsLblStatus->setText("Status: Moving to ...");
}

void MainWindow::torsoLocChanged()
{
}

void MainWindow::spgSayChanged()
{
    std::string strToSay = this->ui->spgTxtSay->text().toStdString();
    std::cout << "QMainWindow.->Saying: " << strToSay << std::endl;
    TakeshiHRI::say(strToSay);
}

void MainWindow::sprFakeRecognizedChanged()
{
    std::string strToFake = this->ui->sprTxtFakeRecog->text().toStdString();
    std::cout << "QMainWindow.->Faking recog speech: " << strToFake << std::endl;
    TakeshiHRI::fakeSpeechRecognized(strToFake);
}

/*
void MainWindow::recSaveVideoChanged()
{
    if(this->recSavingVideo)
    {
        std::cout << "QMainWindow.->Stop saving video." << std::endl;
        TakeshiHardware::stopSavingCloud();
        this->ui->recBtnSaveVideo->setText("Start saving video");
        this->ui->recLblStatus->setText("Status: Stand by");
        this->recSavingVideo = false;
    }
    else
    {
        std::string fileName = this->ui->recTxtVideoFile->text().toStdString();
        if(!boost::filesystem::portable_posix_name(fileName))
        {
            std::cout << "QMainWindow.->File name for video is not a valid name :'(" << std::endl;
            this->ui->recLblStatus->setText("Status: Invalid file name...");
            return;
        }
        std::cout << "QMainWindow.->Starting to save video at: " << fileName << std::endl;
        TakeshiHardware::startSavingCloud(fileName);
        this->ui->recBtnSaveVideo->setText("Stop saving video");
        this->ui->recLblStatus->setText("Status: saving video...");
        this->recSavingVideo = true;
    }
}
*/

void MainWindow::recSaveImageChanged()
{
}

void MainWindow::sktBtnStartClicked()
{
    if(this->sktRecognizing)
    {
        TakeshiVision::stopSkeletonFinding();
        this->sktRecognizing = false;
        this->ui->sktBtnStartRecog->setText("Start Skeletons");
    }
    else
    {
        TakeshiVision::startSkeletonFinding();
        this->sktRecognizing = true;
        this->ui->sktBtnStartRecog->setText("Stop Skeletons");
    }
}


/*
 * This lines should be changed by faceNet methods
 *
void MainWindow::facBtnStartClicked()
{
    if(this->facRecognizing)
    {
        TakeshiVision::stopFaceRecognition();
        this->facRecognizing = false;
        this->ui->facBtnStartRecog->setText("Start Recognizer");
    }
    else
    {
        TakeshiVision::startFaceRecognition();
        this->facRecognizing = true;
        this->ui->facBtnStartRecog->setText("Stop Recognizing");
    }
}
*/


/*
 * This lines should be changed by faceNet methods
 *
void MainWindow::facRecogPressed()
{
    std::string id = this->ui->facTxtRecog->text().toStdString();
    if(id.compare("") == 0)
    {
        //std::cout << "QMainWindow.->Starting recognition without id" << std::endl;
        TakeshiVision::facRecognize();
        return;
    }
    if(!boost::filesystem::portable_posix_name(id))
    {
        //std::cout << "QMainWindow.->Invalid ID for face recognition. " << std::endl;
        return;
    }
    TakeshiVision::facRecognize(id);
}

void MainWindow::facTrainPressed()
{
    std::string str = this->ui->facTxtTrain->text().toStdString();
    std::vector<std::string> parts;
    boost::algorithm::to_lower(str);
    boost::split(parts, str, boost::is_any_of(" ,\t\r\n"), boost::token_compress_on);
    if(parts.size() < 1)
        return;

    int numOfFrames = -1;
    if(!boost::filesystem::portable_posix_name(parts[0]))
    {
        std::cout << "QMainWindow.->Invalid ID for face training. " << std::endl;
        return;
    }
    if(parts.size() > 1)
    {
        std::stringstream ssValue(parts[1]);
        if(!(ssValue >> numOfFrames) || numOfFrames <= 0)
        {
            std::cout << "QMainWindow.->Invalid number of frames for face training. " << std::endl;
            return;
        }
    }

    if(numOfFrames <= 0)
    {
        std::cout << "QMainWindow.->Sending face training without number of frames. " << std::endl;
        TakeshiVision::facTrain(parts[0]);
        return;
    }
    std::cout << "QMainWindow.->Sending face training with " << numOfFrames << " number of frames. " << std::endl;
    TakeshiVision::facTrain(parts[0], numOfFrames);
    return;
}

void MainWindow::facClearPressed()
{
    std::string str = this->ui->facTxtClear->text().toStdString();
    if(str.compare("ALL") == 0)
    {
        std::cout << "QMainWindow.->Clearing all face recognition database" << std::endl;
        TakeshiVision::facClearAll();
        return;
    }
    if(!boost::filesystem::portable_posix_name(str))
    {
        std::cout << "QMainWindow.->Invalid ID for clearing face database. " << std::endl;
        return;
    }
    TakeshiVision::facClearByID(str);
}
*/


void MainWindow::objRecogObjectChanged()
{
    std::vector<vision_msgs::VisionObject> recoObjList;
    TakeshiRepresentation::initKDB("", true, 0);
    if(!TakeshiVision::detectObjects(recoObjList))
    {
        std::cout << "MainWindow.->Cannot dectect objects :'( " << std::endl;
        return;
    }
    QString txtResult = "";
    this->ui->objTxtResults->setPlainText(txtResult);
    for(int i=0; i < recoObjList.size(); i++)
    {
        txtResult = "Id: " + QString::fromStdString(recoObjList[i].id);
        this->ui->objTxtResults->appendPlainText(txtResult);
        txtResult = "Centroid:";
        this->ui->objTxtResults->appendPlainText(txtResult);
        txtResult = QString::number(recoObjList[i].pose.position.x, 'f', 3) + "  " + QString::number(recoObjList[i].pose.position.y, 'f', 3) +
            "  " + QString::number(recoObjList[i].pose.position.z, 'f', 3);
        this->ui->objTxtResults->appendPlainText(txtResult);
        txtResult = "";
        this->ui->objTxtResults->appendPlainText(txtResult);
    }
}

void MainWindow::vsnFindLinesClicked()
{
    float x1, y1, z1, x2, y2, z2;
    TakeshiVision::findLine(x1, y1, z1, x2, y2, z2);
}

//HRI
void MainWindow::hriBtnFollowClicked()
{
    if(this->hriFollowing)
    {
        this->ui->hriBtnStartFollow->setText("Start Follow");
        TakeshiHRI::stopFollowHuman();
        this->hriFollowing = false;
    }
    else
    {
        this->ui->hriBtnStartFollow->setText("Stop Follow");
        TakeshiHRI::startFollowHuman();
        this->hriFollowing = true;
    }
}

void MainWindow::hriBtnLegsClicked()
{
    if(this->hriFindingLegs)
    {
        TakeshiHRI::enableLegFinder(false);
        this->ui->hriBtnStartLegs->setText("Start Leg Finder");
        this->hriFindingLegs = false;
    }
    else
    {
        TakeshiHRI::enableLegFinder(true);
        this->ui->hriBtnStartLegs->setText("Stop Leg Finder");
        this->hriFindingLegs = true;
    }
}

//
//SLOTS FOR SIGNALS EMITTED IN THE QTROSNODE
//

void MainWindow::updateGraphicsReceived()
{
    float rX;
    float rY;
    float rT;
    float trCp;
    TakeshiNavigation::getRobotPose(rX, rY, rT);
    TakeshiManip::getTorsoCurrentPos(trCp);
    //std::cout << "MainWindow.->Current pose: " << currentX << "  " << currentY << "  " << currentTheta << std::endl;
    QString robotTxt = "Robot Pose: "+ QString::number(rX,'f',3) + "  " + QString::number(rY,'f',3) + "  " + QString::number(rT,'f',4);
    QString trsTxt = "Current pos: "+ QString::number(trCp,'f',3);
    this->ui->navLblRobotPose->setText(robotTxt);
    this->ui->trsLblSpine->setText(trsTxt);
    this->robotX = rX;
    this->robotY = rY;
    this->robotTheta = rT;

    float pan;
    float tilt;
    TakeshiHardware::getHeadCurrentPose(pan, tilt);
    QString headTxt = QString::number(pan, 'f', 4) + "  " + QString::number(tilt, 'f', 4);
    this->ui->hdLblHeadPose->setText(headTxt);
    this->headPan = pan;
    this->headTilt = tilt;

    if(TakeshiNavigation::isGoalReached())
        this->ui->navLblStatus->setText("Base Status: Goal Reached (Y)");
    else
        this->ui->navLblStatus->setText("Base Status: Moving to goal pose...");

    if(TakeshiManip::isHdGoalReached())
        this->ui->hdLblStatus->setText("Status: Goal Pose reached (Y)");
    else
        this->ui->hdLblStatus->setText("Status: Moving to goal pose...");

    if(TakeshiManip::isTorsoGoalReached())
        this->ui->trsLblStatus->setText("Status: Goal Reached!");

    std::string faceId = "";
    float facePosX = 0, facePosY = 0, facePosZ = 0;
    float faceConfidence = -1;
    int faceGender = -1;
    bool faceSmiling = false;
    /*
    if(TakeshiVision::getMostConfidentFace(faceId, facePosX, facePosY, facePosZ, faceConfidence, faceGender, faceSmiling))
    {
        QString faceIdQ = QString::fromStdString("ResultID: " + faceId);
        this->ui->facLblResultID->setText(faceIdQ);
        QString facePos = "Position: " +QString::number(facePosX,'f',2)+" "+QString::number(facePosY,'f',2)+" "+QString::number(facePosZ,'f',2);
        this->ui->facLblResultPose->setText(facePos);
        if(faceGender == 0)
            this->ui->facLblResultGender->setText("Gender: Female");
        else if(faceGender == 1)
            this->ui->facLblResultGender->setText("Gender: Male");
        else
            this->ui->facLblResultGender->setText("Gender: Unknown");
        if(faceSmiling)
            this->ui->facLblResultSmile->setText("Smiling: Yes");
        else
            this->ui->facLblResultSmile->setText("Smiling: No");
    }
    */

    if(TakeshiNavigation::obstacleInFront())
        this->ui->navLblObstacleInFront->setText("Obs In Front: True");
    else
        this->ui->navLblObstacleInFront->setText("Obs In Front: False");

    if(TakeshiNavigation::collisionRisk())
        this->ui->navLblRiskOfCollision->setText("Risk of Collision: True");
    else
        this->ui->navLblRiskOfCollision->setText("Risk of Collision: False");

    this->ui->sprLblLastRecog->setText(QString::fromStdString("Recog: " + TakeshiHRI::lastRecogSpeech()));

    TakeshiKnowledge::getInitKnownLoc(initKnownLoacations);
    if(defInitKnownLoacations || initKnownLoacations){
      std::cout << "QMainWindow.->Init know location" << std::endl;
      std::cout << "QMainWindow.->defInitKnownLoacations:" << defInitKnownLoacations << std::endl;
      std::cout << "QMainWindow.->initKnownLoacations:" << initKnownLoacations << std::endl;
      this->ui->locTableWidget->setRowCount(0);

      std::map<std::string, std::vector<float> > loc;
      TakeshiKnowledge::getKnownLocations(loc);

      for(std::map<std::string, std::vector<float> >::iterator it = loc.begin(); it != loc.end(); ++it){
        this->ui->locTableWidget->insertRow(this->ui->locTableWidget->rowCount());
        float row = this->ui->locTableWidget->rowCount() - 1;
        this->ui->locTableWidget->setItem(row, NAME, new QTableWidgetItem(QString::fromStdString(it->first)));
        this->ui->locTableWidget->setItem(row, X, new QTableWidgetItem(QString::number(it->second[0])));
        this->ui->locTableWidget->setItem(row, Y, new QTableWidgetItem(QString::number(it->second[1])));
        if(it->second.size() > 2)
          this->ui->locTableWidget->setItem(row, A, new QTableWidgetItem(QString::number(it->second[2])));
        else
          this->ui->locTableWidget->setItem(row, A, new QTableWidgetItem(""));
      }
      this->ui->locTableWidget->resizeRowsToContents();
      this->ui->locTableWidget->resizeColumnsToContents();
      this->ui->locTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
      this->ui->locTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
      this->ui->locTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
      defInitKnownLoacations = false;
      initKnownLoacations = false;
    }
    else{
      TakeshiKnowledge::getUpdateKnownLoc(updateKnownLoacations);
      //std::cout << "QMainWindow.->updateKnownLoacations:" << updateKnownLoacations << std::endl;
      if(updateKnownLoacations){
        std::map<std::string, std::vector<float> > loc;
        TakeshiKnowledge::getKnownLocations(loc);
        //std::cout << "QMainWindow.->loc size:" << loc.size() << std::endl;
        int row = 0;
        for(std::map<std::string, std::vector<float> >::iterator it = loc.begin(); it != loc.end(); ++it){
          this->ui->locTableWidget->item(row, X)->setText(QString::number(it->second[0]));
          this->ui->locTableWidget->item(row, Y)->setText(QString::number(it->second[1]));
          if(it->second.size() > 2)
            this->ui->locTableWidget->item(row, A)->setText(QString::number(it->second[2]));
          else
            this->ui->locTableWidget->item(row, A)->setText("");
          row++;
        }
        this->ui->locTableWidget->resizeRowsToContents();
        this->ui->locTableWidget->resizeColumnsToContents();
        updateKnownLoacations = false;
      }
    }

}

void MainWindow::on_enInteractiveEdit_clicked()
{
  if(!enableInteractiveEdit){
    TakeshiKnowledge::enableInteractiveUpdate(true);
    this->ui->enInteractiveEdit->setText("Disable Interactive");
    enableInteractiveEdit = true;
  }
  else{
    TakeshiKnowledge::enableInteractiveUpdate(false);
    this->ui->enInteractiveEdit->setText("Enable Interactive");
    enableInteractiveEdit = false;
  }
}

void MainWindow::on_removeLoc_clicked()
{
  std::cout << "QMainWindow.->on_removeLoc_clicked:" << std::endl;
  std::string name = this->ui->addNameLoc->text().toStdString();
  TakeshiKnowledge::deleteKnownLoc(name);
}

void MainWindow::on_locTableWidget_itemSelectionChanged()
{
  std::cout << "QMainWindow.->on_locTableWidget_itemSelectionChanged:" << std::endl;

  QModelIndexList indexes = this->ui->locTableWidget->selectionModel()->selectedRows();

  foreach(QModelIndex index, indexes){
    //std::cout << "QMainWindow.->updateKnownLoacations:" << updateKnownLoacations << std::endl;
    std::cout << "QMainWindow.->row selected:" << this->ui->locTableWidget->item(index.row(), NAME)->text().toStdString() << std::endl;
    this->ui->addNameLoc->setText(this->ui->locTableWidget->item(index.row(), NAME)->text());
    this->ui->addXLoc->setText(this->ui->locTableWidget->item(index.row(), X)->text());
    this->ui->addYLoc->setText(this->ui->locTableWidget->item(index.row(), Y)->text());
    this->ui->addALoc->setText(this->ui->locTableWidget->item(index.row(), A)->text());
  }
}

void MainWindow::on_addLoc_clicked()
{
    std::cout << "QMainWindow.->on_addLoc_clicked:" << std::endl;
    std::cout << "QMainWindow.->on_addLoc_clicked:" << this->ui->addALoc->text().toStdString() << std::endl;

    std::string name = this->ui->addNameLoc->text().toStdString();
    std::vector<float> values;
    values.push_back(this->ui->addXLoc->text().toFloat());
    values.push_back(this->ui->addYLoc->text().toFloat());
    if(this->ui->addALoc->text().compare("") != 0)
      values.push_back(this->ui->addALoc->text().toFloat());
    TakeshiKnowledge::addUpdateKnownLoc(name, values);
}

void MainWindow::on_GetRobotPose_clicked()
{
    float x, y, theta;
    TakeshiNavigation::getRobotPose(x, y, theta);
    this->ui->addXLoc->setText(QString::number(x));
    this->ui->addYLoc->setText(QString::number(y));
    this->ui->addALoc->setText(QString::number(theta));
}

void MainWindow::on_loadFromFile_clicked()
{
  QString pathFile = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        QString::fromStdString(this->pathKnownLoc),
        "Text File (*.txt)"
        );
  std::cout << "QMainWindow.->pathFile:" << pathFile.toStdString() << std::endl;
  TakeshiKnowledge::loadFromFile(pathFile.toStdString());
}

void MainWindow::on_SaveInFile_clicked()
{
  QString pathFile = QFileDialog::getSaveFileName(
        this,
        tr("Save File"),
        QString::fromStdString(this->pathKnownLoc),
        "Text File (*.txt)"
        );
  std::cout << "QMainWindow.->pathFile:" << pathFile.toStdString() << std::endl;
  TakeshiKnowledge::saveInFile(pathFile.toStdString());
}

void MainWindow::quesReqChanged(){
  std::cout << "QMainWindow.->quesReq:" << this->ui->quesReq->text().toStdString() << std::endl;
  std::string answer;
  bool found = TakeshiKnowledge::comparePredQuestion(
          this->ui->quesReq->text().toStdString(), answer);
  if(found)
    this->ui->browserAnswerResp->setText(QString::fromStdString(answer));
  else{
    std::string answer;
    std::string question = this->ui->quesReq->text().toStdString();
    TakeshiRepresentation::initKDB("", true, 0);
    bool success = TakeshiRepresentation::answerQuestionFromKDB(question, answer, 1000);
    if(success)
        this->ui->browserAnswerResp->setText(QString::fromStdString(answer));
    else
        this->ui->browserAnswerResp->setText(QString::fromStdString(""));
  }
  //sb->setValue(sb->maximum());
}

void MainWindow::on_runCLIPS_clicked()
{
    TakeshiRepresentation::runCLIPS(true);
}

void MainWindow::on_resetCLIPS_clicked()
{
    TakeshiRepresentation::resetCLIPS(true);
}

void MainWindow::on_factsCLIPS_clicked()
{
    TakeshiRepresentation::factCLIPS(true);
}

void MainWindow::on_rulesCLIPS_clicked()
{
    TakeshiRepresentation::ruleCLIPS(true);
}

void MainWindow::on_agendaCLIPS_clicked()
{
    TakeshiRepresentation::agendaCLIPS(true);
}

void MainWindow::enterCommandChanged(){
    std::cout << "QMainWindow.->enterCommand:" << this->ui->enterCommand->text().toStdString() << std::endl;
    TakeshiRepresentation::sendCLIPS(this->ui->enterCommand->text().toStdString());
}


void MainWindow::on_openFileCommand_clicked()
{
    std::string path;
    path = ros::package::getPath("knowledge_representation");
    std::cout << path << std::endl;
    QString pathFile = QFileDialog::getOpenFileName(
          this,
          tr("Open File"),
          QString::fromStdString(path),
          "Text File (*.dat)"
          );
    std::cout << "QMainWindow.->pathFile:" << pathFile.toStdString() << std::endl;
    this->ui->loadCommand->setText( pathFile);
}

void MainWindow::setPathKR()
{
    std::string path;
    path = ros::package::getPath("knowledge_representation");
    std::cout << path << std::endl;
    std::stringstream ss;
    ss << path << "/scripts/virbot_gpsr/speechTest.dat";
    this->ui->loadCommand->setText(QString::fromStdString(ss.str()));
}

void MainWindow::loadCommandChanged()
{
    std::cout << "QMainWindow.->loadCommand:" << this->ui->loadCommand->text().toStdString() << std::endl;
    TakeshiRepresentation::loadCLIPS(this->ui->loadCommand->text().toStdString());
}

void MainWindow::setlocClips()
{
    std::string path;
    path = ros::package::getPath("knowledge_representation");
    std::cout << path << std::endl;
    std::stringstream ss;
    ss << path << "/scripts/base_data/Locations.txt";

    this->ui->locCLIPStab->setRowCount(0);
    //obtain the information of the file Locations.txt
    //std::map<std::string, std::vector<std::string> > loc;
    TakeshiRepresentation::getLocations(ss.str(), locations);
    //objects = loc;
    int row = 0;
    std::map<std::string, std::vector<std::string> >::iterator it = locations.begin();
    for(std::map<std::string, std::vector<std::string> >::iterator it = locations.begin(); it != locations.end(); it++){
      this->ui->locCLIPStab->insertRow(this->ui->locCLIPStab->rowCount());
      this->ui->locCLIPStab->setItem(row, NAME, new QTableWidgetItem(QString::fromStdString(it->second[0])));
      this->ui->locCLIPStab->setItem(row, X, new QTableWidgetItem(QString::fromStdString(it->first)));
      this->ui->locCLIPStab->setItem(row, Y, new QTableWidgetItem(QString::fromStdString(it->second[1])));
      if(it->second.size() > 2)
        this->ui->locCLIPStab->setItem(row, A, new QTableWidgetItem(QString::fromStdString(it->second[2])));
      else
        this->ui->locCLIPStab->setItem(row, A, new QTableWidgetItem(""));
      row++;
    }
    this->ui->locCLIPStab->resizeRowsToContents();
    this->ui->locCLIPStab->resizeColumnsToContents();
    this->ui->locCLIPStab->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->locCLIPStab->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->locCLIPStab->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ss.str("");
    ss << path << "/scripts/base_data/Objects.txt";

    TakeshiRepresentation::getObjects(ss.str(), objects);
    objects = objects;

    row=0;
    std::map<std::string, std::vector<std::string> >::iterator it2 = objects.begin();
    for(std::map<std::string, std::vector<std::string> >::iterator it2 = objects.begin(); it2 != objects.end(); it2++){
      this->ui->objCLIPStab->insertRow(this->ui->objCLIPStab->rowCount());
      this->ui->objCLIPStab->setItem(row, NAME, new QTableWidgetItem(QString::fromStdString(it2->first)));
      this->ui->objCLIPStab->setItem(row, X, new QTableWidgetItem(QString::fromStdString(it2->second[0])));
      this->ui->objCLIPStab->setItem(row, Y, new QTableWidgetItem(QString::fromStdString(it2->second[1])));
      this->ui->objCLIPStab->setItem(row, A, new QTableWidgetItem(QString::fromStdString(it2->second[2])));
      this->ui->objCLIPStab->setItem(row, C1, new QTableWidgetItem(QString::fromStdString(it2->second[3])));
      this->ui->objCLIPStab->setItem(row, C2, new QTableWidgetItem(QString::fromStdString(it2->second[4])));
      this->ui->objCLIPStab->setItem(row, C3, new QTableWidgetItem(QString::fromStdString(it2->second[5])));
      this->ui->objCLIPStab->setItem(row, C4, new QTableWidgetItem(QString::fromStdString(it2->second[6])));
      row++;
    }
    this->ui->objCLIPStab->resizeRowsToContents();
    this->ui->objCLIPStab->resizeColumnsToContents();
    this->ui->objCLIPStab->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->objCLIPStab->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->objCLIPStab->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_addCLIPSloc_clicked()
{
    std::cout << "QMainWindow.->on_addCLIPSLoc_clicked:" << std::endl;
    //std::cout << "QMainWindow.->name:" << this->ui->nameCLIPSloc->text().toStdString() << std::endl;
    //std::cout << "QMainWindow.->type:" << this->ui->typeCLIPSloc->text().toStdString() << std::endl;
    //std::cout << "QMainWindow.->quantity:" << this->ui->quantCLIPSloc->text().toStdString() << std::endl;
    //std::cout << "QMainWindow.->room:" << this->ui->roomCLIPSloc->text().toStdString() << std::endl;

    //for(std::map<std::string, std::vector<std::string> >::iterator it = locations.begin(); it != locations.end(); it++){
    //    std::cout << "first:" << it->first << std::endl;
    //}
    std::string name = this->ui->nameCLIPSloc->text().toStdString();
    std::vector<std::string> values;
    values.push_back(this->ui->typeCLIPSloc->text().toStdString());
    values.push_back(this->ui->quantCLIPSloc->text().toStdString());
    values.push_back(this->ui->roomCLIPSloc->text().toStdString());

    TakeshiRepresentation::addLocations(locations,name,values);

    //for(std::map<std::string, std::vector<std::string> >::iterator it2 = locations.begin(); it2 != locations.end(); it2++){
    //    std::cout << "SECOND:" << it2->first << std::endl;
    //}

    this->ui->locCLIPStab->setRowCount(0);

    for(std::map<std::string, std::vector<std::string> >::iterator it = locations.begin(); it != locations.end(); ++it){
      this->ui->locCLIPStab->insertRow(this->ui->locCLIPStab->rowCount());
      float row = this->ui->locCLIPStab->rowCount() - 1;
      this->ui->locCLIPStab->setItem(row, NAME, new QTableWidgetItem(QString::fromStdString(it->second[0])));
      this->ui->locCLIPStab->setItem(row, X, new QTableWidgetItem(QString::fromStdString(it->first)));
      this->ui->locCLIPStab->setItem(row, Y, new QTableWidgetItem(QString::fromStdString(it->second[1])));
      this->ui->locCLIPStab->setItem(row, A, new QTableWidgetItem(QString::fromStdString(it->second[2])));
    }
    this->ui->locCLIPStab->resizeRowsToContents();
    this->ui->locCLIPStab->resizeColumnsToContents();
    this->ui->locCLIPStab->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->locCLIPStab->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->locCLIPStab->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_addCLIPSobj_clicked()
{
    std::cout << "QMainWindow.->on_addCLIPSLoc_clicked:" << std::endl;
    std::cout << "QMainWindow.->name:" << this->ui->nameCLIPSobj->text().toStdString() << std::endl;
    std::cout << "QMainWindow.->cat:" << this->ui->catCLIPSobj->text().toStdString() << std::endl;
    std::cout << "QMainWindow.->location:" << this->ui->locCLIPSobj->text().toStdString() << std::endl;
    std::cout << "QMainWindow.->room:" << this->ui->roomCLIPSobj->text().toStdString() << std::endl;
    std::cout << "QMainWindow.->weight:" << this->ui->weightCLIPSobj->text().toStdString() << std::endl;
    std::cout << "QMainWindow.->size:" << this->ui->sizeCLIPSobj->text().toStdString() << std::endl;
    std::cout << "QMainWindow.->color:" << this->ui->colorCLIPSobj->text().toStdString() << std::endl;
    std::cout << "QMainWindow.->quant:" << this->ui->quantCLIPSobj->text().toStdString() << std::endl;

    //for(std::map<std::string, std::vector<std::string> >::iterator it = objects.begin(); it != objects.end(); it++){
    //    std::cout << "first:" << it->first << std::endl;
    //}
    std::string name = this->ui->nameCLIPSobj->text().toStdString();
    std::vector<std::string> values;
    values.push_back(this->ui->catCLIPSobj->text().toStdString());
    values.push_back(this->ui->locCLIPSobj->text().toStdString());
    values.push_back(this->ui->roomCLIPSobj->text().toStdString());
    values.push_back(this->ui->weightCLIPSobj->text().toStdString());
    values.push_back(this->ui->sizeCLIPSobj->text().toStdString());
    values.push_back(this->ui->colorCLIPSobj->text().toStdString());
    values.push_back(this->ui->quantCLIPSobj->text().toStdString());

    TakeshiRepresentation::addObjects(objects,name,values);



    //for(std::map<std::string, std::vector<std::string> >::iterator it2 = objects.begin(); it2 != objects.end(); it2++){
    //    std::cout << "SECOND:" << it2->first << std::endl;
    //}

    this->ui->objCLIPStab->setRowCount(0);
    for(std::map<std::string, std::vector<std::string> >::iterator it2 = objects.begin(); it2 != objects.end(); it2++){
      this->ui->objCLIPStab->insertRow(this->ui->objCLIPStab->rowCount());
      float row = this->ui->objCLIPStab->rowCount() - 1;
      this->ui->objCLIPStab->setItem(row, NAME, new QTableWidgetItem(QString::fromStdString(it2->first)));
      this->ui->objCLIPStab->setItem(row, X, new QTableWidgetItem(QString::fromStdString(it2->second[0])));
      this->ui->objCLIPStab->setItem(row, Y, new QTableWidgetItem(QString::fromStdString(it2->second[1])));
      this->ui->objCLIPStab->setItem(row, A, new QTableWidgetItem(QString::fromStdString(it2->second[2])));
      this->ui->objCLIPStab->setItem(row, C1, new QTableWidgetItem(QString::fromStdString(it2->second[3])));
      this->ui->objCLIPStab->setItem(row, C2, new QTableWidgetItem(QString::fromStdString(it2->second[4])));
      this->ui->objCLIPStab->setItem(row, C3, new QTableWidgetItem(QString::fromStdString(it2->second[5])));
      this->ui->objCLIPStab->setItem(row, C4, new QTableWidgetItem(QString::fromStdString(it2->second[6])));
    }
    this->ui->objCLIPStab->resizeRowsToContents();
    this->ui->objCLIPStab->resizeColumnsToContents();
    this->ui->objCLIPStab->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->objCLIPStab->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->objCLIPStab->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_locCLIPStab_itemSelectionChanged()
{
    std::cout << "QMainWindow.->on_locTableWidget_itemSelectionChanged:" << std::endl;

    QModelIndexList indexes = this->ui->locCLIPStab->selectionModel()->selectedRows();

    foreach(QModelIndex index, indexes){
      //std::cout << "QMainWindow.->updateKnownLoacations:" << updateKnownLoacations << std::endl;
      std::cout << "QMainWindow.->row selected:" << this->ui->locCLIPStab->item(index.row(), NAME)->text().toStdString() << std::endl;
      this->ui->typeCLIPSloc->setText(this->ui->locCLIPStab->item(index.row(), NAME)->text());
      this->ui->nameCLIPSloc->setText(this->ui->locCLIPStab->item(index.row(), X)->text());
      this->ui->quantCLIPSloc->setText(this->ui->locCLIPStab->item(index.row(), Y)->text());
      this->ui->roomCLIPSloc->setText(this->ui->locCLIPStab->item(index.row(), A)->text());
    }
}

void MainWindow::on_objCLIPStab_itemSelectionChanged()
{
    std::cout << "QMainWindow.->on_locTableWidget_itemSelectionChanged:" << std::endl;

    QModelIndexList indexes = this->ui->objCLIPStab->selectionModel()->selectedRows();

    foreach(QModelIndex index, indexes){
      //std::cout << "QMainWindow.->updateKnownLoacations:" << updateKnownLoacations << std::endl;
      std::cout << "QMainWindow.->row selected:" << this->ui->objCLIPStab->item(index.row(), NAME)->text().toStdString() << std::endl;
      this->ui->nameCLIPSobj->setText(this->ui->objCLIPStab->item(index.row(), NAME)->text());
      this->ui->catCLIPSobj->setText(this->ui->objCLIPStab->item(index.row(), X)->text());
      this->ui->locCLIPSobj->setText(this->ui->objCLIPStab->item(index.row(), Y)->text());
      this->ui->roomCLIPSobj->setText(this->ui->objCLIPStab->item(index.row(), A)->text());
      this->ui->weightCLIPSobj->setText(this->ui->objCLIPStab->item(index.row(), C1)->text());
      this->ui->sizeCLIPSobj->setText(this->ui->objCLIPStab->item(index.row(), C2)->text());
      this->ui->colorCLIPSobj->setText(this->ui->objCLIPStab->item(index.row(), C3)->text());
      this->ui->quantCLIPSobj->setText(this->ui->objCLIPStab->item(index.row(), C4)->text());
    }
}


void MainWindow::on_trainObjButton_clicked()
{
    std::vector<vision_msgs::VisionObject> recoObjList;
    if(false) //!TakeshiVision::detectObjects(recoObjList))
    {
        std::cout << "MainWindow.->Cannot dectect objects :'( " << std::endl;
    }else if (false){ //(recoObjList.size() > 1){
        std::cout << "MainWindow.->Too many objects :'( " << std::endl;
    }else{
        std::cout << "MainWindow.->One object detected. Ready to Train" << std::endl;
        //This code should be implemented
        //std::string obj_name = this->ui->objTxtGoalObject_2->text().toStdString();
        //TakeshiVision::trainObjectByHeight(obj_name);
    }

}

