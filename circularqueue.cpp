#include <iostream>
using namespace std;


// Creating a class named Queue
class Queue
{
  private:
    int queuesize;
    int * A;
    int front, rear;

  public:
    // Constructor - set front and rear as -1
    Queue() {
      queuesize = 3;
      A = new int[queuesize];
      front = -1;
      rear = -1;
    }

    ~Queue() {
      cout << "Calling deconstructor" << endl;
      delete [] A;
    }

    // To check whether Queue is empty or not
    bool IsEmpty()
    {
      return (front == -1 && rear == -1);
    }

    // To check whether Queue is full or not
    bool IsFull()
    {
      return (rear+1)%queuesize == front ? true: false;
    }

    // Inserts an element in queue at rear end
    void Enqueue(int x)
    {
      cout << "Enqueuing " << x << " \n";
      if (IsFull())
      {
        cout << "Error: Queue is Full\n";
        return;
      }

      if (IsEmpty())
      {
        front = rear = 0;
      } else {
        rear = (rear+1)%queuesize;
      }

      A[rear] = x;
    }

    void Dequeue() {
      cout << "Dequeuing \n";
      if (IsEmpty()) {
        cout << "Error: Queue is Empty\n";
        return;
      } else if (front == rear) {
        rear = front = -1;
      } else {
        front = (front + 1)%queuesize;
      }
    }

    int Front()
    {
      if (front == -1)
      {
        cout << "Error: cannot return front from a empty queue\n";
        return -1;
      }
      return A[front];
    }

    void Print()
	  {
		  // Finding number of elements in queue
		  int count = (rear+queuesize-front)%queuesize + 1;
		  cout<<"Queue: ";
		  for(int i = 0; i <count; i++)
		  {
			  int index = (front+i) % queuesize; // Index of element while travesing circularly from front
			  cout<<A[index]<<" ";
		  }
		  cout<<"\n\n";
    }
};

int main() {
  Queue Q;
  Q.Enqueue(2); Q.Print();
  Q.Enqueue(4); Q.Print();
  Q.Enqueue(6); Q.Print();
  Q.Enqueue(8); Q.Print();
  Q.Dequeue(); Q.Print();
  Q.Enqueue(10); Q.Print();
}


