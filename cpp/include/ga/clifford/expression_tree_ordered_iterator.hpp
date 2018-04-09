#ifndef __GA_CLIFFORD_EXPRESSION_TREE_ORDERED_ITERATOR_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_ORDERED_ITERATOR_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType, class TailType>
			class oitr : public itr<ExpressionType, TailType> {
			private:

				typedef itr<ExpressionType, TailType> super;

			public:

				typedef typename super::expression_type expression_type;
				typedef typename super::tail_type tail_type;

				typedef typename super::element_type element_type;

				constexpr oitr() = default;

				constexpr oitr(expression_type *value, tail_type const &tail) :
					super(value, tail) {
				}
			};

			template<class ExpressionType>
			struct _push_up_to_leftmost;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) obegin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> &root) {
				return _push_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(oitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
			}

			template<class ExpressionType>
			constexpr decltype(auto) obegin(clifford_expression<ExpressionType> &root) {
				return obegin(root());
			}

			template<class ExpressionType>
			struct _onext;

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) next(oitr<ExpressionType, TailType> const &curr) {
				return _onext<ExpressionType>::bind(curr);
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _onext<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(oitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
					return _push_up_to_leftmost<RightSubtreeType>::bind(oitr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _onext<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(oitr<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression>, TailType> const &curr) {
					return curr.tail();
				}
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _push_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(oitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
					return _push_up_to_leftmost<LeftSubtreeType>::bind(oitr<LeftSubtreeType, oitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> >(&curr.expression()->left(), curr));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _push_up_to_leftmost<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType> > {
				template<class TailType>
				constexpr static oitr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> bind(oitr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> const &curr) {
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

				constexpr coitr() = default;

				constexpr coitr(expression_type const *value, tail_type const &tail) :
					super(value, tail) {
				}
			};

			template<class ExpressionType>
			struct _cpush_up_to_leftmost;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) obegin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
				return _cpush_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(coitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
			}

			template<class ExpressionType>
			constexpr decltype(auto) obegin(clifford_expression<ExpressionType> const &root) {
				return obegin(root());
			}

			template<class ExpressionType>
			struct _conext;

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) next(coitr<ExpressionType, TailType> const &curr) {
				return _conext<ExpressionType>::bind(curr);
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _conext<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(coitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
					return _cpush_up_to_leftmost<RightSubtreeType>::bind(coitr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _conext<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(coitr<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression>, TailType> const &curr) {
					return curr.tail();
				}
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _cpush_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(coitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
					return _cpush_up_to_leftmost<LeftSubtreeType>::bind(coitr<LeftSubtreeType, coitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> >(&curr.expression()->left(), curr));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _cpush_up_to_leftmost<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType> > {
				template<class TailType>
				constexpr static coitr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> bind(coitr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> const &curr) {
					return curr;
				}
			};

			template<class Type>
			struct obegin_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(obegin(Type()))>::type>::type type;
			};

			template<class ExpressionType>
			struct obegin_type<lazy_expression<ExpressionType> > : obegin_type<ExpressionType> {
			};

			template<class ExpressionType>
			struct obegin_type<clifford_expression<ExpressionType> > : obegin_type<ExpressionType> {
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_ORDERED_ITERATOR_HPP__
