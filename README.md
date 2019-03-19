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
5. [Documentation](#documentation)
6. [Related Project](#related-project)
7. [License](#license)


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


## Documentation
Here you find a brief description of the implemented functions, operators, and classes. The detailed documentation is not ready yet.

| Namespace | Description |
| --- | --- |
| `ga` | The main namespace that encloses all GATL functions, operations, and classes |
| `ga::detail` | The namespace where the magic happens (don't touch it!) |

| Arithmetic Operator | Description |
| --- | --- |
| `+rhs` | Unary plus |
| `-rhs` | Unary minus |
| `lhs + rhs` | Addition |
| `lhs - rhs` | Subtraction |
| `lhs * rhs` | Geometric/Clifford product (same as `gp(lhs, rhs)`) |
| `lhs ^ rhs` | Outer/Wedge product (same as `op(lhs, rhs)`) |
| `lhs < rhs` | Left constraction (same as `lcont(lhs, rhs)`) |
| `lhs > rhs` | Right constraction (same as `rcond(lhs, rhs)`) |
| <code>lhs &#124; rhs</code> | Dot product (same as `dot(lhs, rhs)`) |

| Product | Description |
| --- | --- |
| `dot(lhs, rhs)`, `dot(lhs, rhs, mtr)` | Dot product |
| `gp(lhs, rhs)`, `gp(lhs, rhs, mtr)` | Geometric/Clifford product |
| `hip(lhs, rhs)`, `hip(lhs, rhs, mtr)` | Hestenes inner product |
| `lcont(lhs, rhs)`, `lcont(lhs, rhs, mtr)` | Left contraction |
| `op(lhs, rhs)`, `op(lhs, rhs, mtr)` | Outer/Wedge product |
| `rcont(lhs, rhs)`, `rcont(lhs, rhs, mtr)` | Right contraction |
| `rp(lhs, rhs)`, `rp(lhs, rhs, mtr)` | Regressive product |
| `sp(lhs, rhs)`, `sp(lhs, rhs, mtr)` | Scalar product of blades |

| Sign-change Operation | Description |
| --- | --- |
| `conjugation(arg)` | Clifford conjugation |
| `involution(arg)` | Grade involution |
| `reversion(arg)` | Reversion |

| Trigonometric Function | Description |
| --- | --- |
| `cos(arg)` | Returns the cosine of the scalar argument `arg` (in radians) |
| `sin(arg)` | Returns the sine of the scalar argument `arg` (in radians) |
| `tan(arg)` | Returns the tangent of the scalar argument `arg` (in radians) |

| Hyperbolic Function | Description |
| --- | --- |
| `cosh(arg)` | Returns the hyperbolic cosine of the scalar argument `arg` (in radians) |
| `sinh(arg)` | Returns the hyperbolic sine of the scalar argument `arg` (in radians) |
| `tanh(arg)` | Returns the hyperbolic tangent of the scalar argument `arg` (in radians) |

| Other Mathematical Function | Description |
| --- | --- |
| `abs(arg)` | Returns the absolute value of the scalar argument `arg` |
| `cbrt(arg)` | Returns the cubic root of the scalar argument `arg` |
| `exp(arg)` | Returns the base-e exponential function of the scalar argument `arg` |
| `log(arg)` | Returns the natural logarithm of the scalar argument `arg` |
| `pow(base, exponent)` | Returns the scalar argument `base` raised to the scalar power argument `exponent` |
| `sqrt(arg)` | Returns the square root of the scalar argument `arg` |

| Class | Description |
| --- | --- |
| `template<typename CoefficientType, typename Expression> class clifford_expression` | Some Clifford expression defined by `Expression` and having real coefficients of type `CoefficientType` |
| `template<typename... InputTypes> class lazy_context` | A structure to define lazy arguments for lazy evaluation of Clifford expressions (see `make_lazy_context` function) |
| `template<typename MetricSpaceType> class metric_space` | Base metric space typename |

| Helper Class | Description |
| --- | --- |
| `template<typename CoefficientType, typename Coefficient> using scalar_clifford_expression` | Helper for defining a scalar Clifford expression type |
| `template<typename CoefficientType, default_integral_t Value> using constant` | Helper for defining a compile-time defined constant scalar Clifford expression type |

| Helper for Type Definition | Description |
| --- | --- |
| `template<typename CoefficientType> using scaled_scalar_t` | Helper for defining a scalar value type |

| Helper Testing Meta-Function | Description |
| --- | --- |
| `template<typename Type> constexpr bool is_clifford_expression_v` | Returns whether the given type is a Clifford expression |
| `template<typename Type> constexpr bool is_metric_space_v` | Returns whether the given type is a metric space type |
| `template<typename MetricSpaceType> constexpr bool is_general_metric_space_v` | Returns whether the given metric space is general |
| `template<typename MetricSpaceType> constexpr bool is_orthogonal_metric_space_v` | Returns whether the given metric space is orthogonal |

| Other Helper Meta-Function | Description |
| --- | --- |
| `template<default_integral_t Value, typename CoefficientType = default_integral_t> constexpr auto c` | Returns a compile-time defined constant scalar Clifford expression |

| Helper Function | Description |
| --- | --- |
| `make_lazy_context(InputTypes const &... inputs)` | Created a `lazy_context<InputTypes...>` object |
| `scalar(ValueType const &arg)` | Converts the given native value type to scalar Clifford expression |


## Related Project
Please, visit the GitHub repository of the [**ga-benchmark**](https://github.com/ga-developers/ga-benchmark) project for a benchmark comparing the most popular Geometric Algebra libraries.


## License
This software is licensed under the GNU General Public License v3.0. See the [`LICENSE`](LICENSE) file for details.
