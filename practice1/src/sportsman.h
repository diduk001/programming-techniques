/**
 * @file sportsman.h
 * @brief Структура данных, описывающая спортсмена
 */

#pragma once

#include <string>

/**
 * @struct FullName
 * @brief ФИО спортсмена
 */
struct FullName
{
    std::string last_name;   //**< Фамилия */
    std::string first_name;  //**< Имя */
    std::string middle_name; //**< Отчество */

    /**
     * @brief Проверяет равенство двух ФИО
     * @param[other] ФИО для сравнения
     * @return true, если ФИО совпадают, иначе false
     */
    bool operator==(const FullName &other) const
    {
        return first_name == other.first_name &&
               middle_name == other.middle_name &&
               last_name == other.last_name;
    }

    /**
     * @brief Сравнивает два ФИО для сортировки (сначала по фамилии, затем по имени, затем по отчеству)
     * @param[other] ФИО для сравнения
     * @return true, если текущее ФИО должно идти раньше другого, иначе false
     */
    bool operator<(const FullName &other) const
    {
        if (last_name != other.last_name)
        {
            return last_name < other.last_name;
        }
        if (first_name != other.first_name)
        {
            return first_name < other.first_name;
        }
        return middle_name < other.middle_name;
    }

    /**
     * @brief Проверяет неравенство двух ФИО
     * @param[other] ФИО для сравнения
     * @return true, если ФИО не совпадают, иначе false
     */
    bool operator!=(const FullName &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Сравнивает два ФИО для сортировки (сначала по фамилии, затем по имени, затем по отчеству)
     * @param[other] ФИО для сравнения
     * @return true, если текущее ФИО должно идти позже другого, иначе false
     */
    bool operator>(const FullName &other) const
    {
        return other < *this;
    }

    /**
     * @brief Сравнивает два ФИО для сортировки (сначала по фамилии, затем по имени, затем по отчеству)
     * @param[other] ФИО для сравнения
     * @return true, если текущее ФИО должно идти не позже другого, иначе false
     */
    bool operator<=(const FullName &other) const
    {
        return !(other < *this);
    }

    /**
     * @brief Сравнивает два ФИО для сортировки (сначала по фамилии, затем по имени, затем по отчеству)
     * @param[other] ФИО для сравнения
     * @return true, если текущее ФИО должно идти не раньше другого, иначе false
     */
    bool operator>=(const FullName &other) const
    {
        return !(*this < other);
    }
};

/**
 * @struct Sportsman
 * @brief Структура данных, описывающая спортсмена
 */
struct Sportsman
{
    FullName full_name;       /**< ФИО спортсмена */
    unsigned short age;       /**< Возраст спортсмена в годах */
    unsigned short height_cm; /**< Рост спортсмена в сантиметрах */
    unsigned short weight_kg; /**< Вес спортсмена в килограммах */
    std::string sport;        /**< Спорт, которым занимается спортсмен */

    /**
     * @brief Конструктор, который инициализирует поля структуры на основе строки в формате CSV (вид спорта, фамилия, имя, отчество, возраст, рост, вес)
     * @param[csv_string] Строка в формате CSV
     * @return Инициализированный объект структуры Sportsman
     * @exception std::invalid_argument, если строка не содержит достаточного количества полей или если возраст, рост или вес не являются числовыми значениями
     */
    Sportsman(std::string csv_string)
    {
        size_t pos = 0;
        std::string token;
        std::string delimiter = ",";
        int field_index = 0;

        for (int field_idx = 0; field_idx < 7; field_idx++)
        {
            pos = csv_string.find(delimiter);
            if (pos == std::string::npos)
            {
                if (field_idx != 6)
                {
                    throw std::invalid_argument("Недостаточно полей в CSV строке");
                }
                token = csv_string;
            }
            else
            {
                token = csv_string.substr(0, pos);
                csv_string.erase(0, pos + delimiter.length());
            }

            switch (field_idx)
            {
            case 0:
                sport = token;
                break;
            case 1:
                full_name.last_name = token;
                break;
            case 2:
                full_name.first_name = token;
                break;
            case 3:
                full_name.middle_name = token;
                break;
            case 4:
                age = (unsigned short)std::stoul(token);
                break;
            case 5:
                height_cm = (unsigned short)std::stoul(token);
                break;
            case 6:
                weight_kg = (unsigned short)std::stoul(token);
                break;
            }
        }
    }

    /**
     * @brief Вывод в строку в формате CSV (вид спорта, фамилия, имя, отчество, возраст, рост, вес)
     * @return Строка в формате CSV
     */
    std::string to_csv() const
    {
        return sport + "," +
               full_name.last_name + "," +
               full_name.first_name + "," +
               full_name.middle_name + "," +
               std::to_string(age) + "," +
               std::to_string(height_cm) + "," +
               std::to_string(weight_kg);
    }

    /**
     * @brief Проверяет равенство двух спортсменов (сравнение по полям – вид  спорта, ФИО, возраст)
     * @param[other] Спортсмен для сравнения
     * @return true, если спортсмены совпадают, иначе false
     */
    bool operator==(const Sportsman &other) const
    {
        return sport == other.sport &&
               full_name == other.full_name &&
               age == other.age;
    }

    /**
     * @brief Сравнивает двух спортсменов для сортировки (сравнение по полям – вид  спорта, ФИО, возраст)
     * @param[other] Спортсмен для сравнения
     * @return true, если текущий спортсмен должен идти раньше другого, иначе false
     */
    bool operator<(const Sportsman &other) const
    {
        if (sport != other.sport)
        {
            return sport < other.sport;
        }
        if (full_name != other.full_name)
        {
            return full_name < other.full_name;
        }
        return age < other.age;
    }

    /**
     * @brief Проверяет неравенство двух спортсменов (сравнение по полям – вид  спорта, ФИО, возраст)
     * @param[other] Спортсмен для сравнения
     * @return true, если спортсмены не совпадают, иначе false
     */
    bool operator!=(const Sportsman &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Сравнивает двух спортсменов для сортировки (сравнение по полям – вид  спорта, ФИО, возраст)
     * @param[other] Спортсмен для сравнения
     * @return true, если текущий спортсмен должен идти позже другого, иначе false
     */
    bool operator>(const Sportsman &other) const
    {
        return other < *this;
    }

    /**
     * @brief Сравнивает двух спортсменов для сортировки (сравнение по полям – вид  спорта, ФИО, возраст)
     * @param[other] Спортсмен для сравнения
     * @return true, если текущий спортсмен должен идти не позже другого, иначе false
     */
    bool operator<=(const Sportsman &other) const
    {
        return !(other < *this);
    }

    /**
     * @brief Сравнивает двух спортсменов для сортировки (сравнение по полям – вид  спорта, ФИО, возраст)
     * @param[other] Спортсмен для сравнения
     * @return true, если текущий спортсмен должен идти не раньше другого, иначе false
     */
    bool operator>=(const Sportsman &other) const
    {
        return !(*this < other);
    }
};
