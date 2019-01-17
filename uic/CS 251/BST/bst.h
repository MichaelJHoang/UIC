        /**************************************************
        * 
        * Name: Jon-Michael Hoang
        * NetID: jhoang6
        * Class: CS 251: Data Structures with John Lillis
        * Program 3: Augmenting and Balancing Binary Search Trees
        * [Due] Date: 4/16/2018
        * 
        **************************************************/

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class bst
{
    public: // public public public public public public public public public public public public public public public public public public public public public public public public public public public public public public public public public
    
        // constructor: initializes an empty tree
        bst ()
        {
            root = nullptr;
        }
    
        // destructor
        ~bst ()
        {
            delete_nodes(root);
        }
    
        /**************************************************
        * 
        * function:    insert ()
        * 
        * desc:        inserts x into BST given by t.
        *              Note that a BST stores a SET -- no
        *              duplicates. Thus, if x is already in
        *              t when the call gets made, no
        *              modifications to the tree result.
        * 
        * note:        helper function does most of the work.
        * 
        **************************************************/
        bool insert (T &x)
        {
            bool success;
            root = _insert(root, x, success);
            return success;
        }
        // end insert ()
        
    
        /**************************************************
        * 
        * function:    contains ()
        * 
        * desc:        returns true or false depending on
        *              whether x is an element of the
        *              BST or not (calling object)
        * 
        * note:        
        * 
        **************************************************/
        bool contains (const T &x)
        {
            bst_node *p = root;
            
            while (p != nullptr)
            {
                if (p -> val == x)
                    return true;
                
                if (x < p -> val)
                    p = p -> left;
                else
                    p = p -> right;
                
                return false;
            }
        }
        // end contains ()
    
    
        /**************************************************
         * 
         * function:    
         * 
         * desc:        
         * 
         * note:        
         * 
        **************************************************/
        bool remove (T &x)
        {
            bool success;
            root = _remove(root, x, success);
            return success;
        }
        // end remove ()
        
        
        /**************************************************
         * 
         * function:    
         * 
         * desc:        
         * 
         * note:        
         * 
        **************************************************/
        int size ()
        {
            return _size(root);
        }
        // end size ()
        
        
        /**************************************************
         * 
         * function:    
         * 
         * desc:        
         * 
         * note:        
         * 
        **************************************************/
        int height ()
        {
            return _height(root);
        }
        // end height ()
        
        
        /**************************************************
         * 
         * function:    
         * 
         * desc:        
         * 
         * note:        
         * 
        **************************************************/
        bool min (T &answer)
        {
            if (root == nullptr)
                return false;
                
            answer = _min_node(root) -> val;
            
            return true;
        }
        // end min ()
        
        
        /**************************************************
         * 
         * function:    
         * 
         * desc:        
         * 
         * note:        
         * 
        **************************************************/
        T max ()
        {
            return _max_node(root) -> val;
        }
        // end max ()
        
        
        /**************************************************
         * 
         * function:    
         * 
         * desc:        "stubs" for assigned TODO functions
         *              below
         * 
         * note:        
         * 
        **************************************************/
        
        //TODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
        vector <T> *to_vector()
        {
            vector <T> *theVector = new vector<T>;
            
            _to_vector(root, theVector);
            
            return theVector;
        }
        // end to_vector ()
        
        
        /**************************************************
         * TODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
         * function:    get_ith ()
         * 
         * desc:        determines the ith smallest element
         *              in t and "passes it back" to the
         *              caller via reference parameter x.
         *              i ranges from 1..n where n is the number
         *              of elements in the tree.
         * 
         *              If i is outside this range, false is returned.
         *              Otherwise, true is returned (indicating
         *              "success").
         * 
         * runtime:     O(h), where h is the tree height
         * 
        **************************************************/
        bool get_ith (int i, T &x)
        {
            int n = size();
            
            if (i < 1 || i > n || n == 0) 
                return false;
                
            _get_ith(root, i, x);
            
            return true;
        }
        
        bool get_ith_SLOW(int i, T &x)
        {
            int n = size();
            int sofar = 0;
            
            if (n)
                return false;
            
            _get_ith_SLOW(root, i, x, sofar);
            
            return true;
        }
        // end get_ith ()
        
        
        /**************************************************
         * TODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
         * function:    num_geq ()
         * 
         * desc:        returns the number of elements in the
         *              tree which are greater than or equal
         *              to x.
         * 
         * runtime:     O(h) where h is the tree height
         * 
        **************************************************/
        int num_geq (const T &x)
        {
            int counter = 0;
            
            return _num_geq(root, x, counter);
        }
        // end num_geq ()
        
        
        /**************************************************
         * 
         * function:    num_geq_SLOW ()
         * 
         * desc:        same functionality as num_geq but
         *              sloooow (linear time)
         * 
         * runtime:     O(n)
         * 
        **************************************************/
        int num_geq_SLOW (const T &x)
        {
            return _num_geq_SLOW (root, x);
        }
        // end num_geq_SLOW ()
        
        
        /**************************************************
         * TODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
         * function:    num_leq
         * 
         * desc:        returns the number of elements in
         *              tree which are less than or equal
         *              to x.
         * 
         * runtime:     O(h), where h is the tree height
         * 
        **************************************************/
        int num_leq (const T &x)
        {
            int counter = 0;
            
            return _num_leq(root, x, counter);
        }
        // end num_leq ()
        
        
        /**************************************************
         * TODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
         * function:    num_leq_SLOW
         * 
         * desc:        returns the number of elements in
         *              tree which are less than or equal
         *              to x.
         * 
         * runtime:     O(n)
         * 
        **************************************************/
        int num_leq_SLOW (const T &x)
        {
            return _num_leq_SLOW(root, x);
        }
        // end num_leq_SLOW ()
        
        
        /**************************************************
         * TODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
         * function:    num_range ()
         * 
         * desc:        returns the number of elements in the
         *              tree which are between min and max
         *              (inclusive).
         * 
         * runtime:     O(h), where h is the tree height
         * 
        **************************************************/
        int num_range (const T &min, const T &max)
        {
            int count = 0;
            
            return _num_range(root, min, max, count);
        }
        // end num_range ()
        
        /**************************************************
         * 
         * function:    num_range_SLOW ()
         * 
         * desc:        same functionality as num_range
         *              but sloooow (linear time)
         * 
         * runtime:     O(n)
         * 
        **************************************************/
        int num_range_SLOW (const T &min, const T &max)
        {
            return _num_range_SLOW(root, min, max);
        }
        // end num_range_SLOW ()
        
        
        void inorder ()
        {
            cout << "\n======== BEGIN INORDER ============\n";
            _inorder(root);
            cout << "\n========  END INORDER  ============\n";
        }
        // end inorder ()
        
        
        void preorder ()
        {
            cout << "\n======== BEGIN PREORDER ============\n";
            _preorder(root, 0);
            cout << "\n========  END PREORDER  ============\n";
        }
        // end preorder ()
        
        
        void postorder ()
        {
            cout << "\n======== BEGIN POSTORDER ============\n";
            _postorder(root, 0);
            cout << "\n========  END POSTORDER  ============\n";
        }
        // end postorder ()
        
        
        static bst *from_sorted_vec (const vector <T> &a, int n)
        {
            bst *t = new bst();
            t -> root = _from_vec(a, 0, n-1);
            return t;
        }
        // end from_sorted_vec ()
        
        
        /**************************************************
         * 
         * function:    num_leaves ()
         * 
         * desc:        returns number of leaves
         * 
         * runtime:     
         * 
        **************************************************/
        int num_leaves ()
        {
            cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
            return 0; 
        }
        // end num_leaves ()
        
        
        /**************************************************
         * TODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
         * function:    num_at_level ()
         * 
         * desc:        returns the number of nodes at specified
         *              level in tree.
         * 
         * note:        the root is at level 0
         * 
         * hint:        recursive helper function?
         * 
        **************************************************/
        int num_at_level (int level)
        {
            cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
            return 0;
        }
        // end num_at_level ()
        
    
    private: // private private private private private private private private private private private private private private private private private private private private private private private private private private private private
    
        struct bst_node
        {
            T val;
            bst_node *left;
            bst_node *right;
            
            int numLeft;
            int numRight;
            
            bst_node (const T &_val = T{}, bst_node * l = nullptr, bst_node *r = nullptr):
            val {_val}, left {l}, right {r}
            { }
        };
        // end STRUCT bst_node
        
        
        // PROGRAMMER IMPLEMENTED FUNCTIONS PROGRAMMER IMPLEMENTED FUNCTIONS PROGRAMMER IMPLEMENTED FUNCTIONS PROGRAMMER IMPLEMENTED FUNCTIONS PROGRAMMER IMPLEMENTED FUNCTIONS PROGRAMMER IMPLEMENTED FUNCTIONS PROGRAMMER IMPLEMENTED FUNCTIONS
        
        
        /**************************************************
         * 
         * function:    _to_vector ()
         * 
         * desc:        helper function
         * 
        **************************************************/
        void _to_vector (bst_node *tree, vector <T> *theVector)
        {
            if (tree = nullptr)
                return;
                
            _to_vector(tree -> left, theVector);
            
            theVector -> push_back(tree -> val);
            
            _to_vector(tree -> right, theVector);
        }
        // end _to_vector ()
        
        
        /**************************************************
         * 
         * function:    _get_ith ()
         * 
         * desc:        helper function
         * 
        **************************************************/
        void _get_ith (bst_node *tree, int num, T &x)
        {
            if (tree == nullptr)
                return;
            
            if (tree -> numLeft + 1 == num)
            {
                x = tree -> val;
                return;
            }
            
            if (tree -> numLeft < num)
            {
                _get_ith(tree -> right, num - tree -> numLeft, x);
            }
            
            _get_ith(tree -> left, num, x);
        }
        // end _get_ith ()
        
        
        /**************************************************
         * 
         * function:    _num_geq ()
         * 
         * desc:        helper function
         * 
        **************************************************/
        int _num_geq (bst_node *tree, const T x, int &counter)
        {
            if (tree == nullptr)
                return counter;
            else if (tree -> val >= x)
            {
                counter = tree -> numRight + (++counter);
                _num_geq(tree -> left, x, counter);
            }
            else
                _num_geq(tree -> right, x, counter);
                
            return counter;
        }
        // end _num_geq ()
        
        
        /**************************************************
         * 
         * function:    _num_leq ()
         * 
         * desc:        helper function
         * 
        **************************************************/
        int _num_leq (bst_node *tree, const T x, int &counter)
        {
            if (tree == nullptr)
                return counter;
            else if (tree -> val <= x)
            {
                counter = tree -> numLeft + (++counter);
                _num_leq(tree -> right, x, counter);
            }
            else
                _num_leq(tree -> left, x, counter);
                
            return counter;
        }
        // end _num_leq ()
        
        
        /**************************************************
         * 
         * function:    _num_range ()
         * 
         * desc:        helper function
         * 
        **************************************************/
        int _num_range (bst_node *tree, T min, T max, int &count)
        {
            if (tree == nullptr)
                return count;
                
            if (tree -> val < min)
                _num_range(tree -> right, min, max, count);
            else if (tree -> val > max)
                _num_range(tree -> left, min, max, count);
            else
            {
                count++;
                _num_range(tree -> right, min, max, count);
                _num_range(tree -> left, min, max, count);
            }
            
            return count;
        }
        // end _num_range ()
        
        /*
        bst_node *rotateRight (bst_node *y)
        {
            bst_node *x = y -> left;
            bst_node *temp = x -> right;
            
            // rotate
            x -> right = y;
            y -> left = temp;
            
            // update heights
            y -> height = max(height(y -> left), height(y -> right)) + 1;
            x -> height = max(height(x -> left), height(x -> right)) + 1;
            
            // return new root
            return x;
        }
        
        bst_node *rotateLeft (bst_node *x)
        {
            bst_node *y = x -> right;
            bst_node *temp = y -> left;
            
            // rotate
            y -> left = x;
            x -> right = temp;
            
            // update heights
            x -> height = max(height(x -> left), height(x -> right)) + 1;
            y -> height = max(height(y -> left), height(y -> right)) + 1;
            
            // return new root
            return y;
        }
        
        int getBalance (bst_node *tree)
        {
            if (tree == NULL)
                return 0;
            return height(tree -> left) - height (tree -> right);
        }
        */
        
        // END PROGRAMMER IMPLEMENTED FUNCTIONS END PROGRAMMER IMPLEMENTED FUNCTIONS END PROGRAMMER IMPLEMENTED FUNCTIONS END PROGRAMMER IMPLEMENTED FUNCTIONS END PROGRAMMER IMPLEMENTED FUNCTIONS END PROGRAMMER IMPLEMENTED FUNCTIONS
        
        
        /**************************************************
         * 
         * desc:        helper function which recursively 
         *              deallocates nodes in a tree.
         * 
        **************************************************/
        static void delete_nodes (bst_node *r)
        {
            if (r == nullptr)
                return;
            
            delete_nodes(r -> left);
            delete_nodes(r -> right);
            
            delete r;
        }
        // end delete_nodes ()
        
        
        /**************************************************
         * 
         * function:    insert ()
         * 
         * desc:        recursive helper function inserting
         *              x into binary search tree rooted at
         *              r
         * 
         * returns:     pointer to root of tree after insertion
         * 
         * notes:       if x is already in the tree, no
         *              modifications are made.
         * 
        **************************************************/
        bst_node *_insert (bst_node *r, T &x, bool &success)
        {
            
            if (r == nullptr)
            {
                success = true;
                return new bst_node(x, nullptr, nullptr);
            }
            
            if (r -> val == x)
            {
                success = false;
                return r;
            }
            
            if (x < r -> val)
            {
                r -> left = _insert(r -> right, x, success);
                r -> numLeft++;
                return r;
            }
            else
            {
                r -> right = _insert(r -> right, x, success);
                r -> numRight++;
                return r;
            }
            
            
            /*
            // 1. perform normal BST insertion
            if (r == nullptr)
                return (newThing(x));
            
            if (x < r -> val)
                r -> left = _insert(r -> left, x, success);
            else if (x > r -> val)
                r -> right = _insert(r -> right, x, success);
            else
                return r;
                
            // 2. update height of ancestor node
            r -> height = 1 + max(height(r -> left), height(r -> right));
            
            // 3. get the balance factor of ancestor node to check whether this node
            //    became unbalanced
            int balance = getBalance(r);
            
            // if node becomes unbalanced, then there are 4 cases
            
            // left left case
            if (balance < 1 && x < r -> left -> val)
                return rotateRight(r);
            
            // right right case
            if (balance < -1 && x > r -> right -> val)
                return rotateLeft(r);
                
            // left right case
            if (balance > 1 && x > r -> left -> val)
            {
                r -> left = rotateLeft(r -> left);
                return rotateRight(r);
            }
            
            // right left case
            if (balance < -1 && x < r -> right -> val)
            {
                r -> right = rotateRight(r -> right);
                return rotateLeft(r);
            }
            
            // return the unchanged node pointer
            return r;
            */
        }
        // end insert ()
        
        
        /**************************************************
         * 
         * function:    _min_node ()
         * 
         * desc:        
         * 
         * returns:     pointer to node containing smallest
         *              value in tree rooted at r
         * 
        **************************************************/
        static bst_node *_min_node (bst_node *r)
        {
            if (r == nullptr)
                return nullptr; // should never happen!
            
            while (r -> left != nullptr)
                r = r -> left;
            
            return r;
        }
        // end _min_node ()
        
        
        /**************************************************
         * 
         * function:    _max_node ()
         * 
         * desc:        
         * 
         * returns:     pointer to node containing highest
         *              value in tree rooted at r
         * 
        **************************************************/
        static bst_node *_max_node (bst_node *r)
        {
            if (r == nullptr)
                return nullptr; // should never happen!
            
            while (r -> right != nullptr)
                r = r-> right;
            
            return r;
        }
        // end _max_node ()
        
        
        /**************************************************
         * 
         * function:    _remove ()
         * 
         * desc:        recursive helper function for node
         *              removal
         * 
         * returns:     root of the resulting tree after
         *              removal.
         * 
        **************************************************/
        static bst_node *_remove (bst_node *r, T &x, bool &success)
        {
            bst_node *tmp;
            bool sanity;
            
            if (r == nullptr)
            {
                success = false;
                return nullptr;
            }
            
            if (r -> val == x)
            {
                success = true;
                
                if (r -> left == nullptr)
                {
                    tmp = r -> left;
                    delete r;
                    return tmp;
                }
                
                // if we get here, r has two children
                r -> val = _min_node(r -> right) -> val;
                r -> right = _remove(r -> right, r -> val, sanity);
                
                if (!sanity)
                    cerr << "ERROR:  remove() failed to delete promoted value?\n";
                return r;
            }
            
            if (x < r -> val)
            {
                r -> left = _remove(r -> left, x, success);
                r -> numLeft--;
            }
            else
            {
                r -> right = _remove(r -> right, x, success);
                r -> numRight--;
            }
            return r;
        }
        // end _remove ()
        
        
        /**************************************************
         * 
         * function:    _size ()
         * 
         * desc:        recursive helper function to compute
         *              size of tree rooted at r
         * 
        **************************************************/
        static int _size (bst_node *r)
        {
            if (r == nullptr)
                return 0;
            return _size(r -> left) + _size(r -> right) + 1;
        }
        // end _size ()
        
        
        /**************************************************
         * 
         * function:    _height ()
         * 
         * desc:        ???
         * 
        **************************************************/
        static int _height (bst_node *r)
        {
            int l_h, r_h;
            
            if (r == nullptr)
                return -1;
                
            l_h = _height(r -> left);
            r_h = _height(r -> right);
            
            return 1 + (l_h > r_h ? l_h : r_h);
        }
        // end _height ()
        
        
        /**************************************************
         * 
         * function:    _get_ith_SLOW ()
         * 
         * desc:        ???
         * 
        **************************************************/
        static void _get_ith_SLOW (bst_node *t, int i, T &x, int &sofar)
        {
            if (t == nullptr)
                return;
            
            _get_ith_SLOW (t -> left, i, x, sofar);
            
            if (sofar == i)
                return;
            sofar++;
            
            if (sofar == i)
            {
                x = t -> val;
                return;
            }
            
            _get_ith_SLOW (t -> right, i, x, sofar);
        }
        // end _get_ith_SLOW ()
        
        
        /**************************************************
         * 
         * function:    _num_geq_SLOW ()
         * 
         * desc:        ???
         * 
        **************************************************/
        static int _num_geq_SLOW (bst_node *t, const T &x)
        {
            int total;
            
            if (t == nullptr)
                return 0;
            total = _num_geq_SLOW(t -> left, x) + _num_geq_SLOW(t -> right, x);
            
            if (t -> val >= x)
                total++;
            
            return total;
        }
        // end _num_geq_SLOW ()
        
        
        /**************************************************
         * 
         * function:    _num_leq_SLOW ()
         * 
         * desc:        ???
         * 
        **************************************************/
        static int _num_leq_SLOW (bst_node *t, const T &x)
        {
            int total;
            
            if (t == nullptr)
                return 0;
            total = _num_leq_SLOW(t -> left, x) + _num_leq_SLOW(t -> right, x);
            
            if (t -> val <= x)
                total++;
            
            return total;
        }
        // end _num_leq_SLOW ()
        
        
        /**************************************************
         * 
         * function:    _num_range_SLOW ()
         * 
         * desc:        ???
         * 
        **************************************************/
        static int _num_range_SLOW (bst_node *t, const T &min, const T &max)
        {
            int total;
            
            if (t == nullptr)
                return 0;
            total =_num_range_SLOW(t->left, min, max) + _num_range_SLOW(t->right, min, max);
            
            if (t -> val >= min && t -> val <= max)
                total++;
                
            return total;
        }
        // end _num_range_SLOW ()
        
        
        /**************************************************
         * 
         * function:    indent ()
         * 
         * desc:        ???
         * 
        **************************************************/
        static void indent (int m)
        {
            int i;
            
            for(i=0; i<m; i++)
                cout << "-";
        }
        // end indent ()
        
        
        /**************************************************
         * 
         * function:    _inorder ()
         * 
         * desc:        ???
         * 
        **************************************************/
        static void _inorder (bst_node *r)
        {
            if(r==nullptr)
                return;
            
            _inorder(r->left);
            
            cout << "[ " << r->val << " ]\n";
            
            _inorder(r->right);
        }
        // end _inorder ()
        
        
        /**************************************************
         * 
         * function:    _preorder ()
         * 
         * desc:        ???
         * 
        **************************************************/
        static void _preorder (bst_node *r, int margin)
        {
            if(r==nullptr)
            {
                indent(margin);
                cout << " nullptr \n";
            }
            else
            {
                indent(margin);
                cout << "[ " << r->val << " ]\n";
                _preorder(r->left, margin + 3);
                _preorder(r->right, margin + 3);
            }
        }
        // end _preorder ()
        
        
        /**************************************************
         * TODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
         * function:    _postorder()
         * 
         * TODO:        complete the (recursive) helper
         *              function for the post-order
         *              traversal.
         *              REMEMBER: the indentation needs to be
         *              proportional to the height of the node!
         * 
        **************************************************/
        static void _postorder (bst_node *r, int margin)
        {
            //cout << "\n   WARNING:  POSTORDER UNIMPLEMENTED...\n";
            if (r == nullptr)
            {
                indent(margin);
                cout << " nullptr \n";
            }
            else
            {
                indent(margin);
                
                // recurse on left subtree
                _postorder(r -> left, margin + 2);
                
                // recurse on right subtree
                _postorder(r -> right, margin + 2);
                
                // deal with the node
                printf("[ %d ]", r -> val);
            }
        }
        // end _postorder ()
        
        
        /**************************************************
         * 
         * function:    _from_vec ()
         * 
         * desc:        recursive helper function _from_vec,
         *              used by bst_from_sorted_arr(...).
         *              The function must return a sub tree
         *              that is perfectly balanced, given
         *              a sorted array of elements a.
         * 
        **************************************************/
        static bst_node *_from_vec (const vector <T> &a, int low, int hi)
        {
            int m;
            bst_node *root;
            
            if(hi < low)
                return nullptr;
            
            m = (low+hi)/2;
            
            root = new bst_node(a[m]);
            
            root->left  = _from_vec(a, low, m-1);
            root->right = _from_vec(a, m+1, hi);
            
            return root;
        }
        // end _from_vec ()
        
        
        bst_node *root;
};
// end class bst

#endif