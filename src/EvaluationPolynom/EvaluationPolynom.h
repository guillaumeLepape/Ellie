#ifndef __EVALUATIONPOLYNOM_H__
#define __EVALUATIONPOLYNOM_H__

#include <iostream>

#include "../Factory/PolynomFactory.h"
#include "../Factory/DerivatePolynomFactory.h"

#include "../GaussPoints/GaussPointsFactory.h"

class EvaluationPolynom
{
    public:
        static Eigen::MatrixXd NewReferencePolynom
        ( 
            const int& dimension, 
            const int& orderMesh 
        )
        {   
            std::vector<Polynom> polynom = PolynomFactory::NewPolynom( dimension, orderMesh );

            Eigen::MatrixXd gaussPoints = GaussPointsFactory::NewGaussPoints( dimension, orderMesh );

            // Size of result is nb_polynom_tri x nbGaussPoints
            Eigen::MatrixXd result(gaussPoints.cols(), polynom.size());

            for ( int i = 0; i < result.rows(); i++ )
            {
                for ( int j = 0; j < result.cols(); j++ )
                {
                    result(i,j) = polynom[j]( gaussPoints.col(i) );
                }
            }

            return result;
        }

        static std::vector<Eigen::MatrixXd> NewDerivateReferencePolynom
        (
            const int& dimension,
            const int& orderMesh
        )
        {
            std::vector<DerivatePolynom> derivatePolynom = DerivatePolynomFactory::NewDerivatePolynom( dimension, orderMesh );

            Eigen::MatrixXd gaussPoints = GaussPointsFactory::NewGaussPoints( dimension, orderMesh );

            // Size of the result is nb_polynom_tri x ( dimension*nbGaussPoints )
            std::vector<Eigen::MatrixXd> result( derivatePolynom.size(), Eigen::MatrixXd(dimension, gaussPoints.cols() ) );
            // Eigen::MatrixXd result( dimension,  derivatePolynom.size()*gaussPoints.cols() );

            for ( int i = 0; i < result.size(); i++ )
            {
                for ( int j = 0; j < result[i].rows(); j++ )
                {
                    for ( int k = 0; k < result[i].cols(); k++)
                    {
                        result[i](j, k) = derivatePolynom[i]( j, gaussPoints.col(k) );
                    } 
                }
            }

            return result;
        }
};

#endif // __EVALUATIONPOLYNOM_H__