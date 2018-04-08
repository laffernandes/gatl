#ifndef __GA_CLIFFORD_ELEMENT_ORDERING_HPP__
#define __GA_CLIFFORD_ELEMENT_ORDERING_HPP__

namespace ga {

	namespace common {

		namespace detail {

			template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, class RightBasisBladeType>
			struct lt<clifford::detail::component<LeftCoefficientType, LeftBasisBladeType>, clifford::detail::component<RightCoefficientType, RightBasisBladeType> > :
				lt<LeftBasisBladeType, RightBasisBladeType> {
			};

			template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, default_bitset_t RightPossibleGrades>
			struct lt<clifford::detail::component<LeftCoefficientType, LeftBasisBladeType>, clifford::detail::components<RightCoefficientType, RightPossibleGrades> > :
				lt<LeftBasisBladeType, clifford::detail::dbasis_blade<RightPossibleGrades> > {
			};

			template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, class RightBasisBladeType>
			struct lt<clifford::detail::components<LeftCoefficientType, LeftPossibleGrades>, clifford::detail::component<RightCoefficientType, RightBasisBladeType> > :
				lt<clifford::detail::dbasis_blade<LeftPossibleGrades>, RightBasisBladeType> {
			};

			template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, default_bitset_t RightPossibleGrades>
			struct lt<clifford::detail::components<LeftCoefficientType, LeftPossibleGrades>, clifford::detail::components<RightCoefficientType, RightPossibleGrades> > :
				lt<clifford::detail::dbasis_blade<LeftPossibleGrades>, clifford::detail::dbasis_blade<RightPossibleGrades> > {
			};

		}

	}

}

#endif // __GA_CLIFFORD_ELEMENT_ORDERING_HPP__
