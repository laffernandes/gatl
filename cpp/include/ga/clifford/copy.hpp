#ifndef __GA_CLIFFORD_COPY_HPP__
#define __GA_CLIFFORD_COPY_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class InputElementType, class... InputOtherElementTypes, class OutputElementType, class... OutputOtherElementTypes, typename std::enable_if<eq<InputElementType, OutputElementType>::value, int>::type = 0>
			inline void copy(clifford_expression<InputElementType, InputOtherElementTypes...> const &in, clifford_expression<OutputElementType, OutputOtherElementTypes...> &out) {
				out.element() = in.element();
				copy(in.next(), out.next());
			}

			//TODO INSERIDO POR CAUSA DE BUG PÓS ATUALIZAÇÃO DO VISUAL STUDIO
			template<class InputElementType, class OutputElementType, class... OutputOtherElementTypes, typename std::enable_if<eq<InputElementType, OutputElementType>::value, int>::type = 0>
			inline void copy(clifford_expression<InputElementType> const &in, clifford_expression<OutputElementType, OutputOtherElementTypes...> &out) {
				out.element() = in.element();
				copy(in.next(), out.next());
			}

			//TODO INSERIDO POR CAUSA DE BUG PÓS ATUALIZAÇÃO DO VISUAL STUDIO
			template<class InputElementType, class OutputElementType, typename std::enable_if<eq<InputElementType, OutputElementType>::value, int>::type = 0>
			inline void copy(clifford_expression<InputElementType> const &in, clifford_expression<OutputElementType> &out) {
				out.element() = in.element();
			}

			template<class InputElementType, class... InputOtherElementTypes, class OutputElementType, class... OutputOtherElementTypes, typename std::enable_if<lt<OutputElementType, InputElementType>::value, int>::type = 0>
			inline void copy(clifford_expression<InputElementType, InputOtherElementTypes...> const &in, clifford_expression<OutputElementType, OutputOtherElementTypes...> &out) {
				out.element() = make_component(constant<0>(), out.element().basis_blade());
				copy(in, out.next());
			}

			//TODO INSERIDO POR CAUSA DE BUG PÓS ATUALIZAÇÃO DO VISUAL STUDIO
			template<class InputElementType, class OutputElementType, class... OutputOtherElementTypes, typename std::enable_if<lt<OutputElementType, InputElementType>::value, int>::type = 0>
			inline void copy(clifford_expression<InputElementType> const &in, clifford_expression<OutputElementType, OutputOtherElementTypes...> &out) {
				out.element() = make_component(constant<0>(), out.element().basis_blade());
				copy(in, out.next());
			}

			template<class OutputElementType, class... OutputOtherElementTypes>
			inline void copy(clifford_expression<> const &in, clifford_expression<OutputElementType, OutputOtherElementTypes...> &out) {
				out.element() = make_component(constant<0>(), out.element().basis_blade());
				copy(in, out.next());
			}

			inline void copy(clifford_expression<> const &, clifford_expression<> const &) {
			}

		}

	}

}

#endif // __GA_CLIFFORD_COPY_HPP__
