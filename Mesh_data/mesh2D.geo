//+
Point(1) = {0, 0, 0, 0.5};
//+
Point(2) = {1, 0, 0, 0.5};
//+
Point(3) = {1, 1, 0, 0.5};
//+
Point(4) = {0, 1, 0, 0.5};
//+

Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,1};  
//+
Line Loop(1) = {1, 2, 3, 4};
//+
Plane Surface(1) = {1};
//+
Physical Surface("interior") = {1};
//+
Physical Line("Dirichlet1") = {1,2};
Physical Line("Dirichlet2") = {3,4};
