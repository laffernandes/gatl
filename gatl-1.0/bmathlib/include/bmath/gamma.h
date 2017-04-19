/*
 * Copyright (C) 2010 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_GAMMA_
#define _BMATH_GAMMA_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * la::gamma_function_error class definition.
 *******************************************************************************************************/

// Some gamma function error definition.
class gamma_function_error : public std::runtime_error
{
public:

	// Class constructor.
	gamma_function_error(const std::string &message) : std::runtime_error( message )
	{
	}
};

/*******************************************************************************************************
 * Gamma function and incomplete gamma function implementations.
 *******************************************************************************************************/

// Returns the value ln[fi(x)] for x > 0.
template<typename real_type>
inline
real_type gammln(const real_type &x)
{
	const real_type cof[6] = { 76.18009172947146, -86.50532032941677, 24.01409824083091, -1.231739572450155, 0.1208650973866179e-2, -0.5395239384953e-5 };
	
	real_type tmp = x + static_cast<real_type>( 5.5 );
	tmp -= (x + static_cast<real_type>( 0.5 )) * log( tmp );

	real_type y = x;
	real_type ser = static_cast<real_type>( 1.000000000190015 );
	for (int j=0; j<=5; ++j)
	{
		ser += cof[j] / ++y;
	}

	return log( static_cast<real_type>( 2.5066282746310005 ) * ser / x ) - tmp;
}

// Returns the incomplete gamma function P(a; x) evaluated by its series representation as gamser. Also returns ln fi(a) as gln.
template<typename real_type>
inline
void gser(real_type &gamser, real_type &gln, const real_type &a, const real_type &x)
{
	static const int ITMAX = 100;
	const real_type EPS = static_cast<real_type>( 3.0e-7 );

	gln = gammln( a );

	if (x <= static_cast<real_type>( 0 ))
	{
		if (x < static_cast<real_type>( 0 ))
		{
			throw gamma_function_error( "'x' less than 0 in routine 'gser'." );
		}
		gamser = static_cast<real_type>( 0 );
	}
	else
	{
		real_type ap = a;
		
		real_type del, sum;
		del = sum = static_cast<real_type>( 1 ) / a;

		for (int n=1; n<=ITMAX; ++n)
		{
			++ap;
			del *= x / ap;
			sum += del;
			if (abs( del ) < (abs( sum ) * EPS))
			{
				gamser = sum * exp( (a * log( x )) - x - gln );
				return;
			}
		}
		throw gamma_function_error( "'a' too large, 'ITMAX' too small in routine 'gser'." );
	}
}

// Returns the incomplete gamma function Q(a; x) evaluated by its continued fraction representation as gammcf. Also returns ln (a) as gln.
template<typename real_type>
inline
void gcf(real_type &gammcf, real_type &gln, const real_type &a, const real_type &x)
{
	static const int ITMAX = 100;
	const real_type FPMIN = static_cast<real_type>( 1.0e-30 );
	const real_type EPS = static_cast<real_type>( 3.0e-7 );

	gln = gammln( a );

	real_type an, del;
	real_type b = x + static_cast<real_type>( 1 ) - a; // Set up for evaluating continued fraction by modified Lentz's method (x5.2) with b0 = 0.
	real_type c = static_cast<real_type>( 1 ) / FPMIN;
	real_type d = static_cast<real_type>( 1 ) / b;
	real_type h = d;
	for (int i=1; i<=ITMAX; ++i)
	{
		an = -i * (i - a);
		b += static_cast<real_type>( 2 );
		
		d = (an * d) + b;
		if (abs( d ) < FPMIN)
		{
			d = FPMIN;
		}
		
		c = b + (an / c);
		if (abs( c ) < FPMIN)
		{
			c = FPMIN;
		}

		d = static_cast<real_type>( 1 ) / d;
		del = d * c;
		h *= del;
		if (abs( del - static_cast<real_type>( 1 )) < EPS)
		{
			gammcf = exp( (a * log( x )) - x - gln ) * h; // Put factors in front.
			return;
		}
	}

	throw gamma_function_error( "'a' too large, 'ITMAX' too small in 'gcf'" );
}

// Returns the incomplete gamma function P(a; x).
template<typename real_type>
inline
real_type gammp(const real_type &a, const real_type &x)
{
	if ((x < static_cast<real_type>( 0 )) || (a <= static_cast<real_type>( 0 )))
	{
		throw gamma_function_error( "Invalid arguments in routine 'gammp'" );
	}

	// Use the series representation.
	if (x < (a + static_cast<real_type>( 1 )))
	{
		real_type gamser, gln;
		gser( gamser, gln, a, x);
		return gamser;
	}
	// Use the continued fraction representation...
	else
	{ 
		real_type gammcf, gln;
		gcf( gammcf, gln, a, x );
		return static_cast<real_type>( 1 ) - gammcf; // ... and take its complement.
	}
}

}

#endif // !_BMATH_GAMMA_
