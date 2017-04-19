close all
clear
clc

% First, let's compile everything with GCC. Some MEX-files cannot be
% created with VC because VC cannot handle deep template structures.
% However, MEX-files created with VC are faster, smaller and they use
% OpenMP. So, let's replace as many MEX-files as we can.

ga_compile('gcc','euclidean',1),   ga_compile('vc','euclidean',1)
ga_compile('gcc','euclidean',2),   ga_compile('vc','euclidean',2)
ga_compile('gcc','euclidean',3),   ga_compile('vc','euclidean',3)
ga_compile('gcc','euclidean',4),   ga_compile('vc','euclidean',4)
ga_compile('gcc','euclidean',5),   ga_compile('vc','euclidean',5)

ga_compile('gcc','homogeneous',1), ga_compile('vc','homogeneous',1)
ga_compile('gcc','homogeneous',2), ga_compile('vc','homogeneous',2)
ga_compile('gcc','homogeneous',3), ga_compile('vc','homogeneous',3)
ga_compile('gcc','homogeneous',4), ga_compile('vc','homogeneous',4)

ga_compile('gcc','conformal',1),   ga_compile('vc','conformal',1)
ga_compile('gcc','conformal',2),   ga_compile('vc','conformal',2)
ga_compile('gcc','conformal',3),   ga_compile('vc','conformal',3)

ga_compile('gcc','conformal_voronoi',2),   ga_compile('vc','conformal_voronoi',2)