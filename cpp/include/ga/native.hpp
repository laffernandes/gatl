#ifndef __GA_NATIVE_HPP__
#define __GA_NATIVE_HPP__

namespace ga {

	namespace detail {

		template<class Type>
		struct may_cast_to_native {
			constexpr static bool value = false;
		};

		template<class CoefficientType>
		struct may_cast_to_native<expression<component<CoefficientType, cbasis_blade<0> >, empty_expression, empty_expression> > {
			constexpr static bool value = true;
		};

		template<class CoefficientType>
		struct may_cast_to_native<expression<component<CoefficientType, dbasis_blade<default_bitset_t(1)> >, empty_expression, empty_expression> > {
			constexpr static bool value = true;
		};

		template<class CoefficientType>
		struct may_cast_to_native<expression<components<CoefficientType, default_bitset_t(1)>, empty_expression, empty_expression> > {
			constexpr static bool value = true;
		};

		template<>
		struct may_cast_to_native<empty_expression> {
			constexpr static bool value = true;
		};

	}

	template<class Type>
	constexpr Type native(Type const &arg) {
		return arg;
	}

	template<class CoefficientType>
	constexpr decltype(auto) native(detail::expression<detail::component<CoefficientType, detail::cbasis_blade<0> >, detail::empty_expression, detail::empty_expression> const &arg) {
		return native(arg.element().coefficient());
	}

	template<class CoefficientType>
	constexpr decltype(auto) native(detail::expression<detail::component<CoefficientType, detail::dbasis_blade<default_bitset_t(1)> >, detail::empty_expression, detail::empty_expression> const &arg) {
		return native(arg.element().coefficient());
	}

	template<class CoefficientType>
	constexpr decltype(auto) native(detail::expression<detail::components<CoefficientType, default_bitset_t(1)>, detail::empty_expression, detail::empty_expression> const &arg) {
		return native(arg.element().begin()->second);
	}

	constexpr decltype(auto) native(detail::empty_expression const &) {
		return ga::detail::cvalue<0>();
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) native(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &) = delete;

}

#endif // __GA_NATIVE_HPP__
