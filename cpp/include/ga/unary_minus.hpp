namespace detail {

	// Functor for computing -1, for any k = grade(A)
	//   GradeComponent must be a dynamic_value or a static_value<> structure.
	template<class GradeComponent>
	struct uminus_sign_change {

		typedef static_value<-1> result;

		inline static
		int32_t eval(int32_t&&) = nullptr;
	};

	// Unary minus expression (-A).
	//   Argument must be a multivector<> structure.
	template<class Argument>
	class uminus_expression : public sign_change_expression<
			Argument,
			uminus_sign_change
		> {};

}

_GA_DEFINE_UNARY_NON_METRIC_OPERATION(uminus)

template<class CoefficientType, class Composition, ga::detail::container_class Container>
inline
auto operator - (multivector<CoefficientType, Composition, Container>&& m)->decltype(uminus(m)) {
	return uminus(m);
}
