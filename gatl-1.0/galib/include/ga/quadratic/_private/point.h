/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_QUADRATIC_PRIVATE_POINT_
#define _GA_QUADRATIC_PRIVATE_POINT_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the model for quadratic curves (conic sections).
namespace quadratic
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::quadratic::_private::point<store,e0> struct definition.
 *******************************************************************************************************/

// The base struct for create the point initialization function.
template<typename store, bitmap_t e0>
struct point
{
private:

	// This struct is specialized for the case where the current stored basis blade is a basis vector of the base space.
	template<int cmp, int dummy>
	struct loop
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input)
		{
			(*coefficients) = (*input);
			point<typename store::next,e0>::run( coefficients + 1, input + 1 );
		}
	};

	// This struct is specialized for the case where the current stored basis blade is the basis vector interpreted as the origin of the Euclidean plane.
	template<int dummy>
	struct loop<1,dummy>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input)
		{
			(*coefficients) = 1;
			point<typename store::next,e0>::run( coefficients + 1, input );
		}
	};

	// This struct is specialized for the case where the current stored basis blade is not a basis vector.
	template<int dummy>
	struct loop<2,dummy>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input)
		{
			(*coefficients) = 0;
			point<typename store::next,e0>::run( coefficients + 1, input );
		}
	};

public:

	// The main method
	static _GA_ALWAYS_INLINE
	void run(real_t *coefficients, const real_t *input)
	{
/*TODO Parei aqui!
		loop<
				((ga::_private::bit_count<store::bitmap>::result == 1) ? ((store::bitmap != e0) ? 0 : 1) : 2),
				0
			>::run( coefficients, input );


e_{1} ... e_{n}				<-- os coeficientes dados como entrada s?o colocados aqui
e_{0}						<-- esse kara ? igual a 1/sqrt(2)
e_{1}e_{1} ... e_{1}e_{n}	<-+ esses karas s?o calculados conforme a entrada
e_{2}e_{2} ... e_{2}e_{n}	  | os karas ao quadrado s?o escalados por 1/sqrt(2)
.							  |
.							  |
.							  |
e_{n}e_{n}					<-+
*/

	}
};

// Specialization of point<store,e0> for store equal to store_none.
template<bitmap_t e0>
struct point<store_none,e0>
{
	// The main method
	static _GA_ALWAYS_INLINE
	void run(const real_t *coefficients, const real_t *input)
	{
	}
};

}

}

}

#endif // !_GA_QUADRATIC_PRIVATE_POINT_
