#include <iostream>
#include <unordered_map>
#include <vector>

void InitVec(std::vector<int>& vector, const size_t& size) {
    for (size_t i = 0; i < size; i++) {
        vector.push_back(rand() % 10);
    }
}

void InitMapByVec(std::vector<int>& vector, std::unordered_map<int, int>& map) {
    for (auto i: vector) {
        map[i]++;
    }
}

template <class T>
int GetCrossingData(std::vector<T> &vector, std::unordered_map<T, T> &map) {
    for (size_t i = 0; i < vector.size(); i++) // Итерируемся сначала по вектору,
        if (map.contains(vector[i])) {         // находим совпадения и считаем их.
            if (map[vector[i]] > 0) {           // При этом значение в map при совпадении уменьшаем на 1.
                map[vector[i]]--;
            } else {
                vector.erase(vector.begin() + i);
            }
        }
    for (auto i : map) {                        // Пробегаем по map и удаляем необнуленные значения ключей(они
        if (i.second > 0) {                     // не совпали с вектором).
            map.erase(i.first);
        }
    }
    InitMapByVec(vector, map); // Перезаписываем новые значения
    return EXIT_SUCCESS;
}

template <class T>
int RandDel(std::vector<T> &vector, std::unordered_map<T, T> &map) {
    int deleted_val = 0;
    /*auto func = [&i, &deleted_val, &vector] (int &val) { if (val == deleted_val) {
                                                             vector.erase(vector.begin()+i);
                                                             return;
                                                         } else i++;};*/
    for (size_t i = 0; i < rand()%14+1; i++) {
        deleted_val = rand() % 10;
        auto index = std::find(vector.begin(), vector.end(), deleted_val);
        if (index != vector.end()) {
            vector.erase(index);
        }
    }
    for (size_t i = 0; i < rand()%14+1; i++) {
        deleted_val = rand() % 10;
        if (map.contains(deleted_val)) {
            if (map[deleted_val] > 0)
                map[deleted_val]--;
        } else {
            map.erase(deleted_val);
        }
    }

    return EXIT_SUCCESS;
}

int main() {
    std::vector<int> test_vector;
    std::unordered_map<int, int> test_map; // Ключ - элемент вектора, значение - количество таких ключей

    size_t amount_of_digits;
    amount_of_digits = rand() % 84 + 16; // По условию может быть удалено до 15 элементов

    test_vector.reserve(amount_of_digits);
    test_map.reserve(amount_of_digits);

    InitVec(test_vector, amount_of_digits); // Заполнение
    InitMapByVec(test_vector, test_map);

    for (auto i: test_vector) {                            // Выведем первоначальное соответсвие
        std::cout << i << " " << test_map[i] << std::endl;
    }

    RandDel(test_vector, test_map);        // Удаление случайного количества элементов у map и vector
    GetCrossingData(test_vector, test_map);  // Сохранение только пересечения

    std::cout << "-------After all-------\n";

    // Выводим результат в виде: элемент вектора ==> их количесво в массиве, используя map
    for (auto i: test_vector) {
        std::cout << i << " ===> " << test_map[i] <<std::endl;
    }

    return EXIT_SUCCESS;
}
