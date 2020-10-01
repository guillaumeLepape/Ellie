# General generation of the .msh file

To generate .msh file from a geometry define in .geo file. To do it, run the following command
```
gmsh -<dimension> -order <order> <file.geo> -o <file_output.msh>
```

## Examples
The Ellie software can process mesh of order 1 or 2.

### `mesh2D.geo` file
```
gmsh -2 -order <order> mesh2D.geo -o mesh2D_order<order>.msh
```

### `mesh3D.geo` file
```
gmsh -3 -order <order> mesh3D.geo -o mesh3D_order<order>.msh
```

# .geo file

The geometry can be of dimension 2 or 3. The interior domain (surface for dimension 2 and volume for dimension 3) has to be named "interior". The boundary conditions (line for dimension 2 and volume for dimension 3) has to be named "Dirichlet<index_Dirichlet>" for Dirichlet conditions and "Neumann<index_Neuman>" for Neumann conditions.

An example of this named interior domain and named boundary conditions can be found in `mesh2D.geo`

```
Physical Surface("interior") = {1};

Physical Line("Dirichlet1") = {1};
Physical Line("Neumann1") = {2};
Physical Line("Dirichlet2") = {3};
Physical Line("Neumann2") = {4};
```
