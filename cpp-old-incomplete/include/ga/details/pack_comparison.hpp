template<class Components1, class Operation1, class Components2, class Operation2>
struct less<ga::details::pack<Components1, Operation1>, ga::details::pack<Components2, Operation2> > :
	or_<less<typename Components1::steps, typename Components2::steps>, and_<not_<less<typename Components2::steps, typename Components1::steps> >, or_<less<typename Components1::basis_vectors, typename Components2::basis_vectors>, and_<not_<less<typename Components2::basis_vectors, typename Components1::basis_vectors> >, less<typename Components1::space, typename Components2::space> > > > > {};

template<class Components1, class Operation1, class Components2, class Operation2>
struct greater<ga::details::pack<Components1, Operation1>, ga::details::pack<Components2, Operation2> > :
	less<ga::details::pack<Components2, Operation2>, ga::details::pack<Components1, Operation1> > {};
