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
			components<typename std::common_type<LeftCoefficientType, RightCoefficientType>::type, PossibleGrades> result;
			if (lhs.basis_blade().value() == rhs.basis_blade().value()) {
				result.insert(lhs.basis_blade(), add(lhs.coefficient(), rhs.coefficient()));
			}
			else {
				result.insert(lhs.basis_blade(), lhs.coefficient());
				result.insert(rhs.basis_blade(), rhs.coefficient());
			}
			return result;
		}

		template<class LeftCoefficientType, default_bitset_t PossibleGrades, class RightCoefficientType>
		constexpr decltype(auto) binary_plus_element(components<LeftCoefficientType, PossibleGrades> const &lhs, components<RightCoefficientType, PossibleGrades> const &rhs) {
			//TODO lazy
			components<typename std::common_type<LeftCoefficientType, RightCoefficientType>::type, PossibleGrades> result;
			for (auto itr = lhs.begin(), end = lhs.end(); itr != end; ++itr) {
				result.insert(itr->first, itr->second);
			}
			for (auto itr = rhs.begin(), end = rhs.end(); itr != end; ++itr) {
				auto curr = result.find(itr->first);
				if (curr == result.end()) {
					result.insert(itr->first, itr->second);
				}
				else {
					curr->second = add(curr->second, itr->second);
				}
			}
			return result;
		}

	}

}

#endif // __GA_ELEMENT_BINARY_PLUS_HPP__
