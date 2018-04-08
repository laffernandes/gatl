#ifndef __GA_CLIFFORD_ELEMENT_UNARY_MINUS_HPP__
#define __GA_CLIFFORD_ELEMENT_UNARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class CoefficientType, class BasisBladeType>
			constexpr decltype(auto) unary_minus_element(component<CoefficientType, BasisBladeType> const &arg) {
				return make_component(-arg.coefficient(), arg.basis_blade());
			}

			template<class CoefficientType, default_bitset_t PossibleGrades>
			constexpr decltype(auto) unary_minus_element(components<CoefficientType, PossibleGrades> const &arg) {
				//TODO lazy
				components<CoefficientType, PossibleGrades> result;
				for (auto itr = arg.begin(), end = arg.end(); itr != end; ++itr) {
					result.insert(itr->first, -itr->second);
				}
				return result;
			}

		}

	}

}

#endif // __GA_CLIFFORD_ELEMENT_UNARY_MINUS_HPP__
