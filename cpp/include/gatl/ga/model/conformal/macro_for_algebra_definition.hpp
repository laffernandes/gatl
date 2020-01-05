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

#ifndef __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
#define __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_DEFINITION_HPP__

#define _GA_CONFORMAL_ALGEBRA_DEFINITION(SPACE, BASIS_VECTORS_NAMES, D, ...) \
    using space_t = conformal_metric_space<D>; \
    \
    static space_t const SPACE; \
    static std::array<std::string, D + 2> const BASIS_VECTORS_NAMES = { __VA_ARGS__ , "no", "ni" }; \
    \
    static auto const no = e(c<D + 1>); \
    static auto const ni = e(c<D + 2>); \
    \
    static auto const ep = (ni / c<2>) - no; \
    static auto const em = (ni / c<2>) + no; \
    \
    static auto const _0 = c<0>; \
    static auto const _1 = c<1>; \
    static auto const _2 = c<2>; \
    \
    static auto const I = pseudoscalar(SPACE); \
    static auto const Ie = rcont(I, op(no, ni, SPACE), SPACE);


#endif // __GA_MODEL_CONFORMAL_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
