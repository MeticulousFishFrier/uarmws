#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""ROS Node to handle sending many lines of GCode to UArm using Print Core"""

# Import ROS Python library
import rospy
# to send a file of gcode to the printer
from printrun.printcore import printcore
from printrun import gcoder
import time
import std_msgs.msg
from std_msgs.msg import String
from swiftpro.msg import position

pub = rospy.Publisher("position_topic", position,  queue_size=1)

def swiftpro_gcode_sender_node():
    rospy.init_node("swiftpro_gcode_sender_node")
    rospy.Subscriber("gcodeFilePath_topic", String, callback)
    rospy.spin()


def callback(message):
    print("in call back")
    # gcodeFileName = '/home/xueyelin/Thermite_Boom_Boom/Code/Examples/test2Offset.gcode'
    gcodeFileName = message.data
    # gcodeFileName = data
    print("trying gcode sender")
    print(gcodeFileName)
    # or p.printcore('COM3',115200) on Windows
    p = printcore('/dev/ttyACM0', 115200)

    # Sleeps for 1 sec t o allow for UArm's serial jiberish
    # or pass in your own array of gcode lines instead of reading from a file

    rospy.sleep(1)

    gcode = [i.strip() for i in open(gcodeFileName)]
    gcode = gcoder.LightGCode(gcode)
    p.startprint(gcode)  # this will start a print

    prev_cmd = None
    while(p.printing is True):
        if(prev_cmd != p.sent[-1] ):
            print(p.sent[-1])
            prev_cmd = p.sent[-1]
        # p.disconnect()


# Main function.
if __name__ == "__main__":

    try:
        swiftpro_gcode_sender_node()
    except rospy.ROSInterruptException:
        pass

    # swiftpro_gcode_sender_node()
    print("oh yeah exit")

