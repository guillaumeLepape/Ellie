// #include "src/EvaluationPolynom/EvaluationPolynom.h"
// #include "src/GaussPoints/GaussPointsFactory.h"

#include <iostream>

#include "src/Mesh/Mesh/Mesh.h"
#include "src/Field/Field.h"
#include "src/Laplacian/Laplacian.h"

int main()
{   
    Mesh mesh;

    mesh.ReadMesh( "Mesh_data/mesh2D.msh" );

    // std::cout << mesh << std::endl;

    // Field<double> p( mesh, "p", 1 );

    // p.write();


    // Field<Eigen::Vector2d> u( mesh, "u", {1,2} );

    // u.write();

    // Field<Eigen::Vector3d> u3D( mesh, "u3D", {1,5,4} );
    // u3D.write();

    // Laplacian<Eigen::Vector2d> lap( u );

    // lap.assemblyMatrix();

    // Eigen::ConjugateGradient< Eigen::SparseMatrix<double>, Eigen::Lower|Eigen::Upper> solver;

    // solver.compute(lap.mat());

    // Eigen::SparseVector<double> secondMember( lap.mat().cols() );

    // Eigen::VectorXd solution = solver.solve(secondMember);

    // std::cout << solution << std::endl;

    Field<Eigen::Vector3d> u1( mesh, "u1", {1,5,-9} );
    Field<Eigen::Vector3d> u2( mesh, "u2", {-2,8,5} );

    Field<Eigen::Vector3d> u = u1 + u2;

    u.write();

    return 0;
}