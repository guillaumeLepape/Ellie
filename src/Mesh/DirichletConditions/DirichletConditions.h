#ifndef DIRICHLET_CONDITIONS_H
#define DIRICHLET_CONDITIONS_H

// Include STL file
#include <fstream>

// Include Eigen library file
#include <Eigen/Core>

// Include Utopia files
#include "../PhysicalNames/PhysicalNames.h"
#include "../Element/Element.h"

class DirichletConditions
{
    private:
        std::vector<std::vector<int>> indexDirichletConditions_;
        int nbDirichlet_;

    public:
        DirichletConditions();

        void affectDirichletConditions( const PhysicalNames& physicalNames, const Element& element );

        inline const std::vector<std::vector<int>> dirichletConditions() const { return indexDirichletConditions_; }
        inline const int& nbDirichlet() const { return nbDirichlet_; }

        friend std::ostream& operator<<( std::ostream& os, const DirichletConditions& dirichletConditions );
};

#endif