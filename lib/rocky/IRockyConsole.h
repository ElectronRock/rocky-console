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
     * \brief Common interface of the console library.
     */
    class IRockyConsole
    {
    public:

        virtual ~IRockyConsole() = default;

        /**
         * \brief Initialization of the used subsystems, this method has to be called before any other method
         */
        virtual void Initialize() = 0;

        /**
         * \brief Deinitialization step, the call is required for propper application close
         */
        virtual void Destroy() = 0;

        /**
         * \brief Enables cursor visualization
         */
        virtual void ShowCursor() = 0;

        /**
         * \brief Disables cursor visualization
         */
        virtual void HideCursor() = 0;

        /**
         * \brief Moves render cursor to the given position
         * \param x target position by X axis
         * \param y target position bt Y axis
         * \return true if succeeded, false otherwise
         */
        virtual bool GoToXY(unsigned x, unsigned y) = 0;

        /**
         * \brief Sets current position value to output parameters
         * \param x current position by X axis
         * \param y current position by Y asix
         * \return true if succeeded, false otherwise
         */
        virtual bool ObtainXY(unsigned& x, unsigned& y) = 0;

        /**
         * \brief Setx max available value to output parameters
         * \param x max available value by X axis
         * \param y max available value vy Y axis
         * \return true if succeeded, false otherwise
         */
        virtual bool ObtainMaxXY(unsigned& x, unsigned& y) = 0;

        /**
         * \brief Clears the console window
         * \return true if succeeded, false otherwise
         */
        virtual bool Clear() = 0;

        /**
         * \brief Checks if any key is currently pressed
         * \return true if pressed, false otherwise
         */
        virtual bool IsKeyPressed() = 0;

        /**
         * \brief Gets index of the currently pressed key
         * \return Indentifier of the pressed key
         */
        virtual RockyKey GetKey() = 0;

        /**
         * \brief Sets formated text to the current position of the cursor(position might be set by GoToXY method)
         * \param format C style format of the text
         * \param ... 
         * \return true if succeeded, false otherwise
         */
        virtual bool SetText(const char* format, ...) = 0;

        /**
         * \brief Initializes color pair
         * \param index Index to be used as key of the registered color pair
         * \param back color to be used to the background
         * \param text color of the symbol
         * \return true if succeeded, false otherwise
         */
        virtual bool InitColor(unsigned index, RockyColor back, RockyColor text) = 0;

        /**
         * \brief Sets the color to be used to render symbols
         * \param index of the recently registered color
         * \return true if succeeded, false otherwise
         */
        virtual bool SetColor(unsigned index) = 0;

        /**
         * \brief Sets unregistered color (might not be fully functional)
         * \param back color to be used to the background
         * \param text color of the symbol
         * \return true if succeeded, false otherwise
         */
        virtual bool SetColor(RockyColor back, RockyColor text) = 0;
    };
}