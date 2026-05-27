#include <stdio.h>
#include "bst2.h"
#include <windows.h>

void printTree(treeNode* root, int level) {
    if (root == NULL) return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("    ");
    printf("[%d]\n", root->key);
    printTree(root->left, level + 1);
}

int main(void) {
    SetConsoleOutputCP(65001);
    treeNode* root = NULL;
    int keys[] = {59, 78, 65, 23, 7, 25, 52, 49, 99, 80};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insertBSTNode(root, keys[i]);
        printf("=== %d단계: %d 삽입 후 BST ===\n", i + 1, keys[i]);
        printTree(root, 0);
        printf("중위 순회: ");
        displayInorder(root);
        printf("\n\n");
    }

    getchar();
    return 0;
}
