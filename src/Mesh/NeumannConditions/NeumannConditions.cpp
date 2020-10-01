#include "NeumannConditions.h"

NeumannConditions::NeumannConditions()
{

}


void NeumannConditions::affect_NeumannConditions( const PhysicalNames& physicalNames, const Element& element )
{
    nbNeumann_ = 0;

    const std::vector<std::string>& names = physicalNames.names();

    for ( int i = 0; i < physicalNames.names().size(); i++ )
    {
        if ( names[i].substr( 0, names[i].length() - 1 ) == "Neumann" )
        {
            nbNeumann_++;

            std::vector<std::vector<int>> oneNeumannConditions;

            for ( int j = 0; j < element.nbElement(); j++ )
            {
                if ( element.tags()[j][0] == physicalNames.tag()[i] )
                {
                    oneNeumannConditions.push_back( element.element()[j] );
                }
            }

            indexNeumannConditions_.push_back( oneNeumannConditions );
        }
    }
}

std::ostream& operator<<( std::ostream& os, const NeumannConditions& neumannConditions )
{
    os << "--------------------------------------------------" << std::endl;
    os << "Number of Neumann conditions : " << neumannConditions.nbNeumann_ << std::endl;
    
    // Const reference to indexNeumannConditions to alleviate the syntax
    const std::vector<std::vector<std::vector<int>>> indexNeumannConditions = neumannConditions.indexNeumannConditions_;

    for ( auto i = indexNeumannConditions.cbegin(); i != indexNeumannConditions.cend(); ++i )
    {
        os << "Neumann conditions : " << std::distance( indexNeumannConditions.cbegin(), i + 1) << std::endl;
        for ( auto j = i->cbegin(); j != i->cend(); ++j )
        {
            for ( auto k = j->cbegin(); k != j->cend(); ++k )
            {
                os << *k << " ";
            }
            os << std::endl;            
        }
       
    }
}