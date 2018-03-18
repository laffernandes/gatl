#ifndef __GA_EXPRESSION_COPY_HPP__
#define __GA_EXPRESSION_COPY_HPP__

namespace ga {

	namespace detail {

		template<class InputItrType, class OutputItrType>
		inline void copy(InputItrType const &in, OutputItrType const &out) {
			out.element() = in.element();
			copy(next(in), next(out));
		}

		inline void copy(itr_end const &in, itr_end const &out) {
		}

		template<class InputElementType, class InputLeftSubtreeType, class InputRightSubtreeType, class OutputElementType, class OutputLeftSubtreeType, class OutputRightSubtreeType>
		inline void copy(expression<InputElementType, InputLeftSubtreeType, InputRightSubtreeType> const &in, expression<OutputElementType, OutputLeftSubtreeType, OutputRightSubtreeType> &out) {
			copy(obegin(in), obegin(out));
		}

	}

}

#endif // __GA_EXPRESSION_COPY_HPP__
