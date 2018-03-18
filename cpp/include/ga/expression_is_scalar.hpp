#ifndef __GA_EXPRESSION_IS_SCALAR_HPP__
#define __GA_EXPRESSION_IS_SCALAR_HPP__

namespace ga {

	namespace detail {

		template<class ExpressionType>
		struct is_scalar_expression {
			constexpr static bool value = false;
		};

		template<class CoefficientType>
		struct is_scalar_expression<expression<component<CoefficientType, cbasis_blade<0> >, empty_expression, empty_expression> > {
			constexpr static bool value = true;
		};

		template<class CoefficientType>
		struct is_scalar_expression<expression<component<CoefficientType, dbasis_blade<default_bitset_t(1)> >, empty_expression, empty_expression> > {
			constexpr static bool value = true;
		};

		template<class CoefficientType>
		struct is_scalar_expression<expression<components<CoefficientType, default_bitset_t(1)>, empty_expression, empty_expression> > {
			constexpr static bool value = true;
		};

		template<>
		struct is_scalar_expression<empty_expression> {
			constexpr static bool value = true;
		};

	}

}

#endif // __GA_EXPRESSION_IS_SCALAR_HPP__
