#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType>
			constexpr decltype(auto) begin(clifford_expression<ExpressionType> &arg) {
				return begin(arg());
			}

			template<class ExpressionType>
			constexpr decltype(auto) begin(clifford_expression<ExpressionType> const &arg) {
				return begin(arg());
			}

			template<class ExpressionType>
			constexpr decltype(auto) begin(lazy_expression<ExpressionType> const &arg) {
				return make_simple_clifford_expression(make_component(arg(), cbasis_blade<0>()));
			}

			template<class ValueType, typename std::enable_if<!(is_lazy_expression<ValueType>::value || is_clifford_expression<ValueType>::value), int>::type = 0>
			constexpr decltype(auto) begin(ValueType const &arg) {
				return begin(val(arg));
			}

			template<class Type>
			struct begin_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(begin(Type()))>::type>::type type;
			};

			template<class ExpressionType>
			struct begin_type<clifford_expression<ExpressionType> > : begin_type<ExpressionType> {
			};

			template<class ExpressionType>
			struct begin_type<lazy_expression<ExpressionType> > : begin_type<ExpressionType> {
			};

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__
