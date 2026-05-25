#include <stdio.h>
#include <stdlib.h>
#include "bst2.h"

/* 
 * searchBST: BST/AVL 트리에서 키 x 탐색 (반복)
 *   x < key  → 왼쪽,  x == key → 성공 반환,  x > key → 오른쪽
 *   NULL 도달 시 탐색 실패
 */
treeNode* searchBST(treeNode* root, element x) {
    treeNode* p;
    int count = 0;
    p = root;                               // 루트부터 시작
    while (p != NULL) {
        count++;
        if (x < p->key)       p = p->left;             // 왼쪽으로 이동
        else if (x == p->key) {
            printf("%3d번째에 탐색 성공", count);
            return p;                       // 탐색 성공
        }
        else                  p = p->right;             // 오른쪽으로 이동
    }
    count++;
    printf("%3d번째에 탐색 실패! 찾는 키가 없습니다!", count);
    return p;                               // NULL 반환 (실패)
}

/* 
 * insertBSTNode: BST 노드 삽입 (재귀)
 *   p == NULL → 삽입 위치 도달, 새 노드 생성 후 반환
 *   반환값을 부모의 left/right에 저장해 트리에 연결
 */
treeNode* insertBSTNode(treeNode* p, element x) {
    treeNode* newNode;
    if (p == NULL) {                        // 삽입 위치 도달
        newNode = (treeNode*)malloc(sizeof(treeNode));
        newNode->key   = x;
        newNode->left  = NULL;
        newNode->right = NULL;
        return newNode;
    }
    else if (x < p->key)  p->left  = insertBSTNode(p->left,  x);  // 왼쪽 재귀
    else if (x > p->key)  p->right = insertBSTNode(p->right, x);  // 오른쪽 재귀
    else  printf("\n 이미 같은 키가 있습니다! \n");                // 중복 거부

    return p;
}

/* 
 * deleteBSTNode: BST 노드 삭제 (반복)
 *   Case 1. 단말 노드        → 부모 링크를 NULL로
 *   Case 2. 자식 1개         → 자식을 부모와 직접 연결
 *   Case 3. 자식 2개         → 왼쪽 서브트리의 최댓값(후계자)으로 대체
 */
void deleteBSTNode(treeNode* root, element key) {
    treeNode* parent, *p, *succ, *succ_parent, *child;

    parent = NULL;
    p = root;
    while ((p != NULL) && (p->key != key)) {   // 삭제 대상 탐색
        parent = p;
        if (key < p->key) p = p->left;
        else              p = p->right;
    }

    if (p == NULL) {                        // 키가 없음
        printf("\n 찾는 키가 이진 트리에 없습니다!!");
        return;
    }

    // Case 1: 단말 노드
    if ((p->left == NULL) && (p->right == NULL)) {
        if (parent != NULL) {
            if (parent->left == p) parent->left  = NULL;
            else                   parent->right = NULL;
        }
        else root = NULL;
    }

    // Case 2: 자식 1개
    else if ((p->left == NULL) || (p->right == NULL)) {
        child = (p->left != NULL) ? p->left : p->right;  // 유일한 자식
        if (parent != NULL) {
            if (parent->left == p) parent->left  = child;
            else                   parent->right = child;
        }
        else root = child;
    }

    // Case 3: 자식 2개 → 왼쪽 서브트리에서 최댓값(후계자) 탐색
    else {
        succ_parent = p;
        succ        = p->left;
        while (succ->right != NULL) {       // 왼쪽 서브트리의 가장 오른쪽 노드
            succ_parent = succ;
            succ        = succ->right;
        }
        if (succ_parent->left == succ)  succ_parent->left  = succ->left;
        else                            succ_parent->right = succ->left;
        p->key = succ->key;                 // 후계자 키로 대체
        p = succ;                           // 실제 삭제 대상을 후계자로 변경
    }
    free(p);
}