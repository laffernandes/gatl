template<uint32_t Index>
inline
multivector<uint32_t, ga::detail::tree<ga::detail::pack<ga::detail::single_basis_blade</*TODO Implementar*/, ga::detail::static_value<1> >, ga::detail::identity_operation>, ga::detail::empty_tree, ga::detail::empty_tree> >
make_basis_vector() {
	return /*TODO Implementar*/;
}

inline
multivector<uint32_t, ga::detail::tree<ga::detail::pack<ga::detail::single_basis_blade</*TODO Implementar*/, ga::detail::static_value<1> >, ga::detail::identity_operation>, ga::detail::empty_tree, ga::detail::empty_tree> >
make_basis_vector(uint32_t&& index) {
	return /*TODO Implementar*/;
}

template<uint32_t Index>
inline
auto e()->decltype(make_basis_vector<Index>()) {
	return make_basis_vector<Index>();
}

inline
auto e(uint32_t&& index)->decltype(make_basis_vector(index)) {
	return make_basis_vector(index);
}
