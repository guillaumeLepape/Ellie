#ifndef __GAUSSPOINTSFACTORY_H__
#define __GAUSSPOINTSFACTORY_H__

#include <Eigen/Eigen>

//- Return the Gauss points matrix ( dimension x nbGaussPoints )

class GaussPointsFactory
{
    public:
        static Eigen::MatrixXd NewGaussPoints( const int& dimension, const int& orderMesh )
        {
            if ( dimension == 2 && orderMesh == 1 )
            {
                Eigen::MatrixXd gaussPoints( 3,1 );

                // First Gauss point 
                gaussPoints(0,0) = 1/3.;
                gaussPoints(1,0) = 1/3.;
                gaussPoints(2,0) = 0.;

                return gaussPoints;
            } 

            if ( dimension == 3 && orderMesh == 1 )
            {
                Eigen::MatrixXd gaussPoints( 3,1 );

                // First Gauss point
                gaussPoints(0,0) = 1/4.;
                gaussPoints(1,0) = 1/4.;
                gaussPoints(2,0) = 1/4.;

                return gaussPoints;
            }

            if ( dimension == 2 && orderMesh == 2 )
            {
                Eigen::MatrixXd gaussPoints( 3,3 );

                // First Gauss point
                gaussPoints(0,0) = 1/6.;
                gaussPoints(1,0) = 1/6.;
                gaussPoints(2,0) = 0.;

                // Second Gauss point
                gaussPoints(0,1) = 2/3.;
                gaussPoints(1,1) = 1/6.;
                gaussPoints(2,1) = 0.;

                // Third Gauss point
                gaussPoints(0,2) = 1/6.;
                gaussPoints(1,2) = 2/3.;
                gaussPoints(2,2) = 0.;

                return gaussPoints;
            }

            if ( dimension == 3 && orderMesh == 2 )
            {
                Eigen::MatrixXd gaussPoints( 3,4 );

                double alpha = 0.58541020;
                double beta = 0.13819660;

                // First Gauss point
                gaussPoints(0,0) = beta;
                gaussPoints(1,0) = beta;
                gaussPoints(2,0) = beta;

                // Second Gauss point
                gaussPoints(0,1) = alpha;
                gaussPoints(1,1) = beta;
                gaussPoints(2,1) = beta;

                // Third Gauss point
                gaussPoints(0,2) = beta;
                gaussPoints(1,2) = alpha;
                gaussPoints(2,2) = beta;

                // Forth Gauss point
                gaussPoints(0,3) = beta;
                gaussPoints(1,3) = beta;
                gaussPoints(2,3) = alpha;

                return gaussPoints;
            }

            // throw;
        }
};

#endif // __GAUSSPOINTSFACTORY_H__