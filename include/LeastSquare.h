#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <iostream>
/* 
 * clase name: LeastSquare
 * function: use leastsquare to fit line
 * input data: std::vector form of x and y coordinates of points to fit
 * output: print() give the equation
 *         draw(cv::Mat src) draw line on src image
 *         getX(), getY() predict point's x or y coordinate
 *         getNormalVector(...) give normal vector from a point to line
 */
class LeastSquare{  
    private:
    /* y=a*x+b | x=ah*y+bh */
    /* to prevent the a or ah being infinity */
    /* it will choose the more accurate expression */
    float a, b, ah, bh;
    /* direction vector (d_vector_x, d_vector_y) */
    float d_vector_x, d_vector_y;
    /* choice is y=kx+b or x=kx+b ?*/
	bool is_kxb;

    public:  
    /* use a list of x and y of the points to fit line */
    LeastSquare(const std::vector<int>& x, const std::vector<int>& y);
  
    float getY(const float x) const;
    
    float getX(const float y) const;
    
    //float error_plan1(const std::vector<int>& x, const std::vector<int>& y);
    
    //float error_plan2(const std::vector<int>& x, const std::vector<int>& y);

    void print() const;
    
	void draw(cv::Mat& src);
  
    /* get normal vector from origin point(x, y) to line  */
	void getNormalVector(float point_x, float point_y, float& n_vector_x, float& n_vector_y);
};
