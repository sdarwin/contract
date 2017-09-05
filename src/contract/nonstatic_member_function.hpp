// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#if !BOOST_PP_IS_ITERATING
#   // Include guards (but only if not iter).
#   ifndef CONTRACT_NONSTATIC_MEMBER_FUNCTION_HPP_
#       define CONTRACT_NONSTATIC_MEMBER_FUNCTION_HPP_
#       include "config.hpp"
#       include "assert.hpp"
#       include "state.hpp"
#       include "old.hpp"
#       include "aux_/old.hpp"
#       include "aux_/arg.hpp"
#       include "aux_/checking.hpp"
#       include "aux_/debug.hpp"
#       include "aux_/function/void_base_contract.hpp"
#       include <boost/type_traits.hpp>
#       include <boost/mpl/assert.hpp>
#       include <boost/mpl/if.hpp>
#       include <boost/preprocessor.hpp>
#       include <boost/utility.hpp>
#       include "aux_/function/local_macros_define.hpp" // #undef below.

namespace contract {

// F TEMPLATE PARAMETER SYNTAX
// Boost.Function preferred syntax is used for F so class type is
// passed as pointer in the 1st argumetn
// `ResultType (ClassType*, ArgumentType1, ...)`.
// A more natural syntax would have been to use C++ function pointer
// types as they already have different syntaxes to distinguish
// between members `ResulType (ClassType::*)(ArgumentType1, ...)` and
// non-members `ResultType (*)(ArgumentType1, ...)` (this would aslo
// unified nonstatic_member_function and nonmember_function into a
// signle template). However, some compilers do not fully support
// function pointers to resolve partial template specializations as
// needed by this library (notably, I have tried this and it compiled
// well on GCC but MSVC could not distinguish
// `ResultType (ClassType::*)(...) const` from
// `void (ClassType::*)() const`). Using Boost.Function works well
// plus harmonizes this library more with Boost.
// (The most portable syntax would have been the portable, not
// preferred, Boost.Function syntax but that is obsolete and supported
// by Boost.Function only for backward compatibility).

// PRE/POST/BODY FUNCTION PTR PASSING
// Teorethically, precondition, postcondition, and body function
// pointers could be passed as template parameters. However, that
// does not compile on some compliers for overloaded templated
// functions (like MSVC)... so these function pointers are passed to
// the constructor.
// Both options are fine for subcontracting, because even in the 
// second case the derived class constructs a base contract object
// via its default constructor which set pre, post, and body function
// pointer. Furthermore, the body function pointer could be passed to
// call() instead than to the consturctor because the body is not
// needed when subcontracting (only pre and post are) but all
// functions are passed together to the constructor for consistency.

// Should never be used directly (use only the specializations).
template<typename F
        // , BaseContractClass0 = void_base_contract<F> ...
        BOOST_PP_ENUM_TRAILING( 
                CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE, 
                CONTRACT_tparam_BaseContractClass_default, ~)
        >
class nonstatic_member_function {
    BOOST_MPL_ASSERT_MSG(0, CONTRACT_specified_invalid_function_type_template_parameter_F, ());
};

} // namespace

// Self-iterate this file over arity, void, const, and member.
#       define BOOST_PP_ITERATION_PARAMS_1 (3, \
            (0, CONTRACT_CONFIG_MAX_FUNCTION_ARITY, \
            CONTRACT_CONFIG_NONSTATIC_MEMBER_FUNCTION_HPP_FILE_PATH_))
#       include BOOST_PP_ITERATE() // Iter over arity.
#       include "aux_/function/local_macros_undef.hpp" // #define above.
#   endif // #include guard
# // 1st self-iteration over function-arity.
#elif BOOST_PP_ITERATION_DEPTH() == 1
#   define BOOST_PP_ITERATION_PARAMS_2 (3, (0, 1, \
            CONTRACT_CONFIG_NONSTATIC_MEMBER_FUNCTION_HPP_FILE_PATH_))
#   include BOOST_PP_ITERATE() // Iter over 0 void, 1 non-void func.
# // 2nd self-iteration over void/non-void function.
#elif BOOST_PP_ITERATION_DEPTH() == 2
#   // Define local macros directly depending on iteration.
#   define CONTRACT_arity \
        BOOST_PP_SUB(BOOST_PP_FRAME_FINISH(1), BOOST_PP_FRAME_ITERATION(1))
#   define CONTRACT_is_not_void BOOST_PP_NOT(BOOST_PP_FRAME_ITERATION(2))
#   define CONTRACT_is_member 1 // Always a member function.

namespace contract {

template<
        class ClassType
        // , ResultType (if not void)
        BOOST_PP_COMMA_IF(CONTRACT_is_not_void)
        BOOST_PP_EXPR_IF(CONTRACT_is_not_void, typename ResultType)
        // , ArgumentType0 ...
        BOOST_PP_COMMA_IF(CONTRACT_arity)
        BOOST_PP_ENUM(CONTRACT_arity,
                CONTRACT_tparam_ArgumentType, ~)
        // , BaseContractClass0 ...
        BOOST_PP_COMMA_IF(CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE)
        BOOST_PP_ENUM(
                CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
                CONTRACT_tparam_BaseContractClass, ~)
        >
class nonstatic_member_function<
        // ResultType ([ClassType::]*)(ArgumentType0, ...) [const]
        CONTRACT_f(1 /* member function */)
        // , BaseContractClass0 ...
        BOOST_PP_ENUM_TRAILING(
                CONTRACT_CONFIG_MAX_MULTIPLE_INHERITANCE,
                CONTRACT_BaseContractClass, ~)
        >:

        // This base class is made noncopyable so all contract classes are not
        // copyable. This is because there was no need to copy contract classes
        // but if there will ever be a need it might be possible to define
        // copy operation with correct semantics and remove this constraint.
        boost::noncopyable {

#   include "aux_/function/contract_class_implement.hpp"

}; // class

} // namespace

#   // Undef ALL local macros directly depending on iteration.
#   undef CONTRACT_arity
#   undef CONTRACT_is_not_void
#   undef CONTRACT_is_member
#else // Self-iteration out-of-range (should never happen...).
#   error "Preprocessor iteration depth out-of-range (internal error)"

#endif // BOOST_PP_IS_ITERATING
