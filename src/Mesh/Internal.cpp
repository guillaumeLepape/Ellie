#include "Internal.h"

Internal::Internal()
{

}

void Internal::affectInternalField
( 
    const PhysicalNames& physicalNames, 
    const Element& element 
)
{
    int tag_interior;

     for ( int i = 0; i < physicalNames.names().size(); i++ )
    {
        if ( physicalNames.names()[i] == "interior" )
        {   
            tag_interior = physicalNames.tag()[i];
        }
    }

    for ( int i = 0; i < element.element().size(); i++)
    {
        if ( element.tags()[i][0] == tag_interior )
        {
            indexInternalField_.push_back( element.element()[i] );
        }
    }

    nbInternalIndex_ = indexInternalField_.size();

    // for ( auto i = indexInternalField_.cbegin(); i != indexInternalField_.cend(); i++ )
    // {
    //     for ( auto j = i->cbegin(); j != i->cend(); j++ )
    //     {
    //         std::cout << *j << " ";
    //     }
    //     std::cout << std::endl;
    // }

}

std::ostream& operator<<( std::ostream& os, const Internal& internal )
{
    os << "--------------------------------------------------" << std::endl;
    os << "Number of internal field elements : " << internal.nbInternalIndex() << std::endl;
    
    os << "Internal " << std::endl;
    
    for ( auto i = internal.indexInternalField().cbegin(); i != internal.indexInternalField().cend(); i++ )
    {
        for ( auto j = i->cbegin(); j != i->cend(); j++ )
        {
            os << *j << " ";
        }
        os << std::endl;
    }
}
