#ifndef __GA_LAZY_INSERTION_OPERATOR_HPP__
#define __GA_LAZY_INSERTION_OPERATOR_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftArgumentType, class RightArgumentType>
			inline void write_add(std::ostream &os, detail::add<LeftArgumentType, RightArgumentType> const &rhs) {
				os << rhs.left() << " + " << rhs.right();
			}

			template<class LeftArgumentType, class... RightArgumentTypes>
			inline void write_add(std::ostream &os, detail::add<LeftArgumentType, RightArgumentTypes...> const &rhs) {
				os << rhs.left() << " + ";
				detail::write_add(os, rhs.right());
			}

			template<class LeftArgumentType, class RightArgumentType>
			inline void write_mul(std::ostream &os, detail::mul<LeftArgumentType, RightArgumentType> const &rhs) {
				os << rhs.left() << " * " << rhs.right();
			}

			template<class LeftArgumentType, class... RightArgumentTypes>
			inline void write_mul(std::ostream &os, detail::mul<LeftArgumentType, RightArgumentTypes...> const &rhs) {
				os << rhs.left() << " * ";
				detail::write_mul(os, rhs.right());
			}

			template<id_t Id, id_t SubId, id_t... OtherSubIds>
			inline void write_variable_id(std::ostream &os) {
				os << static_cast<std::int32_t>(Id) << ".";
				write_variable_id<SubId, OtherSubIds...>(os);
			}

			template<id_t Id>
			inline void write_variable_id(std::ostream &os) {
				os << static_cast<std::int32_t>(Id);
			}
		}

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
			if (rhs.get() < 0) {
				os << "(" << rhs.get() << ")";
			}
			else {
				os << rhs.get();
			}
			return os;
		}

		template<class ValueType, id_t Id, id_t... SubIds>
		std::ostream & operator<<(std::ostream &os, variable<ValueType, Id, SubIds...> const &rhs) {
			os << "{" << rhs.get() << " | Id = <";
			detail::write_variable_id<Id, SubIds...>(os);
			os << ">}";
			return os;
		}

		template<class... ArgumentTypes>
		std::ostream & operator<<(std::ostream &os, detail::add<ArgumentTypes...> const &rhs) {
			os << "(";
			detail::write_add(os, rhs);
			os << ")";
			return os;
		}

		template<class... ArgumentTypes>
		std::ostream & operator<<(std::ostream &os, detail::mul<ArgumentTypes...> const &rhs) {
			os << "(";
			detail::write_mul(os, rhs);
			os << ")";
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
