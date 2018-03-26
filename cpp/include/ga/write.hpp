#ifndef __GA_WRITE_HPP__
#define __GA_WRITE_HPP__

namespace ga {

	namespace detail {

		template<class ValueType>
		void write_coefficient(std::ostream &os, ValueType const &rhs, bool const first) {
			if (first) {
				os << rhs;
			}
			else {
				if (rhs >= static_cast<ValueType>(0)) {
					os << " + ";
				}
				else {
					os << " - ";
				}
				os << abs(rhs);
			}
		}

		template<default_integral_t Value>
		void write_coefficient(std::ostream &os, cvalue<Value> const &, bool const first) {
			if (!first) {
				os << " + ";
			}
			os << "<";
			write_coefficient(os, Value, true);
			os << ">";
		}

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
			write_basis_blade(os, rhs.value());
		}

		template<class CoefficientType, class BasisBladeType>
		void write_element(std::ostream &os, component<CoefficientType, BasisBladeType> const &rhs, bool &first) {
			write_coefficient(os, rhs.coefficient(), first);
			os << " * ";
			write_basis_blade(os, rhs.basis_blade());
			first = false;
		}

		template<class CoefficientType, default_bitset_t PossibleGrades>
		void write_element(std::ostream &os, components<CoefficientType, PossibleGrades> const &rhs, bool &first) {
			if (first) {
				os << "[";
			}
			else {
				os << " + [";
				first = true;
			}
			if (!rhs.empty()) {
				for (auto itr = rhs.begin(), end = rhs.end(); itr != end; ++itr) {
					write_coefficient(os, itr->second, first);
					os << " * ";
					write_basis_blade(os, itr->first);
					first = false;
				}
			}
			else {
				write_coefficient(os, cvalue<0>(), first);
				first = false;
			}
			os << "]";
		}

		template<class ItrType>
		void write(std::ostream &os, ItrType const &rhs, bool &first) {
			write_element(os, rhs.element(), first);
			write(os, next(rhs), first);
		}

		void write(std::ostream &, itr_end const &, bool const) {
		}

	}

}

template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
std::ostream & operator<<(std::ostream &os, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
	bool first = true;
	ga::detail::write(os, ga::detail::obegin(rhs), first);
	return os;
}

std::ostream & operator<<(std::ostream &os, ga::detail::empty_expression const &) {
	ga::detail::write_coefficient(os, ga::detail::cvalue<0>(), true);
	return os;
}

template<ga::default_integral_t Value>
std::ostream & operator<<(std::ostream &os, ga::detail::cvalue<Value> const &rhs) {
	ga::detail::write_coefficient(os, rhs, true);
	return os;
}

#endif // __GA_WRITE_HPP__
