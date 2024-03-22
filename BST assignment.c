/* AMBREEN EDITH WATETU- SCT-0611/2022
ERICK MURU - SCT- 0972/2021
ABRAHAM KUIR - SCT=0727/2020
 DATA STRUCTURES ASSIGNMENT*/
#include <stdio.h>
#include <stdlib.h>

// Structure for a node in BST
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find the height of BST
int height(struct Node* root) {
    if (root == NULL)
        return -1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Function to print the level and height of a node
void printLevelAndHeight(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node with value %d not found in the tree.\n", key);
        return;
    }

    if (root->data == key) {
        printf("Level of node %d: %d\n", key, level);
        printf("Height of node %d: %d\n", key, height(root));
        return;
    }

    if (key < root->data)
        printLevelAndHeight(root->left, key, level + 1);
    else
        printLevelAndHeight(root->right, key, level + 1);
}

// Function to print the BST in inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    // Given array representing the BST
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = NULL;

    // Creating the BST from the array
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    // Printing the BST in inorder traversal
    printf("Inorder traversal of the BST: ");
    inorder(root);
    printf("\n");

    // Deleting a node from the BST (Example: Deleting node 20)
    root = deleteNode(root, 20);
    printf("Inorder traversal after deleting node 20: ");
    inorder(root);
    printf("\n");

    // Printing the height of the BST
    printf("Height of the BST: %d\n", height(root));

    // Printing the level and height of a node (Example: Node 25)
    printLevelAndHeight(root, 25, 0);

    return 0;
}
