#ifndef __GA_CLIFFORD_COMPONENT_HPP__
#define __GA_CLIFFORD_COMPONENT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class CoefficientType, class BasisBladeType, bool CompileTimeDefinedCoefficient = CoefficientType::compile_time_defined(), bool CompileTimeDefinedBasisBlade = BasisBladeType::compile_time_defined()>
			class _super_component;
			
			template<class CoefficientType, class BasisBladeType>
			class _super_component<CoefficientType, BasisBladeType, false, false> {
			public:

				typedef CoefficientType coefficient_type;
				typedef BasisBladeType basis_blade_type;

				constexpr coefficient_type const & coefficient() const {
					return coefficient_;
				}

				constexpr coefficient_type & coefficient() {
					return coefficient_;
				}

				constexpr basis_blade_type const & basis_blade() const {
					return basis_blade_;
				}

				constexpr basis_blade_type & basis_blade() {
					return basis_blade_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_component() :
					basis_blade_(0) {
				}

				constexpr _super_component(_super_component const &) = default;
				constexpr _super_component(_super_component &&) = default;

				constexpr _super_component(coefficient_type const &coefficient, basis_blade_type const &basis_blade) :
					coefficient_(coefficient),
					basis_blade_(basis_blade) {
				}

				constexpr _super_component & operator=(_super_component const &) = default;
				constexpr _super_component & operator=(_super_component &&) = default;

			private:

				coefficient_type coefficient_;
				basis_blade_type basis_blade_;

				static_assert(is_lazy_expression<coefficient_type>::value, "The CoefficientType of the ga::clifford::detail::component<CoefficientType, BasisBladeType> should be a ga::lazy::lazy_expression<ExpressionType> type.");
			};

			template<class CoefficientType, class BasisBladeType>
			class _super_component<CoefficientType, BasisBladeType, false, true> {
			public:

				typedef CoefficientType coefficient_type;
				typedef BasisBladeType basis_blade_type;

				constexpr coefficient_type const & coefficient() const {
					return coefficient_;
				}

				constexpr coefficient_type & coefficient() {
					return coefficient_;
				}

				constexpr basis_blade_type basis_blade() const {
					return basis_blade_type();
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_component() = default;
				constexpr _super_component(_super_component const &) = default;
				constexpr _super_component(_super_component &&) = default;

				constexpr _super_component(coefficient_type const &coefficient, basis_blade_type const &) :
					coefficient_(coefficient) {
				}

				constexpr _super_component & operator=(_super_component const &) = default;
				constexpr _super_component & operator=(_super_component &&) = default;

			private:

				coefficient_type coefficient_;

				static_assert(is_lazy_expression<coefficient_type>::value, "The CoefficientType of the ga::clifford::detail::component<CoefficientType, BasisBladeType> should be a ga::lazy::lazy_expression<ExpressionType> type.");
			};

			template<class CoefficientType, class BasisBladeType>
			class _super_component<CoefficientType, BasisBladeType, true, false> {
			public:

				typedef CoefficientType coefficient_type;
				typedef BasisBladeType basis_blade_type;

				constexpr coefficient_type coefficient() const {
					return coefficient_type();
				}

				constexpr basis_blade_type const & basis_blade() const {
					return basis_blade_;
				}

				constexpr basis_blade_type & basis_blade() {
					return basis_blade_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr _super_component() :
					basis_blade_(0) {
				}

				constexpr _super_component(_super_component const &) = default;
				constexpr _super_component(_super_component &&) = default;

				constexpr _super_component(coefficient_type const &, basis_blade_type const &basis_blade) :
					basis_blade_(basis_blade) {
				}

				constexpr _super_component& operator=(_super_component const &) = default;
				constexpr _super_component& operator=(_super_component &&) = default;

			private:

				basis_blade_type basis_blade_;
			};

			template<class CoefficientType, class BasisBladeType>
			class _super_component<CoefficientType, BasisBladeType, true, true> {
			public:

				typedef CoefficientType coefficient_type;
				typedef BasisBladeType basis_blade_type;

				constexpr coefficient_type coefficient() const {
					return coefficient_type();
				}

				constexpr basis_blade_type basis_blade() const {
					return basis_blade_type();
				}

				constexpr static bool compile_time_defined() {
					return true;
				}

			protected:

				constexpr _super_component() = default;
				constexpr _super_component(_super_component const &) = default;
				constexpr _super_component(_super_component &&) = default;

				constexpr _super_component(coefficient_type const &, basis_blade_type const &) {
				}

				constexpr _super_component & operator=(_super_component const &) = default;
				constexpr _super_component & operator=(_super_component &&) = default;
			};

			template<class CoefficientType, class BasisBladeType>
			class component final : private _super_component<CoefficientType, BasisBladeType> {
			private:

				typedef _super_component<CoefficientType, BasisBladeType> _super;

			public:

				using coefficient_type = typename _super::coefficient_type;
				using basis_blade_type = typename _super::basis_blade_type;

				constexpr component() = default;
				constexpr component(component const &) = default;
				constexpr component(component &&) = default;

				constexpr component(coefficient_type const &coefficient, basis_blade_type const &basis_blade) :
					_super(coefficient, basis_blade) {
				}

				constexpr component & operator=(component const &) = default;
				constexpr component & operator=(component &&) = default;

				using _super::coefficient;
				using _super::basis_blade;
				using _super:: compile_time_defined;
			};

			template<class CoefficientType, class BasisBladeType>
			constexpr component<CoefficientType, BasisBladeType> make_component(CoefficientType const &coefficient, BasisBladeType const &basis_blade) {
				return component<CoefficientType, BasisBladeType>(coefficient, basis_blade);
			}

			template<class BasisBladeType>
			constexpr decltype(auto) make_simple_clifford_expression(component<constant<0>, BasisBladeType> const &) {
				return make_empty_clifford_expression();
			}

			template<class CoefficientType>
			constexpr decltype(auto) make_simple_clifford_expression(component<CoefficientType, dbasis_blade<default_bitset_t(0)> > const &) {
				return make_empty_clifford_expression();
			}

			constexpr decltype(auto) make_simple_clifford_expression(component<constant<0>, dbasis_blade<default_bitset_t(0)> > const &) {
				return make_empty_clifford_expression();
			}

		}

	}

}

#endif // __GA_CLIFFORD_COMPONENT_HPP__
