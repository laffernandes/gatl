template<class Pack, class LeftSubtree, class RightSubtree>
struct tree {

	typedef tree         type;
	
	typedef typename if_<and_<is_compile_time<Pack>, is_compile_time<LeftSubtree>, is_compile_time<RightSubtree> >, compile_time_tag, runtime_tag>::type time;

	typedef Pack         pack;

	typedef LeftSubtree  left;
	typedef RightSubtree right;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		left::eval(result, arguments);
		
		pack::eval(result, arguments);
		advance<typename pack::components, is_runtime<pack>::value>(result);
		
		right::eval(result, arguments);
	}
};

struct empty_tree {

	typedef empty_tree type;

	typedef compile_time_tag time;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		// Nothing to be done.
	}
};
