/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_TAKE_GRADES_
#define _GA_PRIVATE_TAKE_GRADES_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{
	
/*******************************************************************************************************
 * ga::_private::take_grades<grades,store> struct definition.
 *******************************************************************************************************/
	
// The base struct for retrieve from store only the basis blades with the same grades identified by the given grades bitmap.
template<bitmap_t grades, typename store>
struct take_grades
{
private:

	// This struct is specialized for keep equal to true.
	template<bitmap_t bitmap, bool keep>
	struct test
	{
		// Keep current basis blade and go to next step of the loop.
		typedef ga::store<
				bitmap,
				typename take_grades<grades,typename store::next>::result
			> result;
	};

	// This struct is specialized for keep equal to false.
	template<bitmap_t bitmap>
	struct test<bitmap,false>
	{
		// Go to next step of the loop.
		typedef typename take_grades<grades,typename store::next>::result result;
	};

public:

	// Specifies the list of bases blades stored by store having a given grade.
	typedef typename test<
			store::bitmap,
			(((1 << bit_count<store::bitmap>::result) & grades) != 0)
		>::result result;
};

// Specialization of take_grades<grades,store> for store equal to store_none.
template<bitmap_t grades>
struct take_grades<grades,store_none>
{
	// Loop's end.
	typedef store_none result;
};

}

}

#endif // !_GA_PRIVATE_TAKE_GRADES_
