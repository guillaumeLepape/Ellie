#ifndef INTERNAL_H
#define INTERNAL_H

#include <Eigen/Eigen>

#include "PhysicalNames.h"
#include "Element.h"

class Internal
{
    private:
        std::vector<std::vector<int>> indexInternalField_;
        int nbInternalIndex_;

    public:
        Internal();
        
        void affectInternalField
        ( 
            const PhysicalNames& physicalNames, 
            const Element& element
        );

        inline const std::vector<std::vector<int>>& indexInternalField() const { return indexInternalField_; }
        inline const int& nbInternalIndex() const { return nbInternalIndex_; }

        friend std::ostream& operator<<( std::ostream& os, const Internal& internal );
};

#endif