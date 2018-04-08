#ifndef __GA_LAZY_MACRO_FOR_VARIABLE_DEFINITION_HPP__
#define __GA_LAZY_MACRO_FOR_VARIABLE_DEFINITION_HPP__

#define LAZY_DEFINE_VARK_FUNCTION(ID) \
	namespace ga { \
		\
		namespace lazy { \
			\
			template<class ValueType> \
			constexpr variable<ID, ValueType> var##ID(ValueType const &arg) { \
				return variable<ID, ValueType>(arg); \
			} \
			\
		} \
		\
	}

#endif // __GA_LAZY_MACRO_FOR_VARIABLE_DEFINITION_HPP__
