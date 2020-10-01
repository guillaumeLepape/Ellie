#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include <vector>

#include "FirstDegreePolynom.h"

//- Model product of polynom of degree 1 multiplied by a scalar lambda

class Polynom
{
    private:
        std::vector<FirstDegreePolynom> m_polynomProduct;
        double m_lambda;

    public:
        //- Define a product of polynom of degree 1 (polynom) multiplied by a scalar (lambda)
        Polynom( const std::vector<FirstDegreePolynom>& polynomProduct, const double& lambda = 1 );
        
        Polynom( const FirstDegreePolynom& firstDegreePolynom, const double& lambda = 1 );

        Polynom
        ( 
            const FirstDegreePolynom& FirstDegreePolynom1, 
            const FirstDegreePolynom& FirstDegreePolynom2,
            const double& lambda = 1
        );

        Polynom( const std::string& str, const double& lambda = 1 );
        Polynom( const std::string& str1, const std::string& str2, const double& lambda = 1 );

        //- Return the values of the polynom product at the coord point
        double operator()( const Eigen::Vector3d& coord ) const;
};

#endif // __POLYNOM_H__