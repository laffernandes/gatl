#ifndef __GA_ELEMENT_BINARY_PLUS_HPP__
#define __GA_ELEMENT_BINARY_PLUS_HPP__

namespace ga {

	namespace detail {

		template<class LeftCoefficientType, default_bitset_t BasisBlade, class RightCoefficientType>
		constexpr decltype(auto) binary_plus_element(component<LeftCoefficientType, cbasis_blade<BasisBlade> > const &lhs, component<RightCoefficientType, cbasis_blade<BasisBlade> > const &rhs) {
			return make_component(add(lhs.coefficient(), rhs.coefficient()), cbasis_blade<BasisBlade>());
		}

		template<class LeftCoefficientType, default_bitset_t PossibleGrades, class RightCoefficientType>
		constexpr decltype(auto) binary_plus_element(component<LeftCoefficientType, dbasis_blade<PossibleGrades> > const &lhs, component<RightCoefficientType, dbasis_blade<PossibleGrades> > const &rhs) {
			//TODO lazy
			typedef typename std::common_type<LeftCoefficientType, RightCoefficientType, decltype(add(LeftCoefficientType(), RightCoefficientType()))>::type coefficient_t;
			components<coefficient_t, PossibleGrades> result;
			if (lhs.basis_blade().value() == rhs.basis_blade().value()) {
				auto result_coefficient = add(lhs.coefficient(), rhs.coefficient());
				if (result_coefficient != 0) {
					result.insert(lhs.basis_blade(), result_coefficient);
				}
			}
			else {
				if (lhs.coefficient() != 0) {
					result.insert(lhs.basis_blade(), lhs.coefficient());
				}
				if (rhs.coefficient() != 0) {
					result.insert(rhs.basis_blade(), rhs.coefficient());
				}
			}
			return result;
		}

		template<class LeftCoefficientType, default_bitset_t PossibleGrades, class RightCoefficientType>
		constexpr decltype(auto) binary_plus_element(components<LeftCoefficientType, PossibleGrades> const &lhs, components<RightCoefficientType, PossibleGrades> const &rhs) {
			//TODO lazy
			typedef decltype(add(std::common_type<LeftCoefficientType, RightCoefficientType>::type(), RightCoefficientType())) coefficient_t;
			components<coefficient_t, PossibleGrades> result;
			for (auto itr = lhs.begin(), end = lhs.end(); itr != end; ++itr) {
				result.insert(itr->first, itr->second);
			}
			for (auto itr = rhs.begin(), end = rhs.end(); itr != end; ++itr) {
				auto result_itr = result.find(itr->first);
				if (result_itr == result.end()) {
					result.insert(itr->first, itr->second);
				}
				else {
					auto new_coefficient = add(result_itr->second, itr->second);
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

#endif // __GA_ELEMENT_BINARY_PLUS_HPP__
