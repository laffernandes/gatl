#ifndef __GA_CLIFFORD_WRITE_HPP__
#define __GA_CLIFFORD_WRITE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType>
			void write_coefficient(std::ostream &os, lazy_expression<ExpressionType> const &rhs, bool const first) {
				if (!first) {
					os << " + ";
				}
				os << rhs;
			}

			template<class ValueType>
			void write_coefficient(std::ostream &os, value<ValueType> const &rhs, bool const first) {
				if (first) {
					os << rhs.get();
				}
				else {
					if (rhs.get() >= static_cast<ValueType>(0)) {
						os << " + ";
					}
					else {
						if (rhs.get() < static_cast<ValueType>(0)) {
							os << " - ";
						}
					}
					os << abs(rhs.get());
				}
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
				write_basis_blade(os, rhs.get());
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
					write_coefficient(os, constant<0>(), first);
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

		using lazy::operator<<;

		template<class RightExpressionType>
		std::ostream & operator<<(std::ostream &os, clifford_expression<RightExpressionType> const &rhs) {
			bool first = true;
			detail::write(os, detail::obegin(rhs()), first);
			return os;
		}

		std::ostream & operator<<(std::ostream &os, detail::empty_expression_tree const &) {
			os << constant<0>();
			return os;
		}

	}

}

#endif // __GA_CLIFFORD_WRITE_HPP__
