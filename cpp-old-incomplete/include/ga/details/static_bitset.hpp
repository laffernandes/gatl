// Bitset concept implementation for compile-time defined bitset.
template<bitset_element_t Bits, class Next = void>
struct static_bitset {

	typedef static_bitset     type;

	typedef compile_time_tag  time;

	typedef bitset_element_t  element_type;
	typedef Next              next;

	static const element_type bits = Bits;
	static const ::size_t     nbytes = sizeof(element_type) + Next::nbytes;

public:

	inline static
	dynamic_bitset_t make_dynamic() {
		dynamic_bitset_t result;
		fill_dynamic_bitset(result, 0);
		return result;
	}

private:

	inline static
	void fill_dynamic_bitset(dynamic_bitset_t &result, const ::size_t offset) {
		static_bitset<Bits, void>::fill_dynamic_bitset(result, offset);
		Next::fill_dynamic_bitset(result, offset + sizeof(element_type));
	}

	template<bitset_element_t, class> friend struct static_bitset;
};

template<bitset_element_t Bits>
struct static_bitset<Bits, void> {

	typedef static_bitset     type;

	typedef compile_time_tag  time;

	typedef bitset_element_t  element_type;
	typedef void              next;

	static const element_type bits = Bits;
	static const ::size_t     nbytes = sizeof(element_type);

public:

	inline static
	dynamic_bitset_t make_dynamic() {
		dynamic_bitset_t result;
		fill_dynamic_bitset(result, 0);
		return result;
	}

private:

	inline static
	void fill_dynamic_bitset(dynamic_bitset_t &result, ::size_t index) {
		element_type mask = bits;
		while (mask != 0) {
			if ((mask & 1) != 0) {
				result.set(index);
			}
			++index;
			mask >>= 1;
		}
	}

	template<bitset_element_t, class> friend struct static_bitset;
};

// Bitset function any<>.
template<class Bitset>
struct any :
	any<typename Bitset::type> {};

template<bitset_element_t Bits, class Next>
struct any<static_bitset<Bits, Next> > :
	or_<bool_<(Bits != 0)>, any<Next> > {};

template<bitset_element_t Bits>
struct any<static_bitset<Bits, void> > :
	bool_<(Bits != 0)> {};

// Bitset function cardinalidy.
template<class X, int digits>
struct _ones;
			
template<class X>
struct _ones<X, 32> {
private:

	static const typename X::value_type a = (X::value & 0x55555555) + ((X::value >> 1) & 0x55555555);
	static const typename X::value_type b = (a & 0x33333333) + ((a >> 2) & 0x33333333);
	static const typename X::value_type c = (b + (b >> 4)) & 0x0F0F0F0F;

public:

	static const ::size_t value = (c * 0x01010101) >> 24;
};

template<class X>
struct _ones<X, 64> {
private:

	static const typename X::value_type a = (X::value & 0x5555555555555555) + ((X::value >> 1) & 0x5555555555555555);
	static const typename X::value_type b = (a & 0x3333333333333333) + ((a >> 2) & 0x3333333333333333);
	static const typename X::value_type c = (b & 0x0F0F0F0F0F0F0F0F) + ((b >> 4) & 0x0F0F0F0F0F0F0F0F);

public:

	static const ::size_t value = (c * 0x0101010101010101) >> 56;
};

template<class Bitset>
struct cardinality :
	cardinality<typename Bitset::type> {};

template<bitset_element_t Bits, class Next>
struct cardinality<static_bitset<Bits, Next> > :
	integral_c<::size_t, _ones<integral_c<bitset_element_t, Bits>, integer_traits<bitset_element_t>::digits>::value + cardinality<Next>::value> {};

template<bitset_element_t Bits>
struct cardinality<static_bitset<Bits, void> > :
	integral_c<::size_t, _ones<integral_c<bitset_element_t, Bits>, integer_traits<bitset_element_t>::digits>::value> {};

// Count the number of zero bits succeeding the least significant one bit.
template<class Bitset>
struct count_trailing_zeros;

template<bitset_element_t X, int digits = (integer_traits<bitset_element_t>::digits >> 1)>
struct _count_trailing_zeros_current;

template<bitset_element_t X, int digits>
struct _count_trailing_zeros_current_inc :
	integral_c<::size_t, digits + _count_trailing_zeros_current<(X >> digits), (digits >> 1)>::value> {};

template<bitset_element_t X, int digits>
struct _count_trailing_zeros_current :
	eval_if_c<((X & ((bitset_element_t(1) << digits) - 1)) == 0), _count_trailing_zeros_current_inc<X, digits>, _count_trailing_zeros_current<X, (digits >> 1)> > {};

template<bitset_element_t X>
struct _count_trailing_zeros_current<X, 1> :
	integral_c<::size_t, (((X & 0x00000001) == 0) ? 1 : 0)> {};

template<class Next>
struct _count_trailing_zeros_next :
	integral_c<::size_t, integer_traits<bitset_element_t>::digits + count_trailing_zeros<Next>::value> {};

template<bitset_element_t Bits, class Next>
struct count_trailing_zeros<static_bitset<Bits, Next> > :
	eval_if_c<(Bits != 0), _count_trailing_zeros_current<Bits>, _count_trailing_zeros_next<Next> > {};

template<bitset_element_t Bits>
struct count_trailing_zeros<static_bitset<Bits, void> > :
	eval_if_c<(Bits != 0), _count_trailing_zeros_current<Bits>, integral_c<::size_t, integer_traits<bitset_element_t>::digits> > {};

// Bitset function set<>.
template<class Bitset, ::size_t Index>
struct set :
	set<typename Bitset::type, Index> {};

template<bitset_element_t Bits, class Next, ::size_t Index>
struct _set_current :
	static_bitset<(Bits | (bitset_element_t(1) << Index)), Next> {};

template<bitset_element_t Bits, class Next, ::size_t Index>
struct _set_next :
	static_bitset<Bits, typename set<Next, Index - integer_traits<bitset_element_t>::digits>::type> {};

template<bitset_element_t Bits, class Next, ::size_t Index>
struct set<static_bitset<Bits, Next>, Index> :
	eval_if_c<(Index < integer_traits<bitset_element_t>::digits), _set_current<Bits, Next, Index>, _set_next<Bits, Next, Index> > {};

template<bitset_element_t Bits, ::size_t Index>
struct set<static_bitset<Bits, void>, Index> :
	_set_current<Bits, void, Index> {};

// Bitset function unset<>.
template<class Bitset, ::size_t Index>
struct unset :
	unset<typename Bitset::type, Index> {};

template<bitset_element_t Bits, class Next, ::size_t Index>
struct _unset_current :
	static_bitset<(Bits & ~(bitset_element_t(1) << Index)), Next> {};

template<bitset_element_t Bits, class Next, ::size_t Index>
struct _unset_next :
	static_bitset<Bits, typename unset<Next, Index - integer_traits<bitset_element_t>::digits>::type> {};

template<bitset_element_t Bits, class Next, ::size_t Index>
struct unset<static_bitset<Bits, Next>, Index> :
	eval_if_c<(Index < integer_traits<bitset_element_t>::digits), _unset_current<Bits, Next, Index>, _unset_next<Bits, Next, Index> > {};

template<bitset_element_t Bits, ::size_t Index>
struct unset<static_bitset<Bits, void>, Index> :
	_unset_current<Bits, void, Index>{};

// Bitset function complement<>.
template<class Bitset>
struct complement :
	complement<typename Bitset::type> {};

template<bitset_element_t Bits, class Next>
struct complement<static_bitset<Bits, Next> > :
	static_bitset<~Bits, typename complement<Next>::type> {};

template<bitset_element_t Bits>
struct complement<static_bitset<Bits, void>> :
	static_bitset<~Bits, void> {};

// Build an empty bitset of size N.
template<int N = GA_MAX_NDIMS>
struct make_empty_bitset;

template<int N>
struct _make_empty_bitset_full :
	static_bitset<0, typename make_empty_bitset<N - integer_traits<bitset_element_t>::digits>::type> {};

template<int N>
struct _make_empty_bitset_partial :
	static_bitset<0, void> {};

template<int N>
struct make_empty_bitset :
	eval_if_c<(N >= integer_traits<bitset_element_t>::digits), _make_empty_bitset_full<N>, _make_empty_bitset_partial<N> >{};

// Build a bitset that represents the pseudoscalar of some n-dimensional space.
template<int N = GA_MAX_NDIMS>
struct make_pseudoscalar_bitset;

template<int N>
struct _make_pseudoscalar_bitset_full :
	static_bitset<~bitset_element_t(0), typename make_pseudoscalar_bitset<N - integer_traits<bitset_element_t>::digits>::type> {};

template<int N>
struct _make_pseudoscalar_bitset_partial :
	static_bitset<(bitset_element_t(1) << N) - 1, void> {};

template<int N>
struct make_pseudoscalar_bitset :
	eval_if_c<(N >= integer_traits<bitset_element_t>::digits), _make_pseudoscalar_bitset_full<N>, _make_pseudoscalar_bitset_partial<N> > {};
