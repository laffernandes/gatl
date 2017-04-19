/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_IS_SUBSTORE_
#define _GA_PRIVATE_IS_SUBSTORE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::is_substore<super_store,sub_store> struct definition.
 *******************************************************************************************************/

// Specifies whether the given sub_store actually is a substore of super_store.
template<typename super_store, typename sub_store>
struct is_substore
{
	// The query result.
	static const bool result =
		(sub_store::bitmap == super_store::bitmap) ? (
			is_substore<typename super_store::next,typename sub_store::next>::result
		) : (
			(sub_store::bitmap > super_store::bitmap) ? (
				is_substore<typename super_store::next,sub_store>::result
			) : (
				false
			)
		);
};

// Specialization of is_substore<super_store,sub_store> for super_store equal to store_none.
template<typename sub_store>
struct is_substore<store_none,sub_store>
{
	// The query result.
	static const bool result = false;
};

// Specialization of is_substore<super_store,sub_store> for sub_store equal to store_none.
template<typename super_store>
struct is_substore<super_store,store_none>
{
	// The query result.
	static const bool result = true;
};

// Specialization of is_substore<super_store,sub_store> for both super_store and sub_store equal to store_none.
template<>
struct is_substore<store_none,store_none>
{
	// The query result.
	static const bool result = true;
};

}

}

#endif // !_GA_PRIVATE_IS_SUBSTORE_
