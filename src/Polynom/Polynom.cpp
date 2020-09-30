#include "Polynom.h"

Polynom::Polynom( const std::vector<FirstDegreePolynom>& polynomProduct, const double& lambda )
    : m_polynomProduct( polynomProduct ), m_lambda( lambda )
{}

Polynom::Polynom( const FirstDegreePolynom& firstDegreePolynom, const double& lambda )
    : m_polynomProduct( 1, firstDegreePolynom ), m_lambda( lambda * firstDegreePolynom.lambda() )
{}

Polynom::Polynom
(
    const FirstDegreePolynom& firstDegreePolynom1,
    const FirstDegreePolynom& firstDegreePolynom2,
    const double& lambda
)
    : m_polynomProduct( { firstDegreePolynom1, firstDegreePolynom2 } ), 
      m_lambda( lambda * firstDegreePolynom1.lambda() * firstDegreePolynom2.lambda() )
{}

Polynom::Polynom( const std::string& str, const double& lambda )
    : m_polynomProduct( { FirstDegreePolynom(str) } ), m_lambda( lambda )
{}

Polynom::Polynom
(
    const std::string& str1,
    const std::string& str2,
    const double& lambda
)
    : m_polynomProduct( { FirstDegreePolynom(str1), FirstDegreePolynom(str2) } ), m_lambda( lambda )
{}

double Polynom::operator()( const Eigen::Vector3d& coord ) const
{
    double result = 1;

    for ( auto firstDegreePolynom = m_polynomProduct.cbegin(); firstDegreePolynom != m_polynomProduct.cend(); firstDegreePolynom++ )
    {
        result *= (*firstDegreePolynom)( coord );
    }

    return m_lambda*result;
}