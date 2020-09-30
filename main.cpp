// #include "src/EvaluationPolynom/EvaluationPolynom.h"
// #include "src/GaussPoints/GaussPointsFactory.h"

#include "src/Mesh/Mesh.h"

// #include "src/Mesh/Mesh_API.h"

#include <iostream>

int main()
{   
    Mesh mesh;

    mesh.ReadMesh( "Mesh_data/mesh2D_refine.msh" );

    std::cout << mesh << std::endl;

    return 0;
}