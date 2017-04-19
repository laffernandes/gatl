// Sum of two instances of the implementation of the value concept.
template<class Value1, class Value2>
struct plus :
	plus<typename Value1::type, typename Value2::type> {};

template<int Value1, int Value2>
struct plus<static_value<Value1>, static_value<Value2> > :
	static_value<Value1 + Value2> {};

template<int Value1>
struct plus<static_value<Value1>, dynamic_value> :
	dynamic_value {};

template<int Value2>
struct plus<dynamic_value, static_value<Value2> > :
	dynamic_value {};

template<>
struct plus<dynamic_value, dynamic_value> :
	dynamic_value {};

// k-Combinations.
template<class N, class K>
struct combs;

template<class T, T N, class K>
struct combs<integral_c<T, N>, K> :
	combs<static_value<N>, K> {};

template<class N, class T, T K>
struct combs<N, integral_c<T, K> > :
	combs<N, static_value<K> > {};

template<class T1, T1 N, class T2, T2 K>
struct combs<integral_c<T1, N>, integral_c<T2, K> > :
	combs<static_value<N>, static_value<K> > {};

template<class N, class K>
struct _combs :
	plus<combs<static_value<N::value - 1>, static_value<K::value - 1> >, combs<static_value<N::value - 1>, K> > {};

template<int N, int K>
struct combs<static_value<N>, static_value<K> > :
	eval_if<less<static_value<N>, static_value<K> >, static_value<0>, _combs<static_value<N>, static_value<K> > > {};

template<int N>
struct combs<static_value<N>, static_value<N> > :
	static_value<1> {};

template<int N>
struct combs<static_value<N>, static_value<0> > :
	static_value<1> {};

template<>
struct combs<static_value<0>, static_value<0> > :
	static_value<1> {};

template<int K>
struct combs<dynamic_value, static_value<K> > :
	dynamic_value {};

template<int N>
struct combs<static_value<N>, dynamic_value> :
	dynamic_value {};

template<>
struct combs<dynamic_value, dynamic_value> :
	dynamic_value {};

// Check whether the given valus is equal to zero.
template<class T>
struct is_zero :
	false_ {};

template<>
struct is_zero<static_value<0> > :
	true_ {};
