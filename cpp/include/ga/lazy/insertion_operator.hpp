#ifndef __GA_LAZY_INSERTION_OPERATOR_HPP__
#define __GA_LAZY_INSERTION_OPERATOR_HPP__

namespace ga {

	namespace lazy {

		template<class ExpressionType>
		std::ostream & operator<<(std::ostream &os, lazy_expression<ExpressionType> const &rhs) {
			os << rhs();
			return os;
		}

		template<default_integral_t Value>
		std::ostream & operator<<(std::ostream &os, constant<Value> const &) {
			os << "<" << Value << ">";
			return os;
		}

		template<class ValueType>
		std::ostream & operator<<(std::ostream &os, value<ValueType> const &rhs) {
			os << rhs.get();
			return os;
		}

		template<id_t Id, class ValueType>
		std::ostream & operator<<(std::ostream &os, variable<Id, ValueType> const &rhs) {
			os << "{" << rhs.get() << " | Id = <" << static_cast<std::int32_t>(Id) << ">}";
			return os;
		}

		template<class LeftExpressionType, class RightExpressionType>
		std::ostream & operator<<(std::ostream &os, detail::add<LeftExpressionType, RightExpressionType> const &rhs) {
			os << "(" << rhs.left() << " + " << rhs.right() << ")";
			return os;
		}

		template<class LeftExpressionType, class RightExpressionType>
		std::ostream & operator<<(std::ostream &os, detail::mul<LeftExpressionType, RightExpressionType> const &rhs) {
			os << "(" << rhs.left() << " * " << rhs.right() << ")";
			return os;
		}

		template<class LeftExpressionType, class RightExpressionType>
		std::ostream & operator<<(std::ostream &os, detail::power<LeftExpressionType, RightExpressionType> const &rhs) {
			os << "pow(" << rhs.left() << ", " << rhs.right() << ")";
			return os;
		}

	}

}

#endif // __GA_LAZY_INSERTION_OPERATOR_HPP__
