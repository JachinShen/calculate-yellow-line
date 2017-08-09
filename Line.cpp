#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
/*************************************************************************/
/*         提取黄色区域，拟合直线方程并给出中心点到直线的向量		     */
/*         以水平向右为x轴，竖直向下为y轴								 */
/*************************************************************************/
/*         最小二乘法类													*/
/*			输入坐标数组，得到两种直线方程y=kx+b, x=ky+b				*/
/*			根据两种方程的误差，选择较小的方程，并以此为之后计算的方程	*/
/*			计算中心点到直线的距离向量									*/
/************************************************************************/
class LeastSquare{  
    float a, b, ah, bh;  //斜率a, 截距b
	bool is_kxb;
public:  
    LeastSquare(const vector<int>& x, const vector<int>& y)  //构造函数，输入x，y坐标，得到斜率和截距
    {  
        float t1=0, t2=0, t3=0, t4=0, t5=0;  
        for(int i=0; i<(int)x.size(); ++i)  
        {  
            t1 += x[i]*x[i];  
            t2 += x[i];  
            t3 += x[i]*y[i];  
            t4 += y[i];  
			t5 += y[i]*y[i];
        }  
        a = (t3*x.size() - t2*t4) / (t1*x.size() - t2*t2);  
        //b = (t4 - a*t2) / x.size();  
        b = (t1*t4 - t2*t3) / (t1*x.size() - t2*t2);  
        
        //t1=0, t2=0, t3=0, t4=0;  
        /*for(int i=0; i<(int)x.size(); ++i)  
        {  
            t1 += y[i]*y[i];  
            t2 += y[i];  
            t3 += y[i]*x[i];  
            t4 += x[i];  
        }  */
        ah = (t3*x.size() - t2*t4) / (t5*x.size() - t4*t4);  
        //b = (t4 - a*t2) / x.size();  
        bh = (t5*t2 - t4*t3) / (t5*x.size() - t4*t4);  
		is_kxb = error_plan1(x,y)<error_plan2(x,y);	//比较误差，选择较小的方程
    }  
  
    float getY(const float x) const  //计算函数值y=kx+b
    {  
        return a*x + b;  
    }  
    
    float getX(const float y) const	//计算x值 x=ah*y+bh
    {
    	return ah*y + bh;
    }
    
    float error_plan1(const vector<int>& x, const vector<int>& y) //y=kx+b方程误差计算（点到直线距离平方和）
    {
    	float error = 0.0;
    	for(int i=0; i<(int)x.size(); ++i)
    	{
    		error += (a*x[i] + b - y[i])*(a*x[i] + b -y[i])/(a*a + 1);
    	}
    	return error;
    }
    
    float error_plan2(const vector<int>& x, const vector<int>& y) //x=ah*y+bh方程误差计算
    {
    	float error = 0.0;
    	for(int i=0; i<(int)x.size(); ++i)
    	{
    		error += (ah*y[i] + bh - x[i])*(ah*y[i] + bh -x[i])/(ah*ah + 1);
    	}
    	return error;
    }

	float getk(){ return a;}	//获取斜率
	
	float getb(){ return b;}	//获取截距
  
    void print() const  //显示直线方程
    {  
        cout<<"y = "<<a<<"x + "<<b<<"\n";
        cout<<"x = "<<ah<<"y + "<<bh<<"\n";
    }  

	void draw(Mat& src)	//绘图
	{
		if(is_kxb)	//如果是y=kx+b误差较小
		{
			for(int i=0; i<src.cols; ++i) //在原图上绘制结果
			{
				int j = (int)getY(i);
				if ( j >=0 && j<=src.rows)
				{
					uchar *data = src.ptr<uchar>(j);
					*(data+i) = 255;
				}
			}
		}
		else	//如果是x=ah*y+bh误差较小
		{
			for(int i=0; i<src.rows; ++i) //在原图上绘制结果
			{
				uchar *data = src.ptr<uchar>(i);
				int j = (int)getX(i);
				if ( j >=0 && j<=src.cols)
				{
					*(data+j) = 255;
				}
			}
		}
	}
  
	void direction(float x, float y, float& vector_x, float& vector_y)	//获取从点（x，y）到直线的向量
	{
		if(is_kxb)
		{
			vector_x = -a*(a*x+b-y)/(a*a+1);
			vector_y = (a*x+b-y)/(a*a+1);
		}
		else
		{
			vector_x = -(x-bh-ah*y)/(ah*ah+1);
			vector_y = ah*(x-bh-ah*y)/(ah*ah+1);
		}
	}
};

/************************************************************************************/
/*			函数名：get_Yellow_Region												*/
/*			功能：输入图像src，返回图像dst，黄色区域值为200,						*/
/*				其他区域根据满足条件多少，值分别为0, 50, 100, 150					*/
/*				便于显示直观图像调试												*/
/*				将最后一个参数if_debug赋1后，将通过颜色分别显示HSV三通道二值化结果	*/
/*				对应关系：蓝色对于H通道，绿色对应S通道，红色对应V通道				*/
/************************************************************************************/
void get_Yellow_Region(Mat& src, Mat& dst, int h_low=30, int h_high=75, int s_threshold=80, int v_threshold=80, bool if_debug=0)
{
	Mat hsv, Line_h1, Line_h2, Line_h, Line_sv;
	vector<Mat> hsvSplit;
	cvtColor(src, hsv, CV_BGR2HSV_FULL); //转换成HSV
	split(hsv, hsvSplit);	//分离出HSV通道，用于提取黄色区域
	threshold(hsvSplit[0], Line_h1, h_low, 255, THRESH_BINARY); //去除 H 小于 h_low 度的区域
	threshold(hsvSplit[0], Line_h2, h_high, 255, THRESH_BINARY_INV); //去除 H 大于 h_high 度的区域
	threshold(hsvSplit[1], hsvSplit[1], s_threshold, 255, THRESH_BINARY); //去除 S 小于 s_threshold 的区域
	threshold(hsvSplit[2], hsvSplit[2], v_threshold, 255, THRESH_BINARY); //去除 V 小于 v_threshold 的区域
	bitwise_and(Line_h1, Line_h2, Line_h);	
	bitwise_and(hsvSplit[1], hsvSplit[2], Line_sv);
	bitwise_and(Line_h, Line_sv, dst);	//矩阵相加, dst = Line_h1 + Line_h2 + hsvSplit[1] + hsvSplit[2]
	if(if_debug)
	{
		hsvSplit[0] = Line_h;
		merge(hsvSplit,hsv);
		imshow("debug", hsv);
		waitKey(1);
	}
}

int main()
{

	VideoCapture cap("line2.avi"); //获取视频
	Mat frame, img; //定义用到的Mat
	vector<Mat> bgrSplit;	//分离通道用到的Mat vector
	vector<int> x,y; //x,y坐标储存vector
	float vector_x,vector_y;
	namedWindow("frame", 1); 
	while(cap.read(frame))	//此函数读取图像并返回bool值，读取成功返回1
	{
		split(frame, bgrSplit);	//分离出BGR通道，为最终显示结果做准备
		get_Yellow_Region(frame, img, 29, 75, 75, 80, 1);
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
			line(bgrSplit[1], Point(frame.cols/2, frame.rows/2), Point(frame.cols/2+vector_x, frame.rows/2+vector_y), Scalar(255));	//以中心点为起点绘制该向量
			merge(bgrSplit, frame);		//加入原图
			
		}
		x.clear(); //清除数据
		y.clear();
		imshow("frame", frame);
		waitKey(0);
	}
    return 0;
}

