#ifndef __DERIVATEPOLYNOM_H__
#define __DERIVATEPOLYNOM_H__

#include "../Polynom/Polynom.h"

//- Model the derivate of reference polynom P
//- DerivatePolynom contains three polynoms : dP/dx, dP/dy, dP/dz

class DerivatePolynom
{
    private:
        std::vector<Polynom> m_derivatePolynom;

    public:
        DerivatePolynom( const std::vector<Polynom>& derivatePolynom );

        DerivatePolynom( const std::vector< std::string >& str );

        //- Evaluation of the derivate polynom in coord point and for the j-component
        double operator()( const int& j, const Eigen::Vector3d& coord );

};

#endif // __DERIVATEPOLYNOM_H__