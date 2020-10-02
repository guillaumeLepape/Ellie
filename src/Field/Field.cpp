#include "Field.h"

template<class Type>
Field<Type>::Field( const Mesh& mesh, const std::string& nameField, const Type& value )
    : mesh_( mesh ),  nameField_( nameField ), value_( mesh.nodes().nbNode(), value )
{

}

template<class Type>
void Field<Type>::print( std::ostream& os ) const
{
    os << "--------------------------------------------------\n";
    os << "Field : " << nameField_ << "\n";

    for ( auto i = value_.cbegin(); i != value_.cend(); ++i )
    {
        for ( int j = 0; j < i->size(); j++ )
        {
            os << (*i)[j] << " ";
        }
        os << "\n";
    }
}

template<>
void Field<double>::print( std::ostream& os ) const
{
    os << "--------------------------------------------------\n";
    os << "Field : " << nameField_ << "\n";

    for ( auto i = value_.cbegin(); i != value_.cend(); ++i )
    {
        os << *i << "\n";
    }
}

template<class Type> 
void Field<Type>::write() const
{
    std::ofstream os;
    os.open(nameField_ + ".inp", std::ios::out);

    writeMeshDimension( os );
    writeNodes( os );
    writeInternalIndex( os );
    writeFieldDimension( os );
    writeNameField( os );
    writeValues( os );
    
    os.close();
}

template<class Type>
void Field<Type>::writeMeshDimension( std::ofstream& os ) const
{
    os << mesh_.nodes().nbNode() << " " 
       << mesh_.internal().nbInternalIndex() << " " 
       << 1 << " "    
       << 0 << " " 
       << 0 << "\n";
}

template<class Type>
void Field<Type>::writeNodes( std::ofstream& os ) const
{
    for (int i = 0; i < mesh_.nodes().nbNode() ; i++)
    {
        os << i << " " << mesh_.nodes().valueNodes()(i,0) 
                << " " << mesh_.nodes().valueNodes()(i,1) 
                << " " << mesh_.nodes().valueNodes()(i,2)  << "\n";
    }
}

template<class Type>
void Field<Type>::writeInternalIndex( std::ofstream& os ) const
{
    for (int i = 0; i < mesh_.internal().nbInternalIndex(); i++)
    {
        switch (mesh_.dimensions().dimension())
        {
        case 2 :
            os << i << " " << 0 << " " << "tri" << " " 
                << mesh_.internal().indexInternalField()[i][0] - 1 << " " 
                << mesh_.internal().indexInternalField()[i][1] - 1 << " " 
                << mesh_.internal().indexInternalField()[i][2] - 1 << "\n";
            break;
        case 3 :
            os << i << " " << 0 << " " << "tet" << " " 
                << mesh_.internal().indexInternalField()[i][0] - 1 << " " 
                << mesh_.internal().indexInternalField()[i][1] - 1 << " " 
                << mesh_.internal().indexInternalField()[i][2] - 1 << " " 
                << mesh_.internal().indexInternalField()[i][3] - 1 << "\n";
            break;
        default :
            throw;
        }
    }
}

template<>
void Field<double>::writeFieldDimension( std::ofstream& os ) const
{
    os << 1 << " " << 1 << "\n";
}

template<>
void Field<Eigen::Vector2d>::writeFieldDimension( std::ofstream& os ) const
{
    os << 1 << " " << 2 << "\n";
}


template<>
void Field<Eigen::Vector3d>::writeFieldDimension( std::ofstream& os ) const
{
    os << 1 << " " << 3 << "\n";
}

template<class Type>
void Field<Type>::writeNameField( std::ostream& os ) const
{
    os << nameField_ << ", ";

    if ( mesh_.dimensions().dimension() == 2 )
    {
        os << nameField_ << "(x,y)\n";
    }
    else if ( mesh_.dimensions().dimension() == 3 )
    {
        os << nameField_ << "(x,y,z)\n";
    }
    else
    {
        throw;
    }
}

template<class Type>
void Field<Type>::writeValues( std::ofstream& os ) const
{
    for (int i = 0; i < value_.size(); i++)
    {
        os << i;
        for (int j = 0; j < value_[i].size(); j++ )
        {
            os << " " << value_[i](j);
        }
        os << "\n";
    }
}

template<>
void Field<double>::writeValues( std::ofstream& os ) const
{
    for (int i = 0; i < value_.size(); i++)
    {
        os << i << " " << value_[i] << "\n";
    }
}

template class Field<double>;
template class Field<Eigen::Vector2d>;
template class Field<Eigen::Vector3d>;