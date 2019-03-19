# GATL: Geometric Algebra Template Library

## Overview
GATL is a C++ library for Euclidean, homogeneous, conformal, and arbitrary [Geometric Algebras](https://en.wikipedia.org/wiki/Geometric_algebra).

Geometric Algebra is a powerful mathematical system encompassing many mathematical concepts (e.g., [complex numbers](https://en.wikipedia.org/wiki/Complex_number), [quaternions algebra](https://en.wikipedia.org/wiki/Quaternion_algebra), [Grassmann-Cayley algebra](https://en.wikipedia.org/wiki/Grassmann%E2%80%93Cayley_algebra), and [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates)) under the same framework. Geometric Algebra is mainly based on the algebraic system called [Clifford Algebra](https://en.wikipedia.org/wiki/Clifford_algebra), but with a strong emphasis on geometric interpretation. In Geometric Algebra, subspaces are treated as primitives for computation. As such, it is an appropriate mathematical tool for modeling for solving geometric problems in visual computing. Also, Geometric Algebra has been proven to be capable of representing many types of geometry.

GATL uses template meta-programming to implement the lazy evaluation concept. As such, it is designed to automatically execute low-level algebraic manipulation in the procedures implemented by the users. This way, GATL is capable of performing some optimizations on the program at compile time.

Contents:
1. [Requirements](#requirements)
2. [How to "Install" GATL](#how-to-install-gatl)
3. [Compiling and Running Examples](#compiling-and-running-examples)
4. [Compiling and Running Unit-Tests](#compiling-and-running-unit-tests)
5. [Related Project](#related-project)
6. [License](#license)


## Requirements
Make sure that you have the following tools before attempting to use GATL.

Required tools:
- Your favorite [C++17](https://en.wikipedia.org/wiki/C%2B%2B14) compiler.

Optional tools:
- [CMake](https://cmake.org) to build and run examples and unit-tests.

Optional C++ libraries:
- [Google Test](https://github.com/google/googletest) to build and run unit-tests.

GATL doesn't have any dependencies other than the C++ standard library.


## How to "Install" GATL
GATL is a pure template library defined in the headers. Therefore, if you just want to use GATL, you can use the header files right away. There is no binary library to link to, and no configured header file.

Use the [git clone](https://git-scm.com/docs/git-clone) command to download the project:
```bash
$ git clone https://github.com/laffernandes/gatl.git [gatl-dir]
```

The directory `<gatl-dir>/cpp/include` must be in the include path of your program, where `<gatl-dir>` is the directory in which you placed GATL's source code.


## Compiling and Running Examples
The basic steps for configuring and building GATL examples look like this in Linux:
```bash
$ cd <gatl-dir>/cpp/tools/example
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
```
Here, `<gatl-dir>` is the directory in which you placed GATL's source code.

Assuming a makefile generator was used:
```bash
$ make -j8
```

The executable files produced by the `make` command start with `gatl_example_`.


## Compiling and Running Unit-Tests
Unit-tests are under construction. Please, don't try to build them.


## Related Project
Please, visit the GitHub repository of the [**ga-benchmark**](https://github.com/ga-developers/ga-benchmark) project for a benchmark comparing the most popular Geometric Algebra libraries.


## License
This software is licensed under the GNU General Public License v3.0. See the [`LICENSE`](LICENSE) file for details.
