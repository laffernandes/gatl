#ifndef __GA_CLIFFORD_EVAL__
#define __GA_CLIFFORD_EVAL__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ItrType, default_bitset_t PossibleGrades, default_bitset_t DynamicPossibleGrades>
			struct _eval_dynamic_possible_grades {
			private:

				constexpr static bool overlap = (!ItrType::element_type::basis_blade_type::compile_time_defined()) && ((PossibleGrades & ItrType::element_type::basis_blade_type::possible_grades()) != default_bitset_t(0));

				constexpr static default_bitset_t aux = _eval_dynamic_possible_grades<
					typename next_type<ItrType>::type,
					overlap ? (PossibleGrades | ItrType::element_type::basis_blade_type::possible_grades()) : PossibleGrades,
					overlap ? (DynamicPossibleGrades | ItrType::element_type::basis_blade_type::possible_grades()) : DynamicPossibleGrades
				>::value;

			public:

				constexpr static default_bitset_t value = (ItrType::element_type::basis_blade_type::possible_grades() & aux) != default_bitset_t(0) ? (ItrType::element_type::basis_blade_type::possible_grades() | aux) : aux;
			};

			template<default_bitset_t PossibleGrades, default_bitset_t DynamicPossibleGrades>
			struct _eval_dynamic_possible_grades<itr_end, PossibleGrades, DynamicPossibleGrades> {
				constexpr static default_bitset_t value = DynamicPossibleGrades;
			};

			template<default_bitset_t DynamicPossibleGrades>
			struct _eval_clifford_expression_element {
				template<class CoefficientType, class BasisBladeType>
				constexpr static decltype(auto) bind(component<CoefficientType, BasisBladeType> const &arg) {
					return make_expression_tree(make_component(lazy::eval(arg.coefficient()), dbasis_blade<DynamicPossibleGrades>(arg.basis_blade().get())), empty_clifford_expression(), empty_clifford_expression());
				}

				template<class CoefficientType>
				constexpr static decltype(auto) bind(component<CoefficientType, dbasis_blade<DynamicPossibleGrades> > const &arg) {
					return make_expression_tree(make_component(lazy::eval(arg.coefficient()), arg.basis_blade()), empty_clifford_expression(), empty_clifford_expression());
				}

				template<class CoefficientType, default_bitset_t PossibleGrades>
				constexpr static decltype(auto) bind(components<CoefficientType, PossibleGrades> const &arg) {
					components<CoefficientType, DynamicPossibleGrades> element;
					for (auto itr = arg.begin(), end = arg.end(); itr != end; ++itr) {
						element.insert(dbasis_blade<DynamicPossibleGrades>(itr->first.get()), itr->second); //TODO lazy
					}
					return make_expression_tree(element, empty_clifford_expression(), empty_clifford_expression());
				}

				template<class CoefficientType>
				constexpr static decltype(auto) bind(components<CoefficientType, DynamicPossibleGrades> const &arg) {
					return make_expression_tree(arg, empty_clifford_expression(), empty_clifford_expression()); //TODO lazy
				}
			};

			template<>
			struct _eval_clifford_expression_element<default_bitset_t(0)> {
				template<class ElementType>
				constexpr static decltype(auto) bind(ElementType const &arg) {
					return make_expression_tree(make_component(lazy::eval(arg.coefficient()), arg.basis_blade()), empty_clifford_expression(), empty_clifford_expression());
				}
			};

			template<class Type, class ItrType>
			constexpr decltype(auto) eval_clifford_expression(ItrType const &arg) {
				return eval_clifford_expression<Type>(next(arg)) + _eval_clifford_expression_element<_eval_dynamic_possible_grades<typename obegin_type<Type>::type, ItrType::element_type::basis_blade_type::possible_grades(), ItrType::element_type::basis_blade_type::compile_time_defined() ? default_bitset_t(0) : ItrType::element_type::basis_blade_type::possible_grades()>::value>::bind(arg.element());
			}

			template<class Type>
			constexpr empty_clifford_expression eval_clifford_expression(itr_end const &) {
				return empty_clifford_expression();
			}

			struct _eval_clifford_expression {
				template<class Type>
				constexpr static decltype(auto) bind(Type const &arg) {
					return eval_clifford_expression<Type>(obegin(arg));
				}
			};

			struct _eval_identity {
				template<class Type>
				constexpr static Type bind(Type const &arg) {
					return arg;
				}
			};

		}

		using lazy::eval;

		template<class ExpressionType>
		constexpr decltype(auto) eval(clifford_expression<ExpressionType> const &arg) {
			return std::conditional<std::is_same<ExpressionType, typename std::remove_const<typename std::remove_reference<decltype(detail::_eval_clifford_expression::bind(arg()))>::type>::type>::value, detail::_eval_identity, detail::_eval_clifford_expression>::type::bind(arg());
		}

	}

}

#endif // __GA_CLIFFORD_EVAL__
