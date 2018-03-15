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
			typedef expression<component<value_type, cbasis_blade<0> >, empty_expression, empty_expression> current_type;

			typedef typename current_type::element_type element_type;

			constexpr itr_value(value_type const &value) :
				current_(make_component(value, cbasis_blade<0>()), empty_expression(), empty_expression()) {
			};

			constexpr decltype(auto) element() const {
				return current_.element();
			}

		protected:

			current_type const current_;
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

		template<class TopType, class TailType>
		class itr {
		public:

			typedef TopType top_type;
			typedef TailType tail_type;

			typedef typename top_type::element_type element_type;

			constexpr itr(top_type const *top, tail_type const &tail) :
				top_(top),
				tail_(tail) {
			};

			constexpr decltype(auto) element() const {
				return top_->element();
			}

			constexpr top_type const * top() const {
				return top_;
			}

			constexpr tail_type const & tail() const {
				return tail_;
			}

		protected:

			top_type const *top_;
			tail_type const tail_;
		};

		template<class TopType>
		class itr<TopType, itr_end> {
		public:

			typedef TopType top_type;
			typedef itr_end tail_type;

			typedef typename top_type::element_type element_type;

			constexpr itr(top_type const *top, tail_type const &) :
				top_(top) {
			};

			constexpr top_type const * top() const {
				return top_;
			}

			constexpr tail_type tail() const {
				return itr_end();
			}

			constexpr decltype(auto) element() const {
				return top_->element();
			}

		protected:

			top_type const *top_;
		};

		template<class TopType, class TailType>
		struct is_end<itr<TopType, TailType> > {
			static const bool value = false;
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) begin(expression<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
			return itr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end());
		}

		constexpr itr_end begin(empty_expression const &) {
			return itr_end();
		}

		template<class TopType>
		struct _next;

		template<class TopType, class TailType>
		constexpr decltype(auto) next(itr<TopType, TailType> const &curr) {
			return _next<TopType>::bind(curr);
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _next<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(itr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return itr<LeftSubtreeType, itr<RightSubtreeType, TailType> >(&curr.top()->left(), itr<RightSubtreeType, TailType>(&curr.top()->right(), curr.tail()));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _next<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(itr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return itr<RightSubtreeType, TailType>(&curr.top()->right(), curr.tail());
			}
		};

		template<class ElementType, class LeftSubtreeType>
		struct _next<expression<ElementType, LeftSubtreeType, empty_expression> > {
			template<class TailType>
			constexpr static decltype(auto) bind(itr<expression<ElementType, LeftSubtreeType, empty_expression>, TailType> const &curr) {
				return itr<LeftSubtreeType, TailType>(&curr.top()->left(), curr.tail());
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
