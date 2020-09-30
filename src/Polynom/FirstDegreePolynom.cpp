#include "FirstDegreePolynom.h"

#include <boost/algorithm/string.hpp>
#include <iostream>

FirstDegreePolynom::FirstDegreePolynom( const int& a, const int& b, const int& c, const int& d, const double& lambda )
    : m_coeff( {a, b, c, d} ), m_lambda( lambda )
{}

FirstDegreePolynom::FirstDegreePolynom( const Eigen::Vector4i& coeff, const double& lambda )
    : m_coeff( {coeff(0), coeff(1), coeff(2), coeff(3)} ), m_lambda( lambda )
{}

// FirstDegreePolynom::FirstDegreePolynom( const std::vector<int>& coeff, const double& lambda )
    // : m_coeff( coeff ), m_lambda( lambda )
// {}

FirstDegreePolynom::FirstDegreePolynom( const std::string polynom1 )
    : m_coeff(4)
{
    std::string polynom = polynom1;
    // std::cout << polynom << std::endl;

    polynom.erase(std::remove(polynom.begin(), polynom.end(), ' '), polynom.end());

    std::vector<bool> presence_monome(4,false);

    for ( int i = 0; i < polynom.size(); i++ )
    {
        if ( polynom[i] == 'x' )
        {
            presence_monome[1] = true;
        }
        else if ( polynom[i] == 'y' )
        {
            presence_monome[2] = true;
        }
        else if ( polynom[i] == 'z' )
        {
            presence_monome[3] = true;
        }
    }


    std::deque<std::string> result;
    std::stringstream ss(polynom);
    std::string sousChaine;
    char delimiter = '+';

    while ( std::getline(ss, sousChaine, delimiter) )
    {
        result.push_back(sousChaine);
    }

    std::deque<std::string> result1;

    for (int i = 0; i < result.size(); i++)
    {
        std::string substr = result[i];
        std::stringstream io( substr );
        std::string sousChaine1;

        char delimiter1 = '-';

        int k = 0;

        while ( std::getline(io, sousChaine1, delimiter1) )
        {
            if ( k == 0 )
            {
                result1.push_back( sousChaine1 );
            }
            else
            {
                result1.push_back( "-" + sousChaine1 );
            }
            k++;
        }
    }


    if ( result1[0].empty() )
    {
        result1.pop_front();
    }

    presence_monome[0] = result1.size() - int(presence_monome[1]) - int(presence_monome[2]) - int(presence_monome[3]);

    // std::cout << " Size " << std::endl;
    // std::cout << result1.size() << std::endl;
    // std::cout << std::endl;


    // std::cout << " Presence " << std::endl;
    // for (int i = 0; i < presence_monome.size(); i++)
    // {
    //     std::cout << presence_monome[i] << std::endl;
    // }
    // std::cout << std::endl;

    int k = 0;

    for ( int i = 0; i < 4; i++ )
    {
        if ( !(presence_monome[i]) )
        {
            m_coeff[i] = 0;
        }
        else
        {
            if ( result1[k] == "x" || result1[k] == "y" || result1[k] == "z" )
            {
                m_coeff[i] = 1;
            }
            else if ( result1[k] == "-x" || result1[k] == "-y" || result1[k] == "-z" )
            {
                m_coeff[i] = -1;
            }
            else
            {
                if ( i == 0 )
                {
                    m_coeff[i] = std::stoi( result1[k] ); 
                }
                else
                {
                    m_coeff[i] = std::stoi( result1[k].substr(0,result1[k].size() - 1) ); 
                }
            }
            k++;
        }
    }
        
    m_lambda = 1;
    // std::cout << " Coeff " << std::endl;
    // for ( int i = 0; i < m_coeff.size(); i++ )
    // {
    //     std::cout << m_coeff[i] << std::endl;
    // }

    // std::cout << std::endl;
    // std::cout << std::endl;
}

double FirstDegreePolynom::operator()( const Eigen::Vector3d& coord ) const
{
    return m_lambda*( m_coeff[0] + m_coeff[1]*coord(0) + m_coeff[2]*coord(1) + m_coeff[3]*coord(2) );
}
