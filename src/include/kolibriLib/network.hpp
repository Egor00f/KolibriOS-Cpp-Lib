#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdio.h>
#include <stdlib.h>

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
            /// @brief Сбросить устройство
            /// @param Device Сбрасываемое устройство
            /// @return 
            int ResetDevice(unsigned short Device);
            
        } // namespace Devices
        

        /// @brief Работа с сокетами
        namespace Socket
        {
            #include <sys/socket.h>

            /// @brief 
            enum Domain
            {
                IPv4 = 2,
                IPv6 = 10
            };
            /// @brief Список типов сокета
            enum SocetTypes
            {
                Stream = 1,
                DGram = 2,
                RAW = 3
            };

            /// @brief Список протоколов
            enum Protocols
            {
                PROTOCOL_IP = 0,
                PROTOCOL_CMP = 1,
                PROTOCOL_TCP = 6,
                PROTOCOL_UDP = 17,
                PROTOCOL_RAW = 255
            };

            /// @brief Окрыть сокет
            /// @param domain тип сети IPv4/IPv6
            /// @param SocetType 
            /// @param protocol Используемый протокол
            /// @return номер сокета
            inline int OpenSocket(int domain = IPv4, int SocetType = Stream, int protocol = PROTOCOL_IP);

            /// @brief Закрыть сокет
            /// @param Socket номер сокета
            /// @return статус
            int CloseSocket(int Socket);

        } // namespace Socket
        
    } // namespace network
    
} // namespace KolibriLib


#endif // __NETWORK_H__