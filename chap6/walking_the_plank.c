/* 문제
1. N명을 일렬로 세워놓고 1번부터 순서를 센다.
2. K-1번까지는 뒤로 가서 다시 줄을 서게 하고 K 번째 승객은 바다로 민다.
3. 마지막 한 명이 남을 때까지 반복
*/

/* 입력 조건
1. 첫째 줄에 N과 K에 대한 정수가 주어짐(1<=N<=50, 1<=K<=N)
    > 7 3
*/

/* 출력 조건
1. 첫째 줄에 널빤지로 선택되는 자리 번호를 순서대로 출력함.
    > 3 6 2 7 5 1 4
*/

/* 접근 방법
- K-1번까지는 뒤로가서 다시 줄을 선다. 
    - 단방향
    - 맨 앞에 있던 사람이 맨 뒤로 이동
        - Queue
    - 다시 줄을 선다
        -enQueue()
    - 삽입과 삭제가 빈번하게 일어남
        - 연결 리스트 사용
- K 번째 승객은 바다로 민다
    - deQueue()
-> 단방향 연결 리스트 방식으로 구현한 Queue 자료구조 형태로 구현
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* link;
} node;

node* front = NULL;
node* rear = NULL;
node* curr = NULL;

int isEmpty(node* front) {
    if (front == NULL) {
        return 1;
    }
    return 0;
}

void enQueue(int num) {
    node* new = malloc(sizeof(node));
    new->data = num;
    new->link = NULL;

    if (isEmpty(front)) {
        front = new;
        rear = new;
    } else {
        rear->link = new;
        rear = new;
    }
}

int deQueue() {
    node* old = front;
    int num;

    if (isEmpty(front)) {
        return -1;
    } else {
        num = old->data;
        front = front->link;

        if (isEmpty(front)) {
            rear = NULL;
        }

        free(old);
        return num;
    }
}

int main() {
    // 1. 변수 선언
    int N, K;   // 전체 인원 수 N, K 번째 사람마다 바다에 빠짐
    scanf("%d %d", &N, &K);

    if (N > 50 || K > N || N < 1 || K < 1) {
        printf("잘못된 선언");
        return 1;
    }

    // 2. 순서에 따른 번호 대입 및 노드 연결
    for (int i = 1; i <= N; i++) {
        enQueue(i);
    }

    // 3. K 번째마다 사람을 바다로 빠뜨리는 알고리즘
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K - 1; j++) {   // K=3일 때 3번째 사람이 빠져야 함. front는 0번째 인덱스를 가리키고 있기 때문에 3번째인 [2]가 나가려면 K-1까지로 범위를 지정해야 함.
            // 맨 앞에 있는 번호를 뒤로 보냄
            enQueue(deQueue());
        }
        if (i != N - 1) {
            printf("%d ", deQueue());
        } else {
            printf("%d", deQueue());
        }
    }

    return 0;
}