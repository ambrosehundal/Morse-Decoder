#include "BinaryTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*Helper function to create a new node in binary tree*/
Node* newNode(const char * data) {
    Node* node = (Node*) malloc(sizeof (Node));
    node->data = *data;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}

/**
 * This function creates a binary tree of a given size given a serialized array of data. All nodes
 * are allocated on the heap via `malloc()` and store the input data in their data member. Note that
 * this parameter is serialized in a top-down, left-to-right order. This means it follows the
 * left-hand-side of the tree to the bottom and then backs it's way back up.
 *
 * So for a tree like:
 *           A
 *        B     C
 *      D   E F   G
 * The data variable is ordered as [A B D E C F G].
 * 
 * This function uses recursion for generating the tree in this top-down, left-right order. This
 * tree, and therefore the input data set, is assumed to be full and balanced therefore each level
 * has 2^level number of nodes in it. If the `data` input is not this size, then this functions
 * behavior is undefined. Since the input data is copied directly into each node, they can
 * originally be allocated on the stack.
 *
 * If allocating memory fails during TreeCreate() then it will return NULL. Additionally, if the
 * creation of either of the subtrees fails within TreeCreate(), it should return NULL. This means
 * that if TreeCreate() returns a non-NULL value, that means that a perfect tree has been created,
 * so all nodes that should exist have been successfully malloc()'d onto the heap.
 *
 * This function does not completely clean up after itself if malloc() fails at any point. Some
 * nodes may be successfully free()d, but a failing TreeCreate() is likely to leave memory in the
 * heap unaccessible.
 *
 * @param level How many vertical levels the tree will have.
 * @param data A serialized array of the character data that will be stored in all nodes. This array
 *              should be of length `2^level - 1`.
 * @return The head of the created tree or NULL if malloc fails for any node.
 */
Node *TreeCreate(int level, const char *data) {
    Node* root = newNode(data);

    //if malloc() fails, return NULL
    if (root == NULL) {
        return NULL;
    }
    if (level > 1) {
        root->leftChild = TreeCreate(level - 1, data + 1);
        root->rightChild = TreeCreate((level - 1), (data + (int) pow(2, (level - 1))));

        //if reached last level bottom node to be created
    } else if (level == 1) {
        root->leftChild = NULL;
        root->rightChild = NULL;

    }
    return root;

}

/**
 * This function returns the left child of the node passed into the function. The function should return
 * NULL if the node passed in has no left child. You will also need to be careful not to dereference the
 * NULL pointer if called with an empty node.
 *
 * @param root Pointer to root node
 * @return The pointer to the left child of the node, NULL if there is no child.
 */
Node *GetLeftChild(Node *root) {
    if ((root->leftChild == NULL)) {
        return NULL;
    }
    return root->leftChild;
}

/**
 * This function returns the right child of the node passed into the function. The function should return
 * NULL if the node passed in has no right child. You will also need to be careful not to dereference the
 * NULL pointer if called with an empty node.
 *
 * @param root Pointer to root node
 * @return The pointer to the right child of the node, NULL if there is no child.
 */
Node *GetRightChild(Node *root) {
    if ((root->rightChild ==                                                                                                                                                                                    NULL)) {
        return NULL;
    }
    
    return root->rightChild;
}

/**
 * This function prints the tree rotated 90 degrees counter clockwise using recursive calls. To print the
 * full tree, it should be called as PrintTree(root, 0).
 *
 * If the tree looks like:        A
 *                              B   C
 * Then calling PrintTree(root, 0) will return:
 *    C
 * A
 *    B
 *
 * The function should be robust to being called on an empty tree, and should be implemented recursively. If
 * the data is NULL or non-printable, then the print should be blank. See the lab write up for details on the
 * print tree algorithm.
 *
 * @param node The node to print the tree from
 * @param space The number of spaces to print before printing the node data 
 * @return none
 */
void PrintTree(Node *node, int space) {
    int i;
    if (node == NULL) {
        return;
    }
    space += LEVEL_SPACES;
    PrintTree(node->rightChild, space);
    //print
    printf("\n");
    for (i = 0; i < space; i++) {
        printf(" ");
    }
    printf("%c\n", node->data);

    PrintTree(node->leftChild, space);
}

