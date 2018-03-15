#ifndef __GA_COMPONENTS_HPP__
#define __GA_COMPONENTS_HPP__

namespace ga {

	namespace detail {

		template<class CoefficientType, default_bitset_t PossibleGrades>
		class components {
		public:

			typedef CoefficientType coefficient_type;
			typedef dbasis_blade<PossibleGrades> basis_blade_type;

			decltype(auto) emplace(basis_blade_type &&basis_blade, coefficient_type &&coefficient) {
				return entries_.emplace(basis_blade, coefficient);
			}
			
			decltype(auto) begin() {
				return entries_.begin();
			}

			decltype(auto) begin() const {
				return entries_.begin();
			}

			decltype(auto) end() {
				return entries_.end();
			}

			decltype(auto) end() const {
				return entries_.end();
			}

		private:

			default_map_type<basis_blade_type, coefficient_type> entries_;
		};

	}

}

#endif // __GA_COMPONENTS_HPP__
