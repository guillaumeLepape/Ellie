#ifndef LAPLACIAN_H
#define LAPLACIAN_H

#include "../Mesh/Mesh/Mesh.h"
#include "../Field/Field.h"

#include <Eigen/Sparse>

template<class Type>
class Laplacian
{
    private:
        const Field<Type>& field_;
        
        Eigen::SparseMatrix<double> lapMat_;
        Eigen::SparseVector<double> lapBC_;

    public:
        Laplacian( const Field<Type>& field );

        void assemblyMatrix();

        inline const Eigen::SparseMatrix<double>& mat() { return lapMat_; }
        inline const Eigen::SparseVector<double>& bc() { return lapBC_; }
};

#endif