#ifndef __GA_CLIFFORD_INSERTION_OPERATOR_HPP__
#define __GA_CLIFFORD_INSERTION_OPERATOR_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			void write_basis_blade(std::ostream &os, default_bitset_t rhs) {
				if (rhs == 0) {
					os << "1";
				}
				else {
					int ind = 0;
					bool first = true;
					while (rhs != 0) {
						if ((rhs & 1) != 0) {
							if (!first) os << "^";
							else first = false;
							os << "e" << (ind + 1);
						}
						rhs >>= 1;
						++ind;
					}
				}
			}

			template<default_bitset_t BasisBlade>
			void write_basis_blade(std::ostream &os, cbasis_blade<BasisBlade> const &) {
				os << "<";
				write_basis_blade(os, BasisBlade);
				os << ">";
			}

			template<default_bitset_t PossibleGrades>
			void write_basis_blade(std::ostream &os, dbasis_blade<PossibleGrades> const &rhs) {
				write_basis_blade(os, rhs.get());
			}

			template<class CoefficientType, class BasisBladeType>
			void write_element(std::ostream &os, component<CoefficientType, BasisBladeType> const &rhs, bool &first) {
				if (first) {
					first = false;
				}
				else {
					os << " + ";
				}
				os << rhs.coefficient() << " * ";
				write_basis_blade(os, rhs.basis_blade());
			}

			template<class CoefficientType, default_bitset_t PossibleGrades>
			void write_element(std::ostream &os, components<CoefficientType, PossibleGrades> const &rhs, bool &first) {
				if (first) {
					first = false;
					os << "[";
				}
				else {
					os << " + [";
				}
				if (rhs.empty()) {
					os << constant<0>();
				}
				else {
					for (auto itr = rhs.begin(), end = rhs.end(); itr != end; ++itr) {
						os << itr->second << " * ";
						write_basis_blade(os, itr->first);
					}
				}
				os << "]";
			}

			template<class ElementType, class... OtherElementTypes>
			void write(std::ostream &os, clifford_expression<ElementType, OtherElementTypes...> const &rhs, bool &first) {
				write_element(os, rhs.element(), first);
				write(os, rhs.next(), first);
			}

			inline void write(std::ostream &, clifford_expression<> const &, bool const) {
			}

		}

		using lazy::operator<<;

		template<class... RightElementTypes>
		std::ostream & operator<<(std::ostream &os, clifford_expression<RightElementTypes...> const &rhs) {
			bool first = true;
			detail::write(os, detail::begin(rhs), first);

			if (first) {
				os << constant<0>();
			}

			return os;
		}

	}

}

#endif // __GA_CLIFFORD_INSERTION_OPERATOR_HPP__
