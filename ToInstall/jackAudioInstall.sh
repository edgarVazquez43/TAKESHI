sudo apt-get install pulseaudio-module-jack
sudo apt-get install qjackctl
#ir al archivo  sudo gedit /etc/pulse/default.pa y agregarlas lineas sig:
#load-module module-jack-sink
#load-module module-jack-source
#in case pulse sink/surce wont apperar
#pacmd load-module module-jack-source channels=2; pacmd load-module module-jack-sink channels=2;
#after running jack
