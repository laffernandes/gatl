/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_UNARY_DISTRIBUTIVE_
#define _GA_PRIVATE_UNARY_DISTRIBUTIVE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::grade_sign<store> struct definition.
 *******************************************************************************************************/

// The base struct for create unary distributive operations over the sum of basis blades stored by a multivector.
template<typename store>
struct grade_sign
{
private:

	// The grade of the current basis blade.
	static const int grade = bit_count<store::bitmap>::result;

	// Returns whether the Clifford conjugation changes the sign of the current basis blade. The sign change is given by (-1)^{grade*(grade+1)/2}: +--++--+
	static const bool clifford_conjugation = ((grade * (grade + 1) >> 1) & 1);

	// Returns whether the grade involution changes the sign of the current basis blade. The sign change is given by (-1)^{grade}: +-+-+-+-
	static const bool grade_involution = (grade & 1);

	// Returns whether the reverse operation changes the sign of the current basis blade. The sign change is given by (-1)^{grade*(grade-1)/2}: ++--++--
	static const bool reverse = ((grade * (grade - 1) >> 1) & 1);

public:

	// Returns whether the Clifford conjugation changes the input multivector.
	static const bool clifford_conjugation_changes = ((clifford_conjugation) || (grade_sign<typename store::next>::clifford_conjugation_changes));

	// Returns whether the grade involution changes the input multivector.
	static const bool grade_involution_changes = ((grade_involution) || (grade_sign<typename store::next>::grade_involution_changes));

	// Returns whether the reverse operation changes the input multivector.
	static const bool reverse_changes = ((reverse) || (grade_sign<typename store::next>::reverse_changes));

	// The main method (Clifford conjugation).
	static _GA_ALWAYS_INLINE
	void clifford_conjugation_run(real_t *result, const real_t *coefficient)
	{
		(*result) = (clifford_conjugation) ? -(*coefficient) : (*coefficient);
		grade_sign<typename store::next>::clifford_conjugation_run( result + 1, coefficient + 1 );
	}

	// The main method (grade involution).
	static _GA_ALWAYS_INLINE
	void grade_involution_run(real_t *result, const real_t *coefficient)
	{
		(*result) = (grade_involution) ? -(*coefficient) : (*coefficient);
		grade_sign<typename store::next>::grade_involution_run( result + 1, coefficient + 1 );
	}

	// The main method (reverse operation).
	static _GA_ALWAYS_INLINE
	void reverse_run(real_t *result, const real_t *coefficient)
	{
		(*result) = (reverse) ? -(*coefficient) : (*coefficient);
		grade_sign<typename store::next>::reverse_run( result + 1, coefficient + 1 );
	}
};

// Specialization of grade_sign<store> for store equal to store_none.
template<>
struct grade_sign<store_none>
{
	// Returns whether the Clifford conjugation changes the input multivector.
	static const bool clifford_conjugation_changes = false;

	// Returns whether the grade involution changes the input multivector.
	static const bool grade_involution_changes = false;

	// Returns whether the reverse operation changes the input multivector.
	static const bool reverse_changes = false;

	// The main method (Clifford conjugation).
	static _GA_ALWAYS_INLINE
	void clifford_conjugation_run(const real_t *result, const real_t *coefficient)
	{
	}

	// The main method (grade involution).
	static _GA_ALWAYS_INLINE
	void grade_involution_run(const real_t *result, const real_t *coefficient)
	{
	}

	// The main method (reverse operation).
	static _GA_ALWAYS_INLINE
	void reverse_run(const real_t *result, const real_t *coefficient)
	{
	}
};

}

}

#endif // !_GA_PRIVATE_UNARY_DISTRIBUTIVE_
