#include "Queue.h"
#include <iostream>
using namespace std;
template <typename T>

// NOTE: A lot of this might not work and that is completely my fault
// I am sorry to whoever is grading this, I promise I'll do better next assignement
int main() 
{
	// I am so sorry I completely blanked on this
	Queue queue(T,5,0);

	queue.IsEmpty();

	queue.Push(1);
	queue.Push(2);
	queue.Push(4);

	queue.Print();
	queue.GetSize();
	queue.IsEmpty();

	queue.Push(3);

	queue.Print();
	queue.GetSize();

	queue.Pop();

	queue.Print();
	queue.GetSize();
}