#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Queue
{
public:
	Queue(int size):start_(0)
					,end_(0)
					,size_(0)
					,container_(size, T()){};
	Queue():start_(0)
			,end_(0)
			,size_(0)
			,container_(10,T()){}
	void push(const T& var);
	T pop();
	void print();
private:
	int start_;
	int end_;
	int size_;
	vector<T> container_;
};

template<typename T>
void Queue<T>::push(const T& var)
{
	if(size_++ == container_.capacity()){
		cout << "the queue is full" << endl;
		return;
	}
	container_[end_] = var;	
	end_ = end_ > container_.capacity()-1 ? 0 : end_+1;
}

template<typename T>
T Queue<T>::pop()
{
	if(size_-- == 0){
		cout << "the queue is empity" << endl;
		return T();
	}

	T tmp = container_[start_];
	start_ = start_ > container_.capacity() -1 ? 0 : start_+1;
	return tmp;
}

template<typename T>
void Queue<T>::print()
{	
	typename vector<T>::iterator it = container_.begin();
	for(; it != container_.end(); ++it)
		cout << *it << endl;
}
