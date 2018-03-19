############################
# SCRIPT INSTALL HSRB-PUMAS #

## ToDo: Execute this script lines from the path:
##      /opt/ros/kinetic/lib
#MAKE SIMBOLIC LINKS FOR MOVEIT LIB#
for lib in `ls | grep 0.9.11`; do
  name=`echo $lib | cut -d '.' -f 1`
  sudo ln -s $lib $name.so.0.9.9
done
