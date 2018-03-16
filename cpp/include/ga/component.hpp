#ifndef __GA_COMPONENT_HPP__
#define __GA_COMPONENT_HPP__

namespace ga {

	namespace detail {

		template<class CoefficientType, class BasisBladeType>
		class component;
			
		template<class CoefficientType, default_bitset_t BasisBlade>
		class component<CoefficientType, cbasis_blade<BasisBlade> > {
		public:

			typedef CoefficientType coefficient_type;
			typedef cbasis_blade<BasisBlade> basis_blade_type;

			constexpr component(component const &) = default;
			constexpr component(component &&) = default;

			constexpr component(coefficient_type const &coefficient, basis_blade_type const &) :
				coefficient_(coefficient) {
			}

			constexpr component& operator=(component const &) = default;
			constexpr component& operator=(component &&) = default;

			constexpr coefficient_type const & coefficient() const {
				return coefficient_;
			}

			constexpr coefficient_type & coefficient() {
				return coefficient_;
			}

			constexpr basis_blade_type basis_blade() const {
				return cbasis_blade<BasisBlade>();
			}

		protected:

			coefficient_type coefficient_;
		};

		template<class CoefficientType, default_bitset_t PossibleGrades>
		class component<CoefficientType, dbasis_blade<PossibleGrades> > {
		public:

			typedef CoefficientType coefficient_type;
			typedef dbasis_blade<PossibleGrades> basis_blade_type;

			constexpr component(component const &) = default;
			constexpr component(component &&) = default;

			constexpr component(coefficient_type const &coefficient, basis_blade_type const &basis_blade) :
				coefficient_(coefficient),
				basis_blade_(basis_blade) {
			}

			constexpr component& operator=(component const &) = default;
			constexpr component& operator=(component &&) = default;

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

		protected:

			coefficient_type coefficient_;
			basis_blade_type basis_blade_;
		};

		template<default_integral_t Coefficient, default_bitset_t BasisBlade>
		class component<cvalue<Coefficient>, cbasis_blade<BasisBlade> > {
		public:

			typedef cvalue<Coefficient> coefficient_type;
			typedef cbasis_blade<BasisBlade> basis_blade_type;

			constexpr component(component const &) = default;
			constexpr component(component &&) = default;

			constexpr component(coefficient_type const &, basis_blade_type const &) {
			}

			constexpr component& operator=(component const &) = default;
			constexpr component& operator=(component &&) = default;

			constexpr coefficient_type coefficient() const {
				return cvalue<Coefficient>();
			}

			constexpr basis_blade_type basis_blade() const {
				return cbasis_blade<BasisBlade>();
			}
		};

		template<default_integral_t Coefficient, default_bitset_t PossibleGrades>
		class component<cvalue<Coefficient>, dbasis_blade<PossibleGrades> > {
		public:

			typedef cvalue<Coefficient> coefficient_type;
			typedef dbasis_blade<PossibleGrades> basis_blade_type;

			constexpr component(component const &) = default;
			constexpr component(component &&) = default;

			constexpr component(coefficient_type const &, basis_blade_type const &basis_blade) :
				basis_blade_(basis_blade) {
			}

			constexpr component& operator=(component const &) = default;
			constexpr component& operator=(component &&) = default;

			constexpr coefficient_type coefficient() const {
				return cvalue<Coefficient>();
			}

			constexpr basis_blade_type const & basis_blade() const {
				return basis_blade_;
			}

			constexpr basis_blade_type & basis_blade() {
				return basis_blade_;
			}

		protected:

			basis_blade_type basis_blade_;
		};

		template<class CoefficientType, class BasisBladeType>
		constexpr component<CoefficientType, BasisBladeType> make_component(CoefficientType const &coefficient, BasisBladeType const &basis_blade) {
			return component<CoefficientType, BasisBladeType>(coefficient, basis_blade);
		}

	}

}

#endif // __GA_COMPONENT_HPP__
