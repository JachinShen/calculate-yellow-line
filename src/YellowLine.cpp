#include "LeastSquare.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
/************************************************************************************/
/*			函数名：getYellowRegion												*/
/*			功能：输入图像src，返回图像dst，黄色区域值为200,						*/
/*				其他区域根据满足条件多少，值分别为0, 50, 100, 150					*/
/*				便于显示直观图像调试												*/
/*				将最后一个参数if_debug赋1后，将通过颜色分别显示HSV三通道二值化结果	*/
/*				对应关系：蓝色对于H通道，绿色对应S通道，红色对应V通道				*/
/************************************************************************************/
void getYellowRegion(cv::Mat& src, cv::Mat& dst, int h_low=30, int h_high=75, int s_threshold=80, int v_threshold=80)
{
  cv::Mat hsv, Line_h1, Line_h2, Line_h, Line_sv;
  std::vector<cv::Mat > hsvSplit;
  cv::cvtColor(src, hsv, CV_BGR2HSV_FULL); //转换成HSV
  cv::split(hsv, hsvSplit);	//分离出HSV通道，用于提取黄色区域
  cv::threshold(hsvSplit[0], Line_h1, h_low,
      255, cv::THRESH_BINARY); //去除 H 小于 h_low 度的区域
  cv::threshold(hsvSplit[0], Line_h2, h_high,
      255, cv::THRESH_BINARY_INV); //去除 H 大于 h_high 度的区域
  cv::threshold(hsvSplit[1], hsvSplit[1], s_threshold,
      255, cv::THRESH_BINARY); //去除 S 小于 s_threshold 的区域
  cv::threshold(hsvSplit[2], hsvSplit[2], v_threshold,
      255, cv::THRESH_BINARY); //去除 V 小于 v_threshold 的区域
  cv::bitwise_and(Line_h1, Line_h2, Line_h);	
  cv::bitwise_and(hsvSplit[1], hsvSplit[2], Line_sv);
  cv::bitwise_and(Line_h, Line_sv, dst);	//矩阵相加, dst = Line_h1 + Line_h2 + hsvSplit[1] + hsvSplit[2]
#ifdef YELLOWLINE_DEBUG
  hsvSplit[0] = Line_h;
  cv::merge(hsvSplit,hsv);
  cv::imshow("debug", hsv);
  cv::waitKey(1);
#endif
}

int main()
{

  cv::VideoCapture cap("../line2.avi"); //获取视频
  cv::Mat frame, img; //定义用到的cv::Mat
  std::vector<cv::Mat > bgrSplit;	//分离通道用到的cv::Mat vector
  std::vector<int> x,y; //x,y坐标储存vector
  float vector_x,vector_y;
  cv::namedWindow("frame", 1); 
  while(cap.read(frame))	//此函数读取图像并返回bool值，读取成功返回1
  {
    cv::split(frame, bgrSplit);	//分离出BGR通道，为最终显示结果做准备
    getYellowRegion(frame, img, 29, 75, 75, 80);
    for (int i=0; i<frame.rows; ++i) //遍历每一行
    {
      uchar *data = img.ptr<uchar>(i); //获取此行开头指针
      for(int j=0; j<frame.cols; ++j) //遍历此行每个元素
      {
        if (*data==255) //如果刚好满足之前4个条件（200 = 50 + 50 + 50 + 50）
        {
          x.push_back(j);	//添加 x 坐标
          y.push_back(i); //添加 y 坐标
        }
        ++data; //指到下一个元素
      }
    }

    if(!x.empty()) //如果有数据
    {
      LeastSquare leastsq(x,y); //拟合曲线
      leastsq.print(); //显示结果
      leastsq.draw(bgrSplit[1]);	//绘制图线	
      leastsq.direction(frame.cols/2, frame.rows/2, vector_x, vector_y);	//获取中心点到直线的向量
      cv::line(bgrSplit[1], cv::Point(frame.cols/2, frame.rows/2),
          cv::Point(frame.cols/2+vector_x, frame.rows/2+vector_y), cv::Scalar(255));	//以中心点为起点绘制该向量
      cv::merge(bgrSplit, frame);		//加入原图

    }
    x.clear(); //清除数据
    y.clear();
    cv::imshow("frame", frame);
    cv::waitKey(0);
  }
  return 0;
}

