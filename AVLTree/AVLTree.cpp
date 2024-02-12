// File: AVLTree.cpp
// Author: Matthew Martinez
// Description: File contains constructor for an AVL tree and common 
// functions to interact with the tree.

#include <iostream>
#include <limits.h>
#include "AVLTree.h"
using namespace std;

// Constructor for AVLTree class
AVLTree::AVLTree(){
  root = nullptr;
  size = 0;
}

/*Description: Function returns pointer to AVLTree root.
  Parameters: N/A
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::getRoot(){
  if (root == nullptr) {
  return nullptr;
  }

  return root;
}

/*Description: Function returns size of AVLTree
  Parameters: N/A
  Returns: int size
*/
int AVLTree::getSize(){
  return size;
}

/*Description: Function returns pointer to node of AVLTree containing val provided. 
  Else returns nullptr
  Parameters: int val
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::search(int val){
  if (root != nullptr) {
    return search(root, val);
  }

  return nullptr;
}

/*Description: Function returns pointer to node of AVLTree containing val provided. 
  Else returns nullptr
  Parameters: std::shared_ptr<AVLNode> n, int val
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::search(std::shared_ptr<AVLNode> n, int val){
  if (n != nullptr) {
    if (n->value == val) {
      return n;
    } else if (n->value < val) {
        return search(n->right,val);
      } else {
          return search(n->left,val);
        }
  }

  return nullptr;
}

/*Description: Function returns pointer to node of AVLTree containing 
  smallest value.
  Parameters: N/A
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::minimum(){
  if (root != nullptr) {
    return minimum(root);
  }
  return nullptr;
}

/*Description: Function returns pointer to node of AVLTree containing 
  smallest value.
  Parameters: std::shared_ptr<AVLNode> n
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::minimum(std::shared_ptr<AVLNode> n){
  if (n->left != nullptr) {
    return minimum(n->left);
  }
  return n;
}

/*Description: Function returns pointer to node of AVLTree containing 
  largest value.
  Parameters: N/A
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::maximum(){
  if (root != nullptr) {
    return maximum(root);
  }
  return nullptr;
}

/*Description: Function returns pointer to node of AVLTree containing 
  largest value.
  Parameters: std::shared_ptr<AVLNode> n
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::maximum(std::shared_ptr<AVLNode> n){
  if (n->right != nullptr) {
    return maximum(n->right);
  }
  return n;
}


// int getHeight(std::shared_ptr<AVLNode> n){
//   // You are not required to implement this function though it may be useful
//   return -1;
// }

// int getBalanceFactor(std::shared_ptr<AVLNode> n){
//   // You are not required to implement this function though it may be useful
//   return -99;
// }

/*Description: Function calls insertValue(std::shared_ptr<AVLNode> n, int val).
  Parameters: N/A
  Returns: N/A
*/
void AVLTree::insertValue(int val){
  insertValue(root,val);
}

/*Description: Function inserts node of given value into AVLTree. Function
  then returns AVLNode pointer inserted. If no insertion occurs, returns n.
  Parameters: std::shared_ptr<AVLNode> n, int val
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::insertValue(std::shared_ptr<AVLNode> n, int val){
  //Finds appropriate empty leaf to insert node into or skipped
  // if value already has a node.
  if (root == nullptr) {
    root = std::shared_ptr<AVLNode>(new AVLNode(val));
    size = size + 1;
    return root;
  } else if (n->value < val) {
      if (n->right == nullptr) {
        n->right = std::shared_ptr<AVLNode>(new AVLNode(val));
        n->right->parent = n;
        size = size + 1;       
      } else {
          n->right = insertValue(n->right,val);
        }
    } else if (n->value > val) {
        if (n->left == nullptr) {
          n->left = std::shared_ptr<AVLNode>(new AVLNode(val));
          n->left->parent = n;
          size = size + 1;
        } else {
            n->left = insertValue(n->left,val);
          }
      }

  //update height of n
  if (n->right != nullptr && n->left != nullptr) {
    n->height = max(n->right->height, n->left->height) + 1;
  } else if (n->right == nullptr && n->left == nullptr) {
      n->height = 0;
    } else if (n->right == nullptr) {
        n->height = (n->left->height) + 1;
      } else {
          n->height = (n->right->height) + 1;
        }         

  //update balance factor of n
  if (n->right != nullptr && n->left != nullptr) {
    n->balanceFactor = (n->right->height) - (n->left->height);     
  } else if (n->right == nullptr && n->left == nullptr) {
      n->balanceFactor = 0;
    } else if (n->right == nullptr) { 
        n->balanceFactor = -1 - (n->left->height);
      } else {
          n->balanceFactor = (n->right->height) + 1; 
        }
          
  // rebalance n
  n = rebalance(n);  
  while (root->parent != nullptr) {
    root = root->parent;
  }  
  return n;
}

/*Description: Function calls deleteValue(std::shared_ptr<AVLNode> n, int val).
  Parameters: int val
  Returns: void
*/
void AVLTree::deleteValue(int val){
  deleteValue(root, val);
}

/*Description: Function returns pointer to node with minimum value of
  subtree of root passed to function (n).
  Parameters: std::shared_ptr<AVLNode> n
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> deleteValueMinimum(std::shared_ptr<AVLNode> n) {
  if (n->left != nullptr) {
    return deleteValueMinimum(n->left);
  }
  return n;
}

/*Description: Function deletes node containing given value. Else returns nullptr.
  Function returns pointer to AVLnode.
  Parameters: std::shared_ptr<AVLNode> n, int val
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::deleteValue(std::shared_ptr<AVLNode> n, int val){
  // Search for node containing value to be deleted.
  if (n != nullptr) {
    if (val < n->value) {
      n->left = deleteValue(n->left, val);
    } else if (val > n->value) {
        n->right = deleteValue(n->right, val);
      } else if (n->left == nullptr && n->right == nullptr) {
        // Node to be deleted has no children. Contains 
        // two cases for node being root or not root.
          if (n == root) {
            root = nullptr;
            n = root;
            size = size -1;
          } else {
              n = nullptr;
              size = size - 1;
            }
        } else if (n->left == nullptr) {
          // Node to be deleted has one child (right child).
          // Contains two cases for node being root or not root.
            if (n == root) {
              root = root->right;
              size = size -1;
              n = root;
              root->parent = nullptr;
            } else {
                std::shared_ptr<AVLNode> temp = n->right;
                if (n->parent->right != nullptr) {
                  if (n->parent->right->value == val) {
                    n->right->parent = n->parent;
                    n->parent->right = n->right; 
                  }
                } else {  
                    n->right->parent = n->parent;
                    n->parent->left = n->right;
                  }
                n = temp;
                size = size -1;
              }
          } else if (n->right == nullptr) {
            // Node to be deleted has one child (left child).
            // Contains two cases for node being root or not root.
              if (n == root) {
                root = root->left;
                size = size - 1;   
                n = root;
                root->parent = nullptr;
              } else {
                  std::shared_ptr<AVLNode> temp = n->left;
                  if (n->parent->right != nullptr) {
                    if (n->parent->right->value == val) {
                      n->left->parent = n->parent;
                      n->parent->right = temp;
                    } else {
                        n->left->parent = n->parent;
                        n->parent->left = n->left;
                      }  
                  } else {
                      n->left->parent = n->parent;
                      n->parent->left = n->parent->left->left;
                    }
                  n = temp;
                  size = size -1;
                  } 
            } else {
                // Node to delete has two children. Replace node to delete value with
                // smallest value in right subtree. Then call deleteValue for minimum 
                // value in right subtree.
                std::shared_ptr<AVLNode> minimumInRightTree = deleteValueMinimum(n->right);  
                n->value = minimumInRightTree->value;
                if (n == root && minimumInRightTree == n->right) {
                  if (root->left !=nullptr) {
                    root->left->parent = root->right;
                    root->right->left = root->left;
                  }
                  
                  root = root->right;
                  root->parent = nullptr;
                  n = root;
                  size = size - 1;
                } else {
                    n->right = deleteValue(n->right, n->value);
                  }              
              }  
  }

  if (n == nullptr) {
    return n;
  }

  // update heights and balance factors of n
  if (n->left == nullptr && n->right == nullptr) {
    n->height = 0;
    n->balanceFactor = 0;
  } else if (n->left == nullptr) {
      n->height = n->right->height + 1;
      n->balanceFactor = n->right->height + 1;
    } else if (n->right == nullptr) {
        n->height = n->left->height + 1;
        n->balanceFactor = -1 - n->left->height; 
      } else {
          n->height = max(n->left->height, n->right->height) + 1;
          n->balanceFactor = n->right->height - n->left->height;
        }
 
  n = rebalance(n);
  
  // update potential root changes
  while (root->parent != nullptr) {
    root = root->parent;
  }  
  return n;
}

/*Description: Function adjusts heights and balance factors of appropriate nodes
  in AVLTree. Returns pointer to node input.
  Parameters: std::shared_ptr<AVLNode> n
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::rebalance(std::shared_ptr<AVLNode> n){
  if (n->right == nullptr && n->left == nullptr) {
    return n;
  }
  
  if (n->balanceFactor == 2 && n->right->balanceFactor >= 0) {
    return rotateLeft(n);
  } else if (n->balanceFactor == 2 && n->right->balanceFactor < 0) {
      return rotateRightLeft(n);
    } else if (n->balanceFactor == -2 && n->left->balanceFactor <= 0) {
        return rotateRight(n);
      } else if (n->balanceFactor == -2 && n->left->balanceFactor > 0) {
          return rotateLeftRight(n);
        } else {
            return n;
          }

  return n;
}

/*Description: Function rotates AVLtree node left. Function returns
  pointer to new root of subtree.
  Parameters: std::shared_ptr<AVLNode> n
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::rotateLeft(std::shared_ptr<AVLNode> n){
  std::shared_ptr<AVLNode> temp = n->right;
  n->right = temp->left;

  if (n->right != nullptr) {
    n->right->parent = n;
  }

  // update height and balance factor of n
  if (n->right == nullptr && n->left == nullptr) {
    n->height = 0;
    n->balanceFactor = 0;
  } else if (n->right == nullptr) {
      n->height = n->left->height + 1;
      n->balanceFactor = -1 - n->left->height;
    } else if (n->left == nullptr) {
        n->height = n->right->height + 1;
        n->balanceFactor = n->right->height + 1;
      } else {
          n->height = max(n->right->height, n->left->height) + 1;
          n->balanceFactor = n->right->height - n->left->height;
        }

  temp->left = n;
  temp->parent = n->parent;
  n->parent = temp;

  if (temp->parent != nullptr) {
    if (temp->parent->right != nullptr) {
      if (temp->parent->right == temp) {
        temp->parent->right = temp;
      }
    } else if (temp->parent->left !=nullptr) {
        if (temp->parent->left == temp) {
          temp->parent->left = temp;
        }
      }
  }

  // update height and balance factor temp
  if (temp->right == nullptr && temp->left == nullptr) {
    temp->height == 0;
    temp->balanceFactor = 0;
  } else if (temp->right == nullptr) {
      temp->height = temp->left->height + 1;
      temp->balanceFactor = -1 - temp->left->height;
    } else if (temp->left == nullptr) {
        temp->height = temp->right->height + 1;
        temp->balanceFactor = temp->right->height + 1;
      } else {
          temp->height = max(temp->right->height, temp->left->height) + 1;
          temp->balanceFactor = temp->right->height - temp->left->height;
        }

  return temp;
}

  


/*Description: Function rotates AVLtree node right. Function returns
  pointer to new root of subtree.
  Parameters: std::shared_ptr<AVLNode> n
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::rotateRight(std::shared_ptr<AVLNode> n){
  std::shared_ptr<AVLNode> temp = n->left;
  n->left = temp->right;
  if (n->left != nullptr) {
    n->left->parent = n;
  }

  // update height and balance factor of n
  if (n->right == nullptr && n->left == nullptr) {
    n->height = 0;
    n->balanceFactor = 0;
  } else if (n->right == nullptr) {
      n->height = n->left->height + 1;
      n->balanceFactor = -1 - n->left->height;
    } else if (n->left == nullptr) {
        n->height = n->right->height + 1;
        n->balanceFactor = n->right->height + 1;
      } else {
          n->height = max(n->right->height, n->left->height) + 1;
          n->balanceFactor = n->right->height - n->left->height;
        }
  
  temp->right = n;
  temp->parent = n->parent;
  n->parent = temp;
  
  if (temp->parent != nullptr) {
    if (temp->parent->right !=nullptr) {
      if (temp->parent->right == temp) {
        temp->parent->right = temp;
      }
    } else if (temp->parent->left !=nullptr) {
        if (temp->parent->left == temp) {
          temp->parent->left = temp;
        }
      }
  }

  // update height and balance factor of temp
  if (temp->right == nullptr && temp->left == nullptr) {
    temp->height == 0;
    temp->balanceFactor = 0;
  } else if (temp->right == nullptr) {
      temp->height = temp->left->height + 1;
      temp->balanceFactor = -1 - temp->left->height;
    } else if (temp->left == nullptr) {
        temp->height = temp->right->height + 1;
        temp->balanceFactor = temp->right->height + 1;
      } else {
          temp->height = max(temp->right->height, temp->left->height) + 1;
          temp->balanceFactor = temp->right->height - temp->left->height;
        }   

  return temp;
}

/*Description: Function rotates AVLtree node left then right. Function returns
  pointer to new root of subtree.
  Parameters: std::shared_ptr<AVLNode> n
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::rotateLeftRight(std::shared_ptr<AVLNode> n){
  //rotate left
  std::shared_ptr<AVLNode> temp1 = n->left, temp2 = n->left->right;
  temp1->right = temp2->left;

  if (temp1->right != nullptr) {
    temp1->right->parent = temp1;
  }

  //update height and balance factor of x
  if (temp1->right == nullptr && temp1->left == nullptr) {
    temp1->height = 0;
    temp1->balanceFactor = 0;
  } else if (temp1->right == nullptr) {
      temp1->height = temp1->left->height + 1;
      temp1->balanceFactor = -1 - temp1->left->height;
    } else if (temp1->left == nullptr) {
        temp1->height = temp1->right->height + 1;
        temp1->balanceFactor = temp1->right->height + 1;
      } else {
          temp1->height = max(temp1->right->height, temp1->left->height) + 1;
          temp1->balanceFactor = temp1->right->height - temp1->left->height;
        }

  temp2->left = temp1;
  temp1->parent = temp2;
  n->left = temp2;
  temp2->parent = n;

  //rotate right
  n->left = temp2->right;
  if (temp2->right != nullptr) {
    temp2->right->parent = n;
  }
  
  //update height and balance factor of y
  if (n->right == nullptr && n->left == nullptr) {
    n->height = 0;
    n->balanceFactor = 0;
  } else if (n->right == nullptr) {
      n->height = n->left->height + 1;
      n->balanceFactor = -1 - n->left->height;
    } else if (n->left == nullptr) {
        n->height = n->right->height + 1;
        n->balanceFactor = n->right->height + 1;
      } else {
          n->height = max(n->right->height, n->left->height) + 1;
          n->balanceFactor = n->right->height - n->left->height;
        }

  temp2->right = n;
  temp2->parent = n->parent;
  n->parent = temp2;

  if (temp2->parent != nullptr) {
    if (temp2->parent->right !=nullptr) {
      if (temp2->parent->right == temp2) {
        temp2->parent->right = temp2;
      }
    } else if (temp2->parent->left !=nullptr) {
        if (temp2->parent->left == temp2) {
          temp2->parent->left = temp2;
        }
      }
  }

  //update height and balance factor of z
  if (temp2->right == nullptr && temp2->left == nullptr) {
    temp2->height = 0;
    temp2->balanceFactor = 0;
  } else if (temp2->right == nullptr) {
      temp2->height = temp2->left->height + 1;
      temp2->balanceFactor = -1 - temp2->left->height;
    } else if (temp2->left == nullptr) {
        temp2->height = temp2->right->height + 1;
        temp2->balanceFactor = temp2->right->height - 1;
      } else {
          temp2->height = max(temp2->right->height, temp2->left->height) + 1;
          temp2->balanceFactor = temp2->right->height - temp2->left->height;
        }

  return temp2;
}

/*Description: Function rotates AVLtree node right then left. Function returns
  pointer to new root of subtree.
  Parameters: std::shared_ptr<AVLNode> n
  Returns: std::shared_ptr<AVLNode>
*/
std::shared_ptr<AVLNode> AVLTree::rotateRightLeft(std::shared_ptr<AVLNode> n){
  // rotate right
  std::shared_ptr<AVLNode> temp1 = n->right, temp2 = n->right->left;
  temp1->left = temp2->right;
  if (temp1->left != nullptr) {
    temp1->left->parent = temp1;
  }

  //update height and balance factors x
  if (temp1->right == nullptr && temp1->left == nullptr) {
    temp1->height = 0;
    temp1->balanceFactor = 0;
  } else if (temp1->right == nullptr) {
      temp1->height = temp1->left->height + 1;
      temp1->balanceFactor = -1 - temp1->left->height;
    } else if (temp1->left == nullptr) {
        temp1->height = temp1->right->height + 1;
        temp1->balanceFactor = temp1->right->height + 1;
      } else {
          temp1->height = max(temp1->right->height, temp1->left->height) + 1;
          temp1->balanceFactor = temp1->right->height - temp1->left->height;
        }

  temp2->right = temp1;

  temp1->parent = temp2;
  
  n->right = temp2;
  temp2->parent = n;


  //rotate left
  n->right = temp2->left;
  if (temp2->left != nullptr) {
    temp2->left->parent = n;
  }
  
  //update height and balance factor of y
  if (n->right == nullptr && n->left == nullptr) {
    n->height = 0;
    n->balanceFactor = 0;
  } else if (n->right == nullptr) {
      n->height = n->left->height + 1;
      n->balanceFactor = -1 - n->left->height;
    } else if (n->left == nullptr) {
        n->height = n->right->height + 1;
        n->balanceFactor = n->right->height + 1;
      } else {
          n->height = max(n->right->height, n->left->height) + 1;
          n->balanceFactor = n->right->height - n->left->height;
        }

  temp2->left = n;
  temp2->parent = n->parent;
  n->parent = temp2;
  
  if (temp2->parent != nullptr) {
    if (temp2->parent->right !=nullptr) {
      if (temp2->parent->right == temp2) {
        temp2->parent->right = temp2;
      }
    } else if (temp2->parent->left !=nullptr) {
        if (temp2->parent->left == temp2) {
          temp2->parent->left = temp2;
        }
      }
  }
  
  //update height and balance factor of z
  if (temp2->right == nullptr && temp2->left == nullptr) {
    temp2->height = 0;
    temp2->balanceFactor = 0;
  } else if (temp2->right == nullptr) {
      temp2->height = temp2->left->height + 1;
      temp2->balanceFactor = -1 - temp2->left->height;
    } else if (temp2->left == nullptr) {
        temp2->height = temp2->right->height + 1;
        temp2->balanceFactor = temp2->right->height - 1;
      } else {
          temp2->height = max(temp2->right->height, temp2->left->height) + 1;
          temp2->balanceFactor = temp2->right->height - temp2->left->height;
        }

  return temp2;
}

/*Description: Function outputs preorder traversal of given BST to console.
  Parameters: std::shared_ptr<Node> n, 
  std::vector<std::shared_ptr<Node>> &order
  Returns: void
*/
void AVLTree::preOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
  if (n != nullptr) {
    order.push_back(n);
    preOrder(n->left,order);
    preOrder(n->right,order);
  }
}

/*Description: Function passes values of nodes from a BST to a vector in
  ascending order. The values are then displayed on terminal.
  Parameters: std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order
  Returns: void
*/
void AVLTree::inOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
  if (n != nullptr) {
    inOrder(n->left, order);
    order.push_back(n);
    inOrder(n->right, order);
  }
}

/*Description: Function passes values of nodes from a BST to a vector in
   post order. The values are then displayed on terminal.
  Parameters: std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order
  Returns: void
*/
void AVLTree::postOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order){
  if (n != nullptr) {
    postOrder(n->left, order);
    postOrder(n->right, order);
    order.push_back(n);
  }
}

