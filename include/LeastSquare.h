#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <iostream>
/* 
 * clase name: LeastSquare
 * function: use leastsquare to fit line
 * input data: std::vector form of x and y coordinates of points to fit
 */
class LeastSquare{  
    private:
    /* y=kx+b | x=ky+b */
    /* to prevent the k being infinity */
    /* it will choose the more accurate expression */
    float k_x, b_x, k_y, b_y;
    /* direction vector (d_vector_x, d_vector_y) */
    float d_vector_x, d_vector_y;
    /* choice is y=kx+b or x=kx+b ?*/
	bool is_kxb;

    void calculateSlopeIntercept(const std::vector<int>& x, const std::vector<int>& y);

    void calculateDirectionVector();

    public:  
    /* use a list of x and y of the points to fit line */
    LeastSquare(const std::vector<int>& x, const std::vector<int>& y);
  
    float getY(const float x) const;
    
    float getX(const float y) const;
    
    //float error_plan1(const std::vector<int>& x, const std::vector<int>& y);
    
    //float error_plan2(const std::vector<int>& x, const std::vector<int>& y);

    void printEquation() const;
    
	void drawFitLine(cv::Mat& src);
  
    /* get normal vector from origin point(x, y) to line  */
	void getNormalVector(float point_x, float point_y, float& n_vector_x, float& n_vector_y);
};
