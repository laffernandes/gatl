/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_ASSIGN_
#define _GA_ASSIGN_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Assign function implementations.
 *******************************************************************************************************/

// Copy the source multivector into the target multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast, typename model, typename store_target, typename store_source>
inline
void
assign(multivector<model,store_target> &target, const multivector<model,store_source> &source, const real_t &tolerance)
{
	if (!_private::assign<((secure_cast)&&(!_private::is_substore<store_target,store_source>::result)),store_target,store_source>::run( target.data(), source.data(), tolerance ))
	{
		ga_always_assert( false, "Casting error while calling ga::assign() function." );
	}
}

// Copy the source multivector into the target multivector. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast, typename model, typename store>
inline
void
assign(multivector<model,store> &target, const multivector<model,store> &source, const real_t &tolerance)
{
	target = source;
}

// Copy the source multivector into the target multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast, typename model, typename store_target>
inline
void
assign(multivector<model,store_target> &target, const real_t &source, const real_t &tolerance)
{
	if (!_private::assign<((secure_cast)&&(!_private::is_substore<store_target,store_scalar>::result)),store_target,store_scalar>::run( target.data(), &source, tolerance ))
	{
		ga_always_assert( false, "Casting error while calling ga::assign() function." );
	}
}

// Copy the source multivector into the target multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast, typename model, typename store_source>
inline
void
assign(real_t &target, const multivector<model,store_source> &source, const real_t &tolerance)
{
	if (!_private::assign<((secure_cast)&&(!_private::is_substore<store_scalar,store_source>::result)),store_scalar,store_source>::run( &target, source.data(), tolerance ))
	{
		ga_always_assert( false, "Casting error while calling ga::assign() function." );
	}
}

// Copy the source multivector into the target multivector. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast>
inline
void
assign(real_t &target, const real_t &source, const real_t &tolerance)
{
	target = source;
}

}

#endif // !_GA_ASSIGN_
