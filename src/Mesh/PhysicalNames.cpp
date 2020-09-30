#include "PhysicalNames.h"

PhysicalNames::PhysicalNames()
{

}

void PhysicalNames::Read_PhysicalNames( std::ifstream& mesh_file )
{
    mesh_file >> nbPhysicalNames_;
    tag_.resize( nbPhysicalNames_ );
    names_.resize( nbPhysicalNames_ );

    int number;

    for ( int i = 0; i < nbPhysicalNames_; i++ )
    {
        mesh_file >> number >> tag_[i] >> names_[i];

        names_[i] = names_[i].substr( 1, names_[i].length() - 2 );
    }
}