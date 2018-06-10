#ifndef __FUTURE_GA_EXPRESSION_POWER_HPP__
#define __FUTURE_GA_EXPRESSION_POWER_HPP__

namespace ga {

	namespace detail {

		// Returns the power of the given integral value.
		template<default_integral_t Base, default_integral_t Exponent>
		struct simpler_ipow {
			typedef constant_value<ipow(Base, Exponent)> type;
		};

		template<default_integral_t Base, default_integral_t Exponent>
		using simpler_ipow_t = typename simpler_ipow<Base, Exponent>::type;

		// Returns the square root of the given integral value.
		template<default_integral_t Value, class Enable = void>
		struct simpler_isqrt;
		
		template<default_integral_t Value>
		struct simpler_isqrt<Value, std::enable_if_t<(Value > 0)> > {
		private:

			constexpr static default_integral_t result = isqrt(Value);

		public:

			typedef std::conditional_t<
				(result * result) == Value,
				constant_value<result>,
				power<constant_value<Value>, power<constant_value<2>, constant_value<-1> > >
			> type;
		};

		template<default_integral_t Value>
		using simpler_isqrt_t = typename simpler_isqrt<Value>::type;

		// Specializations of _power_level2<LeftArgument, RightArgument>.
		template<class LeftExpression, class RightExpression>
		struct _power_level2 {
			typedef power<LeftExpression, RightExpression> type; // default (bind)
		};

		template<class RightExpression>
		struct _power_level2<constant_value<0>, RightExpression> {
			typedef std::conditional_t<
				is_constant_expression_v<RightExpression>,
				std::conditional_t<
					may_be_positive_v<RightExpression>,
					constant_value<0>, // 0^{X} = 0, for X > 0 (simplify)
					nullptr_t // the value of pow(0, X) is undefined for X <= 0
				>,
				power<constant_value<0>, RightExpression>
			> type;
		};

		template<class RightExpression>
		struct _power_level2<constant_value<1>, RightExpression> {
			typedef constant_value<1> type; // 1^{X} = 1 (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _power_level2<constant_value<LeftValue>, constant_value<RightValue> > {
			typedef std::conditional_t<
				LeftValue == -1,
				std::conditional_t<
					(RightValue & 1) == 0,
					constant_value<1>, // (-1)^{K} = 1, if K is odd (simplify)
					constant_value<-1> // (-1)^{K} = -1, if K is even (simplify)
				>,
				std::conditional_t<
					(RightValue > 0),
					simpler_ipow_t<LeftValue, iabs(RightValue)>, // X^{Y} = simpler (simplify)
					power<simpler_ipow_t<LeftValue, iabs(RightValue)>, constant_value<-1> > // X^{Y} = simpler (simplify and bind)
				>
			> type;
		};

		template<default_integral_t LeftValue>
		struct _power_level2<constant_value<LeftValue>, power<constant_value<2>, constant_value<-1> > > {
			typedef simpler_isqrt_t<LeftValue> type; // sqrt(X) = Y, if it is possible simplify for given integer X and Y values (simplify)
		};

		// Specializations of _power_level1<LeftArgument, RightArgument>.
		template<class LeftArgument, class RightArgument>
		struct _power_level1 {
			typedef typename _power_level2<LeftArgument, RightArgument>::type type;
		};

		template<class LeftExpression>
		struct _power_level1<LeftExpression, constant_value<0> > {
			typedef constant_value<1> type; // X^{0} = 1 (simplify)
		};

		template<class LeftExpression>
		struct _power_level1<LeftExpression, constant_value<1> > {
			typedef LeftExpression type; // X^{1} = X (simplify)
		};

		// Specializations of _power<LeftArgument, RightArgument> (distributive property over multiplication).
		template<class LeftArgument, class RightArgument>
		struct _power {
			typedef typename _power_level1<LeftArgument, RightArgument>::type type;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct _power<mul<LeftArgument, LeftNextArguments...>, RightExpression> {
			typedef product_t<power_t<LeftArgument, RightExpression>, power_t<mul_t<LeftNextArguments...>, RightExpression>, real_mapping> type; // (A * B)^{C} = A^{C} * B^{C}
		};

		template<class LeftLeftArgument, class LeftRightArgument, class RightExpression>
		struct _power<power<LeftLeftArgument, LeftRightArgument>, RightExpression> {
			typedef power_t<LeftLeftArgument, product_t<LeftRightArgument, RightExpression, real_mapping> > type; // (A^{B})^{C} = A^{B * C} (simplify)
		};
	}

}

#endif // __FUTURE_GA_EXPRESSION_POWER_HPP__
