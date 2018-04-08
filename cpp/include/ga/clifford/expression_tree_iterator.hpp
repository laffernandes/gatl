#ifndef __GA_CLIFFORD_EXPRESSION_TREE_ITERATOR_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_ITERATOR_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			class itr_end {
			};

			constexpr itr_end begin(empty_expression_tree const &) {
				return itr_end();
			}

			template<class ValueType>
			class itr_value {
			public:

				typedef ValueType value_type;
				typedef expression_tree<component<value_type, cbasis_blade<0> >, empty_expression_tree, empty_expression_tree> expression_type;

				typedef typename expression_type::element_type element_type;

				constexpr itr_value() = default;

				constexpr itr_value(value_type const &value) :
					expression_(make_component(value, cbasis_blade<0>()), empty_expression_tree(), empty_expression_tree()) {
				}

				constexpr decltype(auto) element() const {
					return expression_.element();
				}

			protected:

				expression_type const expression_;

				static_assert(is_lazy_expression<ValueType>::value, "The ValueType template argument of ga::clifford::detail::itr_value<ValueType> should be a subclass of ga::lazy::lazy_expression<ExpressionType>.");
			};

			template<class ExpressionType, typename std::enable_if<!std::is_same<ExpressionType, constant<0> >::value, int>::type = 0>
			constexpr itr_value<ExpressionType> begin(lazy_expression<ExpressionType> const &arg) {
				return itr_value<ExpressionType>(arg());
			}

			template<class ValueType, typename std::enable_if<!is_lazy_expression<ValueType>::value, int>::type = 0>
			constexpr decltype(auto) begin(ValueType const &arg) {
				return begin(value<ValueType>(arg));
			}

			constexpr itr_end begin(constant<0> const &) {
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
			struct _next<expression_tree<ElementType, empty_expression_tree, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, empty_expression_tree, RightSubtreeType>, TailType> const &curr) {
					return itr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail());
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _next<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree>, TailType> const &curr) {
					return itr<LeftSubtreeType, TailType>(&curr.expression()->left(), curr.tail());
				}
			};

			template<class ElementType>
			struct _next<expression_tree<ElementType, empty_expression_tree, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(itr<expression_tree<ElementType, empty_expression_tree, empty_expression_tree>, TailType> const &curr) {
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
			struct _cnext<expression_tree<ElementType, empty_expression_tree, RightSubtreeType> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, empty_expression_tree, RightSubtreeType>, TailType> const &curr) {
					return citr<RightSubtreeType, TailType>(&curr.expression()->right(), curr.tail());
				}
			};

			template<class ElementType, class LeftSubtreeType>
			struct _cnext<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree>, TailType> const &curr) {
					return citr<LeftSubtreeType, TailType>(&curr.expression()->left(), curr.tail());
				}
			};

			template<class ElementType>
			struct _cnext<expression_tree<ElementType, empty_expression_tree, empty_expression_tree> > {
				template<class TailType>
				constexpr static decltype(auto) bind(citr<expression_tree<ElementType, empty_expression_tree, empty_expression_tree>, TailType> const &curr) {
					return curr.tail();
				}
			};

			template<class Type>
			struct begin_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(begin(Type()))>::type>::type type;
			};

			template<class ItrType>
			struct next_type {
				typedef typename std::remove_const<typename std::remove_reference<decltype(next(ItrType()))>::type>::type type;
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_ITERATOR_HPP__
