/*
 *  Author: Xue Ye Lin <xue.ye.lin@vanderbilt.edu>
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

// uarm directions (if you were to just enter gcode into serial)
/*
              x
              |
    zeroPt    |
              |
y______uarm swift pro front______

*/
const std::string GCODE_FILE_PATH =
    "/home/xueyelin/Thermite_Boom_Boom/Code/ROS/uarmws/src/swiftpro/"
    "example_Gcode/U_3DBenchy12.gcode";

serial::Serial _serial; // serial object
swiftpro::SwiftproState arm_state;

const float zeroPt[] = {150, 43, 0};
// G0 X150 Y43 Z0.00

void offset_pos_gcode(std::string &str) {
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
    // std::cout<<xStr[0]<<","<<xStr[1]<<" "<<yStr[0]<<","<<yStr[1]<<std::endl;
    // std::cout<<str.substr(xStr[0],xStr[1])<<"
    // "<<str.substr(yStr[0],yStr[1])<<std::endl;
    float xPos, yPos;
    // swich the x and y and apply offset
    xPos = std::stof(str.substr(yStr[0], yStr[1])) + zeroPt[0];
    yPos = zeroPt[1]- std::stof(str.substr(xStr[0], xStr[1]));
    // std::cout<<xPos<<std::endl;
    // std::cout<<yPos<<std::endl;
    str = str.substr(0, xStr[0]) + std::to_string(xPos) + " Y" +
          std::to_string(yPos) + str.substr(yStr[0] + yStr[1]);
  }
}

std::string write_gcode_ln(std::ifstream &gcode_file) {
  std::string gcode_str;
  if (std::getline(gcode_file, gcode_str)) {
    // skips over comments
    while ((gcode_str[0] == ';' || gcode_str.empty()) && !gcode_file.eof()) {
      std::getline(gcode_file, gcode_str);
      ROS_INFO(" in write gcode");
    }
    // converts from std::string gcode into swiftpro::gcode message
    // the addition of "\r\n" is carraige return and newline to trigger
    // a command in the Marlin firmware
    offset_pos_gcode(gcode_str);
    gcode_str += "\r\n";
    _serial.write(gcode_str.c_str());
    ROS_INFO("%s", gcode_str.c_str());
  }

  return gcode_str;
}

/*
 * Node name: swiftpro_write_gcode_node
 *
 * Topic publish: (rate = 20Hz, queue size = 4) position_read_topic
 */
int main(int argc, char **argv) {
  // initialize ros
  ros::init(argc, argv, "swiftpro_write_gcode_node");
  ros::NodeHandle nh;
  swiftpro::SwiftproState swiftpro_state;

  // initialize serial communication with uarm swift pro
  try {
    _serial.setPort("/dev/ttyACM0");
    _serial.setBaudrate(115200);
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    _serial.setTimeout(to);
    _serial.open();
    ROS_INFO_STREAM("Port has been open successfully");
  } catch (serial::IOException &e) {
    ROS_ERROR_STREAM("Unable to open port");
    return -1;
  }

  // set up uarm for recieving 3D prining G-code data
  if (_serial.isOpen()) {
    ros::Duration(3.5).sleep();    // wait 3.5s
    _serial.write("M2120 V0\r\n"); // stop report position
    ros::Duration(0.1).sleep();    // wait 0.1s
    _serial.write("M17\r\n");      // attach
    ros::Duration(1).sleep();      // wait 0.1s

    ROS_INFO_STREAM("Waiting for commands");
  }
  ros::Duration(3).sleep(); // wait 3s

  std_msgs::String result;

  // dump the intitial data stream and issue first command
  if (_serial.available()) {
    result.data = _serial.read(_serial.available());
    ROS_INFO("read 1: %s", result.data.c_str());
    ros::Duration(1).sleep(); // wait 1s
  }

  // Go to home
  _serial.write("G0 X" + std::to_string(zeroPt[0]) + " Y" +
                std::to_string(zeroPt[1]) + " Z0.3\r\n"); // move to zero point
  ros::Duration(3).sleep();

  // open gcode file to be read
  std::ifstream gcode_file(GCODE_FILE_PATH);
  std::string gcode_str;

  ros::Publisher pub =
      nh.advertise<swiftpro::SwiftproState>("SwiftproState_topic", 1);
  ros::Rate loop_rate(20);

  ROS_INFO("entering while loop");
  while (ros::ok()) {
    // result.data = _serial.read(_serial.available());
    // ROS_INFO("read: %s", result.data.c_str());
    // only operate if there are things in the buffer
    if (_serial.available()) {
      std::string response = _serial.readline();
      ROS_INFO("read: %s", response.c_str());
      ROS_INFO("read: %zu", response.size());

      // only send data if previous command has been completed
      // this is how octoprint does it, might need to put some
      // more into buffers
      ROS_INFO("boolean %d", response.substr(0,2) == "ok");

      if (response.substr(0,2) == "ok" ) {
        ROS_INFO("writing gcode again");

        write_gcode_ln(gcode_file);
        pub.publish(arm_state);
      } else if (response.substr(0, 18) == "ok E22 unreachable ") {
        ROS_INFO("ERROR, Unreachable Position");
        return 1;
      }
      result.data.clear();

      ros::spinOnce();
    }
    loop_rate.sleep();
  }

  gcode_file.close();
  _serial.close();

  return 0;
}