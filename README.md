Trust region algorithm - A derivative free algorithm for function approximation
=========================================

An algorithm for modeling any function inside a trust region with quadratic polynomieals as outlined in: "Distributed derivative free optimization" by Giuliani UFSC 2016 which is based on A. Conn's Derivative free optimization.

The algorithm works by chosing a center point and a trust region radius around the center point. Then the set of points is completed (either with points given as input or the algorithm finds new feasible points) in such a way that the set is deemed to be 'well-poised'. See Conn's book for a definition of well-poisedness. From the set of points we can uniqueliy determine a polynomial that fits any function's values in the given points. This might prove useful for approximating functions and their derivatives whose evaluations are costly (e.g. black-box simulations).

Dependencies
------------

Eigen3 library: http://eigen.tuxfamily.org/

This library is header-only so the installation is simple.

Qt5 library

Install Qt5 via terminal with:
sudo apt-get install qtbase5-dev


Questions
---------

Contact Hilmar Magnússon at hilmarmag[at]gmail.com