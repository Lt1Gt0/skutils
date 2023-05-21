#pragma once
#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include "logger.hpp"
#define OPT [[maybe_unused]]

enum class Severity {
    low = 0,
    medium,
    high
};

inline void error(Severity severity)
{
    logger.Log(ERROR, "Exiting with severity: %d", (int)severity);
    std::cerr << '\n';
    std::exit((int)severity);
}

template<typename T, typename... Ts>
inline constexpr void error(Severity severity, T head, Ts... tail)
{
    std::cerr << head << " ";
    error(severity, tail...);
}
       
#endif // _COMMON_HPP_
