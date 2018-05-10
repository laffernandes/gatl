#ifndef __GA_FUTURE_EXPONENTIATION_HPP__
#define __GA_FUTURE_EXPONENTIATION_HPP__

namespace future {

	namespace detail {

		// Specialization of exponentiation<mul<...>, RightType> (distributive property over multiplication).
		template<class LeftArgument, class... LeftNextArguments, class RightType>
		struct exponentiation<mul<LeftArgument, LeftNextArguments...>, RightType, std::enable_if_t<!is_any_v<RightType, constant<0>, constant<1> > > > {
			typedef product_t<exponentiation_t<LeftArgument, RightType>, exponentiation_t<mul<LeftNextArguments...>, RightType>, real_mapping> type; // (A * B)^{C} = A^{C} * B^{C}
		};

		template<class RightType>
		struct exponentiation<mul<>, RightType, std::enable_if_t<!is_any_v<RightType, constant<0>, constant<1> > > > {
			typedef constant<1> type; // end of recursion
		};

		// Specializations of exponentiation<LeftType, RightType> (simplify or bind operations).
		template<class LeftType, class RightType>
		struct exponentiation<LeftType, RightType> {
			typedef power<LeftType, RightType> type; // default (bind)
		};

		template<class Type, class Enable = void>
		struct constant_sign;

		template<class Type>
		constexpr default_integral_t constant_sign_v = constant_sign<Type>::value;

		template<default_integral_t Value>
		struct constant_sign<constant<Value> > {
			constexpr static default_integral_t value = sign(Value);
		};

		template<class Argument, class... NextArguments>
		struct constant_sign<mul<Argument, NextArguments...>, std::enable_if_t<is_constant_expression_v<mul<Argument, NextArguments...> > > > {
			constexpr static default_integral_t value = constant_sign_v<Argument> * constant_sign_v<mul<NextArguments...> >;
		};

		template<class LeftArgument, class RightArgument>
		struct constant_sign<power<LeftArgument, RightArgument>, std::enable_if_t<is_constant_expression_v<LeftArgument> && is_constant_expression_v<RightArgument> > > {
			constexpr static default_integral_t value = constant_sign_v<LeftArgument>;
		};

		template<class RightType>
		struct exponentiation<constant<0>, RightType, std::enable_if_t<is_constant_expression_v<RightType> > > {
			static_assert(constant_sign_v<RightType> > 0, "The value of pow(0, N) is undefined for N <= 0.");
			typedef constant<0> type; // 0^{X} = 0, for X > 0 (simplify)
		};

		template<class RightType>
		struct exponentiation<constant<1>, RightType> {
			typedef constant<1> type; // 1^{X} = 1 (simplify)
		};

		template<default_integral_t RightValue>
		struct exponentiation<constant<-1>, constant<RightValue>, std::enable_if_t<(RightValue & 1) == 0> > {
			typedef constant<1> type; // (-1)^{K} = 1, if K is odd (simplify)
		};

		template<default_integral_t RightValue>
		struct exponentiation<constant<-1>, constant<RightValue>, std::enable_if_t<(RightValue & 1) == 1> > {
			typedef constant<-1> type; // (-1)^{K} = -1, if K is even (simplify)
		};

		template<class LeftType>
		struct exponentiation<LeftType, constant<0>, std::enable_if_t<!is_any_v<LeftType, constant<0>, constant<1>, constant<-1> > > > {
			typedef constant<1> type; // X^{0} = 1 (simplify)
		};

		template<class LeftType>
		struct exponentiation<LeftType, constant<1>, std::enable_if_t<!is_any_v<LeftType, constant<0>, constant<1>, constant<-1> > > > {
			typedef LeftType type; // X^{1} = X (simplify)
		};

		template<default_integral_t Value>
		struct simpler_isqrt {
		private:

			constexpr static default_integral_t result = isqrt(Value);

			struct return_constant {
				constexpr static decltype(auto) bind() {
					return constant<result>();
				}
			};

			struct return_constant_sqrt {
				constexpr static decltype(auto) bind() {
					return make_power(constant<Value>(), make_power(constant<2>(), constant<-1>()));
				}
			};

		public:

			constexpr static decltype(auto) bind() {
				return std::conditional<(result * result) == Value, return_constant, return_constant_sqrt>::type::bind();
			}
		};

		template<default_integral_t Value>
		using simpler_isqrt_t = typename simpler_isqrt<Value>::type;

		template<default_integral_t LeftValue>
		struct exponentiation<constant<LeftValue>, power<constant<2>, constant<-1> >, std::enable_if_t<(LeftValue > 1)> > {
			typedef simpler_isqrt_t<LeftValue> type; // sqrt(X) = Y, if it is possible simplify for given integer X and Y values (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct exponentiation<constant<LeftValue>, constant<RightValue>, std::enable_if_t<(LeftValue < -1 || 1 < LeftValue) && (RightValue > 0)> > {
			typedef constant<ipow(LeftValue, RightValue)> type; // X^{Y} = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct exponentiation<constant<LeftValue>, constant<RightValue>, std::enable_if_t<(LeftValue < -1 || 1 < LeftValue) && (RightValue < 0)> > {
			typedef power<constant<ipow(LeftValue, -RightValue)>, constant<-1> > type; // X^{Y} = simpler (simplify and bind)
		};

		template<class LeftLeftArgument, class LeftRightArgument, class RightType>
		struct exponentiation<power<LeftLeftArgument, LeftRightArgument>, RightType, std::enable_if_t<!is_any_v<RightType, constant<0>, constant<1> > > > {
			typedef exponentiation_t<LeftLeftArgument, product_t<LeftRightArgument, RightType, real_mapping> > type; // (A^{B})^{C} = A^{B * C} (simplify)
		};

	}

}

#endif // __GA_FUTURE_EXPONENTIATION_HPP__
