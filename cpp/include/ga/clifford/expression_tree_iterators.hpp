#ifndef __GA_CLIFFORD_EXPRESSION_TREE_ITERATORS_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) begin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> &root) {
				return make_itr(&root, itr_end());
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _next<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
					return make_itr(&curr.expression()->left(), make_itr(&curr.expression()->right(), curr.tail()));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _next<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> const &curr) {
					return make_itr(&curr.expression()->right(), curr.tail());
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _next<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression>, TailType> const &curr) {
					return make_itr(&curr.expression()->left(), curr.tail());
				}
			};

			template<class ElementType>
			struct _next<expression_tree<ElementType, empty_clifford_expression, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, empty_clifford_expression, empty_clifford_expression>, TailType> const &curr) {
					return curr.tail();
				}
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) begin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
				return make_citr(&root, itr_end());
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _cnext<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
					return make_citr(&curr.expression()->left(), make_citr(&curr.expression()->right(), curr.tail()));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _cnext<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> const &curr) {
					return make_citr(&curr.expression()->right(), curr.tail());
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _cnext<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression>, TailType> const &curr) {
					return make_citr(&curr.expression()->left(), curr.tail());
				}
			};

			template<class ElementType>
			struct _cnext<expression_tree<ElementType, empty_clifford_expression, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, empty_clifford_expression, empty_clifford_expression>, TailType> const &curr) {
					return curr.tail();
				}
			};

			template<class ExpressionType>
			struct _push_up_to_leftmost;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) obegin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> &root) {
				return _push_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(oitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
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
					return _push_up_to_leftmost<LeftSubtreeType>::bind(make_oitr(&curr.expression()->left(), curr));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _push_up_to_leftmost<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType> > {
				template<class TailType>
				constexpr static oitr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> bind(oitr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> const &curr) {
					return curr;
				}
			};

			template<class ExpressionType>
			struct _cpush_up_to_leftmost;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) obegin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
				return _cpush_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(coitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end()));
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
					return _cpush_up_to_leftmost<LeftSubtreeType>::bind(make_coitr(&curr.expression()->left(), curr));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _cpush_up_to_leftmost<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType> > {
				template<class TailType>
				constexpr static coitr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> bind(coitr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> const &curr) {
					return curr;
				}
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_ITERATORS_HPP__
