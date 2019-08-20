#!/usr/bin/env python
from __future__ import print_function

import roslib
import sys
import rospy
import cv2
import tensorflow as tf
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
from utils import detector_utils as detector_utils
import rospkg


class hand_tracker:

    def __init__(self, hands, thr, graph_file):
        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("image", Image, self.callback)
        self.detection_graph, self.sess = detector_utils.load_inference_graph(
            graph_file)
        self.hands = hands
        self.thr = thr

    def callback(self, data):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)
            return

        (rows, cols, channels) = cv_image.shape

        # actual detection
        boxes, scores = detector_utils.detect_objects(
            cv_image, self.detection_graph, self.sess)

        # draw bounding boxes
        detector_utils.draw_box_on_image(
            self.hands, self.thr, scores, boxes, cols, rows, cv_image)

        #

        cv2.imshow("Image window", cv_image)
        cv2.waitKey(25)

        return
        # try:
        #     self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
        # except CvBridgeError as e:
        #     print(e)


def main(args):
    if rospy.has_param("~hands"):
        hnd = rospy.get_param("~hands")
    else:
        hnd = 2
    if rospy.has_param("~thr"):
        thr = rospy.get_param("~thr")
    else:
        thr = 0.3
    print("Debug message")
    pkg = rospkg.RosPack()
    graph_file = pkg.get_path('hand_tracking')
    graph_file = graph_file + "/scripts/handtracking/hand_inference_graph/"
    print("\n")
    print(graph_file)
    if rospy.has_param("~graph_file"):
        graph_file = graph_file + rospy.get_param("~graph_file")
    else:
        graph_file = graph_file + "frozen_inference_graph.pb"

    ic = hand_tracker(hnd, thr, graph_file)
    rospy.init_node('hand_tracker', anonymous=True)
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main(sys.argv)
