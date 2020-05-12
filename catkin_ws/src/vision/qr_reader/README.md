# QR_reader

PUMAS Team by Mauricio Matamoros have develop a ROS node that provides publishers and subscribers for QR decoder.

This node is on Pumas repository. The exact location is: `HSR_PUMAS/catkin_ws/src/vision/qr_reader`. So, you can copy the `qr_reader`  folder and paste on your `ROS workspace`.

 - subscriber:  `qr/start_qr`  type: `Bool`
 - publisher: `qr/recognized` type: `String`

*Note: please note that the complete name of the topics can be different if you are using a launch file for running the `qr node`. For instance, if you are using `takeshi.launch` the name for the start topic belong to vision namespace, so the complete topic name might be  `/vision/qr/start_qr`, and so on.

# Dependencies
Cpp library   `libzbar` is required. CMakeLists.txt already contains the dependencies required but `libzbar` is required.

You can install the package with the following command:

    $ sudo apt-get install libzbar-dev


## Use

There are some `cpp` functions that can help you with this code. This functions are coded in c++, and they are located into `catkin_ws/src/tools/takeshi_tools/src/TakeshiVision.cpp`.

The qr_reader node is waiting for a boolean message the name of the subscriber is `/vision/qr/start_qr` and is the type boolean. This is needed to be called at the beginning for start the qr_reader.

After that, the qr_reader node will return the string with the information contend into the QR code.




