#include <iostream>
#include "vector.h"

int main() {
   	double array[] = {1.1, 2.2, 3.3};

   	Vector vector(array, 3);

	std::cout << "Вектор после создания: ";
	for (auto i = vector.begin(); i != vector.end(); ++i)
	{
		std::cout << *i << " ";
	}

	std::cout << std::endl;

  	vector.pushBack(4.4);

   	vector.pushFront(0.5); 
	
   	std::cout << "Вектор после pushBack и pushFront: ";
   	for (auto i = vector.begin(); i != vector.end(); ++i)
   	{
	   	std::cout << *i << " ";
  	 }

   	std::cout << std::endl;
 
   	vector.insert(2.5, 2);

   	std::cout << "Вектор после insert: " ;
  	for (auto i = vector.begin(); i != vector.end(); ++i)
  	{
	   	std::cout << *i << " ";
 	}

	std::cout << std::endl;

   	vector.popBack(); 
	
	std::cout << "Вектор после popBack: ";
	for (auto i = vector.begin() ; i != vector.end(); ++i)
	{
		std::cout << *i << " ";
	}

	std::cout << std::endl;
	
	std::cout << "Итерация по элементам вектора: ";
 
   	for (auto i = vector.begin(); i != vector.end(); ++i) {
       	std::cout << *i << " ";
   	}

   	std::cout << "\nSize: " << vector.size() << ", Capacity: " << vector.capacity() << "\n";

   	long long index = vector.find(2.2);

   	if (index != -1) {
      	std::cout << "Найден элемент 2.2 с индексом: " << index << "\n";
   	} 
	
	else {
       	std::cout << "Элемент 2.2 не найден.\n";
   	}

   	return 0;
}
