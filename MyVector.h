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
	MyVector();
	MyVector(const MyVector<T>& v);
	MyVector(MyVector<T>&& v);
	MyVector(const std::initializer_list<T>& l);
	~MyVector();
	void push_back(const T& value);
	void pop_back();
	size_t size() const noexcept { return size_; }
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
	Iterator begin() { return Iterator(&arr[0]); }
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
	ConstIterator cbegin() { return ConstIterator(&arr[0]); }
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
	ReverseIterator rbegin() { return ReverseIterator(&arr[size_ - 1]); }
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
	ReverseIterator crbegin() { return ReverseIterator(&arr[size_ - 1]); }
	ReverseIterator crend() { return ReverseIterator(&arr[-1]); }

	// inserts before given element
	Iterator insert(Iterator where_, const T& val);
	Iterator erase(const Iterator&);

	void clear() noexcept { size_ = 0; }
	void assign(size_t newSize, const T& value);
	T at(size_t index) const;
	const T& back() { return at(size_ - 1); }
	const T& front() { return at(0); }
	const T* data() const noexcept{ return arr; }
	bool empty() const noexcept { return size_ == 0; }
	MyVector<T>& operator= (const MyVector<T>& r);
	MyVector<T>& operator= (MyVector<T>&& r);
	T& operator[] (size_t index) { return arr[index]; }
	const T& operator[] (size_t index) const { return arr[index]; }
	void reserve(size_t newCapacity);
	void resize(size_t newSize);
	void shrink_to_fit();
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