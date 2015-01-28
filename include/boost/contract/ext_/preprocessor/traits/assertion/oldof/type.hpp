
#ifndef BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TYPE_HPP_

/* PRIVATE */

// TODO: This pattern seems to be used a lot... maybe commonize it into some
// utility/* (something like DECL_TRAITS_PUSH_FRONT(decl_trait, traits) -->
// `(decl, push_back(traits, trait))`.
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_TYPE_( \
        decl_type, traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_type), \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)) \
    )

/* PUBLIC */

// Precondition: decl = `{auto | wrapped-type} ...`.
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_TYPE_PARSE_D(d, \
        decl_traits) \
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_TYPE_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUTO_TYPE_PARSE_D(d, \
                BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \
        BOOST_PP_TUPLE_ELEM(2, 1, decl_traits) \
    )
    
// Expand to `auto | (type,,,)`.
#define BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_TYPE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_AUX_TYPE_INDEX, \
        traits \
    )

#endif // #include guard    
