#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "Element.h"

Element::Element()
{

}

void Element::Read_elements(std::ifstream& mesh_file)
{   
    // Declare string to read the file
    std::string str;

    // Get the first which contains the nbElement
    std::getline( mesh_file, str );
    // Assign number of elements
    nbElement_ = std::stoi( str );
    
    typeElement_.resize( nbElement_ );
    tags_.resize( nbElement_ );
    indexElements_.resize( nbElement_ );

    for (int i = 0 ; i < nbElement_ ; i++)
    {        
        std::getline( mesh_file, str );

        std::vector<std::string> SplitVec;
        boost::split( SplitVec, str, boost::is_any_of(" "), boost::token_compress_on ); // SplitVec == { "hello abc","ABC","aBc goodbye" }
        std::vector<int> oneElement( SplitVec.size() );

        for ( int j = 0; j < oneElement.size(); j++  )
        {
            oneElement[j] = std::stoi( SplitVec[j] );
        }

        typeElement_[i] = oneElement[1];

        std::vector<int> oneTag = std::vector<int>( oneElement.begin() + 3, oneElement.begin() + 3 + oneElement[2] );
        tags_[i] = oneTag;

        std::vector<int> oneIndexElement = std::vector<int>( oneElement.begin() + 3 + oneElement[2], oneElement.end() );
        indexElements_[i] = oneIndexElement;
    }

    // for ( auto i = typeElement_.cbegin(); i != typeElement_.cend(); i++ )
    // {
    //     std::cout << *i << std::endl;
    // }

    // for (auto i = tags_.cbegin(); i != tags_.cend(); i++)
    // {
    //     for (auto j = i->cbegin(); j != i->cend(); j++)
    //     {
    //         std::cout << *j << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for ( auto i = indexElements_.cbegin(); i != indexElements_.cend(); i++ )
    // {
    //     for ( auto j = i->cbegin(); j != i->cend(); j++)
    //     {
    //         std::cout << *j << " ";
    //     }
    //     std::cout << std::endl;
    // }

}

