#ifndef _MYVECTOR_H_
#define _MYVECTOR_H_

#include <initializer_list>
#include <algorithm>

template<typename T>
class MyVector
{
private:
	T* arr;
	size_t size_;
	size_t capacity_;
public:
	// Default c-tor. Sets the capacity to 5
	MyVector();
	// Copy c-tor
	MyVector(const MyVector<T>& v);
	// Move c-tor
	MyVector(MyVector<T>&& v);
	// 
	MyVector(const std::initializer_list<T>& l);
	~MyVector();
	// Add element to the end
	void push_back(const T& value);
	// Remove element from the end
	void pop_back();
	// Returns the size of the vector
	size_t size() const noexcept { return size_; }
	// Returns the capacity of the vector
	size_t capacity() const noexcept { return capacity_; }

	struct Iterator {
		//tags
		
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;  
		using reference = T&;  
		
		Iterator(pointer ptr) : m_ptr(ptr) {}
		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		Iterator& operator++() { m_ptr++; return *this; }
		Iterator& operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		Iterator& operator--() { m_ptr--; return *this; }
		Iterator& operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
		friend Iterator operator+(const Iterator& a, difference_type n) { return a.m_ptr + n; }
		friend Iterator operator+(difference_type n, const Iterator& a) { return a.m_ptr + n; }
		friend Iterator operator-(const Iterator& a, difference_type n) { return a.m_ptr - n; }
		friend Iterator operator-(difference_type n, const Iterator& a) { return a.m_ptr - n; }
		friend difference_type operator-(const Iterator& a, const Iterator& b) { return b.m_ptr - a.m_ptr; }
		Iterator& operator+=(difference_type n) { return (m_ptr += n); }
		Iterator& operator-=(difference_type n) { return (m_ptr -= n); }
		T operator[](difference_type n) { return *(m_ptr + n); }
		friend bool operator<  (const Iterator& a, const Iterator& b) { return a.m_ptr < b.m_ptr; }
		friend bool operator<= (const Iterator& a, const Iterator& b) { return a.m_ptr < b.m_ptr || a.m_ptr == b.m_ptr; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
	private:
		pointer m_ptr;
	};
	// Returns the iterator pointing to first element
	Iterator begin() { return Iterator(&arr[0]); }
	// Returns the iterator pointing to the element after the last
	Iterator end() { return Iterator(&arr[size_]); }

	struct ConstIterator {
		//tags

		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		ConstIterator(pointer ptr) : m_ptr(ptr) {}
		const reference operator*() const { return *m_ptr; }
		const pointer operator->() const { return m_ptr; }
		ConstIterator& operator++() { m_ptr++; return *this; }
		ConstIterator& operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }
		ConstIterator& operator--() { m_ptr--; return *this; }
		ConstIterator& operator--(int) { ConstIterator tmp = *this; --(*this); return tmp; }
		friend bool operator== (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const ConstIterator& a, const ConstIterator& b) { return a.m_ptr != b.m_ptr; };
	private:
		pointer m_ptr;

	};
	// Returns the constant iterator pointing to first element
	ConstIterator cbegin() { return ConstIterator(&arr[0]); }
	// Returns the constant iterator pointing to the element after the last
	ConstIterator cend() { return ConstIterator(&arr[size_]); }

	struct ReverseIterator {
		//tags

		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		ReverseIterator(pointer ptr) : m_ptr(ptr) {}
		reference operator*() { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		ReverseIterator& operator++() { m_ptr--; return *this; }
		ReverseIterator operator++(int) { ReverseIterator tmp = *this; ++(*this); return tmp; }
		ReverseIterator& operator--() { m_ptr++; return *this; }
		ReverseIterator operator--(int) { ReverseIterator tmp = *this; --(*this); return tmp; }
		friend bool operator== (const ReverseIterator& a, const ReverseIterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const ReverseIterator& a, const ReverseIterator& b) { return a.m_ptr != b.m_ptr; };
	private:
		pointer m_ptr;

	};
	// Returns the reverse iterator pointing to first element
	ReverseIterator rbegin() { return ReverseIterator(&arr[size_ - 1]); }
	// Returns the reverse iterator pointing to the element after the last
	ReverseIterator rend() { return ReverseIterator(&arr[-1]); }

	struct ConstReverseIterator {
		//tags

		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		ConstReverseIterator(pointer ptr) : m_ptr(ptr) {}
		reference operator*() { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		ConstReverseIterator& operator++() { m_ptr++; return *this; }
		ConstReverseIterator& operator++(int) { ConstReverseIterator tmp = *this; ++(*this); return tmp; }
		ConstReverseIterator& operator--() { m_ptr--; return *this; }
		ConstReverseIterator& operator--(int) { ConstReverseIterator tmp = *this; --(*this); return tmp; }
		friend bool operator== (const ConstReverseIterator& a, const ConstReverseIterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const ConstReverseIterator& a, const ConstReverseIterator& b) { return a.m_ptr != b.m_ptr; };
	private:
		pointer m_ptr;

	};
	// Returns the constant reverse iterator pointing to first element
	ReverseIterator crbegin() { return ReverseIterator(&arr[size_ - 1]); }
	// Returns the constant reverse iterator pointing to the element after the last
	ReverseIterator crend() { return ReverseIterator(&arr[-1]); }

	// Inserts "val" before the given element
	Iterator insert(Iterator where_, const T& val);
	// Erases the given element
	Iterator erase(const Iterator&);

	// Clears the vector
	void clear() noexcept { size_ = 0; }
	// Assigns the new size to the vector and assigns the new value to every element
	void assign(size_t newSize, const T& value);
	// Guranteed to throw std::index_out_of_range if index is out of bounds
	T at(size_t index) const;
	// Returns the last element of the vector
	const T& back() { return at(size_ - 1); }
	// Returns the first element of the vector
	const T& front() { return at(0); }
	// Returns the C-style array
	const T* data() const noexcept{ return arr; }
	// Returns true if the vector is empty
	bool empty() const noexcept { return size_ == 0; }
	// Assingment operator
	MyVector<T>& operator= (const MyVector<T>& r);
	// Move assignment operator
	MyVector<T>& operator= (MyVector<T>&& r);
	// At-index operator which return the reference on the element
	T& operator[] (size_t index) { return arr[index]; }
	// At-index operator which return the element
	const T& operator[] (size_t index) const { return arr[index]; }
	// Reserves the new capacity in the RAM
	void reserve(size_t newCapacity);
	// Changes the size of the vector. Internally calls reserve(size_t). Doesn't change the new elements
	void resize(size_t newSize);
	// Make the capacity equal to the size of the vector
	void shrink_to_fit();
	// Swaps current vector with the given one
	void swap(MyVector<T>& r);
};


template<typename T>
inline MyVector<T>::MyVector() : arr(nullptr), size_(0), capacity_(5)
{
	arr = new T[capacity_];
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector<T>& v) : arr(nullptr), size_(v.size_), capacity_(v.capacity_)
{
	arr = new T[capacity_];
	for (size_t i = 0; i < size_; i++)
		arr[i] = v.arr[i];
}

template<typename T>
inline MyVector<T>::MyVector(MyVector<T>&& v) : arr(v.arr), size_(v.size_), capacity_(v.capacity_)
{
	v.arr = nullptr;
	v.size_ = 0;
	v.capacity_ = 0;
}

template<typename T>
inline MyVector<T>::MyVector(const std::initializer_list<T>& l) : arr(nullptr), size_(l.size()), capacity_(l.size() + 5)
{
	arr = new T[capacity_];
	size_t i = 0;
	for (auto t : l)
	{
		arr[i] = t;
		i++;
	}
}

template<typename T>
inline MyVector<T>::~MyVector()
{
	delete[] arr;
}

template<typename T>
inline void MyVector<T>::push_back(const T& value)
{
	if (size_ < capacity_)
	{
		arr[size_] = value;
		size_++;
	}
	else
	{
		capacity_ += 5;
		T* t = new T[capacity_];
		for (size_t i = 0; i < size_; i++)
		{
			t[i] = arr[i];
		}
		t[size_] = value;
		size_++;
		delete[] arr;
		arr = t;
	}
}

template<typename T>
inline void MyVector<T>::pop_back()
{
	if (size_ > 0)
	{
		size_--;
	}
	else
	{
		throw std::out_of_range("Vector empty before pop");
	}
}

template<typename T>
inline void MyVector<T>::assign(size_t newSize, const T& value)
{
	delete[] arr;
	size_ = newSize;
	if (newSize > capacity_)
	{
		capacity_ = newSize + 5;
		arr = new T[capacity_];
	}
	for (size_t i = 0; i < newSize; i++)
	{
		arr[i] = value;
	}
}

template<typename T>
inline T MyVector<T>::at(size_t index) const
{
	if (index >= size_)
		throw std::out_of_range;
	return arr[index];
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& r)
{
	if (&r == this)
		return *this;

	delete[] arr;
	size_ = r.size_;
	capacity_ = r.capacity_;

	arr = new T[capacity_];
	if (!arr)
		throw std::bad_alloc;
	for (size_t i = 0; i < size_; i++)
		arr[i] = r.arr[i];
	return *this;
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(MyVector<T>&& r)
{
	if (&r == this)
		return *this;

	delete[] arr;
	size_ = r.size_;
	capacity_ = r.capacity_;

	arr = r.arr;
	for (size_t i = 0; i < size_; i++)
		arr[i] = r.arr[i];
	return *this;
}

template<typename T>
inline void MyVector<T>::reserve(size_t newCapacity)
{
	if (newCapacity > capacity_)
	{
		capacity_ = newCapacity;
		T* t = new T[capacity_];
		for (size_t i = 0; i < size_; i++)
			t[i] = arr[i];
		delete[] arr;
		arr = t;
	}
}

template<typename T>
inline void MyVector<T>::resize(size_t newSize)
{
	reserve(newSize);
	if (newSize > size_)
	{
		for (size_t i = size_ - 1; i < newSize; i++)
			arr[i] = static_cast<T>(0);
	}
	size_ = newSize;
}

template<typename T>
inline void MyVector<T>::shrink_to_fit()
{
	T* t = new T[size_];
	for (size_t i = 0; i < size_; i++)
		t[i] = arr[i];
	delete[] arr;
	arr = t;
}

template<typename T>
inline void MyVector<T>::swap(MyVector<T>& r)
{
	MyVector<T>* t = new MyVector<T>;
	*t = *this;

	*this = r;
	r = *t;
}

template<typename T>
inline typename MyVector<T>::Iterator MyVector<T>::insert(Iterator where_, const T& val)
{
	reserve(size_ + 1);
	auto i = end();
	for (; i != where_; i--)
	{
		*i = *(i - 1);
	}
	*i = val;
	size_++;
	return i;
}

template<typename T>
inline typename MyVector<T>::Iterator MyVector<T>::erase(const Iterator& where_)
{
	Iterator i = where_;
	for (; i != end(); i++)
	{
		*i = *(i + 1);
	}
	size_--;
	return i;
}

#endif // _MYVECTOR_H_