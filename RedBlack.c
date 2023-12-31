#include <stdio.h>
#include <stdlib.h>

// Define the colors for Red-Black tree nodes
enum Color {
    RED,
    BLACK
};

// Structure for a Red-Black tree node
struct Node {
    int data;
    enum Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

// Function to create a new Red-Black tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;  // New nodes are always RED
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to perform a left rotation on a Red-Black tree
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        (*root) = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Function to perform a right rotation on a Red-Black tree
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Function to fix violations of Red-Black tree properties after insertion
void fixInsert(struct Node** root, struct Node* newNode) {
    struct Node* parent = NULL;
    struct Node* grandparent = NULL;

    while (newNode != *root && newNode->color == RED && newNode->parent->color == RED) {
        parent = newNode->parent;
        grandparent = parent->parent;

        // Case 1: Uncle is RED
        if (parent == grandparent->left) {
            struct Node* uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                // Case 2: Uncle is BLACK and newNode is a right child
                if (newNode == parent->right) {
                    leftRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                // Case 3: Uncle is BLACK and newNode is a left child
                rightRotate(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                newNode = parent;
            }
        } else {  // (parent == grandparent->right)
            struct Node* uncle = grandparent->left;
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                // Case 2: Uncle is BLACK and newNode is a left child
                if (newNode == parent->left) {
                    rightRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                // Case 3: Uncle is BLACK and newNode is a right child
                leftRotate(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                newNode = parent;
            }
        }
    }

    (*root)->color = BLACK;
}

// Function to insert a node into the Red-Black tree
void insertRB(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* parent = NULL;
    struct Node* current = (*root);

    // Find the proper position to insert the node
    while (current != NULL) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    // Set the parent of the new node
    newNode->parent = parent;

    // Insert the node as a red leaf
    if (parent == NULL)
        (*root) = newNode;
    else if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    // Fix any Red-Black tree violations
    fixInsert(root, newNode);
}

// Function to perform in-order traversal of the Red-Black tree
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Function to find the minimum node in a Red-Black tree
struct Node* findMin(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to fix violations of Red-Black tree properties after deletion
void fixDelete(struct Node** root, struct Node* x) {
    struct Node* sibling;
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            sibling = x->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                sibling = x->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(root, sibling);
                    sibling = x->parent->right;
                }
                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            sibling = x->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                sibling = x->parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(root, sibling);
                    sibling = x->parent->left;
                }
                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

// Function to delete a node from the Red-Black tree
struct Node* deleteNodeRB(struct Node* root, int data) {
    if (root == NULL)
        return root;

    // Find the node to be deleted and store its parent
    struct Node* parent = NULL;
    struct Node* current = root;
    while (current != NULL && current->data != data) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
        return root;  // Node not found

    // Determine if the node to be deleted is a leaf or has one child
    struct Node* child = NULL;
    if (current->left == NULL || current->right == NULL) {
        if (current->left == NULL)
            child = current->right;
        else
            child = current->left;

        // Case 1: Node to be deleted is a leaf
        if (current->color == BLACK) {
            if (child == NULL) {
                // Current node is a leaf with no children (both NULL)
                child = createNode(0); // Create a temporary NULL node (black)
                child->parent = current;
                current->left = child;
            } else if (child->color == RED)
                child->color = BLACK;
            else
                fixDelete(&root, child);
        }

        if (parent == NULL) {
            // Node to be deleted is the root
            free(root);
            return NULL;
        }

        if (current == parent->left)
            parent->left = child;
        else
            parent->right = child;

        if (child != NULL)
            child->parent = parent;
        free(current);
    } else {
        // Case 2: Node to be deleted has two children
        struct Node* successor = findMin(current->right);
        current->data = successor->data;
        root = deleteNodeRB(root, successor->data);
    }

    return root;
}

int main() {
    struct Node* root = NULL;

    // Insert elements into the Red-Black tree
    insertRB(&root, 63);
    insertRB(&root, 9);
    insertRB(&root, 19);
    insertRB(&root, 27);
    insertRB(&root, 18);
    insertRB(&root, 108);
    insertRB(&root, 99);
    insertRB(&root, 81);

    // Print the Red-Black tree in in-order traversal
    printf("In-order traversal of the Red-Black tree: ");
    inOrder(root);
    printf("\n");

    // Delete a node from the Red-Black tree
    root = deleteNodeRB(root, 81);
    root = deleteNodeRB(root, 99);
    root = deleteNodeRB(root, 9);
    // Print the Red-Black tree after deletion
    printf("In-order traversal after deleting 30: ");
    inOrder(root);

    return 0;
}
