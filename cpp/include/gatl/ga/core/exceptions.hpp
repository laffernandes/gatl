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

#ifndef __GA_CORE_EXCEPTIONS_HPP__
#define __GA_CORE_EXCEPTIONS_HPP__

namespace ga {

    // This class defines the type of objects thrown as exceptions to report errors related to not implemented features.
    class not_implemented_error : public std::logic_error {
    public:

        explicit not_implemented_error(const std::string &what_arg) :
            std::logic_error(what_arg) {
        }

        explicit not_implemented_error(const char *what_arg) :
            std::logic_error(what_arg) {
        }
    };

}

#endif // __GA_CORE_EXCEPTIONS_HPP__
