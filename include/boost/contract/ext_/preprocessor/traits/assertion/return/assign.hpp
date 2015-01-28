
#ifndef BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_ASSIGN_HPP_
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_ASSIGN_HPP_

/* PRIVATE */

// Precondition: decl = `name = return NIL`.
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_PARSE_ARGS_( \
        decl, traits) \
    ( \
        BOOST_PP_NIL, \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK(traits, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_RETURN_REMOVE_BACK( \
            BOOST_CONTRACT_EXT_PP_NIL_REMOVE_BACK( \
                decl \
            )) \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_PARSE( \
        decl_traits) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN_PARSE_ARGS_ \
        decl_traits \
    )
    
// Expand to `name =` (note trailing `=` that cannot be removed via pp).
#define BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_AUX_ASSIGN_INDEX, \
        traits \
    )

#endif // #include guard    
