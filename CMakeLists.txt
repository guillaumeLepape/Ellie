cmake_minimum_required(VERSION 3.10.2)

# set the project name
project(Utopia VERSION 1.0.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(run
    main.cpp

    src/DerivatePolynom/DerivatePolynom.cpp
    src/DerivatePolynom/DerivatePolynom.h

    src/Determinant/BijectionElements.h
    src/Determinant/JacobianMatrix.h

    src/EvaluationPolynom/EvaluationPolynom.h

    src/Factory/DerivatePolynomFactory.h
    src/Factory/PolynomFactory.h

    src/GaussPoints/GaussPointsFactory.h

    src/Mesh/Dimensions.cpp
    src/Mesh/Dimensions.h

    src/Mesh/DirichletConditions.cpp
    src/Mesh/DirichletConditions.h
    
    src/Mesh/Element.cpp
    src/Mesh/Element.h

    src/Mesh/Internal.cpp
    src/Mesh/Internal.h

    src/Mesh/Mesh.cpp
    src/Mesh/Mesh.h

    src/Mesh/NeumannConditions.cpp
    src/Mesh/NeumannConditions.h
    
    src/Mesh/Node.cpp
    src/Mesh/Node.h

    src/Mesh/PhysicalNames.cpp
    src/Mesh/PhysicalNames.h

    src/Polynom/FirstDegreePolynom.cpp
    src/Polynom/FirstDegreePolynom.h

    src/Polynom/Polynom.cpp
    src/Polynom/Polynom.h
    
    src/Weight/WeightFactory.h
)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(
    run 
    PUBLIC 
    Eigen3::Eigen
)


