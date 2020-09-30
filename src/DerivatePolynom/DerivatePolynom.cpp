#include "DerivatePolynom.h"

DerivatePolynom::DerivatePolynom( const std::vector<Polynom>& derivatePolynom )
    : m_derivatePolynom( derivatePolynom )
{

}

DerivatePolynom::DerivatePolynom( const std::vector<std::string>& str )
    : m_derivatePolynom( { Polynom( str[0] ), Polynom( str[1] ), Polynom( str[2] ) } )
{}

double DerivatePolynom::operator()( const int& j, const Eigen::Vector3d& coord )
{
    return m_derivatePolynom[j](coord);  
}