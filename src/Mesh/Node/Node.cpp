#include "Node.h"

Node::Node()
{}

void Node::Read_nodes(std::ifstream& mesh_file)
{
    mesh_file >> nbNodes_;
    valueNodes_.resize(nbNodes_,3);

    double x,y,z; int ref;

    for (int i = 0 ; i < nbNodes_ ; i++)
    {
        mesh_file >> ref >> x >> y >> z;
        valueNodes_(i,0) = x;
        valueNodes_(i,1) = y;
        valueNodes_(i,2) = z;
    }
}

std::ostream& operator<<( std::ostream& os, const Node& node )
{
    os << "--------------------------------------------------" << "\n";
    os << "Number of nodes : " << node.nbNode() << "\n";
    os << "Nodes : " << "\n";
    os << node.valueNodes_ << "\n";
}