#ifndef __GA_CLIFFORD_ELEMENT_GRADED_UNARY_MINUS_HPP__
#define __GA_CLIFFORD_ELEMENT_GRADED_UNARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			struct _graded_unary_minus_element_no_change {
				template<class ElementType, class SignChangeIfGradeFunc>
				constexpr static ElementType bind(ElementType const &arg, SignChangeIfGradeFunc const &) {
					return arg;
				}
			};

			template<class BasisBladeType>
			struct _graded_unary_minus_component;
		
			template<default_bitset_t BasisBlade>
			struct _graded_unary_minus_component<cbasis_blade<BasisBlade> > {
			private:

				struct _change {
					template<class CoefficientType, class SignChangeIfGradeFunc>
					constexpr static decltype(auto) bind(component<CoefficientType, cbasis_blade<BasisBlade> > const &arg, SignChangeIfGradeFunc const &) {
						return make_component(-arg.coefficient(), arg.basis_blade());
					}
				};

			public:

				template<class CoefficientType, class SignChangeIfGradeFunc>
				constexpr static decltype(auto) bind(component<CoefficientType, cbasis_blade<BasisBlade> > const &arg, SignChangeIfGradeFunc const &change) {
					return std::conditional<SignChangeIfGradeFunc::template eval<_basis_blade_grade<cbasis_blade<BasisBlade> >::value>::value, _change, _graded_unary_minus_element_no_change>::type::bind(arg, change);
				}
			};

			template<default_bitset_t PossibleGrades>
			struct _graded_unary_minus_component<dbasis_blade<PossibleGrades> > {
			private:

				struct _maybe_change {
					template<class CoefficientType, class SignChangeIfGradeFunc>
					constexpr static decltype(auto) bind(component<CoefficientType, dbasis_blade<PossibleGrades> > const &arg, SignChangeIfGradeFunc const &change) {
						//TODO lazy
						return change(basis_blade_grade(arg.basis_blade())) ? make_component(-arg.coefficient(), arg.basis_blade()) : arg;
					}
				};

			public:
				template<class CoefficientType, class SignChangeIfGradeFunc>
				constexpr static decltype(auto) bind(component<CoefficientType, dbasis_blade<PossibleGrades> > const &arg, SignChangeIfGradeFunc const &change) {
					return std::conditional<SignChangeIfGradeFunc::template maybe_eval<PossibleGrades>::value, _maybe_change, _graded_unary_minus_element_no_change>::type::bind(arg, change);
				}
			};

			template<class CoefficientType, class BasisBladeType, class SignChangeIfGradeFunc>
			constexpr decltype(auto) graded_unary_minus_element(component<CoefficientType, BasisBladeType> const &arg, SignChangeIfGradeFunc const &change) {
				return detail::_graded_unary_minus_component<BasisBladeType>::bind(arg, change);
			}

			struct _graded_unary_minus_components_maybe_change {
				template<class CoefficientType, default_bitset_t PossibleGrades, class SignChangeIfGradeFunc>
				constexpr static decltype(auto) bind(components<CoefficientType, PossibleGrades> const &arg, SignChangeIfGradeFunc const &change) {
					//TODO lazy
					components<CoefficientType, PossibleGrades> result;
					for (auto itr = arg.begin(), end = arg.end(); itr != end; ++itr) {
						if (change(basis_blade_grade(itr->first))) {
							result.insert(itr->first, -itr->second);
						}
					}
					return result;
				}
			};

			template<class CoefficientType, default_bitset_t PossibleGrades, class SignChangeIfGradeFunc>
			constexpr static decltype(auto) graded_unary_minus_element(components<CoefficientType, PossibleGrades> const &arg, SignChangeIfGradeFunc const &change) {
				return std::conditional<SignChangeIfGradeFunc::template maybe_eval<PossibleGrades>::value, _graded_unary_minus_components_maybe_change, _graded_unary_minus_element_no_change>::type::bind(arg, change);
			}

		}

	}

}

#endif // __GA_CLIFFORD_ELEMENT_GRADED_UNARY_MINUS_HPP__
