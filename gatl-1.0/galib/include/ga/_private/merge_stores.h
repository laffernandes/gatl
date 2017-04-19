/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_MERGE_STORES_
#define _GA_PRIVATE_MERGE_STORES_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::merge_stores<store1,store2> struct definition.
 *******************************************************************************************************/

// The result data type defined by this struct returns the store type resulting from the union of the given stores.
template<typename store1, typename store2>
struct merge_stores
{
private:

	// This struct is specialized for the case where the basis blade at left comes before the basis blade at right.
	template<int cmp, int dummy>
	struct loop
	{
		// This recursive template call merges the given store structs.
		typedef store<store1::bitmap,typename merge_stores<typename store1::next,store2>::result> result;
	};

	// Specialization of loop for the case where the basis blade at left is equal to the basis blade at right.
	template<int dummy>
	struct loop<0,dummy>
	{
		// This recursive template call merges the given store structs.
		typedef store<store1::bitmap,typename merge_stores<typename store1::next,typename store2::next>::result> result;
	};

	// Specialization of loop for the case where the basis blade at left comes after the basis blade at right.
	template<int dummy>
	struct loop<1,dummy>
	{
		// This recursive template call merges the given store structs.
		typedef store<store2::bitmap,typename merge_stores<store1,typename store2::next>::result> result;
	};

public:

	// Merges the given lists of basis blades.
	typedef typename loop<((store2::bitmap > store1::bitmap) ? -1 : ((store1::bitmap > store2::bitmap) ? 1 : 0 )),0>::result result;
};

// Specialization of merge_stores<store1,store2> for store1 equal to store_none.
template<typename store2>
struct merge_stores<store_none,store2>
{
	// Returns the store struct at right.
	typedef store2 result;
};

// Specialization of merge_stores<store1,store2> for store2 equal to store_none.
template<typename store1>
struct merge_stores<store1,store_none>
{
	// Returns the store struct at left.
	typedef store1 result;
};

// Specialization of merge_stores<store1,store2> for both store1 and store2 equal to store_none.
template<>
struct merge_stores<store_none,store_none>
{
	// Returns an empty store.
	typedef store_none result;
};

}

}

#endif // !_GA_PRIVATE_MERGE_STORES_
