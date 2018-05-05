#ifndef __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType>
			class itr {
			public:

				typedef ExpressionType expression_type;
				typedef typename expression_type::element_type element_type;

				constexpr itr() :
					expression_(nullptr) {
				}

				constexpr itr(expression_type *value) :
					expression_(value) {
				}

				constexpr expression_type * expression() const {
					return expression_;
				}

				constexpr decltype(auto) element() const {
					return expression_->element();
				}

			protected:

				expression_type *expression_;
			};

			template<class ExpressionType>
			constexpr itr<ExpressionType> make_itr(ExpressionType *value) {
				return itr<ExpressionType>(value);
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) begin(expression_list<ElementType, OtherElementTypes...> &arg) {
				return make_itr(&arg);
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) next(itr<expression_list<ElementType, OtherElementTypes...> > const &curr) {
				return make_itr(&curr.expression()->next());
			}

			template<class ElementType>
			constexpr decltype(auto) next(itr<expression_list<ElementType> > const &) {
				return itr_end();
			}

			template<class ExpressionType>
			class citr {
			public:

				typedef ExpressionType expression_type;
				typedef typename expression_type::element_type element_type;

				constexpr citr() :
					expression_(nullptr) {
				};

				constexpr citr(expression_type const *value) :
					expression_(value) {
				};

				constexpr expression_type const * expression() const {
					return expression_;
				}

				constexpr decltype(auto) element() const {
					return expression_->element();
				}

			protected:

				expression_type const *expression_;
			};

			template<class ExpressionType>
			constexpr citr<ExpressionType> make_citr(ExpressionType const *value) {
				return citr<ExpressionType>(value);
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) begin(expression_list<ElementType, OtherElementTypes...> const &arg) {
				return make_citr(&arg);
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) next(citr<expression_list<ElementType, OtherElementTypes...> > const &curr) {
				return make_citr(&curr.expression()->next());
			}

			template<class ElementType>
			constexpr decltype(auto) next(citr<expression_list<ElementType> > const &) {
				return itr_end();
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) obegin(expression_list<ElementType, OtherElementTypes...> &arg) {
				return begin(arg);
			}

			template<class ElementType, class... OtherElementTypes>
			constexpr decltype(auto) obegin(expression_list<ElementType, OtherElementTypes...> const &arg) {
				return begin(arg);
			}

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_ITERATORS_HPP__
