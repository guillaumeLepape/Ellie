#include "Partition.h"

Partition::Partition()
{

}

void Partition::setPartition( const Node& node, const DirichletConditions& dirichletConditions )
{
    partition_.setConstant(node.nbNode(), 1);
    
    for ( int i = 0; i < dirichletConditions.nbDirichlet(); i++ )
    {
        for ( int j = 0; j < dirichletConditions.dirichletConditions()[i].size(); j++ )
        {
            partition_[dirichletConditions.dirichletConditions()[i][j] - 1] = 0;
        }
    }

    int k = 1;

    for (int i = 0; i < node.nbNode(); i++)
    {
        if (partition_(i) == 1)
        {
            partition_(i) = k;
            k += 1;
        }
    }
}