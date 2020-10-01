#ifndef MESH_H
#define MESH_H

#include <Eigen/Core>

#include <string>
#include <vector>

#include "../PhysicalNames/PhysicalNames.h"
#include "../Node/Node.h"

#include "../Element/Element.h"

#include "../Dimensions/Dimensions.h"
#include "../Internal/Internal.h"
#include "../DirichletConditions/DirichletConditions.h"
#include "../NeumannConditions/NeumannConditions.h"

#include "../Partition/Partition.h"

class Mesh {

private:
    PhysicalNames physicalNames_;

    // Structure containing the number of nodes and their values
    Node nodes_;

    Dimensions dimensions_;
    
    DirichletConditions dirichletConditions_;
    NeumannConditions neumannConditions_;
    Internal internal_;

    Partition partition_;

public:
    Mesh();

    void ReadMesh(const std::string& name_mesh);

    inline const Node& nodes() const { return nodes_; } 

    inline const DirichletConditions& dirichletConditions() const { return dirichletConditions_; }
    inline const NeumannConditions& neumannConditions() const { return neumannConditions_; }
    inline const Internal& internal() const { return internal_; }

    inline const Partition& partition() const { return partition_; }

    // void Partition();

    friend std::ostream& operator<<( std::ostream& os, const Mesh& mesh );
};





#endif
