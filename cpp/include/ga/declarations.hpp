namespace detail {

	// Compile-time tag (something::time type).
	struct compile_time_tag {};

	// Runtime tag (something::time type).
	struct runtime_tag {};

	// Time trait metafunction.
	template<class T>
	struct is_compile_time;

	// Time trait metafunction.
	template<class T>
	struct is_runttime;

	// Value and Bitset concept implementation for runtime defined values.
	struct dynamic_value;

	// Value concept implementation for compile-time defined integral value.
	template<int32_t Value>
	struct static_value;

	// The four possible containters for storing basis blades and coefficients: (i) none, for compile time-define structures; (ii) array, for std::array<>; (iii) vector, for std::vector<>, and (iv) map, for std:map<>.
	enum class container_class { none = 0, array, vector, map };

	// Analyses the composition of a ga::multivector<> structure and choose among the possible container classes.
	//   Composition must be a ga::detail::tree<> structure or a ga::detail::empty_tree structure (for concrete multivectors), or a expression (for lazy multivectors).
	template<class Composition>
	struct sugested_container_class;

	// The superclass of any expression.
	//   Expression must implement the UnaryExpression, the BinaryExpression, or the BinaryMetricExpression concepts.
	template<class Expression>
	class expression;

	// The superclass of binary expressions.
	//   BinaryExpression must be the template class implementing a binary expression.
	//   FirstArgument must be a ga::multivector<> structure.
	//   SecondArgument must be a ga::multivector<> structure.
	//   Composition must be a ga::detail::tree<> or ga::detail::empty_tree structure.
	template<template<class, class> class BinaryExpression, class FirstArgument, class SecondArgument, class Composition>
	class binary_expression;

	// The superclass of binary metric expressions.
	//   BinaryMetricExpression must be the template class implementing a binary expression.
	//   FirstArgument must be a ga::multivector<> structure.
	//   SecondArgument must be a ga::multivector<> structure.
	//   MetricArgument must be a ga::metric<> structure.
	//   Composition must be a ga::detail::tree<> or ga::detail::empty_tree structure.
	template<template<class, class, class> class BinaryMetricExpression, class FirstArgument, class SecondArgument, class MetricArgument, class Composition>
	class binary_metric_expression;

	// The superclass of unary expressions.
	//   UnaryExpression must be the template class implementing an unary expression.
	//   Argument must be a ga::multivector<> structure.
	//   Composition must be a ga::detail::tree<> or ga::detail::empty_tree structure.
	template<template<class> class UnaryExpression, class Argument, class Composition>
	class unary_expression;

	// Geometric product expression (A gp B).
	//   FirstArgument must be a ga::multivector<> structure.
	//   SecondArgument must be a ga::multivector<> structure.
	//   MetricArgument must be a ga::metric<> structure.
	template<class FirstArgument, class SecondArgument, class MetricArgument>
	class gp_expression;

	// Subcase of the geometric product expression take_grade(A gp B, k).
	//   FirstArgument must be a ga::multivector<> structure.
	//   SecondArgument must be a ga::multivector<> structure.
	//   MetricArgument must be a ga::metric<> structure.
	//   GradeSelection must be a grade_section<> metafunction.
	template<class FirstArgument, class SecondArgument, class MetricArgument, template<class, class> class GradeSelection>
	class graded_gp_expression;

	// Subcase of the expressions that change the sign of the components of a given multivector.
	//   Argument must be a ga::multivector<> structure.
	//   SignChange must be a sign_change<> metafunction.
	template<class Argument, template<class> class SignChange>
	class sign_change_expression;

	// Storage superclasses for the argument of an unary expression.
	//   Argument must be a ga::multivector<> structure.
	//   IsCompileTimeDefined must be true or false.
	template<class Argument, bool IsCompileTimeDefined = is_compile_time<typename Argument::composition>::value>
	class single_argument_storage_for_expression;

	// Storage superclasses for the first argument of a binary expression.
	//   Argument must be a ga::multivector<> structure.
	//   IsCompileTimeDefined must be true or false.
	template<class Argument, bool IsCompileTimeDefined = is_compile_time<typename Argument::composition>::value>
	class first_argument_storage_for_expression;

	// Storage superclasses for the second argument of a binary expression.
	//   Argument must be a ga::multivector<> structure.
	//   IsCompileTimeDefined must be true or false.
	template<class Argument, bool IsCompileTimeDefined = is_compile_time<typename Argument::composition>::value>
	class second_argument_storage_for_expression;

	// Storage superclasses for metric argument of an expression.
	//   Argument must be a ga::metric<> structure.
	//   IsCompileTimeDefined must be true or false.
	template<class Argument, bool IsCompileTimeDefined = is_compile_time<typename Argument::definition>::value>
	class metric_argument_storage_for_expression;

	// Tree structure for concrete multivector composition.
	//   Pack must be a ga::detail::pack<> structure.
	//   LeftSubtree must be a ga::detail::tree<> structure or a ga::detail::empty_tree structure.
	//   RightSubtree must be a ga::detail::tree<> structure or a ga::detail::empty_tree structure.
	template<class Pack, class LeftSubtree, class RightSubtree>
	struct tree;

	// Empty tree structure for concrete multivector composition.
	struct empty_tree;

	// Pack setup.
	//   Components may be a ga::detail::single_basis_blade<> or a ga::detail::multiple_basis_blades<> structure.
	//   Operation may be ga::detail::identity_operation or any implementation of the operation concept.
	template<class Components, class Operation>
	struct pack;

	// Components concept implementation for single basis blade.
	//   BasisBlade may be a ... /*TODO Definir o que pode ser colocar aqui*/
	//   Coefficient may be a ga::detail::static_value<> or a ga::detail::dynamic_value structure.
	template<class BasisBlade, class Coefficient>
	struct single_basis_blade;

	// Components concept implementation for multiple basis blades.
	//   Steps concept is implemented by ... /*TODO Definir o que pode ser colocar aqui*/
	//   Count concept is implemented by ga::detail::static_value<> and ga::detail::dynamic_value structure.
	template <class Steps, class Count>
	struct multiple_basis_blades;

	// Converts all the operations assigned to a given composition to identity operations.
	//   Composition must be a ga::detail::tree<> structure or a ga::detail::empty_tree structure (for concrete multivectors), or a expression (for lazy multivectors).
	template<class Composition>
	struct make_concrete;

}

// Multivector class.
//   CoefficientType must be some arithmetic type. If it is an integral type than it must be a signed one.
//   Composition must be a ga::detail::tree<> structure or a ga::detail::empty_tree structure (for concrete multivectors), or a expression (for lazy multivectors).
//   Container defines the data structure used to keep runtime data (steps, basis blades, and coefficients).
template<class CoefficientType, class Composition, ga::detail::container_class Container = ga::detail::sugested_container_class<Composition>::value>
class multivector;

// Metric class.
//   FactorType must be some arithmetic type. If it is an integral type than it must be a signed one.
//   Definition must be a ga::detail::metric_matrix<> or a ga::detail::metric_function<> structure.
template<class FactorType, class Definition>
class metric;
