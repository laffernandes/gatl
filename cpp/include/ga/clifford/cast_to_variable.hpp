#ifndef __GA_CLIFFORD_CAST_TO_VARIABLE_HPP__
#define __GA_CLIFFORD_CAST_TO_VARIABLE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<id_t ExtraId, id_t Id, id_t... SubIds, class CoefficientType, class BasisBladeType>
			constexpr decltype(auto) cast_element_to_var(component<CoefficientType, BasisBladeType> const &arg) {
				return make_component(var<Id, SubIds..., ExtraId>(arg.coefficient()), arg.basis_blade());
			}

			template<id_t ExtraId, id_t Id, id_t... SubIds, class CoefficientType, default_bitset_t PossibleGrades>
			constexpr decltype(auto) cast_element_to_var(components<CoefficientType, PossibleGrades> const &arg) = delete; //TODO lazy

			template<id_t ExtraId, id_t Id, id_t... SubIds, class ItrType>
			constexpr decltype(auto) cast_clifford_to_var(ItrType const &itr) {
				return insert(cast_clifford_to_var<ExtraId + 1, Id, SubIds...>(next(itr)), cast_element_to_var<ExtraId, Id, SubIds...>(itr.element()));
			}

			template<id_t ExtraId, id_t Id, id_t... SubIds>
			constexpr decltype(auto) cast_clifford_to_var(itr_end const &) {
				return empty_clifford_expression();
			}

		}

	}

	namespace lazy {

		template<id_t Id, id_t... SubIds, class ExpressionType>
		constexpr decltype(auto) var(clifford::clifford_expression<ExpressionType> const &arg) {
			return clifford::detail::cast_clifford_to_var<1, Id, SubIds...>(clifford::detail::begin(arg));
		}

	}

}

#endif // __GA_CLIFFORD_CAST_TO_VARIABLE_HPP__
