/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_MAIN_
#define _LA_MAIN_

// Standard C++ Library.
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// Static Tools Library.
#include "stools.h"

// Basic Math Library.
#include "bmath.h"

// Linear Algebra Library.
#define USING_LA_LIB

#ifdef ASSUMED_LA_TOLERANCE
	#define _LA_DEFAULT_TOLERANCE = static_cast<real_type>( ASSUMED_LA_TOLERANCE )
#else // ASSUMED_GA_TOLERANCE
	#define _LA_DEFAULT_TOLERANCE
#endif // ASSUMED_GA_TOLERANCE

#include "la/matrix.h"
#include "la/tensor.h"

#include "la/_private/dot.h"

#include "la/abs.h"
#include "la/addition.h"
#include "la/dot.h"
#include "la/echelon_form.h"
#include "la/pivot.h"
#include "la/determinant.h"
#include "la/inverse.h"
#include "la/multiplication.h"
#include "la/sandwich_product.h"
#include "la/negation.h"
#include "la/norm.h"
#include "la/unit.h"
#include "la/round.h"
#include "la/tests.h"
#include "la/transpose.h"
#include "la/division.h"
#include "la/subtraction.h"
#include "la/unary_plus.h"
#include "la/write.h"

#include "la/_private/eigen.h"
#include "la/eigen.h"

#endif // !_LA_MAIN_
