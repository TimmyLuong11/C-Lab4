#ifndef RESIZABLE_ARRAY_H
#define RESIZABLE_ARRAY_H

#include "Exceptions.h"

const unsigned long DEFAULT_ARRAY_CAPACITY = 10;        // capacity used in no arg constructor

template <typename T>
class ResizableArray {
private:
	unsigned long capacity = DEFAULT_ARRAY_CAPACITY;    // maximum capacity, in items
	unsigned long size = 0;                             // actual number of items currently in array
	T* data = NULL;                                     // pointer to array of any type
	void doubleCapacity();                              // method to double array capacity
	void halveCapacity();                               // method to halve array capacity
public:
	ResizableArray();                                   // constructs array with default capacity
	ResizableArray(unsigned long capacity);             // constructs array with specified capacity
	virtual ~ResizableArray();                          // frees array space as object is deleted
	void add(T item);                                   // adds item, increments size, doubles capacity as necessary
	void addAt(T item, unsigned long index);            // adds item at index, shifts following, doubles capacity as necessary
	void replaceAt(T item, unsigned long index);        // replaces item at index, otherwise unchanged
	void removeAt(unsigned long index);                 // removes item at index, shifts following back
	T get(unsigned long index) const;                   // returns (copy of) item at index
	unsigned long getSize() const;                      // returns number of items currently in array
};

// Add your implementation below this line. Do not add or modify anything above this line.

//Method to double array capacity
template<typename T>
inline void ResizableArray<T>::doubleCapacity()
{
	capacity *= 2;
	T* tempArray = new T[capacity];
	for (unsigned long index = 0; index < size; ++index)
	{
		tempArray[index] = this->data[index];
	}
	this->data = tempArray;
}

//Method to halve array capacity
template<typename T>
inline void ResizableArray<T>::halveCapacity()
{
	capacity /= 2;
	T* tempArray = new T[capacity];
	for (unsigned long index = 0; index < size; ++index)
	{
		tempArray[index] = this->data[index];
	}
	this->data = tempArray;
}

//Constructs array with default capacity
template<typename T>
inline ResizableArray<T>::ResizableArray()
{
	this->data = new T[this->capacity];
}

//Constructs array with specified capacity
template<typename T>
inline ResizableArray<T>::ResizableArray(unsigned long capacity)
{
	this->data = new T[capacity];
	this->capacity = capacity;
}

//Frees array space as object is deleted
template<typename T>
inline ResizableArray<T>::~ResizableArray()
{
	delete[] this->data;
	this->data = NULL;
}

//Adds item, increments size, doubles capacity as necessary
template<typename T>
inline void ResizableArray<T>::add(T item)
{
	if (size < capacity)
	{
		data[size] = item;
		++size;
	}
	else
	{
		doubleCapacity();
		data[size] = item;
		++size;
	}
}

//Adds item at index, shifts following, doubles capacity as necessary
template<typename T>
inline void ResizableArray<T>::addAt(T item, unsigned long index)
{
	if (size == capacity)
	{
		doubleCapacity();
	}
	if (index > size)
	{
		throw new ExceptionIndexOutOfRange();
	}
	else
	{
		++size;
		T* temp = new T[capacity];
		for (unsigned long i = 0; i <= index; ++i) 
		{
			temp[i] = data[i];
			if (i == index)
			{
				temp[i] = item;
			}
		}

		for (unsigned long i = index; i < size - 1; ++i)
		{
			temp[i + 1] = this->data[i];
		}
		this->data = temp;
	}
}

//Replaces item at index, otherwise unchanged
template<typename T>
inline void ResizableArray<T>::replaceAt(T item, unsigned long index)
{
	if (index > size)
	{
		throw new ExceptionIndexOutOfRange();
	}
	data[index] = item;
}

//Removes item at index, shifts following back
template<typename T>
inline void ResizableArray<T>::removeAt(unsigned long index)
{
	if (index >= size)
	{
		throw new ExceptionIndexOutOfRange();
	}
	else
	{
		for (unsigned long i = index; i < size; ++i)
		{
			data[i] = data[i + 1];
		}
		--size;
	}
	if (size == capacity / 2)
	{
		halveCapacity();
	}
}

//Returns (copy of) item at index
template<typename T>
inline T ResizableArray<T>::get(unsigned long index) const
{
	if (index >= size)
	{
		throw new ExceptionIndexOutOfRange();
	}
	return data[index];
}

//Returns number of items currently in array
template<typename T>
inline unsigned long ResizableArray<T>::getSize() const
{
	return this->size;
}

#endif