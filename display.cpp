//CImg display define test
//compilation: g++ -o display display.cpp -I../CImg -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_verbosity=3 \
                 -I/usr/X11R6/include -Dcimg_use_xshm -Dcimg_use_xrandr -L/usr/X11R6/lib -lpthread -lX11 -lXext -lXrandr #GUI
//compilation: g++ -o display display.cpp -I../CImg -Wall -W -lm -ansi -pedantic -O0 -fno-tree-pre -Dcimg_use_vt100 -Dcimg_verbosity=3 -Dcimg_display=0
//run line: ./display -I -h
//run line: ./display -I -x 64 -y 32 -z 8 -c 3

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
  cimg_usage("CImg display define test program\n usage:\t./display -h -I\n\t./display -I -x 64 -y 32 -z 8 -c 3");
  //get if help is requested
  const bool help=cimg_option("-h",false,"showing help only");
  //get x dimension of image from command line (or use default)
  const int dim_x=cimg_option("-x",456,"image width  (i.e. size in x direction)");
  //get y dimension of image from command line (or use default)
  const int dim_y=cimg_option("-y",123,"image height (i.e. size in y direction)");
  //get z dimension of image from command line (or use default)
  const int dim_z=cimg_option("-z",1,  "image depth  (i.e. size in z direction");
  //get c dimension of image from command line (or use default)
  const int dim_c=cimg_option("-c",1,  "image component or spectrum (i.e. size in c direction)");
  //show compilation options, such as debug, GUI, external library (e.g. FTTw), ...
  if(cimg_option("-I",false,"show compilation options")) cimg_library::cimg::info();
  //exit if help requested
  if(help) return 0;
  //load image
  CImg<float> image(dim_x,dim_y,dim_z,dim_c);
  //loop within image with first maximum position search
  std::cout<<"create a gradient within the image.\n"<<std::flush;
  cimg_forXYZC(image,x,y,z,c) //cimg_forXYZV in version prior to CImg.v1.3.?
  {
    image(x,y,z,c)=x+y+z+c;
  }
  //show loaded image statistics and display
#if cimg_display==0
  image.print("image");
#else
  image.display("image");
#endif
  return 0;
}

