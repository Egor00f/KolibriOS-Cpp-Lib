#include "network.hpp"

using namespace KolibriLib;

int Network::Devices::ResetDevice(unsigned short Device)
{
    int error;
    void *ptr = malloc(64);
    __asm__ __volatile__(
        "int $0x40"
        : "=a"(error)
        : "a"(74), "b"((2 << 16) + Device), "c"(ptr)
    );
    return error;
}

int Network::Socket::OpenSocket(int domain, int SocetType, int protocol)
{
    int Socket = socket(domain, SocetType, protocol);

    return Socket;
}

int Network::Socket::CloseSocket(int Socket)
{
    return close(Socket);
}