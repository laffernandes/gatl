#ifndef __GA_ELEMENT_GRADED_PRODUCT__
#define __GA_ELEMENT_GRADED_PRODUCT__

namespace ga {

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

		template<class LeftBasisBladeType, class RightBasisBladeType>
		struct _graded_product_component; //TODO lazy about runtime-defined basis_blades

		//TODO Usar informação de PossibleGrades para agilizar o processo.

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightBasisBlade>
		struct _graded_product_component<cbasis_blade<LeftBasisBlade>, cbasis_blade<RightBasisBlade> > {
		private:

			struct _multiply_all {
				template<class LeftCoefficientType, class RightCoefficientType, class MetricType>
				constexpr static decltype(auto) bind(LeftCoefficientType const &lhs, RightCoefficientType const &rhs, metric<orthogonal_metric<MetricType> > const &) {
					return make_component(mul(mul(_reordering_sign<LeftBasisBlade, RightBasisBlade>::value, MetricType::cmetric_factor<LeftBasisBlade & RightBasisBlade>::value), mul(lhs, rhs)), cbasis_blade<LeftBasisBlade ^ RightBasisBlade>());
				}
			};

			struct _make_zero {
				template<class LeftCoefficientType, class RightCoefficientType, class MetricType>
				constexpr static decltype(auto) bind(LeftCoefficientType const &, RightCoefficientType const &, metric<orthogonal_metric<MetricType> > const &) {
					return make_component(cvalue<0>(), cbasis_blade<0>());
				}
			};

		public:

			template<class LeftCoefficientType, class RightCoefficientType, class MetricType, class KeepIfGradesFunc>
			constexpr static decltype(auto) bind(component<LeftCoefficientType, cbasis_blade<LeftBasisBlade> > const &lhs, component<RightCoefficientType, cbasis_blade<RightBasisBlade> > const &rhs, metric<orthogonal_metric<MetricType> > const &mtr, KeepIfGradesFunc const &) {
				return std::conditional<KeepIfGradesFunc::eval<LeftBasisBlade, RightBasisBlade, LeftBasisBlade ^ RightBasisBlade>::value, _multiply_all, _make_zero>::type::bind(lhs.coefficient(), rhs.coefficient(), mtr);
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
