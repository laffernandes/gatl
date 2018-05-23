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
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &, MapCIts &, bool &first) {
				os << "<" << Value << ">";
				first = false;
			}
		};

		template<id_t Id, std::size_t Index>
		struct write<get_value<Id, Index> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &, MapCIts &, bool &first) {
				os << "{Id: " << Id << ", ValueIndex: " << Index << "}";
				first = false;
			}
		};

		template<id_t Id, std::size_t Index>
		struct write<get_map_values<Id, Index> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &, MapCIts &, bool &first) {
				os << "[{Id: " << Id << ", MapValuesIndex: " << Index << "}]";
				first = false;
			}
		};

		template<>
		struct write<stored_value> {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &, MapCIts &, bool &first) {
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
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &, MapCIts &, bool &first) {
				os << "<";
				write_basis_blade(os, Bitset);
				os >> ">";
				first = false;
			}
		};

		template<id_t Id, std::size_t Index>
		struct write<get_bitset<Id, Index> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &, MapCIts &, bool &first) {
				os << "{Id: " << Id << ", BitsetIndex: " << Index << "}";
				first = false;
			}
		};

		template<id_t Id, std::size_t Index>
		struct write<get_map_bitsets<Id, Index> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &, MapCIts &, bool &first) {
				os << "[{Id: " << Id << ", MapBitsetsIndex: " << Index << "}]";
				first = false;
			}
		};

		template<>
		struct write<stored_bitset> {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &, BitsetCItr &bitset_citr, MapCIts &, bool &first) {
				write_basis_blade(os, *bitset_citr);
				++bitset_citr;
				first = false;
			}
		};

		template<default_bitset_t BasisVectors>
		struct write<constant_basis_blade<BasisVectors> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				write<constant_bitset<BasisVectors> >::run(os, value_citr, bitset_citr, map_citr, first);
				first = false;
			}
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct write<dynamic_basis_blade<PossibleGrades, Bitset> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				write<Bitset>::run(os, value_citr, bitset_citr, map_citr, first);
				first = false;
			}
		};

		template<class Coefficient, class BasisBlade>
		struct write<component<Coefficient, BasisBlade> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				os << "(";
				bool local_first = true;
				write<Coefficient>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ") * ";
				write<BasisBlade>::run(os, value_citr, bitset_citr, map_citr, first);
				first = false;
			}
		};

		template<default_bitset_t PossibleGrades>
		struct write<stored_components_map<PossibleGrades> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				os << "[";
				if (!map_citr->empty()) {
					bool local_first = true;
					for (auto &curr : *map_citr) {
						if (!local_first) {
							os << " + ";
						}
						else {
							local_first = false;
						}
						if (curr.second >= 0) {
							os << curr.second;
						}
						else {
							os << "(" << curr.second << ")";
						}
						os << " * ";
						write_basis_blade(os, curr.first)
					}
				}
				else {
					os << c<0>;
				}
				os << "]";
				++map_citr;
				first = false;
			}
		};

		template<class Argument, class... NextArguments>
		struct write<add<Argument, NextArguments...> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				if (!first) {
					os << " + ";
				}
				write<Argument>::run(os, value_citr, bitset_citr, map_citr, first);
				write<add<NextArguments...> >::run(os, value_citr, bitset_citr, map_citr, first);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write<add<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				if (!first) {
					os << " + ";
				}
				write<LeftArgument>::run(os, value_citr, bitset_citr, map_citr, first);
				os << " + ";
				write<RightArgument>::run(os, value_citr, bitset_citr, map_citr, first);
			}
		};

		template<class Argument, class... NextArguments>
		struct write<mul<Argument, NextArguments...> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				if (!first) {
					os << " * ";
				}
				write<Argument>::run(os, value_citr, bitset_citr, map_citr, first);
				write<mul<NextArguments...> >::run(os, value_citr, bitset_citr, map_citr, first);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write<mul<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				if (!first) {
					os << " * ";
				}
				write<LeftArgument>::run(os, value_citr, bitset_citr, map_citr, first);
				os << " * ";
				write<RightArgument>::run(os, value_citr, bitset_citr, map_citr, first);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write<power<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				bool local_first = true;
				os << "pow(";
				write<LeftArgument>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ", ";
				local_first = true;
				write<RightArgument>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ")";
				first = false;
			}
		};

		template<class LeftBitset, class RightBitset>
		struct write<reordering_sign<LeftBitset, RightBitset> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				bool local_first = true;
				os << "reordering_sign(";
				write<LeftBitset>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ", ";
				local_first = true;
				write<RightBitset>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ")";
				first = false;
			}
		};
	
		template<class Bitset>
		struct write<count_one_bits<Bitset> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				bool local_first = true;
				os << "count_one_bits(";
				write<Bitset>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ")";
				first = false;
			}
		};

		template<class LeftType, class RightType>
		struct write<bitwise_left_shift<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				bool local_first = true;
				os << "(";
				write<LeftType>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << " LSHIFTb ";
				local_first = true;
				write<RightType>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ")";
				first = false;
			}
		};

		template<class LeftType, class RightType>
		struct write<bitwise_and<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				bool local_first = true;
				os << "(";
				write<LeftType>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << " ANDb ";
				local_first = true;
				write<RightType>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ")";
				first = false;
			}
		};

		template<class LeftType, class RightType>
		struct write<bitwise_xor<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				bool local_first = true;
				os << "(";
				write<LeftType>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << " XORb ";
				local_first = true;
				write<RightType>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ")";
				first = false;
			}
		};

		template<class LeftType, class RightType>
		struct write<equal<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				bool local_first = true;
				os << "(";
				write<LeftType>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << " == ";
				local_first = true;
				write<RightType>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ")";
				first = false;
			}
		};

		template<class Test, class TrueResult, class FalseResult>
		struct write<if_else<Test, TrueResult, FalseResult> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, bool &first) {
				bool local_first = true;
				os << "(";
				write<Test>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << " ? ";
				local_first = true;
				write<TrueResult>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << " : ";
				local_first = true;
				write<FalseResult>::run(os, value_citr, bitset_citr, map_citr, local_first);
				os << ")";
				first = false;
			}
		};

	}

	template<class RightCoefficientType, class RightExpression>
	std::ostream & operator<<(std::ostream &os, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		bool first = true;
		auto value_citr = rhs.values().cbegin();
		auto bitset_citr = rhs.bitsets().cbegin();
		auto map_citr = rhs.bitsets().cbegin();
		detail::write<RightExpression>::run(os, value_citr, bitset_citr, map_citr, first);

		if (first) {
			os << constant<0>();
		}

		return os;
	}

}

#endif // __FUTURE_GA_INSERTION_OPERATOR_HPP__
