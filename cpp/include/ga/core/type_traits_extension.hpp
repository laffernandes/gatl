/**
Copyright (C) 2018 Leandro Augusto Frata Fernandes

author     : Fernandes, Leandro A. F.
e-mail     : laffernandes@ic.uff.br
home page  : http://www.ic.uff.br/~laffernandes
repository : https://github.com/laffernandes/gatl.git

This file is part of The Geometric Algebra Template Library (GATL).

GATL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GATL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GATL. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GA_CORE_TYPE_TRAITS_EXTENSION_HPP__
#define __GA_CORE_TYPE_TRAITS_EXTENSION_HPP__

namespace ga {

	namespace detail {

		// Returns true if T and any element in Rest has the same type with the same const-volatile qualifications or false otherwise.
		template<typename T, typename... Rest>
		constexpr bool is_any_v = std::disjunction_v<std::bool_constant<std::is_same_v<T, Rest> >...>;

		// A set of indices.
		template<std::size_t... Indices>
		struct indices {
			using next = indices<Indices..., sizeof...(Indices)>;
		};

		// Helper structure to build a set of indices.
		template<std::size_t Size>
		struct build_indices {
			using type = typename build_indices<Size - 1>::type::next;
		};

		template<>
		struct build_indices<0> {
			using type = indices<>;
		};

		template<std::size_t Size>
		using build_indices_t = typename build_indices<Size>::type;

		// Helper function to convert a tuple into a list-initialization structure.
		template<typename Tuple, std::size_t... Indices>
		constexpr decltype(auto) _to_list_initialization(Tuple &&tuple, indices<Indices...>) noexcept {
			return { std::get<Indices>(std::move(tuple))... };
		}

		template<typename Tuple>
		constexpr decltype(auto) to_list_initialization(Tuple &&tuple) noexcept {
			return _to_list_initialization(std::move(tuple), build_indices_t<std::tuple_size_v<std::remove_cv_t<std::remove_reference_t<Tuple> > > >());
		}

	}

}

#endif // __GA_CORE_TYPE_TRAITS_EXTENSION_HPP__
