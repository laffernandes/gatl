namespace result_of {

	template<class CoefficientType>
	struct make_weighted_scalar {

		typedef multivector<
				CoefficientType,
				ga::details::tree<
					ga::details::pack<
						ga::details::single_basis_blade<
							ga::details::basis_vectors<typename ga::details::make_empty_bitset<>::type>,
							ga::details::dynamic_value
						>,
						ga::details::identity_operation
					>,
					ga::details::empty_tree,
					ga::details::empty_tree
				>
			> type;
	};

	template<int WeightValue, class CoefficientType = int>
	struct make_weighted_scalar_c {

		typedef typename boost::mpl::if_c<
				WeightValue != 0,
				multivector<
					CoefficientType,
					ga::details::tree<
						ga::details::pack<
							ga::details::single_basis_blade<
								ga::details::basis_vectors<typename ga::details::make_empty_bitset<>::type>,
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

template<class CoefficientType>
inline
typename result_of::make_weighted_scalar<CoefficientType>::type
make_weighted_scalar(const CoefficientType weight) {
	typename result_of::make_weighted_scalar<CoefficientType>::type result;
	result.make_storage_inserter().coefficient() = weight;
	return result;
}

template<int WeightValue, class CoefficientType = int>
inline
typename result_of::make_weighted_scalar_c<WeightValue, CoefficientType>::type
make_weighted_scalar_c() {
	return typename result_of::make_weighted_scalar_c<WeightValue, CoefficientType>::type();
}
