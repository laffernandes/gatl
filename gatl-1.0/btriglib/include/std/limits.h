/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_STD_LIMITS_
#define _BTRIG_STD_LIMITS_

// The namespace of the standard C++ template library.
namespace std
{

/*******************************************************************************************************
 * Some useful macro for std::numeric_limits<type> class specialization (internal use only).
 *******************************************************************************************************/

// Macro for declaring a static method in a specialized std::numerical_limits<type> template class.
#define _btrig_declare_limits_method(resulting_type,name) \
	static resulting_type name () { return numeric_limits<real_type>::name ; } \

// Macro for declaring a static property in a specialized std::numerical_limits<type> template class.
#define _btrig_declare_limits_property(resulting_type,name) \
	static const resulting_type name = numeric_limits<real_type>::name ; \

/*******************************************************************************************************
 * std::numeric_limits<type> class specializations.
 *******************************************************************************************************/

// Template class specialization describes arithmetic properties of the degrees<real_type> type.
template<typename real_type>
class numeric_limits<btrig::degrees<real_type> >
{
public:

	// A type that represents the data type being tested.
	typedef btrig::degrees<real_type> _type;

public:

	// Returns the smallest nonzero denormalized value.
	_btrig_declare_limits_method(_type,denorm_min)

	// Returns the number of radix digits that the type can represent without loss of precision.
	_btrig_declare_limits_property(int,digits)

	// Returns the number of decimal digits that the type can represent without loss of precision.
	_btrig_declare_limits_property(int,digits10)

	// Returns the difference between 1 and the smallest value greater than 1 that the data type can represent.
	_btrig_declare_limits_method(_type,epsilon)

	// Tests whether a type allows denormalized values.
	_btrig_declare_limits_property(float_denorm_style,has_denorm)

	// Tests whether loss of accuracy is detected as a denormalization loss rather than as an inexact result.
	_btrig_declare_limits_property(bool,has_denorm_loss)

	// Tests whether a type has a representation for positive infinity.
	_btrig_declare_limits_property(bool,has_infinity)

	// Tests whether a type has a representation for a quiet not a number (NAN), which is nonsignaling.
	_btrig_declare_limits_property(bool,has_quiet_NaN)

	// Tests whether a type has a representation for signaling not a number (NAN).
	_btrig_declare_limits_property(bool,has_signaling_NaN)

	// The representation for positive infinity for a type, if available.
	_btrig_declare_limits_method(_type,infinity)

	// Tests if the set of values that a type may represent is finite.
	_btrig_declare_limits_property(bool,is_bounded)

	// Tests if the calculations done on a type are free of rounding errors.
	_btrig_declare_limits_property(bool,is_exact)

	// Tests if a type conforms to IEC 559 standards.
	_btrig_declare_limits_property(bool,is_iec559)

	// Tests if a type has an integer representation.
	_btrig_declare_limits_property(bool,is_integer)

	// Tests if a type has a modulo representation.
	_btrig_declare_limits_property(bool,is_modulo)

	// Tests if a type has a signed representation.
	_btrig_declare_limits_property(bool,is_signed)

	// Tests if a type has an explicit specialization defined in the template class numeric_limits.
	_btrig_declare_limits_property(bool,is_specialized)

	// Returns the maximum finite value for a type.
	_btrig_declare_limits_method(_type,max) 

	// Returns the maximum positive integral exponent that the floating-point type can represent as a finite value when a base of radix is raised to that power.
	_btrig_declare_limits_property(int,max_exponent)

	// Returns the maximum positive integral exponent that the floating-point type can represent as a finite value when a base of ten is raised to that power.
	_btrig_declare_limits_property(int,max_exponent10)

	// Returns the minimum normalized value for a type.
	_btrig_declare_limits_method(_type,min)

	// Returns the maximum negative integral exponent that the floating-point type can represent as a finite value when a base of radix is raised to that power.
	_btrig_declare_limits_property(int,min_exponent)

	// Returns the maximum negative integral exponent that the floating-point type can represent as a finite value when a base of ten is raised to that power.
	_btrig_declare_limits_property(int,min_exponent10)

	// Returns the representation of a quiet not a number (NAN) for the type.
	_btrig_declare_limits_method(_type,quiet_NaN)

	// Returns the integral base, referred to as radix, used for the representation of a type.
	_btrig_declare_limits_property(int,radix)

	// Returns the maximum rounding error for the type.
	_btrig_declare_limits_method(_type,round_error)

	// Returns a value that describes the various methods that an implementation can choose for rounding a floating-point value to an integer value.
	_btrig_declare_limits_property(float_round_style,round_style)

	// Returns the representation of a signaling not a number (NAN) for the type.
	_btrig_declare_limits_method(_type,signaling_NaN)

	// Tests whether a type can determine that a value is too small to represent as a normalized value before rounding it.
	_btrig_declare_limits_property(bool,tinyness_before)

	// Tests whether trapping that reports on arithmetic exceptions is implemented for a type.
	_btrig_declare_limits_property(bool,traps)
};

// Template class specialization describes arithmetic properties of the radians<real_type> type.
template<typename real_type>
class numeric_limits<btrig::radians<real_type> >
{
public:

	// A type that represents the data type being tested.
	typedef btrig::radians<real_type> _type;

public:

	// Returns the smallest nonzero denormalized value.
	_btrig_declare_limits_method(_type,denorm_min)

	// Returns the number of radix digits that the type can represent without loss of precision.
	_btrig_declare_limits_property(int,digits)

	// Returns the number of decimal digits that the type can represent without loss of precision.
	_btrig_declare_limits_property(int,digits10)

	// Returns the difference between 1 and the smallest value greater than 1 that the data type can represent.
	_btrig_declare_limits_method(_type,epsilon)

	// Tests whether a type allows denormalized values.
	_btrig_declare_limits_property(float_denorm_style,has_denorm)

	// Tests whether loss of accuracy is detected as a denormalization loss rather than as an inexact result.
	_btrig_declare_limits_property(bool,has_denorm_loss)

	// Tests whether a type has a representation for positive infinity.
	_btrig_declare_limits_property(bool,has_infinity)

	// Tests whether a type has a representation for a quiet not a number (NAN), which is nonsignaling.
	_btrig_declare_limits_property(bool,has_quiet_NaN)

	// Tests whether a type has a representation for signaling not a number (NAN).
	_btrig_declare_limits_property(bool,has_signaling_NaN)

	// The representation for positive infinity for a type, if available.
	_btrig_declare_limits_method(_type,infinity)

	// Tests if the set of values that a type may represent is finite.
	_btrig_declare_limits_property(bool,is_bounded)

	// Tests if the calculations done on a type are free of rounding errors.
	_btrig_declare_limits_property(bool,is_exact)

	// Tests if a type conforms to IEC 559 standards.
	_btrig_declare_limits_property(bool,is_iec559)

	// Tests if a type has an integer representation.
	_btrig_declare_limits_property(bool,is_integer)

	// Tests if a type has a modulo representation.
	_btrig_declare_limits_property(bool,is_modulo)

	// Tests if a type has a signed representation.
	_btrig_declare_limits_property(bool,is_signed)

	// Tests if a type has an explicit specialization defined in the template class numeric_limits.
	_btrig_declare_limits_property(bool,is_specialized)

	// Returns the maximum finite value for a type.
	_btrig_declare_limits_method(_type,max) 

	// Returns the maximum positive integral exponent that the floating-point type can represent as a finite value when a base of radix is raised to that power.
	_btrig_declare_limits_property(int,max_exponent)

	// Returns the maximum positive integral exponent that the floating-point type can represent as a finite value when a base of ten is raised to that power.
	_btrig_declare_limits_property(int,max_exponent10)

	// Returns the minimum normalized value for a type.
	_btrig_declare_limits_method(_type,min)

	// Returns the maximum negative integral exponent that the floating-point type can represent as a finite value when a base of radix is raised to that power.
	_btrig_declare_limits_property(int,min_exponent)

	// Returns the maximum negative integral exponent that the floating-point type can represent as a finite value when a base of ten is raised to that power.
	_btrig_declare_limits_property(int,min_exponent10)

	// Returns the representation of a quiet not a number (NAN) for the type.
	_btrig_declare_limits_method(_type,quiet_NaN)

	// Returns the integral base, referred to as radix, used for the representation of a type.
	_btrig_declare_limits_property(int,radix)

	// Returns the maximum rounding error for the type.
	_btrig_declare_limits_method(_type,round_error)

	// Returns a value that describes the various methods that an implementation can choose for rounding a floating-point value to an integer value.
	_btrig_declare_limits_property(float_round_style,round_style)

	// Returns the representation of a signaling not a number (NAN) for the type.
	_btrig_declare_limits_method(_type,signaling_NaN)

	// Tests whether a type can determine that a value is too small to represent as a normalized value before rounding it.
	_btrig_declare_limits_property(bool,tinyness_before)

	// Tests whether trapping that reports on arithmetic exceptions is implemented for a type.
	_btrig_declare_limits_property(bool,traps)
};

/*******************************************************************************************************
 * Cleanup.
 *******************************************************************************************************/

#undef _btrig_declare_limits_method
#undef _btrig_declare_limits_property

}

#endif // !_BTRIG_STD_LIMITS_
