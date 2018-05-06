#ifndef __GA_CLIFFORD_EXPRESSION_TREE_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType, bool CompileTimeDefinedElement = ElementType::compile_time_defined(), bool CompileTimeDefinedLeftSubtree = LeftSubtreeType::compile_time_defined(), bool CompileTimeDefinedRightSubtree = RightSubtreeType::compile_time_defined()>
			class _super_expression_tree;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType, false, false, false> {
			public:

				typedef ElementType element_type;
				typedef LeftSubtreeType left_type;
				typedef RightSubtreeType right_type;

				constexpr element_type & element() {
					return element_;
				}

				constexpr element_type const & element() const {
					return element_;
				}

				constexpr left_type & left() {
					return left_;
				}

				constexpr left_type const & left() const {
					return left_;
				}

				constexpr right_type & right() {
					return right_;
				}

				constexpr right_type const & right() const {
					return right_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_tree() = default;
				constexpr _super_expression_tree(_super_expression_tree const&) = default;
				constexpr _super_expression_tree(_super_expression_tree &&) = default;

				constexpr _super_expression_tree(element_type const &element, left_type const &left, right_type const &right) :
					element_(element),
					left_(left),
					right_(right) {
				}

				constexpr _super_expression_tree & operator=(_super_expression_tree const &) = default;
				constexpr _super_expression_tree & operator=(_super_expression_tree &&) = default;

			private:

				element_type element_;
				left_type left_;
				right_type right_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
				static_assert(!std::is_same<typename element_type::basis_blade_type, dbasis_blade<default_bitset_t(0)> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType, false, false, true> {
			public:

				typedef ElementType element_type;
				typedef LeftSubtreeType left_type;
				typedef RightSubtreeType right_type;

				constexpr element_type & element() {
					return element_;
				}

				constexpr element_type const & element() const {
					return element_;
				}

				constexpr left_type & left() {
					return left_;
				}

				constexpr left_type const & left() const {
					return left_;
				}

				constexpr right_type right() const {
					return right_type();
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_tree() = default;
				constexpr _super_expression_tree(_super_expression_tree const&) = default;
				constexpr _super_expression_tree(_super_expression_tree &&) = default;

				constexpr _super_expression_tree(element_type const &element, left_type const &left, right_type const &) :
					element_(element),
					left_(left) {
				}

				constexpr _super_expression_tree & operator=(_super_expression_tree const &) = default;
				constexpr _super_expression_tree & operator=(_super_expression_tree &&) = default;

			private:

				element_type element_;
				left_type left_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
				static_assert(!std::is_same<typename element_type::basis_blade_type, dbasis_blade<default_bitset_t(0)> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType, false, true, false> {
			public:

				typedef ElementType element_type;
				typedef LeftSubtreeType left_type;
				typedef RightSubtreeType right_type;

				constexpr element_type & element() {
					return element_;
				}

				constexpr element_type const & element() const {
					return element_;
				}

				constexpr left_type left() const {
					return left_type();
				}

				constexpr right_type & right() {
					return right_;
				}

				constexpr right_type const & right() const {
					return right_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_tree() = default;
				constexpr _super_expression_tree(_super_expression_tree const&) = default;
				constexpr _super_expression_tree(_super_expression_tree &&) = default;

				constexpr _super_expression_tree(element_type const &element, left_type const &, right_type const &right) :
					element_(element),
					right_(right) {
				}

				constexpr _super_expression_tree & operator=(_super_expression_tree const &) = default;
				constexpr _super_expression_tree & operator=(_super_expression_tree &&) = default;

			private:

				element_type element_;
				right_type right_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
				static_assert(!std::is_same<typename element_type::basis_blade_type, dbasis_blade<default_bitset_t(0)> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType, false, true, true> {
			public:

				typedef ElementType element_type;
				typedef LeftSubtreeType left_type;
				typedef RightSubtreeType right_type;

				constexpr element_type & element() {
					return element_;
				}

				constexpr element_type const & element() const {
					return element_;
				}

				constexpr left_type left() const {
					return left_type();
				}

				constexpr right_type right() const {
					return right_type();
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_tree() = default;
				constexpr _super_expression_tree(_super_expression_tree const&) = default;
				constexpr _super_expression_tree(_super_expression_tree &&) = default;

				constexpr _super_expression_tree(element_type const &element, left_type const &, right_type const &) :
					element_(element) {
				}

				constexpr _super_expression_tree & operator=(_super_expression_tree const &) = default;
				constexpr _super_expression_tree & operator=(_super_expression_tree &&) = default;

			private:

				element_type element_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
				static_assert(!std::is_same<typename element_type::basis_blade_type, dbasis_blade<default_bitset_t(0)> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType, true, false, false> {
			public:

				typedef ElementType element_type;
				typedef LeftSubtreeType left_type;
				typedef RightSubtreeType right_type;

				constexpr element_type element() const {
					return element_type();
				}

				constexpr left_type & left() {
					return left_;
				}

				constexpr left_type const & left() const {
					return left_;
				}

				constexpr right_type & right() {
					return right_;
				}

				constexpr right_type const & right() const {
					return right_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_tree() = default;
				constexpr _super_expression_tree(_super_expression_tree const&) = default;
				constexpr _super_expression_tree(_super_expression_tree &&) = default;

				constexpr _super_expression_tree(element_type const &, left_type const &left, right_type const &right) :
					left_(left),
					right_(right) {
				}

				constexpr _super_expression_tree & operator=(_super_expression_tree const &) = default;
				constexpr _super_expression_tree & operator=(_super_expression_tree &&) = default;

			private:

				left_type left_;
				right_type right_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType, true, false, true> {
			public:

				typedef ElementType element_type;
				typedef LeftSubtreeType left_type;
				typedef RightSubtreeType right_type;

				constexpr element_type element() const {
					return element_type();
				}

				constexpr left_type & left() {
					return left_;
				}

				constexpr left_type const & left() const {
					return left_;
				}

				constexpr right_type right() const {
					return right_type();
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_tree() = default;
				constexpr _super_expression_tree(_super_expression_tree const&) = default;
				constexpr _super_expression_tree(_super_expression_tree &&) = default;

				constexpr _super_expression_tree(element_type const &, left_type const &left, right_type const &) :
					left_(left) {
				}

				constexpr _super_expression_tree & operator=(_super_expression_tree const &) = default;
				constexpr _super_expression_tree & operator=(_super_expression_tree &&) = default;

			private:

				left_type left_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType, true, true, false> {
			public:

				typedef ElementType element_type;
				typedef LeftSubtreeType left_type;
				typedef RightSubtreeType right_type;

				constexpr element_type element() const {
					return element_type();
				}

				constexpr left_type left() const {
					return left_type();
				}

				constexpr right_type & right() {
					return right_;
				}

				constexpr right_type const & right() const {
					return right_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_tree() = default;
				constexpr _super_expression_tree(_super_expression_tree const&) = default;
				constexpr _super_expression_tree(_super_expression_tree &&) = default;

				constexpr _super_expression_tree(element_type const &, left_type const &, right_type const &right) :
					right_(right) {
				}

				constexpr _super_expression_tree & operator=(_super_expression_tree const &) = default;
				constexpr _super_expression_tree & operator=(_super_expression_tree &&) = default;

			private:

				right_type right_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType, true, true, true> {
			public:

				typedef ElementType element_type;
				typedef LeftSubtreeType left_type;
				typedef RightSubtreeType right_type;

				constexpr element_type element() const {
					return element_type();
				}

				constexpr left_type left() const {
					return left_type();
				}

				constexpr right_type right() const {
					return right_type();
				}

				constexpr static bool compile_time_defined() {
					return true;
				}

			protected:

				constexpr _super_expression_tree() = default;
				constexpr _super_expression_tree(_super_expression_tree const&) = default;
				constexpr _super_expression_tree(_super_expression_tree &&) = default;

				constexpr _super_expression_tree(element_type const &, left_type const &, right_type const &) {
				}

				constexpr _super_expression_tree & operator=(_super_expression_tree const &) = default;
				constexpr _super_expression_tree & operator=(_super_expression_tree &&) = default;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class expression_tree;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			class expression_tree final :
				public clifford_expression<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >,
				private _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> {
			private:

				typedef _super_expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> _super;

			public:

				typedef expression_tree expression_type;

				using element_type = typename _super::element_type;
				using left_type = typename _super::left_type;
				using right_type = typename _super::right_type;

				constexpr expression_tree() = default;
				constexpr expression_tree(expression_tree const &) = default;
				constexpr expression_tree(expression_tree &&) = default;

				template<class OtherExpressionType>
				constexpr expression_tree(clifford_expression<OtherExpressionType> const &other) {
					copy(obegin(other), obegin(*this));
				}

				constexpr expression_tree(element_type const &element, left_type const &left, right_type const &right) :
					_super(element, left, right) {
				}

				constexpr expression_tree & operator=(expression_tree const &) = default;
				constexpr expression_tree & operator=(expression_tree &&) = default;

				template<class OtherExpressionType>
				constexpr expression_tree & operator=(clifford_expression<OtherExpressionType> const &other) {
					copy(obegin(other), obegin(*this));
					return *this;
				}

				using _super::element;
				using _super::left;
				using _super::right;
				using _super::compile_time_defined;
			};

			class empty_expression_tree final : public clifford_expression<empty_expression_tree> {
			public:

				typedef empty_expression_tree expression_type;

				constexpr static bool compile_time_defined() {
					return true;
				}
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) make_expression_tree(ElementType const &element, LeftSubtreeType const &left, RightSubtreeType const &right) {
				return expression_tree<ElementType, LeftSubtreeType, RightSubtreeType>(element, left, right);
			}

			template<class ElementType>
			constexpr decltype(auto) make_simple_clifford_expression(ElementType const &element) {
				return make_expression_tree(element, empty_expression_tree(), empty_expression_tree());
			}

			constexpr decltype(auto) make_empty_expression_tree() {
				return empty_expression_tree();
			}

		}

	}

	namespace common {

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct is_clifford_expression<clifford::detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
			constexpr static bool value = true;
		};

		template<>
		struct is_clifford_expression<clifford::detail::empty_expression_tree> {
			constexpr static bool value = true;
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct common_value_type<clifford::detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > : std::common_type<
			typename common_value_type<typename ElementType::coefficient_type>::type,
			typename common_value_type<LeftSubtreeType>::type,
			typename common_value_type<RightSubtreeType>::type
		> {
		};

		template<>
		struct common_value_type<clifford::detail::empty_expression_tree> {
			typedef default_integral_t type;
		};

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_HPP__
