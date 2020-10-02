#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <fstream>

#include <Eigen/Core>

#include "../Mesh/Mesh/Mesh.h"

template<class Type>
class Field;

template<class Type>
Field<Type> operator+
(
    const Field<Type>& field1,
    const Field<Type>& field2
);

template<class Type>
std::ostream& operator<<
(
    std::ostream& os, 
    const Field<Type>& field
);

template<class Type>
class Field
{
    private:
        const Mesh& mesh_;

        std::string nameField_;

        // Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> value_; 
        std::vector<Type> value_;

        void writeMeshDimension( std::ofstream& os ) const;
        void writeNodes( std::ofstream& os ) const;
        void writeInternalIndex( std::ofstream& os ) const;
        void writeFieldDimension( std::ofstream& os ) const;
        void writeNameField( std::ostream& os ) const;
        void writeValues( std::ofstream& os ) const;

        void print( std::ostream& os ) const;

    public:
        Field( const Mesh& mesh, const std::string& nameField, const std::vector<Type>& value );
        Field( const Mesh& mesh, const std::string& nameField, const Type& value );
        
        void write() const;

        inline const Mesh& mesh() const { return mesh_; }

        friend std::ostream& operator<< <Type> ( std::ostream& os, const Field& field );
        friend Field operator+<Type>( const Field& field1, const Field& field2 );

};

template<class Type>
std::ostream& operator<<( std::ostream& os, const Field<Type>& field )
{
    field.print( os );

    return os;
}

template<class Type>
Field<Type> operator+( const Field<Type>& field1, const Field<Type>& field2 )
{
    if ( field1.value_.size() != field2.value_.size() )
    {
        throw;
    }

    std::vector<Type> field_value( field1.value_.size() );

    for ( int i = 0; i < field1.value_.size(); i++ )
    {
        field_value[i] = field1.value_[i] + field2.value_[i];
    }

    return Field<Type>( field1.mesh_, field1.nameField_ + "+" + field2.nameField_, field_value );
}

#endif