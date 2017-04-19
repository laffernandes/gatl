/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_MACROS_
#define _BTRIG_MACROS_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Some useful macros for declaring methods (internal use only).
 *******************************************************************************************************/

// Macro for declaring constructors.
#define _btrig_declare_constructors(angle_class) \
	angle_class () \
	{ \
	} \
	\
	angle_class (const angle_class <real_type> &value) : \
		m_value(value.m_value) \
	{ \
	} \
	\
	template<typename other_real_type> \
	angle_class (const angle_class <other_real_type> &value) : \
		m_value(value.m_value) \
	{ \
	} \
	\
	angle_class (const real_type &value) : \
		m_value(value) \
	{ \
	} \

// Macro for declaring casting operators.
#define _btrig_declare_casting_operators(other_angle_class) \
	inline \
	operator real_type& () \
	{ \
		return m_value; \
	} \
	\
	inline \
	operator const real_type& () const \
	{ \
		return m_value; \
	} \
	\
	inline \
	operator other_angle_class <real_type> () const \
	{ \
		return other_angle_class <real_type>( to_##other_angle_class () ); \
	} \

// Macro for declaring assignment operators.
#define _btrig_declare_assignment_operator(angle_class,assignment_operator) \
	inline \
	angle_class & operator assignment_operator (const angle_class <real_type> &value) \
	{ \
		m_value assignment_operator value.m_value; \
		return (*this); \
	} \
	\
	template<typename other_real_type> \
	inline \
	angle_class & operator assignment_operator (const angle_class <other_real_type> &value) \
	{ \
		m_value assignment_operator value.m_value; \
		return (*this); \
	} \
	\
	inline \
	angle_class & operator assignment_operator (const real_type &value) \
	{ \
		m_value assignment_operator value; \
		return (*this); \
	} \

/*******************************************************************************************************
 * Some useful macros for declaring unary operations (internal use only).
 *******************************************************************************************************/

// Macro for declaring unary operator.
#define _btrig_declare_unary_operator(angle_class,unary_operator) \
	template<typename real_type> \
	inline \
	angle_class <real_type> \
	operator unary_operator (const angle_class <real_type> &angle) \
	{ \
		return angle_class <real_type>( unary_operator angle.value() ); \
	} \

// Macro for declaring unary operations.
#define _btrig_declare_unary_operation(angle_class,unary_operation) \
	template<typename real_type> \
	inline \
	angle_class <real_type> \
	unary_operation (const angle_class <real_type> &angle) \
	{ \
		return angle_class <real_type>( unary_operation ( angle.value() ) ); \
	} \

/*******************************************************************************************************
 * Some useful macros for declaring unary test operations (internal use only).
 *******************************************************************************************************/

// Macro for declaring unary test with tolerance.
#define _btrig_declare_unary_test_operation_tolerance(angle_class,unary_operation) \
	template<typename real_type> \
	inline \
	bool \
	unary_operation (const angle_class <real_type> &angle, const real_type &tolerance) \
	{ \
		return unary_operation ( angle.value(), tolerance ); \
	} \

/*******************************************************************************************************
 * Some useful macros for declaring binary operations (internal use only).
 *******************************************************************************************************/

// Macro for declaring a binary operator.
#define _btrig_declare_binary_operator(angle_class,binary_operator) \
	template<typename real_type1, typename real_type2> \
	inline \
	angle_class <real_type1> \
	operator binary_operator (const angle_class <real_type1> &angle1, const angle_class <real_type2> &angle2) \
	{ \
		return angle_class <real_type1>( angle1.value() binary_operator angle2.value() ); \
	} \
	\
	template<typename real_type> \
	inline \
	angle_class <real_type> \
	operator binary_operator (const angle_class <real_type> &angle1, const real_type &angle2) \
	{ \
		return angle_class <real_type>( angle1.value() binary_operator angle2 ); \
	} \
	\
	template<typename real_type> \
	inline \
	angle_class <real_type> \
	operator binary_operator (const real_type &angle1, const angle_class <real_type> &angle2) \
	{ \
		return angle_class <real_type>( angle1 binary_operator angle2.value() ); \
	} \

/*******************************************************************************************************
 * Some useful macros for declaring binary test operations (internal use only).
 *******************************************************************************************************/

// Macro for declaring a binary test operator.
#define _btrig_declare_binary_test_operator(angle_class,binary_operator) \
	template<typename real_type> \
	inline \
	bool \
	operator binary_operator (const angle_class <real_type> &angle1, const angle_class <real_type> &angle2) \
	{ \
		return (angle1.value() binary_operator angle2.value()); \
	} \
	\
	template<typename real_type> \
	inline \
	bool \
	operator binary_operator (const angle_class <real_type> &angle1, const real_type &angle2) \
	{ \
		return (angle1.value() binary_operator angle2); \
	} \
	\
	template<typename real_type> \
	inline \
	bool \
	operator binary_operator (const real_type &angle1, const angle_class <real_type> &angle2) \
	{ \
		return (angle1 binary_operator angle2.value()); \
	} \

}

#endif // !_BTRIG_MACROS_
