/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 3
*/

#include <iostream>
#include "GenStack.cpp"
#include "fileio.h"

using namespace std;

string getUserInput(string message);

int main(int argc, char** argv) {
  string userInput;
  string line;
  int lineNumber;
  bool foundError;
  bool checkNextFile;
  char expectDelimeter;
  FileIo *files;
  GenStack<char> *stack;

  // make sure user input the file name
  if (argc != 2) {
    cout << " Must provide input file name " << endl;
    return -1;
  }
  userInput = argv[1];

  // main loop to read the file and check the syntax
  // use generic stack to store delimeter and check
  // exit the program if syntax error is found otherwise
  // ask user for another file to check 
  do {
    lineNumber = 0;
    foundError = false;
    checkNextFile = false;

    // Instantiate stack of char type
    stack = new GenStack<char>;
    // Instantiate file processing object
    files = new FileIo();

    // open file for read and exit if file cannot be opened
    if (!files->openFileForRead(userInput)) {
      return -1;
    }

    // read each line from file and process
    while (getline(files->readStream, line)) {
      // check one character at a time to find or check delimeters
      for (int i = 0; i < line.length(); ++i) {
        // push the character into the stack if it is '{', '[', or '('
        if (line[i] == '{' || line[i] == '[' || line[i] == '(') {
          stack->push(line[i]);
        }
        // check character if it is '}', ']', or ')'
        else if (line[i] == '}' || line[i] == ']' || line[i] == ')') {
          // check if delimeter is expected otherwise display error
          // use try and catch to catch the exception from peeking the stack
          // when stack is empty
          try {
            // set the expected delimeter
            if (stack->peek() == '{') {
              expectDelimeter = '}';
            }
            else if (stack->peek() == '[') {
              expectDelimeter = ']';
            }
            else {
              expectDelimeter = ')';
            }

            if (line[i] != expectDelimeter) {
              cout << "Line " << lineNumber << ": expected " << expectDelimeter << " and found " << line[i] << endl;
              foundError = true;
              break;
            }
            stack->pop();
          } catch (GenStackPopEmptyException) {
            cout << "Line " << lineNumber << ": " << "Stack is empty" << endl;
            foundError = true;
            break;
          }
        }
      }
      lineNumber++;
    }
    // end of file check
    if (!stack->isEmpty() && !foundError) {
      if (stack->peek() == '{') {
        expectDelimeter = '}';
      }
      else if (stack->peek() == '[') {
        expectDelimeter = ']';
      }
      else {
        expectDelimeter = ')';
      }
      cout << "Reached end of file: missing " << expectDelimeter << endl;
      foundError = true;
    }

    // If file checking is ok, ask user to for another file to check
    if (!foundError) {
      cout << "No Syntax error is found" << endl;
      do {
        userInput = getUserInput("Do you want to check another file?(y/n) ");
      } while (userInput != "y" && userInput != "n");
      // Ask the file name if user wants to check another file
      if (userInput == "y") {
        userInput = getUserInput("Enter file name: ");
        checkNextFile = true;
      }
    }
    // delete opened stack and files
    delete stack;
    delete files;

  } while (checkNextFile);

  return 0;
}
// Get user input and return as a string
string getUserInput(string message) {
  string userInput;

  cout << message;
  cin >> userInput;

  return userInput;
}
