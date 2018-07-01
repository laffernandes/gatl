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

#ifndef __GA_CORE_REAL_METRIC_SPACE_HPP__
#define __GA_CORE_REAL_METRIC_SPACE_HPP__

namespace ga {

	namespace detail {

		// Helper for metric space of real numbers (it is used with scalar expressions).
		struct real_metric_space : public metric_space<real_metric_space> {
		public:

			typedef real_metric_space metric_space_type;

			constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - GA_MAX_BASIS_VECTOR_INDEX));
			constexpr static ndims_t vector_space_dimensions = GA_MAX_BASIS_VECTOR_INDEX;

		public:

			template<typename BasisVectorsBitset>
			struct metric_factor {
				typedef detail::constant_value<1> type;
			};
		};

	}

	// Specialization of is_orthogonal_metric_space<MetricSpaceType>.
	template<>
	struct is_orthogonal_metric_space<detail::real_metric_space> :
		std::true_type {
	};

}

#endif // __GA_CORE_REAL_METRIC_SPACE_HPP__
