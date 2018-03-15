#ifndef __GA_EXPRESSION_ORDERED_ITERATOR_HPP__
#define __GA_EXPRESSION_ORDERED_ITERATOR_HPP__

namespace ga {

	namespace detail {

		template<class TopType, class TailType>
		class oitr : public itr<TopType, TailType> {
		private:

			typedef itr<TopType, TailType> super;

		public:

			typedef typename super::top_type top_type;
			typedef typename super::tail_type tail_type;

			typedef typename super::element_type element_type;

			constexpr oitr(top_type const *top, tail_type const &tail) :
				super(top, tail) {
			};
		};

		template<class TopType, class TailType>
		struct is_end<oitr<TopType, TailType> > {
			static const bool value = false;
		};

		template<class TopType>
		struct _push_up_to_leftmost;

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) obegin(expression<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
			return _push_up_to_leftmost<expression<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(oitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
		}

		constexpr itr_end obegin(empty_expression const &) {
			return itr_end();
		}

		template<class ValueType>
		constexpr decltype(auto) obegin(ValueType const &arg) {
			return itr_value<ValueType>(arg);
		}

		template<class TopType>
		struct _onext;

		template<class TopType, class TailType>
		constexpr decltype(auto) next(oitr<TopType, TailType> const &curr) {
			return _onext<TopType>::bind(curr);
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct _onext<expression<ElementType, LeftSubtreeType, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(oitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
				return _push_up_to_leftmost<RightSubtreeType>::bind(oitr<RightSubtreeType, TailType>(&curr.top()->right(), curr.tail()));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _onext<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static decltype(auto) bind(oitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return _push_up_to_leftmost<RightSubtreeType>::bind(oitr<RightSubtreeType, TailType>(&curr.top()->right(), curr.tail()));
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
				return _push_up_to_leftmost<LeftSubtreeType>::bind(oitr<LeftSubtreeType, oitr<expression<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> >(&curr.top()->left(), curr));
			}
		};

		template<class ElementType, class RightSubtreeType>
		struct _push_up_to_leftmost<expression<ElementType, empty_expression, RightSubtreeType> > {
			template<class TailType>
			constexpr static oitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> bind(oitr<expression<ElementType, empty_expression, RightSubtreeType>, TailType> const &curr) {
				return curr;
			}
		};

	}

}

#endif // __GA_EXPRESSION_ORDERED_ITERATOR_HPP__
