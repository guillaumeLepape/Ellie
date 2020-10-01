#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

#include <fstream>

#include <Eigen/Core>

#include "PhysicalNames.h"
#include "Element.h"


class NeumannConditions
{
    private:

        std::vector<std::vector<std::vector<int>>> indexNeumannConditions_;
        // Eigen::MatrixXi _NeumannConditions;
        // Eigen::MatrixXd _NeumannNormal;
        // Eigen::MatrixXd _NeumannLength;
        // Eigen::MatrixXi _sorted_neumann;
        int nbNeumann_;

    public:
        NeumannConditions();

        void affect_NeumannConditions( const PhysicalNames& physicalNames, const Element& element );

        inline const std::vector<std::vector<std::vector<int>>>& indexNeumannConditions() const { return indexNeumannConditions_; }
        inline const int& nbNeumann() const { return nbNeumann_; }

        friend std::ostream& operator<<( std::ostream& os, const NeumannConditions& neumannConditions );
};

#endif