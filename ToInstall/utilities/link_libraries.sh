#######################################################################
## IS NECESARY PREVIOUS INTALLATION TMC (TOYOTA MOTOR COMPANY LIBRARIES)
## EXECUTE    >>>>>  takeshiInstall.sh  <<<<<<<<
## Edited by Edd2 --->
## I dont remember whats the propouse of this script :'(


##      /opt/ros/kinetic/lib
cd /opt/ros/kinetic/lib
#MAKE SIMBOLIC LINKS FOR MOVEIT LIB#
for lib in `ls | grep 0.9.11`; do
  name=`echo $lib | cut -d '.' -f 1`
  sudo ln -s $lib $name.so.0.9.9
done

cd 
