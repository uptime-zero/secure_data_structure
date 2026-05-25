#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* ============================
 *  AVL 트리 구현 (C언어)
 *  - 삽입 (Insert)
 *  - 삭제 (Delete)
 *  - 검색 (Search)
 *  - 순회 (Inorder / Preorder / Postorder)
 * ============================ */

/* ── 노드 구조체 ── */
typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

/* ── 유틸리티 함수 ── */

static int i_max(int a, int b) {
    return (a > b) ? a : b;
}

/* 노드의 높이 반환 (NULL이면 -1) */
static int height(Node *n) {
    return (n == NULL) ? -1 : n->height;
}

/* 노드의 균형 인수 = 왼쪽 높이 - 오른쪽 높이 */
static int balance_factor(Node *n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

/* 높이 갱신 */
static void update_height(Node *n) {
    if (n != NULL)
        n->height = 1 + i_max(height(n->left), height(n->right));
}

/* 새 노드 생성 */
static Node *new_node(int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    n->key    = key;
    n->height = 0;
    n->left   = NULL;
    n->right  = NULL;
    return n;
}

/* ── 회전 연산 ── */

/*
 * 우회전 (Right Rotation)
 *
 *      y                x
 *     / \              / \
 *    x   T3   -->    T1   y
 *   / \                  / \
 *  T1  T2              T2  T3
 */
static Node *rotate_right(Node *y) {
    Node *x  = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left  = T2;

    update_height(y);
    update_height(x);
    return x;
}

/*
 * 좌회전 (Left Rotation)
 *
 *    x                  y
 *   / \                / \
 *  T1   y    -->      x   T3
 *      / \           / \
 *    T2  T3        T1  T2
 */
static Node *rotate_left(Node *x) {
    Node *y  = x->right;
    Node *T2 = y->left;

    y->left  = x;
    x->right = T2;

    update_height(x);
    update_height(y);
    return y;
}

/* ── 균형 재조정 ── */
static Node *rebalance(Node *n) {
    update_height(n);
    int bf = balance_factor(n);

    /* Left-Left (LL) */
    if (bf > 1 && balance_factor(n->left) >= 0)
        return rotate_right(n);

    /* Left-Right (LR) */
    if (bf > 1 && balance_factor(n->left) < 0) {
        n->left = rotate_left(n->left);
        return rotate_right(n);
    }

    /* Right-Right (RR) */
    if (bf < -1 && balance_factor(n->right) <= 0)
        return rotate_left(n);

    /* Right-Left (RL) */
    if (bf < -1 && balance_factor(n->right) > 0) {
        n->right = rotate_right(n->right);
        return rotate_left(n);
    }

    return n; /* 이미 균형 */
}

/* ── 삽입 ── */
Node *avl_insert(Node *root, int key) {
    if (root == NULL)
        return new_node(key);

    if (key < root->key)
        root->left  = avl_insert(root->left,  key);
    else if (key > root->key)
        root->right = avl_insert(root->right, key);
    else
        return root; /* 중복 키 허용하지 않음 */

    return rebalance(root);
}

/* ── 삭제 ── */

/* 서브트리에서 최솟값 노드 반환 */
static Node *min_node(Node *n) {
    while (n->left != NULL)
        n = n->left;
    return n;
}

Node *avl_delete(Node *root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->key) {
        root->left  = avl_delete(root->left,  key);
    } else if (key > root->key) {
        root->right = avl_delete(root->right, key);
    } else {
        /* 삭제할 노드 발견 */
        if (root->left == NULL || root->right == NULL) {
            Node *child = (root->left != NULL) ? root->left : root->right;
            free(root);
            return child; /* 자식 0개 또는 1개 */
        }
        /* 자식이 2개: 오른쪽 서브트리의 최솟값(후계자)으로 대체 */
        Node *successor = min_node(root->right);
        root->key       = successor->key;
        root->right     = avl_delete(root->right, successor->key);
    }

    return rebalance(root);
}

/* ── 검색 ── */
Node *avl_search(Node *root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return avl_search(root->left,  key);
    return     avl_search(root->right, key);
}

/* ── 트리 해제 ── */
void avl_free(Node *root) {
    if (root == NULL) return;
    avl_free(root->left);
    avl_free(root->right);
    free(root);
}

/* ── 순회 ── */

void inorder(Node *root) {           /* 중위: 오름차순 출력 */
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(Node *root) {          /* 전위 */
    if (root == NULL) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) {         /* 후위 */
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

/* ── 트리 시각화 (디버그용) ── */
void print_tree(Node *root, int depth, char *prefix) {
    if (root == NULL) return;
    printf("%s%d (h=%d, bf=%d)\n",
           prefix, root->key, root->height, balance_factor(root));

    char left_prefix[256], right_prefix[256];
    snprintf(left_prefix,  sizeof(left_prefix),  "%s  ├─L: ", prefix);
    snprintf(right_prefix, sizeof(right_prefix), "%s  └─R: ", prefix);

    if (root->left  != NULL) print_tree(root->left,  depth + 1, left_prefix);
    if (root->right != NULL) print_tree(root->right, depth + 1, right_prefix);
}

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 *  메인 – 동작 확인
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
int main(void) {
    SetConsoleOutputCP(65001);  // 콘솔 출력 UTF-8로 변경
    SetConsoleCP(65001);
    Node *root = NULL;

    /* 삽입 테스트 */
    int keys[] = {25, 30, 35, 45, 40, 38, 37, 36, 39};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("=== 삽입 순서: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
        root = avl_insert(root, keys[i]);
    }
    printf("\n\n");

    printf("=== 트리 구조 (루트부터) ===\n");
    print_tree(root, 0, "");

    printf("\n=== 중위 순회 (정렬 결과): ");
    inorder(root);
    printf("\n");

    printf("=== 전위 순회: ");
    preorder(root);
    printf("\n");

    printf("=== 후위 순회: ");
    postorder(root);
    printf("\n");

    /* 검색 테스트 */
    int target = 25;
    Node *found = avl_search(root, target);
    printf("\n=== 검색: %d → %s\n", target, found ? "발견" : "없음");

    target = 99;
    found = avl_search(root, target);
    printf("=== 검색: %d → %s\n", target, found ? "발견" : "없음");

    /* 삭제 테스트 */
    printf("\n=== 삭제: 20\n");
    root = avl_delete(root, 20);
    print_tree(root, 0, "");
    printf("중위: "); inorder(root); printf("\n");

    printf("\n=== 삭제: 10\n");
    root = avl_delete(root, 10);
    print_tree(root, 0, "");
    printf("중위: "); inorder(root); printf("\n");

    printf("\n=== 삭제: 1\n");
    root = avl_delete(root, 1);
    print_tree(root, 0, "");
    printf("중위: "); inorder(root); printf("\n");

    avl_free(root);
    return 0;
}