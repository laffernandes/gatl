/* Copyright (C) Leandro Augusto Frata Fernandes
 * 
 * author     : Fernandes, Leandro A. F.
 * e-mail     : laffernandes@ic.uff.br
 * home page  : http://www.ic.uff.br/~laffernandes
 * repository : https://github.com/laffernandes/gatl.git
 * 
 * This file is part of The Geometric Algebra Template Library (GATL).
 * 
 * GATL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GATL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GATL. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __GA_CORE_RULES_HPP__
#define __GA_CORE_RULES_HPP__

namespace ga {

    namespace detail {
    
        // An identity type trait used by get_rule_for<...> to avoid evaluating all rules in a given rules<...> list.
        template<typename Type>
        struct identity {
            using type = Type;
        };

        // A list of simplification rules that must be applied in the given order.
        template<typename... Rules>
        struct rules {
        };

        // Look for a rule attending the given arguments.
        template<typename Rules, typename... Arguments>
        struct get_rule_for;

        template<typename Rules, typename... Arguments>
        using get_rule_for_t = typename get_rule_for<Rules, Arguments...>::type;

        template<typename Rule, typename... NextRules, typename... Arguments>
        struct get_rule_for<rules<Rule, NextRules...>, Arguments...> {
            using type = typename std::conditional_t<
                Rule::template condition<Arguments...>::value,
                identity<Rule>,
                get_rule_for<rules<NextRules...>, Arguments...>
            >::type;
        };

        template<typename Rule, typename... Arguments>
        struct get_rule_for<rules<Rule>, Arguments...> {
            using type = std::conditional_t<
                Rule::template condition<Arguments...>::value,
                Rule,
                nullptr_t // It should be impossible to reach this case
            >;
        };

        // Look for a rule attending the given arguments and apply it, returning the resulting type.
        template<typename Rules, typename... Arguments>
        using apply_rule_for_t = typename get_rule_for_t<Rules, Arguments...>::template result<Arguments...>::type;
    }

}

#endif // __GA_CORE_RULES_HPP__
