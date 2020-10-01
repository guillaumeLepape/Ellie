#ifndef PARTITION_H
#define PARTITION_H

#include <Eigen/Core>

#include "Node.h"
#include "DirichletConditions.h"

class Partition
{
    private:
        Eigen::VectorXi partition_;
    public:
        Partition();

        void setPartition( const Node& node, const DirichletConditions& dirichletConditions );

        inline const Eigen::VectorXi& partition() const { partition_; }
};

#endif