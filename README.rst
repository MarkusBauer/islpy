.. image:: https://badge.fury.io/py/islpy.png
    :target: http://pypi.python.org/pypi/islpy

islpy is a Python wrapper around Sven Verdoolaege's `isl
<http://www.kotnet.org/~skimo/isl/>`_, a library for manipulating sets and
relations of integer points bounded by linear constraints.

Supported operations on sets include

* intersection, union, set difference,
* emptiness check,
* convex hull,
* (integer) affine hull,
* integer projection,
* computing the lexicographic minimum using parametric integer programming,
* coalescing, and
* parametric vertex enumeration.

It also includes an ILP solver based on generalized basis reduction, transitive
closures on maps (which may encode infinite graphs), dependence analysis and
bounds on piecewise step-polynomials.

Islpy comes with comprehensive `documentation <http://documen.tician.de/islpy>`_.

*Requirements:* islpy needs a C++ compiler to build. GMP, which used to be
a dependency, is no longer required.

Building
--------
By default, islpy builds without any compiler optimization. On linux, best thing I
found is using Clang + link-time optimization. Setup clang and run:
``./clang-build.sh``

If you do not want to deal with Clang/LTO, enable classical optimization at least::

    python configure.py --cxxflags "-O3" --ldflags "-O3"
    python setup.py build

