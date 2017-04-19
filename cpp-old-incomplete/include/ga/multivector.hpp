// Multivector class.
//   CoefficientType must be some arithmetic type. If it is an integral type than it must be a signed one.
//   Composition must be a ga::details::tree<> structure or a ga::details::empty_tree structure (for concrete multivectors), or a expression (for lazy multivectors).
//   Container defines the datastructure used to keep runtime data (steps, basis blades, and coefficients).
template<class CoefficientType, class Composition, container_class Container = details::sugested_container_class<Composition>::value>
class multivector;

namespace details {

	// Weighted basis blade structure for uniform storage.
	template<class CoefficientType>
	class stored_component {
	public:

		typedef dynamic_bitset_t                                                               basis_blade_type;
		typedef dynamic_bitset_t&                                                              basis_blade_reference;
		typedef const dynamic_bitset_t&                                                        basis_blade_const_reference;

		typedef CoefficientType                                                                coefficient_type;
		typedef typename add_lvalue_reference<CoefficientType>::type                           coefficient_reference;
		typedef typename add_lvalue_reference<typename add_const<CoefficientType>::type>::type coefficient_const_reference;

	public:

		inline
		stored_component() :
			_basis_blade(),
			_coefficient(CoefficientType(0)) {}

	public:

		inline
		basis_blade_const_reference basis_blade() const {
			return _basis_blade;
		}

		inline
		basis_blade_reference basis_blade() {
			return _basis_blade;
		}

		inline
		coefficient_const_reference coefficient() const {
			return _coefficient;
		}

		inline
		coefficient_reference coefficient() {
			return _coefficient;
		}

	private:

		basis_blade_type _basis_blade;
		coefficient_type _coefficient;
	};

	// Multivector superclasses.
	template<class CoefficientType, class Expression, container_class Container>
	class lazy_multivector;

	template<class CoefficientType, class Composition, container_class Container>
	class concrete_multivector;

	template<class CoefficientType, class Composition, container_class Container>
	class multivector_with_nonuniform_storage;

	template<class CoefficientType, class Composition, container_class Container>
	class multivector_with_uniform_storage;

	template<class CoefficientType, class Expression, container_class Container>
	class lazy_multivector {
	public:

		typedef CoefficientType                  coefficient_type;
		typedef typename Expression::composition composition;

		static const container_class container = Container;

		typedef Expression                       expression_type;

	private:

		class storage_base_iterator {
		public:

			typedef lazy_multivector        multivector_type;

			typedef CoefficientType         coefficient_type;

			typedef const dynamic_bitset_t& basis_blade_reference;
			typedef const int&              coefficient_reference;
			typedef const ::size_t&         stride_reference;

		public:

			inline
			basis_blade_reference basis_blade() const {
				throw ga::illegal_call_exception();
			}

			inline
			coefficient_reference coefficient() const {
				throw ga::illegal_call_exception();
			}

			inline
			stride_reference stride() const {
				throw ga::illegal_call_exception();
			}

		public:

			inline
			void advance(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_basis_blade(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_coefficient(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_stride(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

		public:

			inline
			storage_base_iterator(const storage_base_iterator &other) {
				// Nothing to be done.
			}
		
		private:

			inline
			storage_base_iterator() {
				// Nothing to be done.
			};

		private:

			friend class lazy_multivector;
		};

	public:

		typedef storage_base_iterator storage_const_iterator;
		typedef storage_base_iterator storage_iterator;
		typedef storage_base_iterator storage_inserter;

		inline
		storage_const_iterator make_storage_const_iterator() const {
			return storage_const_iterator();
		}
	
		inline
		storage_iterator make_storage_iterator() const {
			return storage_iterator();
		}
	
		inline
		storage_inserter make_storage_inserter() const {
			return storage_inserter();
		}

	public:

		inline static
		bool is_concrete() {
			return false;
		}

		inline static
		bool is_lazy() {
			return true;
		}

	public:

		typedef typename Expression::concrete_type concrete_type;
		typedef concrete_type&                     concrete_reference;
		typedef const concrete_type&               concrete_const_reference;

		inline
		concrete_type eval() const {
			return _expression.eval();
		}

	protected:

		inline
		lazy_multivector(const lazy_multivector &other) :
			_expression(other._expression) {}

		inline
		lazy_multivector(const expression_type &expression) :
			_expression(expression) {}

	private:

		const expression_type _expression;

	private:

		template<class, class, container_class> friend class lazy_multivector;
		template<class, class, container_class> friend class multivector_with_nonuniform_storage;
		template<class, class, container_class> friend class multivector_with_uniform_storage;

		template<class> friend struct _write_impl;
	};

	template<class CoefficientType, class Composition, container_class Container>
	class concrete_multivector {
	public:

		typedef multivector<CoefficientType, Composition, Container> concrete_type;
		typedef concrete_type&                                       concrete_reference;
		typedef const concrete_type&                                 concrete_const_reference;

		inline
		concrete_const_reference eval() const {
			return *static_cast<const concrete_type*>(this);
		}

	public:

		inline static
		bool is_concrete() {
			return true;
		}

		inline static
		bool is_lazy() {
			return false;
		}

	protected:

		inline
		concrete_multivector() {
			// Nothing to be done.
		};
	};

	template<class CoefficientType, class Composition>
	class multivector_with_nonuniform_storage<CoefficientType, Composition, container_class::array> :
		public concrete_multivector<CoefficientType, Composition, container_class::array> {
	public:

		typedef CoefficientType      coefficient_type;
		typedef Composition          composition;

		static const container_class container = container_class::array;

	private:

		typedef std::array<dynamic_bitset_t, count_stored_basis_blades<Composition>::value> basis_blades_collection;
		typedef std::array<CoefficientType, count_stored_coefficients<Composition>::value>  coefficients_collection;
		typedef std::array<::size_t, count_dynamic_packs<Composition>::value>               strides_collection;

	private:

		template<class BasisBladesIterator, class CoefficientsIterator, class StridesIterator>
		class storage_base_iterator {
		public:

			typedef multivector_with_nonuniform_storage      multivector_type;

			typedef CoefficientType                          coefficient_type;

			typedef typename BasisBladesIterator::reference  basis_blade_reference;
			typedef typename CoefficientsIterator::reference coefficient_reference;
			typedef typename StridesIterator::reference      stride_reference;

		public:

			inline
			basis_blade_reference basis_blade() const {
				return *_basis_blades_itr;
			}

			inline
			coefficient_reference coefficient() const {
				return *_coefficients_itr;
			}

			inline
			stride_reference stride() const {
				return *_strides_itr;
			}

		public:

			inline
			void advance(const int n = 1) {
				std::advance(_basis_blades_itr, n);
				std::advance(_coefficients_itr, n);
			}

			inline
			void advance_basis_blade(const int n = 1) {
				std::advance(_basis_blades_itr, n);
			}

			inline
			void advance_coefficient(const int n = 1) {
				std::advance(_coefficients_itr, n);
			}

			inline
			void advance_stride(const int n = 1) {
				std::advance(_strides_itr, n);
			}

		public:

			inline
			storage_base_iterator(const storage_base_iterator &other) :
				_basis_blades_itr(other._basis_blades_itr), _coefficients_itr(other._coefficients_itr), _strides_itr(other._strides_itr) {};
		
		private:

			inline
			storage_base_iterator(const BasisBladesIterator &basis_blades_itr, const CoefficientsIterator &coefficients_itr, const StridesIterator &strides_itr) :
				_basis_blades_itr(basis_blades_itr), _coefficients_itr(coefficients_itr), _strides_itr(strides_itr) {};

		private:

			BasisBladesIterator  _basis_blades_itr;
			CoefficientsIterator _coefficients_itr;
			StridesIterator      _strides_itr;

			friend class multivector_with_nonuniform_storage;
		};

	public:

		typedef storage_base_iterator<typename basis_blades_collection::const_iterator, typename coefficients_collection::const_iterator, typename strides_collection::const_iterator> storage_const_iterator;
		typedef storage_base_iterator<typename basis_blades_collection::iterator, typename coefficients_collection::iterator, typename strides_collection::iterator>                   storage_iterator;
		typedef storage_base_iterator<typename basis_blades_collection::iterator, typename coefficients_collection::iterator, typename strides_collection::iterator>                   storage_inserter;

		inline
		storage_const_iterator make_storage_const_iterator() const {
			return storage_const_iterator(_stored_basis_blades.cbegin(), _stored_coefficients.cbegin(), _dynamic_packs_stride.cbegin());
		}
	
		inline
		storage_iterator make_storage_iterator() {
			return storage_iterator(_stored_basis_blades.begin(), _stored_coefficients.begin(), _dynamic_packs_stride.begin());
		}
	
		inline
		storage_inserter make_storage_inserter() {
			return storage_inserter(_stored_basis_blades.begin(), _stored_coefficients.begin(), _dynamic_packs_stride.begin());
		}

	protected:

		inline
		multivector_with_nonuniform_storage() :
			_dynamic_packs_stride(),
			_stored_basis_blades(),
			_stored_coefficients() {
			_dynamic_packs_stride.fill(0);
			_stored_coefficients.fill(CoefficientType(0));
		}

		inline
		multivector_with_nonuniform_storage(const multivector_with_nonuniform_storage &other) :
			_dynamic_packs_stride(other._dynamic_packs_stride),
			_stored_basis_blades(other._stored_basis_blades),
			_stored_coefficients(other._stored_coefficients) {}

		template<class Expression>
		inline
		multivector_with_nonuniform_storage(const expression<Expression> &expression) {
			throw ga::illegal_call_exception();
		}

	private:

		basis_blades_collection _stored_basis_blades;
		coefficients_collection _stored_coefficients;
		strides_collection      _dynamic_packs_stride;
	
	private:

		template<class, class, container_class> friend class lazy_multivector;
		template<class, class, container_class> friend class multivector_with_nonuniform_storage;
		template<class, class, container_class> friend class multivector_with_uniform_storage;
	};

	template<class CoefficientType, class Composition>
	class multivector_with_nonuniform_storage<CoefficientType, Composition, container_class::vector> :
		public concrete_multivector<CoefficientType, Composition, container_class::vector> {
	public:

		typedef CoefficientType      coefficient_type;
		typedef Composition          composition;

		static const container_class container = container_class::vector;

	private:

		typedef std::vector<dynamic_bitset_t>                                 basis_blades_collection;
		typedef std::vector<CoefficientType>                                  coefficients_collection;
		typedef std::array<::size_t, count_dynamic_packs<Composition>::value> strides_collection;

	private:

		template<class BasisBladesIterator, class CoefficientsIterator, class StridesIterator>
		class storage_base_iterator {
		public:

			typedef multivector_with_nonuniform_storage      multivector_type;

			typedef CoefficientType                          coefficient_type;

			typedef typename BasisBladesIterator::reference  basis_blade_reference;
			typedef typename CoefficientsIterator::reference coefficient_reference;
			typedef typename StridesIterator::reference      stride_reference;

		public:

			inline
			basis_blade_reference basis_blade() const {
				return *_basis_blades_itr;
			}

			inline
			coefficient_reference coefficient() const {
				return *_coefficients_itr;
			}

			inline
			stride_reference stride() const {
				return *_strides_itr;
			}

		public:

			inline
			void advance(const int n = 1) {
				std::advance(_basis_blades_itr, n);
				std::advance(_coefficients_itr, n);
			}

			inline
			void advance_basis_blade(const int n = 1) {
				std::advance(_basis_blades_itr, n);
			}

			inline
			void advance_coefficient(const int n = 1) {
				std::advance(_coefficients_itr, n);
			}

			inline
			void advance_stride(const int n = 1) {
				std::advance(_strides_itr, n);
			}

		public:

			inline
			storage_base_iterator(const storage_base_iterator &other) :
				_basis_blades_itr(other._basis_blades_itr), _coefficients_itr(other._coefficients_itr), _strides_itr(other._strides_itr) {};
		
		private:

			inline
			storage_base_iterator(const BasisBladesIterator &basis_blades_itr, const CoefficientsIterator &coefficients_itr, const StridesIterator &strides_itr) :
				_basis_blades_itr(basis_blades_itr), _coefficients_itr(coefficients_itr), _strides_itr(strides_itr) {};

		private:

			BasisBladesIterator  _basis_blades_itr;
			CoefficientsIterator _coefficients_itr;
			StridesIterator      _strides_itr;

			friend class multivector_with_nonuniform_storage;
		};

	public:

		typedef storage_base_iterator<typename basis_blades_collection::const_iterator, typename coefficients_collection::const_iterator, typename strides_collection::const_iterator> storage_const_iterator;
		typedef storage_base_iterator<typename basis_blades_collection::iterator, typename coefficients_collection::iterator, typename strides_collection::iterator>                   storage_iterator;
		typedef storage_base_iterator<std::back_insert_iterator<basis_blades_collection>, std::back_insert_iterator<coefficients_collection>, typename strides_collection::iterator>   storage_inserter;

		inline
		storage_const_iterator make_storage_const_iterator() const {
			return storage_const_iterator(_stored_basis_blades.cbegin(), _stored_coefficients.cbegin(), _dynamic_packs_stride.cbegin());
		}
	
		inline
		storage_iterator make_storage_iterator() {
			return storage_iterator(_stored_basis_blades.begin(), _stored_coefficients.begin(), _dynamic_packs_stride.begin());
		}
	
		inline
		storage_inserter make_storage_inserter() {
			return storage_inserter(std::back_inserter(_stored_basis_blades), std::back_inserter(_stored_coefficients), _dynamic_packs_stride);
		}
	
	protected:

		inline
		multivector_with_nonuniform_storage() :
			_dynamic_packs_stride(),
			_stored_basis_blades(),
			_stored_coefficients() {
			_dynamic_packs_stride.fill(0);
		}

		inline
		multivector_with_nonuniform_storage(const multivector_with_nonuniform_storage &other) :
			_dynamic_packs_stride(other._dynamic_packs_stride),
			_stored_basis_blades(other._stored_basis_blades),
			_stored_coefficients(other._stored_coefficients) {}

		template<class Expression>
		inline
		multivector_with_nonuniform_storage(const expression<Expression> &expression) {
			throw ga::illegal_call_exception();
		}

	private:

		basis_blades_collection _stored_basis_blades;
		coefficients_collection _stored_coefficients;
		strides_collection      _dynamic_packs_stride;

	private:

		template<class, class, container_class> friend class lazy_multivector;
		template<class, class, container_class> friend class multivector_with_nonuniform_storage;
		template<class, class, container_class> friend class multivector_with_uniform_storage;
	};

	template<class CoefficientType, class Composition>
	class multivector_with_uniform_storage<CoefficientType, Composition, container_class::none>  :
		public concrete_multivector<CoefficientType, Composition, container_class::none> {
	public:

		typedef CoefficientType      coefficient_type;
		typedef Composition          composition;

		static const container_class container = container_class::none;

	private:

		class storage_base_iterator {
		public:

			typedef multivector_with_uniform_storage                                               multivector_type;

			typedef CoefficientType                                                                coefficient_type;

			typedef const dynamic_bitset_t&                                                        basis_blade_reference;
			typedef typename add_lvalue_reference<typename add_const<CoefficientType>::type>::type coefficient_reference;
			typedef const ::size_t&                                                                stride_reference;

		public:

			inline
			basis_blade_reference basis_blade() const {
				throw ga::illegal_call_exception();
			}

			inline
			coefficient_reference coefficient() const {
				throw ga::illegal_call_exception();
			}

			inline
			stride_reference stride() const {
				throw ga::illegal_call_exception();
			}

		public:

			inline
			void advance(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_basis_blade(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_coefficient(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_stride(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

		public:

			inline
			storage_base_iterator(const storage_base_iterator &other) {
				// Nothing to be done.
			};
		
		private:

			inline
			storage_base_iterator() {
				// Nothing to be done.
			};

		private:

			friend class multivector_with_uniform_storage;
		};

	public:

		typedef storage_base_iterator storage_const_iterator;
		typedef storage_base_iterator storage_iterator;
		typedef storage_base_iterator storage_inserter;

		inline
		storage_const_iterator make_storage_const_iterator() const {
			return storage_const_iterator();
		}
	
		inline
		storage_iterator make_storage_iterator() const {
			return storage_iterator();
		}
	
		inline
		storage_inserter make_storage_inserter() const {
			return storage_inserter();
		}

	protected:

		inline
		multivector_with_uniform_storage() {
			// Nothing to be done.
		}

		inline
		multivector_with_uniform_storage(const multivector_with_uniform_storage &other) {
			// Nothing to be done.
		}

		template<class Expression>
		inline
		multivector_with_uniform_storage(const expression<Expression> &expression) {
			static_assert(is_base_of<multivector_with_uniform_storage, typename Expression::lazy_type>::value, "Invalid expression evaluation to compile-time defined type.");
			// Nothing to be done.
		}

	private:

		template<class, class, container_class> friend class lazy_multivector;
		template<class, class, container_class> friend class multivector_with_nonuniform_storage;
		template<class, class, container_class> friend class multivector_with_uniform_storage;
	};

	template<class CoefficientType, class Composition>
	class multivector_with_uniform_storage<CoefficientType, Composition, container_class::array>  :
		public concrete_multivector<CoefficientType, Composition, container_class::array> {
	public:

		typedef CoefficientType      coefficient_type;
		typedef Composition          composition;

		static const container_class container = container_class::array;

	private:

		typedef std::array<stored_component<CoefficientType>, count_stored_coefficients<Composition>::value> components_collection;
		typedef std::array<::size_t, count_dynamic_packs<Composition>::value>                                strides_collection;

	public:

		typedef typename add_reference<dynamic_bitset_t>::type basis_blade_reference;
		typedef typename add_reference<CoefficientType>::type  coefficient_reference;

	private:

		template<class ComponentsIterator, class StridesIterator, bool IsConstant>
		class storage_base_iterator {
		public:

			typedef multivector_with_uniform_storage    multivector_type;

			typedef CoefficientType                     coefficient_type;

			typedef typename if_c<IsConstant, typename ComponentsIterator::value_type::basis_blade_const_reference, typename ComponentsIterator::value_type::basis_blade_reference>::type basis_blade_reference;
			typedef typename if_c<IsConstant, typename ComponentsIterator::value_type::coefficient_const_reference, typename ComponentsIterator::value_type::coefficient_reference>::type coefficient_reference;
			typedef typename StridesIterator::reference stride_reference;

		public:

			inline
			basis_blade_reference basis_blade() const {
				return _components_itr->basis_blade();
			}

			inline
			coefficient_reference coefficient() const {
				return _components_itr->coefficient();
			}

			inline
			stride_reference stride() const {
				return *_strides_itr;
			}

		public:

			inline
			void advance(const int n = 1) {
				std::advance(_components_itr, n);
			}

			inline
			void advance_basis_blade(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_coefficient(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_stride(const int n = 1) {
				std::advance(_strides_itr, n);
			}

		public:

			inline
			storage_base_iterator(const storage_base_iterator &other) :
				_components_itr(other._components_itr), _strides_itr(other._strides_itr) {};
		
		private:

			inline
			storage_base_iterator(const ComponentsIterator &components_itr, const StridesIterator &strides_itr) :
				_components_itr(components_itr), _strides_itr(strides_itr) {};

		private:

			ComponentsIterator _components_itr;
			StridesIterator    _strides_itr;

			friend class multivector_with_uniform_storage;
		};

	public:

		typedef storage_base_iterator<typename components_collection::const_iterator, typename strides_collection::const_iterator, true> storage_const_iterator;
		typedef storage_base_iterator<typename components_collection::iterator, typename strides_collection::iterator, false>            storage_iterator;
		typedef storage_base_iterator<typename components_collection::iterator, typename strides_collection::iterator, false>            storage_inserter;

		inline
		storage_const_iterator make_storage_const_iterator() const {
			return storage_const_iterator(_stored_components.cbegin(), _dynamic_packs_stride.cbegin());
		}
	
		inline
		storage_iterator make_storage_iterator() {
			return storage_iterator(_stored_components.begin(), _dynamic_packs_stride.begin());
		}
	
		inline
		storage_inserter make_storage_inserter() {
			return storage_inserter(_stored_components.begin(), _dynamic_packs_stride.begin());
		}

	protected:

		inline
		multivector_with_uniform_storage() :
			_dynamic_packs_stride(),
			_stored_components() {
			_dynamic_packs_stride.fill(0);
		}

		inline
		multivector_with_uniform_storage(const multivector_with_uniform_storage &other) :
			_dynamic_packs_stride(other._dynamic_packs_stride),
			_stored_components(other._stored_components) {}

		template<class Expression>
		inline
		multivector_with_uniform_storage(const expression<Expression> &expression) {
			throw ga::illegal_call_exception();
		}

	private:

		components_collection _stored_components;
		strides_collection    _dynamic_packs_stride;

	private:

		template<class, class, container_class> friend class lazy_multivector;
		template<class, class, container_class> friend class multivector_with_nonuniform_storage;
		template<class, class, container_class> friend class multivector_with_uniform_storage;
	};

	template<class CoefficientType, class Composition>
	class multivector_with_uniform_storage<CoefficientType, Composition, container_class::vector>  :
		public concrete_multivector<CoefficientType, Composition, container_class::vector> {
	public:

		typedef CoefficientType      coefficient_type;
		typedef Composition          composition;

		static const container_class container = container_class::vector;

	private:

		typedef std::vector<stored_component<CoefficientType> >               components_collection;
		typedef std::array<::size_t, count_dynamic_packs<Composition>::value> strides_collection;

	private:

		template<class ComponentsIterator, class StridesIterator, bool IsConstant>
		class storage_base_iterator {
		public:

			typedef multivector_with_uniform_storage    multivector_type;

			typedef CoefficientType                     coefficient_type;

			typedef typename if_c<IsConstant, typename ComponentsIterator::value_type::basis_blade_const_reference, typename ComponentsIterator::value_type::basis_blade_reference>::type basis_blade_reference;
			typedef typename if_c<IsConstant, typename ComponentsIterator::value_type::coefficient_const_reference, typename ComponentsIterator::value_type::coefficient_reference>::type coefficient_reference;
			typedef typename StridesIterator::reference stride_reference;

		public:

			inline
			basis_blade_reference basis_blade() const {
				return _components_itr->basis_blade();
			}

			inline
			coefficient_reference coefficient() const {
				return _components_itr->coefficient();
			}

			inline
			stride_reference stride() const {
				return *_strides_itr;
			}

		public:

			inline
			void advance(const int n = 1) {
				std::advance(_components_itr, n);
			}

			inline
			void advance_basis_blade(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_coefficient(const int n = 0) const {
				throw ga::illegal_call_exception();
			}

			inline
			void advance_stride(const int n = 1) {
				std::advance(_strides_itr, n);
			}

		public:

			inline
			storage_base_iterator(const storage_base_iterator &other) :
				_components_itr(other._components_itr), _strides_itr(other._strides_itr) {};
		
		private:

			inline
			storage_base_iterator(const ComponentsIterator &components_itr, const StridesIterator &strides_itr) :
				_components_itr(components_itr), _strides_itr(strides_itr) {};

		private:

			ComponentsIterator _components_itr;
			StridesIterator    _strides_itr;

			friend class multivector_with_uniform_storage;
		};

	public:

		typedef storage_base_iterator<typename components_collection::const_iterator, typename strides_collection::const_iterator, true> storage_const_iterator;
		typedef storage_base_iterator<typename components_collection::iterator, typename strides_collection::iterator, false>            storage_iterator;
		typedef storage_base_iterator<std::back_insert_iterator<components_collection>, typename strides_collection::iterator, false>    storage_inserter;

		inline
		storage_const_iterator make_storage_const_iterator() const {
			return storage_const_iterator(_stored_components.cbegin(), _dynamic_packs_stride.cbegin());
		}
	
		inline
		storage_iterator make_storage_iterator() {
			return storage_iterator(_stored_components.begin(), _dynamic_packs_stride.begin());
		}
	
		inline
		storage_inserter make_storage_inserter() {
			return storage_inserter(std::back_inserter(_stored_components.begin()), _dynamic_packs_stride.begin());
		}

	protected:

		inline
		multivector_with_uniform_storage() :
			_dynamic_packs_stride(),
			_stored_components() {
			_dynamic_packs_stride.fill(0);
		}

		inline
		multivector_with_uniform_storage(const multivector_with_uniform_storage &other) :
			_dynamic_packs_stride(other._dynamic_packs_stride),
			_stored_components(other._stored_components) {}

		template<class Expression>
		inline
		multivector_with_uniform_storage(const expression<Expression> &expression) {
			throw ga::illegal_call_exception();
		}

	private:

		components_collection _stored_components;
		strides_collection    _dynamic_packs_stride;

	private:

		template<class, class, container_class> friend class lazy_multivector;
		template<class, class, container_class> friend class multivector_with_nonuniform_storage;
		template<class, class, container_class> friend class multivector_with_uniform_storage;
	};

	// Choose between uniform and non-uniform storage multivector superclass.
	template<class CoefficientType, class Composition, container_class Container, bool HasUniformStorage>
	struct make_concrete_multivector_superclass;

	template<class CoefficientType, class Composition, container_class Container>
	struct make_concrete_multivector_superclass<CoefficientType, Composition, Container, true> {

		typedef multivector_with_uniform_storage<CoefficientType, Composition, Container> type;
	};

	template<class CoefficientType, class Composition, container_class Container>
	struct make_concrete_multivector_superclass<CoefficientType, Composition, Container, false> {

		typedef multivector_with_nonuniform_storage<CoefficientType, Composition, Container> type;
	};

	// Choose between storage and lazy multivector superclasses.
	template<class CoefficientType, class Composition, container_class Container>
	struct make_multivector_superclass;

	template<class CoefficientType, class Expression, container_class Container>
	struct make_multivector_superclass {

		typedef lazy_multivector<CoefficientType, Expression, Container> type;
	};

	template<class CoefficientType, class Pack, class LeftSubtree, class RightSubtree, container_class Container>
	struct make_multivector_superclass<CoefficientType, tree<Pack, LeftSubtree, RightSubtree>, Container> :
		make_concrete_multivector_superclass<CoefficientType, tree<Pack, LeftSubtree, RightSubtree>, Container, has_uniform_storage<tree<Pack, LeftSubtree, RightSubtree> >::value> {};

	template<class CoefficientType, container_class Container>
	struct make_multivector_superclass<CoefficientType, empty_tree, Container> :
		make_concrete_multivector_superclass<CoefficientType, empty_tree, Container, has_uniform_storage<empty_tree>::value> {};

	// Creates a storage iterator by advancing a copy of the given head iterator to the given pack position.
	template<class Pack, class Composition>
	struct _go_to_impl_stored_basis_blade_index;

	template<class Composition>
	struct _go_to_impl_stored_basis_blades_count;
	
	template<class Pack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_basis_blades_count<tree<Pack, LeftSubtree, RightSubtree> > :
		plus<if_<and_<is_runtime<typename Pack::components::basis_blade>, is_compile_time<typename Pack::components::count> >, typename Pack::components::count, static_value<0> >, plus<_go_to_impl_stored_basis_blades_count<LeftSubtree>, _go_to_impl_stored_basis_blades_count<RightSubtree> > > {};

	template<>
	struct _go_to_impl_stored_basis_blades_count<empty_tree> :
		static_value<0> {};

	template<class Pack, class AnotherPack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_basis_blade_index_right :
		plus<if_<and_<is_runtime<typename AnotherPack::components::basis_blade>, is_compile_time<typename AnotherPack::components::count> >, typename AnotherPack::components::count, static_value<0> >, plus<_go_to_impl_stored_basis_blades_count<LeftSubtree>, _go_to_impl_stored_basis_blade_index<Pack, RightSubtree> > > {};

	template<class Pack, class AnotherPack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_basis_blade_index<Pack, tree<AnotherPack, LeftSubtree, RightSubtree> > :
		eval_if<less<Pack, AnotherPack>, _go_to_impl_stored_basis_blade_index<Pack, LeftSubtree>, _go_to_impl_stored_basis_blade_index_right<Pack, AnotherPack, LeftSubtree, RightSubtree> > {};

	template<class Pack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_basis_blade_index<Pack, tree<Pack, LeftSubtree, RightSubtree> > :
		static_value<0> {};

	template<class Pack>
	struct _go_to_impl_stored_basis_blade_index<Pack, empty_tree> :
		static_value<0> {};

	template<class Pack, class Composition>
	struct _go_to_impl_stored_coefficient_index;

	template<class Composition>
	struct _go_to_impl_stored_coefficients_count;
	
	template<class Pack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_coefficients_count<tree<Pack, LeftSubtree, RightSubtree> > :
		plus<if_<and_<is_runtime<typename Pack::components::coefficient>, is_compile_time<typename Pack::components::count> >, typename Pack::components::count, static_value<0> >, plus<_go_to_impl_stored_coefficients_count<LeftSubtree>, _go_to_impl_stored_coefficients_count<RightSubtree> > > {};

	template<>
	struct _go_to_impl_stored_coefficients_count<empty_tree> :
		static_value<0> {};

	template<class Pack, class AnotherPack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_coefficient_index_right :
		plus<if_<and_<is_runtime<typename AnotherPack::components::coefficient>, is_compile_time<typename AnotherPack::components::count> >, typename AnotherPack::components::count, static_value<0> >, plus<_go_to_impl_stored_coefficients_count<LeftSubtree>, _go_to_impl_stored_coefficient_index<Pack, RightSubtree> > > {};

	template<class Pack, class AnotherPack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_coefficient_index<Pack, tree<AnotherPack, LeftSubtree, RightSubtree> > :
		eval_if<less<Pack, AnotherPack>, _go_to_impl_stored_coefficient_index<Pack, LeftSubtree>, _go_to_impl_stored_coefficient_index_right<Pack, AnotherPack, LeftSubtree, RightSubtree> > {};

	template<class Pack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_coefficient_index<Pack, tree<Pack, LeftSubtree, RightSubtree> > :
		static_value<0> {};

	template<class Pack>
	struct _go_to_impl_stored_coefficient_index<Pack, empty_tree> :
		static_value<0> {};

	template<class Pack, class Composition>
	struct _go_to_impl_stored_stride_index;

	template<class Pack, class AnotherPack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_stride_index_right :
		plus<if_<is_runtime<typename AnotherPack::components::count>, static_value<1>, static_value<0> >, plus<count_dynamic_packs<LeftSubtree>, _go_to_impl_stored_stride_index<Pack, RightSubtree> > > {};

	template<class Pack, class AnotherPack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_stride_index<Pack, tree<AnotherPack, LeftSubtree, RightSubtree> > :
		eval_if<less<Pack, AnotherPack>, _go_to_impl_stored_stride_index<Pack, LeftSubtree>, _go_to_impl_stored_stride_index_right<Pack, AnotherPack, LeftSubtree, RightSubtree> > {};

	template<class Pack, class LeftSubtree, class RightSubtree>
	struct _go_to_impl_stored_stride_index<Pack, tree<Pack, LeftSubtree, RightSubtree> > :
		static_value<0> {};
	
	template<class Pack>
	struct _go_to_impl_stored_stride_index<Pack, empty_tree> :
		static_value<0> {};
	
	template<class Pack, class Composition, bool HasUniformStorage = has_uniform_storage<Composition>::value, bool HasDynamicPackCount = has_dynamic_pack_count<Composition>::value>
	struct _go_to_impl;

	template<class Pack, class Composition>
	struct _go_to_impl<Pack, Composition, true, true> {

		template<class StorageIterator>
		inline static
		StorageIterator eval(const StorageIterator &head) {
			StorageIterator result = head;
			int offset = 0;
			for (int index = 0; index < _go_to_impl_stored_stride_index<Pack, Composition>::value; ++index) {
				offset += result.stride();
				result.advance_stride();
			}
			result.advance(_go_to_impl_stored_coefficient_index<Pack, Composition>::value + offset);
			return result;
		}
	};

	template<class Pack, class Composition>
	struct _go_to_impl<Pack, Composition, true, false> {

		template<class StorageIterator>
		inline static
		StorageIterator eval(const StorageIterator &head) {
			StorageIterator result = head;
			result.advance(_go_to_impl_stored_coefficient_index<Pack, Composition>::value);
			return result;
		}
	};

	template<class Pack, class Composition>
	struct _go_to_impl<Pack, Composition, false, true> {

		template<class StorageIterator>
		inline static
		StorageIterator eval(const StorageIterator &head) {
			StorageIterator result = head;
			int offset = 0;
			for (int index = 0; index < _go_to_impl_stored_stride_index<Pack, Composition>::value; ++index) {
				offset += result.stride();
				result.advance_stride();
			}
			result.advance_basis_blade(_go_to_impl_stored_basis_blade_index<Pack, Composition>::value + offset);
			result.advance_coefficient(_go_to_impl_stored_coefficient_index<Pack, Composition>::value + offset);
			return result;
		}
	};

	template<class Pack, class Composition>
	struct _go_to_impl<Pack, Composition, false, false> {

		template<class StorageIterator>
		inline static
		StorageIterator eval(const StorageIterator &head) {
			StorageIterator result = head;
			result.advance_basis_blade(_go_to_impl_stored_basis_blade_index<Pack, Composition>::value);
			result.advance_coefficient(_go_to_impl_stored_coefficient_index<Pack, Composition>::value);
			return result;
		}
	};

	template<class Pack, class StorageIterator>
	inline
	StorageIterator go_to(const StorageIterator &head) {
		return _go_to_impl<Pack, typename StorageIterator::multivector_type::composition>::eval(head);
	}

	// Advance the given iterator one position forward according to the given pack configuration.
	template<class CurrentPackComponents, bool Execute>
	struct _advance_impl;

	template<class CurrentPackComponents>
	struct _advance_impl<CurrentPackComponents, false> {

		template<class StorageIterator>
		inline static
		void eval(const StorageIterator &itr) {
			// Nothing to be done.
		}
	};

	template<class Bitset, int Value>
	struct _advance_impl<single_basis_blade<basis_vectors<Bitset>, static_value<Value> >, true> {

		template<class StorageIterator>
		inline static
		void eval(const StorageIterator &itr) {
			// Nothing to be done.
		}
	};
	
	template<class Bitset>
	struct _advance_impl<single_basis_blade<basis_vectors<Bitset>, dynamic_value>, true> {

		template<class StorageIterator>
		inline static
		void eval(StorageIterator &itr) {
			itr.advance_coefficient();
		}
	};
	
	template<class SpaceBitset, class StepsBitset, int Value>
	struct _advance_impl<single_basis_blade<steps<SpaceBitset, StepsBitset>, static_value<Value> >, true> {

		template<class StorageIterator>
		inline static
		void eval(StorageIterator &itr) {
			itr.advance_basis_blade();
		}
	};
	
	template<class SpaceBitset, class StepsBitset>
	struct _advance_impl<single_basis_blade<steps<SpaceBitset, StepsBitset>, dynamic_value>, true> {

		template<class StorageIterator>
		inline static
		void eval(StorageIterator &itr) {
			itr.advance();
		}
	};
	
	template<class SpaceBitset, class StepsBitset, class Count>
	struct _advance_impl<multiple_basis_blades<steps<SpaceBitset, StepsBitset>, Count>, true> {

		template<class StorageIterator>
		inline static
		void eval(StorageIterator &itr) {
			itr.advance(itr.stride());
			itr.advance_stride();
		}
	};

	template<class CurrentPackComponents, bool Execute, class StorageIterator>
	inline
	void advance(StorageIterator &itr) {
		_advance_impl<CurrentPackComponents, Execute>::eval(itr);
	}

}

template<class CoefficientType, class Composition, container_class Container>
class multivector :
	public details::make_multivector_superclass<CoefficientType, Composition, Container>::type {
private:

	typedef typename details::make_multivector_superclass<CoefficientType, Composition, Container>::type super;

public:

	inline
	multivector() :
		super() {}

	inline
	multivector(const multivector &other) :
		super(other) {}

	template<class Expression>
	inline
	multivector(const details::expression<Expression> &expression) :
		super(expression.instance()) {}
};
