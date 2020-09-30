#ifndef __DERIVATEPOLYNOMFACTORY_H__
#define __DERIVATEPOLYNOMFACTORY_H__

#include "../DerivatePolynom/DerivatePolynom.h"

//- Return DerivatePolynom class depending on the dimension of the problem (2 or 3)
//- and the order of the mesh (1 and 2)

class DerivatePolynomFactory
{
    public:
        static std::vector<DerivatePolynom> NewDerivatePolynom( const int& dimension, const int& orderMesh )
        {
            if ( dimension == 2 && orderMesh == 1 )
                return std::vector<DerivatePolynom>
                (
                    {
                        DerivatePolynom( { "-1", "-1", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( -1,0,0,0 ), FirstDegreePolynom( -1,0,0,0 ), FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "1", "0", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 1,0,0,0 ),  FirstDegreePolynom( 0,0,0,0 ),  FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "0", "1", "0" } )
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,0 ),  FirstDegreePolynom( 1,0,0,0 ),  FirstDegreePolynom( 0,0,0,0 ) } )
                    }
                );
                
            if ( dimension == 3 && orderMesh == 1 )
                return std::vector<DerivatePolynom>
                (
                    {
                        DerivatePolynom( { "-1", "-1", "-1" } ),
                        // DerivatePolynom( { FirstDegreePolynom( -1,0,0,0 ), FirstDegreePolynom( -1,0,0,0 ), FirstDegreePolynom( -1,0,0,0 ) } ),
                        DerivatePolynom( { "1", "0", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 1,0,0,0 ),  FirstDegreePolynom( 0,0,0,0 ),  FirstDegreePolynom( 0,0,0,0 )  } ),
                        DerivatePolynom( { "0", "1", "0" } ), 
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,0 ),  FirstDegreePolynom( 1,0,0,0 ),  FirstDegreePolynom( 0,0,0,0 )  } ),                 
                        DerivatePolynom( { "0", "0", "1" } ) 
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,0 ),  FirstDegreePolynom( 0,0,0,0 ),  FirstDegreePolynom( 1,0,0,0 )  } ) 
                    }   
                );

            if ( dimension == 2 && orderMesh == 2 )
                return std::vector<DerivatePolynom>
                (
                    {
                        DerivatePolynom( { "-3 + 4x + 4y", "-3 + 4x + 4y", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( -3,4,4,0 ),  FirstDegreePolynom( -3,4,4,0 ),  FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "-1 + 4x", "0", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( -1,4,0,0 ),  FirstDegreePolynom( 0,0,0,0 ),   FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "0", "-1 + 4y", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,0 ),   FirstDegreePolynom( -1,0,4,0 ),  FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "4 - 8x - 4y", "-4x", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 4,-8,-4,0 ), FirstDegreePolynom( 0,-4,0,0 ),  FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "4y", "4x", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,4,0 ),   FirstDegreePolynom( 0,4,0,0 ),   FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "-4y", "4 - 4x - 8", "0" } )
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,-4,0 ),  FirstDegreePolynom( 4,-4,-8,0 ), FirstDegreePolynom( 0,0,0,0 ) } )
                    }
                );

            if ( dimension == 3 && orderMesh == 2 )
                return std::vector<DerivatePolynom>
                (
                    {
                        DerivatePolynom( { "-3 + 4x + 4y + 4z", "-3 + 4x + 4y + 4z", "-3 + 4x + 4y + 4z" } ),
                        // DerivatePolynom( { FirstDegreePolynom( -3,4,4,4 ),  FirstDegreePolynom( -3,4,4,4 ),  FirstDegreePolynom( -3,4,4,4 ) } ),
                        DerivatePolynom( { "-1 + 4x", "0", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( -1,4,0,0 ),  FirstDegreePolynom( 0,0,0,0 ),   FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "0", "-1 + 4y", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,0 ),   FirstDegreePolynom( -1,0,4,0 ),  FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "0", "0", "-1 + 4z" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,0 ),   FirstDegreePolynom( 0,0,0,0 ),  FirstDegreePolynom( -1,0,0,4 ) } ),
                        DerivatePolynom( { "4 - 8x - 4y - 4z", "-4x",  "-4x" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 4,-8,-4,0 ), FirstDegreePolynom( 0,-4,0,0 ),  FirstDegreePolynom( 0,-4,0,0 ) } ),
                        DerivatePolynom( { "4y", "4x", "0" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,4,0 ),   FirstDegreePolynom( 0,4,0,0 ),   FirstDegreePolynom( 0,0,0,0 ) } ),
                        DerivatePolynom( { "-4y", "4 - 4x - 8y - 4z", "-4y" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,-4,0 ),  FirstDegreePolynom( 4,-4,-8,-4 ), FirstDegreePolynom( 0,0,-4,0 ) } ),
                        DerivatePolynom( { "-4z", "-4z", "4 - 4x - 4y - 8z" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,-4 ),  FirstDegreePolynom( 0,0,0,-4 ), FirstDegreePolynom( 4,-4,-4,-8 ) } ),
                        DerivatePolynom( { "0", "4z", "4y" } ),
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,0 ),   FirstDegreePolynom( 0,0,0,4 ),   FirstDegreePolynom( 0,0,4,0 ) } ),
                        DerivatePolynom( { "4z", "0", "4x" } )
                        // DerivatePolynom( { FirstDegreePolynom( 0,0,0,4 ),   FirstDegreePolynom( 0,0,0,0 ),   FirstDegreePolynom( 0,4,0,0 ) } )
                    }
                );

            // throw;
        }
};  

#endif // __DERIVATEPOLYNOMFACTORY_H__