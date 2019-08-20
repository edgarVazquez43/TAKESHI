# Important details to  use Darknet

Compiling and using darknet-ros is somwhat a hassle as it needs to download and install  darknet separately and uses GPU.
So darknet-ros is not compiled by dafault pretty much like openposes. If you intend to use darknet_ros simply
provide the DARKNET_HOME enviroment variable
``` bash
  export DARKNET_HOME=~/darknet/
```
Change "~/darknet/" to the actual folder of darknet in your computer. And it should compile. Remember it should use the 508381b commit or it won't compile.
