/* Copyright (C) 2021 ElectronRock - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/ElectronRock/rocky-console
 */

#pragma once

#include "rocky/RockyColor.h"
#include "rocky/RockyKey.h"

namespace rocky
{

    /**
     * \brief 
     */
    class IRockyConsole
    {
    public:

        virtual ~IRockyConsole() = default;

        /**
         * \brief 
         */
        virtual void Initialize() = 0;

        /**
         * \brief 
         */
        virtual void Destroy() = 0;

        /**
         * \brief 
         */
        virtual void ShowCursor() = 0;

        /**
         * \brief 
         */
        virtual void HideCursor() = 0;

        /**
         * \brief 
         * \param x 
         * \param y 
         * \return 
         */
        virtual bool GoToXY(unsigned x, unsigned y) = 0;

        /**
         * \brief 
         * \param x 
         * \param y 
         * \return 
         */
        virtual bool ObtainXY(unsigned& x, unsigned& y) = 0;

        /**
         * \brief 
         * \param x 
         * \param y 
         * \return 
         */
        virtual bool ObtainMaxXY(unsigned& x, unsigned& y) = 0;

        /**
         * \brief 
         * \return 
         */
        virtual bool Clear() = 0;

        /**
         * \brief 
         * \return 
         */
        virtual bool IsKeyPressed() = 0;

        /**
         * \brief 
         * \return 
         */
        virtual RockyKey GetKey() = 0;

        /**
         * \brief 
         * \param format 
         * \param ... 
         * \return 
         */
        virtual bool SetText(const char* format, ...) = 0;

        /**
         * \brief 
         * \param index 
         * \param back 
         * \param text 
         * \return 
         */
        virtual bool InitColor(unsigned index, RockyColor back, RockyColor text) = 0;

        /**
         * \brief 
         * \param index 
         * \return 
         */
        virtual bool SetColor(unsigned index) = 0;

        /**
         * \brief
         * \param back 
         * \param text 
         * \return 
         */
        virtual bool SetColor(RockyColor back, RockyColor text) = 0;
    };
}