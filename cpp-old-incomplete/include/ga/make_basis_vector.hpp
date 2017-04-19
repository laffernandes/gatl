namespace result_of {

	template<class CoefficientType = int>
	struct make_basis_vector {

		typedef multivector<
				CoefficientType,
				ga::details::tree<
					ga::details::pack<
						ga::details::single_basis_blade<
							ga::details::steps<typename ga::details::make_pseudoscalar_bitset<>::type, typename ga::details::set<ga::details::make_empty_bitset<>, 1>::type>,
							ga::details::static_value<1>
						>,
						ga::details::identity_operation
					>,
					ga::details::empty_tree,
					ga::details::empty_tree
				>
			> type;
	};

	template<::size_t Index, class CoefficientType = int>
	struct make_basis_vector_c {

		typedef multivector<
				CoefficientType,
				ga::details::tree<
					ga::details::pack<
						ga::details::single_basis_blade<
							ga::details::basis_vectors<typename ga::details::set<ga::details::make_empty_bitset<>, Index>::type>,
							ga::details::static_value<1>
						>,
						ga::details::identity_operation
					>,
					ga::details::empty_tree,
					ga::details::empty_tree
				>
			> type;
	};

	template<class CoefficientType, ::size_t ... Index>
	struct make_weighted_basis_vector;

	template<class CoefficientType>
	struct make_weighted_basis_vector<CoefficientType> {

		typedef multivector<
				CoefficientType,
				ga::details::tree<
					ga::details::pack<
						ga::details::single_basis_blade<
							ga::details::steps<typename ga::details::make_pseudoscalar_bitset<>::type, typename ga::details::set<ga::details::make_empty_bitset<>, 1>::type>,
							ga::details::dynamic_value
						>,
						ga::details::identity_operation
					>,
					ga::details::empty_tree,
					ga::details::empty_tree
				>
			> type;
	};

	template<class CoefficientType, ::size_t Index>
	struct make_weighted_basis_vector<CoefficientType, Index> {

		typedef multivector<
				CoefficientType,
				ga::details::tree<
					ga::details::pack<
						ga::details::single_basis_blade<
							ga::details::basis_vectors<typename ga::details::set<ga::details::make_empty_bitset<>, Index>::type>,
							ga::details::dynamic_value
						>,
						ga::details::identity_operation
					>,
					ga::details::empty_tree,
					ga::details::empty_tree
				>
			> type;
	};

	template<int WeightValue, ::size_t Index, class CoefficientType = int>
	struct make_weighted_basis_vector_c {

		typedef typename boost::mpl::if_c<
				WeightValue != 0,
				multivector<
					CoefficientType,
					ga::details::tree<
						ga::details::pack<
							ga::details::single_basis_blade<
								ga::details::basis_vectors<typename ga::details::set<ga::details::make_empty_bitset<>, Index>::type>,
								ga::details::static_value<WeightValue>
							>,
							ga::details::identity_operation
						>,
						ga::details::empty_tree,
						ga::details::empty_tree
					>
				>,
				multivector<CoefficientType, ga::details::empty_tree>
			>::type type;
	};

}

template<class CoefficientType = int>
inline
typename result_of::make_basis_vector<CoefficientType>::type
make_basis_vector(const ::size_t index) {
	typename result_of::make_basis_vector<CoefficientType>::type result;
	result.make_storage_inserter().basis_blade().set(index);
	return result;
}

template<::size_t Index, class CoefficientType = int>
inline
typename result_of::make_basis_vector_c<Index, CoefficientType>::type
make_basis_vector_c() {
	return typename result_of::make_basis_vector_c<Index, CoefficientType>::type();
}

template<class CoefficientType, ::size_t Index>
inline
typename result_of::make_weighted_basis_vector<CoefficientType, Index>::type
make_weighted_basis_vector(const CoefficientType weight) {
	typename result_of::make_weighted_basis_vector<CoefficientType, Index>::type result;
	result.make_storage_inserter().coefficient() = weight;
	return result;
}

template<class CoefficientType>
inline
typename result_of::make_weighted_basis_vector<CoefficientType>::type
make_weighted_basis_vector(const CoefficientType weight, const ::size_t index) {
	typename result_of::make_weighted_basis_vector<CoefficientType>::type result;
	auto itr = result.make_storage_inserter();
	itr.basis_blade().set(index);
	itr.coefficient() = weight;
	return result;
}

template<int WeightValue, ::size_t Index, class CoefficientType = int>
inline
typename result_of::make_weighted_basis_vector_c<WeightValue, Index, CoefficientType>::type
make_weighted_basis_vector_c() {
	return typename result_of::make_weighted_basis_vector_c<WeightValue, Index, CoefficientType>::type();
}
