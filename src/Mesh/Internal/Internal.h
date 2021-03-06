#ifndef INTERNAL_H
#define INTERNAL_H

#include <Eigen/Core>

#include "../PhysicalNames/PhysicalNames.h"
#include "../Element/Element.h"
#include "../Dimensions/Dimensions.h"
#include "../Node/Node.h"

class Internal
{
    private:
        std::vector<std::vector<int>> indexInternalField_;
        int nbInternalIndex_;

        std::vector<double> internalArea_;
        std::vector<double> determinant_;
        std::vector<double> invertDeterminant_;        

    public:
        Internal();
        
        void affectInternalField
        ( 
            const PhysicalNames& physicalNames, 
            const Element& element
        );

        void computeInternalArea( const Dimensions& dimensions, const Node& node );
        void computeDeterminant( const Dimensions& dimensions, const Node& node );

        inline const std::vector<std::vector<int>>& indexInternalField() const { return indexInternalField_; }
        inline const int& nbInternalIndex() const { return nbInternalIndex_; }

        inline const std::vector<double>& internalArea() const { return internalArea_; }
        inline const std::vector<double>& determinant() const { return determinant_; }
        inline const std::vector<double>& invertDeterminant() const { return invertDeterminant_; }


        friend std::ostream& operator<<( std::ostream& os, const Internal& internal );
};

#endif