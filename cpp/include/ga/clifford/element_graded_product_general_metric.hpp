#ifndef __GA_CLIFFORD_ELEMENT_GRADED_PRODUCT_GENERAL_METRIC__
#define __GA_CLIFFORD_ELEMENT_GRADED_PRODUCT_GENERAL_METRIC__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class LeftBasisBladeType, class RightBasisBladeType>
			struct _general_graded_product_component;
			//TODO Implementar

			template<default_bitset_t ResultPossibleGrades>
			struct _general_graded_product_components_maybe_eval;
			//TODO Implementar

			template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, class RightBasisBladeType, class GeneralMetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_element(component<LeftCoefficientType, LeftBasisBladeType> const &lhs, component<RightCoefficientType, RightBasisBladeType> const &rhs, metric_space<general_metric_space<GeneralMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
				return make_simple_clifford_expression(_general_graded_product_component<LeftBasisBladeType, RightBasisBladeType>::bind(lhs, rhs, mtr, keep));
			}

			template<class LeftElementType, class RightElementType, class GeneralMetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_element(LeftElementType const &lhs, RightElementType const &rhs, metric_space<general_metric_space<GeneralMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
				return make_simple_clifford_expression(_general_graded_product_components_maybe_eval<KeepIfGradesFunc::template possible_grades<LeftElementType::basis_blade_type::possible_grades(), RightElementType::basis_blade_type::possible_grades(), GeneralMetricSpaceType::vector_space_dimension()>::value>::bind(lhs, rhs, mtr, keep));
			}

		}

	}

}

#endif // __GA_CLIFFORD_ELEMENT_GRADED_PRODUCT_GENERAL_METRIC__