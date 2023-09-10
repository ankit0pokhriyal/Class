// LAB ASSIGNMENT
// Insertion & Deletion in AVL
#include <--------->
#include <---------->

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to calculate the height of a node
int height(struct Node* node) {
    if (------------) //  If node empty
        return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return -------------;  // find Maximum
}

// Create a new AVL tree node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially added at leaf
    return node;
}

// Right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    --------------------------; // Mirror of Left Rotate See Below
    ---------------------------; // Mirror of Left Rotate See Below

    ------------;   // Mirror of Left Rotate See Below
    ------------;   // Mirror of Left Rotate See Below

    // Update heights
    ------------------------------------------------------; // Mirror of Left Rotate See Below
    ------------------------------------------------------; // Mirror of Left Rotate See Below

    return x;
}

// Left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* ------------;  // If y at xRight
    struct Node* ------------;  // If T2 at yLeft

    --------------;    // Then y left become x
    --------------;  // And X right become T2

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = ------------------------------------------;  // Same as x-> height

    return y;
}

// Get balance factor of a node
int balanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return ------------------------;  // LeftHeight - RightHeight
}

// Insert a key into the AVL tree
struct Node* insert(struct Node* node, int key) {
    // Perform standard BST insertion
    if (node == NULL)
        return newNode(key);

    if (-------------------) // Condition when value < root
        node->left = insert(node->left, key);
    else if (---------------) // Condition when value > root ( Note: we are not taking any duplicate values)
        node->right = insert(node->right, key);
    else // Duplicate keys are Not allowed
        return node;

    // Update height of the current node
    node->height = ----------------------------------------;

    // Get the balance factor of this node to check if it's unbalanced
    int balance = balanceFactor(node);

    // If this node becomes unbalanced, there are four cases

    // Left Left Case
    if (--------------------------------------) 
        return rightRotate(node);

    // Right Right Case
    if (--------------------------------------)
        return leftRotate(node);

    // Left Right Case
    if (--------------------------------------) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        ----------------------------------------; // Mirror of LeftRight Case
        return leftRotate(node);
    }

    return node;
}
// Function to find the node with the minimum key value in a given AVL tree
// Use to find Inorder Sucessor (NOTE: Using Preorder or Postorder for deletion is out of scope of this code.)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)   // Recurrent function can also be used instead of while loop
        current = current->left;
    return current;
}
struct Node* deleteNode(struct Node* root, int key) {
    // Perform standard BST delete
    if (--------------------)
        return root;

    if (--------------------)
        root->left = deleteNode(root->left, key);
    else if (----------------)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = -----------; // Copy the contents of the non-empty child

            free(temp);
        } else {
            // Node with two children: get the inorder successor (smallest in the right subtree)
            struct Node* temp = ------------------;

            // Copy the inorder successor's data to this node
            root->key = -----------------;

            // Delete the inorder successor
            root->right = --------------------------------;
        }
    }

    // If the tree had only one node, return
    if (root == NULL)
        return root;

    // Update the height of the current node
    ------------------------------------------------------;

    // Get the balance factor of this node
    int balance = balanceFactor(root);

    // If this node becomes unbalanced, there are four cases

    // Left Left Case
    if (----------------------------------------------------) // See Right Right Case
        return rightRotate(root);

    // Left Right Case
    if (----------------------------------------------------) { // See Right Left Case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        --------------------------------------;       // Double Rotation as Insertion
        return leftRotate(root);
    }

    return root;
}


// Print the AVL tree in in-order traversal
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    root = insert(root, 63);
    root = insert(root, 9);
    root = insert(root, 19);
    root = insert(root, 27);
    root = insert(root, 18);
    root = insert(root, 108);
    root = insert(root, 99);
    root = insert(root, 81);

    printf("In-order traversal of the AVL tree: ");
    inOrder(root);
    
    root = deleteNode(root, 81);
    root = deleteNode(root, 99);
    root = deleteNode(root,108);
    root = deleteNode(root, 18);
    root = deleteNode(root, 27);
    root = deleteNode(root, 19);
    
    printf("\nIn-order traversal of the AVL tree: ");
    inOrder(root);

    return 0;
}
 
