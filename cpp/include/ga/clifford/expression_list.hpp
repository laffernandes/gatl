#ifndef __GA_CLIFFORD_EXPRESSION_LIST_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class NextListType, bool CompileTimeDefinedElement = ElementType::compile_time_defined(), bool CompileTimeDefinedTail = NextListType::compile_time_defined()>
			class _super_expression_list;

			template<class ElementType, class NextListType>
			class _super_expression_list<ElementType, NextListType, false, false> {
			public:

				typedef ElementType element_type;
				typedef NextListType next_type;

				constexpr element_type & element() {
					return element_;
				}

				constexpr element_type const & element() const {
					return element_;
				}

				constexpr next_type & next() {
					return next_;
				}

				constexpr next_type const & next() const {
					return next_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_list() = default;
				constexpr _super_expression_list(_super_expression_list const&) = default;
				constexpr _super_expression_list(_super_expression_list &&) = default;

				constexpr _super_expression_list(element_type const &element, next_type const &next) :
					element_(element),
					next_(next) {
				}

				constexpr _super_expression_list & operator=(_super_expression_list const &) = default;
				constexpr _super_expression_list & operator=(_super_expression_list &&) = default;

			private:

				element_type element_;
				next_type next_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
				static_assert(!std::is_same<typename element_type::basis_blade_type, dbasis_blade<default_bitset_t(0)> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class NextListType>
			class _super_expression_list<ElementType, NextListType, false, true> {
			public:

				typedef ElementType element_type;
				typedef NextListType next_type;

				constexpr element_type & element() {
					return element_;
				}

				constexpr element_type const & element() const {
					return element_;
				}

				constexpr next_type const & next() const {
					static next_type const next_;
					return next_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_list() = default;
				constexpr _super_expression_list(_super_expression_list const&) = default;
				constexpr _super_expression_list(_super_expression_list &&) = default;

				constexpr _super_expression_list(element_type const &element, next_type const &) :
					element_(element) {
				}

				constexpr _super_expression_list & operator=(_super_expression_list const &) = default;
				constexpr _super_expression_list & operator=(_super_expression_list &&) = default;

			private:

				element_type element_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
				static_assert(!std::is_same<typename element_type::basis_blade_type, dbasis_blade<default_bitset_t(0)> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class NextListType>
			class _super_expression_list<ElementType, NextListType, true, false> {
			public:

				typedef ElementType element_type;
				typedef NextListType next_type;

				constexpr element_type const & element() const {
					static element_type const element_;
					return element_;
				}

				constexpr next_type & next() {
					return next_;
				}

				constexpr next_type const & next() const {
					return next_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_expression_list() = default;
				constexpr _super_expression_list(_super_expression_list const&) = default;
				constexpr _super_expression_list(_super_expression_list &&) = default;

				constexpr _super_expression_list(element_type const &, next_type const &next) :
					next_(next) {
				}

				constexpr _super_expression_list & operator=(_super_expression_list const &) = default;
				constexpr _super_expression_list & operator=(_super_expression_list &&) = default;

			private:

				next_type next_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class NextListType>
			class _super_expression_list<ElementType, NextListType, true, true> {
			public:

				typedef ElementType element_type;
				typedef NextListType next_type;

				constexpr element_type const & element() const {
					static element_type const element_;
					return element_;
				}

				constexpr next_type const & next() const {
					static next_type const next_;
					return next_;
				}

				constexpr static bool compile_time_defined() {
					return true;
				}

			protected:

				constexpr _super_expression_list() = default;
				constexpr _super_expression_list(_super_expression_list const&) = default;
				constexpr _super_expression_list(_super_expression_list &&) = default;

				constexpr _super_expression_list(element_type const &, next_type const &) {
				}

				constexpr _super_expression_list & operator=(_super_expression_list const &) = default;
				constexpr _super_expression_list & operator=(_super_expression_list &&) = default;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class... OtherElementTypes>
			class expression_list<ElementType, OtherElementTypes...> final :
				public clifford_expression<expression_list<ElementType, OtherElementTypes...> >,
				private _super_expression_list<ElementType, expression_list<OtherElementTypes...> > {
			private:

				typedef _super_expression_list<ElementType, expression_list<OtherElementTypes...> > _super;

			public:

				typedef expression_list expression_type;

				using element_type = typename _super::element_type;
				using next_type = typename _super::next_type;

				constexpr expression_list() = default;
				constexpr expression_list(expression_list const &) = default;
				constexpr expression_list(expression_list &&) = default;

				template<class OtherExpressionType>
				constexpr expression_list(clifford_expression<OtherExpressionType> const &other) {
					copy(begin(other()), begin(*this));
				}

				constexpr expression_list(element_type const &element, OtherElementTypes const &... args) :
					_super(element, next_type(args...)) {
				}

				constexpr expression_list(element_type const &element, next_type const &next) :
					_super(element, next) {
				}

				constexpr expression_list & operator=(expression_list const &) = default;
				constexpr expression_list & operator=(expression_list &&) = default;

				template<class OtherExpressionType>
				constexpr expression_list & operator=(clifford_expression<OtherExpressionType> const &other) {
					copy(begin(other()), begin(*this));
					return *this;
				}

				using _super::element;
				using _super::next;
				using _super::compile_time_defined;
			};

			template<>
			class expression_list<> final :
				public clifford_expression<expression_list<> > {
			public:

				typedef expression_list expression_type;

				constexpr static bool compile_time_defined() {
					return true;
				}
			};

			template<class ElementType>
			constexpr decltype(auto) make_simple_clifford_expression(ElementType const &element) {
				return expression_list<ElementType>(element);
			}

			constexpr decltype(auto) make_empty_clifford_expression() {
				return expression_list<>();
			}

		}

	}

	namespace common {

		template<class... ElementTypes>
		struct is_clifford_expression<clifford::detail::expression_list<ElementTypes...> > {
			constexpr static bool value = true;
		};

		template<class ElementType, class... OtherElementTypes>
		struct common_value_type<clifford::detail::expression_list<ElementType, OtherElementTypes...> > : std::common_type<
			typename common_value_type<typename ElementType::coefficient_type>::type,
			typename common_value_type<clifford::detail::expression_list<OtherElementTypes...> >::type
		> {
		};

		template<>
		struct common_value_type<clifford::detail::expression_list<> > {
			typedef default_integral_t type;
		};

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_HPP__
