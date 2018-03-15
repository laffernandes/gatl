#ifndef __GA_BINARY_MINUS_ELEMENT_HPP__
#define __GA_BINARY_MINUS_ELEMENT_HPP__

namespace ga {

	namespace detail {

		//TODO Try it!

		template<class LeftCoefficientType, default_bitset_t BasisBlade, class RightCoefficientType>
		constexpr decltype(auto) binary_minus_element(component<LeftCoefficientType, cbasis_blade<BasisBlade> > const &lhs, component<RightCoefficientType, cbasis_blade<BasisBlade> > const &rhs) {
			return make_component(sub(lhs.coefficient(), rhs.coefficient()), cbasis_blade<BasisBlade>());
		}

		template<class LeftCoefficientType, default_bitset_t PossibleGrades, class RightCoefficientType>
		constexpr decltype(auto) binary_minus_element(component<LeftCoefficientType, dbasis_blade<PossibleGrades> > const &lhs, component<RightCoefficientType, dbasis_blade<PossibleGrades> > const &rhs) {
			//TODO lazy
			components<typename std::common_type<LeftCoefficientType, RightCoefficientType>::type, PossibleGrades> result;
			if (lhs.basis_blade().value() == rhs.basis_blade().value()) {
				result.emplace(sub(lhs.coefficient(), rhs.coefficient()), lhs.basis_blade());
			}
			else {
				result.emplace(lhs.coefficient(), lhs.basis_blade());
				result.emplace(neg(rhs.coefficient()), rhs.basis_blade());
			}
			return result;
		}

		template<class LeftCoefficientType, default_bitset_t PossibleGrades, class RightCoefficientType>
		constexpr decltype(auto) binary_minus_element(components<LeftCoefficientType, PossibleGrades> const &lhs, components<RightCoefficientType, PossibleGrades> const &rhs) {
			//TODO lazy
			components<typename std::common_type<LeftCoefficientType, RightCoefficientType>::type, PossibleGrades> result;
			for (auto itr = lhs.begin(), end = lhs.end(); itr != end; ++itr) {
				result.emplace(itr->first, itr->second);
			}
			for (auto itr = rhs.begin(), end = rhs.end(); itr != end; ++itr) {
				auto curr = result.find(itr->first);
				if (curr == result.end()) {
					result.emplace(itr->first, neg(itr->second));
				}
				else {
					curr->second = sub(curr->second, itr->second);
				}
			}
			return result;
		}

	}

}

#endif // __GA_BINARY_MINUS_ELEMENT_HPP__
