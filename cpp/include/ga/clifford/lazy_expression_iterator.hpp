#ifndef __GA_CLIFFORD_LAZY_EXPRESSION_ITERATOR_HPP__
#define __GA_CLIFFORD_LAZY_EXPRESSION_ITERATOR_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType>
			class lazy_expression_itr {
			public:

				typedef ExpressionType expression_type;
				typedef component<expression_type, cbasis_blade<0> > element_type;

				constexpr lazy_expression_itr() = default;

				constexpr lazy_expression_itr(expression_type const &arg) :
					element_(make_component(arg, cbasis_blade<0>())) {
				}

				constexpr decltype(auto) element() const {
					return element_;
				}

			protected:

				element_type const element_;

				static_assert(is_lazy_expression<ExpressionType>::value, "The ExpressionType template argument of ga::clifford::detail::lazy_expression_itr<ExpressionType> should be a subclass of ga::lazy::lazy_expression<ExpressionType>.");
			};

			template<class ExpressionType>
			constexpr lazy_expression_itr<ExpressionType> begin(lazy_expression<ExpressionType> const &arg) {
				return lazy_expression_itr<ExpressionType>(arg());
			}

			constexpr itr_end begin(lazy_expression<constant<0> > const &arg) {
				return itr_end();
			}

			constexpr itr_end begin(constant<0> const &) {
				return itr_end();
			}

			template<class ExpressionType>
			constexpr decltype(auto) obegin(lazy_expression<ExpressionType> const &arg) {
				return begin(arg());
			}

			template<class ExpressionType>
			constexpr itr_end next(lazy_expression_itr<ExpressionType> const &) {
				return itr_end();
			}

			template<class ExpressionType>
			struct begin_type<lazy_expression<ExpressionType> > : begin_type<ExpressionType> {
			};

			template<class ExpressionType>
			struct obegin_type<lazy_expression<ExpressionType> > : obegin_type<ExpressionType> {
			};

		}

	}

}

#endif // __GA_CLIFFORD_LAZY_EXPRESSION_ITERATOR_HPP__
