#include <stdio.h>
#include <stdlib.h>

// Define a node structure
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// In-order traversal: Left, Root, Right
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Pre-order traversal: Root, Left, Right
void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Post-order traversal: Left, Right, Root
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    // Manually building the binary tree:
    //         8
    //        /  \
    //       4    12
    //      / \     \
    //     2   7     14

    Node* root = createNode(8);
    root->left = createNode(4);
    root->right = createNode(12);
    root->left->left = createNode(2);
    // root->left->right = createNode(7);
    root->right->right = createNode(14);

    // Traversals
    printf("In-order Traversal: ");
    inorder(root);
    printf("\n");

    printf("Pre-order Traversal: ");
    preorder(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postorder(root);
    printf("\n");

    return 0;
}
