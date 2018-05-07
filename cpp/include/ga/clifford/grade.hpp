#ifndef __GA_CLIFFORD_GRADE__
#define __GA_CLIFFORD_GRADE__

namespace ga {

	namespace clifford {

		enum grade_interpretation_t { UNDETERMINED_GRADE = -2, MIXED_GRADE = -1, SINGLE_GRADE = 0 };

		template<>
		class grade_result<grade_t> final {
		public:

			typedef grade_t value_type;

			constexpr grade_result(grade_result const &) = default;
			constexpr grade_result(grade_result &&) = default;

			constexpr grade_result(grade_t const value) :
				value_(value) {
			}

			constexpr operator grade_t() const {
				return value_;
			}

			constexpr value_type get() const {
				return value_;
			}
	
			constexpr grade_interpretation_t flag() const {
				return value_ >= 0 ? SINGLE_GRADE : (grade_interpretation_t)value_;
			}

		private:

			grade_t const value_;
		};

		template<default_integral_t Value>
		class grade_result<constant<Value> > final {
		public:

			typedef constant<Value> value_type;

			constexpr grade_result(grade_result const &) = default;
			constexpr grade_result(grade_result &&) = default;

			constexpr operator grade_t() const {
				return static_cast<grade_t>(Value);
			}

			constexpr value_type get() const {
				return value_type();
			}

			constexpr grade_interpretation_t flag() const {
				return Value >= 0 ? SINGLE_GRADE : (grade_interpretation_t)Value;
			}
		};

		namespace detail {

			template<class LeftValueType, class RightValueType>
			constexpr static grade_result<grade_t> deduce_grade_look_both(grade_result<LeftValueType> const &lhs, grade_result<RightValueType> const &rhs) {
				return grade_result<grade_t>(static_cast<grade_t>(lhs.get()) == static_cast<grade_t>(rhs.get()) ? lhs.get() : -1);
			}

			template<default_integral_t LeftValue, default_integral_t RightValue>
			constexpr static decltype(auto) deduce_grade_look_both(grade_result<constant<LeftValue> > const &, grade_result<constant<RightValue> > const &) {
				return grade_result<constant<LeftValue == RightValue ? LeftValue : -1> >();
			}

			template<class LeftValueType, class RightValueType>
			constexpr static decltype(auto) deduce_grade_look_right(grade_result<LeftValueType> const &lhs, grade_result<RightValueType> const &rhs) {
				return deduce_grade_look_both(lhs, rhs);
			}

			template<class LeftValueType>
			constexpr static grade_result<LeftValueType> deduce_grade_look_right(grade_result<LeftValueType> const &lhs, grade_result<constant<-2> > const &) {
				return lhs;
			}

			template<class LeftValueType>
			constexpr static grade_result<constant<-1> > deduce_grade_look_right(grade_result<LeftValueType> const &, grade_result<constant<-1> > const &) {
				return grade_result<constant<-1> >();
			}

			template<class LeftValueType, class RightElementType, class ToleranceType>
			constexpr static decltype(auto) deduce_grade_look_left(grade_result<LeftValueType> const &lhs, RightElementType const &rhs, ToleranceType const &tol) {
				return deduce_grade_look_right(lhs, deduce_grade_element(rhs, tol));
			}

			template<class RightElementType, class ToleranceType>
			constexpr static decltype(auto) deduce_grade_look_left(grade_result<constant<-2> > const &, RightElementType const &rhs, ToleranceType const &tol) {
				return deduce_grade_element(rhs, tol);
			}

			template<class RightElementType, class ToleranceType>
			constexpr static grade_result<constant<-1> > deduce_grade_look_left(grade_result<constant<-1> > const &, RightElementType const &, ToleranceType const &) {
				return grade_result<constant<-1> >();
			}

			template<class ElementType, class... OtherElementTypes, class ToleranceType>
			constexpr decltype(auto) deduce_grade(clifford_expression<ElementType, OtherElementTypes...> const &arg, ToleranceType const &tol) {
				return deduce_grade_look_left(deduce_grade(arg.next(), tol), arg.element(), tol);
			}

			template<class ToleranceType>
			constexpr grade_result<constant<-2> > deduce_grade(clifford_expression<> const &, ToleranceType const &) {
				return grade_result<constant<-2> >();
			}

		}

		template<class Type, class ToleranceType = typename detail::common_value_type<Type>::type>
		constexpr decltype(auto) grade(Type const &arg, ToleranceType const &tol = default_tolerance<ToleranceType>()) {
			return detail::deduce_grade(detail::begin(eval(arg)), tol);
		}

	}

}

#endif // __GA_CLIFFORD_GRADE__
