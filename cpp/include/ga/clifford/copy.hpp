#ifndef __GA_CLIFFORD_COPY_HPP__
#define __GA_CLIFFORD_COPY_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class InputItrType, class OutputItrType, typename std::enable_if<eq<typename element_type<InputItrType>::type, typename element_type<OutputItrType>::type>::value, int>::type = 0>
			inline void copy(InputItrType const &in, OutputItrType &out) {
				element(out) = element(in);
				copy(next(in), next(out));
			}

			template<class InputItrType, class OutputItrType, typename std::enable_if<lt<typename element_type<OutputItrType>::type, typename element_type<InputItrType>::type>::value, int>::type = 0>
			inline void copy(InputItrType const &in, OutputItrType &out) {
				element(out) = make_component(constant<0>(), element(out).basis_blade());
				copy(in, next(out));
			}

			template<class OutputItrType>
			inline void copy(itr_end const &in, OutputItrType &out) {
				element(out) = make_component(constant<0>(), element(out).basis_blade());
				copy(in, next(out));
			}

			inline void copy(itr_end const &, itr_end const &) {
			}

		}

	}

}

#endif // __GA_CLIFFORD_COPY_HPP__
