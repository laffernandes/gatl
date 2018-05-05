#ifndef __GA_CLIFFORD_EXPRESSION_LIST_NATIVE_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_NATIVE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class CoefficientType>
			struct may_cast_to_native<expression_list<component<CoefficientType, cbasis_blade<0> > > > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_list<component<CoefficientType, dbasis_blade<default_bitset_t(1)> > > > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_list<components<CoefficientType, default_bitset_t(1)> > > {
				constexpr static bool value = true;
			};

		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_list<detail::component<CoefficientType, detail::cbasis_blade<0> > > const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_list<detail::component<CoefficientType, detail::dbasis_blade<default_bitset_t(1)> > > const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_list<detail::components<CoefficientType, default_bitset_t(1)> > const &arg) {
			return native(arg.element().begin()->second);
		}

		template<class ElementType, class... OtherElementTypes>
		constexpr decltype(auto) native(detail::expression_list<ElementType, OtherElementTypes...> const &) = delete;

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_NATIVE_HPP__
