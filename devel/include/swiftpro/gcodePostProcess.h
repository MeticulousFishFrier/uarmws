#include <fstream>
#include <iostream>
#include <string>

#ifndef SWIFTPRO_GCODEPOSTPROCESS_H
#define SWIFTPRO_GCODEPOSTPROCESS_H

// const std::string GCODE_FILE_PATH =
//     "/home/xueyelin/Thermite_Boom_Boom/Code/Examples/test3.gcode";

// const std::string NEW_GCODE_FILE_PATH =
//     "/home/xueyelin/Thermite_Boom_Boom/Code/Examples/test3Offset.gcode";

// const float zeroPt[] = {150, 43, 0};
// const float zeroPt[] = {133.5, 48.5, 0};

class gcodeFile {
public:
  gcodeFile(const std::string &gcode_file_str,
            const std::string &new_gcode_file_str, float (&zero)[3])
      : in_gcode_file(gcode_file_str), out_gcode_file(gcode_file_str),
        zeroPt(zero) {
    convert_gcode_file();
  }

private:
  std::ifstream in_gcode_file;
  std::ofstream out_gcode_file;
  float (&zeroPt)[3];

  // G0 X133.5 Y48.5 Z0
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

  void convert_gcode_file() {
    std::string gcode_str;
    while (std::getline(in_gcode_file, gcode_str)) {
      // skips over comments
      while (gcode_str[0] == ';' || gcode_str.empty() && !in_gcode_file.eof()) {
        std::getline(in_gcode_file, gcode_str);
      }
      offset_pos_gcode(gcode_str);
      gcode_str += "\r\n";
      std::cout << gcode_str;
      out_gcode_file << gcode_str;
    }
  }
};

#endif // SWIFTPRO_GCODEPOSTPROCESS_H
