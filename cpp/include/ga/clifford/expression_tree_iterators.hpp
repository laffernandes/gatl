#ifndef __GA_CLIFFORD_EXPRESSION_TREE_ITERATORS_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType, class TailType>
			class itr {
			public:

				typedef ExpressionType expression_type;
				typedef TailType tail_type;

				typedef typename expression_type::element_type element_type;

				constexpr itr() :
					expression_(nullptr) {
				}

				constexpr itr(expression_type *value, tail_type const &tail) :
					expression_(value),
					tail_(tail) {
				}

				constexpr decltype(auto) element() const {
					return expression_->element();
				}

				constexpr expression_type * expression() const {
					return expression_;
				}

				constexpr tail_type const & tail() const {
					return tail_;
				}

			protected:

				expression_type *expression_;
				tail_type const tail_;
			};

			template<class ExpressionType>
			class itr<ExpressionType, itr_end> {
			public:

				typedef ExpressionType expression_type;
				typedef itr_end tail_type;

				typedef typename expression_type::element_type element_type;

				constexpr itr() :
					expression_(nullptr) {
				}

				constexpr itr(expression_type *value, tail_type const &) :
					expression_(value) {
				}

				constexpr expression_type * expression() const {
					return expression_;
				}

				constexpr tail_type tail() const {
					return itr_end();
				}

				constexpr decltype(auto) element() const {
					return expression_->element();
				}

			protected:

				expression_type *expression_;
			};

			template<class ExpressionType, class TailType>
			constexpr itr<ExpressionType, TailType> make_itr(ExpressionType *value, TailType const &tail) {
				return itr<ExpressionType, TailType>(value, tail);
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) begin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> &arg) {
				return make_itr(&arg, itr_end());
			}

			constexpr itr_end begin(empty_expression_tree &) {
				return itr_end();
			}

			template<class ExpressionType>
			struct _next;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _next<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &arg) {
					return make_itr(&arg.expression()->left(), make_itr(&arg.expression()->right(), arg.tail()));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _next<expression_tree<ElementType, empty_expression_tree, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, empty_expression_tree, RightSubtreeType>, TailType> const &arg) {
					return make_itr(&arg.expression()->right(), arg.tail());
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _next<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree>, TailType> const &arg) {
					return make_itr(&arg.expression()->left(), arg.tail());
				}
			};

			template<class ElementType>
			struct _next<expression_tree<ElementType, empty_expression_tree, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, empty_expression_tree, empty_expression_tree>, TailType> const &arg) {
					return arg.tail();
				}
			};

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) next(itr<ExpressionType, TailType> const &arg) {
				return _next<ExpressionType>::bind(arg);
			}

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) element(itr<ExpressionType, TailType> const &arg) {
				return arg.element();
			}

			template<class ExpressionType, class TailType>
			class citr {
			public:

				typedef ExpressionType expression_type;
				typedef TailType tail_type;

				typedef typename expression_type::element_type element_type;

				constexpr citr() :
					expression_(nullptr) {
				}

				constexpr citr(expression_type const *value, tail_type const &tail) :
					expression_(value),
					tail_(tail) {
				}

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
			class citr<ExpressionType, itr_end> {
			public:

				typedef ExpressionType expression_type;
				typedef itr_end tail_type;

				typedef typename expression_type::element_type element_type;

				constexpr citr() :
					expression_(nullptr) {
				};

				constexpr citr(expression_type const *value, tail_type const &) :
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
			constexpr citr<ExpressionType, TailType> make_citr(ExpressionType const *value, TailType const &tail) {
				return citr<ExpressionType, TailType>(value, tail);
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) begin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
				return make_citr(&arg, itr_end());
			}

			constexpr itr_end begin(empty_expression_tree const &) {
				return itr_end();
			}

			template<class ExpressionType>
			struct _cnext;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _cnext<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &arg) {
					return make_citr(&arg.expression()->left(), make_citr(&arg.expression()->right(), arg.tail()));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _cnext<expression_tree<ElementType, empty_expression_tree, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, empty_expression_tree, RightSubtreeType>, TailType> const &arg) {
					return make_citr(&arg.expression()->right(), arg.tail());
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _cnext<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree>, TailType> const &arg) {
					return make_citr(&arg.expression()->left(), arg.tail());
				}
			};

			template<class ElementType>
			struct _cnext<expression_tree<ElementType, empty_expression_tree, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, empty_expression_tree, empty_expression_tree>, TailType> const &arg) {
					return arg.tail();
				}
			};

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) next(citr<ExpressionType, TailType> const &arg) {
				return _cnext<ExpressionType>::bind(arg);
			}

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) element(citr<ExpressionType, TailType> const &arg) {
				return arg.element();
			}

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

			template<class ExpressionType, class TailType>
			constexpr oitr<ExpressionType, TailType> make_oitr(ExpressionType *value, TailType const &tail) {
				return oitr<ExpressionType, TailType>(value, tail);
			}

			template<class ExpressionType>
			struct _push_up_to_leftmost;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _push_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(oitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &arg) {
					return _push_up_to_leftmost<LeftSubtreeType>::bind(make_oitr(&arg.expression()->left(), arg));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _push_up_to_leftmost<expression_tree<ElementType, empty_expression_tree, RightSubtreeType> > {
				template<class TailType>
				constexpr static oitr<expression_tree<ElementType, empty_expression_tree, RightSubtreeType>, TailType> bind(oitr<expression_tree<ElementType, empty_expression_tree, RightSubtreeType>, TailType> const &arg) {
					return arg;
				}
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) obegin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> &arg) {
				return _push_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(oitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&arg, itr_end()));
			}

			constexpr itr_end obegin(empty_expression_tree &) {
				return itr_end();
			}

			template<class ExpressionType>
			struct _onext;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _onext<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(oitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &arg) {
					return _push_up_to_leftmost<RightSubtreeType>::bind(oitr<RightSubtreeType, TailType>(&arg.expression()->right(), arg.tail()));
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _onext<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(oitr<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree>, TailType> const &arg) {
					return arg.tail();
				}
			};

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) next(oitr<ExpressionType, TailType> const &arg) {
				return _onext<ExpressionType>::bind(arg);
			}

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) element(oitr<ExpressionType, TailType> const &arg) {
				return arg.element();
			}

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

			template<class ExpressionType, class TailType>
			constexpr coitr<ExpressionType, TailType> make_coitr(ExpressionType const *value, TailType const &tail) {
				return coitr<ExpressionType, TailType>(value, tail);
			}

			template<class ExpressionType>
			struct _cpush_up_to_leftmost;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _cpush_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(coitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &arg) {
					return _cpush_up_to_leftmost<LeftSubtreeType>::bind(make_coitr(&arg.expression()->left(), arg));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _cpush_up_to_leftmost<expression_tree<ElementType, empty_expression_tree, RightSubtreeType> > {
				template<class TailType>
				constexpr static coitr<expression_tree<ElementType, empty_expression_tree, RightSubtreeType>, TailType> bind(coitr<expression_tree<ElementType, empty_expression_tree, RightSubtreeType>, TailType> const &arg) {
					return arg;
				}
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) obegin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
				return _cpush_up_to_leftmost<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >::bind(coitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&arg, itr_end()));
			}

			constexpr itr_end obegin(empty_expression_tree const &) {
				return itr_end();
			}

			template<class ExpressionType>
			struct _conext;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _conext<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(coitr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &arg) {
					return _cpush_up_to_leftmost<RightSubtreeType>::bind(coitr<RightSubtreeType, TailType>(&arg.expression()->right(), arg.tail()));
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _conext<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(coitr<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree>, TailType> const &arg) {
					return arg.tail();
				}
			};

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) next(coitr<ExpressionType, TailType> const &arg) {
				return _conext<ExpressionType>::bind(arg);
			}

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) element(coitr<ExpressionType, TailType> const &arg) {
				return arg.element();
			}

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_ITERATORS_HPP__
