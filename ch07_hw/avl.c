#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/* 
 * [알고리즘 7-7] LL_rotate
 *   L2(child)의 오른쪽 자식 → L1(parent)의 왼쪽 자식으로 이동
 *   L1(parent) → L2(child)의 오른쪽 자식으로 이동
 *   반환: child (새 루트)
 */
treeNode* LL_rotate(treeNode* parent) {
    treeNode* child = parent->left;         // child = L2 저장
    parent->left    = child->right;         // child의 오른쪽 자식 → parent의 왼쪽
    child->right    = parent;               // parent → child의 오른쪽
    return child;                           // child(L2)가 새 루트
}

/* 
 * [알고리즘 7-8] RR_rotate  (LL_rotate의 좌우 대칭)
 *   L2(child)의 왼쪽 자식 → L1(parent)의 오른쪽 자식으로 이동
 *   L1(parent) → L2(child)의 왼쪽 자식으로 이동
 *   반환: child (새 루트)
 */
treeNode* RR_rotate(treeNode* parent) {
    treeNode* child = parent->right;        // child = L2 저장
    parent->right   = child->left;          // child의 왼쪽 자식 → parent의 오른쪽
    child->left     = parent;               // parent → child의 왼쪽
    return child;                           // child(L2)가 새 루트
}

/* 
 * [알고리즘 7-9] LR_rotate  (이중 회전)
 *   L2-L3 구간에 RR_rotate(child) 수행 → 반환 노드를 parent의 왼쪽 자식으로
 *   parent에 LL_rotate(parent) 수행 → L3가 최종 새 루트
 */
treeNode* LR_rotate(treeNode* parent) {
    treeNode* child  = parent->left;        // child = L2 저장
    parent->left     = RR_rotate(child);    // L2 구간 RR 회전 → 결과를 parent 왼쪽에 연결
    return LL_rotate(parent);               // parent 구간 LL 회전 → 새 루트 반환
}

/* 
 * [알고리즘 7-10] RL_rotate  (LR_rotate의 좌우 대칭, 이중 회전)
 *   L2-L3 구간에 LL_rotate(child) 수행 → 반환 노드를 parent의 오른쪽 자식으로
 *   parent에 RR_rotate(parent) 수행 → L3가 최종 새 루트
 */
treeNode* RL_rotate(treeNode* parent) {
    treeNode* child  = parent->right;       // child = L2 저장
    parent->right    = LL_rotate(child);    // L2 구간 LL 회전 → 결과를 parent 오른쪽에 연결
    return RR_rotate(parent);               // parent 구간 RR 회전 → 새 루트 반환
}

/* 
 * getHeight: 서브트리의 높이를 재귀적으로 계산
 *   빈 트리(NULL) → 0,  단말 노드 → 1
 */
int getHeight(treeNode* p) {
    int height = 0;
    if (p != NULL)  // p가 NULL이면 height = 0 그대로 반환
        height = MAX(getHeight(p->left), getHeight(p->right)) + 1;  // 왼쪽/오른쪽 서브트리 중 큰 높이 + 1
    return height;
}

/* 
 * getBF: 균형 인수(Balance Factor) 반환
 *   BF = height(왼쪽) - height(오른쪽)
 *   |BF| <= 1 → 균형,  |BF| >= 2 → 불균형 → 회전 필요
 */
int getBF(treeNode* p) {
    if (p == NULL) return 0;  // 빈 노드의 BF = 0
    return getHeight(p->left) - getHeight(p->right);  // 왼쪽 높이 - 오른쪽 높이
}

/* 
 * rebalance: BF 검사 후 불균형 유형에 맞는 회전 호출
 *
 *   BF > +1  (왼쪽 과잉)
 *     getBF(왼쪽 자식) > 0  → LL 불균형 → LL_rotate
 *     getBF(왼쪽 자식) <= 0 → LR 불균형 → LR_rotate
 *
 *   BF < -1  (오른쪽 과잉)
 *     getBF(오른쪽 자식) < 0  → RR 불균형 → RR_rotate
 *     getBF(오른쪽 자식) >= 0 → RL 불균형 → RL_rotate
 */
treeNode* rebalance(treeNode** p) {
    int BF = getBF(*p);                     // 현재 노드의 BF 계산
    if (BF > 1) {                           // 왼쪽 서브트리 과잉
        if (getBF((*p)->left) > 0)
            *p = LL_rotate(*p);             // LL 불균형
        else
            *p = LR_rotate(*p);             // LR 불균형
    }
    else if (BF < -1) {                     // 오른쪽 서브트리 과잉
        if (getBF((*p)->right) < 0)
            *p = RR_rotate(*p);             // RR 불균형
        else
            *p = RL_rotate(*p);             // RL 불균형
    }
    return *p;
}

/* 
 * insertAVLNode: AVL 트리 삽입
 *   BST와 동일하게 재귀로 삽입 위치를 찾은 뒤,
 *   재귀가 되돌아오는 경로마다 rebalance() 호출 → 균형 유지
 */
treeNode* insertAVLNode(treeNode** root, element x) {
    if (*root == NULL) {                    // 삽입 위치 도달 → 새 노드 생성
        *root = (treeNode*)malloc(sizeof(treeNode));
        (*root)->key   = x;
        (*root)->left  = NULL;
        (*root)->right = NULL;
    }
    else if (x < (*root)->key) {
        (*root)->left  = insertAVLNode(&((*root)->left), x);   // 왼쪽 서브트리로 재귀
        *root = rebalance(root);            // 재귀 복귀 시 균형 검사
    }
    else if (x > (*root)->key) {
        (*root)->right = insertAVLNode(&((*root)->right), x);  // 오른쪽 서브트리로 재귀
        *root = rebalance(root);            // 재귀 복귀 시 균형 검사
    }
    else {
        printf("\n 이미 같은 키가 있습니다! \n");   // 중복 키 거부
        exit(1);
    }
    return *root;
}