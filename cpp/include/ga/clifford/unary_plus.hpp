#ifndef __GA_CLIFFORD_UNARY_PLUS_HPP__
#define __GA_CLIFFORD_UNARY_PLUS_HPP__

namespace ga {

	namespace clifford {

		using lazy::operator+;

		template<class... RightElementTypes>
		constexpr clifford_expression<RightElementTypes...> operator+(clifford_expression<RightElementTypes...> const &rhs) {
			return rhs;
		}

	}

}

#endif // __GA_CLIFFORD_UNARY_PLUS_HPP__
