/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include <cstdlib>
#include "ga.h"

// Main function.
int
main(int argc, char *argv[])
{
	/*
	typedef ga::euclidean::model<5> model;
	typedef ga::multivector<model,typename ga::store_all<model>::store_type> multivector_type;

	static const ga::real_t TOLERANCE = 1.0e-10;

	const multivector_type &e1 = ga::euclidean::template vector<multivector_type>( 1.0, 0.0, 0.0, 0.0, 0.0 );
	const multivector_type &e2 = ga::euclidean::template vector<multivector_type>( 0.0, 1.0, 0.0, 0.0, 0.0 );
	const multivector_type &e3 = ga::euclidean::template vector<multivector_type>( 0.0, 0.0, 1.0, 0.0, 0.0 );
	const multivector_type &e4 = ga::euclidean::template vector<multivector_type>( 0.0, 0.0, 0.0, 1.0, 0.0 );
	const multivector_type &e5 = ga::euclidean::template vector<multivector_type>( 0.0, 0.0, 0.0, 0.0, 1.0 );
	
	const multivector_type &m1 = -0.12804824427184092*e1^e3^e4^e5 + 0.99176794016488512*e2^e3^e4^e5;
	const multivector_type &m2 = e1^e2;
	//const multivector_type &m2 = e1^e2^e3;
	//const multivector_type &m2 = e1^e2^e3^e4;
	//const multivector_type &m2 = e1^e2^e3^e4^e5;

	join( m1, m2, TOLERANCE );
	*/

	return EXIT_SUCCESS;
}

//#include <iostream>
//#include <ctime>
//
//// This method writes the result of a test into the std::clog global stream.
//inline
//void
//log(const bool result, const char *test_name)
//{
//	std::clog << "\t" << test_name << "... " << ((result) ? "ok" : "error" ) << std::endl;
//	assert( result );
//}
//
//// This method validates binary operations.
//template<typename model, typename multivector1, typename multivector2>
//void
//validate_binary(const multivector1 &m1, const multivector2 &m2)
//{
//	srand( static_cast<unsigned int>( time( NULL ) ) );
//
//	const ga::multivector<model,ga::store_scalar> half = { { { static_cast<ga::real_t>( 1 ) / static_cast<ga::real_t>( 2 ) } } };
//
//	const ga::multivector<model,typename ga::store_all<model>::store_type> &m3 = ga::rand_multivector<ga::multivector<model,typename ga::store_all<model>::store_type> >( static_cast<ga::real_t>( -1 ), static_cast<ga::real_t>( 1 ) );
//	const ga::multivector<model,typename ga::store_grade<1,model>::store_type> &v = ga::rand_multivector<ga::multivector<model,typename ga::store_grade<1,model>::store_type> >( static_cast<ga::real_t>( -1 ), static_cast<ga::real_t>( 1 ) );
//	
//	std::clog << "Validate using" << std::endl;
//	std::clog << "    m1 = " << m1 << std::endl;
//	std::clog << "    m2 = " << m2 << std::endl << std::endl;
//	
//	log( (m1 + m2) == (m2 + m1), "addition commutativity" );
//
//	log( (m1 + (m2 + m3)) == ((m1 + m2) + m3), "addition associativity" );
//
//	log( (m1 - m2) == -(m2 - m1), "subtraction" );
//
//	log( ((m1 + m2) * m3) == ((m1 * m3) + (m2 * m3)), "geometric product distributivity over the sum" );
//
//	log( ((m1 * m2) * m3) == (m1 * (m2 * m3)), "geometric product associativity" );
//
//	log( (v << (m1 ^ m2)) == (((v << m1) ^ m2) + (ga::grade_involution( m1 ) ^ (v << m2))), "left contraction, outer product and grade involution" );
//
//	log( ((m1 ^ m2) << m3) == (m1 << (m2 << m3)), "left contraction and outer product" );
//
//	log( (m3 % (m1 << m2)) == ((m3 ^ m1) % m2), "left contraction, outer product and scalar product" );
//
//	log( ((m2 >> m1) % m3) == (m2 % (m1 ^ m3)), "right contraction, outer product and scalar product" );
//
//	log( (m1 % m2) == ga::take_grade<0,model>( m1 * m2 ), "scalar product" );
//
//	if ((ga::is_grade_homogeneous( m1 )) && (ga::is_grade_homogeneous( m2 )))
//	{
//		log( (m1 ^ m2) == (std::pow( static_cast<ga::real_t>( -1 ), static_cast<ga::real_t>( ga::grade( m1 ) * ga::grade( m2 ) ) ) * (m2 ^ m1)), "outer product for homogeneous grade" );
//
//		log( (m1 % m2) == (m2 % m1), "scalar product of homogeneous grade multivectors" );
//	}
//
//	if (ga::is_grade_homogeneous<1>( m1 ))
//	{
//		log( ((m2 / m1) * m1) == m2, "inverse geometric product" );
//
//		log( (m1 * m2) == ((m1 << m2) + (m1 ^ m2)), "geometric product, left contraction and outer product with one vector" );
//
//		if (ga::is_grade_homogeneous<1>( m2 ))
//		{
//			log( (m1 << m2) == (half * ((m1 * m2) + (m2 * m1))), "left contraction and geometric product with vectors" );
//
//			log( ((m1 << m2) == (m1 >> m2)) && ((m1 << m2) == (m1 % m2)), "left contraction, right contraction and scalar product for vectors" );
//		}
//	}
//
//	std::clog << std::endl << std::endl;
//}
//
//// This method validates unary operations.
//template<typename model, typename multivector>
//void
//validate_unary(const multivector &m)
//{
//	const ga::multivector<model,ga::store_none> zero;
//	const ga::multivector<model,ga::store_scalar> one = { { { 1 } } };
//	
//	std::clog << "Validate using" << std::endl;
//	std::clog << "    m = " << m << std::endl << std::endl;
//	
//	log( (+m) == m, "unary plus" );
//
//	log( (-m) == (m * -one), "negation" );
//
//	log( ga::is_zero( m ) == (m == zero), "zero multivector test" );
//
//	log( ga::is_scalar( m ) == ga::is_grade_homogeneous<0>( m ), "scalar value test" );
//
//	if ((ga::is_blade<model>( m )) || (ga::is_versor<model>( m )))
//	{
//		log( (m * ga::inverse( m )) == one, "inverse" );
//	}
//
//	log( m == ga::undual( ga::dual<model>( m ) ), "dualization and undualization" );
//
//	multivector m_unit_e = ga::unit_em( m );
//	log( (ga::is_zero( m )) || (ga::norm_em( m_unit_e ) == one), "unit under Euclidean norm and Euclidean norm" );
//	log( (ga::is_zero( m )) || (ga::norm_em( m_unit_e ) == ga::norm2_em( m_unit_e )), "squared Euclidean norm" );
//
//	multivector m_unit_r = ga::unit( m );
//	log( (ga::is_null( m )) || (ga::norm( m_unit_r ) == ga::norm2( m_unit_r )), "unit under reverse norm and reverse norm" );
//	log( (ga::is_null( m )) || (ga::norm( m_unit_r ) == one), "squared reverse norm" );
//
//	log( (m % zero) == zero, "scalar product with zero at right" );
//	log( (zero % m) == zero, "scalar product with zero at left"  );
//
//	log( (m * zero) == zero, "geometric product with zero at right" );
//	log( (zero * m) == zero, "geometric product with zero at left" );
//
//	log( (m + zero) == m, "addition with zero at right" );
//	log( (zero + m) == m, "addition with zero at left" );
//
//	log( (m - zero) == m, "subtraction with zero at right" );
//	log( (zero - m) == (-m), "subtraction with zero at left" );
//
//	if ((ga::is_blade<model>( m )) || (ga::is_versor<model>( m )))
//	{
//		log( (zero / m) == zero, "inverse geometric product with zero at left" );
//	}
//
//	log( (m << zero) == zero, "left contraction with zero at right" );
//	log( (zero << m) == zero, "left contraction with zero at left" );
//
//	log( (m >> zero) == zero, "right contraction with zero at right" );
//	log( (zero >> m) == zero, "right contraction with zero at left" );
//
//	log( (m ^ zero) == zero, "outer product with zero at right" );
//	log( (zero ^ m) == zero, "outer product with zero at left" );
//
//	log( ga::dot( m, zero ) == zero, "dot product with zero at right" );
//	log( ga::dot( zero, m ) == zero, "dot product with zero at left" );
//
//	log( ga::hip( m, zero ) == zero, "Hestenes' inner product with zero at right" );
//	log( ga::hip( zero, m ) == zero, "Hestenes' inner product with zero at left" );
//
//	log( ((ga::has_grade<0>( m )) ? ((m % one) == ga::take_grade<0,model>( m )) : ((m % one) == zero)), "scalar product with one at right" );
//	log( ((ga::has_grade<0>( m )) ? ((one % m) == ga::take_grade<0,model>( m )) : ((one % m) == zero)), "scalar product with one at left"  );
//
//	log( (m * one) == m, "geometric product with one at right" );
//	log( (one * m) == m, "geometric product with one at left" );
//
//	log( (m / one) == m, "inverse geometric product with one at right" );
//
//	log( ((ga::has_grade<0>( m )) ? ((m << one) == ga::take_grade<0,model>( m )) : ((m << one) == zero)), "left contraction with one at right" );
//	log( (one << m) == m, "left contraction with one at left" );
//
//	log( (m >> one) == m, "right contraction with one at right" );
//	log( ((ga::has_grade<0>( m )) ? ((one >> m) == ga::take_grade<0,model>( m )) : ((one >> m) == zero)), "right contraction with one at left" );
//
//	log( (m ^ one) == m, "outer product with one at right" );
//	log( (one ^ m) == m, "outer product with one at left" );
//
//	log( ga::dot( m, one ) == m, "dot product with one at right" );
//	log( ga::dot( one, m ) == m, "dot product with one at left" );
//
//	log( ga::hip<model>( m, one ) == zero, "Hestenes' inner product with one at right" );
//	log( ga::hip<model>( one, m ) == zero, "Hestenes' inner product with one at left" );
//
//	std::clog << std::endl << std::endl;
//}
//
//// Main function.
//int
//main(int argc, char *argv[])
//{
//	using namespace ga3e;
//	static const real_t tolerance = 1.0e-8;
//	static const size_t iterations = 1000000;
//
//	#define random_blade(blade_type,var) \
//		blade_type var##_x; \
//		for (size_t i=0; i!=var##_x.size; ++i) \
//		{ \
//			var##_x[i] = 10.0 * ((2.0 * (static_cast<real_t>( rand() ) / RAND_MAX)) - 1.0); \
//		} \
//		multivector_t var; \
//		var = var##_x;
//
//	/*
//	#define check_factorization(blade_type,func) \
//	{ \
//		random_blade(blade_type,blade) \
//		\
//		real_t scalar; \
//		std::vector<vector_t> factors; \
//		func( scalar, factors, blade, tolerance ); \
//		\
//		multivector_t current; \
//		assign<false>( current, scalar, tolerance ); \
//		for (std::vector<vector_t>::iterator itr=factors.begin(); itr!=factors.end(); ++itr) \
//		{ \
//			assign<false>( current, current^(*itr), tolerance ); \
//		} \
//	}
//
//	#define benchmark_factorization(blade_type,func) \
//	{ \
//		btools::elapsed_time et; \
//		\
//		et.begin(); \
//		for (size_t k=0; k!=iterations; ++k) \
//		{ \
//			check_factorization(blade_type,func) \
//		} \
//		et.end(); \
//		\
//		std::cout << et.mean_elapsed_time() << " seconds." << std::endl; \
//	}
//	
//	std::cout << "Facorization" << std::endl;
//	std::cout << "---------------------------------------" << std::endl;
//	benchmark_factorization(scalar_t,fast_factorize_em)
//	benchmark_factorization(scalar_t,factorize_em)
//	std::cout << std::endl;
//
//	benchmark_factorization(vector_t,fast_factorize_em)
//	benchmark_factorization(vector_t,factorize_em)
//	std::cout << std::endl;
//
//	benchmark_factorization(bivector_t,fast_factorize_em)
//	benchmark_factorization(bivector_t,factorize_em)
//	std::cout << std::endl;
//	
//	benchmark_factorization(trivector_t,fast_factorize_em)
//	benchmark_factorization(trivector_t,factorize_em)
//	std::cout << std::endl;
//	*/
//
//	#define check_join(blade1_type,blade2_type,func) \
//	{ \
//		random_blade(blade1_type,blade1) \
//		random_blade(blade2_type,blade2) \
//		\
//		std::cout << ((!is_zero( blade1^delta_em( blade1, func( blade1, blade2, tolerance ), tolerance ), tolerance )) ? "ok1, " : "error1, "); \
//		std::cout << ((!is_zero( blade2^delta_em( blade2, func( blade1, blade2, tolerance ), tolerance ), tolerance )) ? "ok2" : "error2") << std::endl; \
//	}
//
//	#define check_meet(blade1_type,blade2_type,func) \
//	{ \
//		random_blade(blade1_type,blade1) \
//		random_blade(blade2_type,blade2) \
//		\
//		std::cout << ((!is_zero( func( blade1, blade2, tolerance )^delta_em( func( blade1, blade2, tolerance ), blade1, tolerance ), tolerance )) ? "ok1, " : "error1, "); \
//		std::cout << ((!is_zero( func( blade1, blade2, tolerance )^delta_em( func( blade1, blade2, tolerance ), blade2, tolerance ), tolerance )) ? "ok2" : "error2") << std::endl; \
//	}
//
//	#define run_op(blade1_type,blade2_type,func) \
//	{ \
//		random_blade(blade1_type,blade1) \
//		random_blade(blade2_type,blade2) \
//		\
//		func( blade1, blade2, tolerance ); \
//	}
//
//	#define benchmark_op(blade1_type,blade2_type,func) \
//	{ \
//		btools::elapsed_time et; \
//		\
//		et.begin(); \
//		for (size_t k=0; k!=iterations; ++k) \
//		{ \
//			run_op(blade1_type,blade2_type,func) \
//		} \
//		et.end(); \
//		\
//		std::cout << et.mean_elapsed_time() << " seconds. "; \
//	}
//
//	std::cout << "Join" << std::endl;
//	std::cout << "---------------------------------------" << std::endl;
//	
//	std::cout << "Scalar / Scalar" << std::endl;
//	benchmark_op(scalar_t,scalar_t,fast_join) check_join(scalar_t,scalar_t,fast_join)
//	benchmark_op(scalar_t,scalar_t,join) check_join(scalar_t,scalar_t,fast_join)
//	std::cout << std::endl;
//
//	std::cout << "Scalar / Vector" << std::endl;
//	benchmark_op(scalar_t,vector_t,fast_join) check_join(scalar_t,vector_t,fast_join)
//	benchmark_op(scalar_t,vector_t,join) check_join(scalar_t,vector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Scalar / Bivector" << std::endl;
//	benchmark_op(scalar_t,bivector_t,fast_join) check_join(scalar_t,bivector_t,fast_join)
//	benchmark_op(scalar_t,bivector_t,join) check_join(scalar_t,bivector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Scalar / Trivector" << std::endl;
//	benchmark_op(scalar_t,trivector_t,fast_join) check_join(scalar_t,trivector_t,fast_join)
//	benchmark_op(scalar_t,trivector_t,join) check_join(scalar_t,trivector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Vector / Scalar" << std::endl;
//	benchmark_op(vector_t,scalar_t,fast_join) check_join(vector_t,scalar_t,fast_join)
//	benchmark_op(vector_t,scalar_t,join) check_join(vector_t,scalar_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Vector / Vector" << std::endl;
//	benchmark_op(vector_t,vector_t,fast_join) check_join(vector_t,vector_t,fast_join)
//	benchmark_op(vector_t,vector_t,join) check_join(vector_t,vector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Vector / Bivector" << std::endl;
//	benchmark_op(vector_t,bivector_t,fast_join) check_join(vector_t,bivector_t,fast_join)
//	benchmark_op(vector_t,bivector_t,join) check_join(vector_t,bivector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Vector / Trivector" << std::endl;
//	benchmark_op(vector_t,trivector_t,fast_join) check_join(vector_t,trivector_t,fast_join)
//	benchmark_op(vector_t,trivector_t,join) check_join(vector_t,trivector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Bivector / Scalar" << std::endl;
//	benchmark_op(bivector_t,scalar_t,fast_join) check_join(bivector_t,scalar_t,fast_join)
//	benchmark_op(bivector_t,scalar_t,join) check_join(bivector_t,scalar_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Bivector / Vector" << std::endl;
//	benchmark_op(bivector_t,vector_t,fast_join) check_join(bivector_t,vector_t,fast_join)
//	benchmark_op(bivector_t,vector_t,join) check_join(bivector_t,vector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Bivector / Bivector" << std::endl;
//	benchmark_op(bivector_t,bivector_t,fast_join) check_join(bivector_t,bivector_t,fast_join)
//	benchmark_op(bivector_t,bivector_t,join) check_join(bivector_t,bivector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Bivector / Trivector" << std::endl;
//	benchmark_op(bivector_t,trivector_t,fast_join) check_join(bivector_t,trivector_t,fast_join)
//	benchmark_op(bivector_t,trivector_t,join) check_join(bivector_t,trivector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Trivector / Scalar" << std::endl;
//	benchmark_op(trivector_t,scalar_t,fast_join) check_join(trivector_t,scalar_t,fast_join)
//	benchmark_op(trivector_t,scalar_t,join) check_join(trivector_t,scalar_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Trivector / Vector" << std::endl;
//	benchmark_op(trivector_t,vector_t,fast_join) check_join(trivector_t,vector_t,fast_join)
//	benchmark_op(trivector_t,vector_t,join) check_join(trivector_t,vector_t,join)
//	std::cout << std::endl;
//
//	std::cout << "Trivector / Bivector" << std::endl;
//	benchmark_op(trivector_t,bivector_t,fast_join) check_join(trivector_t,bivector_t,fast_join)
//	benchmark_op(trivector_t,bivector_t,join) check_join(trivector_t,bivector_t,join)
//	std::cout << std::endl;
//
//	//std::cout << "Trivector / Trivector" << std::endl;
//	//benchmark_op(trivector_t,trivector_t,fast_join) check_join(trivector_t,trivector_t,fast_join)
//	//benchmark_op(trivector_t,trivector_t,join) check_join(trivector_t,trivector_t,join)
//	//std::cout << std::endl;
//	
//	std::cout << "Meet" << std::endl;
//	std::cout << "---------------------------------------" << std::endl;
//	
//	std::cout << "Scalar / Scalar" << std::endl;
//	benchmark_op(scalar_t,scalar_t,fast_meet) check_meet(scalar_t,scalar_t,fast_meet)
//	benchmark_op(scalar_t,scalar_t,meet) check_meet(scalar_t,scalar_t,fast_meet)
//	std::cout << std::endl;
//
//	std::cout << "Scalar / Vector" << std::endl;
//	benchmark_op(scalar_t,vector_t,fast_meet) check_meet(scalar_t,vector_t,fast_meet)
//	benchmark_op(scalar_t,vector_t,meet) check_meet(scalar_t,vector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Scalar / Bivector" << std::endl;
//	benchmark_op(scalar_t,bivector_t,fast_meet) check_meet(scalar_t,bivector_t,fast_meet)
//	benchmark_op(scalar_t,bivector_t,meet) check_meet(scalar_t,bivector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Scalar / Trivector" << std::endl;
//	benchmark_op(scalar_t,trivector_t,fast_meet) check_meet(scalar_t,trivector_t,fast_meet)
//	benchmark_op(scalar_t,trivector_t,meet) check_meet(scalar_t,trivector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Vector / Scalar" << std::endl;
//	benchmark_op(vector_t,scalar_t,fast_meet) check_meet(vector_t,scalar_t,fast_meet)
//	benchmark_op(vector_t,scalar_t,meet) check_meet(vector_t,scalar_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Vector / Vector" << std::endl;
//	benchmark_op(vector_t,vector_t,fast_meet) check_meet(vector_t,vector_t,fast_meet)
//	benchmark_op(vector_t,vector_t,meet) check_meet(vector_t,vector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Vector / Bivector" << std::endl;
//	benchmark_op(vector_t,bivector_t,fast_meet) check_meet(vector_t,bivector_t,fast_meet)
//	benchmark_op(vector_t,bivector_t,meet) check_meet(vector_t,bivector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Vector / Trivector" << std::endl;
//	benchmark_op(vector_t,trivector_t,fast_meet) check_meet(vector_t,trivector_t,fast_meet)
//	benchmark_op(vector_t,trivector_t,meet) check_meet(vector_t,trivector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Bivector / Scalar" << std::endl;
//	benchmark_op(bivector_t,scalar_t,fast_meet) check_meet(bivector_t,scalar_t,fast_meet)
//	benchmark_op(bivector_t,scalar_t,meet) check_meet(bivector_t,scalar_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Bivector / Vector" << std::endl;
//	benchmark_op(bivector_t,vector_t,fast_meet) check_meet(bivector_t,vector_t,fast_meet)
//	benchmark_op(bivector_t,vector_t,meet) check_meet(bivector_t,vector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Bivector / Bivector" << std::endl;
//	benchmark_op(bivector_t,bivector_t,fast_meet) check_meet(bivector_t,bivector_t,fast_meet)
//	benchmark_op(bivector_t,bivector_t,meet) check_meet(bivector_t,bivector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Bivector / Trivector" << std::endl;
//	benchmark_op(bivector_t,trivector_t,fast_meet) check_meet(bivector_t,trivector_t,fast_meet)
//	benchmark_op(bivector_t,trivector_t,meet) check_meet(bivector_t,trivector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Trivector / Scalar" << std::endl;
//	benchmark_op(trivector_t,scalar_t,fast_meet) check_meet(trivector_t,scalar_t,fast_meet)
//	benchmark_op(trivector_t,scalar_t,meet) check_meet(trivector_t,scalar_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Trivector / Vector" << std::endl;
//	benchmark_op(trivector_t,vector_t,fast_meet) check_meet(trivector_t,vector_t,fast_meet)
//	benchmark_op(trivector_t,vector_t,meet) check_meet(trivector_t,vector_t,meet)
//	std::cout << std::endl;
//
//	std::cout << "Trivector / Bivector" << std::endl;
//	benchmark_op(trivector_t,bivector_t,fast_meet) check_meet(trivector_t,bivector_t,fast_meet)
//	benchmark_op(trivector_t,bivector_t,meet) check_meet(trivector_t,bivector_t,meet)
//	std::cout << std::endl;
//
//	//std::cout << "Trivector / Trivector" << std::endl;
//	//benchmark_op(trivector_t,trivector_t,fast_meet) check_meet(trivector_t,trivector_t,fast_meet)
//	//benchmark_op(trivector_t,trivector_t,meet) check_meet(trivector_t,trivector_t,meet)
//	//std::cout << std::endl;
//
//	///**/
//	//using namespace ga3e;
//    //
//	//srand( (unsigned int)time( NULL ) );
//	//
//	//zero_t zero;
//	//real_t real               = rand_multivector<real_t>( -1, 1 );
//	//scalar_t scalar           = rand_multivector<scalar_t>( -1, 1 );
//	//vector_t vector           = rand_multivector<vector_t>( -1, 1 );
//	//bivector_t bivector       = rand_multivector<bivector_t>( -1, 1 );
//	//trivector_t trivector     = rand_multivector<trivector_t>( -1, 1 );
//	//multivector_t multivector = rand_multivector<multivector_t>( -1, 1 );
//	///**/
//
//	///**
//	//typedef gp_return_t(vector_t,vector_t) my_versor_t;
//
//	//my_versor_t                                                  versor = gp( rand_multivector<vector_t>( -1, 1 ), rand_multivector<vector_t>( -1, 1 ) );
//	//gp_return_t(gp_return_t(my_versor_t,bivector_t),my_versor_t) r1 = versor * bivector * inverse( versor );
//	//apply_versor_return_t(my_versor_t,bivector_t)                r2 = apply_even_versor( versor, bivector );
//	//
//	//ga_always_assert( r1 == r2, "Opa!" );
//	//**/
//
//	///**
//	//ga_always_assert( grade( take_grade<0>( vector ) ) == 0, "Opa!" );
//	//ga_always_assert( grade( take_grade<1>( vector ) ) == 1, "Opa!" );
//	//ga_always_assert( grade( take_grade<2>( vector ) ) == 0, "Opa!" );
//	//ga_always_assert( grade( take_grade<0>( bivector ) ) == 0, "Opa!" );
//	//ga_always_assert( grade( take_grade<1>( bivector ) ) == 0, "Opa!" );
//	//ga_always_assert( grade( take_grade<2>( bivector ) ) == 2, "Opa!" );
//	//**/
//	//
//	///**
//	//typedef std::vector<vector_t> factors_t;
//
//	//factors_t factors;
//	//real_t s, my_scalar = rand();
//	//bivector_t my_bivector = rand_multivector<bivector_t>( -1, 1 );
//
//	//if (rand() == 1)
//	//{
//	//	ga::factorize_em( s, factors, my_bivector );
//	//}
//	//else
//	//{
//	//	ga::factorize_em( s, factors, zero );
//	//	ga::factorize_em( s, factors, my_scalar );
//	//}
//
//	//std::cout << s << std::endl;
//	//**/
//
//	///**
//	//std::cout << zero << std::endl;
//	//std::cout << real << std::endl;
//	//std::cout << scalar << std::endl;
//	//std::cout << vector << std::endl;
//	//std::cout << bivector << std::endl;
//	//std::cout << trivector << std::endl;
//	//std::cout << std::endl;
//	//**/
//
//	///**
//	//std::cout << (zero + zero) << std::endl;
//	//std::cout << (zero + real) << std::endl;
//	//std::cout << (zero + scalar) << std::endl;
//	//std::cout << (zero + vector) << std::endl;
//	//std::cout << (zero + bivector) << std::endl;
//	//std::cout << (zero + trivector) << std::endl;
//	//std::cout << (zero + multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (real + zero) << std::endl;
//	//std::cout << (real + real) << std::endl;
//	//std::cout << (real + scalar) << std::endl;
//	//std::cout << (real + vector) << std::endl;
//	//std::cout << (real + bivector) << std::endl;
//	//std::cout << (real + trivector) << std::endl;
//	//std::cout << (real + multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (scalar + zero) << std::endl;
//	//std::cout << (scalar + real) << std::endl;
//	//std::cout << (scalar + scalar) << std::endl;
//	//std::cout << (scalar + vector) << std::endl;
//	//std::cout << (scalar + bivector) << std::endl;
//	//std::cout << (scalar + trivector) << std::endl;
//	//std::cout << (scalar + multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (vector + zero) << std::endl;
//	//std::cout << (vector + real) << std::endl;
//	//std::cout << (vector + scalar) << std::endl;
//	//std::cout << (vector + vector) << std::endl;
//	//std::cout << (vector + bivector) << std::endl;
//	//std::cout << (vector + trivector) << std::endl;
//	//std::cout << (vector + multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (bivector + zero) << std::endl;
//	//std::cout << (bivector + real) << std::endl;
//	//std::cout << (bivector + scalar) << std::endl;
//	//std::cout << (bivector + vector) << std::endl;
//	//std::cout << (bivector + bivector) << std::endl;
//	//std::cout << (bivector + trivector) << std::endl;
//	//std::cout << (bivector + multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (trivector + zero) << std::endl;
//	//std::cout << (trivector + real) << std::endl;
//	//std::cout << (trivector + scalar) << std::endl;
//	//std::cout << (trivector + vector) << std::endl;
//	//std::cout << (trivector + bivector) << std::endl;
//	//std::cout << (trivector + trivector) << std::endl;
//	//std::cout << (trivector + multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (multivector + zero) << std::endl;
//	//std::cout << (multivector + real) << std::endl;
//	//std::cout << (multivector + scalar) << std::endl;
//	//std::cout << (multivector + vector) << std::endl;
//	//std::cout << (multivector + bivector) << std::endl;
//	//std::cout << (multivector + trivector) << std::endl;
//	//std::cout << (multivector + multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (zero - zero) << std::endl;
//	//std::cout << (zero - real) << std::endl;
//	//std::cout << (zero - scalar) << std::endl;
//	//std::cout << (zero - vector) << std::endl;
//	//std::cout << (zero - bivector) << std::endl;
//	//std::cout << (zero - trivector) << std::endl;
//	//std::cout << (zero - multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (real - zero) << std::endl;
//	//std::cout << (real - real) << std::endl;
//	//std::cout << (real - scalar) << std::endl;
//	//std::cout << (real - vector) << std::endl;
//	//std::cout << (real - bivector) << std::endl;
//	//std::cout << (real - trivector) << std::endl;
//	//std::cout << (real - multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (scalar - zero) << std::endl;
//	//std::cout << (scalar - real) << std::endl;
//	//std::cout << (scalar - scalar) << std::endl;
//	//std::cout << (scalar - vector) << std::endl;
//	//std::cout << (scalar - bivector) << std::endl;
//	//std::cout << (scalar - trivector) << std::endl;
//	//std::cout << (scalar - multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (vector - zero) << std::endl;
//	//std::cout << (vector - real) << std::endl;
//	//std::cout << (vector - scalar) << std::endl;
//	//std::cout << (vector - vector) << std::endl;
//	//std::cout << (vector - bivector) << std::endl;
//	//std::cout << (vector - trivector) << std::endl;
//	//std::cout << (vector - multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (bivector - zero) << std::endl;
//	//std::cout << (bivector - real) << std::endl;
//	//std::cout << (bivector - scalar) << std::endl;
//	//std::cout << (bivector - vector) << std::endl;
//	//std::cout << (bivector - bivector) << std::endl;
//	//std::cout << (bivector - trivector) << std::endl;
//	//std::cout << (bivector - multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (trivector - zero) << std::endl;
//	//std::cout << (trivector - real) << std::endl;
//	//std::cout << (trivector - scalar) << std::endl;
//	//std::cout << (trivector - vector) << std::endl;
//	//std::cout << (trivector - bivector) << std::endl;
//	//std::cout << (trivector - trivector) << std::endl;
//	//std::cout << (trivector - multivector) << std::endl;
//	//std::cout << std::endl;
//
//	//std::cout << (multivector - zero) << std::endl;
//	//std::cout << (multivector - real) << std::endl;
//	//std::cout << (multivector - scalar) << std::endl;
//	//std::cout << (multivector - vector) << std::endl;
//	//std::cout << (multivector - bivector) << std::endl;
//	//std::cout << (multivector - trivector) << std::endl;
//	//std::cout << (multivector - multivector) << std::endl;
//	//std::cout << std::endl;
//	//**/
//
//	///**
//	//std::cout << zero << " *** " << exp( zero ) << std::endl << std::endl;
//	//std::cout << real << " *** " << exp( real ) << std::endl << std::endl;
//	//std::cout << scalar << " *** " << exp( scalar ) << std::endl << std::endl;
//	//std::cout << vector << " *** " << exp( vector ) << std::endl << std::endl;
//	//std::cout << bivector << " *** " << exp( bivector ) << std::endl << std::endl;
//	//std::cout << trivector << " *** " << exp( trivector ) << std::endl << std::endl;
//	//std::cout << std::endl;
//	//**/
//
//	///**
//	////typedef vector_t A_t; A_t A = { 10, 5, 0 };
//	////typedef bivector_t A_t; A_t A = { 10, 5, 0 };
//	//typedef trivector_t A_t; A_t A = { -1 };
//	//
//	////typedef ga::multivector<model,ga::store_scalar> B_t; B_t B = { -4 };
//	////typedef vector_t B_t; B_t B = { -63, -4, 0 };
//	////typedef bivector_t B_t; B_t B = { -63, -4, 0 };
//	////typedef trivector_t B_t; B_t B = { 63 };
//	////typedef bivector_t B_t; B_t B = { -63, 0, 0 };
//	//typedef vector_t B_t; B_t B = { 32, -4, 9 };
//	////typedef vector_t B_t; B_t B = { -20, -10, 0 };
//
//	//typedef meet_return_t(A_t,B_t) M_t;  const M_t  &M  = meet( A, B );
//	//typedef meet_return_t(B_t,A_t) M__t; const M__t &M_ = meet( B, A );
//	//typedef join_return_t(A_t,B_t) J_t;  const J_t  &J  = join( A, B );
//	//typedef join_return_t(B_t,A_t) J__t; const J__t &J_ = join( B, A );
//
//	//std::cout << "A = " << A << std::endl;
//	//std::cout << "B = " << B << std::endl;
//	//std::cout << std::endl;
//	//std::cout << "M  = meet(A,B)      = " << M << std::endl;
//	//std::cout << "J  = join(A,B)      = " << J << std::endl;
//	//std::cout << std::endl;
//	//std::cout << "M  = (B _| Ji) _| A = " << lcont_em( lcont_em( B, inverse_em( J )), A ) << std::endl;
//	//std::cout << "J  = A ^ (Mi _| B)  = " << op( A, lcont_em( inverse_em( M ), B ) ) << std::endl;
//	//std::cout << std::endl;
//	//std::cout << std::endl;
//	//std::cout << "M_ = meet(B,A)      = " << M_ << std::endl;
//	//std::cout << "J_ = join(B,A)      = " << J_ << std::endl;
//	//std::cout << std::endl;
//	//std::cout << "M_ = (B _| Ji) _| A = " << lcont_em( lcont_em( A, inverse_em( J_ )), B ) << std::endl;
//	//std::cout << "J_ = A ^ (Mi _| B)  = " << op( B, lcont_em( inverse_em( M_ ), A ) ) << std::endl;
//	//std::cout << std::endl;
//	//**/
//
//	///**
//	//// Bechmark.
//	//static const int N = 1000000;
//
//	//btools::elapsed_time op_et, join_et;
//
//	//vector_t *vectors = new vector_t[N];
//	//bivector_t *bivectors = new bivector_t[N];
//	//
//	//for (int i=0; i<N; ++i)
//	//{
//	//	vectors[i] = rand_multivector<vector_t>( static_cast<ga::real_t>( -1 ), static_cast<ga::real_t>( 1 ) );
//	//	bivectors[i] = rand_multivector<bivector_t>( static_cast<ga::real_t>( -1 ), static_cast<ga::real_t>( 1 ) );
//	//}
//	//
//	//for (int i=0; i<N; ++i)
//	//{
//	//	op_et.begin();
//	//	op( vectors[i], bivectors[i] );
//	//	op_et.end();
//	//}
//
//	//for (int i=0; i<N; ++i)
//	//{
//	//	join_et.begin();
//	//	join( vectors[i], bivectors[i] );
//	//	join_et.end();
//	//}
//
//	//std::cout << "join / op = " << (join_et.mean_elapsed_time() / op_et.mean_elapsed_time()) << std::endl;
//	//std::cout << std::endl;
//
//	//delete [] vectors;
//	//delete [] bivectors;
//	//**/
//
//	///**
//	//multivector_t m;
//	//m.assign<true>( vector );
//
//	//std::cout << lcont( lcont( e1, m ), inverse( m ) ) << std::endl;
//	//**/
//
//	///**
//	//int i;
//	//real_t s;
//	//std::vector<vector_t> factors;
//	//std::vector<vector_t>::iterator itr;
//
//	//// Scalar.
//	//factorize_em( s, factors, real );
//	//std::cout << "s = " << s << std::endl;
//	//for (itr=factors.begin(), i=1; itr!=factors.end(); ++itr, ++i)
//	//{
//	//	std::cout << "f" << i << " = " << (*itr) << std::endl;
//	//}
//	//std::cout << real << " = " << s << std::endl;
//	//std::cout << std::endl;
//
//	//// Scalar.
//	//factorize_em( s, factors, scalar );
//	//std::cout << "s = " << s << std::endl;
//	//for (itr=factors.begin(), i=1; itr!=factors.end(); ++itr, ++i)
//	//{
//	//	std::cout << "f" << i << " = " << (*itr) << std::endl;
//	//}
//	//std::cout << scalar << " = " << s << std::endl;
//	//std::cout << std::endl;
//
//	//// Zero.
//	//factorize_em( s, factors, zero );
//	//std::cout << "s = " << s << std::endl;
//	//for (itr=factors.begin(), i=1; itr!=factors.end(); ++itr, ++i)
//	//{
//	//	std::cout << "f" << i << " = " << (*itr) << std::endl;
//	//}
//	//std::cout << zero << " = " << s << std::endl;
//	//std::cout << std::endl;
//
//	//// Vector.
//	//factorize_em( s, factors, vector );
//	//std::cout << "s = " << s << std::endl;
//	//for (itr=factors.begin(), i=1; itr!=factors.end(); ++itr, ++i)
//	//{
//	//	std::cout << "f" << i << " = " << (*itr) << std::endl;
//	//}
//	//std::cout << vector << " = " << (s ^ factors[0]) << std::endl;
//	//std::cout << std::endl;
//
//	//// e2.
//	//factorize_em( s, factors, e2 );
//	//std::cout << "s = " << s << std::endl;
//	//for (itr=factors.begin(), i=1; itr!=factors.end(); ++itr, ++i)
//	//{
//	//	std::cout << "f" << i << " = " << (*itr) << std::endl;
//	//}
//	//std::cout << e2 << " = " << (s ^ factors[0]) << std::endl;
//	//std::cout << std::endl;
//
//	//// Bivector.
//	//factorize_em( s, factors, bivector );
//	//std::cout << "s = " << s << std::endl;
//	//for (itr=factors.begin(), i=1; itr!=factors.end(); ++itr, ++i)
//	//{
//	//	std::cout << "f" << i << " = " << (*itr) << std::endl;
//	//}
//	//std::cout << bivector << " = " << (s ^ factors[0] ^ factors[1]) << std::endl;
//	//std::cout << std::endl;
//
//	//// Trivector.
//	////btools::elapsed_time et;
//	////for (int j=0; j<1000000; ++j)
//	////{
//	////	et.begin();
//	//	factorize_em( s, factors, trivector );
//	////	et.end();
//	////}
//	////std::cout << "sec.: " << et.mean_elapsed_time() << std::endl;
//	//std::cout << "s = " << s << std::endl;
//	//for (itr=factors.begin(), i=1; itr!=factors.end(); ++itr, ++i)
//	//{
//	//	std::cout << "f" << i << " = " << (*itr) << std::endl;
//	//}
//	//std::cout << trivector << " = " << (s ^ factors[0] ^ factors[1] ^ factors[2]) << std::endl;
//	//std::cout << std::endl;
//	//**/
//
//	///**/
//	//validate_unary<model>( real );
//	//validate_unary<model>( scalar );
//	//validate_unary<model>( vector );
//	//validate_unary<model>( bivector );
//	//validate_unary<model>( trivector );
//	//validate_unary<model>( multivector );
//
//	//validate_binary<model>( real, scalar );
//	//validate_binary<model>( real, vector );
//	//validate_binary<model>( real, bivector );
//	//validate_binary<model>( real, trivector );
//	//validate_binary<model>( real, multivector );
//
//	//validate_binary<model>( scalar, real );
//	//validate_binary<model>( scalar, scalar );
//	//validate_binary<model>( scalar, vector );
//	//validate_binary<model>( scalar, bivector );
//	//validate_binary<model>( scalar, trivector );
//	//validate_binary<model>( scalar, multivector );
//
//	//validate_binary<model>( vector, real );
//	//validate_binary<model>( vector, scalar );
//	//validate_binary<model>( vector, vector );
//	//validate_binary<model>( vector, bivector );
//	//validate_binary<model>( vector, trivector );
//	//validate_binary<model>( vector, multivector );
//
//	//validate_binary<model>( bivector, real );
//	//validate_binary<model>( bivector, scalar );
//	//validate_binary<model>( bivector, vector );
//	//validate_binary<model>( bivector, bivector );
//	//validate_binary<model>( bivector, trivector );
//	//validate_binary<model>( bivector, multivector );
//
//	//validate_binary<model>( trivector, real );
//	//validate_binary<model>( trivector, scalar );
//	//validate_binary<model>( trivector, vector );
//	//validate_binary<model>( trivector, bivector );
//	//validate_binary<model>( trivector, trivector );
//	//validate_binary<model>( trivector, multivector );
//
//	//validate_binary<model>( multivector, real );
//	//validate_binary<model>( multivector, scalar );
//	//validate_binary<model>( multivector, vector );
//	//validate_binary<model>( multivector, bivector );
//	//validate_binary<model>( multivector, trivector );
//	//validate_binary<model>( multivector, multivector );
//	///**/
//}
