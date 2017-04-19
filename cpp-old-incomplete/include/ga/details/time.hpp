struct compile_time_tag {};
struct runtime_tag {};

template<class T>
struct is_compile_time :
	is_same<typename T::time, compile_time_tag> {};

template<class T>
struct is_runtime :
	is_same<typename T::time, runtime_tag> {};
