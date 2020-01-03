#ifndef _CUBIC_ARRAY_H_
#define _CUBIC_ARRAY_H_

#include <vector>

// Permet d'accèder un std::vector comme un tableau à 3 dimensions
// CubicArray<int> arr(5) -> tableau de taille 5 * 5 * 5

template<class T>
class CubicArray : public std::vector<T> {

public:

	/// Constructors
	
	CubicArray();
	CubicArray(size_t cubic_size, const T& value = {});

	/// Memory

	void resize(size_t cubic_size);

	/// Accessors

	// Ces fonctions renvoient toute la taille cubic
	size_t cubic_size() const;
	size_t width()      const;
	size_t height()     const;
	size_t depth()      const;

	// Les coordonnées n'ont pas le droit d'être négatives
	T&       operator()(size_t x, size_t y, size_t z);
	const T& operator()(size_t x, size_t y, size_t z) const;

private:

	size_t m_cubic_size;
};

#include "cubicArray.inl"

#endif
