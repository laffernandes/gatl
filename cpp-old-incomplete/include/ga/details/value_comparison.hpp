template<int Value1, int Value2>
struct less<ga::details::static_value<Value1>, ga::details::static_value<Value2> > :
	bool_<(Value1 < Value2)> {};

template<int Value1>
struct less<ga::details::static_value<Value1>, ga::details::dynamic_value> :
	true_ {};

template<int Value2>
struct less<ga::details::dynamic_value, ga::details::static_value<Value2> > :
	false_ {};

template<ga::details::bitset_element_t Bits1, class Next1>
struct less<ga::details::static_bitset<Bits1, Next1>, ga::details::dynamic_value> :
	true_ {};

template<ga::details::bitset_element_t Bits2, class Next2>
struct less<ga::details::dynamic_value, ga::details::static_bitset<Bits2, Next2> > :
	false_ {};

template<>
struct less<ga::details::dynamic_value, ga::details::dynamic_value> :
	false_ {};
