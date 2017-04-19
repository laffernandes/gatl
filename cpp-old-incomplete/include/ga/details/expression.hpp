// The superclass of any expression.
//   Expression must umplement the UnaryExpression or the BinaryExpression concepts.
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

// The superclass of binary expressions.
//   BinaryExpression must be the template class implementing a binary expression.
//   FirstArgument must be a multivector<> structure.
//   SecondArgument must be a multivector<> structure.
//   Composition must be a tree<> or empty_tree structure.
template<template<class, class> class BinaryExpression, class FirstArgument, class SecondArgument, class Composition>
class binary_expression;

// The superclass of unary expressions.
//   UnaryExpression must be the template class implementing an unary expression.
//   Argument must be a multivector<> structure.
//   Composition must be a tree<> or empty_tree structure.
template<template<class> class UnaryExpression, class Argument, class Composition>
class unary_expression;

// This macro declares all variations of possible storage superclasses for the arguments of expressions.
#define _GA_DECLARE_ARGUMENT_STORAGE_FOR_EXPRESSION(NAME) \
	template<class Argument, bool IsCompileTimeDefined = is_compile_time<typename Argument::composition>::value> \
	class NAME##_argument_storage_for_expression; \
	\
	template<class CoefficientType, class Expression, container_class Container> \
	class NAME##_argument_storage_for_expression<multivector<CoefficientType, Expression, Container>, false> { \
	public: \
	\
		typedef multivector<CoefficientType, Expression, Container> NAME##_argument_type; \
		typedef NAME##_argument_type&                               NAME##_argument_reference; \
		typedef const NAME##_argument_type&                         NAME##_argument_const_reference; \
	\
	public: \
	\
		inline \
		NAME##_argument_const_reference NAME##() const { \
			return _##NAME##; \
		} \
	\
	protected: \
	\
		inline \
		NAME##_argument_storage_for_expression(NAME##_argument_const_reference argument) : \
			_##NAME##(argument) {} \
	\
	private: \
	\
		const NAME##_argument_type _##NAME##; \
	}; \
	\
	template<class CoefficientType, class Pack, class LeftSubtree, class RightSubtree, container_class Container> \
	class NAME##_argument_storage_for_expression<multivector<CoefficientType, tree<Pack, LeftSubtree, RightSubtree>, Container>, false> { \
	public: \
	\
		typedef multivector<CoefficientType, tree<Pack, LeftSubtree, RightSubtree>, Container> NAME##_argument_type; \
		typedef NAME##_argument_type&                                                          NAME##_argument_reference; \
		typedef const NAME##_argument_type&                                                    NAME##_argument_const_reference; \
	\
	public: \
	\
		inline \
		NAME##_argument_const_reference NAME##() const { \
			return _##NAME##; \
		} \
	\
	protected: \
	\
		inline \
		NAME##_argument_storage_for_expression(##NAME##_argument_const_reference argument) : \
			_##NAME##(argument) {} \
	\
	private: \
	\
		NAME##_argument_const_reference _##NAME##; \
	}; \
	\
	template<class CoefficientType, class Expression, container_class Container> \
	class NAME##_argument_storage_for_expression<multivector<CoefficientType, Expression, Container>, true> { \
	public: \
	\
		typedef multivector<CoefficientType, Expression, Container> NAME##_argument_type; \
		typedef NAME##_argument_type&                               NAME##_argument_reference; \
		typedef const NAME##_argument_type&                         NAME##_argument_const_reference; \
	\
	public: \
	\
		inline \
		NAME##_argument_type NAME##() const { \
			return NAME##_argument_type(); \
		} \
	\
	protected: \
	\
		inline \
		NAME##_argument_storage_for_expression(##NAME##_argument_const_reference argument) { \
		} \
	};
