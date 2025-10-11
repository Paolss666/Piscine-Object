#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <mutex>

template<typename T>
class Singleton
{
private:
	std::vector<T*> _elements;
	static Singleton<T>* _instance;
	static std::mutex _mutex;

	Singleton() {}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:
	static Singleton<T>* getInstance()
	{
		if (_instance == nullptr)
		{
			std::lock_guard<std::mutex> lock(_mutex);
			if (_instance == nullptr)
				_instance = new Singleton<T>();
		}
		return _instance;
	}

	void add(T* element)
	{
		if (element == nullptr)
			throw std::invalid_argument("Cannot add null element");
		
		std::lock_guard<std::mutex> lock(_mutex);
		
		auto it = std::find(_elements.begin(), _elements.end(), element);
		if (it == _elements.end())
			_elements.push_back(element);
	}

	T* get(size_t index)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		
		if (index >= _elements.size())
			throw std::out_of_range("Index out of range");
		return _elements[index];
	}

	const std::vector<T*>& getAll() const
	{
		return _elements;
	}

	size_t size() const
	{
		return _elements.size();
	}

	void clear()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_elements.clear();
	}

	~Singleton()
	{
		_elements.clear();
	}
};

template<typename T>
Singleton<T>* Singleton<T>::_instance = nullptr;

template<typename T>
std::mutex Singleton<T>::_mutex;

#endif