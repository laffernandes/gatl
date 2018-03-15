#ifndef __GA_EXPRESSION_HPP__
#define __GA_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		class empty_expression {
		public:

			constexpr empty_expression() = default;

			constexpr static bool compile_time_defined() {
				return true;
			}
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		class expression;

		template<class ElementType>
		class _super_expression_element {
		public:

			typedef ElementType element_type;

			constexpr _super_expression_element(element_type const &element) :
				element_(element) {
			}

			constexpr element_type & element() {
				return element_;
			}

			constexpr element_type const & element() const {
				return element_;
			}

			constexpr static bool compile_time_defined() {
				return false;
			}

		private:

			element_type element_;

			static_assert(!std::is_same<typename element_type::coefficient_type, cvalue<0> >::value, "Zeros are not alowed here!");
		};

		template<default_integral_t CoefficientValue, default_bitset_t BasisBlade>
		class _super_expression_element<component<cvalue<CoefficientValue>, cbasis_blade<BasisBlade> > > {
		public:

			typedef component<cvalue<CoefficientValue>, cbasis_blade<BasisBlade> > element_type;

			constexpr _super_expression_element() = default;

			constexpr _super_expression_element(element_type const &) {
			}

			constexpr element_type element() const {
				return make_component(cvalue<CoefficientValue>(), cbasis_blade<BasisBlade>());
			}

			constexpr static bool compile_time_defined() {
				return true;
			}

			static_assert(CoefficientValue != default_integral_t(0), "Zeros are not alowed here!");
		};

		template<class ExpressionType, bool CompileTimeDefined = ExpressionType::compile_time_defined()>
		class _super_expression_left_subtree;
		
		template<class ExpressionType>
		class _super_expression_left_subtree<ExpressionType, true> {
		public:

			typedef ExpressionType left_type;

			constexpr _super_expression_left_subtree() = default;

			constexpr _super_expression_left_subtree(left_type const &) {
			}

			constexpr left_type left() const {
				return left_type();
			}

			constexpr static bool compile_time_defined() {
				return true;
			}
		};

		template<class ExpressionType>
		class _super_expression_left_subtree<ExpressionType, false> {
		public:

			typedef ExpressionType left_type;

			constexpr _super_expression_left_subtree(left_type const &left) :
				left_(left) {
			}

			constexpr left_type & left() {
				return left_;
			}

			constexpr left_type const & left() const {
				return left_;
			}

			constexpr static bool compile_time_defined() {
				return false;
			}

		private:

			left_type left_;
		};

		template<class ExpressionType, bool CompileTimeDefined = ExpressionType::compile_time_defined()>
		class _super_expression_right_subtree;

		template<class ExpressionType>
		class _super_expression_right_subtree<ExpressionType, true> {
		public:

			typedef ExpressionType right_type;

			constexpr _super_expression_right_subtree() = default;

			constexpr _super_expression_right_subtree(right_type const &) {
			}

			constexpr right_type right() const {
				return right_type();
			}

			constexpr static bool compile_time_defined() {
				return true;
			}
		};

		template<class ExpressionType>
		class _super_expression_right_subtree<ExpressionType, false> {
		public:

			typedef ExpressionType right_type;

			constexpr _super_expression_right_subtree(right_type const &right) :
				right_(right) {
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

		private:

			right_type right_;
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		class expression : private
			_super_expression_element<ElementType>,
			_super_expression_left_subtree<LeftSubtreeType>,
			_super_expression_right_subtree<RightSubtreeType> {
		private:

			typedef _super_expression_element<ElementType> _super_for_element;
			typedef _super_expression_left_subtree<LeftSubtreeType> _super_for_left_subtree;
			typedef _super_expression_right_subtree<RightSubtreeType> _super_for_right_subtree;

		public:

			using element_type = typename _super_for_element::element_type;
			using left_type = typename _super_for_left_subtree::left_type;
			using right_type = typename _super_for_right_subtree::right_type;

			template<bool Enable = compile_time_defined(), typename std::enable_if<Enable, int>::type = 0>
			constexpr expression() {
			}

			constexpr expression(element_type const &element, left_type const &left, right_type const &right) :
				_super_for_element(element),
				_super_for_left_subtree(left),
				_super_for_right_subtree(right) {
			}

			using _super_for_element::element;
			using _super_for_left_subtree::left;
			using _super_for_right_subtree::right;

			constexpr static bool compile_time_defined() {
				return _super_for_element::compile_time_defined() && _super_for_left_subtree::compile_time_defined() && _super_for_right_subtree::compile_time_defined();
			}
		};

		template<class ElementType, class RightSubtreeType>
		class expression<ElementType, empty_expression, RightSubtreeType> : private
			_super_expression_element<ElementType>,
			_super_expression_right_subtree<RightSubtreeType> {
		private:

			typedef _super_expression_element<ElementType> _super_for_element;
			typedef _super_expression_right_subtree<RightSubtreeType> _super_for_right_subtree;

		public:

			using element_type = typename _super_for_element::element_type;
			using right_type = typename _super_for_right_subtree::right_type;

			typedef empty_expression left_type;

			template<bool Enable = compile_time_defined(), typename std::enable_if<Enable, int>::type = 0>
			constexpr expression() {
			}

			constexpr expression(element_type const &element, left_type const &, right_type const &right) :
				_super_for_element(element),
				_super_for_right_subtree(right) {
			}

			using _super_for_element::element;
			using _super_for_right_subtree::right;

			constexpr left_type left() const {
				return left_type();
			}

			constexpr static bool compile_time_defined() {
				return _super_for_element::compile_time_defined() && _super_for_right_subtree::compile_time_defined();
			}
		};

		template<class ElementType, class LeftSubtreeType>
		class expression<ElementType, LeftSubtreeType, empty_expression> : private
			_super_expression_element<ElementType>,
			_super_expression_left_subtree<LeftSubtreeType> {
		private:

			typedef _super_expression_element<ElementType> _super_for_element;
			typedef _super_expression_left_subtree<LeftSubtreeType> _super_for_left_subtree;

		public:

			using element_type = typename _super_for_element::element_type;
			using left_type = typename _super_for_left_subtree::left_type;
			
			typedef empty_expression right_type;

			template<bool Enable = compile_time_defined(), typename std::enable_if<Enable, int>::type = 0>
			constexpr expression() {
			}

			constexpr expression(element_type const &element, left_type const &left, right_type const &) :
				_super_for_element(element),
				_super_for_left_subtree(left) {
			}

			using _super_for_element::element;
			using _super_for_left_subtree::left;

			constexpr right_type right() const {
				return right_type();
			}

			constexpr static bool compile_time_defined() {
				return _super_for_element::compile_time_defined() && _super_for_left_subtree::compile_time_defined();
			}
		};

		template<class ElementType>
		class expression<ElementType, empty_expression, empty_expression> : private
			_super_expression_element<ElementType> {
		private:

			typedef _super_expression_element<ElementType> _super_for_element;

		public:

			using element_type = typename _super_for_element::element_type;
			
			typedef empty_expression left_type;
			typedef empty_expression right_type;

			template<bool Enable = compile_time_defined(), typename std::enable_if<Enable, int>::type = 0>
			constexpr expression() {
			}

			constexpr expression(element_type const &element, left_type const &, right_type const &) :
				_super_for_element(element) {
			}

			using _super_for_element::element;

			constexpr left_type left() const {
				return left_type();
			}

			constexpr right_type right() const {
				return right_type();
			}

			constexpr static bool compile_time_defined() {
				return _super_for_element::compile_time_defined();
			}
		};

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) make_expression(ElementType const &element, LeftSubtreeType const &left, RightSubtreeType const &right) {
			return expression<ElementType, LeftSubtreeType, RightSubtreeType>(element, left, right);
		}

	}

}

#endif // __GA_EXPRESSION_HPP__
