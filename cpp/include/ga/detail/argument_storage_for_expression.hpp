#define _GA_DEFINE_ARGUMENT_STORAGE_FOR_EXPRESSION(NAME) \
	template<class CoefficientType, class Expression, container_class Container> \
	class NAME##_argument_storage_for_expression<multivector<CoefficientType, Expression, Container>, false> { \
	public: \
	\
		typedef multivector<CoefficientType, Expression, Container> NAME##_argument_type; \
		typedef NAME##_argument_type&                               NAME##_argument_reference; \
		typedef const NAME##_argument_type&                         NAME##_argument_const_reference; \
	\
	public: \
	\
		inline \
		NAME##_argument_const_reference NAME##() const { \
			return _##NAME##; \
		} \
	\
	protected: \
	\
		inline \
		NAME##_argument_storage_for_expression(NAME##_argument_type&& argument) : \
			_##NAME##(argument) {} \
	\
	private: \
	\
		const NAME##_argument_type _##NAME##; \
	}; \
	\
	template<class CoefficientType, class Pack, class LeftSubtree, class RightSubtree, container_class Container> \
	class NAME##_argument_storage_for_expression<multivector<CoefficientType, tree<Pack, LeftSubtree, RightSubtree>, Container>, false> { \
	public: \
	\
		typedef multivector<CoefficientType, tree<Pack, LeftSubtree, RightSubtree>, Container> NAME##_argument_type; \
		typedef NAME##_argument_type&                                                          NAME##_argument_reference; \
		typedef const NAME##_argument_type&                                                    NAME##_argument_const_reference; \
	\
	public: \
	\
		inline \
		NAME##_argument_const_reference NAME##() const { \
			return _##NAME##; \
		} \
	\
	protected: \
	\
		inline \
		NAME##_argument_storage_for_expression(NAME##_argument_type&& argument) : \
			_##NAME##(argument) {} \
	\
	private: \
	\
		NAME##_argument_const_reference _##NAME##; \
	}; \
	\
	template<class CoefficientType, class Expression, container_class Container> \
	class NAME##_argument_storage_for_expression<multivector<CoefficientType, Expression, Container>, true> { \
	public: \
	\
		typedef multivector<CoefficientType, Expression, Container> NAME##_argument_type; \
		typedef NAME##_argument_type&                               NAME##_argument_reference; \
		typedef const NAME##_argument_type&                         NAME##_argument_const_reference; \
	\
	public: \
	\
		inline \
		NAME##_argument_type NAME##() const { \
			return NAME##_argument_type(); \
		} \
	\
	protected: \
	\
		inline \
		NAME##_argument_storage_for_expression(NAME##_argument_type&& argument) { \
		} \
	};

_GA_DEFINE_ARGUMENT_STORAGE_FOR_EXPRESSION(first)
_GA_DEFINE_ARGUMENT_STORAGE_FOR_EXPRESSION(second)
_GA_DEFINE_ARGUMENT_STORAGE_FOR_EXPRESSION(single)

template<class FactorType, class Definition>
class metric_argument_storage_for_expression<metric<FactorType, Definition>, false> {
public:

	typedef metric<FactorType, Definition> metric_argument_type;
	typedef metric_argument_type&          metric_argument_reference;
	typedef const metric_argument_type&    metric_argument_const_reference;

public:

	inline
	metric_argument_const_reference metric() const {
		return _metric;
	}

protected:

	inline
	metric_argument_storage_for_expression(metric_argument_type&& argument) :
		_metric(argument) {}

private:

	metric_argument_const_reference _metric;
};

template<class FactorType, class Definition>
class metric_argument_storage_for_expression<metric<FactorType, Definition>, true> {
public:

	typedef metric<FactorType, Definition> metric_argument_type;
	typedef metric_argument_type&          metric_argument_reference;
	typedef const metric_argument_type&    metric_argument_const_reference;

public:

	inline
	metric_argument_type metric() const {
		return metric_argument_type();
	}

protected:

	inline
	metric_argument_storage_for_expression(metric_argument_type&& argument) {
	}
};
