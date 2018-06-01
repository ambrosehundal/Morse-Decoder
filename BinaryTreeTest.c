// Heap size 2048 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "BinaryTree.h"

// **** Set any macros or preprocessor directives here ****


// **** Define any module-level, global, or external variables here ****


// **** Declare any function prototypes here ****

int main() {
    BOARD_Init();

    /******************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     *****************************************************************************/
    const char input[] = "AMBROSE";
    const char temp[] = "SPARTAN";
    const char muneca[] = "TATIANA";
    Node* n;
    Node* m;
    Node* s;

    //Create sample trees for testing
    s = TreeCreate(3, muneca);
    n = TreeCreate(3, input);
    
    //Testing for GetLeftChild())
    printf("Left child is %p\n:", GetLeftChild(n));
    printf("Left expected value is %p\n: ", n->leftChild);
    printf("Left child is %p\n:", GetLeftChild(s));
    printf("Left expected value is %p\n: ", s->leftChild);
    
    //Testing for GetRightChild
    printf("Right child is %p\n:", GetRightChild(n));
    printf("Right expected value is %p\n: ", n->rightChild);
    printf("Right child is %p\n:", GetRightChild(s));
    printf("Right expected value is %p\n: ", s->rightChild);

    //Testing for TreeCreate()
    printf("Node value is: %c\n", n->data);
    printf("Node value is: %c\n", n->leftChild->data);
    printf("Node value is: %c\n", n->leftChild->leftChild->data);
    printf("Node value is: %c\n", n->leftChild->rightChild->data);
    printf("Node value is: %c\n", n->rightChild->leftChild->data);
    printf("Node value is: %c\n", n->rightChild->rightChild->data);
    printf("Node value is: %c\n", n->rightChild->data);
    
    
    m = TreeCreate(3, temp);
    printf("Node value is: %c\n", m->data);
    printf("Node value is: %c\n", m->leftChild->data);
    printf("Node value is: %c\n", m->leftChild->leftChild->data);
    printf("Node value is: %c\n", m->leftChild->rightChild->data);
    printf("Node value is: %c\n", m->rightChild->leftChild->data);
    printf("Node value is: %c\n", m->rightChild->rightChild->data);
    printf("Node value is: %c\n", m->rightChild->data);
    

    /*Testing for PrintTree*/
    PrintTree(m, 0);
    PrintTree(s, 0);
    /******************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     *****************************************************************************/

    while (1);
}
