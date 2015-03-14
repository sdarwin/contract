
#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   error "this compiler does not support variadic macros"
#else

#include <boost/contract/ext_/preprocessor/traits/aux_/index/func.hpp>
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INDEX_TEST \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_INDEX_FUNC_TEMPLATE

#include "../aux_/pp_traits.hpp"
#include <boost/contract/ext_/preprocessor/traits/func.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
        
#define BOOST_CONTRACT_TEST_TEMPLATE_(func_traits) \
    BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE(func_traits), \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARAMS(func_traits) \
    )

#define BOOST_CONTRACT_TEST_AUX_PP_TEMPLATE_CHECK(template_params) \
    BOOST_CONTRACT_TEST_AUX_PP_TRAITS( \
        BOOST_CONTRACT_TEST_TEMPLATE_, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D, \
        BOOST_PP_EMPTY(), \
        template_params, \
        (std::map<int, char>&) (f) ( int x, (std::map<int, char>&) y ), \
        template_params \
    )

#include "../aux_/pp_template.hpp"

int main ( ) {
    boost::contract::test::aux::pp_template();
    return BOOST_CONTRACT_TEST_AUX_PP_TRAITS_REPORT_ERRORS;
}

#endif // variadics

