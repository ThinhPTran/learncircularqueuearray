#include <iostream>
#include <pthread.h>
using namespace std;


// Creating a class named Queue
class Queue
{
  private:
    int queuesize;
    int * A;
    int front, rear;
    pthread_mutex_t mp = PTHREAD_MUTEX_INITIALIZER;

  public:
    // Constructor - set front and rear as -1
    Queue() {
      queuesize = -1;
      A = NULL;
      front = -1;
      rear = -1;
      pthread_mutex_init(&mp,NULL);
    }

    ~Queue() {
      pthread_mutex_lock(&mp);
      cout << "Calling deconstructor" << endl;
      if (A!=NULL) {
        delete [] A;
        A = NULL;
      }
      pthread_mutex_unlock(&mp);
      pthread_mutex_destroy(&mp);
    }

    void Initialize(int inputsize) {
      pthread_mutex_lock(&mp);
      if (inputsize>0) {
        queuesize = inputsize;
        A = new int[queuesize];
        front = -1;
        rear = -1;
      } else {
        cout << "Error: queue size must be positive!!!" << endl;
        pthread_mutex_unlock(&mp);
        return;
      }
      pthread_mutex_unlock(&mp);
    }

    // To check whether Queue is empty or not
    bool IsEmpty()
    {
      if (queuesize<=0) {
        cout << "Must init queue first!!!" << endl;
        return true;
      }
      return (front == -1 && rear == -1);
    }

    // To check whether Queue is full or not
    bool IsFull()
    {
      if (queuesize<=0) {
        cout << "Must init queue first!!!" << endl;
        return false;
      }
      return (rear+1)%queuesize == front ? true: false;
    }

    // Inserts an element in queue at rear end
    void Enqueue(int x)
    {
      pthread_mutex_lock(&mp);
      cout << "Enqueuing " << x << endl;
      if (queuesize<=0) {
        cout << "Must init queue first!!!" << endl;
        pthread_mutex_unlock(&mp);
        return;
      }

      if (IsFull())
      {
        cout << "Error: Queue is Full\n";
        pthread_mutex_unlock(&mp);
        return;
      }

      if (IsEmpty())
      {
        front = rear = 0;
      } else {
        rear = (rear+1)%queuesize;
      }

      A[rear] = x;
      pthread_mutex_unlock(&mp);
    }

    void Dequeue() {
      pthread_mutex_lock(&mp);
      cout << "Dequeuing \n";
      if (queuesize<=0) {
        cout << "Must init queue first!!!" << endl;
        pthread_mutex_unlock(&mp);
        return;
      }

      if (IsEmpty()) {
        cout << "Error: Queue is Empty\n";
        pthread_mutex_unlock(&mp);
        return;
      } else if (front == rear) {
        rear = front = -1;
      } else {
        front = (front + 1)%queuesize;
      }
      pthread_mutex_unlock(&mp);
    }

    int Front()
    {
      if (queuesize<=0) {
        cout << "Must init queue first!!!" << endl;
        return -1;
      }

      if (front == -1)
      {
        cout << "Error: cannot return front from a empty queue\n";
        return -1;
      }
      return A[front];
    }

    void Print() {
      if (queuesize<=0) {
        cout << "Must init queue first!!!" << endl;
        return;
      }

      // Finding number of elements in queue
      int count = (rear+queuesize-front)%queuesize + 1;
      cout <<"Queue: ";
		  
      for(int i = 0; i <count; i++) {
	int index = (front+i) % queuesize; // Index of element while travesing circularly from front
	cout << A[index] << " ";
      }
		  
      cout << endl << endl;
    }
};

int main() {
  Queue Q;
  Q.Initialize(3);
  Q.Enqueue(2); Q.Print();
  Q.Enqueue(4); Q.Print();
  Q.Enqueue(6); Q.Print();
  Q.Enqueue(8); Q.Print();
  Q.Dequeue(); Q.Print();
  Q.Enqueue(10); Q.Print();
}


