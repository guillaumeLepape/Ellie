lc = 0.5;

Point(1) = {0, 0, 0, lc};
//+
Point(2) = {0, 0, 1, lc};
//+
Point(3) = {0, 1, 0, lc};
//+
Point(4) = {0, 1, 1, lc};
//+
Point(5) = {1, 0, 0, lc};
//+
Point(6) = {1, 0, 1, lc};
//+
Point(7) = {1, 1, 0, lc};
//+
Point(8) = {1, 1, 1, lc};

//+
Line(1) = {2, 6};
//+
Line(2) = {6, 5};
//+
Line(3) = {5, 1};
//+
Line(4) = {1, 2};
//+
Line(5) = {2, 4};
//+
Line(6) = {4, 8};
//+
Line(7) = {8, 6};
//+
Line(8) = {8, 7};
//+
Line(9) = {7, 5};
//+
Line(10) = {7, 3};
//+
Line(11) = {3, 4};
//+
Line(12) = {3, 1};
//+
Line Loop(1) = {10, 11, 6, 8};
//+
Plane Surface(1) = {1};
//+
Line Loop(2) = {12, 4, 5, -11};
//+
Plane Surface(2) = {2};
//+
Line Loop(3) = {3, -12, -10, 9};
//+
Plane Surface(3) = {3};
//+
Line Loop(4) = {1, -7, -6, -5};
//+
Plane Surface(4) = {4};
//+
Line Loop(5) = {8, 9, -2, -7};
//+
Plane Surface(5) = {5};
//+
Line Loop(6) = {3, 4, 1, 2};
//+
Plane Surface(6) = {6};
//+
Physical Surface("Dirichlet1") = {2, 1, 5}; 
Physical Surface("Dirichlet2") = {3, 4, 6};
//+
Surface Loop(1) = {4, 6, 3, 2, 1, 5};
//+
Volume(1) = {1};
//+
Physical Volume("interior") = {1};
