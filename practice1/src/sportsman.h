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
