/*
    Файл с константами и малыми струтурами, которые используются везде
*/
#ifndef __SMALL_H__
#define __SMALL_H__



namespace KolibriLib
{
    /// @brief Сообщение всем функциям что нужно завершать работу
    bool EXIT = false;
    /// @brief Код ошибки
    /// @paragraph int main(){/*...*/ return EXITCODE; }
    /// @paragraph Эта библиотека считает что EXITCODE = 0 - это завершение работы без ошибки
    int EXITCODE = 0;

    const ::std::string ConfigurationDir = "/kolibrios/etc/";

    const ::std::string ImgDir = ConfigurationDir + "images/";

    const ::std::string DefaultImage = ImgDir + "default.png";

    const ::std::string CursorsDir = ConfigurationDir + "cursors/"; // Предпологается что в этой папке лежат файлы, они заранее приготовленны

    template <class T>
    /// @brief Просто точка
    /// @paragraph Если необходимо использовать конкретный теип данных для точки используйте шаблоны. Например: point<uint64_t> p;
    struct point
    {
        T x;
        T y;
    };

} // namespace KolibriLib


#endif // __SMALL_H__