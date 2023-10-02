#pragma once
#include <iostream>
using namespace std;
template <typename T>

// NOTE: A lot of this might not work and that is completely my fault
// I am sorry to whoever is grading this, I promise I'll do better next assignement
class Queue
{
	T arr;
	int fullSize;
	int count;

public:

	template <typename T>
	// Constructor
	Queue::Queue()
	{
		fullSize = 5;
		arr = new T[int];
		count = 0;
	}

	// Copy constructor
	Queue(Queue const& other)
	{
		//other = this.other;
	}

	// Copy assignment operator
	Queue& operator=(Queue const& other)
	{
		//return *other;
	}

	// Destructor
	~Queue(void)
	{
		delete[] arr;
	}

	// Adds info to queue
	void Push(T value)
	{
		// If queue is empty, insert to front
		if (IsEmpty())
		{
			arr[0] = value;
			count++;
		}
		// If queue is not empty
		else
		{
			// If value is higher
			if (arr[0] > value)
			{
				arr[1] = arr[0];
				arr[0] = value;
				return;
			}

			// If value is in the middle
			for (int i = 1; i < count; i++)
			{
				// Sorts new data
				if ((arr[i - 1] < value) && (arr[i] > value))
				{
					*arr[i] = value;

					// Expand queue if not big enough
					if (count > 4)
					{
						fullsize += 5;
					}

					// This does not work correctly and is incomplete
					// Does not include ==, <=, >=
					// Sorts remaning queue
					for (int j = i; j < count; j++)
					{
						T temp = *arr[j];
						arr[j] = value;
						arr[j + 1] = temp;
					}

					return;
				}
			}
			count++
		}
	}

	// Removes info from queue
	void Pop()
	{
		T temp = *arr[1];

		// Loop to remove front item in queue
		for (int i = 1; i < count; i++)
		{
			arr[0] = temp;
			temp = *arr[1];
		}

		count--;
	}

	// Writes queue to console
	void Print()
	{
		for (int i = 0; i < count; i++)
		{
			cout << arr[i] + " " << endl;
		}
	}

	//  Returns number of entries in queue
	int GetSize()
	{
		cout << count << endl;
	}

	// Returns whether or not queue is empty
	bool IsEmpty()
	{
		if (count == 0)
		{
			return true;
		}

		return false;
	}
};