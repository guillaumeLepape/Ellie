#ifndef __WEIGHTFACTORY_H__
#define __WEIGHTFACTORY_H__

#include <Eigen/Core>

//- Return the quadrature weights depending on the dimension of the problem (2 or 3)
//- and the order of the mesh (1 or 2)

class WeightFactory
{
    public:
        static Eigen::VectorXd NewWeight( const int& dimension, const int& orderMesh )
        {
            if ( dimension == 2 && orderMesh == 1 ) 
            {
                Eigen::VectorXd vect(1);
                vect(0) = 1.;
                return vect;
            }
        
            if ( dimension == 3 && orderMesh == 1 )
            {
                Eigen::VectorXd vect(1);
                vect(0) = 1.;
                return vect;
            }

            if ( dimension == 2 && orderMesh == 2 )
            {
                Eigen::VectorXd vect(3);
                vect(0) = 1/3.; vect(1) = 1/3.; vect(2) = 1/3.;
                return vect;                
            }
            
            if ( dimension == 3 && orderMesh == 2 )
            {
                Eigen::VectorXd vect(4);
                vect(0) = 1/4.; vect(1) = 1/4.; vect(2) = 1/4.; vect(3) = 1/4.;
                return vect;
            }

            // throw;
        }
};

#endif // __WEIGHTFACTORY_H__