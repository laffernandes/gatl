#ifndef __GA_BINARY_MINUS_ELEMENT_HPP__
#define __GA_BINARY_MINUS_ELEMENT_HPP__

namespace ga {

	namespace detail {

		template<class LeftCoefficientType, default_bitset_t BasisBlade, class RightCoefficientType>
		constexpr decltype(auto) binary_minus_element(component<LeftCoefficientType, cbasis_blade<BasisBlade> > const &lhs, component<RightCoefficientType, cbasis_blade<BasisBlade> > const &rhs) {
			return make_component(sub(lhs.coefficient(), rhs.coefficient()), cbasis_blade<BasisBlade>());
		}

		template<class LeftCoefficientType, default_bitset_t PossibleGrades, class RightCoefficientType>
		constexpr decltype(auto) binary_minus_element(component<LeftCoefficientType, dbasis_blade<PossibleGrades> > const &lhs, component<RightCoefficientType, dbasis_blade<PossibleGrades> > const &rhs) {
			//TODO lazy
			typedef typename std::common_type<LeftCoefficientType, RightCoefficientType, decltype(sub(LeftCoefficientType(), RightCoefficientType()))>::type coefficient_t;
			components<coefficient_t, PossibleGrades> result;
			if (lhs.basis_blade().value() == rhs.basis_blade().value()) {
				auto result_coefficient = sub(lhs.coefficient(), rhs.coefficient());
				if (result_coefficient != 0) {
					result.insert(lhs.basis_blade(), result_coefficient);
				}
			}
			else {
				if (lhs.coefficient() != 0) {
					result.insert(lhs.basis_blade(), lhs.coefficient());
				}
				if (rhs.coefficient() != 0) {
					result.insert(rhs.basis_blade(), neg(rhs.coefficient()));
				}
			}
			return result;
		}

		template<class LeftCoefficientType, default_bitset_t PossibleGrades, class RightCoefficientType>
		constexpr decltype(auto) binary_minus_element(components<LeftCoefficientType, PossibleGrades> const &lhs, components<RightCoefficientType, PossibleGrades> const &rhs) {
			//TODO lazy
			typedef decltype(sub(std::common_type<LeftCoefficientType, decltype(neg(RightCoefficientType()))>::type(), RightCoefficientType())) coefficient_t;
			components<coefficient_t, PossibleGrades> result;
			for (auto itr = lhs.begin(), end = lhs.end(); itr != end; ++itr) {
				result.insert(itr->first, itr->second);
			}
			for (auto itr = rhs.begin(), end = rhs.end(); itr != end; ++itr) {
				auto result_itr = result.find(itr->first);
				if (result_itr == result.end()) {
					result.insert(itr->first, neg(itr->second));
				}
				else {
					auto new_coefficient = sub(result_itr->second, itr->second);
					if (new_coefficient != 0) {
						result_itr->second = new_coefficient;
					}
					else {
						result.erase(result_itr);
					}
				}
			}
			return result;
		}

	}

}

#endif // __GA_BINARY_MINUS_ELEMENT_HPP__
