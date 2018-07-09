#include <fstream>

#include <ga.hpp>

#include <ga1e.hpp>
#include <ga1h.hpp>
#include <ga1m.hpp>
#include <ga1c.hpp>

#include <ga2e.hpp>
#include <ga2h.hpp>
#include <ga2m.hpp>
#include <ga2c.hpp>

#include <ga3e.hpp>
#include <ga3h.hpp>
#include <ga3m.hpp>
#include <ga3c.hpp>

#include <ga4e.hpp>
#include <ga4h.hpp>

#include <ga5e.hpp>

template<int RowIndex>
struct _multiplication_table_rows {

	template<int ColIndex>
	struct _cols {
		template<typename MetricSpaceType, typename Product>
		static void run(std::ostream &os, ga::metric_space<MetricSpaceType> const &mtr, Product const &prod) {
			_cols<ColIndex - 1>::run(os, mtr, prod);
			os << prod(ga::clifford_expression<ga::default_integral_t, ga::detail::component_t<ga::detail::constant_value<1>, ga::detail::constant_basis_blade<RowIndex> > >(), ga::clifford_expression<ga::default_integral_t, ga::detail::component_t<ga::detail::constant_value<1>, ga::detail::constant_basis_blade<ColIndex> > >(), mtr) << "\t";
		}
	};

	template<>
	struct _cols<-1> {
		template<typename MetricSpaceType, typename Product>
		static void run(std::ostream const &, ga::metric_space<MetricSpaceType> const &, Product const &) {
		}
	};

	template<typename MetricSpaceType, typename Product>
	static void run(std::ostream &os, ga::metric_space<MetricSpaceType> const &mtr, Product const &prod) {
		_multiplication_table_rows<RowIndex - 1>::run(os, mtr, prod);
		_cols<(1 << MetricSpaceType::vector_space_dimensions) - 1>::run(os, mtr, prod);
		os << std::endl;
	}
};

template<>
struct _multiplication_table_rows<-1> {
	template<typename MetricSpaceType, typename Product>
	static void run(std::ostream const &, ga::metric_space<MetricSpaceType> const &, Product const &prod) {
	}
};

template<typename MetricSpaceType, typename Product>
void multiplication_table(std::ostream &os, ga::metric_space<MetricSpaceType> const &mtr, Product const &prod) {
	_multiplication_table_rows<(1 << MetricSpaceType::vector_space_dimensions) - 1>::run(os, mtr, prod);
}

template<ga::ndims_t N, ga::bitset_t Rows, ga::bitset_t Cols>
struct _determinants_cols {
private:

	template<typename GeneralMetricSpaceType>
	static void print_bitset(std::ostream &os, ga::metric_space<GeneralMetricSpaceType> const &mtr, ga::bitset_t const bitset) {
		for (ga::ndims_t index = 0; index != GeneralMetricSpaceType::vector_space_dimensions; ++index) {
			if ((bitset & (ga::bitset_t(1) << index)) != ga::bitset_t(0)) {
				os << "1";
			}
			else {
				os << "0";
			}
		}
	}

public:

	template<typename GeneralMetricSpaceType>
	static void run(std::ostream &os, ga::metric_space<GeneralMetricSpaceType> const &mtr) {
		print_bitset(os, mtr, Rows);
		os << ", ";
		print_bitset(os, mtr, Cols);
		os << ", ";
		os << (Rows == Cols ? "1" : "0");
		os << ": " << ga::detail::determinant_t<GeneralMetricSpaceType, ga::detail::constant_bitset<Rows>, ga::detail::constant_bitset<Cols>, N>::eval<0, 0>(std::make_tuple()) << std::endl;
		_determinants_cols<N, Rows, ga::detail::next_combination(Cols, GeneralMetricSpaceType::basis_vectors)>::run(os, mtr);
	}
};

template<ga::ndims_t N, ga::bitset_t Rows>
struct _determinants_cols<N, Rows, ga::bitset_t(0)> {
	template<typename GeneralMetricSpaceType>
	static void run(std::ostream const &, ga::metric_space<GeneralMetricSpaceType> const &) {
	}
};

template<ga::ndims_t N, ga::bitset_t Rows>
struct _determinants_rows {
	template<typename GeneralMetricSpaceType>
	static void run(std::ostream &os, ga::metric_space<GeneralMetricSpaceType> const &mtr) {
		_determinants_cols<N, Rows, ga::detail::first_combination(N)>::run(os, mtr);
		_determinants_rows<N, ga::detail::next_combination(Rows, GeneralMetricSpaceType::basis_vectors)>::run(os, mtr);
	}
};

template<ga::ndims_t N>
struct _determinants_rows<N, ga::bitset_t(0)> {
	template<typename GeneralMetricSpaceType>
	static void run(std::ostream const &, ga::metric_space<GeneralMetricSpaceType> const &) {
	}
};

template<ga::ndims_t N>
struct _determinants_grade {
	template<typename GeneralMetricSpaceType>
	static void run(std::ostream &os, ga::metric_space<GeneralMetricSpaceType> const &mtr) {
		_determinants_grade<N - 1>::run(os, mtr);
		_determinants_rows<N, ga::detail::first_combination(N)>::run(os, mtr);
	}
};

template<>
struct _determinants_grade<0> {
	template<typename GeneralMetricSpaceType>
	static void run(std::ostream const &, ga::metric_space<GeneralMetricSpaceType> const &) {
	}
};

template<typename GeneralMetricSpaceType>
void determinants(std::ostream &os, ga::metric_space<GeneralMetricSpaceType> const &mtr) {
	_determinants_grade<GeneralMetricSpaceType::vector_space_dimensions>::run(os, mtr);
}

template<ga::ndims_t N>
class general_euclidean_metric_space : public ga::metric_space<general_euclidean_metric_space<N> > {
public:

	using metric_space_type = general_euclidean_metric_space;

	constexpr static ga::bitset_t basis_vectors = ga::bitset_t(ga::bitset_t(~0) >> (std::numeric_limits<ga::bitset_t>::digits - N));
	constexpr static ga::ndims_t vector_space_dimensions = N;

	template<typename RowIndex, typename ColIndex>
	struct entry {
		using type = ga::detail::if_else_t<ga::detail::equal_t<RowIndex, ColIndex>, ga::detail::constant_value<1>, ga::detail::constant_value<0> >;
	};
};

namespace ga {

	template<ga::ndims_t N>
	struct is_general_metric_space<general_euclidean_metric_space<N> > :
		std::true_type {
	};

}

int main() {
	constexpr ga::ndims_t N = 1;
	char filename[256];

	auto wrapper = [](auto const &lhs, auto const &rhs, auto const &mtr) -> decltype(auto) { return ga::gp(lhs, rhs, mtr); };

	/**
	{
		sprintf_s(filename, "euclidean_metric_space_%d.txt", N);
		std::ofstream out(filename, std::ofstream::out);
		multiplication_table(out, ga::euclidean_metric_space<N>(), wrapper);
	}
	/**/

	/**/
	{
		sprintf_s(filename, "general_euclidean_metric_space_%d.txt", N);
		std::ofstream out(filename, std::ofstream::out);
		multiplication_table(out, general_euclidean_metric_space<N>(), wrapper);
	}
	/**/

	/**
	{
		sprintf_s(filename, "determinant_%d.txt", N);
		std::ofstream out(filename, std::ofstream::out);
		determinants(out, general_euclidean_metric_space<N>() );
	}
	/**/

	return EXIT_SUCCESS;
}
