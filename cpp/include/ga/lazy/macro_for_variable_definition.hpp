#ifndef __GA_LAZY_MACRO_FOR_VARIABLE_DEFINITION_HPP__
#define __GA_LAZY_MACRO_FOR_VARIABLE_DEFINITION_HPP__

#define GA_DEFINE_LAZY_VARK_FUNCTION(ID) \
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

GA_DEFINE_LAZY_VARK_FUNCTION(1)
GA_DEFINE_LAZY_VARK_FUNCTION(2)
GA_DEFINE_LAZY_VARK_FUNCTION(3)
GA_DEFINE_LAZY_VARK_FUNCTION(4)
GA_DEFINE_LAZY_VARK_FUNCTION(5)
GA_DEFINE_LAZY_VARK_FUNCTION(6)
GA_DEFINE_LAZY_VARK_FUNCTION(7)
GA_DEFINE_LAZY_VARK_FUNCTION(8)
GA_DEFINE_LAZY_VARK_FUNCTION(9)
GA_DEFINE_LAZY_VARK_FUNCTION(10)
GA_DEFINE_LAZY_VARK_FUNCTION(11)
GA_DEFINE_LAZY_VARK_FUNCTION(12)
GA_DEFINE_LAZY_VARK_FUNCTION(13)
GA_DEFINE_LAZY_VARK_FUNCTION(14)
GA_DEFINE_LAZY_VARK_FUNCTION(15)
GA_DEFINE_LAZY_VARK_FUNCTION(16)
GA_DEFINE_LAZY_VARK_FUNCTION(17)
GA_DEFINE_LAZY_VARK_FUNCTION(18)
GA_DEFINE_LAZY_VARK_FUNCTION(19)
GA_DEFINE_LAZY_VARK_FUNCTION(20)

#define GA_USE_LAZY_VARK_FUNCTIONS() \
	using ga::lazy::var1; \
	using ga::lazy::var2; \
	using ga::lazy::var3; \
	using ga::lazy::var4; \
	using ga::lazy::var5; \
	using ga::lazy::var6; \
	using ga::lazy::var7; \
	using ga::lazy::var8; \
	using ga::lazy::var9; \
	using ga::lazy::var10; \
	using ga::lazy::var11; \
	using ga::lazy::var12; \
	using ga::lazy::var13; \
	using ga::lazy::var14; \
	using ga::lazy::var15; \
	using ga::lazy::var16; \
	using ga::lazy::var17; \
	using ga::lazy::var18; \
	using ga::lazy::var19; \
	using ga::lazy::var20;

#endif // __GA_LAZY_MACRO_FOR_VARIABLE_DEFINITION_HPP__
