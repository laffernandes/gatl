#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ElementType, class NextListType, bool CompileTimeDefinedElement = ElementType::compile_time_defined(), bool CompileTimeDefinedTail = NextListType::compile_time_defined()>
			class _super_clifford_expression;

			template<class ElementType, class NextListType>
			class _super_clifford_expression<ElementType, NextListType, false, false> {
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

				constexpr _super_clifford_expression() = default;
				constexpr _super_clifford_expression(_super_clifford_expression const&) = default;
				constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

				constexpr _super_clifford_expression(element_type const &element, next_type const &next) :
					element_(element),
					next_(next) {
				}

				constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
				constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			private:

				element_type element_;
				next_type next_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
				static_assert(!std::is_same<typename element_type::basis_blade_type, dbasis_blade<default_bitset_t(0)> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class NextListType>
			class _super_clifford_expression<ElementType, NextListType, false, true> {
			public:

				typedef ElementType element_type;
				typedef NextListType next_type;

				constexpr element_type & element() {
					return element_;
				}

				constexpr element_type const & element() const {
					return element_;
				}

				constexpr next_type next() const {
					return next_type();
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_clifford_expression() = default;
				constexpr _super_clifford_expression(_super_clifford_expression const&) = default;
				constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

				constexpr _super_clifford_expression(element_type const &element, next_type const &) :
					element_(element) {
				}

				constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
				constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			private:

				element_type element_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
				static_assert(!std::is_same<typename element_type::basis_blade_type, dbasis_blade<default_bitset_t(0)> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class NextListType>
			class _super_clifford_expression<ElementType, NextListType, true, false> {
			public:

				typedef ElementType element_type;
				typedef NextListType next_type;

				constexpr element_type element() const {
					return element_type();
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

				constexpr _super_clifford_expression() = default;
				constexpr _super_clifford_expression(_super_clifford_expression const&) = default;
				constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

				constexpr _super_clifford_expression(element_type const &, next_type const &next) :
					next_(next) {
				}

				constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
				constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			private:

				next_type next_;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
			};

			template<class ElementType, class NextListType>
			class _super_clifford_expression<ElementType, NextListType, true, true> {
			public:

				typedef ElementType element_type;
				typedef NextListType next_type;

				constexpr element_type element() const {
					return element_type();
				}

				constexpr next_type next() const {
					return next_type();
				}

				constexpr static bool compile_time_defined() {
					return true;
				}

			protected:

				constexpr _super_clifford_expression() = default;
				constexpr _super_clifford_expression(_super_clifford_expression const&) = default;
				constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

				constexpr _super_clifford_expression(element_type const &, next_type const &) {
				}

				constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
				constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

				static_assert(!std::is_same<typename element_type::coefficient_type, constant<0> >::value, "Zeros are not alowed here!");
			};

		}

		template<class... ElementTypes>
		class clifford_expression;

		template<class ElementType, class... OtherElementTypes>
		class clifford_expression<ElementType, OtherElementTypes...> final :
			private detail::_super_clifford_expression<ElementType, clifford_expression<OtherElementTypes...> > {
		private:

			typedef detail::_super_clifford_expression<ElementType, clifford_expression<OtherElementTypes...> > _super;

		public:

			typedef clifford_expression expression_type;

			using element_type = typename _super::element_type;
			using next_type = typename _super::next_type;

			constexpr clifford_expression() = default;
			constexpr clifford_expression(clifford_expression const &) = default;
			constexpr clifford_expression(clifford_expression &&) = default;

			template<class... OtherElementTypes>
			constexpr clifford_expression(clifford_expression<OtherElementTypes...> const &other) {
				copy(other, *this);
			}

			constexpr clifford_expression(element_type const &element, OtherElementTypes const &... args) :
				_super(element, next_type(args...)) {
			}

			constexpr clifford_expression(element_type const &element, next_type const &next) :
				_super(element, next) {
			}

			constexpr clifford_expression & operator=(clifford_expression const &) = default;
			constexpr clifford_expression & operator=(clifford_expression &&) = default;

			template<class... OtherElementTypes>
			constexpr clifford_expression & operator=(clifford_expression<OtherElementTypes...> const &other) {
				copy(other, *this);
				return *this;
			}

			using _super::element;
			using _super::next;
			using _super::compile_time_defined;
		};

		template<>
		class clifford_expression<> final {
		public:

			typedef clifford_expression expression_type;

			constexpr static bool compile_time_defined() {
				return true;
			}
		};

		namespace detail {

			template<class ElementType>
			constexpr decltype(auto) make_simple_clifford_expression(ElementType const &element) {
				return clifford_expression<ElementType>(element);
			}

		}

	}

	namespace common {

		template<class... ElementTypes>
		struct is_clifford_expression<clifford::clifford_expression<ElementTypes...> > {
			constexpr static bool value = true;
		};

		template<class ElementType, class... OtherElementTypes>
		struct common_value_type<clifford::clifford_expression<ElementType, OtherElementTypes...> > : std::common_type<
			typename common_value_type<typename ElementType::coefficient_type>::type,
			typename common_value_type<clifford::clifford_expression<OtherElementTypes...> >::type
		> {
		};

		template<>
		struct common_value_type<clifford::clifford_expression<> > {
			typedef default_integral_t type;
		};

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_HPP__
