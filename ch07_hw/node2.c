#include <stdio.h>
#include "node2.h"

/* 
 * displayInorder: 중위 순회 (왼쪽 → 루트 → 오른쪽)
 *   BST에서 실행하면 키가 오름차순으로 출력됨
 */
void displayInorder(treeNode* root) {
    if (root) {
        displayInorder(root->left);         // 왼쪽 서브트리 재귀
        printf("%d_", root->key);           // 현재 노드 출력
        displayInorder(root->right);        // 오른쪽 서브트리 재귀
    }
}