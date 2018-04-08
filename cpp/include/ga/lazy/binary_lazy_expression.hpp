#ifndef __GA_LAZY_BINARY_LAZY_EXPRESSION_HPP__
#define __GA_LAZY_BINARY_LAZY_EXPRESSION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftExpressionType, class RightExpressionType, bool LeftCompileTimeDefined = LeftExpressionType::compile_time_defined(), bool RightCompileTimeDefined = RightExpressionType::compile_time_defined()>
			class binary_lazy_expression;

			template<class LeftExpressionType, class RightExpressionType>
			class binary_lazy_expression<LeftExpressionType, RightExpressionType, false, false> {
			public:

				typedef LeftExpressionType left_type;
				typedef RightExpressionType right_type;

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

				constexpr binary_lazy_expression() = default;
				constexpr binary_lazy_expression(binary_lazy_expression const &) = default;
				constexpr binary_lazy_expression(binary_lazy_expression &&) = default;

				constexpr binary_lazy_expression(left_type const &lhs, right_type const &rhs) :
					left_(lhs),
					right_(rhs) {
				}

			private:

				left_type const left_;
				right_type const right_;
			};

			template<class LeftExpressionType, class RightExpressionType>
			class binary_lazy_expression<LeftExpressionType, RightExpressionType, true, false> {
			public:

				typedef LeftExpressionType left_type;
				typedef RightExpressionType right_type;

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

				constexpr binary_lazy_expression() = default;
				constexpr binary_lazy_expression(binary_lazy_expression const &) = default;
				constexpr binary_lazy_expression(binary_lazy_expression &&) = default;

				constexpr binary_lazy_expression(left_type const &, right_type const &rhs) :
					right_(rhs) {
				}

			private:

				right_type const right_;
			};

			template<class LeftExpressionType, class RightExpressionType>
			class binary_lazy_expression<LeftExpressionType, RightExpressionType, false, true> {
			public:

				typedef LeftExpressionType left_type;
				typedef RightExpressionType right_type;

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

				constexpr binary_lazy_expression() = default;
				constexpr binary_lazy_expression(binary_lazy_expression const &) = default;
				constexpr binary_lazy_expression(binary_lazy_expression &&) = default;

				constexpr binary_lazy_expression(left_type const &lhs, right_type const &) :
					left_(lhs) {
				}

			private:

				left_type const left_;
			};

			template<class LeftExpressionType, class RightExpressionType>
			class binary_lazy_expression<LeftExpressionType, RightExpressionType, true, true> {
			public:

				typedef LeftExpressionType left_type;
				typedef RightExpressionType right_type;

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

				constexpr binary_lazy_expression() = default;
				constexpr binary_lazy_expression(binary_lazy_expression const &) = default;
				constexpr binary_lazy_expression(binary_lazy_expression &&) = default;

				constexpr binary_lazy_expression(left_type const &, right_type const &) {
				}
			};

		}

	}

}

#endif // __GA_LAZY_BINARY_LAZY_EXPRESSION_HPP__
