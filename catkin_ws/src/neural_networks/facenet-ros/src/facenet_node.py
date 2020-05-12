#!/usr/bin/env python
import rospy
import facenet
import align.detect_face
import tensorflow as tf
import cv2
import numpy as np
import os

from vision_msgs.srv import GetFacesFromImage
from vision_msgs.srv import GetFacesFromImageResponse
from vision_msgs.srv import FaceRecognition
from vision_msgs.srv import FaceRecognitionResponse

from sensor_msgs.msg import CompressedImage
from vision_msgs.msg import VisionFaceObjects
from vision_msgs.msg import VisionFaceObject
from geometry_msgs.msg import Point
from sklearn.svm import LinearSVC

NODE_NAME = "facenet"


class FaceNetNode(object):

    def __init__(self, model, database, min_thr=1.5, pub=True, image_size=160, batch_size=16):
        self.model = model
        self.database = database
        self.min_thr = min_thr
        self.publish_img = pub
        self.image_size = image_size
        self.batch_size = batch_size
        self.graph = tf.Graph()

    def __del__(self):
        # Destroy the  TF session
        self.sess.close()

    def __getImageFromMSG(self):
        """As name implies request current image from takeshi camera"""
        try:
            # Remap topic name in launch if needed
            img = rospy.wait_for_message(
                "/image_raw/compressed", CompressedImage, 2.0)
        except rospy.ROSException as e:
            print "Could not get current image: %s" % e
            img = None
        return img

    def setupNode(self):
        self.minsize = 20  # minimum size of face
        # self.threshold = [0.7, 0.8, 0.8]  # three steps's threshold
        self.threshold = [0.6, 0.7, 0.7]  # three steps's threshold
        self.factor = 0.709  # scale factor
        # Sets config for tensorflow
        with self.graph.as_default():
            gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=0.5)
            self.sess = tf.Session(config=tf.ConfigProto(
                gpu_options=gpu_options, log_device_placement=False))
            # Load MTCNN for face aliggment and extraction
            with self.sess.as_default():
                self.pnet, self.rnet, self.onet = align.detect_face.create_mtcnn(
                    self.sess, None)
                facenet.load_model(self.model)

                self.images_placeholder = tf.get_default_graph().get_tensor_by_name("input:0")
                self.embeddings = tf.get_default_graph().get_tensor_by_name("embeddings:0")
                self.phase_train_placeholder = tf.get_default_graph(
                ).get_tensor_by_name("phase_train:0")
        # Setup ros messages and services
        self.output_publisher = rospy.Publisher(
            '/facenet/image_raw/compressed', CompressedImage, queue_size=1)
        self.detect_faces_server = rospy.Service(
            '/facenet/detect_faces', GetFacesFromImage, self.detect_face_srv_callback)
        self.detect_faces_server = rospy.Service(
            '/facenet/recognize_faces', FaceRecognition, self.recognize_face_srv_callback)
        # self.img_subscriber =  rospy.Subscriber("/usb_cam/image_raw/compressed",
        # self.img_subscriber =  rospy.Subscriber("/usb_cam/image_raw/compressed",
        #                      CompressedImage, self.detectFaces)

    def makeClassifier(self):
        """Read database, calculate embeddings and create a linearSVM to classify"""
        dataset = facenet.get_dataset(self.database)
        for cls in dataset:
            assert(len(cls.image_paths) > 0,
                   'There must be at least one image for each class in the dataset')
        paths, labels = facenet.get_image_paths_and_labels(dataset)

        print('Number of classes: %d' % len(dataset))
        print('Number of images: %d' % len(paths))

        if len(paths) > 1:
            with self.graph.as_default():
                with self.sess.as_default():
                    embedding_size = self.embeddings.get_shape()[1]
                    print('Calculating features for images')
                    nrof_images = len(paths)
                    nrof_batches_per_epoch = int(
                        np.ceil(1.0 * nrof_images / self.batch_size))
                    emb_array = np.zeros((nrof_images, embedding_size))
                    for i in range(nrof_batches_per_epoch):
                        start_index = i * self.batch_size
                        end_index = min((i + 1) * self.batch_size, nrof_images)
                        paths_batch = paths[start_index:end_index]
                        images = facenet.load_data(
                            paths_batch, False, False, self.image_size)
                        feed_dict = {self.images_placeholder: images,
                                     self.phase_train_placeholder: False}
                        emb_array[start_index:end_index, :] = self.sess.run(
                            self.embeddings, feed_dict=feed_dict)
                    self.svm = LinearSVC()
                    self.svm.fit(emb_array, labels)
                    class_names = [cls.name.replace(
                        '_', ' ') for cls in dataset]
                    self.labels = class_names
                print self.labels

    def recognizeSVM(self,embeddings):
        """Use previously trained SVM to run inference"""
        predictions = self.svm.decision_function(embeddings)
        best_class_indices = np.argmax(predictions, axis=1)
        #print(best_class_indices)
        best_class_probabilities = predictions[np.arange(len(best_class_indices)), best_class_indices]
        #print best_class_probabilities
        return self.labels[best_class_indices[0]], best_class_probabilities[0]



    def findFaces(self, img, validate=False):
        """Find all faces on img return all faces reshaped and the bounding box"""
        b_boxes = []
        detected = []

        bounding_boxes, _ = align.detect_face.detect_face(
            img, self.minsize, self.pnet, self.rnet, self.onet, self.threshold, self.factor)
        img_h = img.shape[0]
        img_w = img.shape[1]
        for (x1, y1, x2, y2, acc) in bounding_boxes:
            w = x2 - x1
            h = y2 - y1
            y1c = int((y1 + y2) / 2.0 - max(w, h) / 2.0)
            y2c = int((y1 + y2) / 2.0 + max(w, h) / 2.0)
            x1c = int((x1 + x2) / 2.0 - max(w, h) / 2.0)
            x2c = int((x1 + x2) / 2.0 + max(w, h) / 2.0)
            if validate:
                if w <= 0 or h <= 0 or x1c < 0 or y1c < 0 or x2c > np.shape(img)[1] or y2c > np.shape(img)[0]:
                    print "OUT of bounds"
                    continue

            cropped = img[y1c:y2c, x1c:x2c]
            cropped = cv2.resize(
                cropped, (self.image_size, self.image_size), interpolation=cv2.INTER_CUBIC)
            detected.append(facenet.prewhiten(cropped))
            b_boxes.append([x1, y1, x2, y2])

        faces_images = np.array(detected)
        return faces_images, np.array(b_boxes)

    def getMostLikelyFaces(self,detected_imgs):
        """Uses a simple knn algorithm to check the most likely face on the daaset"""
        feed_dict = {self.images_placeholder: detected_imgs,
                     self.phase_train_placeholder: False}
        det_emb = self.sess.run(
            self.embeddings, feed_dict=feed_dict)
        # Distance from every detected face to sample in DB this
        # is faster than iterating on python as np functions are on C
        # Shape of database [images_on_db,512]
        # Shape of distance [detected_images,images_on_db]
        # Shape of best_dist [detected_imgs,1]
        dist = np.linalg.norm(
            self.db_emb - det_emb[:, np.newaxis], axis=2)
        # Extract best face idx in database for each face detected
        print(dist)
        rows = np.arange(det_emb.shape[0])
        best_idx = np.argmin(dist, axis=1)
        best_dist = dist[rows, best_idx]
        return best_dist, best_idx

    def readDB(self):
        with self.graph.as_default():
            with self.sess.as_default():
                self.imagefiles = os.listdir(self.database)
                self.n_images = len(self.imagefiles)
                db_img_list = [cv2.imread(os.path.expanduser(
                    self.database + i)) for i in self.imagefiles]
                db_img_crop = []
                for db in db_img_list:
                    f, _ = self.findFaces(db, validate=False)
                    db_img_crop.append(f)
                db_images = np.array(db_img_crop)
                db_images = db_images.reshape(
                    self.n_images, self.image_size, self.image_size, 3)

                feed_dict = {self.images_placeholder: db_images,
                             self.phase_train_placeholder: False}
                self.db_emb = self.sess.run(
                    self.embeddings, feed_dict=feed_dict)
                print "****DB embeddings extracted****"
                print self.db_emb.shape
                for f in self.imagefiles:
                    print f

    def detect_face_srv_callback(self, req):
        img_np_arr = np.fromstring(req.panoramic_image.data, np.uint8)
        encoded_img = cv2.imdecode(img_np_arr, 1)
        flipped_img = cv2.flip(encoded_img, 1)
        with self.graph.as_default():
            with self.sess.as_default():
                bounding_boxes, _ = align.detect_face.detect_face(
                    flipped_img, self.minsize, self.pnet, self.rnet, self.onet, self.threshold, self.factor)

                detected = []
                faces = VisionFaceObjects()
                for (x1, y1, x2, y2, acc) in bounding_boxes:
                    w = x2 - x1
                    h = y2 - y1
                    y1c = int((y1 + y2) / 2.0 - max(w, h) / 2.0)
                    y2c = int((y1 + y2) / 2.0 + max(w, h) / 2.0)
                    x1c = int((x1 + x2) / 2.0 - max(w, h) / 2.0)
                    x2c = int((x1 + x2) / 2.0 + max(w, h) / 2.0)
                    if w <= 0 or h <= 0 or x1c < 0 or y1c < 0 or x2c > np.shape(flipped_img)[1] or y2c > np.shape(flipped_img)[0]:
                        continue
                    faces.recog_faces.append(
                        self.__ensembleFaceObject(x1, y1, x2, y2))
                    if self.publish_img:
                        cv2.rectangle(flipped_img, (int(x1), int(y1)), (int(x1 + w),
                                                                        int(y1 + h)), (255, 0, 0), 2)
                if self.publish_img:
                    msg = CompressedImage()
                    msg.header.stamp = rospy.Time.now()
                    msg.format = "jpeg"
                    msg.data = np.array(cv2.imencode(
                        '.jpg', flipped_img)[1]).tostring()
                    self.output_publisher.publish(msg)

                resp = GetFacesFromImageResponse()
                resp.faces = faces
                return resp

    def recognize_face_srv_callback(self, req):
        image = self.__getImageFromMSG()
        if not image:
            # Failed return
            return None

        img_np_arr = np.fromstring(image.data, np.uint8)
        encoded_img = cv2.imdecode(img_np_arr, 1)
        flipped_img = cv2.flip(encoded_img, 1)
        with self.graph.as_default():
            with self.sess.as_default():

                faces = VisionFaceObjects()
                detected_imgs, b_boxes = self.findFaces(flipped_img,validate=False)

                if len(detected_imgs) > 0:
                    feed_dict = {self.images_placeholder: detected_imgs,
                                 self.phase_train_placeholder: False}
                    det_emb = self.sess.run(
                        self.embeddings, feed_dict=feed_dict)
                    # Distance from every detected face to sample in DB this
                    # is faster than iterating on python as np functions are on C
                    # Shape of database [images_on_db,512]
                    # Shape of distance [detected_images,images_on_db]
                    # Shape of best_dist [detected_imgs,1]
                    dist = np.linalg.norm(
                        self.db_emb - det_emb[:, np.newaxis], axis=2)
                    # Extract best face idx in database for each face detected
                    rows = np.arange(det_emb.shape[0])
                    best_idx = np.argmin(dist, axis=1)
                    best_dist = dist[rows, best_idx]

                    for det, b_idx, b_dist in zip(rows, best_idx, best_dist):
                        current_box = b_boxes[det]
                        x1, y1, x2, y2 = current_box
                        if b_dist < self.min_thr:
                            nomine = self.imagefiles[b_idx].split('_')[0]
                        else:
                            nomine = "Unknown"

                        print 'Best: ' + str(b_dist) + " " + nomine
                        f = self.__ensembleFaceObject(
                            x1, y1, x2, y2, nomine, b_dist)
                        faces.recog_faces.append(f)
                        if self.publish_img:
                            w = x2 - x1
                            h = y2 - y1
                            cv2.rectangle(flipped_img, (int(x1), int(y1)),
                                          (int(x1 + w),
                                           int(y1 + h)), (255, 0, 0), 2)
                            cv2.putText(
                                flipped_img, nomine, (int(x1), int(y2)), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 255), 2, cv2.LINE_AA)

                if self.publish_img:
                    msg = CompressedImage()
                    msg.header.stamp = rospy.Time.now()
                    msg.format = "jpeg"
                    msg.data = np.array(cv2.imencode(
                        '.jpg', flipped_img)[1]).tostring()
                    self.output_publisher.publish(msg)

                resp = FaceRecognitionResponse()
                resp.faces = faces
                return resp

    def detectFacesContinous(self):
        with self.graph.as_default():
            with self.sess.as_default():
                # Load session and get tensors
                while not rospy.is_shutdown():
                    img = rospy.wait_for_message(
                        "/usb_cam/image_raw/compressed", CompressedImage)
                    img_np_arr = np.fromstring(img.data, np.uint8)
                    encoded_img = cv2.imdecode(img_np_arr, 1)
                    flipped_img = cv2.flip(encoded_img, 1)

                    detected_imgs, b_boxes = self.findFaces(flipped_img,validate=True)

                    if len(detected_imgs) > 0:
                        best_dist, best_idx = self.getMostLikelyFaces(detected_imgs);
                        rows = np.arange(detected_imgs.shape[0])
                        for det, b_idx, b_dist in zip(rows, best_idx, best_dist):
                            x1, y1, x2, y2 = b_boxes[det]
                            w = x2 - x1
                            h = y2 - y1
                            textloc = (int(x1), int(y2))
                            print textloc
                            if b_dist < self.min_thr:
                                nomine = self.imagefiles[b_idx].split('_')[0]
                                print 'Best: ' + str(b_dist) + " " +nomine
                            else:
                                nomine = "Unknown"
                                print 'Best: ' + str(b_dist) + " " +nomine

                            if w <= 0 or h <= 0 or x1 < 0 or y1 < 0 or x2 > np.shape(flipped_img)[1] or y2 > np.shape(flipped_img)[0]:
                                continue
                            cv2.rectangle(flipped_img, (int(x1), int(y1)), (int(x1 + w),
                                                                            int(y1 + h)), (255, 0, 0), 2)
                            cv2.putText(
                                flipped_img, nomine, textloc, cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 255), 2, cv2.LINE_AA)

                    msg = CompressedImage()
                    msg.header.stamp = rospy.Time.now()
                    msg.format = "jpeg"
                    msg.data = np.array(cv2.imencode(
                        '.jpg', flipped_img)[1]).tostring()
                    self.output_publisher.publish(msg)

    def __ensembleFaceObject(self, x1, y1, x2, y2, name="ACK", confidence=0):
        """Helper function to ensemble a face object
        ACK means dont care or no apply"""
        face = VisionFaceObject()

        face.id = name
        face.confidence = confidence
        face.face_centroid.x = 0
        face.face_centroid.y = 0
        face.face_centroid.z = 0

        p = Point()
        p.x = x1
        p.y = y1
        p.z = 0
        face.bounding_box.append(p)

        p = Point()
        p.x = x2
        p.y = y2
        p.z = 0
        face.bounding_box.append(p)
        face.smile = False
        face.gender = 2
        face.ages = 1

        return face

    def run(self):
        minsize = 20  # minimum size of face
        threshold = [0.7, 0.8, 0.8]  # three steps's threshold
        factor = 0.709  # scale factor

        with tf.Graph().as_default():
            gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=0.5)
            sess = tf.Session(config=tf.ConfigProto(
                gpu_options=gpu_options, log_device_placement=False))
            with sess.as_default():
                pnet, rnet, onet = align.detect_face.create_mtcnn(sess, None)

        output_publisher = rospy.Publisher(
            'facenet/image_raw/compressed', CompressedImage, queue_size=1)

        with tf.Graph().as_default():
            with tf.Session() as sess:
                facenet.load_model(self.model)
                imagefiles = os.listdir(self.database)
                db_img_list = [misc.imread(os.path.expanduser(
                    self.database + i)) for i in imagefiles]
                db_img_crop = []
                for db in db_img_list:
                    bounding_boxes, _ = align.detect_face.detect_face(
                        db, minsize, pnet,
                        rnet, onet, threshold, factor)
                    for (x1, y1, x2, y2, acc) in bounding_boxes:
                        w = x2 - x1
                        h = y2 - y1
                        y1c = int((y1 + y2) / 2.0 - max(w, h) / 2.0)
                        y2c = int((y1 + y2) / 2.0 + max(w, h) / 2.0)
                        x1c = int((x1 + x2) / 2.0 - max(w, h) / 2.0)
                        x2c = int((x1 + x2) / 2.0 + max(w, h) / 2.0)
                        cropped = db[y1c:y2c, x1c:x2c]
                        cropped = cv2.resize(
                            cropped, (160, 160), interpolation=cv2.INTER_CUBIC)
                        db_img_crop.append(facenet.prewhiten(cropped))
                        break

                db_images = np.array(db_img_crop)

                images_placeholder = tf.get_default_graph().get_tensor_by_name("input:0")
                embeddings = tf.get_default_graph().get_tensor_by_name("embeddings:0")
                phase_train_placeholder = tf.get_default_graph().get_tensor_by_name("phase_train:0")
                feed_dict = {images_placeholder: db_images,
                             phase_train_placeholder: False}
                db_emb = sess.run(embeddings, feed_dict=feed_dict)

                # nrof_images = len(imagefiles)
                # print('Images:')
                # for i in range(nrof_images):
                # print('%1d: %s' % (i, imagefiles[i]))
                # print('')
                # print('Distance matrix')
                # print('    ')
                # for i in range(nrof_images):
                # print '    %1d     ' % i,
                # print('')
                # for i in range(nrof_images):
                # print '%1d  ' % i,
                # for j in range(nrof_images):
                # dist = np.sqrt(np.sum(np.square(np.subtract(db_emb[i,:], db_emb[j,:]))))
                # print '  %1.4f  ' % dist,
                # print('')

                while not rospy.is_shutdown():
                    img = rospy.wait_for_message(
                        "/usb_cam/image_raw/compressed", CompressedImage)
                    img_np_arr = np.fromstring(img.data, np.uint8)
                    encoded_img = cv2.imdecode(img_np_arr, 1)
                    flipped_img = cv2.flip(encoded_img, 1)
                    bounding_boxes, _ = align.detect_face.detect_face(
                        flipped_img, minsize, pnet,
                        rnet, onet, threshold, factor)

                    detected = []
                    textlocs = []
                    for (x1, y1, x2, y2, acc) in bounding_boxes:
                        w = x2 - x1
                        h = y2 - y1
                        y1c = int((y1 + y2) / 2.0 - max(w, h) / 2.0)
                        y2c = int((y1 + y2) / 2.0 + max(w, h) / 2.0)
                        x1c = int((x1 + x2) / 2.0 - max(w, h) / 2.0)
                        x2c = int((x1 + x2) / 2.0 + max(w, h) / 2.0)
                        if w <= 0 or h <= 0 or x1c < 0 or y1c < 0 or x2c > np.shape(flipped_img)[1] or y2c > np.shape(flipped_img)[0]:
                            continue
                        cv2.rectangle(flipped_img, (int(x1), int(y1)), (int(x1 + w),
                                                                        int(y1 + h)), (255, 0, 0), 2)
                        cropped = flipped_img[y1c:y2c, x1c:x2c]
                        cropped = cv2.resize(
                            cropped, (160, 160), interpolation=cv2.INTER_CUBIC)
                        detected.append(facenet.prewhiten(cropped))
                        textlocs.append((int(x1), int(y2)))
                    detected_imgs = np.array(detected)

                    if len(detected_imgs) > 0:
                        feed_dict = {images_placeholder: detected_imgs,
                                     phase_train_placeholder: False}
                        det_emb = sess.run(embeddings, feed_dict=feed_dict)
                        for det in range(len(detected_imgs)):
                            best = 10.0
                            bestdet = ''
                            for db in range(len(imagefiles)):
                                dist = np.sqrt(
                                    np.sum(np.square(np.subtract(db_emb[db, :], det_emb[det, :]))))
                                print 'distance to ' + \
                                    imagefiles[db] + ': ' + str(dist)
                                if dist < best:
                                    best = dist
                                    bestdet = imagefiles[db]
                            if best < 0.95:
                                print 'best: ' + bestdet
                                cv2.putText(flipped_img, bestdet.split('_')[
                                            0], textlocs[det], cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 255), 2, cv2.LINE_AA)
                            else:
                                cv2.putText(
                                    flipped_img, 'Unknown', textlocs[det], cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 255), 2, cv2.LINE_AA)

                    msg = CompressedImage()
                    msg.header.stamp = rospy.Time.now()
                    msg.format = "jpeg"
                    msg.data = np.array(cv2.imencode(
                        '.jpg', flipped_img)[1]).tostring()
                    output_publisher.publish(msg)


if __name__ == "__main__":
    rospy.init_node(NODE_NAME, anonymous=False)
    model = rospy.get_param("~model")
    database = rospy.get_param("~database")
    min_dist = rospy.get_param("~min_dist")
    img_sz = rospy.get_param("~image_size")
    batch_sz = rospy.get_param("~batch_size")
    node = FaceNetNode(model, database, min_dist,
                       image_size=img_sz, batch_size=batch_sz)
    node.setupNode()
    node.readDB()
    #node.makeClassifier()
    print "*** Starting Inference ***"

    node.detectFacesContinous()
    # rospy.spin()
