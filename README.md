# Ellie
Finite element software in C++. Using gmsh to generate mesh and output .VTK files.

## Clone the repository
Since this git repository contains the submodule eigen, the clone command is the following
```
git clone --recurse-submodules <url>
```

## Compilation
cmake version 3.18.3

To compile this project, go to the Ellie folder and tap the following commands
```
mkdir build 
cd build 
cmake ..
make
```

Then to run the code 
```
cd ..
./build/run
```