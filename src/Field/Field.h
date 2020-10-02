#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <fstream>

#include <Eigen/Core>

#include "../Mesh/Mesh/Mesh.h"

template<class Type>
class Field;

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

    public:
        Field( const Mesh& mesh, const std::string& nameField, const Type& value );

        // friend std::ostream& operator<< <Type> ( std::ostream& os, const Field& field );
        
        void print( std::ostream& os ) const;

        void write() const;

        void writeMeshDimension( std::ofstream& os ) const;
        void writeNodes( std::ofstream& os ) const;
        void writeInternalIndex( std::ofstream& os ) const;
        void writeFieldDimension( std::ofstream& os ) const;
        void writeNameField( std::ostream& os ) const;
        void writeValues( std::ofstream& os ) const;

        inline const Mesh& mesh() const { return mesh_; }

};

template<class Type>
std::ostream& operator<<( std::ostream& os, const Field<Type>& field )
{
    field.print( os );

    return os;
}

#endif