#!/usr/bin/env python

import face_recognition
import cv2
import os
import os.path
import glob
import re
import rospy
import rosgraph
import numpy as np
import rospkg
import shutil
import pandas as pd

from face_recognition.face_recognition_cli import image_files_in_folder
from std_msgs.msg import Header
from std_msgs.msg import String
from sensor_msgs.msg import Image
from sensor_msgs.msg import CompressedImage
from geometry_msgs.msg import Point
from cv_bridge import CvBridge, CvBridgeError
from vision_msgs.msg import *
from vision_msgs.srv import *
from std_msgs.msg import Empty


objpoints = np.array([
    (0.0, 0.0, 0.0),             # Nose tip
    (0.0, -80.0, -30),        # Chin
    (-40.0, 40.0, -30),     # Left eye left corner
                            (40.0, 40.0, -30),      # Right eye right corneq
                            (-30.0, -30.0, -30.0),    # Left Mouth corner
                            (30.0, -30.0, -30.0)      # Right mouth corner
])


def rect2sph(rectcoords):

    x=rectcoords[0]
    y=rectcoords[1]
    z=rectcoords[2]
    r= (x**2+y**2+z**2)**.5

    th=np.arctan(y/(x+.0000000001))
    phi= (np.arctan((x**2+y**2)**.5 )/ ( z+.000000001))
    sphrcoords=np.array([r,th,phi])
    return sphrcoords


def sph2rect(sphrcoords):
    r, th, phi = sphrcoords[0], sphrcoords[1], sphrcoords[2]
    x = r * np.sin(phi) * np.cos(th)
    y = r * np.sin(phi) * np.sin(th)
    z = r * np.cos(phi)

    rectcoords = np.array([x, y, z])
    return rectcoords


def sorted_nicely(strings):
    return sorted(strings, key=natural_sort_key)


def natural_sort_key(key):
    import re
    return [int(t) if t.isdigit() else t for t in re.split(r'(\d+)', key)]
def mask_closest(frame,face_locations):
    a= np.zeros((frame.shape[0],frame.shape[1],frame.shape[2]), np.uint8)
    (top, right, bottom, left) = face_locations[0]
    cv2.rectangle(a, (int(.8*left),int(.8* top)),
                      (int(1.1 * right),int(1.1* bottom)), (255, 255, 255), -1)
    cropped= frame[ int(.8* top):int(1.1* bottom),int(.8*left):int(1.1 * right) ]   
    aux = cv2.bitwise_and(frame,a)
    print "im in faceS",len(face_locations)
    return aux  


class face_reco_node(object):
    """Node for face recognition and detection using face_recognition python lib"""

    def __init__(self, train_dir, verbose=True, tolerance=0.5, debug=False):
        self.train_dir = train_dir
        self.verbose = verbose
        self.tolerance = tolerance
        self.debug = debug
        self.bridge = CvBridge()
        self.reco_server = rospy.Service(
            'facenet_recognizer/faces', FaceRecognition, self.face_recognition_callback)
        self.train_server = rospy.Service(
            'facenet_recognizer/train_face', FaceRecognition, self.train_faces_callback)
        self.clear_sub = rospy.Subscriber(
            "facenet_recognizer/clear_faces", Empty, self.clear_faces_callback)
        self.clear_face_sub = rospy.Subscriber(
            "facenet_recognizer/clear_face_id", String, self.clear_face_id_callback)

    def getImageFromMSG(self):
        """As name implies request current image from takeshi camera"""
        try:
            # Remap topic name in launch if needed
            img = rospy.wait_for_message(
                "/usb_cam/image_raw", Image, 2.0)
        except rospy.ROSException as e:
            print "Could not get current image: %s" % e
            img = None
        return img

    def load_Images(self):
        self.Faces = []
        self.names = []
        # self.face_bounding_boxes
        self.verbose

        # Loop through each person in the training set
        for class_dir in os.listdir(self.train_dir):
            if not os.path.isdir(os.path.join(self.train_dir, class_dir)):
                continue

            # Loop through each training image for the current person
            for img_path in image_files_in_folder(os.path.join(self.train_dir, class_dir)):
                image = face_recognition.load_image_file(img_path)
                face_bounding_boxes = face_recognition.face_locations(image)

                if len(face_bounding_boxes) > 1:
                    img_size = np.asarray(image.shape)[0:2]
                    det = []
                    for (top, right, bottom, left) in face_bounding_boxes:
                        det.append(np.array([left, bottom, right, top]))
                    det = np.array(det)
                    bounding_box_size = (
                        det[:, 2] - det[:, 0]) * (det[:, 3] - det[:, 1])
                    img_center = img_size / 2
                    offsets = np.vstack(
                        [(det[:, 0] + det[:, 2]) / 2 - img_center[1], (det[:, 1] + det[:, 3]) / 2 - img_center[0]])
                    offset_dist_squared = np.sum(np.power(offsets, 2.0), 0)
                    index = np.argmax(bounding_box_size -
                                      offset_dist_squared * 2.0)
                    Faces.append(face_recognition.face_encodings(
                        image, known_face_locations=face_bounding_boxes)[index])
                    names.append(class_dir)
                elif len(face_bounding_boxes) == 1:
                    # Add face encoding for current image to the training set
                    self.Faces.append(face_recognition.face_encodings(
                        image, known_face_locations=face_bounding_boxes)[0])
                    self.names.append(class_dir)
                else:
                    # If there are no people (or too many people) in a training image, skip the image.
                    if self.verbose:
                        print("Image {} not suitable for training: {}".format(img_path, "Didn't find a face" if len(
                            face_bounding_boxes) < 1 else "Found more than one face"))

    def showDetections(self, frame, name, locations):
        # Draw a box around the face
        for (top, right, bottom, left), name in zip(locations, name):
            cv2.rectangle(frame, (left, top),
                          (right, bottom), (0, 0, 255), 2)
            # Draw a label with a name below the face
            cv2.rectangle(frame, (left, bottom - 35),
                          (right, bottom), (0, 0, 255), cv2.FILLED)
            font = cv2. FONT_HERSHEY_DUPLEX
            cv2.putText(frame, name, (left + 6, bottom - 6),
                        font, 1.0, (255, 255, 255), 1)
        cv2.imshow('Face Recognition', frame)

    def train_faces_callback(self, req):
        print("FaceNetRecognizing ", req.id)

        h = std_msgs.msg.Header()
        h.stamp = rospy.Time.now()

        if req.imageBGR.data:
            try:
                frame = self.bridge.imgmsg_to_cv2(req.imageBGR, 'bgr8')
            except CvBridgeError as e:
                print("Could not process image in request:")
                print(e)
                return None
        else:
            msg = self.getImageFromMSG()
            try:
                frame = self.bridge.imgmsg_to_cv2(msg, 'bgr8')
            except CvBridgeError as e:
                print("Could not process image from topic:")
                return None

        self.train_new_face(frame, req.id)
        return FaceRecognitionResponse()

    def train_new_face(self, image, name):
        """Function that takes a photo, stores it in disk and extracts
         embeedings into the system, port finally tested!!!"""
        if not name:
            print("No name supplied")
            return
        print('Training person ' + name)

        #id = msg.data
        id = name
        path = self.train_dir + "/" + id
        try:
            if not os.path.exists(path):
                os.makedirs(path)
        except OSError:
            print ("Directory creation %s failed" % path)
        else:
            print ("Successfully created the directory %s " % path)
        reg_exp = path + "/" + id + "_[0-9]*.jpg"
        result = sorted_nicely(glob.glob(reg_exp))
        if (len(result) == 0):
            name_image = id + "_0.jpg"
        else:
            last_result = result[-1]
            number = re.search(path + "/" + id +
                               "_([0-9]*).jpg", last_result).group(1)
            name_image = id + "_%i.jpg" % +(int(number) + 1)
        print("Saving image in %s" % (path + "/" + name_image))

        cv2_image = image
        cv2.imwrite(os.path.join(path, name_image), cv2_image)
        new_image = face_recognition.load_image_file(path + "/" + name_image)
        face_bounding_boxes = face_recognition.face_locations(image)

        if len(face_bounding_boxes) > 1:
            img_size = np.asarray(image.shape)[0:2]
            det = []
            for (top, right, bottom, left) in face_bounding_boxes:
                det.append(np.array([left, bottom, right, top]))
            det = np.array(det)
            bounding_box_size = (det[:, 2] - det[:, 0]) * \
                (det[:, 3] - det[:, 1])
            img_center = img_size / 2
            offsets = np.vstack([(det[:, 0] + det[:, 2]) / 2 - img_center[1],
                                 (det[:, 1] + det[:, 3]) / 2 - img_center[0]])
            offset_dist_squared = np.sum(np.power(offsets, 2.0), 0)
            index = np.argmax(bounding_box_size - offset_dist_squared * 2.0)
            self.Faces.append(face_recognition.face_encodings(
                new_image, known_face_locations=face_bounding_boxes)[index])
            self.names.append(id)
        elif len(face_bounding_boxes) == 1:
            # Add face encoding for current image to the training set
            self.Faces.append(face_recognition.face_encodings(
                new_image, known_face_locations=face_bounding_boxes)[0])
            self.names.append(id)
        else:
            # If there are no people (or too many people) in a training image, skip the image.
            print("Image {} not suitable for training: {}".format(
                path + "/" + name_image,
                "Didn't find a face" if len(face_bounding_boxes) < 1 else
                "Found more than one face"))

    def face_recognition_callback(self, req):

        ###############################################################################################################################
        print("FaceNetRecognizing ", req.id)

        h = std_msgs.msg.Header()
        h.stamp = rospy.Time.now()

        if req.imageBGR.data:
            try:
                frame = self.bridge.imgmsg_to_cv2(req.imageBGR, 'bgr8')
            except CvBridgeError as e:
                print("Could not process image in request:")
                print(e)
                return None
        else:
            msg = self.getImageFromMSG()
            try:
                frame = self.bridge.imgmsg_to_cv2(msg, 'bgr8')
            except CvBridgeError as e:
                print("Could not process image from topic:")
                return None
        recog_faces = []
        face_locations = face_recognition.face_locations(frame)
        face_encodings = face_recognition.face_encodings(frame, face_locations)
        face_landmarks = face_recognition.face_landmarks(frame)
        labels = []
        distances = []
        Dstoface=[]
        Angs=[]
# FACEWRLDCOORDS######################################################3
        size = frame.shape
        focal_length = size[1]
        center = (size[1] / 2, size[0] / 2)
        camera_matrix = np.array(
            [[focal_length, 0, center[0]],
             [0, focal_length, center[1]],
             [0, 0, 1]], dtype="double"
        )
        dist_coeffs = np.zeros((4, 1))  # Assuming no lens distortion
        print "there are",len(face_landmarks)
        for face_landmark in face_landmarks:
            imgpoints = np.array([
                face_landmark['nose_tip'][2],
                face_landmark['chin'][8],
                face_landmark['left_eye'][0],
                face_landmark['right_eye'][3],
                face_landmark['top_lip'][0],
                face_landmark['top_lip'][6]
            ], dtype="double")
            _, rotation_vector, translation_vector = cv2.solvePnP(
                objpoints, imgpoints, camera_matrix, dist_coeffs)
            z = focal_length
            x, y = imgpoints[0]
            xx = (x - camera_matrix[0, 2])
            yy = -(y - camera_matrix[1, 2])
            Ang = np.arctan(xx / focal_length)
            Crect = np.array([xx, yy, z])
            _, th, phi = rect2sph(Crect)
          
            if np.linalg.norm(rotation_vector) < 5:
                Dtoface = 40 * focal_length / \
                    (np.abs(imgpoints[2][0] - imgpoints[3][0])*1000 / 2)
                Dstoface.append(Dtoface)
                print "##############################"
                print "Dss", Dtoface
                print "##############################"
            else:
                Dtoface = 40 * focal_length / \
                    (np.linalg.norm(imgpoints[2] - imgpoints[3])*1000 / 2)
                Dstoface.append(Dtoface)
                print "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
                print "Dss", Dtoface
                print "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
            Cpol = np.array([Dtoface, th, phi])
            Crect = sph2rect(Cpol)
            Ang = np.arctan(xx / focal_length)
            phi= np.arctan(yy/focal_length)
            Angs.append(Ang)

           
# IMGWLDCOORDS

        for face_encoding in face_encodings:
            matches = face_recognition.compare_faces(
                self.Faces, face_encoding, self.tolerance)
            name = "Unknown"
            face_distance = 0

            if True in matches:
                face_distances = face_recognition.face_distance(
                    self.Faces, face_encoding)
                first_match_index = np.argmin(face_distances)
                face_distance = face_distances[first_match_index]
                face_distance = 1 - round(face_distance, 2)
                name = self.names[first_match_index]

            else:
                face_distances = face_recognition.face_distance(
                    self.Faces, face_encoding)
                face_distance = np.argmin(face_distances)
                face_distance = 1 - round(face_distance, 2)
            labels.append(name)
            distances.append(face_distance)

        for (top, right, bottom, left), name, distance, Ang, Dtoface in zip(face_locations, labels, distances,Angs,Dstoface):
            # If do not care who is recognized
            # OR if  found person of interes
            if(req.id == '' or req.id == name.replace(" ", '') or "train_" in req.id):
                bounding_box = [Point(left, top, 0),
                                Point(right, bottom, 0)]
                face_centroid = Point(Dtoface* np.cos(Ang),Dtoface* np.sin(Ang), 1 + Dtoface*np.tan(phi))   ##SIST COORDS TAKESHI, 
                ##1 es  altura punto focal
                face_class = VisionFaceObject(
                    id=name, confidence=Ang,
                    face_centroid=face_centroid, bounding_box=bounding_box)
                recog_faces.append(face_class)
                serDs= pd.Series(Dstoface)
                serDs.sort_values(inplace=True)
                serrecog= pd.Series(recog_faces)
                serlocations= pd.Series(face_locations)
                serrecogsorted=serrecog.reindex(serDs.index)
                serlocationssorted= serlocations.reindex(serDs.index)
                recog_faces=serrecogsorted.tolist()
                #print(recog_faces)
            else:
                print("face found but incorrect id")

        # if self.debug:
        #     print("Showing detections")
        #     self.showDetections(
        #         frame, labels, face_locations)
        

        #if (req.id ==''):

        


        if("train_" in req.id):
           ###################################
            enable_training = True
            if len(face_locations) != 1:
                enable_training = False 
            if len(face_locations) > 1:
                frame = mask_closest (frame,face_locations)
                enable_training= True 

            print("ACTIVA ENTRENAMIENTO")
            if enable_training == False:
                print("Training did Not find suitable image")

            else:
                print('Training person' + req.id)
                idtrain = req.id
                id = idtrain.replace('train_', '')
                path = self.train_dir + "/" + id
                try:
                    if not os.path.exists(path):
                        os.makedirs(path)
                except OSError:
                    print ("Directory creation %s failed" % path)
                else:
                    print ("Successfully created the directory %s " % path)
                reg_exp = path + "/" + id + "_[0-9]*.jpg"
                result = sorted_nicely(glob.glob(reg_exp))
                if (len(result) == 0):
                    name_image = id + "_0.jpg"
                else:
                    last_result = result[-1]
                    number = re.search(path + "/" + id +
                                       "_([0-9]*).jpg", last_result).group(1)
                    name_image = id + "_%i.jpg" % +(int(number) + 1)
                print name_image

                cv2_image = frame
                face_bounding_boxes = face_recognition.face_locations(
                    cv2_image)
                if (len(result) <= 9):
                    cv2.imwrite(os.path.join(path, name_image), cv2_image)
                    self.Faces.append(face_recognition.face_encodings(
                        frame, known_face_locations=face_bounding_boxes)[0])
                    self.names.append(id)




        return FaceRecognitionResponse(VisionFaceObjects(h, recog_faces))




            ######################################################################################

    def clear_faces_callback(self, msg):
        """Caution this functions erases all faces stored in disk"""
        shutil.rmtree(self.train_dir, ignore_errors=True)
        Faces = []
        names = []

    def clear_face_id_callback(self, msg):
        face_clear_id = msg.data
        person_dir = self.train_dir + "/" + face_clear_id
        if os.path.exists(person_dir):
            shutil.rmtree(person_dir, ignore_errors=True)
            index = 0
            while index < len(names):
                if names[index] == face_clear_id:
                    names.pop(index)
                    Faces.pop(index)
                else:
                    index = index + 1

    def processFrames(self):
        print("Starting stream")

        while not rospy.is_shutdown() and rosgraph.is_master_online():
            #print("Waiting for image\n")
            try:
                img = rospy.wait_for_message(
                    "/usb_cam/image_raw", Image, timeout=1)
                image_color = self.bridge.imgmsg_to_cv2(img, 'bgr8')
            except rospy.ROSException as e:
                print("Could not get image!!!")
                break
            # Get faces and encode
            face_locations = face_recognition.face_locations(image_color)
            face_encodings = face_recognition.face_encodings(
                image_color, face_locations)

            labels = []

            for face_encoding in face_encodings:
                matches = face_recognition.compare_faces(
                    self.Faces, face_encoding, self.tolerance)
                name = "Unknown"

                if True in matches:
                    first_match_index = matches.index(True)
                    name = self.names[first_match_index]
                    face_distances = face_recognition.face_distance(
                        self.Faces, face_encoding)
                    face_distance = face_distances[first_match_index]
                    face_distance = 1 - round(face_distance, 2)  # Why?

                labels.append(name)

            self.showDetections(image_color, labels, face_locations)
            cv2.waitKey(1)


def main():
    rospy.init_node('face_recognition_lib_node')
    rate = rospy.Rate(30)
    #train_dir = rospack.get_path('face_recog') + "/faces"
    train_dir = rospy.get_param("~train_dir")
    tolerance = rospy.get_param("~tolerance", 0.5)
    dbg = rospy.get_param("~debug", False)
    # If stream is set to true will finid faces on every frame good for debugging!
    stream = rospy.get_param("~stream", False)

    try:
        if not os.path.exists(train_dir):
            os.makedirs(train_dir)
    except OSError:
        print ("Creation of the directory %s failed" % train_dir)
    else:
        print ("Successfully created the directory %s " % train_dir)

    recognizer = face_reco_node(
        train_dir, verbose=dbg, tolerance=tolerance, debug=dbg)
    recognizer.load_Images()

    if stream:
        recognizer.processFrames()
    else:
        print("Services available")
        while not rospy.core.is_shutdown():
            rate.sleep()


if __name__ == '__main__':
    main()
