#ifndef __GA_DEFAULT_TOLERANCE_HPP__
#define __GA_DEFAULT_TOLERANCE_HPP__

#ifndef GA_DEFAULT_FLT_TOLERANCE
	#define GA_DEFAULT_FLT_TOLERANCE 1.0e-8f
#else
	static_assert(GA_DEFAULT_FLT_TOLERANCE >= 0, "GA_DEFAULT_FLT_TOLERANCE must be a non-negative value.")
#endif // GA_DEFAULT_FLT_TOLERANCE

#ifndef GA_DEFAULT_DBL_TOLERANCE
	#define GA_DEFAULT_DBL_TOLERANCE 1.0e-8
#else
	static_assert(GA_DEFAULT_DBL_TOLERANCE >= 0, "GA_DEFAULT_DBL_TOLERANCE must be a non-negative value.")
#endif // GA_DEFAULT_DBL_TOLERANCE

namespace ga {

	template<class ValueType>
	constexpr ValueType default_tolerance() {
		static_assert(std::is_integral<ValueType>::value, "Invalid integral or floating point type. Maybe you have to specialize 'template<class ValueType> constexpr ValueType ga::default_tolerance()' function to some custom ValueType class.");
		return static_cast<ValueType>(0);
	}

	template<>
	constexpr std::float_t default_tolerance<std::float_t>() {
		return GA_DEFAULT_FLT_TOLERANCE;
	}

	template<>
	constexpr std::double_t default_tolerance<std::double_t>() {
		return GA_DEFAULT_DBL_TOLERANCE;
	}

}

#endif // __GA_DEFAULT_TOLERANCE_HPP__
