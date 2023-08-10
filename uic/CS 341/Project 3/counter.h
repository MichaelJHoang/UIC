/*counter.h*/

//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
//
// The Counter container is a set with no duplicates.  However, it keeps
// a count of how many times an element was inserted, hence the name
// "Counter".  Users of the Counter container can test for set membership,
// as well as obtain an element's count.
// 
// Example:  suppose C is a Counter, and you insert the elements 3, 11, 
// 5, 11, 3, and 11.  Then C contains the elements {3, 5, 11}, where 3's 
// count is 2, 5's count is 1, and 11's count is 3.
//
// Given N elements, search operations are O(lgN), and insert is O(N); these
// are average-time complexities.  In terms of space, the container will 
// consume at most 4N space.
// 

#pragma once

#include <iostream>
#include <iterator>

using std::cout;  // for debug printing:
using std::endl;

template<typename T>
class Counter
{
private:
  
  class iterator
  {
    //
    // TODO
    //
    private:
      
      //node bstArr[];
      
      //int usedIndex = 0;
    
    public:
    
      //public iterator()
      //{
        //for (int x = 0; x < root.size(); x++)
        //{
          //bstArr[x] = new node;
          //bstArr[x] = root;
        //}
      //}
  };
  
  typedef struct NODE
  {
    T data;
    int count;
    NODE *left, *right;
  }node;
  
  node *bst;
  
  int used = 0;
  
public:
  //
  // constructor:
  //
  Counter()
  {
     bst = nullptr;//= (node *) malloc (sizeof(node));
  }
  
  
  //
  // copy constructor:
  //
  Counter(const Counter& other)
  {
    //
    // TODO
    // 
    //bst = new node;
    *bst = *other.bst;
  }
  
  
  //
  // destructor:
  // 
  ~Counter()
  { 
    //
    // TODO
    // 
    
  }


  //
  // size()
  // 
  // Returns the # of elements in the set.
  // 
  // Time complexity: O(1).
  // 
  int size() const
  {
    //
    // DONE
    // 
    return used;
  }
  
  
  //
  // empty()
  //
  // Returns true if the set is empty, false if not.
  // 
  // Time complexity: O(1).
  // 
  bool empty() const
  {
    //
    // DONE
    // 
    return (bst == nullptr || used == 0) ? true : false;
  }
  
  
  //
  // clear()
  //
  // Empties the set, deleting all elements and counts.
  //
  void _clear (node*& root)
  {
    if (root == nullptr)
      return;
    if (root -> left != nullptr)
      _clear (root -> left);
    if (root -> right != nullptr)
      _clear (root -> right);
      
    delete root;
    this -> used = 0;
    
    return;
  }
  void clear()
  {
    //
    // TODO
    //
    _clear (bst);
    
    return;
  }
  
  //
  // [e]
  //
  // Returns true if set contains e, false if not.
  //
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: average-case O(lgN).
  //
  bool searchContain (node*& root, const T&e)
  {
    while (root != nullptr)
    {
      if (e > root -> data && !(e < root -> data))
        return searchContain(root -> right, e);
      else if (e < root -> data && !(e > root -> data))
        return searchContain(root -> left, e);
      else if ((!(e > root -> data) && !(e < root -> data)) || (e == root -> data))
        return true;
    }
    
    return false;
  }
  bool operator[](const T& e)
  {
    //
    // TODO
    // 
    // Binary Search
    return searchContain(bst, e);
  }
  
  //
  // (e)
  // 
  // Returns a count of how many times e has been inserted into the set;
  // the count will be 0 if e has never been inserted.
  // 
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: average-case O(lgN).
  // 
  int searchCount (node*& root, const T&e)
  {
    while (root != nullptr)
    {
      if (e > root -> data && !(e < root -> data))
        return searchCount(root -> right, e);
      else if (e < root -> data && !(e > root -> data))
        return searchCount(root -> left, e);
      else if ((!(e > root -> data) && !(e < root -> data)) || (e == root -> data))
        return root -> count;
    }
    
    return 0;
  }
  int operator()(const T& e)
  {
    //
    // DONE
    // 
    return searchCount(bst, e);
  }
  
  //
  // insert(e)
  // 
  // If e is not a member of the set, e is inserted and e's count set to 0.
  // If e is already in the set, it is *not* inserted again; instead, e's
  // count is increased by 1.  Sets are unbounded in size, and elements are
  // inserted in order as defined by T's < operator; this enables in-order 
  // iteration.
  // 
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: worst-case O(N).
  // Space complexity: 4N.
  //
  node *newNode (const T&e)
  {
    node *temp = new node;
    temp -> data = e;
    temp -> count = 1;
    temp -> left = temp -> right = nullptr;
    
    return temp;
  }
  
  node *_insert (node*& root, const T&e)
  {
    if (root == nullptr)
    {
      used = used + 1;
      return newNode(e);
    }
    
    if (e < root -> data && !(e > root -> data))
      root -> left = _insert(root -> left, e);
    else if (e > root -> data && !(e < root -> data))
      root -> right = _insert(root -> right, e);
    else if ((!(e > root -> data) && !(e < root -> data)) || (e == root -> data))
    {
      root -> count = root -> count + 1;
    }
    
    return root;
  }
  
  void insert(const T& e)
  {
    //
    // TODO
    //
    bst = _insert(bst, e);
    return;
  }
  
  
  // 
  // += e
  //
  // Inserts e into the set; see insert.
  //
  // Time complexity: worst-case O(N).
  // Space complexity: 4N.
  // 
  Counter& operator+=(const T& e)
  {
    //
    // insert e into "this" set:
    //
    this->insert(e);

    // return "this" updated set:
    return *this;
  }
  
  
  //
  // lhs = rhs;
  //
  // Makes a deep copy of rhs (right-hand-side) and assigns into
  // lhs (left-hand-side).  Any existing elements in the lhs
  // are destroyed *before* the deep copy is made.
  // 
  // NOTE: the lhs is "this" object.
  //
  Counter& operator=(const Counter& rhs)
  {
    //
    // NOTE: where is the lhs in the function call?  The lhs operand is 
    // hidden --- it's "this" object.  So think this->operator=(rhs).  
    //

    // check for self-assignment:
    if (this == &rhs)  // S = S;
      return *this;
    
    
    //
    // TODO
    //
    
    /*
    Counter* newLeft = nullptr;
    Counter* newRight = nullptr;
    
    try
    {
      newLeft = new Counter(*rhs.left);
      newRight = new Counter(*rhs.right);
    }
    catch (...)
    {
      delete newLeft;
      delete newRight;
      
      throw;
    }
    
    
    
    delete newLeft;
    delete newRight;
    */
    
    //
    // return "this" updated set:
    //
    return *this;
  }
  

  //
  // begin()
  // 
  // Returns an iterator denoting the first element of the set.  If the 
  // set is empty, begin() == end().  The iterator will advance through
  // the elements in order, as defined by T's < operator.
  //
  iterator begin()
  {
    return iterator(/*TODO*/);
  }
  
  
  //
  // end()
  // 
  // Returns an iterator denoting the end of the iteration space --- i.e.
  // one past the last element of the set.  If the set is empty, then
  // begin() == end().
  // 
  iterator end()
  {
    return iterator(/*TODO*/);
  }

};
