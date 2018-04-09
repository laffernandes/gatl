#ifndef __GA_LAZY_LAZY_EXPRESSION_HPP__
#define __GA_LAZY_LAZY_EXPRESSION_HPP__

namespace ga {

	namespace lazy {

		template<class ExpressionType>
		class lazy_expression {
		public:

			typedef ExpressionType expression_type;

			constexpr expression_type const & operator()() const {
				return *static_cast<expression_type const *>(this);
			}

			constexpr expression_type & operator()() {
				return *static_cast<expression_type *>(this);
			}

		protected:

			constexpr lazy_expression() = default;
			constexpr lazy_expression(lazy_expression const &) = default;
			constexpr lazy_expression(lazy_expression &&) = default;

			constexpr lazy_expression & operator=(lazy_expression const &) = default;
			constexpr lazy_expression & operator=(lazy_expression &&) = default;
		};

	}

	namespace common {

		template<class ExpressionType>
		struct is_lazy_expression<lazy::lazy_expression<ExpressionType> > {
			constexpr static bool value = true;
		};

	}

}

#endif // __GA_LAZY_LAZY_EXPRESSION_HPP__
