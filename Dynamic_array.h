#pragma once

template <typename T> 
class Dynamic_array
{
private:
	long long size_;
	long long capacity_;
	T* d_array_;
	void copy(T* dest, T* origin)
	{
		for (int i = 0; i < size_; i++)
		{
			dest[i] = origin[i];
		}
	}
public:
	Dynamic_array()
	{
		size_ = 0;
		capacity_ = 100;
		d_array_ = new T[100];
	}

	Dynamic_array(const Dynamic_array &cpy)
	{
		size_ = cpy.size();
		capacity_ = cpy.capacity_;
		d_array_ = new T[cpy.capacity_];
		for (int i = 0; i < cpy.size(); i++)
		{
			d_array_[i] = cpy.d_array_[i];
		}
	}

	T& operator=(const T& cpy)
	{
		size_ = cpy.size();
		capacity_ = cpy.capacity_;
		d_array_ = new T[cpy.capacity_];
		for (int i = 0; i < cpy.size(); i++)
		{
			d_array_[i] = cpy.d_array_[i];
		}
	}


	~Dynamic_array()
	{
	}

	T &operator [](long long position)
	{
		if (position >= size_ || position < 0)
			throw "Dynamic_array out of bounds";
		return d_array_[position];
	}

	void add(T& element)
	{
		if (size_ + 3 >= capacity_) {
			capacity_ += 100;
			T* temparray = new T[capacity_];
			copy(temparray, d_array_);
			delete d_array_;
			d_array_ = temparray;
		}
		d_array_[size_++] = element;
	}


	/*void remove(T element) unrequired
	{

	}*/

	long long size() const
	{
		return size_;
	}

	
};