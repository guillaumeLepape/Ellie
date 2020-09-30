#ifndef MESH_H
#define MESH_H

#include <Eigen/Core>

#include <string>
#include <vector>

#include "PhysicalNames.h"
#include "Node.h"

#include "Element.h"

#include "Dimensions.h"
#include "Internal.h"
#include "DirichletConditions.h"
#include "NeumannConditions.h"

// // forward declaration of the class
// class Mesh;

// // forward declaration of the stream operator
// std::ostream& operator<<
// ( 
//     std::ostream& os, 
//     const Mesh& mesh 
// );

class Mesh {

private:
    PhysicalNames physicalNames_;

    // Structure containing the number of nodes and their values
    Node nodes_;

    // Eigen::Matrix<double, Eigen::Dynamic, 3> _nodes;
    // int _nb_nodes;

    // Structure containing the number of internal elements and their values
    // Element elements_;

    // Element elements_;

    // Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> _elements;
    // Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> _sorted_elements;
    // Eigen::VectorXd _element_area;
    // int _nb_elements;
    // Eigen::VectorXd _determinant;
    // Eigen::VectorXd _invert_determinant;

    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> _boundary_reference;

    double _lc;

    Dimensions dimensions_;
    
    DirichletConditions dirichletConditions_;
    NeumannConditions neumannConditions_;
    Internal internal_;

    // Eigen::VectorXi _DirichletConditions;
    // int _nb_dirichlet;

    // Eigen::MatrixXi _NeumannConditions;
    // Eigen::MatrixXd _NeumannNormal;
    // Eigen::MatrixXd _NeumannLength;
    // Eigen::MatrixXi _sorted_neumann;
    // int  _nb_neumann;


    int dimension_;
    int orderMesh_;

    int _nb_vertex;

    int _nb_col_neumann;
    int _nb_col_neumann_normal, _nb_col_neumann_length;


    int _nb_col_element;

    std::vector<Eigen::Vector2i> _edges;
    int _nb_edge_per_element;

    Eigen::VectorXi _partition_vect;

    int _elm_type_boundary, _elm_type_element;


public:
    Mesh();

    void ReadMesh(const std::string& name_mesh);

    // getter for all private attributes of the mesh
    // inline const Eigen::Matrix<double, Eigen::Dynamic, 3> GetNodes() const {return _nodes;}
    // inline const int GetNumberofNodes() const {return _nb_nodes;}

    inline const Node& nodes() const { return nodes_; } 

    // inline const Element& elements() const { return elements_; }

    inline const DirichletConditions& dirichletConditions() const { return dirichletConditions_; }
    inline const NeumannConditions& neumannConditions() const { return neumannConditions_; }
    inline const Internal& internal() const { return internal_; }
    // inline const Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> GetElement() const {return _elements;}
    // inline const Eigen::VectorXd GetElementArea() const {return _element_area;}
    // inline const int GetNumberofElement() const {return _nb_elements;}
    // inline const Eigen::VectorXd GetDeterminant() const {return _determinant;}
    // inline const Eigen::VectorXd GetInvertDeterminant() const {return _invert_determinant;}

    // inline const Element& elements() const { return elements_; }

    inline const int dimension() const { return dimension_; }
    inline const int orderMesh() const { return orderMesh_; }

    inline const double GetLengthoftheMesh() const {return _lc;}

    // inline const DirichletConditions dirichletConditions() const { dirichletConditions_; }
    // inline const NeumannConditions neumannConditions() const { neumannConditions_; } 

    // inline const double GetNumberDirichlet() const {return _nb_dirichlet;}
    // inline const double GetNumberNeumann() const {return _nb_neumann;}

    inline const int GetNumberofVertex() const {return _nb_vertex;}

    // inline const Eigen::VectorXi GetDirichletConditions() const {return _DirichletConditions;}
    // inline const Eigen::MatrixXi GetNeumannConditions() const {return _NeumannConditions;}
    // inline const Eigen::MatrixXd GetNeumannNormal() const {return _NeumannNormal;}
    // inline const Eigen::MatrixXd GetNeumannLength() const {return _NeumannLength;}

    inline const Eigen::VectorXi GetPartitionVect() const {return _partition_vect;}


    void Partition();

    void Resizing(int elm_type);

    void ElementSort();
    void NeumannSort();

    Eigen::Vector2d NodeFromBoundary2D(const int& i);
    Eigen::Vector3d NodeFromBoundary3D(const int& i);

    void NeumannConditions1();
    void Edge(const Eigen::VectorXi& vertices);

    void EraseOneCharacter(std::string& str, const char& C);

    void Dirichlet(const Eigen::VectorXi& ref_node, const int& j);
    void Neumann(const Eigen::VectorXi& ref_node, const int& j);

    void Element1(const Eigen::VectorXi& ref_node_element);

    friend std::ostream& operator<<( std::ostream& os, const Mesh& mesh );
};





#endif
