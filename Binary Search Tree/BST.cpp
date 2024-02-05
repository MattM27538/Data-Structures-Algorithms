// BST.cpp
// Author: Matthew Martinez
// Description: File contains constructor for a binary search tree and common 
// functions to interact with the BST.

#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"

using std::cout;
using std:: endl;


// constructor for BST
BST::BST(){
  root = nullptr;
  size = 0;
}

// Destructor for BST
BST::~BST(){}

/*Description: Function calls search(std::shared_ptr<Node> n, int target)
  Returns pointer to node with value matching input target. Else
  return nullptr.
  Parameters: int target
  Returns: std::shared_ptr<Node>
*/

std::shared_ptr<Node> BST::search(int target){
  if (root != nullptr) {
    return search(root, target);
  }

  return nullptr;
}

/*Description: Searches BST for input value target. Returns pointer
  to node with value matching target. Else returns nullptr.
  Parameters: std::shared_ptr<Node> n, int target
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> BST::search(std::shared_ptr<Node> n, int target){
  if (n != nullptr) {
    if (n->value == target) {
      return n;
    } else if (n->value < target) {
        return search(n->right,target);
      } else {
          return search(n->left,target);
        }
  }

  return nullptr;
}

/*Description: Function calls minimum(std::shared_ptr<Node> n).
  Parameters: N/A
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> BST::minimum(){
  if (root != nullptr) {
    return minimum(root);
  }
  return nullptr;
}

/*Description: Function finds the minimum value in a BST and returns a shared_ptr
  to the node containing that value.
  Parameters:
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n){
  if (n->left != nullptr) {
    return minimum(n->left);
  }
  return n;
}

/*Description: Function calls maximum(std::shared_ptr<Node> n).
  Parameters: N/A
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> BST::maximum(){
  if (root != nullptr) {
    return maximum(root);
  }
  return nullptr;
}

/*Description: Function finds the maximum value in a BST and returns a shared_ptr
  to the node containing that value.
  Parameters:
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n){
  if (n->right != nullptr) {
    return maximum(n->right);
  }
  return n;
}

/*Description: Function calls insertValue(std::shared_ptr<Node> n, int val)
  and passes int val to said function.
  Parameters: int val
  Returns: void
*/
void BST::insertValue(int val){ 
  insertValue(root,val);
}

/*Description: Function inserts value as node into BST. Function
  does not add repeat values. Function returns shared pointer to
  inserted node.
  Parameters: std::shared_ptr<Node> n, int val
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> BST::insertValue(std::shared_ptr<Node> n, int val){
  if (n == nullptr) {
    root = std::shared_ptr<Node>(new Node(val));
    size = size + 1;
    return root;
  } else if (n->value == val) {
      return nullptr;
    } else if (n->value < val) {
        if (n->right == nullptr) {
          n->right = std::shared_ptr<Node>(new Node(val));
          size = size + 1;
          return n->right;
        } else {
            return insertValue(n->right,val);
          }
      } else {
          if (n->left == nullptr) {
            n->left = std::shared_ptr<Node>(new Node(val));
            size = size + 1;
            return n->left;
          } else {
              return insertValue(n->left,val);
            }
        }
}

/*Description: Function calls deleteValue(std::shared_ptr<Node> n, int val).
  Parameters: int val
  Returns: void
*/
void BST::deleteValue(int val){
  deleteValue(root, val);  
}

/*Description: Function returns pointer to node with minimum value of
  subtree with root passed to function (n).
  Parameters: std::shared_ptr<Node> n
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> deleteValueMinimum(std::shared_ptr<Node> n) {
  if (n->left != nullptr) {
    return deleteValueMinimum(n->left);
  }
  return n;
}

/*Description: Function returns pointer to node of BST that holds
  minimum value to be deleted on far right of tree.
  Parameters: std::shared_ptr<Node> n
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> deleteValueHelperRight(std::shared_ptr<Node> n) {
  if (n->right->right == nullptr) {
    return n;
  } 
  return deleteValueHelperRight(n->right);
}

/*Description:Function returns pointer to node of BST that holds
  minimum value to be deleted on far left of tree.
  Parameters: std::shared_ptr<Node> n
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> deleteValueHelperLeft(std::shared_ptr<Node> n) {
  if (n->left->left == nullptr) {
    return n;
  }
  return deleteValueHelperLeft(n->left);
}

/*Description: Function deletes node in BST and updates size of BST.
  Parameters: std::shared_ptr<Node> n, int val
  Returns: std::shared_ptr<Node>
*/
std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val){
  // Deletes root and makes adjustments to tree as necessary.
  if (n == nullptr) {
    return nullptr;
  } else if (root->value == val) {
      // Node has no children.
      if (root->left == nullptr && root->right == nullptr) {
        root = nullptr;
        return nullptr;
      } 
        // Node has one child.
        else if (root->right == nullptr) {
          root = root->left;
          return root;
        } else if (root->left == nullptr) {
            root = root->right;
            n->left = nullptr;
            return root;
          } else {
            // Node to delete has two children. 
              std::shared_ptr<Node> minimumInRightTree = deleteValueMinimum(root->right);    
              root->value = minimumInRightTree->value;
              minimumInRightTree = nullptr;
                if (root->right->left == nullptr && root->right->right ==nullptr) {
                  root->right = nullptr;
                  return nullptr;
                } else if (root->right->left == nullptr) {
                    root->right = root->right->right;
                    return n;
                  } else {
                      std::shared_ptr<Node> DeleteLeftChildOfThisPointer = deleteValueHelperLeft(root->right);
                      if (DeleteLeftChildOfThisPointer->left->left == nullptr && 
                          DeleteLeftChildOfThisPointer->left->right == nullptr) {
                            DeleteLeftChildOfThisPointer->left = nullptr;
                      } else {
                          DeleteLeftChildOfThisPointer->left = DeleteLeftChildOfThisPointer->left->right;
                        }
                      return n;
                  }
            }
    } 
  // Deletes value in BST on left side of tree and makes adjustments to tree as necessary. 
    else if (n->value > val) {
      if (n->left == nullptr) {
        return nullptr;
      } else if (n->left->value == val) {
          if (n->left->right == nullptr && n->left->left == nullptr) {
            // Node has no children.
            n->left = nullptr;
            return nullptr;
          } 
            // Node has one child.
            else if (n->left->right == nullptr) {
            n->left = n->left->left;
            return n;
            } else if (n->left->left == nullptr) {
                n->left = n->left->right;
                return n;
              } else {
                  // Node to delete has two children. 
                  std::shared_ptr<Node> minimumInRightTree = deleteValueMinimum(n->left->right);    
                  n->left->value = minimumInRightTree->value;
                  minimumInRightTree = nullptr;
                  if (n->left->right->left == nullptr && n->left->right->right == nullptr) {
                    n->left->right = nullptr;
                    return nullptr;
                  } else if (n->left->right->left == nullptr) {
                      n->left->right = n->left->right->right;
                      return n;
                    } else {
                        std::shared_ptr<Node> DeleteLeftChildOfThisPointer = deleteValueHelperLeft(n->left->right);
                        if (DeleteLeftChildOfThisPointer->left->left == nullptr && 
                            DeleteLeftChildOfThisPointer->left->right == nullptr) {
                              DeleteLeftChildOfThisPointer->left = nullptr;
                        } else {
                            DeleteLeftChildOfThisPointer->left = DeleteLeftChildOfThisPointer->left->right;
                          }
                        return n;
                      }
                }
  // Deletes value in BST on right side of tree and makes adjustments to tree as necessary.
        } else {
          return deleteValue(n->left, val);
        }
    } else if (n->value < val) {
        if (n->right == nullptr) {
        return nullptr;
        } else if (n->right->value == val) {
            if (n->right->right == nullptr && n->right->left == nullptr) {
              // Node has no children.
              n->right = nullptr;
              return nullptr;
            } 
              // Node has one child.
              else if (n->right->right == nullptr) {
                n->right = n->right->left;
                return n;
              } else if (n->right->left == nullptr) {
                  n->right = n->right->right;
                  return n;
                } else {
                  // Node to delete has two children. 
                    std::shared_ptr<Node> minimumInRightTree = deleteValueMinimum(n->right->right);    
                    n->right->value = minimumInRightTree->value;
                    minimumInRightTree = nullptr;
                    if (n->right->right->left == nullptr && n->right->right->right == nullptr) {
                      n->right->right = nullptr;
                      return nullptr;
                    } else if (n->right->right->left == nullptr) {
                        n->right->right = n->right->right->right;
                        return n;
                      } else {
                          std::shared_ptr<Node> DeleteLeftChildOfThisPointer = deleteValueHelperLeft(n->right->right);
                          if (DeleteLeftChildOfThisPointer->left->left == nullptr && 
                              DeleteLeftChildOfThisPointer->left->right == nullptr) {
                            DeleteLeftChildOfThisPointer->left = nullptr;
                          } else {
                              DeleteLeftChildOfThisPointer->left = DeleteLeftChildOfThisPointer->left->right;
                            }
                          return n;
                        }
                  }
          } else {
            return deleteValue(n->right, val);
            }
        } 
  return nullptr; 
}

/*Description: Function calls isBST(std::shared_ptr<Node> n, 
  int low, int high). Function returns true if BST is a BST
  else returns false.

  Parameters: std::shared_ptr<Node> n
  Returns: bool
*/
bool BST::isBST(std::shared_ptr<Node> n){
  return isBST(n,INT_MIN,INT_MAX);
}

/*Description: Function determines if input BST(input is 
  node to BST root) is a BST.
  Parameters: std::shared_ptr<Node> n, int low, int high
  Returns: bool
*/
bool BST::isBST(std::shared_ptr<Node> n, int low, int high){
  if (n == nullptr) {
    return true;
  }
  
  if (n->value < low || n->value > high) {
    return false;
  }

  return isBST(n->left,low,n->value) && isBST(n->right,n->value,high);
}

/*Description: Function outputs preorder traversal of given BST to console.
  Parameters: std::shared_ptr<Node> n, 
  std::vector<std::shared_ptr<Node>> &order
  Returns: void
*/
void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
  if (n != nullptr) {
    cout << n->value << " ";
    preOrder(n->left,order);
    preOrder(n->right,order);
  }
}

/*Description: Function passes values of nodes from a BST to a vector in
  ascending order. The values are then displayed on terminal.
  Parameters: std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order
  Returns: void
*/
void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
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
void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order){
  if (n != nullptr) {
    postOrder(n->left, order);
    postOrder(n->right, order);
    order.push_back(n);
  }
}
