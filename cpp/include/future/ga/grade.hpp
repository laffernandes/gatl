#ifndef __FUTURE_GA_GRADE_HPP__
#define __FUTURE_GA_GRADE_HPP__

namespace ga {

	// Interpretation of the result produced by the future::ga::grade() function.
	enum grade_interpretation_t { LAZY_GRADE = -3, UNDETERMINED_GRADE = -2, MIXED_GRADE = -1, SINGLE_GRADE = 0 };

	// The result of the future::ga::grade() function.
	template<class Value>
	class grade_result;
	
	template<class Value>
	class grade_result<scalar_clifford_expression<grade_t, Value> > final {
	public:

		typedef scalar_clifford_expression<grade_t, Value> value_type;

		constexpr grade_result(grade_result const &) = default;
		constexpr grade_result(grade_result &&) = default;

		constexpr grade_result(value_type const &) {
		}

		constexpr operator value_type() const {
			return value_type();
		}

		constexpr operator grade_t() const = delete;

		constexpr grade_interpretation_t flag() const {
			return LAZY_GRADE;
		}
	};

	template<>
	class grade_result<scalar_clifford_expression<grade_t, detail::stored_value> > final {
	public:

		typedef scalar_clifford_expression<grade_t, detail::stored_value> value_type;

		constexpr grade_result(grade_result const &) = default;
		constexpr grade_result(grade_result &&) = default;

		constexpr grade_result(value_type const &value) :
			value_(value) {
		}

		constexpr operator value_type() const {
			return value_;
		}

		constexpr operator grade_t() const {
			return value_;
		}

		constexpr grade_interpretation_t flag() const {
			return flag(*this);
		}

	private:

		constexpr grade_interpretation_t flag(grade_t const grade) const {
			return grade >= 0 ? SINGLE_GRADE : (grade_interpretation_t)grade;
		}

		value_type const value_;
	};

	template<grade_t GradeValue>
	class grade_result<scalar_clifford_expression<grade_t, detail::constant_value<GradeValue> > > final {
	public:

		typedef scalar_clifford_expression<grade_t, detail::constant_value<GradeValue> > value_type;

		constexpr grade_result(grade_result const &) = default;
		constexpr grade_result(grade_result &&) = default;

		constexpr grade_result(value_type const &) {
		}

		constexpr operator value_type() const {
			return value_type();
		}

		constexpr operator grade_t() const {
			return static_cast<grade_t>(GradeValue);
		}

		constexpr grade_interpretation_t flag() const {
			return GradeValue >= 0 ? SINGLE_GRADE : (grade_interpretation_t)GradeValue;
		}
	};

	namespace detail {

		template<class Value>
		constexpr decltype(auto) make_grade_result(scalar_clifford_expression<grade_t, Value> const &arg) {
			return grade_result<scalar_clifford_expression<grade_t, Value> >(arg);
		}

		// Grade deduction.
		//TODO Considerar map
		template<class Expression, class ToleranceValue>
		struct deduce_grade_result;

		template<class Expression, class ToleranceValue>
		using deduce_grade_result_t = typename deduce_grade_result<Expression, ToleranceValue>::type;

		template<class Argument, class... NextArguments, class ToleranceValue>
		struct deduce_grade_result<add<Argument, NextArguments...>, ToleranceValue> {
		private:
				
			typedef typename deduce_grade_result_t<Argument, ToleranceValue> argument_grade;
			typedef typename deduce_grade_result_t<add_t<NextArguments...>, ToleranceValue> next_arguments_grade;

		public:
				
			typedef if_else_t<
				equal_t<argument_grade, constant_value<MIXED_GRADE> >,
				constant_value<MIXED_GRADE>,
				if_else_t<
					equal_t<next_arguments_grade, constant_value<MIXED_GRADE> >,
					constant_value<MIXED_GRADE>,
					if_else_t<
						equal_t<argument_grade, constant_value<UNDETERMINED_GRADE> >,
						next_arguments_grade,
						if_else_t<
							equal_t<next_arguments_grade, constant_value<UNDETERMINED_GRADE> >,
							argument_grade,
							if_else_t<
								equal_t<argument_grade, next_arguments_grade>,
								argument_grade,
								constant_value<MIXED_GRADE>
							>
						>
					>
				>
			> type;
		};

		template<class Coefficient, class BasisBlade, class ToleranceValue>
		struct deduce_grade_result<component<Coefficient, BasisBlade>, ToleranceValue> {
			typedef if_else_t<
				less_or_equal_t<absolute_t<Coefficient>, ToleranceValue>,
				constant_value<UNDETERMINED_GRADE>,
				count_one_bits_t<basis_vectors_t<BasisBlade> >
			> type;
		};

	}

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) grade(clifford_expression<CoefficientType, Expression> const &arg, CoefficientType const &tol) {
		auto const lazy = make_lazy_context(arg, scalar(tol));
		return detail::make_grade_result(lazy.eval(scalar_clifford_expression<grade_t, detail::deduce_grade_result_t<decltype(lazy)::argument_expression_t<0>, detail::coefficient_t<decltype(lazy)::argument_expression_t<1> > > >()));
	}

	template<class Type, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) grade(Type const &arg, Type const &tol) {
		return grade(scalar(arg), tol);
	}

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) grade(clifford_expression<CoefficientType, Expression> const &arg) {
		auto const lazy = make_lazy_context(arg, default_tolerance<CoefficientType>());
		return detail::make_grade_result(lazy.eval(scalar_clifford_expression<grade_t, detail::deduce_grade_result_t<decltype(lazy)::argument_expression_t<0>, detail::coefficient_t<decltype(lazy)::argument_expression_t<1> > > >()));
	}

	template<class Type, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) grade(Type const &arg) {
		return grade(scalar(arg));
	}

}

#endif // __FUTURE_GA_GRADE_HPP__
