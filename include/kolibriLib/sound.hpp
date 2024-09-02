#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include <sys/ksys.h>
#include <sound.h>

namespace KolibriLib
{
    namespace Sound
    {
        /// @brief Получить состояние спикера(Вкл/выкл)
        /// @return true если спикер разрешён, иначе false
        inline bool SpeakerStatus()
        {
            bool a;

            asm_inline(
                "int $0x40"
                : "=a"(a)
                : "a"(18), "b"(8), "c"(1));

            return !a;
        }

        /// @brief Переключить состояние спикера
        inline void SpeakerSwitch()
        {
            asm_inline (
                "int $0x40" 
                :: "a"(18), "b"(8), "c"(2)
            );
        }

        /// @brief Включить спикер
        /// @details если спикер уже включен, то функция ничего не сделает
        inline void EnableSpeaker()
        {
            if (!SpeakerStatus())
                SpeakerSwitch();
        }

        /// @brief Выключить спикер
        /// @details если спикер уже выключен, то функция ничего не сделает
        inline void DisableSpeaker()
        {
            if (SpeakerStatus())
                SpeakerSwitch();
        }

        struct SpeakerSound
        {
            struct Data
            {
                uint8_t lenght;
                uint8_t note;

                uint8_t GetNote() const;
            };

            Data* data;

            SpeakerSound(std::size_t size);
            ~SpeakerSound();
        };

        bool PlayOnSpeaker(SpeakerSound data);

        typedef int Error;

        typedef enum
        {
            PCM__2_16_48 = PCM_2_16_48,
            PCM__1_16_48 = PCM_1_16_48,
            PCM__2_16_44 = PCM_2_16_44,
            PCM__1_16_44 = PCM_1_16_44,
            PCM__2_16_32 = PCM_2_16_32,
            PCM__1_16_32 = PCM_1_16_32,
            PCM__2_16_24 = PCM_2_16_24,
            PCM__1_16_24 = PCM_1_16_24

        } SoundFormat;

        Error initSound()
        {
            Error err;
            int version = -1;

            if ((err = InitSound(&version)) != 0)
            {
                goto epic_fail;
            };

            if ((SOUND_VERSION > (version & 0xFFFF)) ||
                (SOUND_VERSION < (version >> 16)))
            {
                goto epic_fail;
            }

            epic_fail:
            return err;
        }

        Error PlaySound(void *buffer, int buffer_size, SoundFormat snd_format)
        {
            SNDBUF hBuff;

            Error err;

            if ((err = CreateBuffer(snd_format | PCM_OUT, 0, &hBuff)) != 0)
            {
                goto epic_fail;
            };
            WaveOut(hBuff, buffer, buffer_size);

            epic_fail:
            return err;
        }
    }
} // namespace KolibriLib

#endif // __SOUND_HPP__