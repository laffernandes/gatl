#ifndef __GA_EVAL__
#define __GA_EVAL__

namespace ga {

	namespace detail {

		template<default_bitset_t DynamicGrades, class Expression>
		struct eval_result_pair {
			constexpr eval_result_pair(Expression &&arg) :
				result(arg) {
			}

			static default_bitset_t const dynamic_grades = DynamicGrades;
			Expression const result;
		};

		template<default_bitset_t DynamicGrades, class Expression>
		constexpr decltype(auto) make_eval_result_pair(Expression &&arg) {
			return eval_result_pair<DynamicGrades, Expression>(std::forward<Expression>(arg));
		}

		struct _eval_expression_add_dynamic {
			template<default_bitset_t LeftDynamicGrades, class LeftExpression, class RightCoefficientType, default_bitset_t RightBasisBlade>
			constexpr static decltype(auto) bind(eval_result_pair<LeftDynamicGrades, LeftExpression> const &lhs, component<RightCoefficientType, cbasis_blade<RightBasisBlade> > const &rhs) {
				return make_eval_result_pair<LeftDynamicGrades>(plus(lhs.result, make_expression(make_component(rhs.coefficient(), dbasis_blade<cbasis_blade<RightBasisBlade>::possible_grades()>(RightBasisBlade)), empty_expression(), empty_expression())));
			}

			template<default_bitset_t LeftDynamicGrades, class LeftExpression, class RightCoefficientType, default_bitset_t RightPossibleGrades>
			constexpr static decltype(auto) bind(eval_result_pair<LeftDynamicGrades, LeftExpression> const &lhs, component<RightCoefficientType, dbasis_blade<RightPossibleGrades> > const &rhs) {
				return make_eval_result_pair<LeftDynamicGrades | RightPossibleGrades>(plus(lhs.result, make_expression(rhs, empty_expression(), empty_expression())));
			}

			template<default_bitset_t LeftDynamicGrades, class LeftExpression, class RightCoefficientType, default_bitset_t RightPossibleGrades>
			constexpr static decltype(auto) bind(eval_result_pair<LeftDynamicGrades, LeftExpression> const &lhs, components<RightCoefficientType, RightPossibleGrades> const &rhs) {
				return make_eval_result_pair<LeftDynamicGrades | RightPossibleGrades>(plus(lhs.result, make_expression(rhs, empty_expression(), empty_expression())));
			}
		};

		struct _eval_expression_add_as_is {
			template<default_bitset_t LeftDynamicGrades, class LeftExpression, class RightElementType>
			constexpr static decltype(auto) bind(eval_result_pair<LeftDynamicGrades, LeftExpression> const &lhs, RightElementType const &rhs) {
				return make_eval_result_pair<RightElementType::basis_blade_type::compile_time_defined() ? LeftDynamicGrades : (LeftDynamicGrades | RightElementType::basis_blade_type::possible_grades())>(plus(lhs.result, make_expression(rhs, empty_expression(), empty_expression())));
			}
		};

		template<default_bitset_t LeftDynamicGrades, class LeftExpression, class RightElementType>
		constexpr static decltype(auto) eval_expression_add(eval_result_pair<LeftDynamicGrades, LeftExpression> const &lhs, RightElementType const &rhs) {
			return std::conditional<(LeftDynamicGrades & RightElementType::basis_blade_type::possible_grades()) != default_bitset_t(0), _eval_expression_add_dynamic, _eval_expression_add_as_is>::type::bind(lhs, rhs);
		}

		struct _eval_expression_next;
		struct _eval_expression_end;

		template<class ItrType>
		constexpr static decltype(auto) eval_expression(ItrType const &arg) {
			return std::conditional<!is_end<ItrType>::value, _eval_expression_next, _eval_expression_end>::type::bind(arg);
		}

		struct _eval_expression_next {
			template<class ItrType>
			constexpr static decltype(auto) bind(ItrType const &arg) {
				return eval_expression_add(eval_expression(next(arg)), arg.element());
			}
		};

		struct _eval_expression_end {
			template<class ItrType>
			constexpr static decltype(auto) bind(ItrType const &) {
				return make_eval_result_pair<default_bitset_t(0)>(empty_expression());
			}
		};

	}

	template<class Type>
	constexpr decltype(auto) eval(Type const &arg) {
		return detail::eval_expression(obegin(arg)).result;
	}

}

#endif // __GA_EVAL__
