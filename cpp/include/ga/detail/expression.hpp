template<class Expression>
class expression {
public:

	typedef Expression             expression_type;
	typedef expression_type&       expression_reference;
	typedef const expression_type& expression_const_reference;

public:

	inline
	expression_const_reference instance() const {
		return *static_cast<const expression_type*>(this);
	}

	inline
	expression_reference instance() {
		return *static_cast<expression_type*>(this);
	}

protected:

	inline
	expression() {
		// Nothing to be done.
	}
};
