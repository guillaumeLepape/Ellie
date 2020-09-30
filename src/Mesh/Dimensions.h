#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "Element.h"

class Dimensions
{
    private:
        //- Dimension of the problem (2 or 3)
        int dimension_;
        //- Order of the mesh (1 or 2)
        int orderMesh_;

        int elmTypeBoundary_;
        int elmTypeElement_;

        // int nbColNeumann_;
        // int nbColElement_;

        // int nbColNeumannNormal_;
        // int nbColNeumannLength_;
        int nbEdgePerElement_;

        int nbInternalIndex_;

    public:
        Dimensions();

        void affectDimensions( const Element& element );

        // inline const int& nbColElement() const { return nbColElement_; }
        inline const int& dimension() const { return dimension_; }
        inline const int& orderMesh() const { return orderMesh_; }

        inline const int& nbInternalIndex() const { return nbInternalIndex_; }

};

#endif