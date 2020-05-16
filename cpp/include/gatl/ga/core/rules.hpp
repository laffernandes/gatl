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
    
        // A list of simplification rules that must be applied in the given order.
        template<typename... Rules>
        struct rules {
        };

        // Look for a rule attending the given arguments and apply it, returning the resulting type.
        template<typename Rules, typename... Arguments>
        struct apply_rule_for;

        template<typename Rules, typename... Arguments>
        using apply_rule_for_t = typename apply_rule_for<Rules, Arguments...>::type;

        template<typename Rule, typename... NextRules, typename... Arguments>
        struct apply_rule_for<rules<Rule, NextRules...>, Arguments...> {
            using type = typename std::conditional_t<
                !std::is_same_v<typename Rule::template result<Arguments...>::type, std::nullptr_t>,
                typename Rule::template result<Arguments...>,
                apply_rule_for<rules<NextRules...>, Arguments...>
            >::type;
        };

        template<typename Rule, typename... Arguments>
        struct apply_rule_for<rules<Rule>, Arguments...> {
            using type = std::conditional_t<
                !std::is_same_v<typename Rule::template result<Arguments...>::type, std::nullptr_t>,
                typename Rule::template result<Arguments...>::type,
                std::nullptr_t // It should be impossible to reach this case
            >;
        };

    }

}

#endif // __GA_CORE_RULES_HPP__
