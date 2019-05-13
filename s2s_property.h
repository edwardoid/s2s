/* 
 * This file is part of the S2S distribution (https://github.com/edwardoid/s2s).
 * Copyright (c) 2019 Edward Sargsyan.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SIGNAL_TO_SLOT_PROPERTY_H
#define SIGNAL_TO_SLOT_PROPERTY_H

#include "s2s.h"

namespace SignalSlot
{
    template<typename T>
    class Property: public Signal<const T&>
    {
    public:
        void set(const T& newValue) {
            if (value != newValue) {
                value = newValue;
                Signal<const T&>::emit(newValue);
            }
        }

        const Property<T>& operator = (const T& src) {
            set(src);
            return *this;
        }

        const Property<T>& operator = (const Property<T>& src) {
            return set(src.value);
        }

        void bind(Property<T>& src) {
            src.connect([this](const T& v) {
                set(v);
            });
        }

        operator T () { return value; }
        T value;
    };
}

#endif // SIGNAL_TO_SLOT_PROPERTY_H
