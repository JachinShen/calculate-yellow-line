#define YELLOWLINE_DEBUG
#ifdef YELLOWLINE_DEBUG
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#endif
#include <vector>
#include <iostream>
class LeastSquare{  
    float a, b, ah, bh, tx, ty;  //斜率a, 截距b
	bool is_kxb;
public:  
    LeastSquare(const std::vector<int>& x, const std::vector<int>& y);
  
    float getY(const float x) const;
    
    float getX(const float y) const;
    
    float error_plan1(const std::vector<int>& x, const std::vector<int>& y);
    
    float error_plan2(const std::vector<int>& x, const std::vector<int>& y);

    void print() const;
    
#ifdef YELLOWLINE_DEBUG
	void draw(cv::Mat& src);
#endif
  
	void direction(float x, float y, float& vector_x, float& vector_y);
};
