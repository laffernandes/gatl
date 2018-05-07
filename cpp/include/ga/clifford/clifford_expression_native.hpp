#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_NATIVE_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_NATIVE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class Type>
			struct may_cast_to_native {
				constexpr static bool value = false;
			};

			template<class CoefficientType>
			struct may_cast_to_native<clifford_expression<component<CoefficientType, cbasis_blade<0> > > > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<clifford_expression<component<CoefficientType, dbasis_blade<default_bitset_t(1)> > > > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<clifford_expression<components<CoefficientType, default_bitset_t(1)> > > {
				constexpr static bool value = true;
			};

			template<>
			struct may_cast_to_native<clifford_expression<> > {
				constexpr static bool value = true;
			};

		}

		template<class Type>
		constexpr Type native(Type const &arg) {
			return arg;
		}

		template<class ValueType>
		constexpr ValueType native(lazy::value<ValueType> const &arg) {
			return arg.get();
		}

		template<class ExpressionType>
		constexpr decltype(auto) native(lazy_expression<ExpressionType> const &arg) {
			return native(arg());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(clifford_expression<detail::component<CoefficientType, detail::cbasis_blade<0> > > const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(clifford_expression<detail::component<CoefficientType, detail::dbasis_blade<default_bitset_t(1)> > > const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(clifford_expression<detail::components<CoefficientType, default_bitset_t(1)> > const &arg) {
			return native(arg.element().begin()->second);
		}

		constexpr decltype(auto) native(clifford_expression<> const &) {
			return constant<0>();
		}

		template<class... ElementTypes>
		constexpr decltype(auto) native(clifford_expression<ElementTypes...> const &) = delete;

		namespace detail {

			template<class Type, typename std::enable_if<may_cast_to_native<Type>::value, int>::type = 0>
			constexpr decltype(auto) try_cast_to_native(Type const &arg) {
				return native(arg);
			}

			template<class Type, typename std::enable_if<!may_cast_to_native<Type>::value, int>::type = 0>
			constexpr Type try_cast_to_native(Type const &arg) {
				return arg;
			}

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_NATIVE_HPP__
