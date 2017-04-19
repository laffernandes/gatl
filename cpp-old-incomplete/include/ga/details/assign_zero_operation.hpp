template<class Bitset>
struct assign_zero_operation<pack<single_basis_blade<basis_vectors<Bitset>, dynamic_value>, identity_operation> > {

	typedef pack<single_basis_blade<basis_vectors<Bitset>, dynamic_value>, identity_operation> result_type;
	typedef assign_zero_operation                                                              type;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		result.coefficient() = typename ResultInserter::multivector_type::coefficient_type(0);
	}
};

template<class SpaceBitset, class StepsBitset>
struct assign_zero_operation<pack<single_basis_blade<steps<SpaceBitset, StepsBitset>, dynamic_value>, identity_operation> > {

	typedef pack<single_basis_blade<steps<SpaceBitset, StepsBitset>, dynamic_value>, identity_operation> result_type;
	typedef assign_zero_operation                                                                        type;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		//TODO Parei aqui. result.basis_blade()
		result.coefficient() = typename ResultInserter::multivector_type::coefficient_type(0);
	}
};

template<class SpaceBitset, class StepsBitset, class Count>
struct assign_zero_operation<pack<multiple_basis_blades<steps<SpaceBitset, StepsBitset>, Count>, identity_operation> > {

	typedef pack<multiple_basis_blades<steps<SpaceBitset, StepsBitset>, Count>, identity_operation> result_type;
	typedef assign_zero_operation                                                                   type;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		//TODO Parei aqui.
		/*
		ArgumentConstIterator argument_copy = go_to<argument_type>(get_argument<input_argument_id<Path> >(arguments));
		for (::size_t i = 0; i < argument_copy.stride(); ++i) {
			map<type>(result, argument_copy.basis_blade()).coefficient() += argument_copy.coefficient();
			argument_copy.advance();
		}
		*/
	}
};
