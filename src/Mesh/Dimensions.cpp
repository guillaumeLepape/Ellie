#include "Dimensions.h"

Dimensions::Dimensions()
{

}

void Dimensions::affectDimensions( const Element& element )
{
    if ( element.typeElement()[1] == 1 && element.typeElement()[element.element().size() - 1] == 2 )
    {
        // nbColNeumann_ = 2;
        // nbColElement_ = 3;
        dimension_ = 2;
        orderMesh_ = 1;
        // nbVertex_ = 3;
        // nbColNeumannNormal_ = 2;
        // nbColNeumannLength_ = 1;
        nbEdgePerElement_ = 3;
        elmTypeBoundary_ = 1;
        elmTypeElement_ = 2;
    }
    else if ( element.typeElement()[1] == 2 && element.typeElement()[element.element().size() - 1] == 4 )
    {
        // nbColNeumann_ = 3;
        // nbColElement_ = 4;
        dimension_ = 3;
        orderMesh_ = 1;
        // nbVertex_ = 4;
        // nbColNeumannNormal_ = 3;
        // nbColNeumannLength_ = 1;
        nbEdgePerElement_ = 6;
        elmTypeBoundary_ = 2;
        elmTypeElement_ = 4;
    }

   
}