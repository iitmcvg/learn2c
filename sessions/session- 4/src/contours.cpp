#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/** @function main */
int main( int argc, char** argv )
{
  
  Mat src; Mat src_gray;
  
  /// Load source image and convert it to gray
  src = imread( <path to image> , 1 );

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  namedWindow( "src", CV_WINDOW_AUTOSIZE );
  imshow( "src", src );
  
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// threshold
  //threshold(src_gray,threshold_output, 150,255,THRESH_BINARY);
  
  //imshow( "Threshold", threshold_output );
  
  /// Find contours
  findContours( src_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( src_gray.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       drawContours( drawing, contours, i, Scalar(255,255,255), 1, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
  waitKey(0);
  return(0);
}
