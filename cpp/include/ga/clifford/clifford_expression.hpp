#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_HPP__

namespace ga {

	namespace clifford {

		template<class ExpressionType>
		class clifford_expression {
		public:

			typedef ExpressionType expression_type;

			constexpr expression_type const & operator()() const {
				return *static_cast<expression_type const *>(this);
			}

			constexpr expression_type & operator()() {
				return *static_cast<expression_type *>(this);
			}

		protected:

			constexpr clifford_expression() = default;
			constexpr clifford_expression(clifford_expression const &) = default;
			constexpr clifford_expression(clifford_expression &&) = default;

			constexpr clifford_expression & operator=(clifford_expression const &) = default;
			constexpr clifford_expression & operator=(clifford_expression &&) = default;
		};

		template<class Type>
		struct is_clifford_expression {
			constexpr static bool value = false;
		};

		template<class ExpressionType>
		struct is_clifford_expression<clifford_expression<ExpressionType> > {
			constexpr static bool value = true;
		};

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_HPP__
