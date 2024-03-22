/* AMBREEN EDITH WATETU- SCT-0611/2022
 DATA STRUCTURES ASSIGNMENT*/
#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}

// Function to create BST from array
struct Node* createBSTFromArray(int arr[], int n) {
    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }
    return root;
}

// Function to find the minimum value node in a BST
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to get the height of the BST
int height(struct Node* root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to print the level and height of a node
void printLevelAndHeight(struct Node* root, int value, int level) {
    if (root == NULL) {
        printf("Node not found\n");
        return;
    }
    if (value == root->data) {
        printf("Level: %d\n", level);
        printf("Height: %d\n", height(root));
    } else if (value < root->data) {
        printLevelAndHeight(root->left, value, level + 1);
    } else {
        printLevelAndHeight(root->right, value, level + 1);
    }
}

// Function to deallocate memory of BST
void freeBST(struct Node* root) {
    if (root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = createBSTFromArray(arr, n);

    // Test deleting a node
    int keyToDelete = 20;
    printf("Deleting node with value %d\n", keyToDelete);
    root = deleteNode(root, keyToDelete);

    // Print the height of the BST
    printf("Height of the BST: %d\n", height(root));

    // Test printing level and height of a node
    int valueToFind = 30;
    printf("Printing level and height of node with value %d\n", valueToFind);
    printLevelAndHeight(root, valueToFind, 0);

    // Deallocate memory
    freeBST(root);

    return 0;
}
