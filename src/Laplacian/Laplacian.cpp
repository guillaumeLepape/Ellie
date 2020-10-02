#include "Laplacian.h"
#include "../Weight/WeightFactory.h"
#include "../EvaluationPolynom/EvaluationPolynom.h"

#include "../GaussPoints/GaussPointsFactory.h"

#include "../Determinant/JacobianMatrix.h"

template<class Type>
Laplacian<Type>::Laplacian( const Field<Type>& field )
    : field_( field )
{
    int nDirichlet = 0;

    for ( int i = 0; i < field_.mesh().dirichletConditions().nbDirichlet(); i++ )
    {
        nDirichlet += field_.mesh().dirichletConditions().dirichletConditions()[i].size();
    }

    int size = field.mesh().internal().nbInternalIndex() - nDirichlet;
    lapMat_.resize( size, size );
    lapBC_.resize( size );
}

template<class Type>
void Laplacian<Type>::assemblyMatrix()
{
    int row,col;
    double valueMat;
    std::vector< Eigen::Triplet<double> > coefficientsMat;

    const Mesh& mesh = field_.mesh();

    //Initialization of the quadratura parameters
    const int& dimension = mesh.dimensions().dimension();
    const int& orderMesh = mesh.dimensions().orderMesh();

    Eigen::VectorXd omega = WeightFactory::NewWeight( dimension, orderMesh );

    std::vector<Eigen::MatrixXd> ReferenceDerivateReferencePolynom = EvaluationPolynom::NewDerivateReferencePolynom( dimension, orderMesh);
    
    // for (  auto i = ReferenceDerivateReferencePolynom.cbegin(); i != ReferenceDerivateReferencePolynom.cend(); ++i)
    // {
    //     std::cout << *i << std::endl;
    // }
    // std::cout << ReferenceDerivateReferencePolynom << std::endl;
    const std::vector<double>& determinant = mesh.internal().determinant();
    const std::vector<double>& invertDeterminant = mesh.internal().invertDeterminant();

    const Eigen::VectorXi& partition = mesh.partition().partition();

    const std::vector<std::vector<int>>& internal = mesh.internal().indexInternalField();

    // Eigen::VectorXd vect1,vect2;
    // vect1.resize(_dimension); vect2.resize(_dimension);

    // Eigen::MatrixXd ReferencePolynomialMatrix, ReferenceDerivatedPolynomialMatrix;

    // ReferencePolynomialMatrix = _pol.ReferencePolynomialMatrix(gaussPoints);
    // ReferenceDerivatedPolynomialMatrix = _pol.ReferenceDerivatedPolynomialMatrix(gaussPoints);

    // _nb_second_member_Dirichlet = 0;
    // _second_member_Dirichlet_temp.resize(_nb_second_member_Dirichlet);
    // _second_member_f_temp.resize(_nb_second_member_Dirichlet);

    // _second_member_index.resize(_nb_second_member_Dirichlet,3);

    const int& nbVertex = mesh.internal().indexInternalField()[0].size();
    Eigen::MatrixXd coord(dimension, nbVertex);

    for (int i = 0; i < mesh.internal().nbInternalIndex(); i++)
    {
        for (int j = 0; j < coord.rows(); j++)
        {
            for (int k = 0; k < coord.cols(); k++)
            {
                coord(j,k) =  mesh.nodes().valueNodes()( mesh.internal().indexInternalField()[i][k]-1, j );
            }
        }

        Eigen::MatrixXd jacobianMatrix = JacobianMatrix::ComputeJacobianMatrix(dimension, coord, invertDeterminant[i]);

        for ( int j = 0; j < ReferenceDerivateReferencePolynom.size(); j++ )
        {
            for ( int k = 0; k < ReferenceDerivateReferencePolynom.size(); k++ )
            {
                if ( partition(internal[i][j] - 1) == 0 && partition(internal[i][k] - 1) == 0)
                {

                }
                else if ( partition(internal[i][k] - 1) == 0 )
                {

                }
                else if ( partition(internal[i][j] - 1) == 0 )
                {

                }
                else if ( partition(internal[i][j] - 1) != 0 && partition(internal[i][k] - 1) != 0 )
                {
                    row = partition(internal[i][j] - 1) - 1;
                    col = partition(internal[i][k] - 1) - 1;

                    valueMat = 0.;

                    

                    for (int l = 0; l < omega.size(); l++)
                    {
                        // for (int n = 0; n < dimension; n++)
                        // {
                        //     vect1(n) = ReferenceDerivatedPolynomialMatrix(j,_dimension*l+n);
                        //     vect2(n) = ReferenceDerivatedPolynomialMatrix(k,_dimension*l+n);
                        // }        

                        valueMat += 0.5*omega(l)*determinant[i]*
                            (jacobianMatrix * ReferenceDerivateReferencePolynom[j].col(l))
                        .dot(jacobianMatrix * ReferenceDerivateReferencePolynom[k].col(l));
                    }

                    coefficientsMat.push_back(Eigen::Triplet<double>(row,col,valueMat));
                }
                else
                {
                    throw;
                }

            }
        }

    //     //Computation of the local matrices
    //     for (int j = 0; j < _nb_polynom_tri; j++)
    //     {
    //         for (int k = 0; k < _nb_polynom_tri; k++)
    //         {

    //             if ( _partition_vect(_elements(i,j)) == -1 && _partition_vect(_elements(i,k)) == -1 )
    //             {}
    //             else if ( _partition_vect(_elements(i,k)) == -1)
    //             {
    //                 _nb_second_member_Dirichlet++;

    //                 _second_member_Dirichlet_temp.conservativeResize(_nb_second_member_Dirichlet);
    //                 _second_member_f_temp.conservativeResize(_nb_second_member_Dirichlet);
    //                 _second_member_index.conservativeResize(_nb_second_member_Dirichlet,3);

    //                 _second_member_Dirichlet_temp( _nb_second_member_Dirichlet - 1) = 0.;
    //                 _second_member_f_temp( _nb_second_member_Dirichlet - 1 ) = 0.;


    //                 for (int l = 0; l < _nb_gauss_points_elements; l++)
    //                 {

    //                     for (int n = 0; n < _dimension; n++)
    //                     {
    //                         vect1(n) = ReferenceDerivatedPolynomialMatrix(j,_dimension*l+n);
    //                         vect2(n) = ReferenceDerivatedPolynomialMatrix(k,_dimension*l+n);
    //                     }

    //                     _second_member_Dirichlet_temp( _nb_second_member_Dirichlet - 1 ) -= 0.5*omega(l)*determinant*(_jacobianMatrixInvert*vect1).dot(_jacobianMatrixInvert*vect2);//*_fonc.DirichletBoundaryCondition( Vector_node(_elements(i,k)) );

    //                     _second_member_f_temp( _nb_second_member_Dirichlet - 1 ) += 0.5*omega(l)*determinant*ReferencePolynomialMatrix(j,l)*ReferencePolynomialMatrix(k,l);//*_fonc.f( Vector_node(_elements(i,k)) );
    //                 }

    //                 _second_member_index( _nb_second_member_Dirichlet - 1,0 ) = i;
    //                 _second_member_index( _nb_second_member_Dirichlet - 1,1 ) = j;
    //                 _second_member_index( _nb_second_member_Dirichlet - 1,2 ) = k;

    //             }
    //             else if (_partition_vect(_elements(i,j)) == -1)
    //             {}
    //             else if ( _partition_vect(_elements(i,j)) != -1 && _partition_vect(_elements(i,k)) != -1 )
    //             {
    //                 row = _partition_vect(_elements(i,j));
    //                 col = _partition_vect(_elements(i,k));

    //                 value_K = 0.;
    //                 value_M = 0.;

    //                 for (int l = 0; l < _nb_gauss_points_elements; l++)
    //                 {

    //                     for (int n = 0; n < _dimension; n++)
    //                     {
    //                         vect1(n) = ReferenceDerivatedPolynomialMatrix(j,_dimension*l+n);
    //                         vect2(n) = ReferenceDerivatedPolynomialMatrix(k,_dimension*l+n);
    //                     }        

    //                     value_K += 0.5*omega(l)*determinant*(_jacobianMatrixInvert*vect1).dot(_jacobianMatrixInvert*vect2);
    //                     value_M += 0.5*omega(l)*determinant*ReferencePolynomialMatrix(j,l)*ReferencePolynomialMatrix(k,l);

    //                 }

    //                 coefficients_K.push_back(Eigen::Triplet<double> (row,col,value_K));
    //                 coefficients_M.push_back(Eigen::Triplet<double> (row,col,value_M));
    //             }
    //             else
    //                 abort();


    //         }
    //     }
    }

    for ( int i = 0; i < coefficientsMat.size(); i++ )
    {
        std::cout << coefficientsMat[i].col() << " " 
              << coefficientsMat[i].row() << " " 
              << coefficientsMat[i].value() << std::endl;
              std::cout << std::endl;
    }

    lapMat_.setFromTriplets( coefficientsMat.begin(), coefficientsMat.end() );
    // _global_mass_matrix.setFromTriplets(coefficients_M.begin(), coefficients_M.end());

    // std::cout << lapMat_ << std::endl;

    lapMat_.makeCompressed();
    // _global_mass_matrix.makeCompressed();
}

template class Laplacian<double>;
template class Laplacian<Eigen::Vector2d>;
template class Laplacian<Eigen::Vector3d>;