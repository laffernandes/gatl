#ifndef __GA_CLIFFORD_ELEMENT_GRADED_PRODUCT_ORTHOGONAL_METRIC__
#define __GA_CLIFFORD_ELEMENT_GRADED_PRODUCT_ORTHOGONAL_METRIC__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType>
			constexpr decltype(auto) make_simple_clifford_expression(ElementType const &);

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
				constexpr static auto value = constant<((_swaps_count<(LeftBasisBlade >> 1), RightBasisBlade>::value & 1) != 0) ? -1 : 1>();
			};

			default_integral_t reordering_sign(default_bitset_t lhs, default_bitset_t const rhs) {
				lhs >>= 1;
				int changes = 0;
				while (lhs != default_bitset_t(0)) {
					changes += static_cast<int>(ones(lhs & rhs));
					lhs >>= 1;
				}
				return static_cast<default_integral_t>((changes & 1) == 0 ? 1 : -1);
			};

			struct _graded_product_element_make_zero {
				template<class LeftElementType, class RightElementType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(LeftElementType const &, RightElementType const &, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &, KeepIfGradesFunc const &) {
					return make_component(constant<0>(), cbasis_blade<0>());
				}
			};

			template<default_bitset_t ResultPossibleGrades>
			struct _graded_product_component_maybe_eval {
				template<class LeftComponentType, class RightComponentType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					//TODO lazy
					typedef typename std::remove_reference<decltype(reordering_sign(lhs.basis_blade().get(), rhs.basis_blade().get()) * mtr.metric_factor(lhs.basis_blade().get() & rhs.basis_blade().get()) * lhs.coefficient() * rhs.coefficient())>::type coefficient_t;
					auto result_basis_blade = dbasis_blade<ResultPossibleGrades>(lhs.basis_blade().get() ^ rhs.basis_blade().get());
					if (keep(basis_blade_grade(lhs.basis_blade()), basis_blade_grade(rhs.basis_blade()), basis_blade_grade(result_basis_blade))) {
						return make_component(reordering_sign(lhs.basis_blade().get(), rhs.basis_blade().get()) * mtr.metric_factor(lhs.basis_blade().get() & rhs.basis_blade().get()) * lhs.coefficient() * rhs.coefficient(), result_basis_blade);
					}
					else {
						return make_component(coefficient_t(), dbasis_blade<ResultPossibleGrades>(default_bitset_t(0)));
					}
				}
			};

			//TODO Fazer o mesmo para pseudoscalar
			template<>
			struct _graded_product_component_maybe_eval<default_bitset_t(1)> {
				template<class LeftComponentType, class RightComponentType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					//TODO lazy
					typedef typename std::remove_reference<decltype(reordering_sign(lhs.basis_blade().get(), rhs.basis_blade().get()) * mtr.metric_factor(lhs.basis_blade().get() & rhs.basis_blade().get()) * lhs.coefficient() * rhs.coefficient())>::type coefficient_t;
					if (keep(basis_blade_grade(lhs.basis_blade()), basis_blade_grade(rhs.basis_blade()), basis_blade_grade(dbasis_blade<default_bitset_t(1)>(lhs.basis_blade().get() ^ rhs.basis_blade().get())))) {
						return make_component(reordering_sign(lhs.basis_blade().get(), rhs.basis_blade().get()) * mtr.metric_factor(lhs.basis_blade().get() & rhs.basis_blade().get()) * lhs.coefficient() * rhs.coefficient(), cbasis_blade<0>());
					}
					else {
						return make_component(coefficient_t(), cbasis_blade<0>());
					}
				}
			};

			template<>
			struct _graded_product_component_maybe_eval<default_bitset_t(0)> : _graded_product_element_make_zero {
			};

			template<default_bitset_t ResultPossibleGrades>
			struct _graded_product_components_maybe_eval {
				template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, class RightBasisBladeType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(components<LeftCoefficientType, LeftPossibleGrades> const &lhs, component<RightCoefficientType, RightBasisBladeType> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					//TODO lazy
					typedef decltype(reordering_sign(default_bitset_t(), default_bitset_t()) * mtr.metric_factor(default_bitset_t()) * LeftCoefficientType() * RightCoefficientType()) coeficient_t;
					grade_t rhs_grade = basis_blade_grade(rhs.basis_blade());
					components<coeficient_t, ResultPossibleGrades> result;
					for (auto lhs_itr = lhs.begin(), lhs_end = lhs.end(); lhs_itr != lhs_end; ++lhs_itr) {
						auto result_basis_blade = dbasis_blade<ResultPossibleGrades>(lhs_itr->first.get() ^ rhs.basis_blade().get());
						if (keep(basis_blade_grade(lhs_itr->first), rhs_grade, basis_blade_grade(result_basis_blade))) {
							auto result_coefficient = reordering_sign(lhs_itr->first.get(), rhs.basis_blade().get()) * mtr.metric_factor(lhs_itr->first.get() & rhs.basis_blade().get()) * lhs_itr->second * rhs.coefficient();
							auto result_itr = result.find(result_basis_blade);
							if (result_itr == result.end()) {
								if (result_coefficient != 0) {
									result.insert(result_basis_blade, result_coefficient);
								}
							}
							else {
								auto new_coefficient = result_itr->second + result_coefficient;
								if (new_coefficient != 0) {
									result_itr->second = new_coefficient;
								}
								else {
									result.erase(result_itr);
								}
							}
						}
					}
					return result;
				}

				template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, default_bitset_t RightPossibleGrades, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(component<LeftCoefficientType, LeftBasisBladeType> const &lhs, components<RightCoefficientType, RightPossibleGrades> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					//TODO lazy
					typedef decltype(reordering_sign(default_bitset_t(), default_bitset_t()) * mtr.metric_factor(default_bitset_t()) * LeftCoefficientType() * RightCoefficientType()) coefficient_t;
					grade_t lhs_grade = basis_blade_grade(lhs.basis_blade());
					components<coefficient_t, ResultPossibleGrades> result;
					for (auto rhs_itr = rhs.begin(), rhs_end = rhs.end(); rhs_itr != rhs_end; ++rhs_itr) {
						auto result_basis_blade = dbasis_blade<ResultPossibleGrades>(lhs.basis_blade().get() ^ rhs_itr->first.get());
						if (keep(lhs_grade, basis_blade_grade(rhs_itr->first), basis_blade_grade(result_basis_blade))) {
							auto result_coefficient = reordering_sign(lhs.basis_blade().get(), rhs_itr->first.get()) * mtr.metric_factor(lhs.basis_blade().get() & rhs_itr->first.get()) * lhs.coefficient() * rhs_itr->second;
							auto result_itr = result.find(result_basis_blade);
							if (result_itr == result.end()) {
								if (result_coefficient != 0) {
									result.insert(result_basis_blade, result_coefficient);
								}
							}
							else {
								auto new_coefficient = result_itr->second + result_coefficient;
								if (new_coefficient != 0) {
									result_itr->second = new_coefficient;
								}
								else {
									result.erase(result_itr);
								}
							}
						}
					}
					return result;
				}

				template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, default_bitset_t RightPossibleGrades, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(components<LeftCoefficientType, LeftPossibleGrades> const &lhs, components<RightCoefficientType, RightPossibleGrades> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					//TODO lazy
					typedef decltype(reordering_sign(default_bitset_t(), default_bitset_t()) * mtr.metric_factor(default_bitset_t()) * LeftCoefficientType() * RightCoefficientType()) coefficient_t;
					components<coefficient_t, ResultPossibleGrades> result;
					for (auto lhs_itr = lhs.begin(), lhs_end = lhs.end(); lhs_itr != lhs_end; ++lhs_itr) {
						grade_t lhs_grade = basis_blade_grade(lhs_itr->first);
						for (auto rhs_itr = rhs.begin(), rhs_end = rhs.end(); rhs_itr != rhs_end; ++rhs_itr) {
							auto result_basis_blade = dbasis_blade<ResultPossibleGrades>(lhs_itr->first.get() ^ rhs_itr->first.get());
							if (keep(lhs_grade, basis_blade_grade(rhs_itr->first), basis_blade_grade(result_basis_blade))) {
								auto result_coefficient = reordering_sign(lhs_itr->first.get(), rhs_itr->first.get()) * mtr.metric_factor(lhs_itr->first.get() & rhs_itr->first.get()) * lhs_itr->second * rhs_itr->second;
								auto result_itr = result.find(result_basis_blade);
								if (result_itr == result.end()) {
									if (result_coefficient != 0) {
										result.insert(result_basis_blade, result_coefficient);
									}
								}
								else {
									auto new_coefficient = result_itr->second + result_coefficient;
									if (new_coefficient != 0) {
										result_itr->second = new_coefficient;
									}
									else {
										result.erase(result_itr);
									}
								}
							}
						}
					}
					return result;
				}
			};

			//TODO Fazer o mesmo para pseudoscalar
			template<>
			struct _graded_product_components_maybe_eval<default_bitset_t(1)> {
				template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, class RightBasisBladeType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(components<LeftCoefficientType, LeftPossibleGrades> const &lhs, component<RightCoefficientType, RightBasisBladeType> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					//TODO lazy
					typedef decltype(reordering_sign(default_bitset_t(), default_bitset_t()) * mtr.metric_factor(default_bitset_t()) * LeftCoefficientType() * RightCoefficientType()) coeficient_t;
					grade_t rhs_grade = basis_blade_grade(rhs.basis_blade());
					coeficient_t result_coefficient = static_cast<coeficient_t>(0);
					for (auto lhs_itr = lhs.begin(), lhs_end = lhs.end(); lhs_itr != lhs_end; ++lhs_itr) {
						if (keep(basis_blade_grade(lhs_itr->first), rhs_grade, basis_blade_grade(dbasis_blade<default_bitset_t(1)>(lhs_itr->first.get() ^ rhs.basis_blade().get())))) {
							result_coefficient = result_coefficient + (reordering_sign(lhs_itr->first.get(), rhs.basis_blade().get()) * mtr.metric_factor(lhs_itr->first.get() & rhs.basis_blade().get()) * lhs_itr->second * rhs.coefficient());
						}
					}
					return make_component(result_coefficient, cbasis_blade<0>());
				}

				template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, default_bitset_t RightPossibleGrades, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(component<LeftCoefficientType, LeftBasisBladeType> const &lhs, components<RightCoefficientType, RightPossibleGrades> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					//TODO lazy
					typedef decltype(reordering_sign(default_bitset_t(), default_bitset_t()) * mtr.metric_factor(default_bitset_t()) * LeftCoefficientType() * RightCoefficientType()) coefficient_t;
					grade_t lhs_grade = basis_blade_grade(lhs.basis_blade());
					coefficient_t result_coefficient = static_cast<coefficient_t>(0);
					for (auto rhs_itr = rhs.begin(), rhs_end = rhs.end(); rhs_itr != rhs_end; ++rhs_itr) {
						if (keep(lhs_grade, basis_blade_grade(rhs_itr->first), basis_blade_grade(dbasis_blade<default_bitset_t(1)>(lhs.basis_blade().get() ^ rhs_itr->first.get())))) {
							result_coefficient = result_coefficient + (reordering_sign(lhs.basis_blade().get(), rhs_itr->first.get()) * mtr.metric_factor(lhs.basis_blade().get() & rhs_itr->first.get()) * lhs.coefficient() * rhs_itr->second);
						}
					}
					return make_component(result_coefficient, cbasis_blade<0>());
				}

				template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, default_bitset_t RightPossibleGrades, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(components<LeftCoefficientType, LeftPossibleGrades> const &lhs, components<RightCoefficientType, RightPossibleGrades> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					//TODO LAZY O de cima e o original.
					/**
					typedef decltype(reordering_sign(default_bitset_t(), default_bitset_t()) * mtr.metric_factor(default_bitset_t()) * LeftCoefficientType() * RightCoefficientType()) coefficient_t;
					coefficient_t result_coefficient = static_cast<coefficient_t>(0);
					for (auto lhs_itr = lhs.begin(), lhs_end = lhs.end(); lhs_itr != lhs_end; ++lhs_itr) {
						grade_t lhs_grade = basis_blade_grade(lhs_itr->first);
						for (auto rhs_itr = rhs.begin(), rhs_end = rhs.end(); rhs_itr != rhs_end; ++rhs_itr) {
							if (keep(lhs_grade, basis_blade_grade(rhs_itr->first), basis_blade_grade(dbasis_blade<default_bitset_t(1)>(lhs_itr->first.get() ^ rhs_itr->first.get())))) {
								result_coefficient = result_coefficient + (reordering_sign(lhs_itr->first.get(), rhs_itr->first.get()) * mtr.metric_factor(lhs_itr->first.get() & rhs_itr->first.get()) * lhs_itr->second * rhs_itr->second);
							}
						}
					}
					return make_component(result_coefficient, cbasis_blade<0>());
					/*/
					typedef decltype(reordering_sign(default_bitset_t(), default_bitset_t()) * mtr.metric_factor(default_bitset_t()) * LeftCoefficientType() * RightCoefficientType()) coefficient_t;
					return make_component(coefficient_t(), cbasis_blade<0>());
					/**/
				}
			};

			template<>
			struct _graded_product_components_maybe_eval<default_bitset_t(0)> : _graded_product_element_make_zero {
			};

			template<class LeftBasisBladeType, class RightBasisBladeType>
			struct _graded_product_component;

			template<default_bitset_t LeftBasisBlade, default_bitset_t RightBasisBlade>
			struct _graded_product_component<cbasis_blade<LeftBasisBlade>, cbasis_blade<RightBasisBlade> > {
			private:

				struct _eval {
					template<class LeftComponentType, class RightComponentType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
					constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &, KeepIfGradesFunc const &) {
						return make_component(_reordering_sign<LeftBasisBlade, RightBasisBlade>::value * OrthogonalMetricSpaceType::cmetric_factor<LeftBasisBlade & RightBasisBlade>::value * lhs.coefficient() * rhs.coefficient(), cbasis_blade<LeftBasisBlade ^ RightBasisBlade>());
					}
				};

			public:

				template<class LeftComponentType, class RightComponentType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					return std::conditional<KeepIfGradesFunc::template eval<LeftBasisBlade, RightBasisBlade, LeftBasisBlade ^ RightBasisBlade>::value, _eval, _graded_product_element_make_zero>::type::bind(lhs, rhs, mtr, keep);
				}
			};

			template<default_bitset_t LeftBasisBlade, default_bitset_t RightPossibleGrades>
			struct _graded_product_component<cbasis_blade<LeftBasisBlade>, dbasis_blade<RightPossibleGrades> > {
				template<class LeftComponentType, class RightComponentType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					return _graded_product_component_maybe_eval<KeepIfGradesFunc::template possible_grades<cbasis_blade<LeftBasisBlade>::possible_grades(), RightPossibleGrades, OrthogonalMetricSpaceType::vector_space_dimension()>::value>::bind(lhs, rhs, mtr, keep);
				}
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightBasisBlade>
			struct _graded_product_component<dbasis_blade<LeftPossibleGrades>, cbasis_blade<RightBasisBlade> > {
				template<class LeftComponentType, class RightComponentType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					return _graded_product_component_maybe_eval<KeepIfGradesFunc::template possible_grades<LeftPossibleGrades, cbasis_blade<RightBasisBlade>::possible_grades(), OrthogonalMetricSpaceType::vector_space_dimension()>::value>::bind(lhs, rhs, mtr, keep);
				}
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct _graded_product_component<dbasis_blade<LeftPossibleGrades>, dbasis_blade<RightPossibleGrades> > {
				template<class LeftComponentType, class RightComponentType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
				constexpr static decltype(auto) bind(LeftComponentType const &lhs, RightComponentType const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
					return _graded_product_component_maybe_eval<KeepIfGradesFunc::template possible_grades<LeftPossibleGrades, RightPossibleGrades, OrthogonalMetricSpaceType::vector_space_dimension()>::value>::bind(lhs, rhs, mtr, keep);
				}
			};

			template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, class RightBasisBladeType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_element(component<LeftCoefficientType, LeftBasisBladeType> const &lhs, component<RightCoefficientType, RightBasisBladeType> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
				return make_simple_clifford_expression(_graded_product_component<LeftBasisBladeType, RightBasisBladeType>::bind(lhs, rhs, mtr, keep));
			}

			template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, class RightBasisBladeType, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_element(components<LeftCoefficientType, LeftPossibleGrades> const &lhs, component<RightCoefficientType, RightBasisBladeType> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
				return make_simple_clifford_expression(_graded_product_components_maybe_eval<KeepIfGradesFunc::template possible_grades<LeftPossibleGrades, RightBasisBladeType::possible_grades(), OrthogonalMetricSpaceType::vector_space_dimension()>::value>::bind(lhs, rhs, mtr, keep));
			}

			template<class LeftCoefficientType, class LeftBasisBladeType, class RightCoefficientType, default_bitset_t RightPossibleGrades, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_element(component<LeftCoefficientType, LeftBasisBladeType> const &lhs, components<RightCoefficientType, RightPossibleGrades> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
				return make_simple_clifford_expression(_graded_product_components_maybe_eval<KeepIfGradesFunc::template possible_grades<LeftBasisBladeType::possible_grades(), RightPossibleGrades, OrthogonalMetricSpaceType::vector_space_dimension()>::value>::bind(lhs, rhs, mtr, keep));
			}

			template<class LeftCoefficientType, default_bitset_t LeftPossibleGrades, class RightCoefficientType, default_bitset_t RightPossibleGrades, class OrthogonalMetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_element(components<LeftCoefficientType, LeftPossibleGrades> const &lhs, components<RightCoefficientType, RightPossibleGrades> const &rhs, metric_space<orthogonal_metric_space<OrthogonalMetricSpaceType> > const &mtr, KeepIfGradesFunc const &keep) {
				return make_simple_clifford_expression(_graded_product_components_maybe_eval<KeepIfGradesFunc::template possible_grades<LeftPossibleGrades, RightPossibleGrades, OrthogonalMetricSpaceType::vector_space_dimension()>::value>::bind(lhs, rhs, mtr, keep));
			}

		}

	}

}

#endif // __GA_CLIFFORD_ELEMENT_GRADED_PRODUCT_ORTHOGONAL_METRIC__
