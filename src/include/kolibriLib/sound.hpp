#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include <sys/ksys.h>
#include <sound.h>

namespace KolibriLib
{
    namespace Sound
    {
        

        void PlaySound()
        {
            SNDBUF hBuff;
            void *buffer;    // семплы в формате snd_format
            int buffer_size; // размер буфера в байтах

            if(!CreateBuffer(PCM_OUT, 0, &hBuff))
            {
                _ksys_debug_puts("Error in CreateBuffer");
            }
            WaveOut(hBuff, buffer, buffer_size);
        }
    }
} // namespace KolibriLib

#endif // __SOUND_HPP__