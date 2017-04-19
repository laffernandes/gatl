template<class T>
struct is_compile_time :
	std::is_same<typename T::time, compile_time_tag> {};

template<class T>
struct is_runtime :
	std::is_same<typename T::time, runtime_tag> {};
