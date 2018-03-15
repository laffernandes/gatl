#ifndef __GA_UNARY_MINUS_HPP__
#define __GA_UNARY_MINUS_HPP__

namespace ga {

	namespace detail {

		struct _unary_minus_neg;
		struct _unary_minus_end;

		template<class ItrType>
		constexpr decltype(auto) unary_minus(ItrType const &arg) {
			return std::conditional<!is_end<ItrType>::value, _unary_minus_neg, _unary_minus_end>::type::bind(arg);
		}

		struct _unary_minus_neg {
			template<class ItrType>
			constexpr static decltype(auto) bind(ItrType const &arg) {
				return insert(unary_minus(next(arg)), unary_minus_element(arg.element()));
			}
		};

		struct _unary_minus_end {
			template<class ItrType>
			constexpr static empty_expression bind(ItrType const &) {
				return empty_expression();
			}
		};

	}

	template<class RightType>
	constexpr decltype(auto) uminus(RightType const &rhs) {
		return detail::unary_minus(detail::begin(rhs));
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) uminus(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
		return detail::unary_minus(detail::begin(rhs));
	}

	constexpr detail::empty_expression uminus(detail::empty_expression const &) {
		return detail::empty_expression();
	}

	template<default_integral_t Value>
	constexpr detail::cvalue<-Value> uminus(detail::cvalue<Value> const &) {
		return detail::cvalue<-Value>();
	}

}

template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
constexpr decltype(auto) operator-(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
	return ga::uminus(rhs);
}

constexpr ga::detail::empty_expression operator-(ga::detail::empty_expression const &) {
	return ga::detail::empty_expression();
}

template<ga::default_integral_t Value>
constexpr ga::detail::cvalue<-Value> operator-(ga::detail::cvalue<Value> const &) {
	return ga::detail::cvalue<-Value>();
}

#endif // __GA_UNARY_MINUS_HPP__
