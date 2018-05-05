#ifndef __GA_LAZY_ARGUMENTS_STORAGE_HPP__
#define __GA_LAZY_ARGUMENTS_STORAGE_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftArgumentType, class RightArgumentType, bool LeftCompileTimeDefined = LeftArgumentType::compile_time_defined(), bool RightCompileTimeDefined = RightArgumentType::compile_time_defined()>
			class arguments_storage;

			template<class LeftArgumentType, class RightArgumentType>
			class arguments_storage<LeftArgumentType, RightArgumentType, false, false> {
			public:

				typedef LeftArgumentType left_type;
				typedef RightArgumentType right_type;

				constexpr left_type const & left() const {
					return left_;
				}

				constexpr right_type const & right() const {
					return right_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr arguments_storage() = default;
				constexpr arguments_storage(arguments_storage const &) = default;
				constexpr arguments_storage(arguments_storage &&) = default;

				constexpr arguments_storage(left_type const &lhs, right_type const &rhs) :
					left_(lhs),
					right_(rhs) {
				}

				constexpr arguments_storage & operator=(arguments_storage const &) = default;
				constexpr arguments_storage & operator=(arguments_storage &&) = default;

			private:

				left_type left_;
				right_type right_;
			};

			template<class LeftArgumentType, class RightArgumentType>
			class arguments_storage<LeftArgumentType, RightArgumentType, true, false> {
			public:

				typedef LeftArgumentType left_type;
				typedef RightArgumentType right_type;

				constexpr left_type left() const {
					return left_type();
				}

				constexpr right_type const & right() const {
					return right_;
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr arguments_storage() = default;
				constexpr arguments_storage(arguments_storage const &) = default;
				constexpr arguments_storage(arguments_storage &&) = default;

				constexpr arguments_storage(left_type const &, right_type const &rhs) :
					right_(rhs) {
				}

				constexpr arguments_storage & operator=(arguments_storage const &) = default;
				constexpr arguments_storage & operator=(arguments_storage &&) = default;

			private:

				right_type right_;
			};

			template<class LeftArgumentType, class RightArgumentType>
			class arguments_storage<LeftArgumentType, RightArgumentType, false, true> {
			public:

				typedef LeftArgumentType left_type;
				typedef RightArgumentType right_type;

				constexpr left_type const & left() const {
					return left_;
				}

				constexpr right_type right() const {
					return right_type();
				}

				constexpr static bool compile_time_defined() {
					return false;
				}

			protected:

				constexpr arguments_storage() = default;
				constexpr arguments_storage(arguments_storage const &) = default;
				constexpr arguments_storage(arguments_storage &&) = default;

				constexpr arguments_storage(left_type const &lhs, right_type const &) :
					left_(lhs) {
				}

				constexpr arguments_storage & operator=(arguments_storage const &) = default;
				constexpr arguments_storage & operator=(arguments_storage &&) = default;

			private:

				left_type left_;
			};

			template<class LeftArgumentType, class RightArgumentType>
			class arguments_storage<LeftArgumentType, RightArgumentType, true, true> {
			public:

				typedef LeftArgumentType left_type;
				typedef RightArgumentType right_type;

				constexpr left_type left() const {
					return left_type();
				}

				constexpr right_type right() const {
					return right_type();
				}

				constexpr static bool compile_time_defined() {
					return true;
				}

			protected:

				constexpr arguments_storage() = default;
				constexpr arguments_storage(arguments_storage const &) = default;
				constexpr arguments_storage(arguments_storage &&) = default;

				constexpr arguments_storage(left_type const &, right_type const &) {
				}

				constexpr arguments_storage & operator=(arguments_storage const &) = default;
				constexpr arguments_storage & operator=(arguments_storage &&) = default;
			};

		}

	}

}

#endif // __GA_LAZY_ARGUMENTS_STORAGE_HPP__
