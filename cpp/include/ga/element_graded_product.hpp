#ifndef __GA_ELEMENT_GRADED_PRODUCT__
#define __GA_ELEMENT_GRADED_PRODUCT__

namespace ga {

	//TODO Try it!

	namespace detail {

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightBasisBlade>
		struct _swaps_count {
			constexpr static size_t value = _basis_blade_grade<cbasis_blade<LeftBasisBlade & RightBasisBlade> >::value + _swaps_count<(LeftBasisBlade >> 1), RightBasisBlade>::value;
		};

		template<default_bitset_t RightBasisBlade>
		struct _swaps_count<0, RightBasisBlade> {
			constexpr static size_t value = 0;
		};

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightBasisBlade>
		struct _reordering_sign {
			constexpr static auto value = cvalue<((_swaps_count<(LeftBasisBlade >> 1), RightBasisBlade>::value & 1) != 0) ? -1 : 1>();
		};

		default_integral_t reordering_sign(default_bitset_t lhs, default_bitset_t const &rhs) {
			lhs >>= 1;
			int changes = 0;
			while (lhs != default_bitset_t(0)) {
				changes += static_cast<int>(ones(lhs & rhs));
				lhs >>= 1;
			}
			return static_cast<default_integral_t>((changes & 1) == 0 ? 1 : -1);
		};

		struct _graded_product_element_make_zero {
			template<class LeftElementType, class RightElementType, class MetricType>
			constexpr static decltype(auto) bind(LeftElementType const &, RightElementType const &, metric<orthogonal_metric<MetricType> > const &) {
				return make_component(cvalue<0>(), cbasis_blade<0>());
			}
		};

		template<default_bitset_t ResultPossibleGrades>
		struct _graded_product_component_maybe_eval {
			template<class LeftComponentType, class RightComponentType, class MetricType>
			constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric<orthogonal_metric<MetricType> > const &mtr) {
				return make_component(mul(mul(reordering_sign(lhs.basis_blade().value(), rhs.basis_blade().value()), mtr.metric_factor(lhs.basis_blade().value() & rhs.basis_blade().value())), mul(lhs.coefficient(), rhs.coefficient())), dbasis_blade<ResultPossibleGrades>(lhs.basis_blade().value() ^ rhs.basis_blade().value()));
			}
		};

		template<class LeftBasisBladeType, class RightBasisBladeType>
		struct _graded_product_component;

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightBasisBlade>
		struct _graded_product_component<cbasis_blade<LeftBasisBlade>, cbasis_blade<RightBasisBlade> > {
		private:

			struct _eval {
				template<class LeftComponentType, class RightComponentType, class MetricType>
				constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric<orthogonal_metric<MetricType> > const &) {
					return make_component(mul(mul(_reordering_sign<LeftBasisBlade, RightBasisBlade>::value, MetricType::cmetric_factor<LeftBasisBlade & RightBasisBlade>::value), mul(lhs.coefficient(), rhs.coefficient())), cbasis_blade<LeftBasisBlade ^ RightBasisBlade>());
				}
			};

		public:

			template<class LeftComponentType, class RightComponentType, class MetricType, class KeepIfGradesFunc>
			constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric<orthogonal_metric<MetricType> > const &mtr, KeepIfGradesFunc const &) {
				return std::conditional<KeepIfGradesFunc::template eval<LeftBasisBlade, RightBasisBlade, LeftBasisBlade ^ RightBasisBlade>::value, _eval, _graded_product_element_make_zero>::type::bind(lhs, rhs, mtr);
			}
		};

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightPossibleGrades>
		struct _graded_product_component<cbasis_blade<LeftBasisBlade>, dbasis_blade<RightPossibleGrades> > {
			template<class LeftComponentType, class RightComponentType, class MetricType, class KeepIfGradesFunc>
			constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric<orthogonal_metric<MetricType> > const &mtr, KeepIfGradesFunc const &) {
				return std::conditional<KeepIfGradesFunc::template maybe_eval<cbasis_blade<LeftBasisBlade>::possible_grades(), RightPossibleGrades>::value, _graded_product_component_maybe_eval<KeepIfGradesFunc::template possible_grades<cbasis_blade<LeftBasisBlade>::possible_grades(), RightPossibleGrades>::value>, _graded_product_element_make_zero>::type::bind(lhs, rhs, mtr);
			}
		};

		template<default_bitset_t LeftPossibleGrades, default_bitset_t RightBasisBlade>
		struct _graded_product_component<dbasis_blade<LeftPossibleGrades>, cbasis_blade<RightBasisBlade> > {
			template<class LeftComponentType, class RightComponentType, class MetricType, class KeepIfGradesFunc>
			constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric<orthogonal_metric<MetricType> > const &mtr, KeepIfGradesFunc const &) {
				return std::conditional<KeepIfGradesFunc::template maybe_eval<LeftPossibleGrades, cbasis_blade<RightBasisBlade>::possible_grades()>::value, _graded_product_component_maybe_eval<KeepIfGradesFunc::template possible_grades<LeftPossibleGrades, cbasis_blade<RightBasisBlade>::possible_grades()>::value>, _graded_product_element_make_zero>::type::bind(lhs, rhs, mtr);
			}
		};

		template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
		struct _graded_product_component<dbasis_blade<LeftPossibleGrades>, dbasis_blade<RightPossibleGrades> > {
			template<class LeftComponentType, class RightComponentType, class MetricType, class KeepIfGradesFunc>
			constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric<orthogonal_metric<MetricType> > const &mtr, KeepIfGradesFunc const &) {
				return std::conditional<KeepIfGradesFunc::template maybe_eval<LeftPossibleGrades, RightPossibleGrades>::value, _graded_product_component_maybe_eval<KeepIfGradesFunc::template possible_grades<LeftPossibleGrades, RightPossibleGrades>::value>, _graded_product_element_make_zero>::type::bind(lhs, rhs, mtr);
			}
		};

		template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, class RightBasisBladeType, class MetricType, class KeepIfGradesFunc>
		constexpr decltype(auto) graded_product_element(component<LeftCoefficientType, LeftBasisBladeType> const &lhs, component<RightCoefficientType, RightBasisBladeType> const &rhs, metric<orthogonal_metric<MetricType> > const &mtr, KeepIfGradesFunc const &keep) {
			return _graded_product_component<LeftBasisBladeType, RightBasisBladeType>::bind(lhs, rhs, mtr, keep);
		}

		//TODO components

	}

}

#endif // __GA_ELEMENT_GRADED_PRODUCT__