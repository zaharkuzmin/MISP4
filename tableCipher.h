/** @file
 * @author Канцеров Л.Е.
 * @version 1.0
 * @date 17.12.2023
 * @copyright ИБСТ ПГУ
 * @brief Заголовочный файл модуля tableCipher
 */
#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cctype>
#include <locale>
#include <codecvt>
/**
 * @brief Класс обработки ошибок
 */
class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
/**
 * @brief Класс шифрования и расшифрования текста шифром табличной маршрутной перестановки
 */
class tableCipher
{
private:
    ///Ключ для зашифрования текста
    int key1;
    ///Русский алфавит в верхнем регистре
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ";
    ///Русский алфавит в нижнем регистре
    std::wstring lnumAlpha = L"абвгдеёжзийклмнопрстуфхцчшщьыъэюя";
    /**
     * @brief Функция проверки принадлежности к русскому алфавиту
     * @param wc Передаваемый символ
     * @return Значение true, если символ - буква русского алфавита, false - если нет.
     */
    bool is_rus(wchar_t wc);
    /**
     * @brief Функция проверки на нижний регистр
     * @param wch Передаваемый символ
     * @return Порядковый номер буквы в массиве, содержащем алфавит в нижнем регистре, если символ - в нижнем регистре, -1 - если нет.
     */
    int is_low_rus(wchar_t wch);
public:
    /**
     * @brief Запрет конструктора без параметров
     */
    tableCipher()=delete;
    /**
     * @brief Конструктор класса
     * @param key Ключ шифрования
     */
    tableCipher(const int& key)
    {
        if (key<=0) {
            throw cipher_error("Key is not valid\n");
        } else {
            key1=key;
        }
    }
    /**
     * @brief Функция зашифрования
     * @param open_text Открытый текст
     * @return Зашифрованный текст
     */
    std::wstring encrypt(std::wstring& open_text);
    /**
     * @brief Функция расшифрования
     * @param cipher_text Зашифрованный текст
     * @return Открытый текст
     */
    std::wstring decrypt(std::wstring& cipher_text);
    /**
     * @brief Функция валидации передаваемого текста
     * @param s Передаваемый текст
     * @return Валидированный текст
     * @throw cipher_error если текст пустой или содержит недопустимые символы
     */
    std::wstring toValid(std::wstring& s);
};
