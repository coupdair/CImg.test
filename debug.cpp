//CImg debug define test
//compilation: g++ -o debug debug.cpp -I../CImg -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_display=0 -Dcimg_verbosity=3 -Dcimg_strict_warnings #no GUI
//               -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr #GUI
//shell loop for compilation: for w in yes no ; do if [ "$w" == "yes" ] ; then w=_cimg_strict_warnings; dw=-Dcimg_strict_warnings; else w=; dw=; fi; for v in 0 3; do g++ -o debug_cimg_verbosity$v$w debug.cpp -I../CImg -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_display=0 $dw -Dcimg_verbosity=$v; done ; done; ls debug_cimg_*
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
  cimg_usage("CImg debug define test program\n usage:\t./debug -h -I\n\t./debug -I -i ../CImg/examples/img/parrot_original.ppm");
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
  //loop within image with first maximum position search
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
  //loop outoff image with first maximum position search
  std::cout<<"scan for (first) maximum position, should go out off container bound\n  - if cimg_debug=0, might create a segmentation fault.\n  - if cimg_strict_warnings and cimg_verbosity=3, should output an error message and stop (i.e. exception).\n  - if cimg_verbosity=3, should output warning messages, but not stop.\n\n"<<std::flush;
  max=cimg::type<float>::min();
const int shift=123;
  cimg_forXYZC(image,x,y,z,c) //cimg_forXYZV in version prior to CImg.v1.3.?
  {
    if(image(x+shift,y,z,c)>max)
    {
      max=image(x+shift,y,z,c);
      max_x=x+shift;max_y=y;max_z=z;max_c=c;
    }
  }
  std::cout<<"\rmaximum position=("<<max_x<<","<<max_y<<","<<max_z<<","<<max_c<<") with a value of "<<max<<"\n"<<std::flush;
  return 0;
}

