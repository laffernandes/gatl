# GATL: Geometric Algebra Template Library

Contents:
1. [Overview](#1-overview)
2. [Requirements](#2-requirements)
3. [How to "Install" GATL](#3-how-to-install-gatl)
4. [Compiling and Running Examples](#4-compiling-and-running-examples)
5. [Compiling and Running Unit-Tests](#5-compiling-and-running-unit-tests)
6. [Documentation](#6-documentation)
7. [Related Project](#7-related-project)
8. [License](#8-license)


## 1. Overview
GATL is a C++ library for Euclidean, homogeneous, conformal, and arbitrary [Geometric Algebras](https://en.wikipedia.org/wiki/Geometric_algebra).

Geometric Algebra is a powerful mathematical system encompassing many mathematical concepts (e.g., [complex numbers](https://en.wikipedia.org/wiki/Complex_number), [quaternions algebra](https://en.wikipedia.org/wiki/Quaternion_algebra), [Grassmann-Cayley algebra](https://en.wikipedia.org/wiki/Grassmann%E2%80%93Cayley_algebra), and [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates)) under the same framework. Geometric Algebra is mainly based on the algebraic system called [Clifford Algebra](https://en.wikipedia.org/wiki/Clifford_algebra), but with a strong emphasis on geometric interpretation. In Geometric Algebra, subspaces are treated as primitives for computation. As such, it is an appropriate mathematical tool for modeling for solving geometric problems in visual computing. Also, Geometric Algebra has been proven to be capable of representing many types of geometry.

GATL uses template meta-programming to implement the lazy evaluation concept. As such, it is designed to automatically execute low-level algebraic manipulation in the procedures implemented by the users. This way, GATL is capable of performing some optimizations on the program at compile time.


## 2. Requirements
Make sure that you have the following tools before attempting to use GATL.

Required tools:
- Your favorite [C++17](https://en.wikipedia.org/wiki/C%2B%2B14) compiler.

Optional tools:
- [CMake](https://cmake.org) to build and run examples and unit-tests.

Optional C++ libraries:
- [Google Test](https://github.com/google/googletest) to build and run unit-tests.

GATL doesn't have any dependencies other than the C++ standard library.


## 3. How to "Install" GATL
GATL is a pure template library defined in the headers. Therefore, if you just want to use GATL, you can use the header files right away. There is no binary library to link to, and no configured header file.

Use the [git clone](https://git-scm.com/docs/git-clone) command to download the project:
```bash
$ git clone https://github.com/laffernandes/gatl.git [gatl-dir]
```

The directory `<gatl-dir>/cpp/include` must be in the include path of your program, where `<gatl-dir>` is the directory in which you placed GATL's source code.


## 4. Compiling and Running Examples
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


## 5. Compiling and Running Unit-Tests
Unit-tests are under construction. Please, don't try to build them.


## 6. Documentation
Here you find a brief description of the classes, functions, procedures, and operators that are available for the user. The detailed documentation is not ready yet.

Contents:
- [Namespaces](#namespaces)
- [Classes and Data Types](#classes-and-data-types)
- [Utilities Constants and Functions](#utilities-constants-and-functions)
- [Products and Basic Operations](#products-and-basic-operations)
- [Overloaded Operators](#overloaded-operators)
- [Overloaded Mathematical Functions](#overloaded-mathematical-functions)
- [Tools](#tools)
- [Algebra-Specific Declarations](#algebra-specific-declarations)
  - [Signed](#signed)
  - [Euclidean](#euclidean)
  - [Homogeneous/Projective](#homogeneousprojective)
  - [Mikowski/Spacetime](#mikowskispacetime)
  - [Conformal](#conformal)


### Namespaces

| Namespace | Description |
| --- | --- |
| `ga` | The main namespace that encloses all GATL implementations |
| `ga1e`, `ga2e`, `ga3e`, `ga4e`, `ga5e` | The namespace of Euclidean geometric algebra of R<sup>*n*</sup> |
| `ga1h`, `ga2h`, `ga3h`, `ga4h` | The namespace of homogeneous/projective geometric algebra of R<sup>*d*</sup> (*n* = *d* + 1) |
| `ga1m`, `ga2m`, `ga3m` | The namespace of Mikowski/spacetime algebra of R<sup>*d*</sup> (*n* = *d* + 2) |
| `ga1c`, `ga2c`, `ga3c` | The namespace of conformal geometric algebra of R<sup>*d*</sup> (*n* = *d* + 2) |

The namespaces of specific geometric algebras (*e.g.*, `ga3e`, `ga3h`, `ga3m`, and `ga3c`) use the `ga` namespace. Also, they overload all metric operations by setting the `mtr` argument according to their respective spaces.

All above mentioned namespaces declare a nested `detail` namespace. This is the namespace where the magic happens. Don't touch it!

According to the GATL conventions, the header file for each namespace is its name followed by the `.hpp` expresion. For instance, `ga.hpp`, `ga3e.hpp`, `ga3h.hpp`, `ga3m.hpp`, `ga3c.hpp`, and so on.


### Classes and Data Types

| Class | Description |
| --- | --- |
| `clifford_expression<CoefficientType, Expression>` | A Clifford expression |
| `grade_result<Value>` | A class to encode the result of the `grade` function |
| `lazy_context<InputTypes...>` | A class to define lazy arguments for lazy evaluation of Clifford expressions |
| `metric_space<MetricSpaceType>` | Base metric space class |

| Exception Class | Descrition |
| --- | --- |
| `bad_checked_copy` | An exception of this type is thrown when a checked copy fails |
| `not_implemented_error` | Defines the type of objects thrown as exceptions to report errors related to not implemented features |

| Class Alias | Description |
| --- | --- |
| `constant<CoefficientType, IntegralValue>` | Alias for constant scalar Clifford expressions whose coefficient is known in compile time |
| `scalar_clifford_expression<CoefficientType, Coefficient>` | Alias for scalar Clifford expressions |

| Helper for Type Definition | Description |
| --- | --- |
| `full_multivector_t<CoefficientType, VectorSpaceDimensions [, FirstGrade [, LastGrade]]>` | Helper for defining a Clifford expression representing a general multivector with runtime defined coefficients over an *n*-dimensional vector space |
| `full_derived_multivector_t<CoefficientType, Expression>` | Helper for defining a Clifford expression representing a general multivector with runtime defined coefficients in all components of the given Clifford expression |
| `full_kvector_t<CoefficientType, VectorSpaceDimensions, Grade>` | Helper for defining a Clifford expression representing a *k*-vector with runtime defined coefficients over an *n*-dimensional vector space |
| `full_vector_t<CoefficientType, VectorSpaceDimensions>` | Helper for defining a Clifford expression representing a vector with runtime defined coefficients over an *n*-dimensional vector space |
| `scaled_constant_basis_blade_t<CoefficientType, Indices...>` | Helper for defining a Clifford expression representing a scaled compile-time defined basis blade |
| `scaled_constant_basis_vector_t<CoefficientType, Index>` | Helper for defining a Clifford expression representing a scaled compile-time defined basis vector |
| `scaled_basis_blade_t<CoefficientType, FirstPossibleGrade[, LastPossibleGrade]>` | Helper for defining a Clifford expression representing a scaled runtime defined basis blade |
| `scaled_basis_vector_t<CoefficientType>` | Helper for defining a Clifford expression representing a scaled runtime defined basis vector |
| `scaled_scalar_t<CoefficientType>` | Helper for defining a Clifford expression representing a scalar value whose coefficient is unknown in compile time |
| `scaled_pseudoscalar_t<CoefficientType, N>` | Helper for defining a Clifford expression representing a scaled compile-time defined pseudoscalar |
| `unit_constant_basis_blade_t<Indices...>` | Helper for defining a Clifford expression representing an unit compile-time defined basis blade |
| `unit_constant_basis_vector_t<Index>` | Helper for defining a Clifford expression representing an unit compile-time defined basis vector |
| `unit_basis_blade_t<FirstPossibleGrade [, LastPossibleGrade]>` | Helper for defining a Clifford expression representing an unit runtime defined basis blade |
| `unit_basis_vector_t` | Helper for defining a Clifford expression representing an unit runtime defined basis vector |
| `unit_pseudoscalar_t<N>` | Helper for defining a Clifford expression representing an unit compile-time defined pseudoscalar |


### Utilities Constants and Functions

| Constant | Description |
| --- | --- |
| `c<IntegralValue [, CoefficientType]>` | Returns a compile-time defined scalar Clifford expression |

| Function | Description |
| --- | --- |
| `make_lazy_context(inputs...)` | Creates a `lazy_context<InputTypes...>` object |
| `e(index)` | Returns a runtime defined unit basis vector (index values can be defined using `c<IntegralValue>`, too) |
| `scalar(arg)` | Converts the given numerical value to a scalar Clifford expression |
| `pseudoscalar([mtr])` | Returns the compile-time defined unit pseudoscalar of the given space |
| `vector([mtr,] coords...)` | Makes a vector with the given set of coordinates (coordinate values can be defined using `c<IntegralValue>`, too) |


### Products and Basic Operations

| Product | Description |
| --- | --- |
| `cp(lhs, rhs [, mtr])` | Commutator product |
| `dp(lhs, rhs [, tol] [, mtr])` | Delta product |
| `dot(lhs, rhs [, mtr])` | Dot product |
| `gp(lhs, rhs [, mtr])` | Geometric/Clifford product |
| `hip(lhs, rhs [, mtr])` | Hestenes inner product |
| `igp(lhs, rhs [, mtr])` | Inverse geometric/Clifford product (the argument `rhs` must be a versor)  |
| `lcont(lhs, rhs [, mtr])` | Left contraction |
| `op(lhs, rhs [, mtr])` | Outer/Wedge product |
| `rp(lhs, rhs [, mtr])` | Regressive product |
| `rcont(lhs, rhs [, mtr])` | Right contraction |
| `sp(lhs, rhs [, mtr])` | Scalar product of blades |

| Sign-Change Operation | Description |
| --- | --- |
| `conjugation(arg)` | Clifford conjugation |
| `involution(arg)` | Grade involution |
| `reversion(arg)` | Reversion |

| Dualization Operation | Description |
| --- | --- |
| `dual(arg [, pseudoscalar [, mtr]])` | Dualization operation |
| `undual(arg [, pseudoscalar [, mtr]])` | Undualization operation |

| Norm-Based Operation | Description |
| --- | --- |
| `rnorm_sqr(arg [, mtr])` | Squared reverse norm |
| `rnorm(arg [, mtr])` | Reverse norm |
| `inv(arg [, mtr])` | Inverse of the given versor using the squared reverse norm |
| `unit(arg [, mtr])` | Unit Clifford expression under reverse norm |

| Transformation Operation | Description |
| --- | --- |
| `apply_even_versor(versor, arg [, mtr])` | Returns the argument `arg` transformed by the even versor using the sandwich product |
| `apply_odd_versor(versor, arg [, mtr])` | Returns the argument `arg` transformed by the odd versor using the sandwich product |
| `apply_rotor(rotor, arg [, mtr])` | Returns the argument `arg` transformed by the evenrotor using the sandwich product |

| Blade Operation | Description |
| --- | --- |
| `fast_join(lhs, rhs [, tol] [, mtr])` | Returns the join of the given pair of blades using the algorithm developed by [Fontijne (2008)](https://doi.org/10.1007/978-1-84996-108-0_21) |
| `fast_meet_and_join(lhs, rhs [, tol] [, mtr])` | Returns a `std::tuple<T1, T2>` structure where `T1` is the meet and `T2` is the join of the given pair of blades using the algorithm developed by [Fontijne (2008)](https://doi.org/10.1007/978-1-84996-108-0_21) |
| `fast_plunge(lhs, rhs [, tol] [, mtr])` | Returns the plunge of the given pair of blades as described by [Dorst at al. (2007)](http://www.geometricalgebra.net/), and implemented using the `fast_join` function |
| `meet_and_join(lhs, rhs [, tol] [, mtr])` | Returns a `std::tuple<T1, T2>` structure where `T1` is the meet and `T2` is the join of the given pair of blades using the algorithm described by [Dorst at al. (2007)](http://www.geometricalgebra.net/) |
| `plunge(lhs, rhs [, tol] [, mtr])` | Returns the plunge of the given pair of blades as described by [Dorst at al. (2007)](http://www.geometricalgebra.net/), and implemented using the `meet_and_join` function |

| Copy Procedure | Description |
| --- | --- |
| `checked_trivial_copy(input, result, [, tol])` | Copies the coefficients of `input` argument into the `result` when it is possible to perform runtime-checked trivial copy |
| `trivial_copy(input, result, [, tol])` | Copies the coefficients of `input` argument into the `result` argument when it is possible to perform a trivial copy |

| Misc Operation | Description |
| --- | --- |
| `grade(arg [, tol])` | Returns a `grade_result<Value>` structure with the grade of the given argument `arg` |
| `largest_grade(arg [, tol])` | Returns a scalar expression with the largest grade part of the argument `arg` such that it is not zero |
| `take_grade(arg, k)` | Returns the *k*-grade part of the argument `arg` |
| `take_largest_grade(arg [, tol])` | Returns the portion of the argument `arg` with the largest grade |


### Overloaded Operators

| Arithmetic Operator | Description |
| --- | --- |
| `+rhs` | Unary plus |
| `-rhs` | Unary minus |
| `lhs + rhs` | Addition |
| `lhs - rhs` | Subtraction |
| `lhs * rhs` | Geometric/Clifford product (same as `gp(lhs, rhs)`) |
| `lhs / rhs` | Inverse geometric/Clifford product (same as `igp(lhs, rhs)`) |
| `lhs ^ rhs` | Outer/Wedge product (same as `op(lhs, rhs)`) |
| `lhs < rhs` | Left constraction (same as `lcont(lhs, rhs)`) |
| `lhs > rhs` | Right constraction (same as `rcond(lhs, rhs)`) |
| <code>lhs &#124; rhs</code> | Dot product (same as `dot(lhs, rhs)`) |

| Input/Output Operator | Description | 
| --- | --- |
| `os << arg` | Insert formatted output (it uses the `write` function) |


### Overloaded Mathematical Functions

| Trigonometric Function | Description |
| --- | --- |
| `cos(arg)` | Cosine of the scalar argument `arg` (in radians) |
| `sin(arg)` | Sine of the scalar argument `arg` (in radians) |
| `tan(arg)` | Tangent of the scalar argument `arg` (in radians) |

| Hyperbolic Function | Description |
| --- | --- |
| `cosh(arg)` | Hyperbolic cosine of the scalar argument `arg` (in radians) |
| `sinh(arg)` | Hyperbolic sine of the scalar argument `arg` (in radians) |
| `tanh(arg)` | Hyperbolic tangent of the scalar argument `arg` (in radians) |

| Exponential and Logarithmic Function | Description |
| --- | --- |
| `exp(arg [, tol] [, mtr])` | Base-*e* exponential function of the even blade argument `arg` |
| `log(arg)` | Natural logarithm of the scalar argument `arg` |

| Power Function | Description |
| --- | --- |
| `pow(base, exponent)` | Scalar argument `base` raised to the scalar power argument `exponent` |
| `cbrt(arg)` | Cubic root of the scalar argument `arg` |
| `sqrt(arg)` | Square root of the scalar argument `arg` |

| Other Function | Description |
| --- | --- |
| `abs(arg)` | Absolute value of the scalar argument `arg` |


### Tools

| Function | Description |
| --- | --- |
| `default_tolerance<ValueType>()` | Return the standard tolerance value `tol` assumed for the given value type |
| `for_each_basis_vector(arg, f)` | Applies the given function object `f` to the result of dereferencing every basis vector in the given Clifford expression comprised of a single component |
| `for_each_component(arg, f)` | Applies the given function object `f` to the result of dereferencing every component in the given Cliffod expression |
| `write(os, expression, basis_vectors)` | Writes the given Clifford expression into the output stream `os` using the given set of basis vectors  |

| Testing Function | Description |
| --- | --- |
| `is_blade(arg [, tol] [, mtr])` | Returns whether the given Clifford expression is a blade |
| `is_invertible(arg [, tol] [, mtr])` | Returns whether the given Clifford expression is invertible (only for blades and versors) |
| `is_null(arg [, tol] [, mtr])` | Returns whether the given Clifford expression is a null multivector |
| `is_unit(arg [, tol] [, mtr])` | Returns whether the given Clifford expression is an unit multivector |
| `is_versor(arg [, tol] [, mtr])` | Returns whether the given Clifford expression is a versor |
| `is_zero(arg [, tol])` | Returns whether the given Clifford expression is equal to zero |

| Meta-Function | Description |
| --- | --- |
| `largest_possible_grade_v<Expression>` | Helper to deduce the largest possible grade value in the given `Expression` extracted from a Clifford expression |
| `smallest_possible_grade_v<Expression>` | Helper to deduce the smallest possible grade value in the given `Expression` extracted from a Clifford expression |

| Testing Meta-Function | Description |
| --- | --- |
| `is_clifford_expression_v<Type>` | Returns whether the given type is a Clifford expression |
| `is_general_metric_space_v<MetricSpaceType>` | Returns whether the given metric space is general |
| `is_metric_space_v<Type>` | Returns whether the given type is a metric space type |
| `is_orthogonal_metric_space_v<MetricSpaceType>` | Returns whether the given metric space is orthogonal |


### Algebra-Specific Declarations

#### Signed
Specific classes, functions, procedures, and operators of a signed geometric algebras of R<sup>*p, q*</sup>.

| Class | Descrition |
| --- | --- |
| `signed_metric_space<P, Q>` | Orthogonal metric space with signature (*p*, *q*) (*n* = *p* + *q*) |


#### Euclidean
Specific classes, functions, procedures, and operators of Euclidean geometric algebras of R<sup>*n*</sup>.

| Class | Descrition |
| --- | --- |
| `euclidean_metric_space<N>` | Euclidean metric space |

| Constant Value | Descrition |
| --- | --- |
| `e1`, `e2`, ... | Euclidean basis vector (same as `e(c<1>)`,  `e(c<2>)`, ..., `e(c<N>)`) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `Ie` | Unit pseudoscalar of the Euclidean portion of the vector space (same as `I`) |

| Function | Descrition |
| --- | --- |
| `euclidean_vector([mtr,] coords...)` | Makes a Euclidean vector with the given set of coordinates (coordinate values can be defined using `c<IntegralValue>`, too) |

| Operation | Description |
| --- | --- |
| `project(lhs, rhs [, mtr])` | Orthogonal projection of blade `lhs` ontho blade `rhs` |
| `reject(lhs, rhs [, mtr])` | Rejection of blade `lhs` by blade `rhs` |



#### Homogeneous/Projective
Specific classes, functions, procedures, and operators of homogeneous/projective geometric algebras of R<sup>*d*</sup> (*n* = *d* + 1).

| Class | Descrition |
| --- | --- |
| `homogeneous_metric_space<D>` | Homogeneous/Projective metric space |

| Constant Value | Descrition |
| --- | --- |
| `e1`, `e2`, ... | Euclidean basis vector (same as `e(c<1>)`,  `e(c<2>)`, ..., `e(c<D>)`) |
| `ep` | Euclidean homogeneous basis vector (same as `e(c<D + 1>)`, `sp(ep, ep) = 1`) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `Ie` | Unit pseudoscalar of the Euclidean portion of the vector space (same as `rcont(I, ep)`) |

| Function | Descrition |
| --- | --- |
| `euclidean_vector([mtr,] coords...)` | Makes a Euclidean vector with the given set of coordinates (coordinate values can be defined using `c<IntegralValue>`, too) |
| `point([mtr,] coords...)` | Makes a unit point using the given set of coordinates (coordinate values can be defined using `c<IntegralValue>`, too) |

| Parameter Function | Description |
| --- | --- |
| `flat_direction(flat [, mtr])` | The direction parameter of a given flat |
| `flat_moment(flat [, mtr])` | The moment parameter of a given flat |
| `flat_support_vector(flat [, mtr])` | The support vector parameter of a given flat |
| `flat_unit_support_point(flat [, mtr])` | The unit support point parameter of a given flat |

| Transformation Operation | Description |
| --- | --- |
| `translate(direction, flat [, mtr])` | Translate the given flat to a given direction |


#### Mikowski/Spacetime
Specific classes, functions, procedures, and operators of Mikowski/spacetime geometric algebras of R<sup>*d*</sup> (*n* = *d* + 2).

| Class | Descrition |
| --- | --- |
| `minkowski_metric_space<D>` | Minkowski/Spacetime metric space |

| Constant Value | Descrition |
| --- | --- |
| `e1`, `e2`, ... | Euclidean basis vector (same as `e(c<1>)`,  `e(c<2>)`, ..., `e(c<D>)`) |
| `ep` | Positive extra basis vector (same as `e(c<D + 1>)`, `sp(ep, ep) = 1`) |
| `em` | Negative extra basis vector (same as `e(c<D + 2>)`, `sp(em, em) = -1`) |
| `no` | Null vector interpreted as the point at the origin (same as `(em - ep) / c<2>`) |
| `ni` | Null vector interpreted as the point at infinity (same as `ep + em`) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `Ie` | Unit pseudoscalar of the Euclidean portion of the vector space (same as `rcont(I, ep ^ em)`) |

| Function | Descrition |
| --- | --- |
| `euclidean_vector([mtr,] coords...)` | Makes a Euclidean vector with the given set of coordinates (coordinate values can be defined using `c<IntegralValue>`, too) |
| `point([mtr,] coords...)` | Makes a unit point using the given set of coordinates (coordinate values can be defined using `c<IntegralValue>`, too) |

| Parameter Function | Description |
| --- | --- |
| `flat_direction(flat [, mtr])` | The direction parameter of a given flat |
| `flat_location(flat [, mtr])` | The location parameter of a given flat |
| `round_direction(round [, mtr])` | The direction parameter of a given round |
| `round_location(round [, mtr])` | The location parameter of a given round |
| `round_size_sqr(round [, mtr])` | The squared size parameter of a given round |
| `tangent_direction(tangent [, mtr])` | The direction parameter of a given tangent |
| `tangent_location(tangent [, mtr])` | The location parameter of a given tangent |


#### Conformal
Specific classes, functions, procedures, and operators of conformal geometric algebras of R<sup>*d*</sup> (*n* = *d* + 2).

| Class | Descrition |
| --- | --- |
| `conformal_metric_space<D>` | Conformal metric space |

| Constant Value | Descrition |
| --- | --- |
| `e1`, `e2`, ... | Euclidean basis vector (same as `e(c<1>)`,  `e(c<2>)`, ..., `e(c<D>)`) |
| `no` | Null vector interpreted as the point at the origin (same as `e(c<D + 1>)`) |
| `ni` | Null vector interpreted as the point at infinity (same as `e(c<D + 2>)`) |
| `ep` | Positive extra basis vector (same as `(ni / c<2>) - no`) |
| `em` | Negative extra basis vector (same as `(ni / c<2>) + no`) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `Ie` | Unit pseudoscalar of the Euclidean portion of the vector space (same as `rcont(I, no ^ ni)`) |

| Function | Descrition |
| --- | --- |
| `euclidean_vector([mtr,] coords...)` | Makes a Euclidean vector with the given set of coordinates (coordinate values can be defined using `c<IntegralValue>`, too) |
| `point([mtr,] coords...)` | Makes a unit point using the given set of coordinates (coordinate values can be defined using `c<IntegralValue>`, too) |

| Parameter Function | Description |
| --- | --- |
| `flat_direction(flat [, mtr])` | The direction parameter of a given flat |
| `flat_location(flat [, mtr])` | The location parameter of a given flat |
| `round_direction(round [, mtr])` | The direction parameter of a given round |
| `round_location(round [, mtr])` | The location parameter of a given round |
| `round_size_sqr(round [, mtr])` | The squared size parameter of a given round |
| `tangent_direction(tangent [, mtr])` | The direction parameter of a given tangent |
| `tangent_location(tangent [, mtr])` | The location parameter of a given tangent |


## 7. Related Project
Please, visit the GitHub repository of the [**ga-benchmark**](https://github.com/ga-developers/ga-benchmark) project for a benchmark comparing the most popular Geometric Algebra libraries.


## 8. License
This software is licensed under the GNU General Public License v3.0. See the [`LICENSE`](LICENSE) file for details.
