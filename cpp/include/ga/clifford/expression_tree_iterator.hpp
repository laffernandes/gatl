#ifndef __GA_CLIFFORD_EXPRESSION_TREE_ITERATOR_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_ITERATOR_HPP__

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

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) begin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> &root) {
				return itr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end());
			}

			template<class ExpressionType>
			constexpr decltype(auto) begin(clifford_expression<ExpressionType> &root) {
				return begin(root());
			}

			template<class ExpressionType>
			struct _next;

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) next(itr<ExpressionType, TailType> const &curr) {
				return _next<ExpressionType>::bind(curr);
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _next<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
					return itr<LeftSubtreeType, itr<RightSubtreeType, TailType> >(&curr.expression()->left(), itr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _next<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> const &curr) {
					return itr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail());
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _next<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression>, TailType> const &curr) {
					return itr<LeftSubtreeType, TailType>(&curr.expression()->left(), curr.tail());
				}
			};

			template<class ElementType>
			struct _next<expression_tree<ElementType, empty_clifford_expression, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, empty_clifford_expression, empty_clifford_expression>, TailType> const &curr) {
					return curr.tail();
				}
			};

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

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) begin(expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &root) {
				return citr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, itr_end>(&root, itr_end());
			}

			template<class ExpressionType>
			constexpr decltype(auto) begin(clifford_expression<ExpressionType> const &root) {
				return begin(root());
			}

			template<class ExpressionType>
			struct _cnext;

			template<class ExpressionType, class TailType>
			constexpr decltype(auto) next(citr<ExpressionType, TailType> const &curr) {
				return _cnext<ExpressionType>::bind(curr);
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _cnext<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>, TailType> const &curr) {
					return citr<LeftSubtreeType, citr<RightSubtreeType, TailType> >(&curr.expression()->left(), citr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail()));
				}
			};

			template<class ElementType, class RightSubtreeType>
			struct _cnext<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, empty_clifford_expression, RightSubtreeType>, TailType> const &curr) {
					return citr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail());
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _cnext<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, LeftSubtreeType, empty_clifford_expression>, TailType> const &curr) {
					return citr<LeftSubtreeType, TailType>(&curr.expression()->left(), curr.tail());
				}
			};

			template<class ElementType>
			struct _cnext<expression_tree<ElementType, empty_clifford_expression, empty_clifford_expression> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, empty_clifford_expression, empty_clifford_expression>, TailType> const &curr) {
					return curr.tail();
				}
			};

			template<class Type>
			struct begin_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(begin(Type()))>::type>::type type;
			};

			template<class ExpressionType>
			struct begin_type<lazy_expression<ExpressionType> > : begin_type<ExpressionType> {
			};

			template<class ExpressionType>
			struct begin_type<clifford_expression<ExpressionType> > : begin_type<ExpressionType> {
			};

			template<class ItrType>
			struct next_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(next(ItrType()))>::type>::type type;
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_ITERATOR_HPP__
