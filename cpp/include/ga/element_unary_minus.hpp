#ifndef __GA_ELEMENT_UNARY_MINUS_HPP__
#define __GA_ELEMENT_UNARY_MINUS_HPP__

namespace ga {

	namespace detail {

		template<class CoefficientType, class BasisBladeType>
		constexpr decltype(auto) unary_minus_element(component<CoefficientType, BasisBladeType> const &arg) {
			return make_component(neg(arg.coefficient()), arg.basis_blade());
		}

		template<class CoefficientType, default_bitset_t PossibleGrades>
		constexpr decltype(auto) unary_minus_element(components<CoefficientType, PossibleGrades> const &arg) {
			//TODO lazy
			components<CoefficientType, PossibleGrades> result;
			for (auto itr = arg.begin(), end = arg.end(); itr != end; ++itr) {
				result.insert(itr->first, neg(itr->second));
			}
			return result;
		}

	}

}

#endif // __GA_ELEMENT_UNARY_MINUS_HPP__
