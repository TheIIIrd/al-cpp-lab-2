/*
Лабораторная работа 2. Изучение перегрузки стандартных операций в языке Си++

Вариант 19
Дан класс (например, с именем Vector), задающий вектор размерности n.
Поля класса: указатель на массив, задающий вектор (тип элемента int или double
в зависимости от варианта), массив должен создаваться динамически, число
элементов (размерность) вектора (тип int). Класс включает: конструктор без
параметров, задающий пустой вектор (число элементов равно 0), конструктор,
создающий объект вектор на основе обычного одномерного массива размерности n,
конструктор копирования, конструктор перемещения, деструктор.

Необходимо перегрузить операции и продемонстрировать их работу. Перегрузить
операцию [] (обращение к элементу вектора по индексу), операцию = (присваивание
с копированием), операцию = (присваивание с перемещением), а также операцию
вставки (<<) объекта в поток cout  или в файл (объект класса ostream) и операцию
извлечения (>>) объекта из потока cin или из файла (объект класса istream).

^ логическая операция (исключающая ИЛИ) с двумя векторами одинаковой
размерности, на выходе вектор такой же размерности элемент, которого равен
логическая операции ^ соответствующих элементов двух векторов

Типы операндов и результата для перегруженной операции:
Тип элемента вектора (массива): bool
Первый операнд: Vector
Второй операнд: Vector
Результат: Vector
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <fstream>
#include <iostream>
#include <utility>

class Vector {
  friend std::ostream &operator<<(std::ostream &os, const Vector &vector);
  friend std::istream &operator>>(std::istream &is, const Vector &vector);
  friend Vector operator*(bool _LOGIC, Vector &_VECT_TWO);
  friend Vector operator+(Vector &_VECT_ONE, Vector &_VECT_TWO);
  friend Vector operator^(Vector &_VECT_ONE, Vector &_VECT_TWO);

private:
  bool *_MAS = nullptr;
  size_t _LEN = 0;

public:
  Vector(bool *_MAS, size_t _LEN) {
    this->_LEN = _LEN;
    this->_MAS = new bool[_LEN];

    for (size_t i = 0; i < this->_LEN; ++i)
      this->_MAS[i] = _MAS[i];
  }

  Vector(size_t _LEN) {
    this->_LEN = _LEN;
    this->_MAS = new bool[_LEN];
  }

  Vector(const Vector &_VECT) {
    this->_LEN = _VECT._LEN;
    this->_MAS = new bool[this->_LEN];

    for (size_t i = 0; i < this->_LEN; ++i)
      this->_MAS[i] = _VECT._MAS[i];
  }

  Vector(Vector &&_VECT) {
    std::swap(this->_MAS, _VECT._MAS);
    std::swap(this->_LEN, _VECT._LEN);
  }

  Vector() {
    this->_LEN = 0;
    this->_MAS = nullptr;
  }

  bool &operator[](size_t _INDEX) { return this->_MAS[_INDEX]; }

  Vector &operator=(const Vector &_VECT_TWO) {
    if (this != &_VECT_TWO) {
      this->_LEN = _VECT_TWO._LEN;

      if (this->_MAS != nullptr)
        delete[] this->_MAS;
      this->_MAS = new bool[this->_LEN];

      for (size_t i = 0; i < this->_LEN; ++i)
        this->_MAS[i] = _VECT_TWO._MAS[i];
    }
    return *this;
  }

  Vector &operator=(Vector &&_VECT_TWO) {
    if (this != &_VECT_TWO) {
      std::swap(this->_MAS, _VECT_TWO._MAS);
      std::swap(this->_LEN, _VECT_TWO._LEN);
    }
    return *this;
  }

  ~Vector() {
    if (this->_MAS != nullptr)
      delete[] this->_MAS;
  }
};

inline std::ostream &operator<<(std::ostream &os, const Vector &vector) {
  os << "Len = " << vector._LEN << std::endl;

  for (size_t i = 0; i < vector._LEN; ++i)
    os << vector._MAS[i] << " ";
  os << std::endl;

  return os;
}

inline std::istream &operator>>(std::istream &is, Vector &vector) {
  size_t _TEMP_LEN;
  is >> _TEMP_LEN;

  bool _TEMP_MAS[_TEMP_LEN];

  for (size_t i = 0; i < _TEMP_LEN; ++i)
    is >> _TEMP_MAS[i];

  vector = Vector(_TEMP_MAS, _TEMP_LEN);

  return is;
}

inline Vector operator*(bool _LOGIC, Vector &_VECT_TWO) {
  Vector _VECTOR(_VECT_TWO._LEN);

  for (size_t i = 0; i < _VECT_TWO._LEN; ++i)
    _VECTOR._MAS[i] = _VECT_TWO._MAS[i] * _LOGIC;

  return _VECTOR;
}

inline Vector operator+(Vector &_VECT_ONE, Vector &_VECT_TWO) {
  Vector _VECTOR(_VECT_ONE._LEN + _VECT_TWO._LEN);

  for (size_t i = 0; i < _VECT_ONE._LEN; ++i)
    _VECTOR._MAS[i] = _VECT_ONE._MAS[i];

  for (size_t i = 0; i < _VECT_TWO._LEN; ++i)
    _VECTOR._MAS[_VECT_ONE._LEN + i] = _VECT_TWO._MAS[i];

  return _VECTOR;
}

inline Vector operator^(Vector &_VECT_ONE, Vector &_VECT_TWO) {
  Vector _VECTOR(_VECT_ONE._LEN);

  for (size_t i = 0; i < _VECT_ONE._LEN; ++i) {
    if (_VECT_ONE._MAS[i] != _VECT_TWO._MAS[i])
      _VECTOR._MAS[i] = 1;
    else
      _VECTOR._MAS[i] = 0;
  }
  return _VECTOR;
}

inline void customOutput(const Vector &_VECT) {
  std::ofstream fout("../stream/output.txt", std::ios::app);

  fout << _VECT;
  std::cout << _VECT;

  fout.close();
}

#endif
