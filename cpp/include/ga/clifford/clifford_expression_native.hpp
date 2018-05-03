#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_NATIVE_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_NATIVE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class Type>
			struct may_cast_to_native {
				constexpr static bool value = false;
			};

			template<>
			struct may_cast_to_native<empty_clifford_expression> {
				constexpr static bool value = true;
			};

			template<class ExpressionType>
			struct may_cast_to_native<clifford_expression<ExpressionType> > : may_cast_to_native<ExpressionType> {
			};

		}

		template<class Type, typename std::enable_if<!is_clifford_expression<Type>::value, int>::type = 0>
		constexpr Type native(Type const &arg) {
			return arg;
		}

		template<class ValueType>
		constexpr ValueType native(lazy::value<ValueType> const &arg) {
			return arg.get();
		}

		constexpr decltype(auto) native(detail::empty_clifford_expression const &) {
			return constant<0>();
		}

		template<class ExpressionType>
		constexpr decltype(auto) native(lazy_expression<ExpressionType> const &arg) {
			return native(arg());
		}

		template<class ExpressionType>
		constexpr decltype(auto) native(clifford_expression<ExpressionType> const &arg) {
			return native(arg());
		}

		namespace detail {

			template<class Type, typename std::enable_if<may_cast_to_native<Type>::value, int>::type = 0>
			constexpr decltype(auto) try_to_cast_to_native(Type const &arg) {
				return native(arg);
			}

			template<class Type, typename std::enable_if<!may_cast_to_native<Type>::value, int>::type = 0>
			constexpr Type try_to_cast_to_native(Type const &arg) {
				return arg;
			}

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_NATIVE_HPP__
