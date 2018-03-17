/**
#ifndef __GA_ELEMENT_ORDERING_HPP__
#define __GA_ELEMENT_ORDERING_HPP__

namespace ga {

	namespace detail {

		template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, class RightBasisBladeType>
		struct lt<component<LeftCoefficientType, LeftBasisBladeType>, component<RightCoefficientType, RightBasisBladeType> > :
			lt<LeftBasisBladeType, RightBasisBladeType> {
		};

		template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, default_bitset_t RightPossibleGrades>
		struct lt<component<LeftCoefficientType, LeftBasisBladeType>, components<RightCoefficientType, RightPossibleGrades> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, class RightBasisBladeType>
		struct lt<components<LeftCoefficientType, LeftPossibleGrades>, component<RightCoefficientType, RightBasisBladeType> > {
			constexpr static bool value = false;
		};

		template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, default_bitset_t RightPossibleGrades>
		struct lt<components<LeftCoefficientType, LeftPossibleGrades>, components<RightCoefficientType, RightPossibleGrades> > :
			lt<dbasis_blade<LeftPossibleGrades>, dbasis_blade<RightPossibleGrades> > {
		};

	}

}

#endif // __GA_ELEMENT_ORDERING_HPP__
/*/
#ifndef __GA_ELEMENT_ORDERING_HPP__
#define __GA_ELEMENT_ORDERING_HPP__

namespace ga {

	namespace detail {

		template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, class RightBasisBladeType>
		struct lt<component<LeftCoefficientType, LeftBasisBladeType>, component<RightCoefficientType, RightBasisBladeType> > :
			lt<LeftBasisBladeType, RightBasisBladeType> {
		};

		template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, default_bitset_t RightPossibleGrades>
		struct lt<component<LeftCoefficientType, LeftBasisBladeType>, components<RightCoefficientType, RightPossibleGrades> > :
			le<LeftBasisBladeType, dbasis_blade<RightPossibleGrades> > {
		};

		template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, class RightBasisBladeType>
		struct lt<components<LeftCoefficientType, LeftPossibleGrades>, component<RightCoefficientType, RightBasisBladeType> > :
			lt<dbasis_blade<LeftPossibleGrades>, RightBasisBladeType> {
		};

		template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, default_bitset_t RightPossibleGrades>
		struct lt<components<LeftCoefficientType, LeftPossibleGrades>, components<RightCoefficientType, RightPossibleGrades> > :
			lt<dbasis_blade<LeftPossibleGrades>, dbasis_blade<RightPossibleGrades> > {
		};

	}

}

#endif // __GA_ELEMENT_ORDERING_HPP__
/**/