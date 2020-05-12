#!/bin/bash
PRINT_MESSAGE () {
	echo -e "${BLUE}$1${NC}"
}
PRINT_QUESTION_MESSAGE () {
	echo -e "${YELLOW}$1${NC}"	
}
PRINT_CORRECT_MESSAGE () {
	echo -e "${GREEN}$1${NC}"	
}
PRINT_ERROR_MESSAGE () {
	echo -e "${RED}$1${NC}"	
}


BLUE='\e[94m'
YELLOW='\e[93m'
GREEN='\e[32m'
RED='\e[31m'
NC='\e[0m'

INSTALL_DIR=$(pwd)
CUDAFILE="cuda_10.0_410_linux_run"
CUDAPATH="$(pwd)/${CUDAFILE}"
CUDAPATCHFILE="cuda_10.0_410_patch_linux_run"
CUDAPATCHPATH="$(pwd)/${CUDAPATCHFILE}"
CUDNNTAR="libcudnn7.tar.xz"
CUDNNTARPATH="$(pwd)/${CUDNNTAR}"
CUDNN="libcudnn7_7.6.5.32-1+cuda10.0.deb"
CUDNNDEV="libcudnn7-dev_7.6.5.32-1+cuda10.0.deb"
OPENCVFILE="opencv-4.1.0"
OPENCVZIPFILE=${OPENCVFILE}.zip
OPENCVPATH="$(pwd)/${OPENCVZIPFILE}"
OPENCVCONTRIBFILE=opencv_contrib-4.1.0
OPENCVCONTRIBZIPFILE="${OPENCVCONTRIBFILE}.zip"
OPENCVCONTRIBPATH="$(pwd)/${OPENCVCONTRIBZIPFILE}"
OPENPOSE="openpose"
OPENPOSEPATH="$(pwd)/${OPENPOSE}/"
CMAKE="cmake-3.17.0-rc1"
CMAKETAR="${CMAKE}.tar.gz"
CMAKEPATH="$(pwd)/${CMAKETAR}"
DLIB_FILE="v19.6"
DLIBZIP="${DLIB_FILE}.zip"
DLIB="dlib-19.6"
DLIB_PATH="$(pwd)/$DLIBZIP"
SPHINXBASE="sphinxbase"
SPHINXBASEPATH="$(pwd)/${SPHINXBASE}"
POCKETSPHINX="pocketsphinx"
POCKETSPHINXPATH="$(pwd)/${POCKETSPHINX}"
DARKNET="$(pwd)/darknet"
_finished=false
CASES="setup"



while [ $_finished == false ]

do 
	case $CASES in 
		setup)
			clear
			PRINT_MESSAGE "-----------------------------------------------------------------------------------"
			PRINT_MESSAGE "----->In this installer, all the HSR software requirements will be installed<------"
			PRINT_MESSAGE "-----------------------------------------------------------------------------------"
			PRINT_MESSAGE "Requeriments:"
			PRINT_MESSAGE "-Ubuntu 18"
			PRINT_MESSAGE "-Nvidia graphics card with its drivers"
			PRINT_MESSAGE "-Execute this scripts in a folder out of HSR_PUMAS folder ( ~/Documents/, ~/my_software/ )"
			PRINT_MESSAGE "-You need to execute this script without sudo privilegies"
			PRINT_MESSAGE "-A lot of free time to install this"
			PRINT_MESSAGE "-----------------------------------------------------------------------------------"
			PRINT_MESSAGE "-----------------------------------------------------------------------------------"
			PRINT_MESSAGE "-----------------------------------------------------------------------------------"

			PRINT_QUESTION_MESSAGE "Do you want to install ${CUDAFILE} and ${CUDNN}? (y/n)"
			PRINT_CORRECT_MESSAGE "You need the Nvidia Drivers"
			read _cuda
			PRINT_QUESTION_MESSAGE "Do you want to install ${OPENCVFILE}? (y/n)"
			PRINT_CORRECT_MESSAGE "You need the Nvidia Drivers"
			PRINT_CORRECT_MESSAGE "You need ${CUDAFILE} and ${CUDNN}"
			read _opencv
			PRINT_QUESTION_MESSAGE "Do you want to install OpenPose 1.5.0? (y/n)"
			PRINT_CORRECT_MESSAGE "You need the Nvidia Drivers"
			PRINT_CORRECT_MESSAGE "You need ${CUDAFILE} and ${CUDNN}"
			PRINT_CORRECT_MESSAGE "You need ${OPENCVFILE}"
			read _openpose
			PRINT_QUESTION_MESSAGE "Do you want to install ROS-Melodic and its dependencies? (y/n)"
			read _ros
			PRINT_QUESTION_MESSAGE "Do you want to install HSR tmc-packages? (y/n)"
			read _tmc
			PRINT_QUESTION_MESSAGE "Do you want to install pyRobotics and CLIPS"
			read _pyclips
			PRINT_QUESTION_MESSAGE "Do you want to install DarkNet (compatible with DarkNet-ROS)"
			PRINT_CORRECT_MESSAGE "You need the Nvidia Drivers"
			PRINT_CORRECT_MESSAGE "You need ${CUDAFILE} and ${CUDNN}"
			PRINT_CORRECT_MESSAGE "You need ${OPENCVFILE}"
			read _darknet
			PRINT_QUESTION_MESSAGE "Do you want to install Facenet"
			read _facenet
			PRINT_QUESTION_MESSAGE "Do you want to install PocketSphinx?"
			read _pocket
			PRINT_QUESTION_MESSAGE "Do you want to install the HSR Aliases? (y/n)"
			read _alias
			PRINT_QUESTION_MESSAGE "Do you want to compile the HSR_PUMAS repo? (y/n)"
			read _compile

			clear
			PRINT_MESSAGE "\n\n-----------------------------------------------------------------------------------"
			PRINT_MESSAGE "Resume:"
			if [ $_cuda == 'y' ] || [ $_cuda == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "${CUDAFILE} and ${CUDNN}...................yes"
			else 
			PRINT_ERROR_MESSAGE "${CUDAFILE} and ${CUDNN}....................no"
			fi
			if [ $_opencv == 'y' ] || [ $_opencv == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "${OPENCVFILE}....................................................................yes"
			else 
			PRINT_ERROR_MESSAGE "${OPENCVFILE}.....................................................................no"
			fi
			if [ $_openpose == 'y' ] || [ $_openpose == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "OpenPose 1.5.0..................................................................yes"
			else 
			PRINT_ERROR_MESSAGE "OpenPose 1.5.0...................................................................no"
			fi
			if [ $_ros == 'y' ] || [ $_ros == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "ROS-Melodic and its dependencies................................................yes"
			else 
			PRINT_ERROR_MESSAGE "ROS-Melodic and its dependencies.................................................no"
			fi
			if [ $_tmc == 'y' ] || [ $_tmc == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "HSR tmc-packages................................................................yes"
			else 
			PRINT_ERROR_MESSAGE "HSR tmc-packages?................................................................no"
			fi
			if [ $_pyclips == 'y' ] || [ $_pyclips == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "pyRobotics and CLIPS............................................................yes"
			else 
			PRINT_ERROR_MESSAGE "pyRobotics and CLIPS.............................................................no"
			fi
			if [ $_darknet == 'y' ] || [ $_darknet == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "DarkNet (compatible with DarkNet-ROS)...........................................yes"
			else 
			PRINT_ERROR_MESSAGE "DarkNet (compatible with DarkNet-ROS)............................................no"
			fi
			if [ $_facenet == 'y' ] || [ $_facenet == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "Facenet.........................................................................yes"
			else 
			PRINT_ERROR_MESSAGE "Facenet..........................................................................no"
			fi
			if [ $_pocket == 'y' ] || [ $_pocket == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "PocketSphinx....................................................................yes"
			else 
			PRINT_ERROR_MESSAGE "PocketSphinx.....................................................................no"
			fi
			if [ $_alias == 'y' ] || [ $_alias == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "HSR Aliases.....................................................................yes"
			else 
			PRINT_ERROR_MESSAGE "HSR Aliases......................................................................no"
			fi
			if [ $_compile == 'y' ] || [ $_compile == 'Y' ]; then
			PRINT_CORRECT_MESSAGE "HSR Repository compiled.........................................................yes"
			else 
			PRINT_ERROR_MESSAGE "HSR Resository compiled..........................................................no"
			fi
			PRINT_MESSAGE "-----------------------------------------------------------------------------------\n\n\n"
		
			PRINT_QUESTION_MESSAGE "Do you want continue? (y/n)"
			read _start_install
			
			if [ $_start_install == 'y' ] || [ $_start_install == 'Y' ]; then
				CASES="start"
			fi

			;;

		start)
			
			if [ $_cuda == 'y' ] || [ $_cuda == 'Y' ]; then
				sudo apt-get update
				cd $INSTALL_DIR	
				if [ ! -f "$CUDAPATH" ]; then
					PRINT_MESSAGE "Downloading ${CUDAFILE}"
					if wget "https://developer.nvidia.com/compute/cuda/10.0/Prod/local_installers/cuda_10.0.130_410.48_linux" -O $CUDAFILE; then
						PRINT_CORRECT_MESSAGE "Done!"
					else
						PRINT_ERROR_MESSAGE "There was an error downloading ${CUDAFILE}"
						rm $CUDAPATH
						exit 0		
					fi
				else
					PRINT_CORRECT_MESSAGE "Done!"	
				fi

				if [ ! -f "$CUDAPATCHPATH" ]; then
					PRINT_MESSAGE "Downloading ${CUDAPATCHFILE}"
					if wget "http://developer.download.nvidia.com/compute/cuda/10.0/Prod/patches/1/cuda_10.0.130.1_linux.run" -O $CUDAPATCHFILE; then
						PRINT_CORRECT_MESSAGE "Done!"
					else
						PRINT_ERROR_MESSAGE "There was an error downloading ${CUDAPATCHFILE}"
						rm $CUDAPATCHPATH
						exit 0		
					fi
				else
					PRINT_CORRECT_MESSAGE "Done!"	
				fi

				if [ ! -f "$CUDNNTARPATH" ]; then
					PRINT_MESSAGE "Downloading ${CUDNN}"
					if wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=1D9pCunHbYn0DP0BccNACrXTbWhrHSWKC' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=1D9pCunHbYn0DP0BccNACrXTbWhrHSWKC" -O $CUDNNTAR && rm -rf /tmp/cookies.txt; then
						PRINT_CORRECT_MESSAGE "Done!"
					else
						PRINT_ERROR_MESSAGE "There was an error downloading ${CUDNNTARPATH}"
						rm $CUDNNPATH
						exit 0			
					fi
				else
					PRINT_CORRECT_MESSAGE "Done!"	
				fi

				PRINT_MESSAGE "Installing ${CUDAFILE}..."
				chmod +x $CUDAFILE
				sudo ./$CUDAFILE --silent --toolkit
				PRINT_CORRECT_MESSAGE "Done!"

				PRINT_MESSAGE "Installing ${CUDAPATCHFILE}..."
				chmod +x $CUDAPATCHFILE
				sudo ./cuda_10.0_410_patch_linux_run --silent --accept-eula
				PRINT_CORRECT_MESSAGE "Done!"

				PRINT_MESSAGE "Installing ${CUDNN}..."
				tar -xf ${CUDNNTAR} 
				sudo dpkg -i ${CUDNN}
				sudo dpkg -i ${CUDNNDEV}
				rm	${CUDNN} ${CUDNNDEV}	 
				PRINT_CORRECT_MESSAGE "Done!"

				PRINT_MESSAGE "Set up hte environment..."
				echo "export LD_LIBRARY_PATH=/usr/local/cuda-10.0/lib64\${LD_LIBRARY_PATH:+:\${LD_LIBRARY_PATH}}" >> ~/.bashrc
				echo "export PATH=/usr/local/cuda/bin\${PATH:+:\${PATH}}" >> ~/.bashrc
				source ~/.bashrc 
				sudo ldconfig
				PRINT_CORRECT_MESSAGE "${CUDAFILE} has been installed"
			fi

			if [ $_opencv == 'y' ] || [ $_opencv == 'Y' ]; then
				sudo apt-get update
				cd $INSTALL_DIR	
				if [ ! -f "$OPENCVPATH" ]; then
					PRINT_MESSAGE "Downloading ${OPENCVZIPFILE}"
					if  wget -O opencv.zip https://github.com/opencv/opencv/archive/4.1.0.zip -O $OPENCVZIPFILE; then
						PRINT_CORRECT_MESSAGE "Done!"
					else
						PRINT_ERROR_MESSAGE "There was an error downloading ${OPENCVZIPFILE}"
						rm $OPENCVPATH
						exit 0		
					fi
				else
					PRINT_CORRECT_MESSAGE "Done!"	
				fi

				if [ ! -f "$OPENCVCONTRIBPATH" ]; then
					PRINT_MESSAGE "Downloading ${OPENCVCONTRIBZIPFILE}"
					if  wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.1.0.zip -O $OPENCVCONTRIBPATH; then
						PRINT_CORRECT_MESSAGE "Done!"
					else
						PRINT_ERROR_MESSAGE "There was an error downloading ${OPENCVCONTRIBZIPFILE}"
						rm $OPENCVCONTRIBPATH
						exit 0		
					fi
				else
					PRINT_CORRECT_MESSAGE "Done!"	
				fi

				PRINT_MESSAGE "Installing OpenCV dependencies..."
		 		#OS Libraries
				sudo apt-get -y install git gfortran
				sudo apt-get -y install build-essential checkinstall cmake pkg-config yasm
				sudo apt-get -y install libjpeg8-dev libpng-dev
				sudo apt-get -y install software-properties-common
				sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
				sudo apt-get -y update		 
				sudo apt-get -y install libjasper1
				sudo apt-get -y install libtiff-dev
				sudo apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev
				sudo apt-get -y install libxine2-dev libv4l-dev
				cd /usr/include/linux
				sudo ln -s -f ../libv4l1-videodev.h videodev.h
				cd "$cwd"
				sudo apt-get -y install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
				sudo apt-get -y install libgtk2.0-dev libtbb-dev qt5-default
				sudo apt-get -y install libatlas-base-dev
				sudo apt-get -y install libfaac-dev libmp3lame-dev libtheora-dev
				sudo apt-get -y install libvorbis-dev libxvidcore-dev
				sudo apt-get -y install libopencore-amrnb-dev libopencore-amrwb-dev
				sudo apt-get -y install libavresample-dev
				sudo apt-get -y install x264 v4l-utils
		 		# Optional dependencies
				sudo apt-get -y install libprotobuf-dev protobuf-compiler
				sudo apt-get -y install libgoogle-glog-dev libgflags-dev
				sudo apt-get -y install libgphoto2-dev libeigen3-dev libhdf5-dev doxygenibatlas-base-dev
				sudo easy_install pip
				#Python libraries
				sudo apt-get -y install python-dev python-pip python3-dev python3-pip python-numpy
				sudo -H pip3 install -U pip numpy
				sudo apt-get -y install python3-testresources

				PRINT_MESSAGE "Installing ${OPENCVFILE}"
				cd $INSTALL_DIR
				unzip -o $OPENCVZIPFILE 
				unzip -o $OPENCVCONTRIBZIPFILE 
				mkdir $OPENCVFILE/build
				cd $OPENCVFILE/build
				cmake -D CMAKE_BUILD_TYPE=RELEASE -D PYTHON2_EXECUTABLE=/usr/bin/python2.7 -D INSTALL_PYTHON_EXAMPLES=ON -D INSTALL_C_EXAMPLES=ON -D ENABLE_FAST_MATH=1 -D CUDA_FAST_MATH=1 -D WITH_TBB=ON -D BUILD_opencv_cudacodec=OFF -D CUDA_GENERATION=Auto -D WITH_CUBLAS=1 -D WITH_V4L=ON -D WITH_QT=OFF -D WITH_OPENGL=ON -D WITH_GSTREAMER=ON -D WITH_OPEPLES=ON -D WITH_VTK=ON -D WITH_OPENNI=ON -D WITH_OPENCL=OFF -D WITH_CUDA=ON -D WITH_CUDNN=ON -D OPENCV_DNN_CUDA=ON -D WITH_GDAL=ON -D WITH_XINE=ON -D BUILD_EXAMPLES=ON -D OPENCV_EXTRA_MODULES_PATH=../../${OPENCVCONTRIBFILE}/modules ..
				make -j$(nproc)
				sudo make install
				sudo touch /etc/ld.so.conf.d/opencv.conf
				sudo /bin/bash -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
				sudo ldconfig
				PRINT_CORRECT_MESSAGE "${OPENCVFILE} has been installed"
			fi

			if [ $_openpose == 'y' ] || [ $_openpose == 'Y' ]; then
				sudo apt-get update
				cd $INSTALL_DIR	
				if [ ! -d "$OPENPOSEPATH" ]; then
					PRINT_MESSAGE "Downloading OpenPose"
					if  git clone https://github.com/CMU-Perceptual-Computing-Lab/openpose; then
						cd $OPENPOSE
						git checkout v1.5.0
						#sed -i '1i #define CV_LOAD_IMAGE_GRAYSCALE cv::IMREAD_GRAYSCALE' openpose/examples/tests/resizeTest.cpp
						PRINT_CORRECT_MESSAGE "Done!"
					else
						PRINT_ERROR_MESSAGE "There was an error downloading OpenPose"
						rm $OPENPOSEPATH
						exit 0		
					fi
				else
					PRINT_CORRECT_MESSAGE "Done!"	
				fi

				PRINT_MESSAGE "Installing OpenPose dependencies..."
				cd $INSTALL_DIR
				#General dependencies
				sudo apt-get --assume-yes install libprotobuf-dev libleveldb-dev libsnappy-dev libhdf5-serial-dev protobuf-compiler
				sudo apt-get --assume-yes install --no-install-recommends libboost-all-dev
				sudo apt-get install libssl-dev
				#Python libs
				sudo -H pip2 install --upgrade numpy protobuf
				#Cmake 3.17
				if [ ! -f "$CMAKEPATH" ]; then
					wget https://github.com/Kitware/CMake/releases/download/v3.17.0-rc1/cmake-3.17.0-rc1.tar.gz
				fi

				tar -xzvf $CMAKETAR
				cd $CMAKE
				./bootstrap
		  		make -j$(nproc)
		  		sudo make install

				PRINT_MESSAGE "Installing OpenPose..."
				cd $INSTALL_DIR
				mkdir $OPENPOSE/build
				cd $OPENPOSE/build
				sudo make clean
				cmake ..
				make -j$(nproc)
				sudo make install
				export OPENPOSE_HOME=${INSTALL_DIR}/openpose
				echo "export OPENPOSE_HOME=${INSTALL_DIR}/openpose" >> ~/.bashrc
				source ~/.bashrc 
				PRINT_CORRECT_MESSAGE "OpenPose has been installed"
			fi	

			if [ $_ros == 'y' ] || [ $_ros == 'Y' ]; then
				sudo apt-get install --assume-yes --install-suggests jackd2 libjack-jackd2-dev pulseaudio-module-jack qjackctl
				cd $INSTALL_DIR
				sudo apt-get update
				PRINT_MESSAGE "Installing ROS-MELODIC..."
				sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
				sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
				sudo apt update
				sudo apt install --assume-yes ros-melodic-desktop-full
				sudo rosdep init
				rosdep update
				echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
				sudo apt install --assume-yes python-rosinstall python-rosinstall-generator python-wstool build-essential
				source /opt/ros/melodic/setup.bash 
				source ~/.bashrc
				PRINT_CORRECT_MESSAGE "Done!"

				PRINT_MESSAGE "Installing ROS dependencies..."

				sudo apt-get install --assume-yes ros-melodic-moveit
				sudo apt-get install --assume-yes ros-melodic-tf2-bullet
				sudo apt-get install --assume-yes ros-melodic-amcl
				sudo apt-get install --assume-yes python-pyaudio python3-pyaudio
				sudo apt-get install --assume-yes ros-melodic-urg-node
				sudo apt-get install --assume-yes ros-melodic-gmapping
				sudo apt-get install --assume-yes libzbar-dev
				PRINT_CORRECT_MESSAGE "ROS-Melodic has been installed"
			fi

			if [ $_tmc == 'y' ] || [ $_tmc == 'Y' ]; then	
				cd $INSTALL_DIR	
				PRINT_MESSAGE "Installing HSR tmc packages..."
				sudo apt-get update
				sudo sh -c 'echo "deb https://hsr-user:jD3k4G2e@packages.hsr.io/ros/ubuntu `lsb_release -cs` main" > /etc/apt/sources.list.d/tmc.list'
				sudo sh -c 'echo "deb https://hsr-user:jD3k4G2e@packages.hsr.io/tmc/ubuntu `lsb_release -cs` multiverse main" >> /etc/apt/sources.list.d/tmc.list'
				sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
				sudo sh -c 'echo "deb https://apache.bintray.com/couchdb-deb `lsb_release -cs` main" > /etc/apt/sources.list.d/couchdb.list'
				wget https://hsr-user:jD3k4G2e@packages.hsr.io/tmc.key -O - | sudo apt-key add -
				wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
				wget https://couchdb.apache.org/repo/bintray-pubkey.asc -O - | sudo apt-key add -
				sudo apt-get update
				sudo apt-get install --assume-yes --install-suggests ros-melodic-tmc-desktop-full
				PRINT_CORRECT_MESSAGE "HSR tmc_packages has been installed"

			fi

			if [ $_pyclips == 'y' ] || [ $_pyclips == 'Y' ]; then
				PRINT_MESSAGE "Installing pyRobotics and clips dependencies..."
				sudo apt-get update
				cd ~/HSR_PUMAS/ToInstall/pyRobotics-1.8.0
				sudo python setup.py config
				sudo python setup.py install
				cd ~/HSR_PUMAS/ToInstall/CLIPS/instPy
				sudo python setup.py config
				sudo python setup.py install
				cd ~/HSR_PUMAS/ToInstall/CLIPS/pyclips	
				sudo python setup.py config
				sudo python setup.py install
				sudo apt install python-clips
				pip2 install networkx==1.11
				PRINT_CORRECT_MESSAGE "pyRobotics and clips dependencies has been installed"
			fi

			if [ $_facenet == 'y' ] || [ $_facenet == 'Y' ]; then
				PRINT_MESSAGE "Installing Facenet..."
				sudo apt-get update
				cd $INSTALL_DIR	
				if [ ! -f "$DLIB_PATH" ]; then
					PRINT_MESSAGE "Downloading dlib library..."
					wget https://github.com/davisking/dlib/archive/v19.6.zip
					unzip $DLIBZIP
					PRINT_CORRECT_MESSAGE "Done!"
				fi
				PRINT_MESSAGE "Installing dlib library..."
				cd $DLIB
				mkdir build
				cd build
				cmake ..
				make -j$(nproc)
				sudo make install
				PRINT_CORRECT_MESSAGE "dlib library has been installed"

				PRINT_MESSAGE "Installing Facenet..."
				pip2 install face_recognition
				pip2 install pandas
				PRINT_CORRECT_MESSAGE "Facenet has been installed"
			fi
			
			if [ $_pocket == 'y' ] || [ $_pocket == 'Y' ]; then
				sudo apt-get update
				cd $INSTALL_DIR	
				if [ ! -d "$SPHINXBASEPATH" ]; then
						PRINT_MESSAGE "Downloading sphinxbase..."
						git clone https://github.com/cmusphinx/sphinxbase
						PRINT_CORRECT_MESSAGE "Done!"
				fi
				if [ ! -d "$POCKETSPHINXPATH" ]; then
						PRINT_MESSAGE "Downloading pocketsphinx..."
						git clone https://github.com/cmusphinx/pocketsphinx
						PRINT_CORRECT_MESSAGE "Done!"
				fi
				PRINT_MESSAGE "Installing pocketsphinx dependencies..."
				sudo apt-get update
				sudo apt-get --assume-yes install bison
				sudo apt-get --assume-yes install swig

				PRINT_MESSAGE "Installing sphinxbase..."
				cd $SPHINXBASE
				./autogen.sh
				./configure
				make
				sudo make install	

				PRINT_MESSAGE "Installing pocketsphinx..."
				cd $INSTALL_DIR	
				cd $POCKETSPHINX
				./autogen.sh
				./configure
				make clean all
				make check
				sudo make install

				python -m pip install --upgrade pip setuptools wheel
			    pip2 install --upgrade pocketsphinx

				PRINT_CORRECT_MESSAGE "PocketSphinx has been installed"

			fi

			if [ $_darknet == 'y' ] ||[ $_darknet == 'Y' ]; then
				sudo apt-get update
				cd $INSTALL_DIR	
				if [ ! -d "$DARKNET" ]; then
						PRINT_MESSAGE "Downloading darknet..."
						git clone https://github.com/pjreddie/darknet
						cd $DARKNET
						git checkout 508381b37f
						PRINT_CORRECT_MESSAGE "Done!"
				fi	
				cd $DARKNET
				git checkout 508381b37f
				export DARKNET_HOME=$DARKNET
				echo "export DARKNET_HOME=$DARKNET" >> ~/.bashrc
				source ~/.bashrc 
				PRINT_CORRECT_MESSAGE "DarkNet has been installed"
			fi

			if [ $_compile == 'y' ] || [ $_compile == 'Y' ]; then
				PRINT_MESSAGE "HSR_PUMAS will be compiled"
				sudo apt-get update
				cd ~/HSR_PUMAS/catkin_ws/
				source devel/setup.bash
				git checkout develop
				source ~/.bashrc
				sudo ldconfig
				source ~/.bash_profile
				catkin_make -j$(nproc) -l$(nproc) && cd -
				PRINT_CORRECT_MESSAGE "Done!"
			fi

			if [ $_alias == 'y' ] || [ $_alias == 'Y' ]; then
				sudo apt-get update
				echo "BLUE='\\e[94m'" >> ~/.bashrc
				echo "YELLOW='\\e[93m'" >> ~/.bashrc
				echo "GREEN='\\e[32m'" >> ~/.bashrc
				echo "RED='\\e[31m'" >> ~/.bashrc
				echo "NC='\\e[0m'" >> ~/.bashrc

				echo "alias hsrb_s='source /home/takeshi/HSR_PUMAS/catkin_ws/devel/setup.bash'" >> ~/.bashrc
				echo "alias hsrb_cmake='cd /home/takeshi/HSR_PUMAS/catkin_ws && catkin_make -j4 -l4 && cd -'" >> ~/.bashrc
				echo "alias hsrb_l='roslaunch takeshi_start takeshi.launch'" >> ~/.bashrc

				echo "alias hsrb_sim='export ROS_MASTER_URI=http://pumasDell:11311 export PS1=\"\$RED\u@\$GREEN\h\$YELLOW:[<pumasDell>]\$RED\\\$(__git_ps1)\$BLUE\\\\W\$GREEN->\$NC\"'" >> ~/.bashrc
				echo "alias hsrb_mode='export ROS_MASTER_URI=http://hsrb.local:11311 export PS1=\"\$RED\u@\$GREEN\h\$YELLOW:[<hsrb>]\$RED\$(__git_ps1)\$BLUE\\\\W\$GREEN->\$NC\"'" >> ~/.bashrc
				source ~/.bashrc 
				sudo ldconfig
				PRINT_CORRECT_MESSAGE "HSR Aliases has been installed"
			fi

			_finished=true

			;;
	esac
done











		
















