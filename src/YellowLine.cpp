#define YELLOWLINE_DEBUG
#include "LeastSquare.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void getYellowRegion(cv::Mat& src, cv::Mat& dst, int H_low=30, int H_high=75, int S_threshold=80, int V_threshold=80)
{
  cv::Mat hsv, yellow_h1, yellow_h2, yellow_h, yellow_sv;
  std::vector<cv::Mat > hsvSplit;
  cv::cvtColor(src, hsv, CV_BGR2HSV_FULL); 
  cv::split(hsv, hsvSplit);	

  cv::threshold(hsvSplit[0], yellow_h1, H_low,
      255, cv::THRESH_BINARY); 
  cv::threshold(hsvSplit[0], yellow_h2, H_high,
      255, cv::THRESH_BINARY_INV); //restrict H in yellow range
  cv::threshold(hsvSplit[1], hsvSplit[1], S_threshold,
      255, cv::THRESH_BINARY); 
  cv::threshold(hsvSplit[2], hsvSplit[2], V_threshold,
      255, cv::THRESH_BINARY); //remove not so yellow points

  cv::bitwise_and(yellow_h1, yellow_h2, yellow_h);	
  cv::bitwise_and(hsvSplit[1], hsvSplit[2], yellow_sv);
  cv::bitwise_and(yellow_h, yellow_sv, dst);	//get overlapped region

#ifdef YELLOWLINE_DEBUG
  hsvSplit[0] = yellow_h;
  cv::merge(hsvSplit, hsv);//hsv mapping bgr for tuning parameters
  cv::imshow("debug", hsv);
  cv::waitKey(1);
#endif
}

int main()
{
  const int H_low = 29;  
  const int H_high = 29;  
  const int S_threshold = 29;  
  const int V_threshold = 29;  

  cv::VideoCapture cap("../line2.avi"); 
  cv::Mat frame, yellow_region, draw_line; 
  std::vector<cv::Mat > bgrSplit;	
  std::vector<int> yellow_points_x, yellow_points_y; 
  float vector_x,vector_y;
  cv::namedWindow("frame", 1); 

  while(cap.read(frame))	
  {
    cv::split(frame, bgrSplit);	
    getYellowRegion(frame, yellow_region, 
            H_low, H_high, S_threshold, V_threshold);

    /* get yellow points' x and y */
    for (int i=0; i<frame.rows; ++i) 
    {
      uchar *data = yellow_region.ptr<uchar>(i); 
      for(int j=0; j<frame.cols; ++j) 
      {
        if (*data==255) 
        {
          yellow_points_x.push_back(j);
          yellow_points_y.push_back(i);
        }
        ++data;
      }
    }

    /* fit line and display*/
    if(!yellow_points_x.empty())
    {
      LeastSquare leastsq(yellow_points_x,yellow_points_y);
      leastsq.print();
      leastsq.getDirection(frame.cols/2, frame.rows/2, vector_x, vector_y);

      leastsq.draw(bgrSplit[1]);
      cv::line(bgrSplit[1], cv::Point(frame.cols/2, frame.rows/2),
              cv::Point(frame.cols/2+vector_x, frame.rows/2+vector_y), cv::Scalar(255));	
      cv::merge(bgrSplit, draw_line);		

    }
    cv::imshow("frame", draw_line);
    cv::waitKey(0);

    yellow_points_x.clear(); 
    yellow_points_y.clear();
  }
  return 0;
}

