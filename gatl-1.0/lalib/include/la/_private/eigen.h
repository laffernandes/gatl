/*
 * Copyright (C) 2010 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_PRIVATE_EIGEN_
#define _LA_PRIVATE_EIGEN_

// The namespace of the linear algebra library.
namespace la
{

// A namespace for internal use of the linear algebra library.
namespace _private
{

/*******************************************************************************************************
 * Eigenvectors and Eigenvalues
 * Code from "The Better C Eigenvector Source Code Page"
 * http://www.nauticom.net/www/jdtaft/CEigenBetter.htm
 *******************************************************************************************************/

template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
static void
tri_diagonalize(matrix<value_type,size,size> &d, matrix<value_type,size,1> &e, matrix<value_type,size,size> &A, const matrix<value_type,size,size> &Cxd)
{
	int i, j, k, l;
	value_type f, g, h, hh;
	static const int isize = static_cast<int>( size );

	for (i = 0; i < isize; ++i) {
		for (j = 0; j <= i; ++j) {
			A(i,j) = Cxd(i,j);
		}
	}
	for (i = isize - 1; i > 0; --i) {
		l = i - 2;
		f = A(i,i-1);
		g = static_cast<value_type>( 0 );
		for (k = 0; k <= l; ++k) {
			g += A(i,k)*A(i,k);
		}
		h = g + f*f;
		if (g <= std::numeric_limits<value_type>::epsilon()) {
			e[i] = f;
			h = static_cast<value_type>( 0 );
			d[i] = h;
			continue;
		}
		++l;
		g = sqrt(h);
		if (f >= static_cast<value_type>( 0 )) g = -g;
		e[i] = g;
		h = h - f*g;
		A(i,i-1) = f - g;
		f = static_cast<value_type>( 0 );
		for (j = 0; j <= l; ++j) {
			A(j,i) = A(i,j)/h;
			g = static_cast<value_type>( 0 );
			for (k = 0; k <= j; ++k) {
				g += A(j,k)*A(i,k);
			}
			for (k = j + 1; k <= l; ++k) {
				g += A(k,j)*A(i,k);				
			}
			e[j] = g/h;
			f += g*A(j,i);
		}
		hh = f/(h + h);
		for (j = 0; j <= l; ++j) {
			f = A(i,j);
			g = e[j] - hh*f;
			e[j] = g;
			for (k = 0; k <= j; ++k) {
				A(j,k) = A(j,k) - f*e[k] - g*A(i,k);
			}
		}
		d[i] = h;
	}
	d[0] = e[0] = static_cast<value_type>( 0 );
	for (i = 0; i < isize; ++i) {
		l = i - 1;
		if (d[i] != static_cast<value_type>( 0 )) {
			for (j = 0; j <= l; ++j) {
				g = static_cast<value_type>( 0 );
				for (k = 0; k <= l; ++k) {
					g += A(i,k)*A(k,j);
				}
				for (k = 0; k <= l; ++k) {
					A(k,j) = A(k,j) - g*A(k,i);
				}
			}
		}
		d[i] = A(i,i);
		A(i,i) = static_cast<value_type>( 1 );
		for (j = 0; j <= l; ++j) {
			A(i,j) = A(j,i) = static_cast<value_type>( 0 );
		}
	}
}

template<bool sort, template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
static int
calc_eigenstructure(matrix<value_type,size,size> &d, matrix<value_type,size,1> &e, matrix<value_type,size,size> &A)
{
	int i, j, k, l, m;
	value_type b, c, f, g, h, p, r, s;
	static const int isize = static_cast<int>( size );

	for (i = 1; i < isize; ++i) e[i - 1] = e[i];
	e[isize - 1] = b = f = static_cast<value_type>( 0 );
	for (l = 0; l < isize; ++l) {
		h = std::numeric_limits<value_type>::epsilon()*(abs(d[l]) + abs(e[l]));
		if (b < h) b = h;
		for (m = l; m < isize; ++m) {
			if (abs(e[m]) <= b) break;
		}
		j = 0;
		if (m != l) do {
			if (j++ == 30)
				return -1;
			p = (d[l + 1] - d[l])/(static_cast<value_type>( 2 )*e[l]);
			r = sqrt(p*p + static_cast<value_type>( 1 ));
			h = d[l] - e[l]/(p + (p < static_cast<value_type>( 0 ) ? -r : r));
			for (i = l; i < isize; ++i) d[i] = d[i] - h;
			f += h;
			p = d[m];
			c = static_cast<value_type>( 1 );
			s = static_cast<value_type>( 0 );
			for (i = m - 1; i >= l; --i) {
				g = c*e[i];
				h = c*p;
				if (abs(p) >= abs(e[i])) {
					c = e[i]/p;
					r = sqrt(c*c + static_cast<value_type>( 1 ));
					e[i + 1] = s*p*r;
					s = c/r;
					c = static_cast<value_type>( 1 )/r;
				} else {
					c = p/e[i];
					r = sqrt(c*c + static_cast<value_type>( 1 ));
					e[i + 1] = s*e[i]*r;
					s = static_cast<value_type>( 1 )/r;
					c = c/r;
				}
				p = c*d[i] - s*g;
				d[i + 1] = h + s*(c*g + s*d[i]);
				for (k = 0; k < isize; ++k) {
					h = A(k,i+1);
					A(k,i+1) = s*A(k,i) + c*h;
					A(k,i) = c*A(k,i) - s*h;
				}
			}
			e[l] = s*p;
			d[l] = c*p;
		} while (abs(e[l]) > b);
		d[l] = d[l] + f;
	}

	/* order the eigenvectors  */
	if (sort) {
		for (i = 0; i < isize; ++i) {
			k = i;
			p = d[i];
			for (j = i + 1; j < isize; ++j) {
				if (d[j] > p) {	// Mudei de "<" para ">" aqui para retornar uma ordenação mais cômoda
					k = j;
					p = d[j];
				}
			}
			if (k != i) {
				d[k] = d[i];
				d[i] = p;
				for (j = 0; j < isize; ++j) {
					p = A(j,i);
					A(j,i) = A(j,k);
					A(j,k) = p;
				}
			}
		}
	}
	return 0;
}

}

}

#endif // !_LA_PRIVATE_EIGEN_