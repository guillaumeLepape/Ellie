#include "Mesh.h"

#include <fstream>
#include <iostream>


// Constructor
Mesh::Mesh()
{}

void Mesh::ReadMesh(const std::string& name_mesh)
{
    // Open flux for mesh
    std::ifstream mesh_file(name_mesh.data());

    // Check if the mesh can be opened
    // If not (for example, the mesh file name can incorrect) stop the execution
    if (!mesh_file.is_open())
    {
        std::cout << "Unable to open file " << name_mesh << std::endl;
        throw;
    }
    else
    {
        std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "Reading mesh: " << name_mesh << std::endl;
    }

    // Declare the string line to read the mesh
    std::string file_line;

    // Read mesh file from the beginning to the end
    while (!mesh_file.eof())
    {
        std::getline(mesh_file, file_line);

        // Read the version of the mesh used
        if (file_line.find("$MeshFormat") != std::string::npos)
        {
            // 2.2 0 8
        }

        if (file_line.find("$PhysicalNames") != std::string::npos)
        {
            physicalNames_.Read_PhysicalNames( mesh_file );
        }

        if (file_line.find("$Nodes") != std::string::npos)
        {
            nodes_.Read_nodes( mesh_file );
        }

        if (file_line.find("$Elements") != std::string::npos)
        {
            Element elements;
            elements.Read_elements( mesh_file );

            dimensions_.affectDimensions( elements );

            internal_.affectInternalField( physicalNames_, elements );
            internal_.computeInternalArea( dimensions_ , nodes_ );
            internal_.computeDeterminant( dimensions_, nodes_ );

            dirichletConditions_.affectDirichletConditions( physicalNames_, elements );
            partition_.setPartition( nodes_, dirichletConditions_ );
            neumannConditions_.affect_NeumannConditions( physicalNames_, elements );

        }
    }

}


// void Mesh::Partition()
// {
//     partitionVect_.setConstant(nodes_.nbNode(), 1);
    
//     for ( int i = 0; i < dirichletConditions_.nbDirichlet(); i++ )
//     {
//         for ( int j = 0; j < dirichletConditions_.dirichletConditions()[i].size(); j++ )
//         {
//             partitionVect_[dirichletConditions_.dirichletConditions()[i][j] - 1] = 0;
//         }
//     }

//     int k = 1;

//     for (int i = 0; i < nodes_.nbNode(); i++)
//     {
//         if (partitionVect_(i) == 1)
//         {
//             partitionVect_(i) = k;
//             k += 1;
//         }
//     }

// }


std::ostream& operator<<( std::ostream& os, const Mesh& mesh )
{
    os << mesh.nodes_;

    os << mesh.internal_;

    os << mesh.dirichletConditions_;
    os << mesh.neumannConditions_;

    return os;
}