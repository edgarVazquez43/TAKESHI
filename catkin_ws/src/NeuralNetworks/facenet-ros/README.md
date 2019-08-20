# facenet-ros
Modified Facenet for Takeshi-HSR by Coyo based on:
Face recognition for ROS using FaceNet and MTCNN Tensorflow implementation from https://github.com/davidsandberg/facenet.

## Important Notice:
There is a compatibility bug on facenet.py it is fixed on this particular version but if you try to pull from the original repo it won't load the model.
On top of that the models davidsandberg provided are a bit old and are likely to stop working on a future  Tensorflow release. I highly recommend  retraining the neural network as specified on the original repo and save the model using a modern tensorflow version.
