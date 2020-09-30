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

        // // I build a board, _boundary_reference with the physical_tag that is a integer related to the position of the boundary element
        // // and int_name that is a integer related to the type of boundaty condition ( 1 for Dirichlet and 2 for Neumann )
        // if (file_line.find("$PhysicalNames") != std::string::npos)
        // {
        //     int number_of_names;
        //     mesh_file >> number_of_names;

        //     switch (number_of_names)
        //     {
        //     case 2:
        //     {
        //         int physical_dimension, physical_tag;
        //         std::string physical_name;
        //         int int_name;
        //         mesh_file >> physical_dimension >> physical_tag >> physical_name;
        //         EraseOneCharacter(physical_name,'/"');
        //         if (physical_name.compare("Dirichlet") == 0) //If it is a Dirichlet condition, physical_name=1. Else, it's 2.
        //             int_name = 1;
        //         else
        //             int_name = 2;

        //         _boundary_reference.resize(1,2);
        //         _boundary_reference(0,0) = physical_tag;
        //         _boundary_reference(0,1) = int_name;

        //         break;
        //     }
        //     case 3:
        //     {
        //         int physical_dimension_1; int physical_tag_1; std::string physical_name_1;
        //         int physical_dimension_2; int physical_tag_2; std::string physical_name_2;
        //         int int_name_1, int_name_2;
        //         mesh_file >> physical_dimension_1 >> physical_tag_1 >> physical_name_1;
        //         mesh_file >> physical_dimension_2 >> physical_tag_2 >> physical_name_2;

        //         EraseOneCharacter(physical_name_1,'/"');
        //         EraseOneCharacter(physical_name_2,'/"');
        //         if (physical_name_1 == "Dirichlet") //If it is a Dirichlet condition, physical_name_1=1. Else, it's 2.
        //             int_name_1 = 1;
        //         else
        //             int_name_1 = 2;

        //         if (physical_name_2 == "Dirichlet") //If it is a Dirichlet condition, physical_name_2=1. Else, it's 2.
        //             int_name_2 = 1;
        //         else
        //             int_name_2 = 2;

        //         _boundary_reference.resize(2,2);
        //         _boundary_reference(0,0) = physical_tag_1;
        //         _boundary_reference(0,1) = int_name_1;
        //         _boundary_reference(1,0) = physical_tag_2;
        //         _boundary_reference(1,1) = int_name_2;

        //         break;
        //     }
        //     default :
        //         abort();
        //     }

        // }



        if (file_line.find("$Nodes") != std::string::npos)
        {
            // mesh_file >> _nb_nodes;
            // _nodes.resize(_nb_nodes,3);

            // for (int i = 0 ; i < _nb_nodes ; i++)
            // {
            //     double x,y,z; int ref;
            //     mesh_file >> ref >> x >> y >> z;
            //     _nodes(i,0) = x;
            //     _nodes(i,1) = y;
            //     _nodes(i,2) = z;
            // }

            nodes_.Read_nodes( mesh_file );
        }

        // std::cout << nodes_.valueNodes() << std::endl;

        if (file_line.find("$Elements") != std::string::npos)
        {
            Element elements;
            elements.Read_elements( mesh_file );

            dimensions_.affectDimensions( elements );

            internal_.affectInternalField( physicalNames_, elements );

            dirichletConditions_.affectDirichletConditions( physicalNames_, elements );
            neumannConditions_.affect_NeumannConditions( physicalNames_, elements );

            // dirichletConditions_.resize(1);

            // dirichletConditions_[0].affectDirichletConditions( 2, elements_ );

            // int nb_elements;
            // mesh_file >> nb_elements;

            // _nb_dirichlet = 0;
            // _nb_neumann = 0;
            // _nb_elements = 0;

            // int ref,nb_of_tag,tag_1,tag_2;
            // int elm_type;

            // _edges.resize(0);


            // mesh_file >> ref >> elm_type >> nb_of_tag;

            // Resizing(elm_type);
            // _DirichletConditions.resize(3*nb_elements);
            // _NeumannConditions.resize(nb_elements,_nb_col_neumann);
            // _elements.resize(nb_elements,_nb_col_element);
            // _element_area.resize(nb_elements);
            // _determinant.resize(nb_elements);
            // _invert_determinant.resize(nb_elements);


            // for (int i = 0; i < nb_elements ; i++)
            // {
            //     if (i != 0)
            //         mesh_file >> ref >> elm_type >> nb_of_tag;

            //     mesh_file >> tag_1;
            //     mesh_file >> tag_2;

            //     // From the Gmsh documentation
            //     // elememt type
            //     // 1  : 2-node line
            //     // 2  : 3-node triangle
            //     // 4  : 4-node tetrahedron
            //     // 8  : 3-node second order line (2 nodes associated with the vertices and 1 with the edge)
            //     // 9  : 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges)
            //     // 11 : 10-node second order tetrahedron (4 nodes associated with the vertices and 6 with the edges)


            //     if (elm_type == _elm_type_boundary)
            //     {
            //         Eigen::VectorXi ref_node_boundary(_nb_col_neumann);

            //         for (int j = 0; j < _nb_col_neumann; j++)
            //         {
            //             mesh_file >> ref_node_boundary(j);
            //             ref_node_boundary(j) = ref_node_boundary(j) - 1;
            //         }

            //         for (int k = 0; k < _boundary_reference.rows(); k++)
            //         {

            //             if ( _boundary_reference(k,0) == tag_1)
            //             {
            //                 // Dirichlet Condition
            //                 if (_boundary_reference(k,1) == 1)
            //                 {
            //                     Dirichlet(ref_node_boundary,k);
            //                 }

            //                 // Neumann Condition
            //                 else if (_boundary_reference(k,1) == 2)
            //                 {
            //                     Neumann(ref_node_boundary,k);
            //                 }

            //                 else
            //                     abort();
            //             }
            //         }
            //     }
            //     else if (elm_type == _elm_type_element)
            //     {
            //         Eigen::VectorXi ref_node_element(_nb_col_element);

            //         for (int j = 0; j < _nb_col_element; j++)
            //         {
            //             mesh_file >> ref_node_element(j);
            //             ref_node_element(j) = ref_node_element(j) - 1;
            //         }

            //         Edge(ref_node_element.head(_nb_vertex));

            //         Element(ref_node_element);

            //     }
            //     else
            //         abort();
            // }

        }
    }


    // _elements.conservativeResize(_nb_elements,_nb_col_element);
    // _NeumannConditions.conservativeResize(_nb_neumann,_nb_col_neumann);
    // _NeumannLength.resize(_nb_neumann,_nb_col_neumann_length);
    // _NeumannNormal.resize(_nb_neumann,_nb_col_neumann_normal);


    // _element_area.conservativeResize(_nb_elements);
    // _DirichletConditions.conservativeResize(_nb_dirichlet);

    // _lc = 0.;

    // for (int i = 1; i < _edges.size(); i++)
    // {
    //     _lc += sqrt(pow( nodes_.valueNodes()(_edges[i](0),0) 
    //                     - nodes_.valueNodes()(_edges[i](1),0), 2) 
    //                 + pow( nodes_.valueNodes()(_edges[i](0),1) 
    //                     - nodes_.valueNodes()(_edges[i](1),1)  ,2 ) 
    //                 + pow( nodes_.valueNodes()(_edges[i](0),2) 
    //                     - nodes_.valueNodes()(_edges[i](1),2) ,2) );
    // }

    // _lc = _lc/double(_edges.size());

    // NeumannConditions();

    // Partition();

    // std::cout << std::endl;
    // std::cout << std::endl;

//    for (int i = 0; i < _edges.size(); i++)
//    {
//        cout  << _edges[i](0) <<  " "<< _edges[i](1) << endl;
//    }

//    cout << "-----------------------" << endl;
//    cout << _edges.size() << endl;

    // std::cout << std::endl;
    // std::cout << std::endl;

    // std::cout << "-------------------------------------------------------" << std::endl;
    // std::cout << nodes_.nbNode() << " nodes" << std::endl;
    // std::cout << elements_.nbElement() << " elements" << std::endl;

    // for ( auto dirCond = dirichletConditions_.cbegin(); dirCond != dirichletConditions_.cend(); ++dirCond )
    // {
    //     std::cout << dirCond->nbDirichlet() << " Dirichlet condition nodes" << std::endl;
    // }

    // for ( auto neuCond = neumannConditions_.cbegin(); neuCond != neumannConditions_.cbegin(); ++neuCond )
    // {
    //     std::cout << neuCond->nbNeumann() << " Neumann condition edges" << std::endl;
    // }

    // std::cout << _nb_dirichlet << " Dirichlet condition nodes" << std::endl;
    // std::cout << _nb_neumann << " Neumann condition edges" << std::endl;

    //cout << "----------------------------" << endl;
    //cout << _DirichletConditions << endl;
}



void Mesh::NeumannConditions1()
{
    // ElementSort();
    // NeumannSort();

    // if (dimension_ == 2)
    // {
    //     if (orderMesh_ == 1)
    //     {
    //         Eigen::Vector2d normal;

    //         double x1,x2,y1,y2;
    //         Eigen::Vector2d X3;

    //         double norm;

    //         for (int i = 0; i < _nb_neumann; i++)
    //         {
    //             x1 = nodes_.valueNodes()(_NeumannConditions(i,0),0);
    //             x2 = nodes_.valueNodes()(_NeumannConditions(i,1),0);
    //             y1 = nodes_.valueNodes()(_NeumannConditions(i,0),1);
    //             y2 = nodes_.valueNodes()(_NeumannConditions(i,1),1);

    //             norm = sqrt(pow(x2-x1,2) + pow(y1-y2,2) );

    //             _NeumannLength(i,0) = norm;

    //             normal(0) = -(y2-y1)/norm;
    //             normal(1) = (x2-x1)/norm;



    //             X3 = NodeFromBoundary2D(i);

    //             Eigen::Vector2d vect;

    //             vect(0) = 0.5*(x1 + x2) - (1/3.)*(x1 + x2 + X3(0));
    //             vect(1) = 0.5*(y1 + y2) - (1/3.)*(y1 + y2 + X3(1));

    //             if( vect.dot(normal) < 0 )
    //                 normal = -normal;

    //             _NeumannNormal(i,0) = normal(0);
    //             _NeumannNormal(i,1) = normal(1);
    //         }
    //     }
    //     else if(orderMesh_ == 2)
    //     {
    //         Eigen::Vector2d normal, normal1, normal2;

    //         double x1,x2,y1,y2,x_middle,y_middle;
    //         Eigen::Vector2d X3;

    //         double norm, norm1, norm2;

    //         for (int i = 0; i < _nb_neumann; i++)
    //         {
    //             x1 = nodes_.valueNodes()(_NeumannConditions(i,0),0);
    //             x2 = nodes_.valueNodes()(_NeumannConditions(i,1),0);
    //             y1 = nodes_.valueNodes()(_NeumannConditions(i,0),1);
    //             y2 = nodes_.valueNodes()(_NeumannConditions(i,1),1);
    //             x_middle = nodes_.valueNodes()(_NeumannConditions(i,2),0);
    //             y_middle = nodes_.valueNodes()(_NeumannConditions(i,2),1);

    //             norm = sqrt( pow(x2 - x1,2) + pow(y2 - y1,2) );
    //             norm1 = sqrt( pow(x_middle - x1,2) + pow(y_middle - y1,2) );
    //             norm2 = sqrt( pow(x2 - x_middle,2) + pow(y2 - y_middle,2) );

    //             _NeumannLength(i,0) = norm1;
    //             _NeumannLength(i,1) = norm2;

    //             normal(0) = -(y2 - y1)/norm;
    //             normal(1) = (x2 - x1)/norm;
    //             normal1(0) = -(y_middle - y1)/norm1;
    //             normal1(1) = (x_middle - x1)/norm1;
    //             normal2(0) = -(y2 - y_middle)/norm2;
    //             normal2(1) = (x2 - x_middle)/norm2;


    //             X3 = NodeFromBoundary2D(i);

    //             Eigen::Vector2d vect;

    //             vect(0) = 0.5*(x1 + x2) - (1/3.)*(x1 + x2 + X3(0));
    //             vect(1) = 0.5*(y1 + y2) - (1/3.)*(y1 + y2 + X3(1));


    //             if( vect.dot(normal) < 0 )
    //             {
    //                 normal = -normal;
    //                 normal1 = -normal1;
    //                 normal2 = -normal2;
    //             }

    //             _NeumannNormal(i,0) = normal(0);
    //             _NeumannNormal(i,1) = normal(1);
    //             _NeumannNormal(i,2) = normal1(0);
    //             _NeumannNormal(i,3) = normal1(1);
    //             _NeumannNormal(i,4) = normal2(0);
    //             _NeumannNormal(i,5) = normal2(1);
    //         }
    //     }
    //     else if (orderMesh_ == 3)
    //     {}
    //     else
    //         abort();
    // }
    // else if (dimension_ == 3)
    // {
    //     if (orderMesh_ == 1)
    //     {
    //         Eigen::Vector3d normal;

    //         double x1,y1,z1,x2,y2,z2,x3,y3,z3;
    //         Eigen::Vector3d X4;

    //         double area;



    //         for (int i = 0; i < _nb_neumann; i++)
    //         {
    //             x1 = nodes_.valueNodes()(_NeumannConditions(i,0),0);
    //             y1 = nodes_.valueNodes()(_NeumannConditions(i,0),1);
    //             z1 = nodes_.valueNodes()(_NeumannConditions(i,0),2);

    //             x2 = nodes_.valueNodes()(_NeumannConditions(i,1),0);
    //             y2 = nodes_.valueNodes()(_NeumannConditions(i,1),1);
    //             z2 = nodes_.valueNodes()(_NeumannConditions(i,1),2);

    //             x3 = nodes_.valueNodes()(_NeumannConditions(i,2),0);
    //             y3 = nodes_.valueNodes()(_NeumannConditions(i,2),1);
    //             z3 = nodes_.valueNodes()(_NeumannConditions(i,2),2);

    //             normal(0) = (y3 - y1)*(z2 - z1) - (y2 - y1)*(z3 - z1);
    //             normal(1) = (z3 - z1)*(x2 - x1) - (z2 - z1)*(x3 - x1);
    //             normal(2) = (x3 - x1)*(y2 - y1) - (x2 - x1)*(y3 - y1);

    //             area = 0.5*sqrt( pow(normal(0),2) + pow(normal(1),2) + pow(normal(2),2)  );

    //             _NeumannLength(i,0) = area;

    //             normal = pow(2*area,-1)*normal;



    //             X4 = NodeFromBoundary3D(i);

    //             Eigen::Vector3d vect;

    //             vect(0) = 0.5*(x1 + x2 + x3) - (1/4.)*(x1 + x2 + x3 + X4(0));
    //             vect(1) = 0.5*(y1 + y2 + y3) - (1/4.)*(y1 + y2 + y3 + X4(1));
    //             vect(2) = 0.5*(z1 + z2 + z3) - (1/4.)*(z1 + z2 + z3 + X4(2));


    //             if( vect.dot(normal) < 0 )
    //             {
    //                 normal = -normal;
    //             }

    //             _NeumannNormal(i,0) = normal(0);
    //             _NeumannNormal(i,1) = normal(1);
    //             _NeumannNormal(i,2) = normal(2);

    //         }
    //     }
    //     else if (orderMesh_ == 2)
    //     {

    //     }
    //     else
    //         abort();
    // }
    // else
    //     abort();


}


void Mesh::Partition()
{
    // _partition_vect.resize(nodes_.nb_nodes());
    // _partition_vect.setZero();

    // for (int i = 0; i < _nb_dirichlet; i++)
    // {
    //     _partition_vect(_DirichletConditions(i)) = -1;
    // }

    // int k = 0;

    // for (int i = 0; i < nodes_.nb_nodes(); i++)
    // {
    //     if (_partition_vect(i) == 0)
    //     {
    //         _partition_vect(i) = k;
    //         k += 1;
    //     }
    // }

}




void Mesh::EraseOneCharacter(std::string & str, const char& C)
{
    str.erase(std::remove(str.begin(), str.end(), C), str.end());
}



void Mesh::Resizing(int elm_type)
{
    if (elm_type == 1)       // linear 2D mesh : triangle
    {
        _nb_col_neumann = 2;
        _nb_col_element = 3;
        dimension_ = 2;
        orderMesh_ = 1;
        _nb_vertex = 3;
        _nb_col_neumann_normal = 2;
        _nb_col_neumann_length = 1;
        _nb_edge_per_element = 3;
        _elm_type_boundary = 1;
        _elm_type_element = 2;
    }
    else if (elm_type == 2)  // linear 3D mesh : tetrahedron
    {
        _nb_col_neumann = 3;
        _nb_col_element = 4;
        dimension_ = 3;
        orderMesh_ = 1;
        _nb_vertex = 4;
        _nb_col_neumann_normal = 3;
        _nb_col_neumann_length = 1;
        _nb_edge_per_element = 6;
        _elm_type_boundary = 2;
        _elm_type_element = 4;
    }
    else if (elm_type == 8)  // quadratic 2D mesh : triangle
    {
        _nb_col_neumann = 3;
        _nb_col_element = 6;
        dimension_ = 2;
        orderMesh_ = 2;
        _nb_vertex = 3;
        _nb_col_neumann_normal = 6;
        _nb_col_neumann_length = 2;
        _nb_edge_per_element = 3;
        _elm_type_boundary = 8;
        _elm_type_element = 9;
    }
    else if (elm_type == 9)  // quadratic 3D mesh : tetrahedron
    {
        _nb_col_neumann = 6;
        _nb_col_element = 10;
        dimension_ = 3;
        orderMesh_ = 2;
        _nb_vertex = 4;


        _nb_edge_per_element = 6;
        _elm_type_boundary = 9;
        _elm_type_element = 11;
    }
    else if (elm_type == 26) // cubic 2D mesh : triangle
    {
        _nb_col_neumann = 4;
        _nb_col_element = 10;
        dimension_ = 2;
        orderMesh_ = 3;
        _nb_vertex = 3;


        _nb_edge_per_element = 3;
        _elm_type_boundary = 26;
        _elm_type_element = 21;
    }
    else
        abort();
}



void Mesh::ElementSort()
{
    // _sorted_elements.resize(_nb_elements,_nb_vertex);

    // for (int i = 0; i < _nb_elements; i++)
    // {
    //     std::vector<int> vect(_nb_vertex);
    //     for (int j = 0; j < _nb_vertex; j++)
    //     {
    //         vect[j] = _elements(i,j);
    //     }

    //     std::sort(vect.begin(), vect.end());

    //     for (int j = 0; j < _nb_vertex; j++)
    //     {
    //         _sorted_elements(i,j) = vect[j];
    //     }
    // }
}



void Mesh::NeumannSort()
{
    // _sorted_neumann.resize(_nb_neumann,_nb_vertex - 1);

    // for (int i = 0; i < _nb_neumann; i++)
    // {
    //     std::vector<int> vect(_nb_vertex - 1);
    //     for (int j = 0; j < _nb_vertex - 1; j++)
    //     {
    //         vect[j] = _NeumannConditions(i,j);
    //     }

    //     std::sort(vect.begin(), vect.end());

    //     for (int j = 0; j < _nb_vertex - 1; j++)
    //     {
    //         _sorted_neumann(i,j) = vect[j];
    //     }
    // }


}


Eigen::Vector2d Mesh::NodeFromBoundary2D(const int& i)
{
    double X,Y;

    int p = 0;

    // for (int j = 0; j < _nb_elements ; j++)
    // {
    //     if ( (_sorted_neumann(i,0) == _sorted_elements(j,1)) && (_sorted_neumann(i,1) == _sorted_elements(j,2)) )
    //     {
    //         X = nodes_.valueNodes()(_sorted_elements(j,0),0);
    //         Y = nodes_.valueNodes()(_sorted_elements(j,0),1);
    //         p += 1;
    //         break;
    //     }
    //     else if ( (_sorted_neumann(i,0) == _sorted_elements(j,0)) && (_sorted_neumann(i,1) == _sorted_elements(j,2)) )
    //     {
    //         X = nodes_.valueNodes()(_sorted_elements(j,1),0);
    //         Y = nodes_.valueNodes()(_sorted_elements(j,1),1);
    //         p += 1;
    //         break;
    //     }
    //     else if ( (_sorted_neumann(i,0) == _sorted_elements(j,0)) && (_sorted_neumann(i,1) == _sorted_elements(j,1)) )
    //     {
    //         X = nodes_.valueNodes()(_sorted_elements(j,2),0);
    //         Y = nodes_.valueNodes()(_sorted_elements(j,2),1);
    //         p += 1;
    //         break;
    //     }
    // }

    if (p != 1)
    {
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "Problem : " << p << std::endl;
    }

    return {X,Y};
}



Eigen::Vector3d Mesh::NodeFromBoundary3D(const int& i)
{
    double X,Y,Z;

    int p = 0;

    // for (int j = 0; j < _nb_elements ; j++)
    // {
    //     if ( (_sorted_neumann(i,0) == _sorted_elements(j,1)) && (_sorted_neumann(i,1) == _sorted_elements(j,2)) && (_sorted_neumann(i,2) == _sorted_elements(j,3)) )
    //     {
    //         X = nodes_.valueNodes()(_sorted_elements(j,0),0);
    //         Y = nodes_.valueNodes()(_sorted_elements(j,0),1);
    //         Z = nodes_.valueNodes()(_sorted_elements(j,0),2);
    //         p += 1;
    //         break;
    //     }
    //     else if ( (_sorted_neumann(i,0) == _sorted_elements(j,0)) && (_sorted_neumann(i,1) == _sorted_elements(j,2)) && (_sorted_neumann(i,2) == _sorted_elements(j,3)) )
    //     {
    //         X = nodes_.valueNodes()(_sorted_elements(j,1),0);
    //         Y = nodes_.valueNodes()(_sorted_elements(j,1),1);
    //         Z = nodes_.valueNodes()(_sorted_elements(j,1),2);
    //         p += 1;
    //         break;
    //     }
    //     else if ( (_sorted_neumann(i,0) == _sorted_elements(j,0)) && (_sorted_neumann(i,1) == _sorted_elements(j,1)) && (_sorted_neumann(i,2) == _sorted_elements(j,3)) )
    //     {
    //         X = nodes_.valueNodes()(_sorted_elements(j,2),0);
    //         Y = nodes_.valueNodes()(_sorted_elements(j,2),1);
    //         Z = nodes_.valueNodes()(_sorted_elements(j,2),2);
    //         p += 1;
    //         break;
    //     }
    //     else if ( (_sorted_neumann(i,0) == _sorted_elements(j,0)) && (_sorted_neumann(i,1) == _sorted_elements(j,1)) && (_sorted_neumann(i,2) == _sorted_elements(j,2)) )
    //     {
    //         X = nodes_.valueNodes()(_sorted_elements(j,3),0);
    //         Y = nodes_.valueNodes()(_sorted_elements(j,3),1);
    //         Z = nodes_.valueNodes()(_sorted_elements(j,3),2);
    //         p += 1;
    //         break;
    //     }
    // }

    if (p != 1)
    {
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "Problem : " << p << std::endl;
    }

    return {X,Y,Z};
}



void Mesh::Edge(const Eigen::VectorXi& vertices)
{
    std::vector<Eigen::Vector2i> edge;
    edge.resize(_nb_edge_per_element);

    Eigen::VectorXi check(_nb_edge_per_element);

    for (int j = 0; j < _nb_edge_per_element; j++)
    {
        check(j) = -1;
    }


    int integer1,integer2;
    switch (dimension_)
    {
    case 2 :

        for (int j = 0; j < _nb_edge_per_element; j++)
        {

            switch (j)
            {
            case 0 :
                integer1 = 1;
                integer2 = 2;
                break;
            case 1 :
                integer1 = 0;
                integer2 = 2;
                break;
            case 2 :
                integer1 = 0;
                integer2 = 1;
                break;
            default :
                abort();
            }


            if (vertices(integer1) < vertices(integer2))
            {
                edge[j] = {vertices(integer1),vertices(integer2)};
            }
            else
                edge[j] = {vertices(integer2),vertices(integer1)};
        }
        break;

    case 3 :

        for (int j = 0; j < _nb_edge_per_element; j++)
        {
            switch (j)
            {
            case 0 :
                integer1 = 2;
                integer2 = 3;
                break;
            case 1 :
                integer1 = 1;
                integer2 = 3;
                break;
            case 2 :
                integer1 = 1;
                integer2 = 2;
                break;
            case 3 :
                integer1 = 0;
                integer2 = 3;
                break;
            case 4 :
                integer1 = 0;
                integer2 = 2;
                break;
            case 5 :
                integer1 = 0;
                integer2 = 1;
                break;
            default :
                abort();
            }


            if (vertices(integer1) < vertices(integer2))
            {
                edge[j] = {vertices(integer1),vertices(integer2)};
            }
            else
                edge[j] = {vertices(integer2),vertices(integer1)};
        }

        break;
    default :
        abort();
    }



    for (int j = 0; j < _nb_edge_per_element; j++)
    {
        for (int i = 0; i < _edges.size(); i++)
        {
            if (check(j) == -1)
            {
                if (_edges[i] == edge[j])
                {
                    check(j) = 0;
                }
            }
        }
    }



    for (int j = 0; j < _nb_edge_per_element; j++)
    {
        if (check(j) == -1)
        {
            _edges.push_back(edge[j]);
        }
    }


}





void Mesh::Dirichlet(const Eigen::VectorXi& ref_node, const int& j)
{
    // int number_of_nodes = ref_node.size();

    // Eigen::VectorXi vect(number_of_nodes);

    // for (int i = 0; i < number_of_nodes; i++)
    // {
    //     vect(i) = -1;
    // }

    // for (int i = 0; i < _nb_dirichlet; i++)
    // {
    //     for (int k = 0; k < number_of_nodes; k++)
    //     {
    //         if (_DirichletConditions(i) == ref_node(k))
    //         {
    //             vect(k) = 0;
    //         }
    //     }
    // }

    // for (int k = 0; k < number_of_nodes; k++)
    // {
    //     if (vect(k) == -1)
    //     {
    //         _DirichletConditions(_nb_dirichlet) = ref_node(k);
    //         _nb_dirichlet++;
    //     }
    // }



}


void Mesh::Neumann(const Eigen::VectorXi& ref_node, const int& j)
{
    // for (int k = 0; k < _nb_col_neumann; k++)
    // {
    //     _NeumannConditions(_nb_neumann,k) = ref_node(k);
    // }

    // _nb_neumann++;
}



void Mesh::Element1(const Eigen::VectorXi& ref_node_element)
{
    // for (int k = 0; k < _nb_col_element; k++)
    // {
    //     _elements(_nb_elements,k) = ref_node_element(k);
    // }


    // double x1,x2,x3,x4;
    // double y1,y2,y3,y4;
    // double z1,z2,z3,z4;

    // if (_dimension == 2)
    // {

    //     x1 = nodes_.valueNodes()(ref_node_element(0),0);
    //     x2 = nodes_.valueNodes()(ref_node_element(1),0);
    //     x3 = nodes_.valueNodes()(ref_node_element(2),0);
    //     y1 = nodes_.valueNodes()(ref_node_element(0),1);
    //     y2 = nodes_.valueNodes()(ref_node_element(1),1);
    //     y3 = nodes_.valueNodes()(ref_node_element(2),1);

    //     _element_area(_nb_elements) = 0.5*abs( (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1) );
    //     _determinant(_nb_elements) = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
    // }
    // else if (_dimension == 3)
    // {
    //     x1 = nodes_.valueNodes()(ref_node_element(0),0);
    //     x2 = nodes_.valueNodes()(ref_node_element(1),0);
    //     x3 = nodes_.valueNodes()(ref_node_element(2),0);
    //     x4 = nodes_.valueNodes()(ref_node_element(3),0);

    //     y1 = nodes_.valueNodes()(ref_node_element(0),1);
    //     y2 = nodes_.valueNodes()(ref_node_element(1),1);
    //     y3 = nodes_.valueNodes()(ref_node_element(2),1);
    //     y4 = nodes_.valueNodes()(ref_node_element(3),1);

    //     z1 = nodes_.valueNodes()(ref_node_element(0),2);
    //     z2 = nodes_.valueNodes()(ref_node_element(1),2);
    //     z3 = nodes_.valueNodes()(ref_node_element(2),2);
    //     z4 = nodes_.valueNodes()(ref_node_element(3),2);

    //     _element_area(_nb_elements) = (1/6.)* ((x2 - x1)*(y3 - y1)*(z4 - z1) + (x3 - x1)*(y4 - y1)*(z2 - z1) + (y2 - y1)*(z3 - z1)*(x4 - x1) - (z2-z1)*(y3-y1)*(x4-x1) - (y2 - y1)*(x3 - x1)*(z4 - z1) - (x2 - x1)*(z3 - z1)*(y4 - y1) );
    //     _determinant(_nb_elements) = (x2-x1)*(y3-y1)*(z4-z1) + (x3-x1)*(y4-y1)*(z2-z1) + (y2-y1)*(z3-z1)*(x4-x1) - (z2-z1)*(y3-y1)*(x4-x1) - (y2-y1)*(x3-x1)*(z4-z1) - (x2-x1)*(z3-z1)*(y4-y1);
    // }

    // _invert_determinant(_nb_elements) = 1./_determinant(_nb_elements);
    // _nb_elements++;
}


// void Mesh::print( std::ostream& os ) const
// {
//     os << "Number of nodes: " << nodes_.nbNode();
//     os << "Number of elements: " << elements_.nbElement();
// }

std::ostream& operator<<( std::ostream& os, const Mesh& mesh )
{

    os << mesh.nodes_;
    // os << "--------------------------------------------------" << std::endl;
    // os << "Number of nodes : " << mesh.nodes_.nbNode() << std::endl;
    // os << "Nodes : " << std::endl;
    // os << mesh.nodes_.valueNodes() << std::endl;

    os << mesh.internal_;

    os << mesh.dirichletConditions_;
    os << mesh.neumannConditions_;

    // os << "--------------------------------------------------" << std::endl;
    // os << "Number of internal field elements : " << mesh.internal_.nbInternalIndex() << std::endl;
    // os << "Number of elements : " << mesh.elements_.nbElement() << std::endl;
    
    // os << "--------------------------------------------------" << std::endl;
    // os << "Number of Dirichlet conditions : " << mesh.dirichletConditions_.nbDirichlet() << std::endl;
    // os << "Dirichlet conditions" << std::endl;

    // for ( int j = 0; j < mesh.dirichletConditions_.dirichletConditions().size(); j++ )
    // {
    //     for ( int k = 0; k < mesh.dirichletConditions_.dirichletConditions()[j].size(); k++)
    //     {
    //         os << mesh.dirichletConditions_.dirichletConditions()[j][k] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return os;
}