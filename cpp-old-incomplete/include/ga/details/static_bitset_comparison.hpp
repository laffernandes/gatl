template<ga::details::bitset_element_t Bits1, class Next1, ga::details::bitset_element_t Bits2, class Next2>
struct equal<ga::details::static_bitset<Bits1, Next1>, ga::details::static_bitset<Bits2, Next2> > :
	and_<bool_<(Bits1 == Bits2)>, equal<Next1, Next2> > {};

template<ga::details::bitset_element_t Bits1, ga::details::bitset_element_t Bits2, class Next2>
struct equal<ga::details::static_bitset<Bits1, void>, ga::details::static_bitset<Bits2, Next2> > :
	and_<bool_<(Bits1 == Bits2)>, not_<ga::details::any<Next2> > > {};

template<ga::details::bitset_element_t Bits1, class Next1, ga::details::bitset_element_t Bits2>
struct equal<ga::details::static_bitset<Bits1, Next1>, ga::details::static_bitset<Bits2, void> > :
	and_<bool_<(Bits1 == Bits2)>, not_<ga::details::any<Next1> > > {};

template<ga::details::bitset_element_t Bits1, ga::details::bitset_element_t Bits2>
struct equal<ga::details::static_bitset<Bits1, void>, ga::details::static_bitset<Bits2, void> > :
	bool_<(Bits1 == Bits2)> {};

template<ga::details::bitset_element_t Bits1, class Next1, ga::details::bitset_element_t Bits2, class Next2>
struct less<ga::details::static_bitset<Bits1, Next1>, ga::details::static_bitset<Bits2, Next2> > :
	or_<less<Next1, Next2>, and_<not_<less<Next2, Next1> >, bool_<(Bits1 < Bits2)> > > {};

template<ga::details::bitset_element_t Bits1, ga::details::bitset_element_t Bits2, class Next2>
struct less<ga::details::static_bitset<Bits1, void>, ga::details::static_bitset<Bits2, Next2> > :
	ga::details::any<ga::details::static_bitset<Bits2, Next2> > {};

template<ga::details::bitset_element_t Bits1, class Next1, ga::details::bitset_element_t Bits2>
struct less<ga::details::static_bitset<Bits1, Next1>, ga::details::static_bitset<Bits2, void> > :
	false_ {};

template<ga::details::bitset_element_t Bits1, ga::details::bitset_element_t Bits2>
struct less<ga::details::static_bitset<Bits1, void>, ga::details::static_bitset<Bits2, void> > :
	bool_<(Bits1 < Bits2)> {};
