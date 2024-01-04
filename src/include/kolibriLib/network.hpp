#ifndef __NETWORK_H__
#define __NETWORK_H__

extern "C"
{
    #include <sys/socket.h>
}

#include "childWindow.hpp"

namespace KolibriLib
{
    namespace Network
    {
        namespace Devices
        {
            /* bool ResetDevice(unsigned short Device)
            {
                int error;
                void *ptr = malloc(64);
                asm_inline(
                    "int $0x40"
                    :"=a"(error)
                    :"a"(74), "b"((2 << 16) + Device), "c"(*ptr)
                );
                return error;
            } */
        } // namespace Devices
        

        namespace Socket
        {
            enum Domain{
                IPv4 = 2,
                IPv6 = 10
            };
            enum SocetTypes
            {
                Stream = 1,
                DGram = 2,
                RAW = 3
            };

            /// @brief Окрыть сокет
            /// @param domain тим сети IPv4/IPv6
            /// @param SocetType 
            /// @return 
            int OpenSocket(int domain = IPv4, int SocetType = Stream, int protocol)
            {
                int Socket = socket(domain, SocetType, protocol);

                if(Socket == -1)
                {
                    childWindow::ErrorWindow("Can't creat Socket");
                }

                return Socket;
            }
        } // namespace Socket
        
    } // namespace network
    
} // namespace KolibriLib


#endif // __NETWORK_H__