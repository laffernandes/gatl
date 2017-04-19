struct dynamic_value {

	typedef dynamic_value    type;
	typedef runtime_tag      time;
};

template<int32_t Value>
struct static_value {

	typedef static_value     type;
	typedef compile_time_tag time;

	static const int32_t value = Value;
};
