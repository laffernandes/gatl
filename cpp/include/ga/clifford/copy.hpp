#ifndef __GA_CLIFFORD_COPY_HPP__
#define __GA_CLIFFORD_COPY_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class InputElementType, class... InputOtherElementTypes, class OutputElementType, class... OutputOtherElementTypes, typename std::enable_if<eq<InputElementType, OutputElementType>::value, int>::type = 0>
			inline void copy(expression_list<InputElementType, InputOtherElementTypes...> const &in, expression_list<OutputElementType, OutputOtherElementTypes...> &out) {
				out.element() = in.element();
				copy(in.next(), out.next());
			}

			template<class InputElementType, class... InputOtherElementTypes, class OutputElementType, class... OutputOtherElementTypes, typename std::enable_if<lt<OutputElementType, InputElementType>::value, int>::type = 0>
			inline void copy(expression_list<InputElementType, InputOtherElementTypes...> const &in, expression_list<OutputElementType, OutputOtherElementTypes...> &out) {
				out.element() = make_component(constant<0>(), out.element().basis_blade());
				copy(in, out.next());
			}

			template<class OutputElementType, class... OutputOtherElementTypes>
			inline void copy(expression_list<> const &in, expression_list<OutputElementType, OutputOtherElementTypes...> &out) {
				out.element() = make_component(constant<0>(), out.element().basis_blade());
				copy(in, out.next());
			}

			inline void copy(expression_list<> const &, expression_list<> const &) {
			}

		}

	}

}

#endif // __GA_CLIFFORD_COPY_HPP__
