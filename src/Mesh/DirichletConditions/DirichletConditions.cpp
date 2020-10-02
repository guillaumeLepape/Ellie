#include "DirichletConditions.h"

#include <algorithm>
#include <unordered_set>

DirichletConditions::DirichletConditions()
{

}

void DirichletConditions::affectDirichletConditions( const PhysicalNames& physicalNames, const Element& element )
{
    nbDirichlet_ = 0;

    const std::vector<std::string>& names = physicalNames.names();

    for ( int i = 0; i < physicalNames.names().size(); i++ )
    {
        std::vector<int> dirichletConditions;

        if ( names[i].substr( 0, names[i].length() - 1 ) == "Dirichlet" )
        {
            nbDirichlet_++;
        
            for ( int j = 0; j < element.nbElement(); j++ )
            {
                if ( element.tags()[j][0] == physicalNames.tag()[i] )
                {
                    for ( int k = 0; k < element.element()[j].size(); k++ )
                    {
                        dirichletConditions.push_back( element.element()[j][k] );
                    }

                }
            }

            // Delete duplicate entries of the dirichletConditions
            std:sort( dirichletConditions.begin(), dirichletConditions.end() );
            dirichletConditions.erase( std::unique( dirichletConditions.begin(), dirichletConditions.end() ),dirichletConditions.end() );

            indexDirichletConditions_.push_back( dirichletConditions );
        }
    }
}

std::ostream& operator<<( std::ostream& os, const DirichletConditions& dirichletConditions )
{
    os << "--------------------------------------------------\n";
    os << "Number of Dirichlet conditions : " << dirichletConditions.nbDirichlet_ << "\n";

    // Const reference to indexDirichletConditions to alleviate the syntax
    const std::vector<std::vector<int>>& indexDirichletConditions = dirichletConditions.indexDirichletConditions_;

    for ( auto i = indexDirichletConditions.cbegin(); i != indexDirichletConditions.cend(); ++i )
    {
        os << "Dirichlet conditions : " << std::distance( indexDirichletConditions.cbegin(), i + 1) << "\n";
        for ( auto j = i->cbegin(); j != i->cend(); ++j )
        {
            os << *j << " ";
        }
        os << "\n";
    }
}
