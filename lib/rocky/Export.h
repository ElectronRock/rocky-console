/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#include "rocky/Foundation.h"

#if defined(ROCKY_WIN)
#ifdef  ROCKY_EXPORT 
   /*Enabled as "export" while compiling the dll project*/
#define ROCKY_API __declspec(dllexport)  
#else
   /*Enabled as "import" in the Client side for using already created dll file*/
#define ROCKY_API __declspec(dllimport)  
#endif
#else
#define ROCKY_API
#endif
