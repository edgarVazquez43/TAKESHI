# Face recognition based on face_recognition

Ok this node provides a port from JUSTINA to use the face_recognition library
This is a dlib based implementation on facenet and has a lot of other
nice features like a face key point detector, like lips and noses and a nice
HOG based face face detection algorithm. As it is based on dlib it is easy and
fast to use. Althought most these features are not yet implemented as a
ROS service/message it is easy to expand.

The alternative, here as facenet-ros uses tensorflow and despite having a
 similar performance the pretrained model used here is soo old that tensorflow
 throws a lot of warning when loading it. And it is likely to stop working on
 melodic. So unless really need to  simply use face_recognition

## Instalation
For this you need to get dlib. The simplest way is:
```bash
  pip install --user dlib
```
However this takes a lot of time and does not actually install dlib in your machine. I recommend cloning the (https://github.com/davisking/dlib)[dlib] repo and compiling the python bindings from source, in my experience is actually faster and allows you to use cuda for faster runtimes!
```bash
  python setup.py install
```
If it says something about not being able to install just add sudo at the beginning.
Now it is just a matter of installing face_recognition:
```bash
  pip install --user face_recognition
```
A quick note ROS kinetic still supports only python 2.7 so make sure to
 install both dlib and face_recognition under your python2 install. However ROS Melodic will only support python3+ so change acoordingly.

 ## Dataset
 The train data can be a folder, inside that folder you need a folder for each person of interest and inside each person folder a bunch of photos names PERSON_1.jpg, PERSON_2.jpg etc. More than one picture per person is prefered.
