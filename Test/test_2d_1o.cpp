#include <iostream>

#include "../src/Factory/PolynomFactory.h"

int main()
{
    std::vector<Polynom> polynom = PolynomFactory::NewPolynom( 2, 1 );

    Eigen::Vector3d point0 = { 0,0,0 };
    Eigen::Vector3d point1 = { 1,0,0 };
    Eigen::Vector3d point2 = { 0,1,0 };

    std::vector<Eigen::Vector3d> points;
    points.push_back(point0);
    points.push_back(point1);
    points.push_back(point2);  

    for ( int i = 0; i < polynom.size(); i++ )
    {
        for ( int j = 0; j < polynom.size(); j++)
        {
            std::cout << i << " " << j << " " << polynom[i]( points[j] ) << std::endl;
        }
    }


    return 0;
}