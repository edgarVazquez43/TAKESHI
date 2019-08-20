#!/bin/bash
##############################################################################
# ---- This script was edited by  EDD2 ---
# The original script belog to Justina's team

#toDo:  make a variable for each robot: (Justina, Takeshi)
#toDo:  Split code segments into other script what would be called out this script (Ex: OpenCV replace libs.)
#toDo:  Include HSR specific pachages (Ex: Gazebo, TMC, AudioTransmision, JackAudio)


# Color only for dislplay messages in bash terminal
FRM='\033['
BLACK='0;30'
RED='1;31'
GREEN='1;32'
YELLOW='1;33'
BLUE='1;34'
PURPLE='1;35'
CYAN='1;36'
WHITE='1;37'
BGBLACK=';40m'
BGRED=';41m'
BGGREEN=';42m'
BGYELLOW=';43m'
BGBLUE=';44m'
BGWHITE=';47m'
NC='\033[0m'

echo -e "${FRM}${GREEN}${BGRED} This script install Justinas packages required and this is usefull for robot Takeshi too${NC}"
echo -e "\t Please use:"
echo -e "\t --install"
echo -e "\t\t To install Justina software for first time"
echo -e "\t\t (${FRM}${RED}${BGBLACK}must be executed as sudo${NC})"
echo -e "\t "
echo -e "\t Or use:"
echo -e "\t --update"
echo -e "\t\t To update an already existent Justina installation,"
echo -e "\t\t this includes udev rules, folder creations and user groups"
echo -e "\t "
echo -n "Select option [--install/--update]:  "
read OPTION
echo -n "Select robot option [--takeshi/--justina]:  "
read ROBOT


if [ "$OPTION" = --install ] || [ "$OPTION" = --update ] ; then
    SOURCE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )"
    echo -e "${FRM}${WHITE}${BGBLUE}The source directory is $SOURCE_DIR ${NC}"
    if [ "$OPTION" == "-i" ] || [ "$OPTION" == "--install" ]; then
	if [ ! "$EUID" -ne 0 ]; then
	    echo -e "This script ${FRM}${RED}${BGBLACK}must be executed as normal user${NC}"
	    exit;
	fi
	INSTALL_DIR=""
	if [ $# -eq 2 ] ; then
	    INSTALL_DIR=$2
	    if [ ! -d "$INSTALL_DIR" ]; then
		echo -e "${FRM}${RED}${BGBLACK}Not exist installation directory${NC}"
		exit -1
	    else
		echo -e "${FRM}${WHITE}${BGBLUE}The installation directory is $INSTALL_DIR ${NC}"
	    fi
	else
	    INSTALL_DIR=$HOME
	    echo -e "${FRM}${WHITE}${BGBLUE}The installation directory is $INSTALL_DIR ${NC}"
	fi

	#############################
	###     SCRIPT START   ######
	#THE REAL STUFF

	sudo chown $USER.$USER /home/$USER/ -R

	###########    INSTALL  ROS KINETIC   #####################
	clear
	echo -n -e "${FRM}${RED}${BGBLACK}Do you want to install ROS kinetic Desktop-full packages? [y/n]:${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo "Installing Ros Packages and dependencies"
	    sudo ./rosKinetic_full_install.sh
	fi

	#########   TMC  packages for takeshi   ##################
	if [ "$ROBOT" = --takeshi ] || [ "$ROBOT" = -t ]; then
	    clear
	    echo -n -e "${FRM}${RED}${BGBLACK}Do you want to install TMC (Toyota Motor Company) & MoveIt packages? [y/n]: ${NC}"
	    read VAR
	    if [ "$VAR" = y ]; then
		echo "Installing TMC packages..."
		./utilities/tmc_packages_install.sh
	    fi
	fi
	
	###########    INSTALL  PACKAGE REQUIRED   #####################
	clear
	echo -e "${FRM}${RED}${BGBLACK}Do you want to install packages required?${NC}"
	echo -n -e "${FRM}${RED}${BGBLACK}Do you agree? [y/n]:${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo "Installing Ros Packages and dependencies"
	    sudo apt-get -y update
	    sudo apt-get install -y freeglut3-dev pkg-config build-essential libxmu-dev libxi-dev libusb-1.0-0-dev doxygen graphviz mono-complete
	    sudo apt-get install -y build-essential libgtk2.0-dev libjpeg-dev libtiff5-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev libeigen3-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common texlive-latex-extra libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev ant default-jdk libvtk6.2
	    echo -e "${FRM}${GREEN}${BGBLUE} Robot's dependencies has been installed ${NC}"
	fi

	###########    INSTALL  OPENCV DEPENDENCIES   #####################
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install OPENCV DEPENDENCIES?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE} Installing opencv dependencies ${NC}"
	    
	    #TODO Validate that as necesary, because this is for test kinect one installation
	    sudo apt-get install -y libturbojpeg libjpeg-turbo8-dev
	    sudo apt-get install -y libglfw3-dev
	    #TODO END

	    sudo apt-get install -y pkg-config unzip ffmpeg qtbase5-dev python-dev python3-dev python-numpy python3-numpy
	    sudo apt-get install -y libopencv-dev libgtk-3-dev libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libtiff5-dev libjasper-dev
	    sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libxine2-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
	    sudo apt-get install -y libv4l-dev libtbb-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev
	    #python-vtk is a package that uninstall some package of ros
	    #sudo apt-get install -y libvorbis-dev libxvidcore-dev v4l-utils python-vtk
	    sudo apt-get install -y libvorbis-dev libxvidcore-dev v4l-utils
	    sudo apt-get install -y liblapacke-dev libopenblas-dev checkinstall
	    sudo apt-get install -y libgdal-dev
	    sudo apt-get install -y libatlas-base-dev
	    #This libraries are only for test 
	    #sudo apt-get install -y libvtk6*
	    #sudo apt-get install -y libopenni-dev
	    sudo easy_install pip
	    echo -e "${FRM}${GREEN}${BGBLUE} Opencv dependencies have been installed${NC}"
	fi

	#################################################
	####         CUDA 8.0         ###################
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install CUDA 8.0?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE} Installing Cuda 8, Patch Cuda 8 and cuDNN 5.1${NC}"
	    cd $INSTALL_DIR
	    cudaFile="$(pwd)/cuda_8.0.61_375.26_linux-run"
	    cudaPatchFile="$(pwd)/cuda_8.0.61.2_linux-run"
	    if [ ! -f "$cudaFile" ]; then
		echo -e "${FRM}${WHITE}${BGBLUE} Downloading CUDA 8 ${NC}"
		wget https://developer.nvidia.com/compute/cuda/8.0/Prod2/local_installers/cuda_8.0.61_375.26_linux-run
		echo -e "${FRM}${GREEN}${BGBLUE} CUDA 8 has been downloaded ${NC}"
	    fi
	    
	    if [ ! -f "$cudaPatchFile" ]; then
		echo -e "${FRM}${WHITE}${BGBLUE} Downloading Patch CUDA 8 ${NC}"
		wget https://developer.nvidia.com/compute/cuda/8.0/Prod2/patches/2/cuda_8.0.61.2_linux-run
		echo -e "${FRM}${GREEN}${BGBLUE} Patch CUDA 8 has been downloaded ${NC}"
	    fi

	    chmod +x cuda_8.0.61_375.26_linux-run
	    chmod +x cuda_8.0.61.2_linux-run 
	    echo -e "${FRM}${WHITE}${BGBLUE} Installing CUDA 8${NC}"
	    sudo ./cuda_8.0.61_375.26_linux-run --silent --toolkit --samples --samplespath=$INSTALL_DIR
	    #sudo ./cuda_8.0.61_375.26_linux-run
	    echo -e "${FRM}${GREEN}${BGBLUE} CUDA 8 has been installed ${NC}"
	    echo -e "${FRM}${WHITE}${BGBLUE} Installing Patch CUDA 8${NC}"
	    sudo ./cuda_8.0.61.2_linux-run --silent --accept-eula --installdir=/usr/local/cuda-8.0
	    #sudo ./cuda_8.0.61.2_linux-run
	    echo -e "${FRM}${GREEN}${BGBLUE} Patch CUDA 8 has been installed ${NC}"
	    echo -e "${FRM}${WHITE}${BGBLUE} Installing cuDNN 5.1 for CUDA 8 ${NC}"
	    cd $INSTALL_DIR
	    ubuntu_version="$(lsb_release -r)"
	    CUDNN_URL="http://developer.download.nvidia.com/compute/redist/cudnn/v5.1/cudnn-8.0-linux-x64-v5.1.tgz"
	    wget -c ${CUDNN_URL}
	    mkdir cudnn_5_1
	    tar -xvf cudnn-8.0-linux-x64-v5.1.tgz -C cudnn_5_1
	    sudo cp cudnn_5_1/cuda/include/* /usr/local/cuda-8.0/include
	    sudo cp -av cudnn_5_1/cuda/lib64/* /usr/local/cuda-8.0/lib64
	    echo -e "${FRM}${GREEN}${BGBLUE} cuDNN has been installed ${NC}"
	    echo -e "${FRM}${GREEN}${BGBLUE} Cuda 8, Patch Cuda 8 and cuDNN 5.1 has been installed${NC}"
	fi
	
	#################################################
	########### OPENCV 3.3  #########################
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install OPENCV3.3?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    cd $INSTALL_DIR
	    opencvFile="$(pwd)/opencv-3.3.1.zip"
	    opencv_contrib_file="$(pwd)/opencv_contrib-3.3.1.zip"
	    if [ ! -f "$opencvFile" ]; then
		echo -e "${FRM}${WHITE}${BGBLUE} Downloading OpenCV 3.3.1 ${NC}"
		wget https://sourceforge.net/projects/opencvlibrary/files/opencv-unix/3.3.1/opencv-3.3.1.zip
		echo -e "${FRM}${GREEN}${BGBLUE} OpenCV 3.3.1 has been downloaded ${NC}"
		unzip opencv-3.3.1.zip
	    fi
	    if [ ! -f "$opencv_contrib_file" ]; then
		echo -e "${FRM}${WHITE}${BGBLUE} Downloading OpenCV 3.3.1 contrib ${NC}"
		wget https://github.com/opencv/opencv_contrib/archive/3.3.1.zip
		echo -e "${FRM}${GREEN}${BGBLUE} OpenCV 3.3.1 contrib  has been downloaded ${NC}"
		mv 3.3.1.zip opencv_contrib-3.3.1.zip
		unzip opencv_contrib-3.3.1.zip
	    fi
	    echo -e "${FRM}${WHITE}${BGBLUE} Installing OpenCV 3.3.1 ${NC}"
	    cd opencv-3.3.1
	    mkdir build
	    cd build
	    cmake -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPEPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON -D WITH_VTK=ON -D WITH_OPENNI=ON -D WITH_OPENCL=OFF -D CMAKE_BUILD_TYPE=RELEASE FORCE_VTK=ON -D WITH_CUBLAS=ON -D CUDA_NVCC_FLAGS="-D_FORCE_INLINES" -D WITH_GDAL=ON -D WITH_XINE=ON -D BUILD_EXAMPLES=ON -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-3.3.1/modules ..
	    make -j4
	    sudo make install
	    sudo touch /etc/ld.so.conf.d/opencv.conf
	    sudo /bin/su -c "echo '/usr/local/lib' >> /etc/ld.so.conf.d/opencv.conf"
	    sudo ldconfig
	    echo -e "${FRM}${GREEN}${BGBLUE} OpenCV 3.3.1 has been installed ${NC}"
	fi


	#################################################################
	######     OPENPOSE    Installing  ##############################
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install OPENPOSE?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE} Preparing to build OpenPose ${NC}"
	    #General dependencies
	    sudo apt-get --assume-yes install libprotobuf-dev libleveldb-dev libsnappy-dev libhdf5-serial-dev protobuf-compiler
	    sudo apt-get --assume-yes install --no-install-recommends libboost-all-dev
	    #Remaining dependencies, 14.04
	    sudo apt-get --assume-yes install libgflags-dev libgoogle-glog-dev liblmdb-dev
	    #Python libs
	    sudo -H pip install --upgrade numpy protobuf
	    cd $INSTALL_DIR
	    sudo touch /etc/ld.so.conf.d/nvidia.conf
	    sudo /bin/su -c "echo '/usr/local/cuda/lib64' >> /etc/ld.so.conf.d/nvidia.conf"
	    sudo /bin/su -c "echo '/usr/local/cuda/lib' >> /etc/ld.so.conf.d/nvidia.conf"
	    sudo ldconfig
	    git clone https://github.com/CMU-Perceptual-Computing-Lab/openpose
	    cd openpose
	    git checkout v1.4.0
	    mkdir build
	    cd build
	    sudo make clean
	    cmake ..
	    make -j4
	    sudo make install
	    echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/usr/local/cuda/lib64" >> /home/$USER/.bashrc
	    echo "export ROS_PACKAGE_PATH=\$ROS_PACKAGE_PATH:$SOURCE_DIR/catkin_ws/src:/opt/ros/kinetic/share" >> /home/$USER/.bashrc
	    echo "export OPENPOSE_HOME=$INSTALL_DIR/openpose" >> /home/$USER/.bashrc
	    source /home/$USER/.bashrc
	    echo -e "${FRM}${GREEN}${BGBLUE} OpenPose has been installed ${NC}"
	fi
	
	########################################################
	######    INSTALL   DLIB  ##############################
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install DLIB?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    cd $INSTALL_DIR
	    dlib_file="v19.6.zip"
	    dlib_file_desc="dlib-19.6"
	    dlib_file_path="$INSTALL_DIR/$dlib_file"
	    if [ ! -f "$dlib_file_path" ]; then
		echo -e "${FRM}${WHITE}${BGBLUE} Downloading dlib library ${NC}"
		wget https://github.com/davisking/dlib/archive/v19.6.zip
		unzip $dlib_file
		echo -e "${FRM}${GREEN}${BGBLUE} dlib library has been downloading ${NC}"
	    fi
	    echo -e "${FRM}${WHITE}${BGBLUE} Installing dlib library ${NC}"
	    cd $dlib_file_desc
	    mkdir build
	    cd build
	    cmake ..
	    make -j4
	    sudo make install
	    echo -e "${FRM}${GREEN}${BGBLUE} dlib library has been installing ${NC}"
	fi

	
	##########################################################
	######    INSTALL  PRIME-SENSE AND KINECT   ##############
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install PRIME-SENSE & KINECT Drivers?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	
	    echo -e "${FRM}${WHITE}${BGBLUE} Preparing to build Prime sense drivers ${NC}"
	    cd $INSTALL_DIR
	    mkdir -p prime_sense
	    cd prime_sense
	    sensorKinect_file="$(pwd)/SensorKinect"
	    if [ ! -d "$sensorKinect_file" ]; then
		git clone https://github.com/ph4m/SensorKinect.git
	    fi
	    cd SensorKinect
	    git checkout unstable
	    echo -e "${FRM}${GREEN}${BGBLUE} Prime sense drivers has been prepared ${NC}"
	    cd ../SensorKinect/Platform/Linux/CreateRedist
	    echo -e "${FRM}${WHITE}${BGBLUE} Installing Prime sense drivers ${NC}"
	    ./RedistMaker
	    cd ../Redist/Sensor-Bin-Linux-x64-v5.1.2.1/
	    sudo ./install.sh
	    echo -e "${FRM}${GREEN}${BGBLUE}Prime sense drivers has been installed${NC}"
	    echo -e "${FRM}${WHITE}${BGBLUE}Installing NITE for skeleton traking${NC}"
	    cd $INSTALL_DIR
	    nite_file="$(pwd)/NITE-Bin-Linux-x64-v1.5.2.23.tar.zip"
	    if [ ! -f "$nite_file" ]; then
		wget http://www.openni.ru/wp-content/uploads/2013/10/NITE-Bin-Linux-x64-v1.5.2.23.tar.zip
		unzip NITE-Bin-Linux-x64-v1.5.2.23.tar.zip
		tar -xvf NITE-Bin-Linux-x64-v1.5.2.23.tar.bz2
	    fi
	    cd NITE-Bin-Dev-Linux-x64-v1.5.2.23
	    sudo ./install.sh
	    echo -e "${FRM}${GREEN}${BGBLUE}NITE correctly installed ${NC}"
	    echo -e "${FRM}${WHITE}${BGBLUE}Installing OpenNI to update default libraries${NC}"
	    cd $INSTALL_DIR
	    openni_file_dir="$(pwd)/OpenNI"
	    if [ ! -f "$openni_file_dir" ]; then
		git clone https://github.com/OpenNI/OpenNI
	    fi
	    cd OpenNI/
	    git checkout unstable
	    cd Platform/Linux/CreateRedist
	    ./RedistMaker	
	    cd ../Redist/OpenNI-Bin-Dev-Linux-x64-v1.5.8.5/
	    sudo ./install.sh
	    echo -e "${FRM}${GREEN}${BGBLUE}OpenNI has been installed to update default libraries${NC}"
	fi



	#########################################################################
	######    INSTALL  ROS-PACKAGES  FOR NAV, RGB-D SENSORS    ##############
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install ROS-packages?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE}Installing ros package's dependencies${NC}"
	    sudo apt-get -y install ros-kinetic-urg-node
	    sudo apt-get -y install ros-kinetic-joy
	    sudo apt-get -y install ros-kinetic-openni-camera
	    sudo apt-get -y install ros-kinetic-openni-launch
	    sudo apt-get -y install ros-kinetic-openni2-camera
	    sudo apt-get -y install ros-kinetic-openni2-launch
	    sudo apt-get -y install ros-kinetic-amcl
	    sudo apt-get -y install ros-kinetic-tf2-bullet
	    sudo apt-get -y install ros-kinetic-fake-localization
	    sudo apt-get -y install ros-kinetic-map-server
	    sudo apt-get -y install ros-kinetic-sound-play
	    sudo apt-get -y install ros-kinetic-gmapping
	    #sudo apt-get -y install ros-kinetic-dynamixel-sdk
	    echo -e "${FRM}${GREEN}${BGBLUE}Ros package's dependencies has been installed${NC}"
	fi

	
	##########################################################
	######    INSTALL  pyRobotics and CLIPS     ##############
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install pyRobotics & CLIPS?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE}Installing pyRobotics and clips dependencies${NC}"
	    cd $SOURCE_DIR/ToInstall/pyRobotics-1.8.0
	    sudo python setup.py config
	    sudo python setup.py install
	    cd $SOURCE_DIR/ToInstall/CLIPS/instPy
	    sudo python setup.py config
	    sudo python setup.py install
	    cd $SOURCE_DIR/ToInstall/CLIPS/pyclips	
	    sudo python setup.py config
	    sudo python setup.py install
	    echo -e "${FRM}${GREEN}${BGBLUE}pyRobotics and clips dependencies has been installed${NC}"
	fi

	
	#####################################################
	######      INSTALL   LIBFEENECT2      ##############
	#TODO Validate that as necesary, because this is for test the kinect one installation
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install LIBFREENECT2?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    cd $INSTALL_DIR
	    git clone https://github.com/OpenKinect/libfreenect2.git
	    cd libfreenect2
	    mkdir build
	    sudo rm build/*
	    cd build
	    cmake ..
	    make -j4
	    sudo make install
	    sudo cp ../platform/linux/udev/90-kinect2.rules /etc/udev/rules.d/
	    #TODO END
	fi


	##################################################################
	######    INSTALL  DYNAMIXEL SERVOMOTORS PACKAGE    ##############
	#NOTE: Its not needed in Takeshi Robot
	clear
	if [ "$ROBOT" -ne --takeshi ] || [ "$ROBOT" -ne -t ]; then
	    echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install DYNAMIXEL lib?[y/n]:  ${NC}"
	    read CONFIRM
	    if [ "$CONFIRM" = y ]; then
		echo -e "${FRM}${WHITE}${BGBLUE} Preparing to build the Dynamixel SDK${NC}"
		cd $INSTALL_DIR
		git clone https://github.com/ROBOTIS-GIT/DynamixelSDK
		cd DynamixelSDK
		git checkout 3.5.4
		echo -e "${FRM}${GREEN}${BGBLUE} Dynamixel SDK have been prepared ${NC}"
		echo -e "${FRM}${WHITE}${BGBLUE} Installing the Dynamixel SDK${NC}"
		cd c++/build
		cmake ..
		make -j4
		sudo make install
		echo -e "${FRM}${GREEN}${BGBLUE} Dynamixel SDK have been installed ${NC}"
	    fi
	fi

	    
	########################################################
	######    SERIAL COMUNICATION PACKAGES    ##############
	#NOTE: Its not needed in Takeshi Robot
        clear
	if [ "$ROBOT" -ne --takeshi ] || [ "$ROBOT" -ne -t ]; then
	    echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install SERIAL COMUNICATION PACKAGES?[y/n]:  ${NC}"
	    read CONFIRM
	    if [ "$CONFIRM" = y ]; then
		echo -e "${FRM}${WHITE}${BGBLUE} Preparing the serial library, that use jrk controller${NC}"
		cd $INSTALL_DIR
		git clone https://github.com/wjwwood/serial
		cd serial
		mkdir build
		cd build
		echo -e "${FRM}${GREEN}${BGBLUE} The serial lib have been prepared ${NC}"
		echo -e "${FRM}${WHITE}${BGBLUE} Installing the serial library, that use jrk controller${NC}"
		cmake ..
		make -j4
		sudo make install
		echo -e "${FRM}${GREEN}${BGBLUE} The serial lib have been installed ${NC}"
	    fi
	fi
	
	################################################
	######    JACK AUDIO LIBRARIES    ##############
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to install JACK audio?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE}Installing basic audio libraries${NC}"
	    sudo apt-get -y install libzbar-dev
	    echo -e "${FRM}${WHITE}${BGBLUE}Audio support will be installed, choose <yes> when asked for real time permissions${NC}"
	    read -p "(Waiting for key press in order to continue)"
	    sudo apt-get -y install jackd2 libjack-jackd2-dev pulseaudio-module-jack qjackctl
	    echo -e "${FRM}${WHITE}${BGBLUE}Installing kinect audio driver${NC}"
	    sudo apt-get -y install kinect-audio-setup
	    echo -e "${FRM}${WHITE}${BGBLUE}Installing pyaudio lib for directional audio node${NC}"
	    sudo apt-get -y install libasound-dev portaudio19-dev libportaudio2 libportaudiocpp0
	    sudo apt-get -y install ffmpeg libav-tools
	    sudo pip install pyaudio==0.2.9 --upgrade
	    echo -e "${FRM}${GREEN}${BGBLUE}Audio libraries has been installed${NC}"
	fi


	#############################################################################
	######    REPLACE KINECT LIBRARIES FOR USE OF KINECT SENSOR    ##############
	# Replace the original opencv libs for own compiled OpenCV libs
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to REPLACE OPENCV-KINECT(compiled) ---> OPENCV-ROS ?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE}Coping OpenCV libraries to ros directory${NC}"
	    FILES="/usr/local/lib/libopencv*"
	    pathCopy="/opt/ros/kinetic/lib/"
	    pattherDelete=$pathCopy"libopencv*"
	    for f in $pattherDelete
	    do
		sudo rm $f
	    done

	    for f in $FILES
	    do
		filename=$(basename "$f")
		extension="${filename##*.}"
		if [ $extension = "so" ]; then
		    sudo cp $f $pathCopy
		    newfilename="${filename%.*}"3.$extension
		    sudo mv $pathCopy$filename $pathCopy$newfilename
		    sudo echo $newfilename
		    cd $pathCopy
		    sudo ln -s $newfilename.3.3 $newfilename.3.3.1
		    sudo ln -s $newfilename $newfilename.3.3
		fi
		#echo $f
		#mv $f $f
	    done
	    echo -e "${FRM}${GREEN}${BGBLUE}Have been copying the OpenCV libraries to ROS directory${NC}"
	fi

	
	################################
	#This is for permissions of USBs
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to give permissions to USB?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    if [ ! -d "/media/$USER/usbPDF/" ]; then
		sudo mkdir /media/$USER/USBPDF/
		mkdir /home/$USER/objs/
		#Add user to dialout, in order to use Arduino and Texas instrument board----
		sudo adduser $USER dialout
	    fi
	    echo "source /opt/ros/kinetic/setup.bash" >> /home/$USER/.bashrc
	    echo "source $SOURCE_DIR/catkin_ws/devel/setup.bash" >> /home/$USER/.bashrc
	    source /home/$USER/.bashrc
	    source $SOURCE_DIR/catkin_ws/devel/setup.bash
	    echo -e "${FRM}${WHITE}${BGBLUE}Copying the rules of Justina to system${NC}"
	    cd $SOURCE_DIR
	    sudo cp ToInstall/USB/80-justinaRobot.rules /etc/udev/rules.d/
	    sudo udevadm control --reload-rules && sudo service udev restart && sudo udevadm trigger
	    serialsPort=($(ls /dev/ttyACM*))
	    for f in "${serialsPort[@]}"
	    do
		sudo echo $f
		cmd="sudo udevadm test \$(udevadm info \-q path \-n $f)"
		sudo echo $cmd
		eval "$cmd"
	    done
	fi


	###############################################################
	####   Modify  .bashrc (change promt, include some alias)    ##
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to add alias to BASH, git color and Justina?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE}Sourcing to get git branche and alias launchers${NC}"
	    echo "green=\"\[\033[01;32m\]\"" >> /home/$USER/.bashrc
	    echo "blue=\"\[\033[01;34m\]\"" >> /home/$USER/.bashrc
	    echo "purple=\"\[\033[01;35m\]\"" >> /home/$USER/.bashrc
	    echo "red=\"\[\033[01;31m\]\"" >> /home/$USER/.bashrc
	    echo "yellow=\"\[\033[01;33m\]\"" >> /home/$USER/.bashrc
	    echo "reset=\"\[\033[0m\]\"" >> /home/$USER/.bashrc
	    echo "export GIT_PS1_SHOWDIRTYSTATE=1" >> /home/$USER/.bashrc
	    echo "export PS1=\"\$red\u@\$green\h\$yellow:\$red\\\$(__git_ps1)\$blue\\\\W\$green->\$reset \"" >> /home/$USER/.bashrc
	    echo "alias em='emacs -nw'" >> /home/$USER/.bashrc
	    echo "alias jsea='roslaunch surge_et_ambula justina.launch'" >> /home/$USER/.bashrc
	    echo "alias jseas='roslaunch surge_et_ambula justina_simul.launch'" >> /home/$USER/.bashrc
	    echo -e "${FRM}${RED}${BGWHITE}You can now ${NC}${FRM}${BLACK}${BGWHITE}behold${NC}${FRM}${RED}${BGWHITE} the power of Justina software${NC}"
	fi

	###  END INSTALL

    elif [ "$1" == "-u" ] || [ "$1" == "--update" ]; then
	##########################################
	# This option is for only UPDATE USBs
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to give permissions to USB?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    if [ ! -d "/media/$USER/usbPDF/" ]; then
		sudo mkdir /media/$USER/USBPDF/
		mkdir /home/$USER/objs/
		#Add user to dialout, in order to use Arduino and Texas instrument board----
		sudo adduser $USER dialout
	    fi
	    cd $SOURCE_DIR
	    sudo cp ToInstall/USB/80-justinaRobot.rules /etc/udev/rules.d/
	    sudo udevadm control --reload-rules && sudo service udev restart && sudo udevadm trigger
	    serialsPort=($(ls /dev/ttyACM*))
	    for f in "${serialsPort[@]}"
	    do
		sudo echo $f
		cmd="sudo udevadm test \$(udevadm info \-q path \-n $f)"
		sudo echo $cmd
		eval "$cmd"
		
	    done
	fi

	###############################################################
	####   Modify  .bashrc (change promt, include some alias)    ##
	clear
	echo -e -n "${FRM}${RED}${BGBLACK}Do you want to add alias to BASH, git color and Justina?[y/n]:  ${NC}"
	read CONFIRM
	if [ "$CONFIRM" = y ]; then
	    echo -e "${FRM}${WHITE}${BGBLUE}Sourcing to get git branche and alias launchers${NC}"
	    echo "green=\"\[\033[01;32m\]\"" >> /home/$USER/.bashrc
	    echo "blue=\"\[\033[01;34m\]\"" >> /home/$USER/.bashrc
	    echo "purple=\"\[\033[01;35m\]\"" >> /home/$USER/.bashrc
	    echo "red=\"\[\033[01;31m\]\"" >> /home/$USER/.bashrc
	    echo "yellow=\"\[\033[01;33m\]\"" >> /home/$USER/.bashrc
	    echo "reset=\"\[\033[0m\]\"" >> /home/$USER/.bashrc
	    echo "export GIT_PS1_SHOWDIRTYSTATE=1" >> /home/$USER/.bashrc
	    echo "export PS1=\"\$red\u@\$green\h\$yellow:\$red\\\$(__git_ps1)\$blue\\\\W\$green->\$reset \"" >> /home/$USER/.bashrc
	    echo "alias em='emacs -nw'" >> /home/$USER/.bashrc
	    echo "alias jsea='roslaunch surge_et_ambula justina.launch'" >> /home/$USER/.bashrc
	    echo "alias jseas='roslaunch surge_et_ambula justina_simul.launch'" >> /home/$USER/.bashrc
	    echo -e "${FRM}${WHITE}${BGBLUE}Copying the rules of Justina to system${NC}"
	    echo -e "${FRM}${RED}${BGWHITE}You can now ${NC}${FRM}${BLACK}${BGWHITE}behold${NC}${FRM}${RED}${BGWHITE} the power of Justina software${NC}"
	fi

	### END UPDATE ####
    else
	echo -e "${FRM}${CYAN}${BGRED} Invalid option supplied, use one of the following...${NC}"
	echo -e "\t-i, --install"
	echo -e "\t\t To install Justina software for first time"
	echo -e "\t\t (${FRM}${RED}${BGBLACK}must be executed as sudo${NC})"
	echo -e "\t-u, --update"
	echo -e "\t\t To update an already existent Justina installation,"
	echo -e "\t\t this includes udev rules, folder creations and user groups"
    fi
else
    echo -e "${FRM}${GREEN}${BGRED} No option supplied, use one of the following...${NC}"
    echo -e "\t-i, --install"
    echo -e "\t\t To install Justina software for first time"
    echo -e "\t\t (${FRM}${RED}${BGBLACK}must be executed as sudo${NC})"
    echo -e "\t-u, --update"
    echo -e "\t\t To update an already existent Justina installation,"
    echo -e "\t\t this includes udev rules, folder creations and user group"
fi
