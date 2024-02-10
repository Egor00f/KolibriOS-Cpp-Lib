#include "network.hpp"

int KolibriLib::Network::Devices::GetNumberNetworkDevices()
{
    int number;
    __asm__ __volatile__ (
        "int $0x40"
        :"=a"(number)
        :"a"(74), "b"(-1)
    );
    return number;
}

std::string KolibriLib::Network::Devices::GetDeviceName(unsigned Device)
{
    char *buff =(char*) malloc(64);
    int err;
    __asm__ __volatile__ (
        "int $0x40"
        :"=a"(err)
        :"a"(74), "b"((Device << 16) + 1), "c"(buff)
    );

    std::string s;

    if(err != -1)
    {
        s = buff;
    }

    free(buff);
    return s;
}

int KolibriLib::Network::Devices::ResetDevice(unsigned Device)
{
    int err;
    __asm__ __volatile__(
        "int $0x40"
        : "=a"(err)
        : "a"(74), "b"((Device << 16) + 2)
    );
    return err;
}