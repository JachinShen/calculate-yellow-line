#include "LeastSquare.h"

LeastSquare::LeastSquare( const std::vector< int >& x,
    const std::vector< int >& y )  //构造函数，输入x，y坐标，得到斜率和截距
{
  float t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0;
  for ( int i = 0; i < ( int )x.size(); ++i )
  {
    t1 += x[i] * x[i];
    t2 += x[i];
    t3 += x[i] * y[i];
    t4 += y[i];
    t5 += y[i] * y[i];
  }
  a = ( t3 * x.size() - t2 * t4 ) / ( t1 * x.size() - t2 * t2 );
  b = ( t1 * t4 - t2 * t3 ) / ( t1 * x.size() - t2 * t2 );

  ah = ( t3 * x.size() - t2 * t4 ) / ( t5 * x.size() - t4 * t4 );
  bh = ( t5 * t2 - t4 * t3 ) / ( t5 * x.size() - t4 * t4 );

  is_kxb = abs( a ) < abs( ah );

  if ( is_kxb )
  {
    tx = -1;
    ty = -a;
  }
  else
  {
    tx = -ah;
    ty = -1;
  }
  float length = sqrt( tx * tx + ty * ty );
  tx = tx / length;
  ty = ty / length;
  if ( ( -tx - ty ) < 0 )
  {
    tx = -tx;
    ty = -ty;
  }
}

float LeastSquare::getY( const float x ) const  //计算函数值y=kx+b
{
  return a * x + b;
}

float LeastSquare::getX( const float y ) const  //计算x值 x=ah*y+bh
{
  return ah * y + bh;
}

float LeastSquare::error_plan1(
    const std::vector< int >& x,
    const std::vector< int >& y )  // y=kx+b方程误差计算（点到直线距离平方和）
{
  float error = 0.0;
  for ( int i = 0; i < ( int )x.size(); ++i )
  {
    error +=
      ( a * x[i] + b - y[i] ) * ( a * x[i] + b - y[i] ) / ( a * a + 1 );
  }
  return error;
}

float LeastSquare::error_plan2( const std::vector< int >& x,
    const std::vector< int >& y )  // x=ah*y+bh方程误差计算
{
  float error = 0.0;
  for ( int i = 0; i < ( int )x.size(); ++i )
  {
    error += ( ah * y[i] + bh - x[i] ) * ( ah * y[i] + bh - x[i] ) /
      ( ah * ah + 1 );
  }
  return error;
}

void LeastSquare::print() const  //显示直线方程
{
  if ( is_kxb )
    std::cout << "y = " << a << "x + " << b << "\n";
  else
    std::cout << "x = " << ah << "y + " << bh << "\n";
}

void LeastSquare::draw( cv::Mat& src )  //绘图
{
  uchar* data;
  if ( is_kxb )  //如果是y=kx+b误差较小
  {
    for ( int i = 0; i < src.cols; ++i )  //在原图上绘制结果
    {
      int j = ( int )getY( i );
      if ( j >= 0 && j <= src.rows )
      {
        data = src.ptr< uchar >( j );
        *( data + i ) = 255;
      }
    }
  }
  else  //如果是x=ah*y+bh误差较小
  {
    for ( int i = 0; i < src.rows; ++i )  //在原图上绘制结果
    {
      data = src.ptr< uchar >( i );
      int j = ( int )getX( i );
      if ( j >= 0 && j <= src.cols )
      {
        *( data + j ) = 255;
      }
    }
  }
}

void LeastSquare::direction( float x, float y, float& distance_x,
    float& distance_y )  //获取从点（x，y）到直线的向量
{
  if ( is_kxb )
  {
    distance_x = -a * ( a * x + b - y ) / ( a * a + 1 );
    distance_y = ( a * x + b - y ) / ( a * a + 1 );
  }
  else
  {
    distance_x = -( x - bh - ah * y ) / ( ah * ah + 1 );
    distance_y = ah * ( x - bh - ah * y ) / ( ah * ah + 1 );
  }
}
