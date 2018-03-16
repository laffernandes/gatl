#ifndef __GA_EXPRESSION_ITERATOR_HPP__
#define __GA_EXPRESSION_ITERATOR_HPP__

namespace ga {

	namespace detail {

		template<class ItrType>
		struct is_end;

		class itr_end {};

		template<>
		struct is_end<itr_end> {
			static const bool value = true;
		};

		template<class ValueType>
		class itr_value {
		public:

			typedef ValueType value_type;
			typedef expression<component<value_type, cbasis_blade<0> >, empty_expression, empty_expression> expression_type;

			typedef typename expression_type::element_type element_type;

			constexpr itr_value(value_type const &value) :
				expression_(make_component(value, cbasis_blade<0>()), empty_expression(), empty_expression()) {
			};

			constexpr decltype(auto) element() const {
				return expression_.element();
			}

		protected:

			expression_type const expression_;
		};

		template<class ValueType>
		struct is_end<itr_value<ValueType> > {
			static const bool value = false;
		};

		template<class ValueType>
		constexpr itr_value<ValueType> begin(ValueType const &arg) {
			return itr_value<ValueType>(arg);
		}

		constexpr itr_end begin(cvalue<0> const &) {
			return itr_end();
		}

		template<class ValueType>
		constexpr itr_end next(itr_value<ValueType> const &) {
			return itr_end();
		}

		template<class ExpressionType, class TailType>
		class itr {
		public:

			typedef ExpressionType expression_type;
			typedef TailType tail_type;

			typedef typename expression_type::element_type element_type;

			constexpr itr(expression_type const *value, tail_type const &tail) :
				expression_(value),
				tail_(tail) {
			};

			constexpr decltype(auto) element() const {
				return expression_->element();
			}

			constexpr expression_type const * expression() const {
				return expression_;
			}

			constexpr tail_type const & tail() const {
				return tail_;
			}

		protected:

			expression_type const *expression_;
			tail_type const tail_;
		};

		template<class ExpressionType>
		class itr<ExpressionType, itr_end> {
		public:

			typedef ExpressionType expression_type;
			typedef itr_end tail_type;

			typedef typename expression_type::element_type element_type;

			constexpr itr(expression_type const *value, tail_type const &) :
				expression_(value) {
			};

			constexpr expression_type const * expression() const {
				return expression_;
			}

			constexpr tail_type tail() const {
				return itr_end();
			}

			constexpr decltype(auto) element() const {
				return expression_->element();
			}

		protected:

			expression_type const *expression_;
		};

		template<class ExpressionType, class TailType>
		struct is_end<itr<ExpressionType, TailType> > {
			static const bool value = false;
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) begin(expression<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
			return itr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end());
		}

		constexpr itr_end begin(empty_expression const &) {
			return itr_end();
		}

		template<class ExpressionType>
		struct _next;

		template<class ExpressionType, class TailType>
		constexpr decltype(auto) next(itr<ExpressionType, TailType> const &curr) {
			return _next<ExpressionType>::bind(curr);
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _next<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(itr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return itr<LeftSubtreeType, itr<RightSubtreeType, TailType> >(&curr.expression()->left(), itr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _next<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(itr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return itr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail());
			}
		};

		template<class ElementType, class LeftSubtreeType>
		struct _next<expression<ElementType, LeftSubtreeType, empty_expression> > {
			template<class TailType>
			constexpr static decltype(auto) bind(itr<expression<ElementType, LeftSubtreeType, empty_expression>, TailType> const &curr) {
				return itr<LeftSubtreeType, TailType>(&curr.expression()->left(), curr.tail());
			}
		};

		template<class ElementType>
		struct _next<expression<ElementType, empty_expression, empty_expression> > {
			template<class TailType>
			constexpr static decltype(auto) bind(itr<expression<ElementType, empty_expression, empty_expression>, TailType> const &curr) {
				return curr.tail();
			}
		};

	}

}

#endif // __GA_EXPRESSION_ITERATOR_HPP__
