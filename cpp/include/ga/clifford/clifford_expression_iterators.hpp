#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			class itr_end {
			};

			template<class ExpressionType>
			constexpr decltype(auto) begin(clifford_expression<ExpressionType> &arg) {
				return begin(arg());
			}

			template<class ExpressionType>
			constexpr decltype(auto) begin(clifford_expression<ExpressionType> const &arg) {
				return begin(arg());
			}

			template<class ValueType, typename std::enable_if<!(is_lazy_expression<ValueType>::value || is_clifford_expression<ValueType>::value), int>::type = 0>
			constexpr decltype(auto) begin(ValueType const &arg) {
				return begin(val(arg));
			}

			template<class ExpressionType>
			constexpr decltype(auto) obegin(clifford_expression<ExpressionType> &arg) {
				return obegin(arg());
			}

			template<class ExpressionType>
			constexpr decltype(auto) obegin(clifford_expression<ExpressionType> const &arg) {
				return obegin(arg());
			}

			template<class ValueType, typename std::enable_if<!(is_lazy_expression<ValueType>::value || is_clifford_expression<ValueType>::value), int>::type = 0>
			constexpr decltype(auto) obegin(ValueType const &arg) {
				return begin(arg);
			}

			template<class Type>
			struct begin_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(begin(Type()))>::type>::type type;
			};

			template<class ExpressionType>
			struct begin_type<clifford_expression<ExpressionType> > : begin_type<ExpressionType> {
			};

			template<class Type>
			struct obegin_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(obegin(Type()))>::type>::type type;
			};

			template<class ExpressionType>
			struct obegin_type<clifford_expression<ExpressionType> > : obegin_type<ExpressionType> {
			};

			template<class ItrType>
			struct next_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(next(ItrType()))>::type>::type type;
			};

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_ITERATORS_HPP__
