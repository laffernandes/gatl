#ifndef __GA_EXPRESSION_ORDERED_ITERATOR_HPP__
#define __GA_EXPRESSION_ORDERED_ITERATOR_HPP__

namespace ga {

	namespace detail {

		constexpr itr_end obegin(empty_expression const &) {
			return itr_end();
		}

		template<class ValueType>
		constexpr decltype(auto) obegin(ValueType const &arg) {
			return itr_value<ValueType>(arg);
		}

		template<class ExpressionType, class TailType>
		class oitr : public itr<ExpressionType, TailType> {
		private:

			typedef itr<ExpressionType, TailType> super;

		public:

			typedef typename super::expression_type expression_type;
			typedef typename super::tail_type tail_type;

			typedef typename super::element_type element_type;

			constexpr oitr(expression_type *value, tail_type const &tail) :
				super(value, tail) {
			};
		};

		template<class ExpressionType, class TailType>
		struct is_end<oitr<ExpressionType, TailType> > {
			static const bool value = false;
		};

		template<class ExpressionType>
		struct _push_up_to_leftmost;

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) obegin(expression<ElementType, LeftSubtreeType, RightSubtreeType> &root) {
			return _push_up_to_leftmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(oitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
		}

		template<class ExpressionType>
		struct _onext;

		template<class ExpressionType, class TailType>
		constexpr decltype(auto) next(oitr<ExpressionType, TailType> const &curr) {
			return _onext<ExpressionType>::bind(curr);
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _onext<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(oitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _push_up_to_leftmost<RightSubtreeType>::bind(oitr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _onext<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(oitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return _push_up_to_leftmost<RightSubtreeType>::bind(oitr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
			}
		};

		template<class ElementType, class LeftSubtreeType>
		struct _onext<expression<ElementType, LeftSubtreeType, empty_expression> > {
			template<class TailType>
			constexpr static decltype(auto) bind(oitr<expression<ElementType, LeftSubtreeType, empty_expression>, TailType> const &curr) {
				return curr.tail();
			}
		};

		template<class ElementType>
		struct _onext<expression<ElementType, empty_expression, empty_expression> > {
			template<class TailType>
			constexpr static decltype(auto) bind(oitr<expression<ElementType, empty_expression, empty_expression>, TailType> const &curr) {
				return curr.tail();
			}
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _push_up_to_leftmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(oitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _push_up_to_leftmost<LeftSubtreeType>::bind(oitr<LeftSubtreeType, oitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> >(&curr.expression()->left(), curr));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _push_up_to_leftmost<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static oitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> bind(oitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return curr;
			}
		};






		template<class ExpressionType, class TailType>
		class coitr : public citr<ExpressionType, TailType> {
		private:

			typedef citr<ExpressionType, TailType> super;

		public:

			typedef typename super::expression_type expression_type;
			typedef typename super::tail_type tail_type;

			typedef typename super::element_type element_type;

			constexpr coitr(expression_type const *value, tail_type const &tail) :
				super(value, tail) {
			};
		};

		template<class ExpressionType, class TailType>
		struct is_end<coitr<ExpressionType, TailType> > {
			static const bool value = false;
		};

		template<class ExpressionType>
		struct _cpush_up_to_leftmost;

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) obegin(expression<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
			return _cpush_up_to_leftmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(coitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
		}

		template<class ExpressionType>
		struct _conext;

		template<class ExpressionType, class TailType>
		constexpr decltype(auto) next(coitr<ExpressionType, TailType> const &curr) {
			return _conext<ExpressionType>::bind(curr);
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _conext<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(coitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _cpush_up_to_leftmost<RightSubtreeType>::bind(coitr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _conext<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(coitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return _cpush_up_to_leftmost<RightSubtreeType>::bind(coitr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
			}
		};

		template<class ElementType, class LeftSubtreeType>
		struct _conext<expression<ElementType, LeftSubtreeType, empty_expression> > {
			template<class TailType>
			constexpr static decltype(auto) bind(coitr<expression<ElementType, LeftSubtreeType, empty_expression>, TailType> const &curr) {
				return curr.tail();
			}
		};

		template<class ElementType>
		struct _conext<expression<ElementType, empty_expression, empty_expression> > {
			template<class TailType>
			constexpr static decltype(auto) bind(coitr<expression<ElementType, empty_expression, empty_expression>, TailType> const &curr) {
				return curr.tail();
			}
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _cpush_up_to_leftmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(coitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _cpush_up_to_leftmost<LeftSubtreeType>::bind(coitr<LeftSubtreeType, coitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> >(&curr.expression()->left(), curr));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _cpush_up_to_leftmost<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static coitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> bind(coitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return curr;
			}
		};

	}

}

#endif // __GA_EXPRESSION_ORDERED_ITERATOR_HPP__
