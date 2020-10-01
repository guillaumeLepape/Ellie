#ifndef __FIRSTDEGREEPOLYNOM_H__
#define __FIRSTDEGREEPOLYNOM_H__

#include <string>

#include <Eigen/Core>

//- Model a polynom of degree 1 in 2d or 3d
//- In 2D : P = lambda( a + b x + c y )
//- In 3D : P = lambda( a + b x + c y + d z )

class FirstDegreePolynom 
{
    private:
        //- The lambda scalar
        double m_lambda;
        
        //- The m_coeff attribute is the coeff of the polynom
        Eigen::Vector4i m_coeff;

    public:
        //- Define a polynom of degree 1 by using 4 coefficients of the polynom
        FirstDegreePolynom( const int& a, const int& b, const int& c, const int& d, const double& lambda = 1 );

        //- Same constructor but using a Eigen::Vector instead of 4 int
        // FirstDegreePolynom( const std::vector<int>& coeff, const double& lambda = 1 );
        FirstDegreePolynom( const Eigen::Vector4i& coeff, const double& lambda = 1 );

        //- Define first or zero degree polynom from the string expresion of the polynom
        //- For example, if the polynom1 = "2 - x + 9y + z", the m_coeff attribute is equal 
        //- to { 2, -1, 9, 1 }
        //- By default, m_lambda = 1 
        FirstDegreePolynom( const std::string polynom1 );

        //- Return the values of the polynom at the coord point
        double operator()( const Eigen::Vector3d& coord ) const;

        //- Accessor for the lambda scalar
        const double& lambda() const { return m_lambda; }

};

#endif // __FIRSTDEGREEPOLYNOM_H__