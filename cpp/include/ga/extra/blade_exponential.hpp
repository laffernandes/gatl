#ifndef __GA_EXTRA_BLADE_EXPONENTIATION_HPP__
#define __GA_EXTRA_BLADE_EXPONENTIATION_HPP__

namespace ga {

	template<class CoefficientType, class Expression, class ToleranceCoefficient, class MetricSpaceType>
	constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg, scalar_clifford_expression<CoefficientType, ToleranceCoefficient> const &tol, metric_space<MetricSpaceType> const &) {
		typedef decltype(make_lazy_context(arg, tol)) lazy_context_type;

		typedef lazy_context_type::argument_expression_t<0> blade_expression;
		typedef detail::coefficient_t<lazy_context_type::argument_expression_t<1> > tolerance_value;

		typedef detail::coefficient_t<detail::product_t<blade_expression, blade_expression, detail::metric_space_mapping_t<MetricSpaceType, detail::sp_mapping> > > signed_squared_alpha_value;
		typedef detail::absolute_t<signed_squared_alpha_value> squared_alpha_value;
		typedef detail::power_t<squared_alpha_value, detail::power_t<detail::constant_value<2>, detail::constant_value<-1> > > alpha_value;

		typedef detail::if_else_t<
			detail::less_or_equal_t<squared_alpha_value, tolerance_value>,
			detail::constant_value<1>,
			detail::if_else_t<
				detail::less_or_equal_t<signed_squared_alpha_value, detail::constant_value<0> >,
				detail::cosine_t<alpha_value>,
				detail::hyperbolic_cosine_t<alpha_value>
			>
		> scalar_coefficient_value;

		typedef detail::if_else_t<
			detail::less_or_equal_t<squared_alpha_value, tolerance_value>,
			detail::constant_value<1>,
			detail::if_else_t<
				detail::less_or_equal_t<signed_squared_alpha_value, detail::constant_value<0> >,
				detail::product_t<detail::sine_t<alpha_value>, detail::power_t<alpha_value, detail::constant_value<-1> >, detail::value_mapping>,
				detail::product_t<detail::hyperbolic_sine_t<alpha_value>, detail::power_t<alpha_value, detail::constant_value<-1> >, detail::value_mapping>
			>
		> blade_weight_value;

		typedef detail::addition_t<
			detail::component_t<scalar_coefficient_value, detail::constant_basis_blade<default_bitset_t(0)> >,
			detail::product_t<
				detail::component_t<blade_weight_value, detail::constant_basis_blade<default_bitset_t(0)> >,
				blade_expression,
				detail::exterior_product_mapping<MetricSpaceType::vector_space_dimensions>
			>
		> result_expression;

		auto const lazy = make_lazy_context(arg, tol);
		return lazy.eval(clifford_expression<default_integral_t, result_expression>());
	}

	template<class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg, CoefficientType const &tol, metric_space<MetricSpaceType> const &) {
		return exp(arg, scalar(tol), mtr);
	}

	template<class CoefficientType, class Expression, class MetricSpaceType>
	constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		return exp(arg, default_tolerance<CoefficientType>(), mtr);
	}

	template<class CoefficientType, class Coefficient, class MetricSpaceType>
	constexpr decltype(auto) exp(scalar_clifford_expression<CoefficientType, Coefficient> const &arg, CoefficientType const &, metric_space<MetricSpaceType> const &) {
		return exp(arg);
	}

	template<class CoefficientType, class Coefficient, class MetricSpaceType>
	constexpr decltype(auto) exp(scalar_clifford_expression<CoefficientType, Coefficient> const &arg, metric_space<MetricSpaceType> const &) {
		return exp(arg);
	}

	template<class Type, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) exp(Type const &arg, Type const &, metric_space<MetricSpaceType> const &) {
		return exp(arg);
	}

	template<class Type, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) exp(Type const &arg, metric_space<MetricSpaceType> const &) {
		return exp(arg);
	}

	template<class Type, class = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) exp(Type const &arg, Type const &) {
		return exp(arg);
	}

}

#endif // __GA_EXTRA_BLADE_EXPONENTIATION_HPP__
