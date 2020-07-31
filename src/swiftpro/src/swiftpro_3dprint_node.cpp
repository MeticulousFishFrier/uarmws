/*
 * Author: Xue Ye Lin <xue.ye.lin@vanderbilt.edu>
 * Last Modified: 07/30/20
 */

#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <string>
#include <swiftpro/SwiftproState.h>
#include <swiftpro/angle4th.h>
#include <swiftpro/gcode.h>
#include <swiftpro/position.h>
#include <swiftpro/status.h>

#include <fstream>
#include <iostream>
#include <string>

// should be relative path
// const std::string GCODE_FILE_PATH =
//     "/home/xueyelin/Thermite_Boom_Boom/Code/ROS/uarmws/src/swiftpro/"
//     "example_Gcode/moveZTest.gcode";

const std::string GCODE_FILE_PATH =
    "/home/xueyelin/Thermite_Boom_Boom/Code/Examples/test3.gcode";

const std::string NEW_GCODE_FILE_PATH =
    "/home/xueyelin/Thermite_Boom_Boom/Code/Examples/test3Offset.gcode";

// const float zeroPt[] = {150, 43, 0};
// const float zeroPt[] = {133.5, 48.5, 0};

// G0 X133.5 Y48.5 Z0
void offset_pos_gcode(std::string &str,const float (&zeroPt)[3]) {
  // only offset if its x and y we have to rearange
  if ((str.substr(0, 2) == "G1" || str.substr(0, 2) == "G0") &&
      str.find('X') != -1) {
    int xStr[2], yStr[2];

    for (int i(0); i < str.length(); ++i) {
      if (str[i] == 'X') {
        // go to next next space or if end is reached first
        xStr[0] = i + 1;
        for (; str[i] != ' '; ++i) {
        }
        xStr[1] = i - xStr[0];

      } else if (str[i] == 'Y') {
        yStr[0] = i + 1;
        int yEnd = str.substr(yStr[0]).find_first_of(' ');
        // std::cout<<yEnd;
        yStr[1] = (yEnd != -1) ? yEnd : str.length() - yStr[0];
      }
    }

    float xPos, yPos;
    // swich the x and y and apply offset
    xPos = std::stof(str.substr(yStr[0], yStr[1])) + zeroPt[0];
    yPos = zeroPt[1] - std::stof(str.substr(xStr[0], xStr[1]));
    str = str.substr(0, xStr[0]) + std::to_string(xPos) + " Y" +
          std::to_string(yPos) + str.substr(yStr[0] + yStr[1]);
  }
}

std::string convert_gcode_file(const std::string &gcode_file_path,const float (&zeroPt)[3]) {
  std::ifstream in_gcode_file(gcode_file_path);
  // TODO: change gcodefile filepath such that we basically generate another file
  // in the same folder as the original file
  std::string new_gcode_file_path(gcode_file_path);

  std::ofstream out_gcode_file(gcode_file_path);

  std::string gcode_str;
  // std::cout<<"in first while loop\n";
  while (std::getline(in_gcode_file, gcode_str)) {
    // skips over comments
    while (gcode_str[0] == ';' || gcode_str.empty() && !in_gcode_file.eof()) {
      std::getline(in_gcode_file, gcode_str);
    }
    offset_pos_gcode(gcode_str,zeroPt);
    gcode_str += "\r\n";
    std::cout << gcode_str;
    out_gcode_file << gcode_str;
  }
  return gcode_file_path;
}

/*
 * Node name: swiftpro_3dprint_node
 * Description: Takes a GCode file, converts it to uarm coordinates in a new
 * GCode file such that X0 Y0 corresponds to the bottom left corner of the 3D
 * print object and resets the Z0  of the UArm to correspond with the lowest
 * point of the surface that is to be printed on
 *
 * TODO:
 * - Make a subscriber to a (not started) camera node that automatically
 * supplies the X0 Y0 Z0 offset of the surface via OpenCV
 * - Post process Slic3r G-Code to create a new G-Code file with appropritate
 * offsets
 * - Add option so GCODE_FILE_PATH is defined at command line when roslaunch is
 * performed
 *
 * Topic publish: (rate = 20Hz, queue size = 1) position_read_topic
 */
int main(int argc, char **argv) {
  ros::init(argc, argv, "swiftpro_3dprint_node");

  ros::NodeHandle nh;

  // latch allows a new subscriber always gets the last message that was
  // published even if the message was published before the subscriber was
  // connected.
  ros::Publisher gcode_pub =
      nh.advertise<std_msgs::String>("gcodeFilePath_topic", 1, true);

  ros::Rate loop_rate(20);

  std_msgs::String file_path;

  file_path.data = GCODE_FILE_PATH;

  ROS_INFO("%s", file_path.data.c_str());

  gcode_pub.publish(file_path);
  ros::spin();

  return 0;
}