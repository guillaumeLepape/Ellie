#include <iostream>

#include "../src/Factory/PolynomFactory.h"

int main()
{
    std::vector<Polynom> polynom = PolynomFactory::NewPolynom( 2, 3 );

    Eigen::Vector3d point0 = { 0,0,0 };
    Eigen::Vector3d point1 = { 1,0,0 };
    Eigen::Vector3d point2 = { 0,1,0 };

    Eigen::Vector3d point3 = { 1/3., 0, 0 };
    Eigen::Vector3d point4 = { 2/3., 0, 0 }; 

    Eigen::Vector3d point5 = { 2/3., 1/3., 0 };
    Eigen::Vector3d point6 = { 1/3., 2/3., 0 };

    Eigen::Vector3d point7 = { 0, 2/3., 0 };
    Eigen::Vector3d point8 = { 0, 1/3., 0 };
    
    Eigen::Vector3d point9 = { 1/3., 1/3., 0 };

    
    std::vector<Eigen::Vector3d> points;
    points.push_back(point0);
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
    points.push_back(point4);
    points.push_back(point5);
    points.push_back(point6);
    points.push_back(point7);
    points.push_back(point8);
    points.push_back(point9);    

    for ( int i = 0; i < polynom.size(); i++ )
    {
        for ( int j = 0; j < polynom.size(); j++)
        {
            std::cout << i << " " << j << " " << polynom[i]( points[j] ) << std::endl;
        }
    }


    return 0;
}