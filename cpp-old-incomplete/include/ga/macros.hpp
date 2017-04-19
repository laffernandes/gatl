#define _GA_DECLARE_BINARY_OPERATION(OPERATION) \
	namespace result_of { \
	\
		template<class FirstArgumentType, class SecondArgumentType> \
		struct OPERATION; \
		\
		template<class FirstCoefficientType, class FirstComposition, container_class FirstContainer, class SecondCoefficientType, class SecondComposition, container_class SecondContainer> \
		struct OPERATION##<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, multivector<SecondCoefficientType, SecondComposition, SecondContainer> > { \
		\
			typedef typename ga::details::##OPERATION##_expression< \
					multivector<FirstCoefficientType, FirstComposition, FirstContainer>, \
					multivector<SecondCoefficientType, SecondComposition, SecondContainer> \
				>::lazy_type type; \
		}; \
		\
		template<class FirstCoefficientType, class FirstComposition, container_class FirstContainer, class SecondArgumentType> \
		struct OPERATION##<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, SecondArgumentType> { \
		\
			typedef typename ga::details::##OPERATION##_expression< \
					multivector<FirstCoefficientType, FirstComposition, FirstContainer>, \
					typename make_weighted_scalar<SecondArgumentType>::type \
				>::lazy_type type; \
		}; \
		\
		template<class FirstArgumentType, class SecondCoefficientType, class SecondComposition, container_class SecondContainer> \
		struct OPERATION##<FirstArgumentType, multivector<SecondCoefficientType, SecondComposition, SecondContainer> > { \
		\
			typedef typename ga::details::##OPERATION##_expression< \
					typename make_weighted_scalar<FirstArgumentType>::type, \
					multivector<SecondCoefficientType, SecondComposition, SecondContainer> \
				>::lazy_type type; \
		}; \
		\
	} \
	\
	template<class FirstCoefficientType, class FirstComposition, container_class FirstContainer, class SecondCoefficientType, class SecondComposition, container_class SecondContainer> \
	inline \
	typename result_of::##OPERATION##<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, multivector<SecondCoefficientType, SecondComposition, SecondContainer> >::type \
	OPERATION##(const multivector<FirstCoefficientType, FirstComposition, FirstContainer> &m1, const multivector<SecondCoefficientType, SecondComposition, SecondContainer> &m2) { \
		return ga::details::##OPERATION##_expression<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, multivector<SecondCoefficientType, SecondComposition, SecondContainer> >::bind(m1, m2); \
	}; \
	\
	template<class FirstCoefficientType, class FirstComposition, container_class FirstContainer, class SecondArgumentType> \
	inline \
	typename result_of::##OPERATION##<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, SecondArgumentType>::type \
	OPERATION##(const multivector<FirstCoefficientType, FirstComposition, FirstContainer> &m1, const SecondArgumentType &m2) { \
		return ga::details::##OPERATION##_expression<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, typename result_of::make_weighted_scalar<SecondArgumentType>::type>::bind(m1, make_weighted_scalar(m2)); \
	}; \
	\
	template<class FirstArgumentType, class SecondCoefficientType, class SecondComposition, container_class SecondContainer> \
	inline \
	typename result_of::##OPERATION##<FirstArgumentType, multivector<SecondCoefficientType, SecondComposition, SecondContainer> >::type \
	OPERATION##(const FirstArgumentType &m1, const multivector<SecondCoefficientType, SecondComposition, SecondContainer> &m2) { \
		return ga::details::##OPERATION##_expression<typename result_of::make_weighted_scalar<FirstArgumentType>::type, multivector<SecondCoefficientType, SecondComposition, SecondContainer> >::bind(make_weighted_scalar(m1), m2); \
	};

#define _GA_DECLARE_BINARY_OPERATION_FOR_SCALARS(OPERATION, SYMBOL) \
	namespace result_of { \
	\
		template<class FirstArgumentType, class SecondArgumentType> \
		struct OPERATION { \
		\
			typedef typename boost::common_type<FirstArgumentType, SecondArgumentType>::type type; \
		}; \
	\
	} \
	\
	template<class FirstArgumentType, class SecondArgumentType> \
	inline \
	typename result_of::##OPERATION##<FirstArgumentType, SecondArgumentType>::type \
	OPERATION##(const FirstArgumentType &m1, const SecondArgumentType &m2) { \
		return m1 SYMBOL m2; \
	};

#define _GA_OVERLOAD_BINARY_OPERATOR(OPERATION, SYMBOL) \
	template<class FirstCoefficientType, class FirstComposition, container_class FirstContainer, class SecondCoefficientType, class SecondComposition, container_class SecondContainer> \
	inline \
	auto \
	operator SYMBOL (const multivector<FirstCoefficientType, FirstComposition, FirstContainer> &m1, const multivector<SecondCoefficientType, SecondComposition, SecondContainer> &m2)->decltype(##OPERATION##(m1, m2)) { \
		return OPERATION##(m1, m2); \
	}; \
	\
	template<class FirstCoefficientType, class FirstComposition, container_class FirstContainer, class SecondArgumentType> \
	inline \
	auto \
	operator SYMBOL (const multivector<FirstCoefficientType, FirstComposition, FirstContainer> &m1, const SecondArgumentType &m2)->decltype(##OPERATION##(m1, m2)) { \
		return OPERATION##(m1, m2); \
	}; \
	\
	template<class FirstArgumentType, class SecondCoefficientType, class SecondComposition, container_class SecondContainer> \
	inline \
	auto \
	operator SYMBOL (const FirstArgumentType &m1, const multivector<SecondCoefficientType, SecondComposition, SecondContainer> &m2)->decltype(##OPERATION##(m1, m2)) { \
		return OPERATION##(m1, m2); \
	};
