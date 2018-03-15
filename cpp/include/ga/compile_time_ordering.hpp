#ifndef __GA_COMPILE_TIME_ORDERING_HPP__
#define __GA_COMPILE_TIME_ORDERING_HPP__

namespace ga {

	namespace detail {
		
		template<class LeftType, class RightType>
		struct lt;

		template<class LeftType, class RightType>
		struct le {
			constexpr static bool value = lt<LeftType, RightType>::value || !lt<RightType, LeftType>::value;
		};

		template<class LeftType, class RightType>
		struct eq {
			constexpr static bool value = !lt<LeftType, RightType>::value && !lt<RightType, LeftType>::value;
		};

		template<class LeftType, class RightType>
		struct ne {
			constexpr static bool value = lt<LeftType, RightType>::value || lt<RightType, LeftType>::value;
		};

		template<class LeftType, class RightType>
		struct gt {
			constexpr static bool value = !lt<LeftType, RightType>::value && lt<RightType, LeftType>::value;
		};

		template<class LeftType, class RightType>
		struct ge {
			constexpr static bool value = !lt<LeftType, RightType>::value;
		};

	}

}

#endif // __GA_COMPILE_TIME_ORDERING_HPP__
