class illegal_call_exception : std::runtime_error {
public:

	inline
	illegal_call_exception() :
		std::runtime_error("Illegal call to invalid constructor or method. Please contact Leandro A. F. Fernandes (laffernandes@ic.uff.br).") {}
};
