#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class VectorShort {
private:
    short* data;              // Вказівник на масив елементів
    size_t size;              // Кількість елементів у векторі
    int codeError;            // Код помилки
    static int objectCount;   // Лічильник кількості об'єктів

public:
    // Коди помилок
    enum Errors { OK = 0, OUT_OF_RANGE = 1, MEMORY_ERROR = 2 };

    // Конструктор без параметрів
    VectorShort() : size(1), codeError(OK) {
        data = new(nothrow) short[1];
        if (!data) codeError = MEMORY_ERROR;
        else data[0] = 0;
        ++objectCount;
    }

    // Конструктор з параметром розміру
    VectorShort(size_t s) : size(s), codeError(OK) {
        data = new(nothrow) short[s]{};
        if (!data) codeError = MEMORY_ERROR;
        ++objectCount;
    }

    // Конструктор з параметрами розміру і значення ініціалізації
    VectorShort(size_t s, short value) : size(s), codeError(OK) {
        data = new(nothrow) short[s];
        if (!data) codeError = MEMORY_ERROR;
        else for (size_t i = 0; i < s; ++i) data[i] = value;
        ++objectCount;
    }

    // Конструктор копіювання
    VectorShort(const VectorShort& other) : size(other.size), codeError(other.codeError) {
        data = new(nothrow) short[size];
        if (!data) {
            codeError = MEMORY_ERROR;
        } else {
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        ++objectCount;
    }

    // Деструктор
    ~VectorShort() {
        delete[] data;
        --objectCount;
    }

    // Префіксні та постфіксні ++ та --
    VectorShort& operator++() { for (size_t i = 0; i < size; ++i) ++data[i]; return *this; }
    VectorShort operator++(int) { VectorShort tmp = *this; ++(*this); return tmp; }
    VectorShort& operator--() { for (size_t i = 0; i < size; ++i) --data[i]; return *this; }
    VectorShort operator--(int) { VectorShort tmp = *this; --(*this); return tmp; }

    // Логічне заперечення !
    bool operator!() const { return size != 0; }

    // Побітове заперечення ~
    VectorShort operator~() const {
        VectorShort result(size);
        for (size_t i = 0; i < size; ++i)
            result.data[i] = ~data[i];
        return result;
    }

    // Унарний мінус
    VectorShort operator-() const {
        VectorShort result(size);
        for (size_t i = 0; i < size; ++i)
            result.data[i] = -data[i];
        return result;
    }

    // Оператор присвоєння
    VectorShort& operator=(const VectorShort& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new(nothrow) short[size];
            if (!data) codeError = MEMORY_ERROR;
            else {
                for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
                codeError = OK;
            }
        }
        return *this;
    }

    // Арифметичні оператори присвоєння з вектором
    VectorShort& operator+=(const VectorShort& other) {
        for (size_t i = 0; i < size && i < other.size; ++i) data[i] += other.data[i];
        return *this;
    }
    VectorShort& operator-=(const VectorShort& other) {
        for (size_t i = 0; i < size && i < other.size; ++i) data[i] -= other.data[i];
        return *this;
    }

    // Арифметичні оператори присвоєння з числом
    VectorShort& operator*=(short value) {
        for (size_t i = 0; i < size; ++i) data[i] *= value;
        return *this;
    }
    VectorShort& operator/=(short value) {
        for (size_t i = 0; i < size; ++i) data[i] /= value;
        return *this;
    }
    VectorShort& operator%=(short value) {
        for (size_t i = 0; i < size; ++i) data[i] %= value;
        return *this;
    }

    // Побітові оператори присвоєння
    VectorShort& operator|=(const VectorShort& other) {
        for (size_t i = 0; i < size && i < other.size; ++i) data[i] |= other.data[i];
        return *this;
    }
    VectorShort& operator^=(const VectorShort& other) {
        for (size_t i = 0; i < size && i < other.size; ++i) data[i] ^= other.data[i];
        return *this;
    }
    VectorShort& operator&=(const VectorShort& other) {
        for (size_t i = 0; i < size && i < other.size; ++i) data[i] &= other.data[i];
        return *this;
    }

    // Арифметичні бінарні оператори (реалізація нижче)
    friend VectorShort operator+(const VectorShort& a, const VectorShort& b);
    friend VectorShort operator-(const VectorShort& a, const VectorShort& b);
    friend VectorShort operator*(const VectorShort& a, short val);
    friend VectorShort operator/(const VectorShort& a, short val);
    friend VectorShort operator%(const VectorShort& a, short val);

    // Побітові бінарні оператори
    friend VectorShort operator|(const VectorShort& a, const VectorShort& b);
    friend VectorShort operator^(const VectorShort& a, const VectorShort& b);
    friend VectorShort operator&(const VectorShort& a, const VectorShort& b);

    // Порівняння
    friend bool operator==(const VectorShort& a, const VectorShort& b);
    friend bool operator!=(const VectorShort& a, const VectorShort& b);
    friend bool operator>(const VectorShort& a, const VectorShort& b);
    friend bool operator<(const VectorShort& a, const VectorShort& b);
    friend bool operator>=(const VectorShort& a, const VectorShort& b);
    friend bool operator<=(const VectorShort& a, const VectorShort& b);

    // Індексація з перевіркою виходу за межі
    short& operator[](size_t idx) {
        if (idx >= size) {
            codeError = OUT_OF_RANGE;
            return data[size - 1];
        }
        codeError = OK;
        return data[idx];
    }

    // Виклик як функції (друк)
    void operator()() const {
        for (size_t i = 0; i < size; ++i)
            cout << data[i] << " ";
        cout << endl;
    }

    // Оператори введення/виведення
    friend ostream& operator<<(ostream& os, const VectorShort& vec);
    friend istream& operator>>(istream& is, VectorShort& vec);

    // Статичні методи
    static int getObjectCount() { return objectCount; } // Повертає кількість об'єктів
    int getCodeError() const { return codeError; }      // Повертає код помилки
};

// Ініціалізація статичного члена
int VectorShort::objectCount = 0;

// Приклад використання
int main() {
    VectorShort a(5, 2);
    VectorShort b = a;
    a += b;
    a();
    cout << "Objects: " << VectorShort::getObjectCount() << endl;
    return 0;
}
