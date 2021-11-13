/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#if defined(_WIN32) || defined(_WIN64)
#   define ROCKY_WIN
#else
#   if defined(ROCKY_WIN)
#       undef ROCKY_WIN
#   endif
#endif
