#pragma once
#include "stdafx.h"

template<typename T>
class Singleton
{
public:
	static T* Get()
	{
		if (instance == nullptr)
			instance = new T();

		return instance;
	}
	static void Delete()
	{
		SAFE_DELETE(instance);
	}
protected:
	Singleton() {};
	virtual ~Singleton() { SAFE_DELETE(instance); }

private:
	static T* instance;
};

template <typename T> T* Singleton<T>::instance = nullptr;