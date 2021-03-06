/*
 * Copyright (c) 2018-2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "includes.hpp"

/* Any broadly useful language defines should go here. */

#define AMS_ASSERT(expr) do { if (!(expr)) { std::abort(); } } while (0)

#define AMS_UNREACHABLE_DEFAULT_CASE() default: std::abort()

#define NON_COPYABLE(cls) \
    cls(const cls&) = delete; \
    cls& operator=(const cls&) = delete

#define NON_MOVEABLE(cls) \
    cls(cls&&) = delete; \
    cls& operator=(cls&&) = delete

#define ALIGNED(algn) __attribute__((aligned(algn)))
#define NORETURN      __attribute__((noreturn))
#define WEAK_SYMBOL   __attribute__((weak))
#define ALWAYS_INLINE inline __attribute__((always_inline))
#define NOINLINE      __attribute__((noinline))

#define CONST_FOLD(x) (__builtin_constant_p(x) ? (x) : (x))

#define CONCATENATE_IMPL(S1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1, s2)

#define BITSIZEOF(x) (sizeof(x) * CHAR_BIT)

#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(pref) CONCATENATE(pref, __COUNTER__)
#else
#define ANONYMOUS_VARIABLE(pref) CONCATENATE(pref, __LINE__)
#endif

#define AMS_PREDICT(expr, value, _probability) __builtin_expect_with_probability(expr, value, ({ \
                                                    constexpr double probability = _probability; \
                                                    static_assert(0.0 <= probability);           \
                                                    static_assert(probability <= 1.0);           \
                                                    probability;                                 \
                                               }))

#define AMS_PREDICT_TRUE(expr, probability)  AMS_PREDICT(!!(expr), 1, probability)
#define AMS_PREDICT_FALSE(expr, probability) AMS_PREDICT(!!(expr), 0, probability)

#define AMS_LIKELY(expr)   AMS_PREDICT_TRUE(expr, 1.0)
#define AMS_UNLIKELY(expr) AMS_PREDICT_FALSE(expr, 1.0)
