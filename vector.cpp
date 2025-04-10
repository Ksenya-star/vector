#include "vector.h"
#include <iostream>

//Конструктор

Vector::Vector(const ValueType* rawArray, const size_t size, float coef)
    : _size(size), _capacity(size), _multiplicativeCoef(coef) 
{
	_data = new ValueType[_capacity];
	std::copy(rawArray, rawArray + size, _data);
}

//Конструктор копирования

Vector::Vector(const Vector& other)
    : _size(other._size), _capacity(other._capacity), _multiplicativeCoef(other._multiplicativeCoef) 
{
	_data = new ValueType[_capacity];
	std::copy(other._data, other._data + _size, _data);
}

//Оператор копирующего присваивания
 
Vector& Vector::operator=(const Vector& other) 
{
	if (this != &other) 
    	{
        	delete[] _data;
        	_size = other._size;
        	_capacity = other._capacity;
        	_multiplicativeCoef = other._multiplicativeCoef;
        	_data = new ValueType[_capacity];
        	std::copy(other._data, other._data + _size, _data);
    	}
    	return *this;
}

//Конструктор перемещения

Vector::Vector(Vector&& other) noexcept 
    : _data(other._data), _size(other._size), _capacity(other._capacity), _multiplicativeCoef(other._multiplicativeCoef){
	    other._data = nullptr;
	    other._size = 0;
	    other._capacity = 0;
}

//Оператор перемещающего присваивания

Vector& Vector::operator=(Vector&& other) noexcept 
{
    	if (this != &other) 
	{
        	delete[] _data;
        	_data = other._data;
        	_size = other._size;
        	_capacity = other._capacity;
        	_multiplicativeCoef = other._multiplicativeCoef;

        	other._data = nullptr;
        	other._size = 0;
        	other._capacity = 0;
    	}
    	return *this;
}

//Деструктор 

Vector::~Vector() 
{
	delete[] _data;
}

//Добавление элемента в конец

void Vector::pushBack(const ValueType& value) 
{
	if (_size >= _capacity) 
	{
		reserve(static_cast<size_t>(_capacity * _multiplicativeCoef));
    	}
    	_data[_size++] = value;
}

//Добавление элемента в начало

void Vector::pushFront(const ValueType& value) 
{
	if (_size >= _capacity) 
	{
        	reserve(static_cast<size_t>(_capacity * _multiplicativeCoef));
   	}
    
	std::move_backward(_data, _data + _size, _data + _size + 1);
    
	_data[0] = value;
    
	++_size;
}

//Вставка элемента в определённую позицию

void Vector::insert(const ValueType& value, size_t pos) 
{
	if (pos > _size) 
	{
        	throw std::out_of_range("Вне диапазона.");
    	}
    
    	if (_size >= _capacity) 
	{
        	reserve(static_cast<size_t>(_capacity * _multiplicativeCoef));
    	}
    
    	std::move_backward(_data + pos, _data + _size, _data + _size + 1);
    
    	_data[pos] = value;
    
    	++_size;
}

//Вставка массива элементов в определённую позицию

void Vector::insert(const ValueType* values, size_t size, size_t pos) 
{
	if (pos > _size) 
	{
        	throw std::out_of_range("Вне диапазона.");
    	}
    
    	while (_size + size > _capacity) 
	{
        	reserve(static_cast<size_t>(_capacity * _multiplicativeCoef));
    	}
    
    	std::move_backward(_data + pos, _data + _size, _data + _size + size);
    
    	std::copy(values, values + size, _data + pos);
    
    	_size += size;
}

//Удаление последнего элемента

void Vector::popBack() 
{
	if (_size > 0) 
	{
		--_size;
   	}
}

//удаление пераого элемента

void Vector::popFront() 
{
	if (_size > 0) 
	{
		std::move(_data + 1, _data + _size, _data);
		--_size;
   	}
}

//Удаление элементов из вектора по позиции и количеству

void Vector::erase(size_t pos, size_t count) 
{
	if (pos >= _size) 
	{
		throw std::out_of_range("Вне диапазона.");
  	}
   
   	count = std::min(count, _size - pos);
   
   	std::move(_data + pos + count, _data + _size, _data + pos);
   
   	_size -= count;
}

//Удаление элементов из вектра по диапазону позиций

void Vector::eraseBetween(size_t beginPos, size_t endPos) 
{
	if (beginPos >= endPos || endPos > _size) 
	{
		throw std::out_of_range("Недопустимый диапазон.");
	}
   
	std::move(_data + endPos, _data + _size, _data + beginPos);
	_size -= (endPos - beginPos);
}

//Размер

size_t Vector::size() const 
{
	return _size;
}

//Вместимость

size_t Vector::capacity() const 
{
	return _capacity;
}

//Загруженность вектора

double Vector::loadFactor() const 
{
	return static_cast<double>(_size) / static_cast<double>(_capacity);
}

//Доступ к элементу по индексу

ValueType& Vector::operator[](size_t idx) 
{
	if (idx >= _size) 
	{
		throw std::out_of_range("Вне диапазона.");
   	}
   	return _data[idx];
}

//Доступ к элементу по индексу(const)

const ValueType& Vector::operator[](size_t idx) const 
{
	if (idx >= _size) 
	{
		throw std::out_of_range("Вне диапазона.");
   	}
   	return _data[idx];
}

//Поиск первого вхождения значения

long long Vector::find(const ValueType& value) const 
{
	for (long long i = 0; i < static_cast<long long>(_size); ++i) 
	{
		if (_data[i] == value) 
		{
          		return i;
		}
   	}
   	return -1; 
}

//Резервированеи памяти для вектора

void Vector::reserve(size_t capacity) 
{
	if (capacity > _capacity) 
	{
		ValueType* newData = new ValueType[capacity];
       		std::copy(_data, _data + _size, newData);
       		delete[] _data;
       		_data = newData;
       		_capacity = capacity;
   	}
}

//Уменьшение ёмкости до текущего размера
 
void Vector::shrinkToFit() 
{
	if (_size < _capacity)
	{
       		ValueType* newData = new ValueType[_size];
       		std::copy(_data, _data + _size, newData);
       		delete[] _data;
       		_data = newData;
       		_capacity = _size;
  	}
}

 
Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}

 
ValueType& Vector::Iterator::operator*() 
{ 
	return *_ptr; 
}


const ValueType& Vector::Iterator::operator*() const 
{
	return *_ptr; 
}

 
ValueType* Vector::Iterator::operator->() 
{
	return _ptr; 
}

 
const ValueType* Vector::Iterator::operator->() const 
{
       	return _ptr; 
}

 
Vector::Iterator Vector::Iterator::operator++() 
{
   ++_ptr;
   return *this;
}


Vector::Iterator Vector::Iterator::operator++(int)
{
	Iterator temp = *this;
	++_ptr;
	return temp;
}

bool Vector::Iterator::operator==(const Iterator& other) const
{
	return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

Vector::Iterator Vector::begin()
{
	return Iterator(_data);
}


Vector::Iterator Vector::end()
{
	return Iterator(_data + _size);
}


