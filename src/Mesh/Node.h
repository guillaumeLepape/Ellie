#ifndef NODE_H
#define NODE_H

#include <fstream>

#include <Eigen/Core>

class Node
{
    private :
        Eigen::Matrix<double, Eigen::Dynamic, 3> valueNodes_;
        int nbNodes_;
    
    public:
        Node();
        void Read_nodes(std::ifstream& mesh_file);

        inline const Eigen::Matrix<double, Eigen::Dynamic, 3>& valueNodes() const {return valueNodes_;}
        inline const int& nbNode() const { return nbNodes_; }

        friend std::ostream& operator<<( std::ostream& os, const Node& node );
};

#endif