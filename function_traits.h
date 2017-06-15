#pragma once

template<typename F>
struct function_traits
{
    typedef typename function_traits<decltype(&F::operator())>::return_type return_type;
};

// F is a function
template<typename R, typename... A>
struct function_traits<R (*)(A...)>
{
    typedef R return_type;
    // TODO: ...
};

// F is an immutable functional object
template<typename R, typename T, typename... A>
struct function_traits<R (T::*)(A...) const>
{
    typedef R return_type;
    // TODO: ...
};

// F is a mutable functional object
template<typename R, typename T, typename... A>
struct function_traits<R (T::*)(A...)>
{
    typedef R return_type;
    // TODO: ...
};

template<typename F>
using return_type = typename function_traits<F>::return_type;
