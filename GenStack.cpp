/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 3
*/

// create an exception class
class GenStackPopEmptyException {};

// declare generic stack
template <class T>
class GenStack {
private:
  // set default stack size to 128;
  int defaultStackSize = 128;
  int top;
  int size;
  // stack is implemented using dynamic array
  T *stack;

  // redouble the stack size
  void resize();
public:
  GenStack();
  ~GenStack();

  void push(T data);
  T pop();
  T peek();
  bool isEmpty();
  int getSize();
};

// default constructor
template <class T>
GenStack<T>::GenStack() {
  size = defaultStackSize;
  stack = new T[size];
  top = -1;
}
// default destructor
template <class T>
GenStack<T>::~GenStack() {
  delete [] stack;
}
// push data into the stack
template <class T>
void GenStack<T>::push(T data) {
  // double the stack size if it is full
  if (getSize() == size) {
    resize();
  }
  // increment the top by one and then insert the data into the new top location
  stack[++top] = data;
}
// remove and return the data from the top of the stack
template <class T>
T GenStack<T>::pop() {
  // throw exception if stack is empty
  if (isEmpty()) {
    throw GenStackPopEmptyException();
  }
  // decrement the top after top data is returned
  return stack[top--];
}
// return the data from the top of the stack
template <class T>
T GenStack<T>::peek() {
  // throw exception if stack is empty
  if (isEmpty()) {
    throw GenStackPopEmptyException();
  }
  return stack[top];
}
// check if stack is empty
template <class T>
bool GenStack<T>::isEmpty() {
  return (top == -1);
}
// return stack size
template <class T>
int GenStack<T>::getSize() {
  return (top + 1);
}
// create a new array that is double the size of old array
// copy old array to new array
template <class T>
void GenStack<T>::resize() {
  size *= 2;
  T *newStack = new T[size];
  for (int i = 0; i < size / 2; ++i) {
    newStack[i] = stack[i];
  }
  // delete old arrays
  delete [] stack;
  // change the pointer to new array
  stack = newStack;
}
