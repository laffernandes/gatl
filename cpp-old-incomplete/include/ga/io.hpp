namespace details {

	template<class Operation>
	struct _write_impl_operation;

	template<class Result >
	struct _write_impl_operation<assign_zero_operation<Result> > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			os << typename Arguments::coefficient_type(0);
		}
	};
	
	template<class Result, class PreviousAssignOperations, class Argument>
	struct _write_impl_operation<minus_assign_operation<Result, PreviousAssignOperations, Argument> > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			_write_impl_operation<PreviousAssignOperations>::eval(os, arguments);

			os << " - ";
			_write_impl<Argument>::eval(os, arguments);
		}
	};
	
	template<class Result, class PreviousAssignOperations, class Argument>
	struct _write_impl_operation<plus_assign_operation<Result, PreviousAssignOperations, Argument> > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			_write_impl_operation<PreviousAssignOperations>::eval(os, arguments);

			os << " + ";
			_write_impl<Argument>::eval(os, arguments);
		}
	};

	template<bool IsStatic>
	void _write_impl_basis_blade(std::ostream &os, const dynamic_bitset_t &bitset) {
		if (bitset.any()) {
			os << " * ";
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
			if (IsStatic) os << "[";
#endif
			for (::size_t index = 0; index < bitset.size(); ++index) {
				if (bitset.test(index)) os << "e" << index;
			}
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
			if (IsStatic) os << "]";
#endif
		}
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
		else {
			os << " * ";
			if (IsStatic) os << "[";
			os << "1";
			if (IsStatic) os << "]";
		}
#endif
	}

	template<bool IsStatic, class ValueType>
	void _write_impl_coefficient(std::ostream &os, const ValueType &value) {
		if (value < 0) {
			os << "(";
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
			if (IsStatic) os << "[";
#endif
			os << value;
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
			if (IsStatic) os << "]";
#endif
			os << ")";
		}
		else {
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
			if (IsStatic) os << "[";
#endif
			os << value;
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
			if (IsStatic) os << "]";
#endif
		}
	}

	template<class T>
	struct _write_impl;
	
	template<class CoefficientType, class Expression, container_class Container>
	struct _write_impl<multivector<CoefficientType, Expression, Container> > {

		inline static
		void eval(std::ostream &os, const multivector<CoefficientType, Expression, Container> &m) {
			_write_impl<typename Expression::composition>::eval(os, m);
		}
	};
	
	template<class CoefficientType, class Pack, class LeftSubtree, class RightSubtree, container_class Container>
	struct _write_impl<multivector<CoefficientType, tree<Pack, LeftSubtree, RightSubtree>, Container> > {

		inline static
		void eval(std::ostream &os, const multivector<CoefficientType, tree<Pack, LeftSubtree, RightSubtree>, Container> &m) {
			_write_impl<tree<Pack, LeftSubtree, RightSubtree> >::eval(os, m.make_storage_const_iterator());
		}
	};
	
	template<class CoefficientType, container_class Container>
	struct _write_impl<multivector<CoefficientType, empty_tree, Container> > {

		inline static
		void eval(std::ostream &os, const multivector<CoefficientType, empty_tree, Container> &m) {
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
			os << "[null multivector]";
#else
			os << CoefficientType(0);
#endif
		}
	};

	template<class Pack, class LeftSubtree, class RightSubtree>
	struct _write_impl<tree<Pack, LeftSubtree, RightSubtree> > {

		template<class ArgumentType>
		inline static
		void eval(std::ostream &os, ArgumentType &arg) {
			if (!is_same<LeftSubtree, empty_tree>::value) {
				_write_impl<LeftSubtree>::eval(os, arg);
				os << " + ";
			}

			_write_impl<Pack>::eval(os, arg);

			if (!is_same<RightSubtree, empty_tree>::value) {
				os << " + ";
				_write_impl<RightSubtree>::eval(os, arg);
			}
		};
	};

	template<>
	struct _write_impl<empty_tree> {

		template<class ArgumentType>
		inline static
		void eval(std::ostream &os, const ArgumentType &arg) {
			// Nothing do be done.
		}
	};

	template<class Bitset, int Value>
	struct _write_impl<pack<single_basis_blade<basis_vectors<Bitset>, static_value<Value> >, identity_operation> > {

		template<class StorageConstIterator>
		inline static
		void eval(std::ostream &os, const StorageConstIterator &itr) {
			_write_impl_coefficient<true>(os, typename StorageConstIterator::coefficient_type(Value));
			_write_impl_basis_blade<true>(os, Bitset::make_dynamic());
		}
	};

	template<class Bitset>
	struct _write_impl<pack<single_basis_blade<basis_vectors<Bitset>, dynamic_value>, identity_operation> > {

		template<class StorageConstIterator>
		inline static
		void eval(std::ostream &os, StorageConstIterator &itr) {
			_write_impl_coefficient<false>(os, itr.coefficient());
			_write_impl_basis_blade<true>(os, Bitset::make_dynamic());
			itr.advance_coefficient();
		}
	};

	template<class SpaceBitset, class StepsBitset, int Value>
	struct _write_impl<pack<single_basis_blade<steps<SpaceBitset, StepsBitset>, static_value<Value> >, identity_operation> > {

		template<class StorageConstIterator>
		inline static
		void eval(std::ostream &os, StorageConstIterator &itr) {
			_write_impl_coefficient<true>(os, typename StorageConstIterator::coefficient_type(Value));
			_write_impl_basis_blade<false>(os, itr.basis_blade());
			itr.advance_basis_blade();
		}
	};

	template<class SpaceBitset, class StepsBitset>
	struct _write_impl<pack<single_basis_blade<steps<SpaceBitset, StepsBitset>, dynamic_value>, identity_operation> > {

		template<class StorageConstIterator>
		inline static
		void eval(std::ostream &os, StorageConstIterator &itr) {
			_write_impl_coefficient<false>(os, itr.coefficient());
			_write_impl_basis_blade<false>(os, itr.basis_blade());
			itr.advance();
		}
	};

	template<class SpaceBitset, class StepsBitset, class Count>
	struct _write_impl<pack<multiple_basis_blades<steps<SpaceBitset, StepsBitset>, Count>, identity_operation> > {

		template<class StorageConstIterator>
		inline static
		void eval(std::ostream &os, StorageConstIterator &itr) {
			const ::size_t count = itr.stride();

			if (count > 0) {
				_write_impl_coefficient<false>(os, itr.coefficient());
				_write_impl_basis_blade<false>(os, itr.basis_blade());
				itr.advance();

				for (::size_t i = 2; i <= count; ++i) {
					os << " + ";
					_write_impl_coefficient<false>(os, itr.coefficient());
					_write_impl_basis_blade<false>(os, itr.basis_blade());
					itr.advance();
				}
			}

			itr.advance_stride();
		}
	};

	template<class Components, class InnerArgument>
	struct _write_impl<pack<Components, first_argument_tag<InnerArgument> > > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			os << "first<";
			_write_impl<InnerArgument>::eval(os, arguments._expression.first());
			os << ">";
		}
	};

	template<class Components, class InnerComponents>
	struct _write_impl<pack<Components, first_argument_tag<pack<InnerComponents, identity_operation> > > > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			os << "first<";
			_write_impl<pack<InnerComponents, identity_operation> >::eval(os, go_to<pack<InnerComponents, identity_operation> >(arguments._expression.first().make_storage_const_iterator()));
			os << ">";
		}
	};

	template<class Components, class InnerArgument>
	struct _write_impl<pack<Components, second_argument_tag<InnerArgument> > > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			os << "second<";
			_write_impl<InnerArgument>::eval(os, arguments._expression.second());
			os << ">";
		}
	};

	template<class Components, class InnerComponents>
	struct _write_impl<pack<Components, second_argument_tag<pack<InnerComponents, identity_operation> > > > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			os << "second<";
			_write_impl<pack<InnerComponents, identity_operation> >::eval(os, go_to<pack<InnerComponents, identity_operation> >(arguments._expression.second().make_storage_const_iterator()));
			os << ">";
		}
	};

	template<class Components, class InnerArgument>
	struct _write_impl<pack<Components, single_argument_tag<InnerArgument> > > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			os << "single<";
			_write_impl<InnerArgument>::eval(os, arguments._expression.single());
			os << ">";
		}
	};

	template<class Components, class InnerComponents>
	struct _write_impl<pack<Components, single_argument_tag<pack<InnerComponents, identity_operation> > > > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			os << "single<";
			_write_impl<pack<InnerComponents, identity_operation> >::eval(os, go_to<pack<InnerComponents, identity_operation> >(arguments._expression.single().make_storage_const_iterator()));
			os << ">";
		}
	};

	template<class Components, class Operation>
	struct _write_impl<pack<Components, Operation> > {

		template<class Arguments>
		inline static
		void eval(std::ostream &os, const Arguments &arguments) {
			os << "(";
			_write_impl_operation<Operation>::eval(os, arguments);
			os << ")";
		}
	};

	template<class Multivector>
	inline
	void write(std::ostream &os, const Multivector &m) {
		_write_impl<Multivector>::eval(os, m);
	}

}

template<class CoefficientType, class Composition, container_class Container>
inline
std::ostream& operator << (std::ostream &os, const multivector<CoefficientType, Composition, Container> &m) {
#ifdef _GA_WRITE_MULTIVECTOR_STRUCTURE
	details::write(os, m);
	if (m.is_lazy()) {
		os << "  ->  ";
		details::write(os, m.eval());
	}
#else
	details::write(os, m.eval());
#endif
	return os;
}
