#ifndef __GA_GRADE__
#define __GA_GRADE__

namespace ga {

	enum grade_interpretation_t { UNDETERMINED_GRADE = -2, MIXED_GRADE = -1, SINGLE_GRADE = 0 };

	template<>
	class grade_result<grade_t> {
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

		constexpr value_type value() const {
			return value_;
		}
	
		constexpr grade_interpretation_t flag() const {
			return value_ >= 0 ? SINGLE_GRADE : (grade_interpretation_t)value_;
		}

	private:

		grade_t const value_;
	};

	template<default_integral_t Value>
	class grade_result<detail::cvalue<Value> > {
	public:

		typedef detail::cvalue<Value> value_type;

		constexpr grade_result(grade_result const &) = default;
		constexpr grade_result(grade_result &&) = default;

		constexpr operator grade_t() const {
			return static_cast<grade_t>(Value);
		}

		constexpr value_type value() const {
			return value_type();
		}

		constexpr grade_interpretation_t flag() const {
			return Value >= 0 ? SINGLE_GRADE : (grade_interpretation_t)Value;
		}
	};

	namespace detail {

		struct _deduce_grade_itr;
		struct _deduce_grade_end;

		template<class ItrType, class ToleranceType>
		constexpr decltype(auto) deduce_grade(ItrType const &arg, ToleranceType const &tol) {
			return std::conditional<!is_end<ItrType>::value, _deduce_grade_itr, _deduce_grade_end>::type::bind(arg, tol);
		}

		struct _deduce_grade_itr {
		private:

			template<class LeftValueType, class RightValueType>
			constexpr static grade_result<grade_t> look_both(grade_result<LeftValueType> const &lhs, grade_result<RightValueType> const &rhs) {
				return grade_result<grade_t>(static_cast<grade_t>(lhs.value()) == static_cast<grade_t>(rhs.value()) ? lhs.value() : -1);
			}

			template<default_integral_t LeftValue, default_integral_t RightValue>
			constexpr static decltype(auto) look_both(grade_result<cvalue<LeftValue> > const &, grade_result<cvalue<RightValue> > const &) {
				return grade_result<cvalue<LeftValue == RightValue ? LeftValue : -1> >();
			}

			template<class LeftValueType, class RightValueType>
			constexpr static decltype(auto) look_right(grade_result<LeftValueType> const &lhs, grade_result<RightValueType> const &rhs) {
				return look_both(lhs, rhs);
			}

			template<class LeftValueType>
			constexpr static grade_result<LeftValueType> look_right(grade_result<LeftValueType> const &lhs, grade_result<cvalue<-2> > const &) {
				return lhs;
			}

			template<class LeftValueType>
			constexpr static decltype(auto) look_right(grade_result<LeftValueType> const &, grade_result<cvalue<-1> > const &) {
				return grade_result<cvalue<-1> >();
			}

			template<class LeftValueType, class RightElementType, class ToleranceType>
			constexpr static decltype(auto) look_left(grade_result<LeftValueType> const &lhs, RightElementType const &rhs, ToleranceType const &tol) {
				return look_right(lhs, deduce_grade_element(rhs, tol));
			}

			template<class RightElementType, class ToleranceType>
			constexpr static decltype(auto) look_left(grade_result<cvalue<-2> > const &, RightElementType const &rhs, ToleranceType const &tol) {
				return deduce_grade_element(rhs, tol);
			}

			template<class RightElementType, class ToleranceType>
			constexpr static decltype(auto) look_left(grade_result<cvalue<-1> > const &, RightElementType const &, ToleranceType const &) {
				return grade_result<cvalue<-1> >();
			}

		public:

			template<class ItrType, class ToleranceType>
			constexpr static decltype(auto) bind(ItrType const &arg, ToleranceType const &tol) {
				return look_left(deduce_grade(next(arg), tol), arg.element(), tol);
			}
		};

		struct _deduce_grade_end {
			template<class ItrType, class ToleranceType>
			constexpr static decltype(auto) bind(ItrType const &, ToleranceType const &) {
				return grade_result<cvalue<-2> >();
			}
		};

	}

	template<class Type, class ToleranceType = typename detail::native_coefficient_type<Type>::type>
	constexpr decltype(auto) grade(Type const &arg, ToleranceType const &tol = default_tolerance<ToleranceType>()) {
		return detail::deduce_grade(detail::begin(eval(arg)));
	}

}

#endif // __GA_GRADE__
