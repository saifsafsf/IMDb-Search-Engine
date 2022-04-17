#include <iostream>
#include <queue>
using namespace std;

/*
    Implementation of ADT BST
    N here refers to the Node class i.e. ActorNode / DirectorNode / MovieNode
    A here refers to the Attribute i.e. Actor / Director / Movie
*/
template <class N, class A>
class BST
{
    // function to find maximum between two numbers
    int maximum(int num1, int num2)
    {
        return (num1 > num2) ? num1 : num2;
    }

public:
    N *_root = NULL;

    BST()
    {
        _root = NULL; // Root is set to NULL on declaration of BST
    }

    // Traverse the tree inorder
    void InOrderTraversal(N *n)
    {
        if (n == NULL)
        {
            return;
        }
        else
        {
            InOrderTraversal(n->_left);
            cout << n->_value->_name << endl;
            InOrderTraversal(n->_right);
        }
    }

    // Traverse the tree in preorder
    void PreOrderTraversal(N *n)
    {
        if (n == NULL)
        {
            return;
        }
        else
        {
            cout << n->_value->_name << endl;
            PreOrderTraversal(n->_left);
            PreOrderTraversal(n->_right);
        }
    }

    // Traverse the tree in postorder
    void PostOrderTraversal(N *n)
    {
        if (n == NULL)
        {
            return;
        }
        else
        {
            PostOrderTraversal(n->_left);
            PostOrderTraversal(n->_right);
            cout << n->_value->_name << endl;
        }
    }

    // Traverse the tree in postorder
    void DescendingOrder(N *n)
    {
        if (n == NULL)
        {
            return;
        }
        else
        {
            DescendingOrder(n->_right);
            cout << n->_value->_name << endl;
            DescendingOrder(n->_left);
        }
    }

    void BreadthFirstTraversal()
    {
        if (_root == NULL)
        {
            return;
        }
        queue<N *> q1;
        q1.push(_root);
        while (!q1.empty())
        {
            N *current = q1.front();
            q1.pop();
            cout << current->_value->_name << endl;
            if (current->_left != NULL)
            {
                q1.push(current->_left);
            }
            if (current->_right != NULL)
            {
                q1.push(current->_right);
            }
        }
    }

    // if value is not found, search returns NULL
    // If value is found, search returns pointer to Node
    N *Search(int value)
    {
        if (_root == NULL)
        {
            return NULL;
        }
        else
        {
            N *current = _root;
            while (current != NULL && current->_value->_releaseYear != value)
            {
                if (value > current->_value->_releaseYear)
                {
                    current = current->_right;
                }
                else
                {
                    current = current->_left;
                }
            }
            return current;
        }
    }

    N *Search(string value)
    {
        if (_root == NULL)
        {
            return NULL;
        }
        else
        {
            N *current = _root;
            while (current != NULL && current->_value->_name.substr(0, value.size()) != value)
            {
                if (value > current->_value->_name)
                {
                    current = current->_right;
                }
                else
                {
                    current = current->_left;
                }
            }
            return current;
        }
    }

    int ComputeTreeHeight(N *n)
    {
        // If node is empty, return zero degree
        if (n == NULL)
        {
            return 0;
        }
        // If node is a leaf, return one degree
        if (n->_left == NULL && n->_right == NULL)
        {
            return 0;
        }
        else
        {
            int height = 1;
            int leftHeight = ComputeTreeHeight(n->_left);
            int rightHeight = ComputeTreeHeight(n->_right);
            int max = maximum(leftHeight, rightHeight); // find which is greater between right and left
            height += max;
            return height;
        }
    }

    int getBalanceFactor(N *n)
    {
        if (n == NULL)
        {
            return 0;
        }
        else
        {

            int adjustment = 0;
            if (n->_left != NULL && n->_right == NULL)
            {
                adjustment++;
            }
            else if (n->_left == NULL && n->_right != NULL)
            {
                adjustment--;
            }
            return adjustment + ComputeTreeHeight(n->_left) - ComputeTreeHeight(n->_right);
        }
    }

    N *findParentNode(N *n)
    {
        if (n == _root)
        {
            return NULL;
        }

        N *current = _root;
        while (current->_left != n && current->_right != n)
        {
            if (current->_value->_name > n->_value->_name)
            {
                current = current->_left;
            }
            else
            {
                current = current->_right;
            }
        }
        return current;
    }

    void leftRotate(N *n)
    {
        if (n->_right == NULL)
        {
            return;
        }
        N *rightSubtree = n->_right;
        n->_right = rightSubtree->_left;
        N *parentOfN = findParentNode(n);
        if (parentOfN == NULL)
        {
            _root = rightSubtree;
        }
        else
        {
            if (parentOfN->_right == n)
            {
                parentOfN->_right = rightSubtree;
            }
            else if (parentOfN->_left == n)
            {
                parentOfN->_left = rightSubtree;
            }
            else
            {
                cout << "ERROR: Parent Node Mismatch" << endl;
            }
        }
        rightSubtree->_left = n;
    }

    void rightRotate(N *n)
    {
        if (n->_left == NULL)
        {
            return;
        }
        N *leftSubtree = n->_left;
        n->_left = leftSubtree->_right;
        N *parentOfN = findParentNode(n);
        if (parentOfN == NULL)
        {
            _root = leftSubtree;
        }
        else
        {
            if (parentOfN->_right == n)
            {
                parentOfN->_right = leftSubtree;
            }
            else if (parentOfN->_left == n)
            {
                parentOfN->_left = leftSubtree;
            }
            else
            {
                cout << "ERROR: Parent Node Mismatch" << endl;
            }
        }
        leftSubtree->_right = n;
    }

    void leftRight(N *z)
    {
        N *x = z->_left;
        N *y = x->_right;

        leftRotate(x);
        rightRotate(z);
    }

    void rightLeft(N *z)
    {
        N *x = z->_right;
        N *y = x->_left;
        rightRotate(x);
        leftRotate(z);
    }

    // Traverse the tree inorder
    void UpdateBalanceFactor(N *n)
    {
        if (n == NULL)
        {
            return;
        }
        else
        {
            UpdateBalanceFactor(n->_left);
            UpdateBalanceFactor(n->_right);
            n->_balanceFactor = getBalanceFactor(n);

            if (n->_balanceFactor > 1)
            {
                if (n->_left != NULL && n->_left->_left != NULL)
                {
                    rightRotate(n);
                }
                else
                {
                    leftRight(n);
                }
                n->_balanceFactor = getBalanceFactor(n);
            }
            else if (n->_balanceFactor < -1)
            {
                if (n->_right != NULL && n->_right->_right != NULL)
                {
                    leftRotate(n);
                }
                else
                {
                    rightLeft(n);
                }
            }
        }
    }

    // Function to insert new node into the tree at correct position
    void insertNode(A *value)
    {
        N *n = new N(value);

        // If root is NULL, inserted value is set as root
        if (_root == NULL)
        {
            
            _root = n;
            return;
        }
        else
        {
            
            // For traversal, two pointers are used
            N *current = _root; // First pointer for current node
            N *previous = NULL; // Second pointer for previous node

            // Loop runs until current becomes NULL, and previous reaches a leaf
            while (current != NULL)
            {
                previous = current;
                // Depending on value current node moves to left or right child
                if (value->_name > current->_value->_name)
                {
                    current = current->_right;
                }
                else
                {
                    current = current->_left;
                }
            }

           

            // When previous is a leaf node, it is checked whether value to be inserted is right or left child
            if (value->_name > previous->_value->_name)
            {
                previous->_right = n;
            }
            else
            {
                previous->_left = n;
            }
        }

        
    }

    // Function to insert new node into the tree at correct position (rating/score wise)
    void insertInAVLRatingWise(A *value)
    {
        N *n = new N(value);

        // If root is NULL, inserted value is set as root
        if (_root == NULL)
        {
            _root = n;
            return;
        }
        else
        {
            // For traversal, two pointers are used
            N *current = _root; // First pointer for current node
            N *previous = NULL; // Second pointer for previous node

            // Loop runs until current becomes NULL, and previous reaches a leaf
            while (current != NULL)
            {
                
                previous = current;
                // Depending on value current node moves to left or right child
                if (value->_imdbScore > current->_value->_imdbScore)
                {
                    current = current->_right;
                }
                else
                {
                    current = current->_left;
                }
            }

            // When previous is a leaf node, it is checked whether value to be inserted is right or left child
            if (value->_imdbScore > previous->_value->_imdbScore)
            {
                previous->_right = n;
            }
            else
            {
                previous->_left = n;
            }
        }
      
      
    }

    // Function to insert new node into the tree at correct position (rating/score wise)
    void insertNodeRatingWise(A *value)
    {
        N *n = new N(value);

        // If root is NULL, inserted value is set as root
        if (_root == NULL)
        {
            _root = n;
            return;
        }
        else
        {
            // For traversal, two pointers are used
            N *current = _root; // First pointer for current node
            N *previous = NULL; // Second pointer for previous node

            // Loop runs until current becomes NULL, and previous reaches a leaf
            while (current != NULL)
            {
                // cout << "in the insert node rating wise(while loop)\n\n";
                previous = current;
                // Depending on value current node moves to left or right child
                if (value->_imdbScore > current->_value->_imdbScore)
                {
                    current = current->_right;
                }
                else
                {
                    current = current->_left;
                }
            }

            // When previous is a leaf node, it is checked whether value to be inserted is right or left child
            if (value->_imdbScore > previous->_value->_imdbScore)
            {
                previous->_right = n;
            }
            else
            {
                previous->_left = n;
            }
        }
       
    }

    // Function to insert new node into the tree at correct position (year wise)
    void insertNodeYearWise(A *value)
    {
        N *n = new N(value);

        // If root is NULL, inserted value is set as root
        if (_root == NULL)
        {
            _root = n;
            return;
        }
        else
        {
            // For traversal, two pointers are used
            N *current = _root; // First pointer for current node
            N *previous = NULL; // Second pointer for previous node

            // Loop runs until current becomes NULL, and previous reaches a leaf
            while (current != NULL)
            {
                previous = current;
                // Depending on value current node moves to left or right child
                if (value->_releaseYear > current->_value->_releaseYear)
                {
                    current = current->_right;
                }
                else
                {
                    current = current->_left;
                }
            }

            // When previous is a leaf node, it is checked whether value to be inserted is right or left child
            if (value->_releaseYear > previous->_value->_releaseYear)
            {
                previous->_right = n;
            }
            else
            {
                previous->_left = n;
            }
        }
        
    }

    void DeleteNode(string value)
    {
        // If value is not found, the function execution stops
        if (Search(value) == NULL)
        {
            return;
        }
        else
        {
            // Two nodes are used for traversal
            N *previous = NULL;
            N *current = _root;
            // When value is found, the loop breaks
            while (current != NULL && current->_value->_name != value)
            {
                previous = current;
                if (value > current->_value->_name)
                {
                    current = current->_right;
                }
                else
                {
                    current = current->_left;
                }
            }

            // There are three cases for node deletion

            // If current node is a leaf
            if (current->_right == NULL && current->_left == NULL)
            {
                // If current is a leaf, find which node left or right current node was and set that to NULL
                if (previous->_right == current)
                {
                    previous->_right = NULL;
                }
                else
                {
                    previous->_left = NULL;
                }
                delete current;
                return;
            }

            // If one of the child of current node is empty
            else if (current->_right == NULL || current->_left == NULL)
            {
                // First check which child (right or left) current node is
                // Then link parent to child of current node
                if (previous->_right == current)
                {
                    if (current->_right != NULL)
                    {
                        previous->_right = current->_right;
                    }
                    else
                    {
                        previous->_right = current->_left;
                    }
                }

                else
                {
                    if (current->_right != NULL)
                    {
                        previous->_left = current->_right;
                    }
                    else
                    {
                        previous->_left = current->_left;
                    }
                }
                delete current;
            }

            // If both child of current node exist
            else
            {
                // Find smallest number in right subtree
                N *nPrevious = NULL;
                N *n = current->_right;
                while (n->_left != NULL)
                {
                    nPrevious = n;
                    n = n->_left;
                }
                nPrevious->_left = NULL;     // Break link of parent with smallest number
                current->_value = n->_value; // current node is set to smallest value in right subtree
                delete n;
            }
        }
        UpdateBalanceFactor(_root);
    }

    void DeleteNode(int value)
    {
        // If value is not found, the function execution stops
        if (Search(value) == NULL)
        {
            return;
        }
        else
        {
            // Two nodes are used for traversal
            N *previous = NULL;
            N *current = _root;
            // When value is found, the loop breaks
            while (current != NULL && current->_value->_releaseYear != value)
            {
                previous = current;
                if (value > current->_value->_releaseYear)
                {
                    current = current->_right;
                }
                else
                {
                    current = current->_left;
                }
            }

            // There are three cases for node deletion

            // If current node is a leaf
            if (current->_right == NULL && current->_left == NULL)
            {
                // If current is a leaf, find which node left or right current node was and set that to NULL
                if (previous->_right == current)
                {
                    previous->_right = NULL;
                }
                else
                {
                    previous->_left = NULL;
                }
                delete current;
                return;
            }

            // If one of the child of current node is empty
            else if (current->_right == NULL || current->_left == NULL)
            {
                // First check which child (right or left) current node is
                // Then link parent to child of current node
                if (previous->_right == current)
                {
                    if (current->_right != NULL)
                    {
                        previous->_right = current->_right;
                    }
                    else
                    {
                        previous->_right = current->_left;
                    }
                }

                else
                {
                    if (current->_right != NULL)
                    {
                        previous->_left = current->_right;
                    }
                    else
                    {
                        previous->_left = current->_left;
                    }
                }
                delete current;
            }

            // If both child of current node exist
            else
            {
                // Find smallest number in right subtree
                N *nPrevious = NULL;
                N *n = current->_right;
                while (n->_left != NULL)
                {
                    nPrevious = n;
                    n = n->_left;
                }
                nPrevious->_left = NULL;     // Break link of parent with smallest number
                current->_value = n->_value; // current node is set to smallest value in right subtree
                delete n;
            }
        }
        UpdateBalanceFactor(_root);
    }
};
