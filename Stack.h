
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
using namespace std;
struct Position {
    int row;
    int col;

    Position() : row(-1), col(-1) {}  // Default constructor
    Position(int r, int c) : row(r), col(c) {}  // Parameterized constructor
};

template <class Object>
class Stack
{
public:
    Stack( );
    Stack( const Stack & rhs );
    ~Stack( );
    bool isEmpty( ) const;
    bool isFull( ) const;
    void makeEmpty( );
    void pop( );
    void push( const Object & x );
    Object topAndPop( );
    const Object & top( ) const;
    const Stack & operator=( const Stack & rhs );
    
private:
struct ListNode
    {
    Object element;
    ListNode *next;
    ListNode( const Object & theElement, ListNode * n = NULL )
    : element( theElement ), next( n ) { }
    };
    ListNode *topOfStack; // list itself is the stack
};
    
#endif

