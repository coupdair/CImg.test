//CImg debug define test
//compilation: g++ -o debug debug.cpp -I../CImg -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_display=0 -Dcimg_debug=1 #no GUI
//               -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr #GUI
//run line: ./debug -I -h
//run line: ./debug -I -i ../CImg/examples/img/parrot_original.ppm

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
  cimg_usage("CImg debug define test program\n usage:\t./option -h -I\n\t./option -I -i ../CImg/examples/img/parrot_original.ppm");
  //get if help is requested
  const bool help=cimg_option("-h",false,"showing help only");
  //get a file name from command line (or use default)
  const std::string file_name=cimg_option("-i","image.png","Input image");
  //show compilation options, such as debug, GUI, external library (e.g. FTTw), ...
  if(cimg_option("-I",false,"show compilation options")) cimg_library::cimg::info();
  //exit if help requested
  if(help) return 0;
  //load image
  const CImg<float> image(file_name.c_str());
  //show loaded image statistics
  image.print(file_name.c_str());
  //loop within image
  std::cout<<"scan for (first) maximum position"<<std::flush;
  float max=cimg::type<float>::min();int max_x,max_y,max_z,max_c;
  cimg_forXYZC(image,x,y,z,c) //cimg_forXYZV in version prior to CImg.v1.3.?
  {
    if(image(x,y,z,c)>max)
    {
      max=image(x,y,z,c);
      max_x=x;max_y=y;max_z=z;max_c=c;
    }
  }
  std::cout<<"\rmaximum position=("<<max_x<<","<<max_y<<","<<max_z<<","<<max_c<<") with a value of "<<max<<"\n"<<std::flush;
  //loop outoff image
  //! \todo try to read outoff bounds
  return 0;
}

