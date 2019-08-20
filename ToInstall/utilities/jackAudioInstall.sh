######################################
## Support: Ed-1 #### 

sudo apt-get install pulseaudio-module-jack
sudo apt-get install qjackctl

#ir al archivo  sudo gedit /etc/pulse/default.pa y agregarlas lineas sig:
#load-module module-jack-sink
#load-module module-jack-source 


