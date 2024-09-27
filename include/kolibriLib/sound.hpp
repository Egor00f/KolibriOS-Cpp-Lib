#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include <include_ksys.h>

#include <sound.h>

#include <utility>

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
            asm_inline(
                "int $0x40" ::"a"(18), "b"(8), "c"(2));
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

            Data *data;

            SpeakerSound(std::size_t size);
            ~SpeakerSound();
        };

        bool PlayOnSpeaker(SpeakerSound data);

        typedef int Error;
        using SoundFormat = int;

        enum class BufferType
        {
            /// @brief Статический буфер
            /// @details Простая звуковая сигнализация, озвучка интерфейса и т.п. Позволяет одновременно использовать звуковые данные в разных форматах.
            Out = PCM_OUT,

            /// @brief Потоковый буфер
            /// @details различные аудиоплееры. Программа загружает большие объёмы звуковых данных из сети, накопителей или генерирует их в реальном времени.
            Static = PCM_STATIC,

            /// @brief Кольцевой буфер
            /// @details игры и другие приложения с повышенными требованиями к синхронности аудио- и видеоряда.
            Ring = PCM_RING
        };

        Error initSound();

        class SoundLib
        {
        public:
            SoundLib();
        };

        Error PlaySound(void *buffer, int buffer_size, SoundFormat snd_format);

        class Buffer
        {
        public:
            /// @brief Конструктор
            /// @param type 
            /// @param format 
            /// @throw ошибка
            Buffer(BufferType type, SoundFormat format);

            /// @brief Конструктор
            /// @param type 
            /// @param format 
            /// @param ec ошибка
            Buffer(BufferType type, SoundFormat format, Error& ec) noexcept;

            ~Buffer();

            /// @brief проиграть буффер 
            /// @return 
            Error PlayAsync();

            /// @brief Проиграть буффер(ждать конца)
            /// @return 
            Error PlaySync();

            Error Reset();

            Error Play(bool async);

            /// @brief Устанавливает новый формат звукового буфера
            /// @details Применимо для PCM_OUT и PCM_STATIC буферов.
            /// @param format Новый формат
            /// @return ошибка
            Error SetFormat(SoundFormat format);

            /// @brief Устанавливает уровень громкости для правого и левого каналов.
            /// @details Уровень задаётся как ослабление сигнала в сотых долях децибела в диапазоне 0 - -10000, где 0 - максимальная громкость -10000 (-100dB) - полная тишина
            /// @return Ошибка
            Error SetVolume(int left, int right);

            /// @brief Устанавливает уровень громкости для правого и левого каналов.
            /// @details Уровень задаётся как ослабление сигнала в сотых долях децибела в диапазоне 0 - -10000, где 0 - максимальная громкость -10000 (-100dB) - полная тишина
            /// @return Ошибка
            Error SetVolume(std::pair<int, int> vol);

            /// @brief 
            /// @param left 
            /// @param right 
            /// @return 
            Error GetVolume(int &left, int &right) const;

            std::pair<int, int> GetVolume(Error &ec) const;

            /// @brief Устанавливает баланс левого и правого каналов
            /// @details Баланс задаётся в сотых долях децибела в диапазоне -10000 - 10000, где -10000 - тишина в правом канале 10000 - тишина в левом канале 0 - нормальный баланс каналов
            /// @param pan
            /// @return
            Error SetPan(int pan);

            /// @brief Получить баланс левого и правого каналов
            /// @param ec
            /// @return
            int GetPan(Error &ec) const;

            int GetSize(Error &ec);

            int GetFree(Error &ec);

            int GetPos(Error &ec);

            Error SetPos(int pos);

            /// @brief 
            /// @param buff буффер
            /// @param buff_size зармер буфера
            /// @param offset смешение
            /// @return 
            Error Set(void* buff, int buff_size, int offset = 0);

            Error Stop();

        private:
            SNDBUF _hBuff;
        };

        extern SoundLib lib;
    }
} // namespace KolibriLib

#endif // __SOUND_HPP__