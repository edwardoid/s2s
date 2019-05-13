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

#ifndef SIGNAL_TO_SLOT_H
#define SIGNAL_TO_SLOT_H

#include <map>
#include <functional>

namespace SignalSlot
{
    template<typename... Args>
    class Signal
    {
    public:
        using Slot = std::function<void(Args... args)>;
        void emit(Args... args) {
            for(const auto& s : m_slots) {
                s.second(args...);
            }
        }

        int connect(Slot&& slot) {
            if (IDX == 0) {
                ++IDX;
            }
            m_slots.emplace(IDX, slot);
            return IDX;
        }

        void connect(Signal<Args...>& signal) {
            connect([&signal](Args... args) {
                signal.emit(args...);
            });
        }

        void disconnect(int id) {
            m_slots.erase(id);
        }
    private:
        int IDX = 0;
        std::map<int, Slot> m_slots;
    };
}

#endif // SIGNAL_TO_SLOT_H
