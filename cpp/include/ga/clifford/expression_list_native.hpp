#ifndef __GA_CLIFFORD_EXPRESSION_LIST_NATIVE_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_NATIVE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class CoefficientType>
			struct may_cast_to_native<expression_list<component<CoefficientType, cbasis_blade<0> >, empty_clifford_expression> > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_list<component<CoefficientType, dbasis_blade<default_bitset_t(1)> >, empty_clifford_expression> > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_list<components<CoefficientType, default_bitset_t(1)>, empty_clifford_expression> > {
				constexpr static bool value = true;
			};

		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_list<detail::component<CoefficientType, detail::cbasis_blade<0> >, detail::empty_clifford_expression> const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_list<detail::component<CoefficientType, detail::dbasis_blade<default_bitset_t(1)> >, detail::empty_clifford_expression> const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_list<detail::components<CoefficientType, default_bitset_t(1)>, detail::empty_clifford_expression> const &arg) {
			return native(arg.element().begin()->second);
		}

		template<class ElementType, class NextListType>
		constexpr decltype(auto) native(detail::expression_list<ElementType, NextListType> const &) = delete;

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_NATIVE_HPP__
