

#include <fstream>
#include <iostream>





void offset_pos_gcode(std::string str){
  //only offset if its x and y we have to rearange
  if(str.substr(0,2)=="G1" || str.substr(0,2)=="G0" ){
    float pt[2];
    int xStr[2], yStr[2];
    
    // for(int i(0);i<str.length();++i){
    //   if(str[i] == 'X'){
    //     //go to next next space or if end is reached first
    //     xStr[0] = i;
    //     for(;str[i]!=' ';++i){}
    //     xStr[1] = i;

    //   }
    //   else if (str[i] == 'Y'){
    //     yStr[0] = i;
    //     for(;str[i]!=' ' && i<str.length();++i){}
    //     yStr[1] = i;
    //   }
    // }
  std::cout<<xStr[0]<<","<<xStr[1]<<" "<<yStr[0]<<","<<yStr[1]<<std::endl;
  std::cout<<str.substr(xStr[0],xStr[1]-xStr[0])<<" "<<str.substr(yStr[0],yStr[1]-yStr[0])<<std::endl
  }
}

int main(int argc, char **argv)
{
    std::string a = "G1 X45.289 Y51.675 E3582.4682";
    offset_pos_gcode(a);
  return 0;
}