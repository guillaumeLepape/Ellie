#ifndef __JACOBIANMATRIX_H__
#define __JACOBIANMATRIX_H__

#include <Eigen/Eigen>

class JacobianMatrix
{
    public:

        //- dimension of the problem (2 or 3), coord of the element (tri)
        static Eigen::MatrixXd ComputeJacobianMatrix( const int& dimension, const Eigen::MatrixXd& coord,const double& invert_determinant)
        {   
            if ( dimension == 2 )
            {
                const double& x1 = coord(0,0);
                const double& y1 = coord(1,0);

                const double& x2 = coord(1,0);
                const double& y2 = coord(1,1);

                const double& x3 = coord(2,0);
                const double& y3 = coord(2,1);

                Eigen::Matrix2d jacobianMatrix;

                jacobianMatrix(0,0) = y3 - y1;
                jacobianMatrix(1,0) = -(y2 - y1);
                jacobianMatrix(0,1) = -(x3 - x1);
                jacobianMatrix(1,1) = x2 - x1;

                return invert_determinant*jacobianMatrix.transpose();
            }
            if ( dimension == 3 )
            {
                const double& x1 = coord(0,0);
                const double& x2 = coord(1,0);
                const double& x3 = coord(2,0);
                const double& x4 = coord(3,0);
                const double& y1 = coord(0,1);
                const double& y2 = coord(1,1);
                const double& y3 = coord(2,1);
                const double& y4 = coord(3,1);
                const double& z1 = coord(0,2);
                const double& z2 = coord(1,2);
                const double& z3 = coord(2,2);
                const double& z4 = coord(3,2);

                double a,b,c,d,e,f,g,h,i;

                a = x2 - x1;
                b = x3 - x1;
                c = x4 - x1;
                d = y2 - y1;
                e = y3 - y1;
                f = y4 - y1;
                g = z2 - z1;
                h = z3 - z1;
                i = z4 - z1;

                Eigen::Matrix3d jacobianMatrix;

                jacobianMatrix(0,0) = e*i - f*h;
                jacobianMatrix(1,0) = f*g - d*i;
                jacobianMatrix(2,0) = d*h - e*g;
                jacobianMatrix(0,1) = c*h - b*i;
                jacobianMatrix(1,1) = a*i - c*g;
                jacobianMatrix(2,1) = b*g - a*h;
                jacobianMatrix(0,2) = b*f - c*e;
                jacobianMatrix(1,2) = c*d - a*f;
                jacobianMatrix(2,2) = a*e - b*d;

                return invert_determinant*jacobianMatrix.transpose();
            }
            // throw;
        }
};

#endif // __JACOBIANMATRIX_H__