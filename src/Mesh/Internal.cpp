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

void Internal::computeInternalArea( const Dimensions& dimensions, const Node& node )
{
    const int& dimension = dimensions.dimension();

    internalArea_.resize( nbInternalIndex_ );

    for ( int i = 0; i < nbInternalIndex_; i++ )
    {
        if ( dimension == 2 )
        {
            const double& x1 = node.valueNodes()( indexInternalField_[i][0] - 1, 0);
            const double& y1 = node.valueNodes()( indexInternalField_[i][0] - 1, 1);

            const double& x2 = node.valueNodes()( indexInternalField_[i][1] - 1, 0);
            const double& y2 = node.valueNodes()( indexInternalField_[i][1] - 1, 1);
            
            const double& x3 = node.valueNodes()( indexInternalField_[i][2] - 1, 0);
            const double& y3 = node.valueNodes()( indexInternalField_[i][2] - 1, 1);

            internalArea_[i] = 0.5*std::abs( (x2 - x1)*(y3 - y1) 
                                           - (x3 - x1)*(y2 - y1) );
        }
        else if( dimension == 3 )
        {
            const double& x1 = node.valueNodes()( indexInternalField_[i][0] - 1, 0);
            const double& y1 = node.valueNodes()( indexInternalField_[i][0] - 1, 1);
            const double& z1 = node.valueNodes()( indexInternalField_[i][0] - 1, 2);

            const double& x2 = node.valueNodes()( indexInternalField_[i][1] - 1, 0);
            const double& y2 = node.valueNodes()( indexInternalField_[i][1] - 1, 1);
            const double& z2 = node.valueNodes()( indexInternalField_[i][1] - 1, 2);

            const double& x3 = node.valueNodes()( indexInternalField_[i][2] - 1, 0);
            const double& y3 = node.valueNodes()( indexInternalField_[i][2] - 1, 1);
            const double& z3 = node.valueNodes()( indexInternalField_[i][2] - 1, 2);

            const double& x4 = node.valueNodes()( indexInternalField_[i][3] - 1, 0);
            const double& y4 = node.valueNodes()( indexInternalField_[i][3] - 1, 1);
            const double& z4 = node.valueNodes()( indexInternalField_[i][3] - 1, 2);

            internalArea_[i] = (1/6.)*( (x2 - x1)*(y3 - y1)*(z4 - z1) 
                                      + (x3 - x1)*(y4 - y1)*(z2 - z1) 
                                      + (y2 - y1)*(z3 - z1)*(x4 - x1) 
                                      - (z2 - z1)*(y3 - y1)*(x4 - x1) 
                                      - (y2 - y1)*(x3 - x1)*(z4 - z1) 
                                      - (x2 - x1)*(z3 - z1)*(y4 - y1) );
        }
        else
        {
            throw;
        }
        
    }

    // double area = 0.;
    // for ( auto i = internalArea_.cbegin(); i != internalArea_.cend(); ++i )
    // {
    //     area += *i;
    // }
    // std::cout << "area : " << area << std::endl;

}

void Internal::computeDeterminant( const Dimensions& dimensions, const Node& node )
{
    const int& dimension = dimensions.dimension();

    determinant_.resize( nbInternalIndex_ );
    invertDeterminant_.resize( nbInternalIndex_ );

    for ( int i = 0; i < nbInternalIndex_; i++ )
    {
        if ( dimension == 2 )
        {
            const double& x1 = node.valueNodes()( indexInternalField_[i][0] - 1, 0);
            const double& y1 = node.valueNodes()( indexInternalField_[i][0] - 1, 1);

            const double& x2 = node.valueNodes()( indexInternalField_[i][1] - 1, 0);
            const double& y2 = node.valueNodes()( indexInternalField_[i][1] - 1, 1);
            
            const double& x3 = node.valueNodes()( indexInternalField_[i][2] - 1, 0);
            const double& y3 = node.valueNodes()( indexInternalField_[i][2] - 1, 1);

            determinant_[i] = (x2 - x1)*(y3 - y1) 
                            - (x3 - x1)*(y2 - y1);

            invertDeterminant_[i] = 1/determinant_[i];

        }
        else if( dimension == 3 )
        {
            const double& x1 = node.valueNodes()( indexInternalField_[i][0] - 1, 0);
            const double& y1 = node.valueNodes()( indexInternalField_[i][0] - 1, 1);
            const double& z1 = node.valueNodes()( indexInternalField_[i][0] - 1, 2);

            const double& x2 = node.valueNodes()( indexInternalField_[i][1] - 1, 0);
            const double& y2 = node.valueNodes()( indexInternalField_[i][1] - 1, 1);
            const double& z2 = node.valueNodes()( indexInternalField_[i][1] - 1, 2);

            const double& x3 = node.valueNodes()( indexInternalField_[i][2] - 1, 0);
            const double& y3 = node.valueNodes()( indexInternalField_[i][2] - 1, 1);
            const double& z3 = node.valueNodes()( indexInternalField_[i][2] - 1, 2);

            const double& x4 = node.valueNodes()( indexInternalField_[i][3] - 1, 0);
            const double& y4 = node.valueNodes()( indexInternalField_[i][3] - 1, 1);
            const double& z4 = node.valueNodes()( indexInternalField_[i][3] - 1, 2);

            determinant_[i] = (x2 - x1)*(y3 - y1)*(z4 - z1) 
                            + (x3 - x1)*(y4 - y1)*(z2 - z1) 
                            + (y2 - y1)*(z3 - z1)*(x4 - x1) 
                            - (z2 - z1)*(y3 - y1)*(x4 - x1) 
                            - (y2 - y1)*(x3 - x1)*(z4 - z1) 
                            - (x2 - x1)*(z3 - z1)*(y4 - y1);

            invertDeterminant_[i] = 1/determinant_[i];
        }
        else
        {
            throw;
        }
    }   
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
