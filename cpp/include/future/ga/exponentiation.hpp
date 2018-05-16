#ifndef __FUTURE_GA_EXPONENTIATION_HPP__
#define __FUTURE_GA_EXPONENTIATION_HPP__

namespace ga {

	namespace detail {

		// Specialization of exponentiation<mul<...>, RightExpression> (distributive property over multiplication).
		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct exponentiation<mul<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_any_v<RightExpression, constant_value<0>, constant_value<1> > > > {
			typedef product_t<exponentiation_t<LeftArgument, RightExpression>, exponentiation_t<mul_t<LeftNextArguments...>, RightExpression>, real_mapping> type; // (A * B)^{C} = A^{C} * B^{C}
		};

		// Specializations of exponentiation<LeftExpression, RightExpression> (simplify or bind operations).
		template<class LeftExpression, class RightExpression>
		struct exponentiation<LeftExpression, RightExpression> {
			typedef power_t<LeftExpression, RightExpression> type; // default (bind)
		};

		template<class Expression, class Enable = void>
		struct constant_sign;

		template<class Expression>
		constexpr default_integral_t constant_sign_v = constant_sign<Expression>::value;

		template<default_integral_t Value>
		struct constant_sign<constant_value<Value> > {
			constexpr static default_integral_t value = sign(Value);
		};

		template<class Argument, class... NextArguments>
		struct constant_sign<mul<Argument, NextArguments...>, std::enable_if_t<is_constant_expression_v<mul_t<Argument, NextArguments...> > > > {
			constexpr static default_integral_t value = constant_sign_v<Argument> * constant_sign_v<mul_t<NextArguments...> >;
		};

		template<class LeftArgument, class RightArgument>
		struct constant_sign<power<LeftArgument, RightArgument>, std::enable_if_t<is_constant_expression_v<LeftArgument> && is_constant_expression_v<RightArgument> > > {
			constexpr static default_integral_t value = constant_sign_v<LeftArgument>;
		};

		template<class RightExpression>
		struct exponentiation<constant_value<0>, RightExpression, std::enable_if_t<is_constant_expression_v<RightExpression> > > {
			static_assert(constant_sign_v<RightExpression> > 0, "The value of pow(0, N) is undefined for N <= 0.");
			typedef constant_value<0> type; // 0^{X} = 0, for X > 0 (simplify)
		};

		template<class RightExpression>
		struct exponentiation<constant_value<1>, RightExpression> {
			typedef constant_value<1> type; // 1^{X} = 1 (simplify)
		};

		template<default_integral_t RightValue>
		struct exponentiation<constant_value<-1>, constant_value<RightValue>, std::enable_if_t<(RightValue & 1) == 0> > {
			typedef constant_value<1> type; // (-1)^{K} = 1, if K is odd (simplify)
		};

		template<default_integral_t RightValue>
		struct exponentiation<constant_value<-1>, constant_value<RightValue>, std::enable_if_t<(RightValue & 1) == 1> > {
			typedef constant_value<-1> type; // (-1)^{K} = -1, if K is even (simplify)
		};

		template<class LeftExpression>
		struct exponentiation<LeftExpression, constant_value<0>, std::enable_if_t<!is_any_v<LeftExpression, constant_value<0>, constant_value<1>, constant_value<-1> > > > {
			typedef constant_value<1> type; // X^{0} = 1 (simplify)
		};

		template<class LeftExpression>
		struct exponentiation<LeftExpression, constant_value<1>, std::enable_if_t<!is_any_v<LeftExpression, constant_value<0>, constant_value<1>, constant_value<-1> > > > {
			typedef LeftExpression type; // X^{1} = X (simplify)
		};

		template<default_integral_t Value>
		struct simpler_isqrt {
		private:

			constexpr static default_integral_t result = isqrt(Value);

		public:

			typedef std::conditional_t<
				(result * result) == Value,
				constant_value<result>,
				power_t<constant_value<Value>, power_t<constant_value<2>, constant_value<-1> > >
			> type;
		};

		template<default_integral_t Value>
		using simpler_isqrt_t = typename simpler_isqrt<Value>::type;

		template<default_integral_t LeftValue>
		struct exponentiation<constant_value<LeftValue>, power<constant_value<2>, constant_value<-1> >, std::enable_if_t<(LeftValue > 1)> > {
			typedef simpler_isqrt_t<LeftValue> type; // sqrt(X) = Y, if it is possible simplify for given integer X and Y values (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct exponentiation<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<(LeftValue < -1 || 1 < LeftValue) && (RightValue > 0)> > {
			typedef constant_value<ipow(LeftValue, RightValue)> type; // X^{Y} = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct exponentiation<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<(LeftValue < -1 || 1 < LeftValue) && (RightValue < 0)> > {
			typedef power_t<constant_value<ipow(LeftValue, -RightValue)>, constant_value<-1> > type; // X^{Y} = simpler (simplify and bind)
		};

		template<class LeftLeftArgument, class LeftRightArgument, class RightExpression>
		struct exponentiation<power<LeftLeftArgument, LeftRightArgument>, RightExpression, std::enable_if_t<!is_any_v<RightExpression, constant_value<0>, constant_value<1> > > > {
			typedef exponentiation_t<LeftLeftArgument, product_t<LeftRightArgument, RightExpression, real_mapping> > type; // (A^{B})^{C} = A^{B * C} (simplify)
		};

	}

}

#endif // __FUTURE_GA_EXPONENTIATION_HPP__