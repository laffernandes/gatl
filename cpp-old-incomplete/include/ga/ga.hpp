#ifndef GA_HPP
#define GA_HPP

#include <array>
#include <bitset>
#include <iterator>
#include <vector>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/integer_traits.hpp>
#include <boost/type_traits.hpp>

/*TODO Próximo passos:
  - A criação de basis vector deveria ser baseada em lazy, assim como a criação de escalares (multiplicação da variável pela base 1)
  - Resolver as contas que estão marcadas com "Parei aqui".
  - O uso de insert nas expressions é afetado pelo ir e vir do std::advance()?
  - Relacionar todas as operações unárias da gatl original e portar.
  - Relacionar todas as operações binárias não métricas da gatl original e portar.
  - Relacionar todas as operações binárias métricas da gatl original e portar.
  - Simplificar merge_assign_operations<> quando os argumentos são estáticos. Simplificar mais se a soma der zero.
  - Imprimir vetores conforme modelo de geometria.
  - Dominar o mundo.
*/

#define _GA_WRITE_MULTIVECTOR_STRUCTURE

#ifndef GA_MAX_NDIMS
	#define GA_MAX_NDIMS 31
#elif (GA_MAX_NDIMS) < 0
	#error GA_MAX_NDIMS must be a positive integer value.
#endif

namespace ga {

	namespace details {

		using namespace boost;
		using namespace boost::mpl;

		#if (GA_MAX_NDIMS) <= 8
			typedef unsigned char bitset_element_t;
		#elif (GA_MAX_NDIMS) <= 16
			typedef unsigned short bitset_element_t;
		#else
			typedef unsigned int bitset_element_t;
		#endif

		typedef std::bitset<GA_MAX_NDIMS> dynamic_bitset_t;

		#include <ga/details/time.hpp>

		#include <ga/details/static_bitset.hpp>
		#include <ga/details/value.hpp>
		
		#include <ga/details/value_functions.hpp>

		#include <ga/details/tree.hpp>
		//#include <ga/details/tree_transform_binary.hpp> //TODO Precisa?

		#include <ga/details/assign_operations.hpp>
		#include <ga/details/argument_tag.hpp>

		#include <ga/details/pack.hpp>

		#include <ga/details/identity_operation.hpp>

		#include <ga/details/composition_functions.hpp>

		#include <ga/details/apply_plus.hpp>

		#include <ga/details/distribute.hpp>

		#include <ga/details/assign_zero_operation.hpp>
		#include <ga/details/plus_assign_operation.hpp>

		#include <ga/details/apply_unary_minus.hpp>

		#include <ga/details/minus_assign_operation.hpp>

		#include <ga/details/storage.hpp>

		#include <ga/details/expression.hpp>
	}

	using ga::details::container_class;

	#include <ga/macros.hpp>

	#include <ga/exceptions.hpp>
	#include <ga/multivector.hpp>

	namespace details {

		#include <ga/details/binary_expression.hpp>
		#include <ga/details/unary_expression.hpp>

		#include <ga/details/organize.hpp>
		#include <ga/details/update_argument_tag.hpp>

		#include <ga/details/plus_expression.hpp>
		#include <ga/details/unary_minus_expression.hpp>
		#include <ga/details/minus_expression.hpp>

	}

	#include <ga/io.hpp>

	#include <ga/make_scalar.hpp>
	#include <ga/make_basis_vector.hpp>

	#include <ga/minus.hpp>
	#include <ga/plus.hpp>
	#include <ga/unary_minus.hpp>
	#include <ga/unary_plus.hpp>

	#include <ga/types.hpp>
	#include <ga/constants.hpp>

}

namespace boost {

	namespace mpl {

		#include <ga/details/static_bitset_comparison.hpp>
		#include <ga/details/value_comparison.hpp>
		#include <ga/details/pack_comparison.hpp>

	}

}

#endif
