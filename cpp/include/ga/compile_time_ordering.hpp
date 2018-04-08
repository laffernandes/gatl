#ifndef __GA_COMPILE_TIME_ORDERING_HPP__
#define __GA_COMPILE_TIME_ORDERING_HPP__

namespace ga {

	namespace common {

		namespace detail {
		
			template<class LeftType, class RightType>
			struct lt;

			template<class LeftType, class RightType>
			struct le final {
				constexpr static bool value = lt<LeftType, RightType>::value || !lt<RightType, LeftType>::value;
			};

			template<class LeftType, class RightType>
			struct eq final {
				constexpr static bool value = !lt<LeftType, RightType>::value && !lt<RightType, LeftType>::value;
			};

			template<class LeftType, class RightType>
			struct ne final {
				constexpr static bool value = lt<LeftType, RightType>::value || lt<RightType, LeftType>::value;
			};

			template<class LeftType, class RightType>
			struct gt final {
				constexpr static bool value = !lt<LeftType, RightType>::value && lt<RightType, LeftType>::value;
			};

			template<class LeftType, class RightType>
			struct ge final {
				constexpr static bool value = !lt<LeftType, RightType>::value;
			};

		}

	}

}

#endif // __GA_COMPILE_TIME_ORDERING_HPP__
