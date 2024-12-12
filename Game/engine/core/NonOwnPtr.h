#pragma once
#include "Precompiled.h"

/*
	- Main purpose of this class is to provice access to pointers without worrying about ownership and life time.
	- This class is not responsible for cleaning up memeory
*/

#define THROW_IF_NULL if(!mPtr) { throw std::invalid_argument( "Ptr is null" ); }

template<typename T>
class NonOwnPtr
{
public:
	NonOwnPtr() = default;

	NonOwnPtr(T* ptr)
	{
		mPtr = ptr;
	}

	~NonOwnPtr()
	{
		reset();
	}

	NonOwnPtr(const NonOwnPtr& rhs)
	{
		mPtr = rhs.mPtr;
	}

	NonOwnPtr& operator=(const NonOwnPtr& rhs)
	{
		if (&rhs != this)
		{
			mPtr = rhs.mPtr;
		}
		return *this;
	}

	NonOwnPtr(NonOwnPtr&& rhs) noexcept
	{
		mPtr = rhs.mPtr;
		rhs.reset();
	}
	NonOwnPtr& operator=(NonOwnPtr&& rhs) noexcept
	{
		if (&rhs != this)
		{
			mPtr = rhs.mPtr;
			rhs.reset();
		}
		return *this;
	}

	T& operator*()
	{
		THROW_IF_NULL
		return *mPtr;
	}

	const T& operator*() const
	{
		THROW_IF_NULL
		return *mPtr;
	}

	T* operator->()
	{
		THROW_IF_NULL
		return mPtr;
	}
	const T* operator->() const
	{
		THROW_IF_NULL
		return mPtr;
	}

	const T* get() const
	{
		THROW_IF_NULL
		return mPtr;
	}

	T* get()
	{
		THROW_IF_NULL
		return mPtr;
	}

	bool isNull() const
	{
		return mPtr == nullptr;
	}
	
	const bool operator==(const NonOwnPtr& rhs) const
	{
		return mPtr == rhs.mPtr;
	}

	void reset()
	{
		mPtr = nullptr;
	}

	void operator delete(void*) = delete; // dosent have ownership of memeory, so cannot delete it;

private:
	T* mPtr = nullptr;
};

template <typename T>
static NonOwnPtr<T> Make_NonOwnPtr(T* ptr)
{
	return NonOwnPtr<T>(ptr);
}

template <typename T>
static NonOwnPtr<T>& Make_NonOwnPtr(T value)
{
	return NonOwnPtr<T>(std::move(new T()));
}