#ifndef __GA_ELEMENT_KEEP_IF_GRADE_HPP__
#define __GA_ELEMENT_KEEP_IF_GRADE_HPP__

namespace ga {

	namespace detail {

		//TODO Try it!

		template<class KType>
		class keep_if_grade_func;
		
		template<>
		class keep_if_grade_func<grade_t> {
		public:

			constexpr keep_if_grade_func(grade_t const k) :
				k_(k) {
			}

			constexpr bool operator()(grade_t const arg_grade) const {
				return arg_grade == k_;
			}

			template<default_bitset_t PossibleGrades>
			struct maybe_eval {
				constexpr static bool value = true;
			};

		private:

			grade_t const k_;
		};

		template<grade_t K>
		class keep_if_grade_func<cvalue<K> > {
		public:

			constexpr bool operator()(grade_t const arg_grade) const {
				return arg_grade == K;
			}

			template<grade_t ArgGrade>
			struct eval {
				constexpr static bool value = ArgGrade == K;
			};

			template<default_bitset_t PossibleGrades>
			struct maybe_eval {
				constexpr static bool value = (PossibleGrades & (default_bitset_t(1) << K)) != default_bitset_t(0);
			};
		};

		struct _keep_if_grade_element_make_zero {
			template<class ElementType, class KeepIfGradeFunc>
			constexpr static decltype(auto) bind(ElementType const &, KeepIfGradeFunc const &) {
				return make_component(cvalue<0>(), cbasis_blade<0>());
			}
		};

		template<class BasisBladeType>
		struct _keep_if_grade_component;

		template<default_bitset_t BasisBlade>
		struct _keep_if_grade_component<cbasis_blade<BasisBlade> > {
		private:

			struct _keep {
				template<class CoefficientType, class BasisBladeType, class KeepIfGradeFunc>
				constexpr static component<CoefficientType, BasisBladeType> bind(component<CoefficientType, BasisBladeType> const &arg, KeepIfGradeFunc const &) {
					return arg;
				}
			};

		public:

			template<class CoefficientType, class KeepIfGradeFunc>
			constexpr static decltype(auto) bind(component<CoefficientType, cbasis_blade<BasisBlade> > const &arg, KeepIfGradeFunc const &keep) {
				return std::conditional<KeepIfGradeFunc::eval<_basis_blade_grade<cbasis_blade<BasisBlade> >::value>::value, _keep, _keep_if_grade_element_make_zero>::type::bind(arg, keep);
			}
		};

		template<default_bitset_t PossibleGrades>
		struct _keep_if_grade_component<dbasis_blade<PossibleGrades> > {
		private:

			struct _maybe_keep {
				template<class CoefficientType, class KeepIfGradeFunc>
				constexpr static decltype(auto) bind(component<CoefficientType, dbasis_blade<PossibleGrades> > const &arg, KeepIfGradeFunc const &keep) {
					//TODO lazy
					if (keep(basis_blade_grade(arg.basis_blade()))) {
						return make_component(arg.coefficient(), arg.basis_blade());
					}
					else {
						return make_component(static_cast<CoefficientType>(0), arg.basis_blade());
					}
				}
			};

		public:

			template<class CoefficientType, class KeepIfGradeFunc>
			constexpr static decltype(auto) bind(component<CoefficientType, dbasis_blade<PossibleGrades> > const &arg, KeepIfGradeFunc const &keep) {
				return std::conditional<KeepIfGradeFunc::maybe_eval<PossibleGrades>::value, _maybe_keep, _keep_if_grade_element_make_zero>::type::bind(arg, keep);
			}
		};

		template<class CoefficientType, class BasisBladeType, class KeepIfGradeFunc>
		constexpr static decltype(auto) keep_if_grade_element(component<CoefficientType, BasisBladeType> const &arg, KeepIfGradeFunc const &keep) {
			return _keep_if_grade_component<BasisBladeType>::bind(arg, keep);
		}

		struct _keep_if_grade_components_maybe_keep {
			template<class CoefficientType, default_bitset_t PossibleGrades, class KeepIfGradeFunc>
			constexpr static decltype(auto) bind(components<CoefficientType, PossibleGrades> const &arg, KeepIfGradeFunc const &keep) {
				//TODO lazy
				components<CoefficientType, PossibleGrades> result;
				for (auto itr = arg.begin(), end = result.end(); itr != end; ++itr) {
					if (keep(basis_blade_grade(itr->first.value()))) {
						return.emplace(itr->first, itr->second);
					}
				}
				return result;
			}
		};
		
		template<class CoefficientType, default_bitset_t PossibleGrades, class KeepIfGradeFunc>
		constexpr static decltype(auto) keep_if_grade_element(components<CoefficientType, PossibleGrades> const &arg, KeepIfGradeFunc const &keep) {
			return std::conditional<KeepIfGradeFunc::maybe_eval<PossibleGrades>::value, _keep_if_grade_components_maybe_keep, _keep_if_grade_components_make_zero>::type::bind(arg, keep);
		}

	}

}

#endif // __GA_ELEMENT_KEEP_IF_GRADE_HPP__
