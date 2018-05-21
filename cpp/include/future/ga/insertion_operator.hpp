#ifndef __FUTURE_GA_INSERTION_OPERATOR_HPP__
#define __FUTURE_GA_INSERTION_OPERATOR_HPP__

namespace ga {

	namespace detail {

		void write_basis_blade(std::ostream &os, default_bitset_t arg) {
			if (arg == 0) {
				os << "1";
			}
			else {
				int ind = 0;
				bool first = true;
				while (arg != 0) {
					if ((arg & 1) != 0) {
						if (!first) os << "^";
						else first = false;
						os << "e" << (ind + 1);
					}
					arg >>= 1;
					++ind;
				}
			}
		}

		template<class Expression>
		struct write;

		template<default_integral_t Value>
		struct write<constant_value<Value> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &, bool &first) {
				os << "<" << Value << ">";
				first = false;
			}
		};

		template<id_t Id, std::size_t Index>
		struct write<get_value<Id, Index> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &, bool &first) {
				os << "{Id: " << Id << ", ValueIndex: " << Index << "}";
				first = false;
			}
		};

		template<>
		struct write<stored_value> {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &, bool &first) {
				if (first) {
					os << (*value_citr);
					first = false;
				}
				else {
					if ((*value_citr) >= 0) {
						os << (*value_citr);
					}
					else {
						os << "(" << (*value_citr) << ")";
					}
				}
				++value_citr;
			}
		};

		template<default_bitset_t Bitset>
		struct write<constant_bitset<Bitset> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &, bool &first) {
				os << "<";
				write_basis_blade(os, Bitset);
				os >> ">";
				first = false;
			}
		};

		template<id_t Id, std::size_t Index>
		struct write<get_bitset<Id, Index> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &, bool &first) {
				os << "{Id: " << Id << ", BitsetIndex: " << Index << "}";
				first = false;
			}
		};

		template<>
		struct write<stored_bitset> {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &bitset_citr, bool &first) {
				write_basis_blade(os, *bitset_citr);
				++bitset_citr;
				first = false;
			}
		};

		template<default_bitset_t BasisVectors>
		struct write<constant_basis_blade<BasisVectors> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, bool &first) {
				write<constant_bitset<BasisVectors> >::run(os, value_citr, bitset_citr, first);
				first = false;
			}
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct write<dynamic_basis_blade<PossibleGrades, Bitset> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, bool &first) {
				write<Bitset>::run(os, value_citr, bitset_citr, first);
				first = false;
			}
		};

		template<class Coefficient, class BasisBlade>
		struct write<component<Coefficient, BasisBlade> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, bool &first) {
				os << "(";
				bool local_first = true;
				write<Coefficient>::run(os, value_citr, bitset_citr, local_first);
				os << ") * ";
				write<BasisBlade>::run(os, value_citr, bitset_citr, first);
				first = false;
			}
		};

		template<class Argument, class... NextArguments>
		struct write<add<Argument, NextArguments...> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, bool &first) {
				if (!first) {
					os << " + ";
				}
				write<Argument>::run(os, value_citr, bitset_citr, first);
				write<add<NextArguments...> >::run(os, value_citr, bitset_citr, first);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write<add<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, bool &first) {
				if (!first) {
					os << " + ";
				}
				write<LeftArgument>::run(os, value_citr, bitset_citr, first);
				os << " + ";
				write<RightArgument>::run(os, value_citr, bitset_citr, first);
			}
		};

		template<class Argument, class... NextArguments>
		struct write<mul<Argument, NextArguments...> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, bool &first) {
				if (!first) {
					os << " * ";
				}
				write<Argument>::run(os, value_citr, bitset_citr, first);
				write<mul<NextArguments...> >::run(os, value_citr, bitset_citr, first);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write<mul<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, bool &first) {
				if (!first) {
					os << " * ";
				}
				write<LeftArgument>::run(os, value_citr, bitset_citr, first);
				os << " * ";
				write<RightArgument>::run(os, value_citr, bitset_citr, first);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write<power<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, bool &first) {
				bool local_first = true;
				os << "pow(";
				write<LeftArgument>::run(os, value_citr, bitset_citr, local_first);
				os << ", ";
				local_first = true;
				write<RightArgument>::run(os, value_citr, bitset_citr, local_first);
				os << ")";
				first = false;
			}
		};
	
	}

	template<class RightCoefficientType, class RightExpression>
	std::ostream & operator<<(std::ostream &os, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		bool first = true;
		detail::write<RightExpression>::run(os, rhs.values().cbegin(), rhs.bitsets().cbegin(), first);

		if (first) {
			os << constant<0>();
		}

		return os;
	}

}

#endif // __FUTURE_GA_INSERTION_OPERATOR_HPP__
