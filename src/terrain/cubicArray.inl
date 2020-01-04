#ifndef _CUBIC_ARRAY_INL_
#define _CUBIC_ARRAY_INL_

#include "cubicArray.h" 

///////////////////////// CubicArray

// Constructors

template<class T>
CubicArray<T>::CubicArray() : std::vector<T>(), m_cubic_size{0} {}

template<class T>
CubicArray<T>::CubicArray(size_t cubic_size, const T& value) : std::vector<T>(cubic_size * cubic_size * cubic_size, value), m_cubic_size{cubic_size} {}

// Memory

template<class T>
void CubicArray<T>::resize(size_t cubic_size) {
	std::vector<T>::resize(cubic_size * cubic_size * cubic_size);
	m_cubic_size = cubic_size;
}

// Accessors

template<class T>
size_t CubicArray<T>::cubic_size()  const {
	return m_cubic_size;;
}

template<class T>
size_t CubicArray<T>::width()  const {
	return this->cubic_size();
}

template<class T>
size_t CubicArray<T>::height() const {
	return this->cubic_size();
}

template<class T>
size_t CubicArray<T>::depth()  const {
	return this->cubic_size();
}

template<class T>
T&       CubicArray<T>::operator()(size_t x, size_t y, size_t z) {
	return (*this)[ x + (y * this->width()) + (z * this->width() * this->height()) ];
}

template<class T>
const T& CubicArray<T>::operator()(size_t x, size_t y, size_t z) const {
	return (*this)[ x + (y * this->width()) + (z * this->width() * this->height()) ];
}

#endif