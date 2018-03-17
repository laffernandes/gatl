#ifndef __GA_COMPONENTS_HPP__
#define __GA_COMPONENTS_HPP__

namespace ga {

	namespace detail {

		template<class CoefficientType, default_bitset_t PossibleGrades>
		class components {
		public:

			typedef CoefficientType coefficient_type;
			typedef dbasis_blade<PossibleGrades> basis_blade_type;

			constexpr components() = default;
			constexpr components(components const &) = default;
			constexpr components(components &&) = default;

			constexpr components& operator=(components const &) = default;
			constexpr components& operator=(components &&) = default;

			inline void insert(basis_blade_type const &basis_blade, coefficient_type const &coefficient) {
				entries_.emplace(basis_blade, coefficient);
			}
			
			template<class Iterator>
			inline void erase(Iterator itr) {
				entries_.erase(itr);
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

		private:

			default_map_type<basis_blade_type, coefficient_type> entries_;
		};

	}

}

#endif // __GA_COMPONENTS_HPP__
