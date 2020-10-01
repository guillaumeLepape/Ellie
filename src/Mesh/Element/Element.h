#ifndef ELEMENT_H
#define ELEMENT_H

#include <fstream>
#include <iostream>
#include <vector>

#include <Eigen/Core>

//- Read the elements from $Elements line to $EndElements line
//- Then it contains all the boundary conditions indexes and the internal elements indexes
//- The elements has to be separated into Dirichlet conditions (in DirichletConditions class),
//- the Neumann conditions (in NeumannConditions) and the internal mesh (in Internal)

class Element
{
    private:
        // The number of elements of the mesh
        int nbElement_; 
        
        // The vector containing the typeElement
        std::vector<int> typeElement_;
        
        // Vector containing the tags of the mesh elements
        std::vector<std::vector<int>> tags_;

        // Vector containing the nodes index of the each elements
        std::vector<std::vector<int>> indexElements_;

    public:
        Element();

        void Read_elements(std::ifstream& mesh_file);

        inline const int& nbElement() const { return nbElement_; }

        inline const std::vector<int>& typeElement() const { return typeElement_; }
        inline const std::vector<std::vector<int>>& tags() const { return tags_; }
        inline const std::vector<std::vector<int>>& element() const { return indexElements_; }
};

#endif
