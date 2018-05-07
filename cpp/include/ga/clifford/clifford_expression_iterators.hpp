#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class... ElementTypes>
			constexpr decltype(auto) begin(clifford_expression<ElementTypes...> &arg) {
				return arg;
			}

			template<class... ElementTypes>
			constexpr decltype(auto) begin(clifford_expression<ElementTypes...> const &arg) {
				return arg;
			}

			template<class ExpressionType>
			constexpr decltype(auto) begin(lazy_expression<ExpressionType> const &arg) {
				return make_simple_clifford_expression(make_component(arg(), cbasis_blade<0>()));
			}

			template<class ValueType, typename std::enable_if<!is_lazy_expression<ValueType>::value, int>::type = 0>
			constexpr decltype(auto) begin(ValueType const &arg) {
				return make_simple_clifford_expression(make_component(val(arg), cbasis_blade<0>()));
			}

			template<class Type>
			struct begin_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(begin(Type()))>::type>::type type;
			};

			template<class ExpressionType>
			struct begin_type<lazy_expression<ExpressionType> > : begin_type<ExpressionType> {
			};

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__
