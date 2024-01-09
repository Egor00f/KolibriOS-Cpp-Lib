#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/ksys.h>

#include "childWindow.hpp"

/// \brief Основное пространство имён
/// \author Egor00f
namespace KolibriLib
{
    
    /// @brief Работа с сетью
    namespace Network
    {

        /// @brief Работа с сетевой картой
        namespace Devices
        {
            /// @brief Получить кол-во сетевых устройств
            /// @return Кол-во сетевых устройств
            inline int GetDevicesAmount()
            {
                int amount;
                asm_inline(
                    "int $0x40"
                    :"=a"(amount)
                    :"a"(74), "b"(-1)
                );
                return amount;
            }

            /// @brief Получить тип устройства
            /// @param device устройство
            /// @return тип устройства
            inline int GetDeviceType(const int device)
            {
                int type;
                asm_inline(
                    "int $0x40"
                    :"=a"(type)
                    :"a"(74), "b"(0)
                );
                return type;
            }

            /// @brief Получить имя устройства
            /// @param Device устройство
            /// @return Имя устройства
            inline std::string GetDeviceName(const int Device)
            {
                int abc;
                void *buff = malloc(64);
                asm_inline(
                    "int $0x40"
                    :"=a"(abc)
                    :"a"(74), "b"((1 << 16) + Device), "c"(buff)
                );
                return std::string((char*)buff);
            }

            /// @brief Сбросить устройство
            /// @param Device устройство
            /// @return 
            int ResetDevice(const unsigned Device)
            {
                int error;
                void *ptr = malloc(64);
                asm_inline(
                    "int $0x40"
                    :"=a"(error)
                    :"a"(74), "b"((2 << 16) + Device), "c"(ptr)
                );
                return error;
            } 

            /// @brief Класс для работы с сетевыми устройствами
            class NetDevice
            {
            private:
                unsigned _device;
            public:
                NetDevice(/* args */);
                ~NetDevice();
                
                /// @brief Получить имя устройства
                /// @return (std::string) Имя устройства
                std::string GetName();

                /// @brief Сбросить устройство
                /// @return 
                int Reset();
            };
            
            NetDevice::NetDevice(/* args */)
            {
            }
            
            NetDevice::~NetDevice()
            {
            }
            
        } // namespace Devices
        
        
    } // namespace network
    
} // namespace KolibriLib


#endif // __NETWORK_H__