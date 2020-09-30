#ifndef __POLYNOMFACTORY_H__
#define __POLYNOMFACTORY_H__

#include "../Polynom/Polynom.h"

#include <memory>

//- Return Polynom class depending on the dimension of the problem (2 or 3)
//- and the order of the mesh (1 or 2)

class PolynomFactory
{
    public:
        static std::vector<Polynom> NewPolynom( const int& dimension, const int& orderMesh )
        {
            if ( dimension == 2 && orderMesh == 1 )
            {
                return std::vector<Polynom>
                ( 
                    { 
                        Polynom( "1-x-y" ), 
                        Polynom( "x" ), 
                        Polynom( "y" )
                    }
                );
            }

            if ( dimension == 3 && orderMesh == 1 )
            {
                return std::vector<Polynom>
                ( 
                    { 
                        Polynom( "1-x-y-z" ),
                        Polynom( "x" ),
                        Polynom( "y" ),
                        Polynom( "z" )
                    } 
                );
            }

            if ( dimension == 2 && orderMesh == 2 )
            {
                return std::vector<Polynom>
                ( 
                    { 
                        Polynom( "1-x-y", "1-2x-2y" ),
                        Polynom( "x", "-1+2x" ),
                        Polynom( "y", "-1+2y" ),
                        Polynom( "x", "1-x-y", 4. ),
                        Polynom( "x", "y", 4. ),
                        Polynom( "y", "1-x-y", 4. )
                    }
                );
            }

            if ( dimension == 3 && orderMesh == 2 )
            {
                return std::vector<Polynom>
                (
                    {
                        Polynom( "1-x-y-z", "1-2x-2y-2z" ),  
                        Polynom( "x", "-1+2x" ),
                        Polynom( "y", "-1+2y" ),
                        Polynom( "z", "-1+2z" ),
                        Polynom( "x", "1-x-y-z", 4. ),
                        Polynom( "x", "y", 4. ),
                        Polynom( "y", "1-x-y-z", 4. ),
                        Polynom( "z", "1-x-y-z", 4. ),
                        Polynom( "y", "z", 4. ),
                        Polynom( "x", "z", 4. )
                    }
                );
            }

            // if ( dimension == 2 && orderMesh == 3 )
            // {
            //     return std::vector<Polynom>
            //     (
            //         {
            //             Polynom( { FirstDegreePolynom(1,-1,-1,0), FirstDegreePolynom(2,-3,-3,0), FirstDegreePolynom(1,-3,-3,0) }, 0.5   ),
            //             Polynom( { FirstDegreePolynom(0,1,0,0),   FirstDegreePolynom(-1,3,0,0),  FirstDegreePolynom(-2,3,0,0)  }, 0.5   ),
            //             Polynom( { FirstDegreePolynom(0,0,1,0),   FirstDegreePolynom(-1,0,3,0),  FirstDegreePolynom(-2,0,3,0)  }, 0.5   ),
            //             Polynom( { FirstDegreePolynom(0,1,0,0),   FirstDegreePolynom(1,-1,-1,0), FirstDegreePolynom(2,-3,-3,0) }, 9./2. ),
            //             Polynom( { FirstDegreePolynom(0,1,0,0),   FirstDegreePolynom(1,-1,-1,0), FirstDegreePolynom(-1,3,0,0)  }, 9./2. ),
            //             Polynom( { FirstDegreePolynom(0,1,0,0),   FirstDegreePolynom(0,0,1,0),   FirstDegreePolynom(-1,3,0,0)  }, 9./2. ),
            //             Polynom( { FirstDegreePolynom(0,1,0,0),   FirstDegreePolynom(0,0,1,0),   FirstDegreePolynom(-1,0,3,0)  }, 9./2. ),
            //             Polynom( { FirstDegreePolynom(0,0,1,0),   FirstDegreePolynom(1,-1,-1,0), FirstDegreePolynom(-1,0,3,0)  }, 9./2. ),
            //             Polynom( { FirstDegreePolynom(0,0,1,0),   FirstDegreePolynom(1,-1,-1,0), FirstDegreePolynom(2,-3,-3,0) }, 9./2. ),
            //             Polynom( { FirstDegreePolynom(1,-1,-1,0), FirstDegreePolynom(0,1,0,0),   FirstDegreePolynom(0,0,1,0)   }, 27.   )
            //         }
            //     );
            // }

            // throw;
        }
};

#endif // __POLYNOMFACTORY_H__