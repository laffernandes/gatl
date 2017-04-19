#define _GA_DEFINE_MAKE_SCALAR_COMPILE_TIME(COEFFICIENT_TYPE) \
	template<COEFFICIENT_TYPE Value> \
	inline \
	multivector<COEFFICIENT_TYPE, ga::detail::tree<ga::detail::pack<ga::detail::single_basis_blade</*TODO Implementar*/, ga::detail::static_value<Value> >, ga::detail::identity_operation>, ga::detail::empty_tree, ga::detail::empty_tree> > \
	make_scalar() { \
		return /*TODO Implementar*/; \
	}

#define _GA_DEFINE_MAKE_SCALAR_RUNTIME(COEFFICIENT_TYPE) \
	inline \
	multivector<COEFFICIENT_TYPE, ga::detail::tree<ga::detail::pack<ga::detail::single_basis_blade</*TODO Implementar*/, ga::detail::dynamic_value>, ga::detail::identity_operation>, ga::detail::empty_tree, ga::detail::empty_tree> > \
	make_scalar(COEFFICIENT_TYPE&& value) { \
		return /*TODO Implementar*/; \
	}

_GA_DEFINE_MAKE_SCALAR_COMPILE_TIME(int8_t)
_GA_DEFINE_MAKE_SCALAR_COMPILE_TIME(int16_t)
_GA_DEFINE_MAKE_SCALAR_COMPILE_TIME(int32_t)
_GA_DEFINE_MAKE_SCALAR_COMPILE_TIME(int64_t)

_GA_DEFINE_MAKE_SCALAR_RUNTIME(int8_t)
_GA_DEFINE_MAKE_SCALAR_RUNTIME(int16_t)
_GA_DEFINE_MAKE_SCALAR_RUNTIME(int32_t)
_GA_DEFINE_MAKE_SCALAR_RUNTIME(int64_t)

_GA_DEFINE_MAKE_SCALAR_RUNTIME(float)
_GA_DEFINE_MAKE_SCALAR_RUNTIME(double)
_GA_DEFINE_MAKE_SCALAR_RUNTIME(long double)
