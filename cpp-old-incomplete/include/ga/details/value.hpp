// Value and Bitset concept tag for runtime defined values.
struct dynamic_value {

	typedef dynamic_value type;

	typedef runtime_tag   time;
};

// Value concept implementation for compile-time defined integral value.
template<int Value>
struct static_value {

	typedef static_value     type;

	typedef compile_time_tag time;

	static const int value = Value;
};
