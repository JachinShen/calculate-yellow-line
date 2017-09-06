#include "LeastSquare.h"

LeastSquare::LeastSquare( const std::vector< int >& x,
        const std::vector< int >& y )
{
    calculateSlopeIntercept(x, y);
    
    calculateDirectionVector();
}

void LeastSquare::calculateSlopeIntercept(const std::vector<int>& x, const std::vector<int>& y)
{
    float t1 = 0.0, t2 = 0.0, t3 = 0.0, t4 = 0.0, t5 = 0.0;
    /* use formulas to calculate a,b,ah,bh */
    for ( int i = 0; i < (int)x.size(); ++i )
    {
        t1 += x[i] * x[i];
        t2 += x[i];
        t3 += x[i] * y[i];
        t4 += y[i];
        t5 += y[i] * y[i];
    }

    /* prevent a or ah being Nan*/
    if( (t1 * x.size() - t2 * t2) < 1e-6 )
    {
        is_kxb = false;
        k_y = 0;
        b_y = ( t5 * t2 - t4 * t3 ) / ( t5 * x.size() - t4 * t4 );
    }
    else
    {
        if( ( t5 * x.size() - t4 * t4 ) < 1e-6)
        {
            is_kxb = true;
            k_x = 0;
            b_x = ( t1 * t4 - t2 * t3 ) / ( t1 * x.size() - t2 * t2 );
        }
        else
        {
            k_x = ( t3 * x.size() - t2 * t4 ) / ( t1 * x.size() - t2 * t2 );
            b_x = ( t1 * t4 - t2 * t3 ) / ( t1 * x.size() - t2 * t2 );

            k_y = ( t3 * x.size() - t2 * t4 ) / ( t5 * x.size() - t4 * t4 );
            b_y = ( t5 * t2 - t4 * t3 ) / ( t5 * x.size() - t4 * t4 );

            /* because commonly a*ah = 1 */
            /* so choosing the small-abs one can express the line more accurately */
            is_kxb = abs( k_x ) < abs( k_y );
        }
    }

}

void LeastSquare::calculateDirectionVector()
{
    if ( is_kxb )
    {
        d_vector_x = -1;
        d_vector_y = -k_x;
    }
    else
    {
        d_vector_x = -k_y;
        d_vector_y = -1;
    }

    /* normalize */
    float length = sqrt( d_vector_x * d_vector_x + d_vector_y * d_vector_y );
    d_vector_x = d_vector_x / length;
    d_vector_y = d_vector_y / length;

    /* let direction vector point to left-up */
    /* by calculating the dot product with (-1, -1) */
    /* (in image coordinate (-1, -1) point to left_up) */
    if ( ( -d_vector_x - d_vector_y ) < 0 )
    {
        d_vector_x = -d_vector_x;
        d_vector_y = -d_vector_y;
    }

}

float LeastSquare::getY( const float x ) const
{
    return k_x * x + b_x;
}

float LeastSquare::getX( const float y ) const
{
    return k_y * y + b_y;
}

/*
   float LeastSquare::error_plan1(
   const std::vector< int >& x,
   const std::vector< int >& y )
   {
   float error = 0.0;
   for ( int i = 0; i < ( int )x.size(); ++i )
   {
   error +=
   ( a * x[i] + b - y[i] ) * ( a * x[i] + b - y[i] ) / ( a * a + 1 );
   }
   return error;
   }
   */

/*
   float LeastSquare::error_plan2( const std::vector< int >& x,
   const std::vector< int >& y )
   {
   float error = 0.0;
   for ( int i = 0; i < ( int )x.size(); ++i )
   {
   error += ( ah * y[i] + bh - x[i] ) * ( ah * y[i] + bh - x[i] ) /
   ( ah * ah + 1 );
   }
   return error;
   }
   */

void LeastSquare::printEquation() const
{
    if ( is_kxb )
        std::cout << "y = " << k_x << "x + " << b_x << "\n";
    else
        std::cout << "x = " << k_y << "y + " << b_y << "\n";
}

void LeastSquare::drawFitLine( cv::Mat& src )
{
    uchar* data;
    /* two cases , different independent value*/
    if ( is_kxb )
    {
        for ( int i = 0; i < src.cols; ++i )
        {
            int j = ( int )getY( i );
            if ( j >= 0 && j <= src.rows )
            {
                data = src.ptr< uchar >( j );
                *( data + i ) = 255;
            }
        }
    }
    else
    {
        for ( int i = 0; i < src.rows; ++i )
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

void LeastSquare::getNormalVector( float point_x, float point_y, float& n_vector_x,
        float& n_vector_y )
{
    if ( is_kxb )
    {
        n_vector_x = -k_x * ( k_x * point_x + b_x - point_y ) / ( k_x * k_x + 1 );
        n_vector_y = ( k_x * point_x + b_x - point_y ) / ( k_x * k_x + 1 );
    }
    else
    {
        n_vector_x = -( point_x - b_y - k_y * point_y ) / ( k_y * k_y + 1 );
        n_vector_y = k_y * ( point_x - b_y - k_y * point_y ) / ( k_y * k_y + 1 );
    }
}
