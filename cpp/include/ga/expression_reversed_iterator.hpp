#ifndef __GA_EXPRESSION_REVERSED_ITERATOR_HPP__
#define __GA_EXPRESSION_REVERSED_ITERATOR_HPP__

namespace ga {

	namespace detail {

		constexpr itr_end rbegin(empty_expression const &) {
			return itr_end();
		}

		template<class ValueType>
		constexpr decltype(auto) rbegin(ValueType const &arg) {
			return itr_value<ValueType>(arg);
		}

		template<class ExpressionType, class TailType>
		class ritr : public itr<ExpressionType, TailType> {
		private:

			typedef itr<ExpressionType, TailType> super;

		public:

			typedef typename super::expression_type expression_type;
			typedef typename super::tail_type tail_type;

			typedef typename super::element_type element_type;

			constexpr ritr() = default;

			constexpr ritr(expression_type *value, tail_type const &tail) :
				super(value, tail) {
			}
		};

		template<class ExpressionType>
		struct _push_up_to_rightmost;

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) rbegin(expression<ElementType, LeftSubtreeType, RightSubtreeType> &root) {
			return _push_up_to_rightmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(ritr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
		}

		template<class ExpressionType>
		struct _rnext;

		template<class ExpressionType, class TailType>
		constexpr decltype(auto) next(ritr<ExpressionType, TailType> const &curr) {
			return _rnext<ExpressionType>::bind(curr);
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _rnext<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(ritr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _push_up_to_rightmost<LeftSubtreeType>::bind(ritr<LeftSubtreeType, TailType>(&curr.expression()->left(), curr.tail()));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _rnext<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(ritr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return curr.tail();
			}
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _push_up_to_rightmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(ritr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _push_up_to_rightmost<RightSubtreeType>::bind(ritr<RightSubtreeType, ritr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> >(&curr.expression()->right(), curr));
			}
		};

		template<class ElementType, class LeftSubtreeType>
		struct _push_up_to_rightmost<expression<ElementType, LeftSubtreeType, empty_expression> > {
			template<class TailType>
			constexpr static ritr<expression<ElementType, LeftSubtreeType, empty_expression>, TailType> bind(ritr<expression<ElementType, LeftSubtreeType, empty_expression>, TailType> const &curr) {
				return curr;
			}
		};

		template<class ExpressionType, class TailType>
		class critr : public citr<ExpressionType, TailType> {
		private:

			typedef citr<ExpressionType, TailType> super;

		public:

			typedef typename super::expression_type expression_type;
			typedef typename super::tail_type tail_type;

			typedef typename super::element_type element_type;

			constexpr critr() = default;
			
			constexpr critr(expression_type const *value, tail_type const &tail) :
				super(value, tail) {
			}
		};

		template<class ExpressionType>
		struct _cpush_up_to_rightmost;

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) rbegin(expression<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
			return _cpush_up_to_rightmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(critr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
		}

		template<class ExpressionType>
		struct _crnext;

		template<class ExpressionType, class TailType>
		constexpr decltype(auto) next(critr<ExpressionType, TailType> const &curr) {
			return _crnext<ExpressionType>::bind(curr);
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _crnext<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(critr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _cpush_up_to_rightmost<LeftSubtreeType>::bind(critr<LeftSubtreeType, TailType>(&curr.expression()->left(), curr.tail()));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _crnext<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(critr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return curr.tail();
			}
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _cpush_up_to_rightmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(critr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _cpush_up_to_rightmost<RightSubtreeType>::bind(critr<RightSubtreeType, critr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> >(&curr.expression()->right(), curr));
			}
		};

		template<class ElementType, class LeftSubtreeType>
		struct _cpush_up_to_rightmost<expression<ElementType, LeftSubtreeType, empty_expression> > {
			template<class TailType>
			constexpr static critr<expression<ElementType, LeftSubtreeType, empty_expression>, TailType> bind(critr<expression<ElementType, LeftSubtreeType, empty_expression>, TailType> const &curr) {
				return curr;
			}
		};

		template<class Type>
		struct rbegin_type {
			typedef typename std::remove_const<typename std::remove_reference<decltype(rbegin(Type()))>::type>::type type;
		};

	}

}

#endif // __GA_EXPRESSION_REVERSED_ITERATOR_HPP__
