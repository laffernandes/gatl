#ifndef __GA_CLIFFORD_COMPONENTS_HPP__
#define __GA_CLIFFORD_COMPONENTS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class CoefficientType, default_bitset_t PossibleGrades>
			class components final {
			public:

				typedef CoefficientType coefficient_type;
				typedef dbasis_blade<PossibleGrades> basis_blade_type;

				constexpr components() = default;
				constexpr components(components const &) = default;
				constexpr components(components &&) = default;

				template<class OtherCoefficientType>
				constexpr components(components<OtherCoefficientType, PossibleGrades> const &other) :
					entries_(other.begin(), other.end()) {
				}

				constexpr components& operator=(components const &) = default;
				constexpr components& operator=(components &&) = default;

				inline void insert(basis_blade_type const &basis_blade, coefficient_type const &coefficient) {
					entries_.emplace(basis_blade, coefficient);
				}
			
				template<class Iterator>
				inline void erase(Iterator itr) {
					entries_.erase(itr);
				}

				inline bool empty() const {
					return entries_.empty();
				}

				inline decltype(auto) find(basis_blade_type const &basis_blade) {
					return entries_.find(basis_blade);
				}

				inline decltype(auto) find(basis_blade_type const &basis_blade) const {
					return entries_.find(basis_blade);
				}

				inline decltype(auto) begin() {
					return entries_.begin();
				}

				inline decltype(auto) begin() const {
					return entries_.begin();
				}

				inline decltype(auto) end() {
					return entries_.end();
				}

				inline decltype(auto) end() const {
					return entries_.end();
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			private:

				std::map<basis_blade_type, coefficient_type> entries_;
			};

			template<default_bitset_t PossibleGrades>
			constexpr decltype(auto) make_simple_clifford_expression(components<constant<0>, PossibleGrades> const &) {
				return make_empty_clifford_expression();
			}

			template<class CoefficientType>
			constexpr decltype(auto) make_simple_clifford_expression(components<CoefficientType, default_bitset_t(0) > const &) {
				return make_empty_clifford_expression();
			}

			constexpr decltype(auto) make_simple_clifford_expression(components<constant<0>, default_bitset_t(0) > const &) {
				return make_empty_clifford_expression();
			}

		}

	}

}

#endif // __GA_CLIFFORD_COMPONENTS_HPP__
