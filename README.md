# GATL: Geometric Algebra Template Library
GATL is a C++ library for Euclidean, homogeneous/projective, Mikowski/spacetime, conformal, and arbitrary [geometric algebras](https://en.wikipedia.org/wiki/Geometric_algebra).

Geometric algebra is a powerful mathematical system encompassing many mathematical concepts (*e.g.*, [complex numbers](https://en.wikipedia.org/wiki/Complex_number), [quaternions algebra](https://en.wikipedia.org/wiki/Quaternion_algebra), [Grassmann-Cayley algebra](https://en.wikipedia.org/wiki/Grassmann%E2%80%93Cayley_algebra), and [Plücker coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates)) under the same framework. Geometric algebra is mainly based on the algebraic system called [Clifford algebra](https://en.wikipedia.org/wiki/Clifford_algebra), but with a strong emphasis on geometric interpretation. In geometric algebra, subspaces are treated as primitives for computation. As such, it is an appropriate mathematical tool for modeling and solving geometric problems in physics, chemistry, engineering, and computer science.

GATL uses template meta-programming to implement the [lazy evaluation](https://en.wikipedia.org/wiki/Lazy_evaluation) strategy. This way, GATL is capable of performing some optimizations on the program at compile time. In other words, GATL is designed to automatically execute low-level algebraic manipulation in the procedures described by the users with geometric algebra operations, leading to more efficient programs.

Please, let me know if you want to contribute to this project. [Here](http://www.ic.uff.br/~laffernandes) you will find my contact information.

**Contents:**
1. [Requirements](#1-requirements)
2. [How to "Install" GATL](#2-how-to-install-gatl)
3. [Compiling Examples](#3-compiling-examples)
4. [Compiling and Running Unit-Tests](#4-compiling-and-running-unit-tests)
5. [Documentation](#5-documentation)
6. [Related Project](#6-related-project)
7. [License](#7-license)


## 1. Requirements
Make sure that you have the following tools before attempting to use GATL.

Required tool:
- Your favorite [C++17](https://en.wikipedia.org/wiki/C%2B%2B14) compiler.

Optional tool:
- [CMake](https://cmake.org) to automate installation and to build and run examples and unit-tests.

Optional C++ library:
- [Google Test](https://github.com/google/googletest) to build and run unit-tests.

GATL doesn't have any dependencies other than the [C++ standard library](https://en.cppreference.com/w/cpp/header).


## 2. How to "Install" GATL
GATL is a pure template library defined in the headers. Therefore, if you just want to use GATL, you can use the header files right away. There is no binary library to link to and no configured header file.

Use the [git clone](https://git-scm.com/docs/git-clone) command to download the project, where `<gatl-dir>` must be replaced by the directory in which you want to place GATL's source code, or removed `<gatl-dir>` from the command line to download the project to the `./gatl` directory:
```bash
$ git clone https://github.com/laffernandes/gatl.git <gatl-dir>
```

The directory `<gatl-dir>/cpp/include` must be in the include path of your program, *i.e.*, you have to use the `-I<gatl-dir>/cpp/include` option flag while compiling your program. Alternatively, you can use CMake to copy GATL's header files to the common include directory in your system (*e.g.*, `/usr/local/include`, in Linux) in order to avoid the use of the `-I<gatl-dir>/cpp/include` option flag. The basic steps for installing GATL using CMake look like this in Linux:
```bash
$ cd <gatl-dir>/cpp
$ mkdir build
$ cd build
$ cmake ..
```


## 3. Compiling Examples
The basic steps for configuring and building GATL examples look like this in Linux:
```bash
$ cd <gatl-dir>/cpp/tools/example
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
```

Recall that `<gatl-dir>` is the directory in which you placed GATL's source code.

Assuming a makefile generator was used, the examples are build using:
```bash
$ make -j8
```

The executable files produced by the `make` command start with `gatl_example_`.


## 4. Compiling and Running Unit-Tests
Unit-tests are under construction. Please, don't try to build them.


## 5. Documentation
Here you find a brief description of the namespaces, macros, classes, functions, procedures, and operators available for the user. The detailed documentation is not ready yet.

According to GATL conventions, in the following definitions, `lhs` and `rhs` are informal shorthand for, respectively, the left-hand side and the right-hand side arguments of some procedure. In addition, the `mtr` argument must be an instance of the `metric_space<...>` class, while all other arguments can be either an instances of the `clifford_expression<...>` class or other numerical types (*e.g.*, `double`, `float`, `int`, or instances of third-party classes). Numerical types are automatically converted by GATL to scalar Clifford expression using the `scalar` function.

Contents:
- [Namespaces](#namespaces)
- [Macros](#macros)
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
Namespaces are declarative regions that provide scope to the names of the types, function, variables, *etc.*, inside it. GATL defines the following namespaces.

| Namespace | Description |
| --- | --- |
| `ga` | The main namespace that encloses all GATL implementations |
| `ga1e`, `ga2e`, `ga3e`, `ga4e`, `ga5e` | The namespace of Euclidean geometric algebra of R<sup>*n*</sup> |
| `ga1h`, `ga2h`, `ga3h`, `ga4h` | The namespace of homogeneous/projective geometric algebra of R<sup>*d*</sup> (*n* = *d* + 1) |
| `ga1m`, `ga2m`, `ga3m` | The namespace of Mikowski/spacetime algebra of R<sup>*d*</sup> (*n* = *d* + 2) |
| `ga1c`, `ga2c`, `ga3c` | The namespace of conformal geometric algebra of R<sup>*d*</sup> (*n* = *d* + 2) |

The namespaces of specific geometric algebras (*e.g.*, `ga3e`, `ga3h`, `ga3m`, and `ga3c`) already use the `ga` namespace. In addition, they overload all metric operations presented in the following section by setting the `mtr` argument according to their respective spaces.

All above-mentioned namespaces declare a nested `detail` namespace. This is the namespace where the magic happens. Don't touch it!

According to the GATL conventions, the root directory for the header files that you will include in your program is the `gatl` folder. Also, the header file for each namespace is its name followed by the `.hpp` expression. Putting both conventions together, we have `gatl/ga.hpp`, `gatl/ga3e.hpp`, `gatl/ga3h.hpp`, `gatl/ga3m.hpp`, `gatl/ga3c.hpp`, and so on.


### Macros
Optionally, set the following macros before including GATL headers in your program in order to change some conventions of the library.

| Class | Description |
| --- | --- |
| `GA_DEFAULT_FLOATING_POINT_TYPE` | Defines the floating point type assumed as default by the library (default is `std::double_t`) |
| `GA_DEFAULT_INTEGRAL_TYPE` | Defines the signed integral type assumed as default by the library (default is `std::int64_t`) |
| `GA_MAX_BASIS_VECTOR_INDEX` | Defines the maximum number of basis vectors assumed while performing algebraic manipulations and setting the size of bitsets (default is `63`) |


### Classes and Data Types
The following basic data types are defined in order to assign a meaning to conventional types, like `double`, `int`, and so on.

| Basic Type | Description |
| --- | --- |
| `default_floating_point_t` | The floating point type assumed as default by the library (see `GA_DEFAULT_FLOATING_POINT_TYPE`) |
| `default_integral_t` | The signed integral type assumed as default by the library (see `GA_DEFAULT_INTEGRAL_TYPE`) |
| `bitset_t` | The bitset type used by the library (uses `GA_MAX_BASIS_VECTOR_INDEX` to select the smallest unsigned integral type capable to meet implementation requirements) |
| `grade_t` | The signed integral type used to represent grade values  (same as `default_integral_t`) |
| `index_t` | The unsigned integral type used to represent the index of basis vectors (set to `std::uint64_t`) |
| `ndims_t` | The unsigned integral type used to represent the number of dimensions of the vector space (same as `index_t`) |
| `associative_container_t<ValueType>` | The associative container class used by the `clifford_expression<...>` class to store components of multivectors (set to `std::map<bitset_t, ValueType>`) |
| `sequence_container_t<EntryType, Size>` | The sequence container class used by the `clifford_expression<...>` class to store components of multivectors (set to `std::array<EntryType, Size>`) |

The following classes correspond to the most important structures of GATL.

| Class | Description |
| --- | --- |
| `clifford_expression<CoefficientType, Expression>` | A Clifford expression |
| `grade_result<Value>` | A class to encode the result of the `grade` function |
| `lazy_context<InputTypes...>` | A class to define lazy arguments for lazy evaluation of Clifford expressions |
| `metric_space<MetricSpaceType>` | The base metric space class |

| Exception Class | Descrition |
| --- | --- |
| `bad_checked_copy_exception` | An exception of this type is thrown when a checked copy fails |
| `not_implemented_error` | An exception to report errors related to not implemented features |

For sake of simplicity, GATL provides the following set of class aliases and helper meta-functions to assist type definition. Nevertheless, it is strongly recommended to use the `auto` placeholder type specifier (please, refer to the [C++ specification](https://en.cppreference.com/w/cpp/language/auto) for details) whenever possible.

| Class Alias | Description |
| --- | --- |
| `constant<CoefficientType, IntegralValue>` | An alias for constant scalar Clifford expressions whose coefficient is known in compile time |
| `scalar_clifford_expression<CoefficientType, Coefficient>` | An alias for scalar Clifford expressions |

| Helper for Practical Type Definition | Description |
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
Here you find some useful meta-constants and functions to assist the implementation of your program.

| Constant | Description |
| --- | --- |
| `c<IntegralValue [, CoefficientType]>` | Defines a constant scalar Clifford expression whose coefficient is known in compile time |

| Function | Description |
| --- | --- |
| `make_lazy_context(inputs...)` | Creates a `lazy_context<InputTypes...>` object |
| `e(index)` | Returns a runtime defined unit basis vector (index values can be set using `c<IntegralValue>`, too) |
| `scalar(arg)` | Converts the given numerical value to a scalar Clifford expression |
| `pseudoscalar([mtr])` | Returns the compile-time defined unit pseudoscalar of the given metric space |
| `vector([mtr,] coords...)` | Makes a vector with the given set of coordinates (coordinate values can be set using `c<IntegralValue>`, too) |


### Products and Basic Operations
The following tables present a set of basic products and operations from geometric algebra.

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
| `unit(arg [, mtr])` | Unit under reverse norm |

| Transformation Operation | Description |
| --- | --- |
| `apply_even_versor(versor, arg [, mtr])` | Returns the argument transformed by the even versor using the sandwich product |
| `apply_odd_versor(versor, arg [, mtr])` | Returns the argument transformed by the odd versor using the sandwich product |
| `apply_rotor(rotor, arg [, mtr])` | Returns the argument transformed by the rotor using the sandwich product |

| Blade Operation | Description |
| --- | --- |
| `fast_join(lhs, rhs [, tol] [, mtr])` | Returns the join of the given pair of blades using the algorithm developed by [Fontijne (2008)](https://doi.org/10.1007/978-1-84996-108-0_21) |
| `fast_meet_and_join(lhs, rhs [, tol] [, mtr])` | Returns a `std::tuple<T1, T2>` structure where `T1` is the meet and `T2` is the join of the given pair of blades using the algorithm developed by [Fontijne (2008)](https://doi.org/10.1007/978-1-84996-108-0_21) |
| `fast_plunge(lhs, rhs [, tol] [, mtr])` | Returns the plunge of the given pair of blades as described by [Dorst at al. (2007)](http://www.geometricalgebra.net/), and implemented using the `fast_join` function |
| `meet_and_join(lhs, rhs [, tol] [, mtr])` | Returns a `std::tuple<T1, T2>` structure where `T1` is the meet and `T2` is the join of the given pair of blades using the algorithm described by [Dorst at al. (2007)](http://www.geometricalgebra.net/) |
| `plunge(lhs, rhs [, tol] [, mtr])` | Returns the plunge of the given pair of blades as described by [Dorst at al. (2007)](http://www.geometricalgebra.net/), and implemented using the `meet_and_join` function |

| Misc Operation | Description |
| --- | --- |
| `grade(arg [, tol])` | Returns a `grade_result<Value>` structure encoding the grade of the given argument |
| `largest_grade(arg [, tol])` | Returns a scalar expression with the largest grade part of the argument, such that it is not zero |
| `take_grade(arg, k)` | Returns the *k*-grade part of the argument |
| `take_largest_grade(arg [, tol])` | Returns the portion of the argument with the largest grade |


### Overloaded Operators
GATL overload some C++ operators with the aim of making the writing of source code closer to the writing of mathematical expressions with geometric algebra.

It is important to notice that the precedence and associativity of C++ operators are different than the one assumed in mathematical functions. For instance, one would expect that the outer/wedge product `^` would be evaluated before the addition operation in the following expression `a + b ^ c`, because product precedes addition in math. However, in C++ the addition operator (`+`) precedes the bitwise XOR operator (`^`), leading to possible mistakes while implementing mathematical procedures (please, refer to the [C++ specification](https://en.cppreference.com/w/cpp/language/operator_precedence) for details). As a result, the resulting expression in this example would be `(a + b) ^ c`. The use of parenthesis is strongly recommended in order to avoid those mistakes. By rewriting the example, `a + (b ^ c)` will guarantee the expected behavior.

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
The following tables present the C++ mathematical functions overloaded by GATL with the aim of accepting Clifford expressions as input.

| Trigonometric Function | Description |
| --- | --- |
| `cos(arg)` | Cosine of the scalar argument (in radians) |
| `sin(arg)` | Sine of the scalar argument (in radians) |
| `tan(arg)` | Tangent of the scalar argument (in radians) |

| Hyperbolic Function | Description |
| --- | --- |
| `cosh(arg)` | Hyperbolic cosine of the scalar argument (in radians) |
| `sinh(arg)` | Hyperbolic sine of the scalar argument (in radians) |
| `tanh(arg)` | Hyperbolic tangent of the scalar argument (in radians) |

| Exponential and Logarithmic Function | Description |
| --- | --- |
| `exp(arg [, tol] [, mtr])` | Base-*e* exponential function of the even blade argument |
| `log(arg)` | Natural logarithm of the scalar argument |

| Power Function | Description |
| --- | --- |
| `pow(base, exponent)` | Scalar argument `base` raised to the scalar power argument `exponent` |
| `cbrt(arg)` | Cubic root of the scalar argument |
| `sqrt(arg)` | Square root of the scalar argument |

| Other Function | Description |
| --- | --- |
| `abs(arg)` | Absolute value of the scalar argument |


### Tools
GATL includes a set of useful functions, procedures, and meta-functions to help developers to write their programs.

| Function | Description |
| --- | --- |
| `default_tolerance<ValueType>()` | Return the standard tolerance value `tol` assumed for the given value type |
| `for_each_basis_vector(arg, f)` | Applies the given function object `f` to the result of dereferencing every basis vector in the given Clifford expression comprised of a single component |
| `for_each_component(arg, f)` | Applies the given function object `f` to the result of dereferencing every component in the given Cliffod expression |
| `write(os, expression, basis_vectors)` | Writes the given Clifford expression into the output stream `os` using the given set of basis vectors  |

| Testing Function | Description |
| --- | --- |
| `is_null(arg [, tol] [, mtr])` | Returns whether the given argument is a null multivector |
| `is_unit(arg [, tol] [, mtr])` | Returns whether the given argument is an unit multivector |
| `is_zero(arg [, tol])` | Returns whether the given argument is equal to zero |

| Copy Procedure | Description |
| --- | --- |
| `checked_trivial_copy(input, result, [, tol])` | Copies the coefficients of the `input` argument into the `result` argument when it is possible to perform runtime-checked trivial copy |
| `trivial_copy(input, result, [, tol])` | Copies the coefficients of the `input` argument into the `result` argument when it is possible to perform a trivial copy |

| Meta-Function | Description |
| --- | --- |
| `largest_possible_grade_v<Expression>` | Helper to deduce the largest possible grade value in the given `Expression` parameter extracted from a Clifford expression |
| `smallest_possible_grade_v<Expression>` | Helper to deduce the smallest possible grade value in the given `Expression` parameter extracted from a Clifford expression |

| Testing Meta-Function | Description |
| --- | --- |
| `is_clifford_expression_v<Type>` | Returns whether the given type is a Clifford expression |
| `is_metric_space_v<Type>` | Returns whether the given type is a metric space type |
| `is_general_metric_space_v<MetricSpaceType>` | Returns whether the given metric space is general |
| `is_orthogonal_metric_space_v<MetricSpaceType>` | Returns whether the given metric space is orthogonal |


### Algebra-Specific Declarations
In the following sub-section, you find declarations that are specific of the respective geometric algebra.


#### Signed
Classes and constants of signed geometric algebras of R<sup>*p, q*</sup>.

| Class | Descrition |
| --- | --- |
| `signed_metric_space<P, Q>` | Orthogonal metric space with signature (*p*, *q*) (*n* = *p* + *q*) |

| Constant Value | Descrition |
| --- | --- |
| `_0`, `_1` | Zero and one, respectively (same as `c<0>` and `c<1>`, respectively) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `space` | An instance of the orthogonal metric space class with signature (*p*, *q*) |


#### Euclidean
Classes, constants, functions, and operations of Euclidean geometric algebras of R<sup>*n*</sup>. They are available in the following namespaces: `ga1e`, `ga2e`, `ga3e`, `ga4e`, and `ga5e`.

| Class | Descrition |
| --- | --- |
| `euclidean_metric_space<N>` | Euclidean metric space |

| Constant Value | Descrition |
| --- | --- |
| `_0`, `_1` | Zero and one, respectively (same as `c<0>` and `c<1>`, respectively) |
| `e1`, `e2`, ... | Euclidean basis vector (same as `e(c<1>)`,  `e(c<2>)`, ..., `e(c<N>)`) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `Ie` | Unit pseudoscalar of the Euclidean portion of the vector space (same as `I`) |
| `space` | An instance of the Euclidean metric space class |

| Function | Descrition |
| --- | --- |
| `euclidean_vector([mtr,] coords...)` | Makes an Euclidean vector with the given set of coordinates (coordinate values can be set using `c<IntegralValue>`, too) |

| Operation | Description |
| --- | --- |
| `project(lhs, rhs [, mtr])` | Orthogonal projection of blade `lhs` ontho blade `rhs` |
| `reject(lhs, rhs [, mtr])` | Rejection of blade `lhs` by blade `rhs` |


#### Homogeneous/Projective
Classes, constants, functions, and operations of homogeneous/projective geometric algebras of R<sup>*d*</sup> (*n* = *d* + 1). They are available in the following namespaces: `ga1h`, `ga2h`, `ga3h`, and `ga4h`.

| Class | Descrition |
| --- | --- |
| `homogeneous_metric_space<D>` | Homogeneous/Projective metric space |

| Constant Value | Descrition |
| --- | --- |
| `_0`, `_1` | Zero and one, respectively (same as `c<0>` and `c<1>`, respectively) |
| `e1`, `e2`, ... | Euclidean basis vector (same as `e(c<1>)`,  `e(c<2>)`, ..., `e(c<D>)`) |
| `ep` | Positive extra basis vector interpreted as the point at the origin (same as `e(c<D + 1>)`) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `Ie` | Unit pseudoscalar of the Euclidean portion of the vector space (same as `rcont(I, ep)`) |
| `space` | An instance of the homogeneous/projective metric space class |

| Function | Descrition |
| --- | --- |
| `euclidean_vector([mtr,] coords...)` | Makes an Euclidean vector with the given set of coordinates (coordinate values can be set using `c<IntegralValue>`, too) |
| `point([mtr,] coords...)` | Makes an unit point using the given set of coordinates (coordinate values can be set using `c<IntegralValue>`, too) |

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
Classes, constants, functions, and operations of Mikowski/spacetime geometric algebras of R<sup>*d*</sup> (*n* = *d* + 2). They are available in the following namespaces: `ga1m`, `ga2m`, and `ga3m`.

| Class | Descrition |
| --- | --- |
| `minkowski_metric_space<D>` | Minkowski/Spacetime metric space |

| Constant Value | Descrition |
| --- | --- |
| `_0`, `_1` | Zero and one, respectively (same as `c<0>` and `c<1>`, respectively) |
| `e1`, `e2`, ... | Euclidean basis vector (same as `e(c<1>)`,  `e(c<2>)`, ..., `e(c<D>)`) |
| `ep` | Positive extra basis vector (same as `e(c<D + 1>)`) |
| `em` | Negative extra basis vector (same as `e(c<D + 2>)`) |
| `no` | Null vector interpreted as the point at the origin (same as `(em - ep) / c<2>`) |
| `ni` | Null vector interpreted as the point at infinity (same as `ep + em`) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `Ie` | Unit pseudoscalar of the Euclidean portion of the vector space (same as `rcont(I, ep ^ em)`) |
| `space` | An instance of the Minkowski/spacetime metric space class |

| Function | Descrition |
| --- | --- |
| `euclidean_vector([mtr,] coords...)` | Makes an Euclidean vector with the given set of coordinates (coordinate values can be set using `c<IntegralValue>`, too) |
| `point([mtr,] coords...)` | Makes an unit point using the given set of coordinates (coordinate values can be set using `c<IntegralValue>`, too) |

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
Classes, constants, functions, and operations of conformal geometric algebras of R<sup>*d*</sup> (*n* = *d* + 2). They are available in the following namespaces: `ga1c`, `ga2c`, and `ga3c`.

| Class | Descrition |
| --- | --- |
| `conformal_metric_space<D>` | Conformal metric space |

| Constant Value | Descrition |
| --- | --- |
| `_0`, `_1` | Zero and one, respectively (same as `c<0>` and `c<1>`, respectively) |
| `e1`, `e2`, ... | Euclidean basis vector (same as `e(c<1>)`,  `e(c<2>)`, ..., `e(c<D>)`) |
| `no` | Null vector interpreted as the point at the origin (same as `e(c<D + 1>)`) |
| `ni` | Null vector interpreted as the point at infinity (same as `e(c<D + 2>)`) |
| `ep` | Positive extra basis vector (same as `(ni / c<2>) - no`) |
| `em` | Negative extra basis vector (same as `(ni / c<2>) + no`) |
| `I` | Unit pseudoscalar (same as `pseudoscalar()`) |
| `Ie` | Unit pseudoscalar of the Euclidean portion of the vector space (same as `rcont(I, no ^ ni)`) |
| `space` | An instance of the conformal metric space class |

| Function | Descrition |
| --- | --- |
| `euclidean_vector([mtr,] coords...)` | Makes an Euclidean vector with the given set of coordinates (coordinate values can be set using `c<IntegralValue>`, too) |
| `point([mtr,] coords...)` | Makes an unit point using the given set of coordinates (coordinate values can be set using `c<IntegralValue>`, too) |

| Parameter Function | Description |
| --- | --- |
| `flat_direction(flat [, mtr])` | The direction parameter of a given flat |
| `flat_location(flat [, mtr])` | The location parameter of a given flat |
| `round_direction(round [, mtr])` | The direction parameter of a given round |
| `round_location(round [, mtr])` | The location parameter of a given round |
| `round_size_sqr(round [, mtr])` | The squared size parameter of a given round |
| `tangent_direction(tangent [, mtr])` | The direction parameter of a given tangent |
| `tangent_location(tangent [, mtr])` | The location parameter of a given tangent |


## 6. Related Project
Please, visit the GitHub repository of the [**ga-benchmark**](https://github.com/ga-developers/ga-benchmark) project for a benchmark comparing the most popular geometric algebra libraries.


## 7. License
This software is licensed under the GNU General Public License v3.0. See the [`LICENSE`](LICENSE) file for details.
