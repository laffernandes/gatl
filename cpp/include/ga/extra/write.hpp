#ifndef __GA_EXTRA_WRITE_HPP__
#define __GA_EXTRA_WRITE_HPP__

namespace ga {

	namespace detail {

		template<std::size_t N>
		void write_basis_blade(std::ostream &os, default_bitset_t const arg, std::string const(&basis_vectors)[N]) {
			if (arg == default_bitset_t(0)) {
				os << "1";
			}
			else {
				default_bitset_t bitset = arg;
				while (bitset != default_bitset_t(0)) {
					default_bitset_t const first_set_bit = rightmost_set_bit(bitset);

					if (bitset != arg) os << "^";
					os << basis_vectors[ones(first_set_bit - std::make_signed_t<default_bitset_t>(1))];

					bitset ^= first_set_bit;
				}
			}
		}

		template<class Expression>
		struct write_expression;

		template<default_integral_t Value>
		struct write_expression<constant_value<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr const &, BitsetCItr const &, MapCIts const &, std::string const(&)[N]) {
				os << "<" << Value << ">";
			}
		};

		template<tag_t Tag, std::size_t Index>
		struct write_expression<get_value<Tag, Index> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr const &, BitsetCItr const &, MapCIts const &, std::string const(&)[N]) {
				os << "{Tag: " << Tag << ", ValueIndex: " << Index << "}";
			}
		};

		template<tag_t Tag, std::size_t Index>
		struct write_expression<get_map_values<Tag, Index> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr const &, BitsetCItr const &, MapCIts const &, std::string const(&)[N]) {
				os << "[{Tag: " << Tag << ", MapValuesIndex: " << Index << "}]";
			}
		};

		template<>
		struct write_expression<stored_value> {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr const &, MapCIts const &, std::string const(&)[N]) {
				if ((*value_citr) >= 0) os << (*value_citr);
				else os << "(" << (*value_citr) << ")";
				std::advance(value_citr, 1);
			}
		};

		template<default_bitset_t Bitset>
		struct write_expression<constant_bitset<Bitset> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr const &, BitsetCItr const &, MapCIts const &, std::string const(&basis_vectors)[N]) {
				os << "<";
				write_basis_blade(os, Bitset, basis_vectors);
				os << ">";
			}
		};

		template<tag_t Tag, std::size_t Index>
		struct write_expression<get_bitset<Tag, Index> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr const &, BitsetCItr const &, MapCIts const &, std::string const(&)[N]) {
				os << "{Tag: " << Tag << ", BitsetIndex: " << Index << "}";
			}
		};

		template<tag_t Tag, std::size_t Index>
		struct write_expression<get_map_bitsets<Tag, Index> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr const &, BitsetCItr const &, MapCIts const &, std::string const(&)[N]) {
				os << "[{Tag: " << Tag << ", MapBitsetsIndex: " << Index << "}]";
			}
		};

		template<>
		struct write_expression<stored_bitset> {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr const &, BitsetCItr &bitset_citr, MapCIts const &, std::string const(&basis_vectors)[N]) {
				write_basis_blade(os, *bitset_citr, basis_vectors);
				std::advance(bitset_citr, 1);
			}
		};

		template<default_bitset_t BasisVectors>
		struct write_expression<constant_basis_blade<BasisVectors> > : write_expression<constant_bitset<BasisVectors> >  {
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct write_expression<dynamic_basis_blade<PossibleGrades, Bitset> > : write_expression<Bitset> {
		};

		template<class Coefficient, class BasisBlade>
		struct write_expression<component<Coefficient, BasisBlade> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				if (is_function_v<name_t::add, Coefficient>) os << "(";
				write_expression<Coefficient>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				if (is_function_v<name_t::add, Coefficient>) os << ")";
				os << " * ";
				write_expression<BasisBlade>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
			}
		};

		template<default_bitset_t PossibleGrades>
		struct write_expression<component<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> > > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr const &, BitsetCItr const &, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "[";
				if (!map_citr->empty()) {
					bool first = true;
					for (auto &curr : *map_citr) {
						if (!first) os << " + ";
						else first = false;

						if (curr.second , 0) os << "(" << curr.second << ")";
						else os << curr.second;

						os << " * ";
						write_basis_blade(os, curr.first, basis_vectors);
					}
				}
				else {
					os << c<0>;
				}
				os << "]";
				std::advance(map_citr, 1);
			}
		};

		template<class Argument, class... NextArguments>
		struct write_expression<add<Argument, NextArguments...> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				write_expression<Argument>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " + ";
				write_expression<add<NextArguments...> >::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write_expression<add<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				write_expression<LeftArgument>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " + ";
				write_expression<RightArgument>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
			}
		};

		template<class Argument, class... NextArguments>
		struct write_expression<mul<Argument, NextArguments...> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				write_expression<Argument>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " * ";
				write_expression<mul<NextArguments...> >::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write_expression<mul<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				write_expression<LeftArgument>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " * ";
				write_expression<RightArgument>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
			}
		};

		template<class LeftArgument, class RightArgument>
		struct write_expression<power<LeftArgument, RightArgument> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "pow(";
				write_expression<LeftArgument>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ", ";
				write_expression<RightArgument>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<absolute<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "abs(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<exponential<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "exp(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<logarithm<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "log(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<cosine<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "cos(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<sine<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "sin(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<tangent<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "tan(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<hyperbolic_cosine<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "cosh(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<hyperbolic_sine<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "sinh(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Value>
		struct write_expression<hyperbolic_tangent<Value> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "tanh(";
				write_expression<Value>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class LeftBitset, class RightBitset>
		struct write_expression<reordering_sign<LeftBitset, RightBitset> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "reordering_sign(";
				write_expression<LeftBitset>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ", ";
				write_expression<RightBitset>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};
	
		template<class Bitset>
		struct write_expression<count_one_bits<Bitset> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "count_one_bits(";
				write_expression<Bitset>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class LeftType, class RightValue>
		struct write_expression<bitwise_left_shift<LeftType, RightValue> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<LeftType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " LSHIFTb ";
				write_expression<RightValue>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Bitset>
		struct write_expression<bitwise_uminus<Bitset> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(-";
				write_expression<Bitset>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Bitset>
		struct write_expression<bitwise_dec<Bitset> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<Bitset>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " - <1>)";
			}
		};

		template<class LeftType, class RightType>
		struct write_expression<bitwise_and<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<LeftType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " ANDb ";
				write_expression<RightType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class LeftType, class RightType>
		struct write_expression<bitwise_or<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<LeftType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " ORb ";
				write_expression<RightType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class LeftType, class RightType>
		struct write_expression<bitwise_xor<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<LeftType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " XORb ";
				write_expression<RightType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class LeftType, class RightType>
		struct write_expression<equal<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<LeftType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " == ";
				write_expression<RightType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class LeftType, class RightType>
		struct write_expression<less_or_equal<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<LeftType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " <= ";
				write_expression<RightType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class LeftType, class RightType>
		struct write_expression<logical_and<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<LeftType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " AND ";
				write_expression<RightType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class LeftType, class RightType>
		struct write_expression<logical_or<LeftType, RightType> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<LeftType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " OR ";
				write_expression<RightType>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

		template<class Test, class TrueValue, class FalseValue>
		struct write_expression<if_else<Test, TrueValue, FalseValue> > {
			template<class ValueCItr, class BitsetCItr, class MapCIts, std::size_t N>
			inline static void run(std::ostream &os, ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, std::string const(&basis_vectors)[N]) {
				os << "(";
				write_expression<Test>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " ? ";
				write_expression<TrueValue>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << " : ";
				write_expression<FalseValue>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
				os << ")";
			}
		};

	}

	template<class CoefficientType, class Expression, std::size_t N>
	std::ostream & write(std::ostream &os, clifford_expression<CoefficientType, Expression> const &expression, std::string const (&basis_vectors)[N]) {
		auto value_citr = expression.values().cbegin();
		auto bitset_citr = expression.bitsets().cbegin();
		auto map_citr = expression.maps().cbegin();
		detail::write_expression<Expression>::run(os, value_citr, bitset_citr, map_citr, basis_vectors);
		return os;
	}

}

#endif // __GA_EXTRA_WRITE_HPP__
