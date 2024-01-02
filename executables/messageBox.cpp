/*
    Мини программа
    Выводит сообщение в окошке
    принимаемые агрументы: 
    Title, Message
*/

extern "C"
{
    #include <sys/ksys.h>
}

#include "../include/base.hpp"
#include "../include/window.hpp"


#define DEFAUTL_HEIGHT  100
#define DEFAULT_WIDTH   200

int main(int agrc, char* argv[])
{

    while(true)
    {
        const uint32_t button = KolibriLib::UI::buttons::GetButton();

        if(button == 1){
            KolibriLib::OS::Exit(0);
        }

        KolibriLib::window::DrawWindow({100, 100}, {DEFAULT_WIDTH, DEFAUTL_HEIGHT}, argv[1], 0x13);
        KolibriLib::window::DrawText(argv[2], {(int)KolibriLib::window::MARGIN, DEFAULT_WIDTH / 2});
    }

    return 0;
}