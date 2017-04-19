// BasisVectors adaptor for StaticBitset.
//   Bitset must be a static_bitset<> structure.
template<class Bitset>
struct basis_vectors;

template<bitset_element_t Bits, class Next>
struct basis_vectors<static_bitset<Bits, Next> > :
	static_bitset<Bits, Next> {};

// Steps adaptor for StaticBitset.
//   SpaceBitset must be a static_bitset<> structure.
//   StepsBitset must be a static_bitset<> structure.
template<class SpaceBitset, class StepsBitset>
struct steps;

template<bitset_element_t SpaceBits, class SpaceNext, bitset_element_t StepsBits, class StepsNext>
struct steps<static_bitset<SpaceBits, SpaceNext>, static_bitset<StepsBits, StepsNext> > {
	
	//TODO static_assert(or_<less<static_bitset<StepsBits, StepsNext>, typename make_pseudoscalar_bitset<>::type>, equal<static_bitset<StepsBits, StepsNext>, typename make_pseudoscalar_bitset<>::type> >::value, "Invalid set of steps for the given set of basis vectors.");
	static_assert(any<static_bitset<SpaceBits, SpaceNext> >::value, "Invalid set of basis vectors. The component should be a single_basis_blade<basis_vectors<[zero]>, dynamic_value>.");
	static_assert(any<static_bitset<StepsBits, StepsNext> >::value, "Invalid set of steps. The component should be a single_basis_blade<basis_vectors<[zero]>, dynamic_value>.");
};

// Components concept implementation for single basis blade.
//   BasisBlade may be a basis_vectors<> or a steps<> structure.
//   Coefficient may be a static_value<> or a dynamic_value structure.
template<class BasisBlade, class Coefficient>
struct single_basis_blade;

template<class Bitset, int Value>
struct single_basis_blade<basis_vectors<Bitset>, static_value<Value> > {

	typedef single_basis_blade  type;

	typedef compile_time_tag    time;

	typedef Bitset              space;
	typedef typename set<make_empty_bitset<>, cardinality<Bitset>::value>::type steps;
	typedef Bitset              basis_vectors;
	typedef static_value<Value> coefficient;

	typedef static_value<1>     count;
	typedef static_value<1>     max_count;
};

template<class Bitset>
struct single_basis_blade<basis_vectors<Bitset>, dynamic_value> {

	typedef single_basis_blade type;

	typedef runtime_tag        time;

	typedef Bitset             space;
	typedef typename set<make_empty_bitset<>, cardinality<Bitset>::value>::type steps;
	typedef Bitset             basis_vectors;
	typedef dynamic_value      coefficient;

	typedef static_value<1>    count;
	typedef static_value<1>    max_count;
};

template<class SpaceBitset, class StepsBitset, int Value>
struct single_basis_blade<steps<SpaceBitset, StepsBitset>, static_value<Value> > {

	typedef single_basis_blade  type;

	typedef runtime_tag         time;

	typedef SpaceBitset         space;
	typedef StepsBitset         steps;
	typedef dynamic_value       basis_vectors;
	typedef static_value<Value> coefficient;

	typedef static_value<1>     count;
	typedef static_value<1>     max_count;
};

template<class SpaceBitset, class StepsBitset>
struct single_basis_blade<steps<SpaceBitset, StepsBitset>, dynamic_value> {

	typedef single_basis_blade type;

	typedef runtime_tag        time;

	typedef SpaceBitset        space;
	typedef StepsBitset        steps;
	typedef dynamic_value      basis_vectors;
	typedef dynamic_value      coefficient;

	typedef static_value<1>    count;
	typedef static_value<1>    max_count;
};

// Components concept implementation for multiple basis blades.
//   Steps concept is implemented by steps<> structure.
//   Count concept is implemented by static_value<> and dynamic_value structure.
template <class Steps, class Count>
struct multiple_basis_blades;

template <class SpaceBitset, class StepsBitset, int N>
struct multiple_basis_blades<steps<SpaceBitset, StepsBitset>, static_value<N> > {
	static_assert((N > 0), "Invalid number of basis blades.");

	typedef multiple_basis_blades type;

	typedef runtime_tag           time;

	typedef SpaceBitset           space;
	typedef StepsBitset           steps;
	typedef dynamic_value         basis_vectors;
	typedef dynamic_value         coefficient;

	typedef dynamic_value         count;
	typedef static_value<N>       max_count;
};

template <class SpaceBitset, class StepsBitset>
struct multiple_basis_blades<steps<SpaceBitset, StepsBitset>, dynamic_value> {

	typedef multiple_basis_blades type;

	typedef runtime_tag           time;

	typedef SpaceBitset           space;
	typedef StepsBitset           steps;
	typedef dynamic_value         basis_vectors;
	typedef dynamic_value         coefficient;

	typedef dynamic_value         count;
	typedef dynamic_value         max_count;
};

// Pack setup.
//   Components may be a single_basis_blade<> or a multiple_basis_blades<> structure.
//   Operation may be identity operation or any implementation of the operation concept.
template<class Components, class Operation>
struct pack {

	typedef pack                      type;

	typedef typename Components::time time;

	typedef Components                components;
	typedef Operation                 operation;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		//TODO Parei aqui.
	}
};

template<class Components, class Argument>
struct pack<Components, first_argument_tag<Argument> > {

	typedef pack                         type;

	typedef typename Components::time    time;

	typedef Components                   components;
	typedef first_argument_tag<Argument> operation;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		//TODO Parei aqui.
	}
};

template<class Components, class Argument>
struct pack<Components, second_argument_tag<Argument> > {

	typedef pack                          type;

	typedef typename Components::time     time;

	typedef Components                    components;
	typedef second_argument_tag<Argument> operation;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		//TODO Parei aqui.
	}
};

template<class Components, class Argument>
struct pack<Components, single_argument_tag<Argument> > {

	typedef pack                          type;

	typedef typename Components::time     time;

	typedef Components                    components;
	typedef single_argument_tag<Argument> operation;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		//TODO Parei aqui.
	}
};
