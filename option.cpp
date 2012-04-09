//CImg command line option test
//compilation: g++ -o option option.cpp -I../CImg -Wall -W -lm -ansi -pedantic -O3 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_display=0 #no GUI
//               -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr #GUI
//run line: ./option -I -h
//run line: ./option -I -i ../CImg/examples/img/parrot_original.ppm
//run line: ./option --value 4.321

//include CImg library (and use its main namespace)
//#include "../CImg/CImg.h"
#include "CImg.h"
using namespace cimg_library;

//include STL library
#include <iostream>
#include <string>
//using namespace std;

int main(int argc,char **argv)
{
  //Display program usage, when invoked from the command line with option '-h'.
  cimg_usage("CImg command line option test program\nusage:\t./option -h -I\n\t./option -I -i ../CImg/examples/img/parrot_original.ppm");
  //get if help is requested
  const bool help=cimg_option("-h",false,"showing help only");
  //get a file name from command line (or use default)
  const std::string file_name=cimg_option("-i","image.png","Input image");
  //get a floating point value from command line (or use default)
  const double value=cimg_option("--value",1.2345,"optional value");
  //show compilation options, such as debug, GUI, external library (e.g. FTTw), ...
  if( cimg_option("-I",(const char*)NULL,"show compilation options") != NULL ) cimg_library::cimg::info();
  //exit if help requested
  if(help) return 0;
  //show value
  std::cout<<"value="<<value<<std::endl;
  //load image
  const CImg<unsigned char> image(file_name.c_str());
  //show loaded image statistics
  image.print(file_name.c_str());
  return 0;
}

