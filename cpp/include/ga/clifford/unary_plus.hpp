#ifndef __GA_CLIFFORD_UNARY_PLUS_HPP__
#define __GA_CLIFFORD_UNARY_PLUS_HPP__

namespace ga {

	namespace clifford {

		using lazy::operator+;

		template<class RightExpressionType>
		constexpr RightExpressionType operator+(clifford_expression<RightExpressionType> const &rhs) {
			return rhs();
		}

	}

}

#endif // __GA_CLIFFORD_UNARY_PLUS_HPP__
