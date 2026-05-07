/* 문제
1. 스택 수란 RQ, MS로 LQ에 결과를 만들 수 있는 수열
2. 가능한 연산은 RQ -> MS, MS -> LQ, RQ -> LQ
*/

/* 입력 조건
1. 첫째 줄에 오른쪽 큐에 들어가는 데이터 크기 N의 정수가 주어진다. (3<=N<=20)
2. 둘째 줄에 테스트할 수열이 N개의 숫자로 주어짐
> 10
> 3 4 6 7 8 5 9 2 1 10
*/

/* 출력 조건
1. 첫째 줄에 테스트 결과가 스택 수이면 POSSIBLE, 스택 수가 아니면 IMPOSSIBLE을 출력
> POSSIBLE
*/

/* 접근 방법
- 입력받은 수열을 LQ로 가정하고 역으로 추적한다.
    - RQ에서 숫자를 하나씩 꺼낸다
    - 현재 MS의 top과 (LQ의) 현재 숫자가 같으면 pop
    - 다르면 RQ에서 MS로 push
    - MS top이 LQ 현재 숫자보다 크면 IMPOSSIBLE
    - 문제없이 수열을 만들 수 있다면 POSSIBLE
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;
    struct Node* link;
} node;

node* top = NULL;

// 큐 구조체 (Right/Left Queue)
typedef struct Queue {
    node* front;
    node* rear;
} Queue;

void push(int data) {
    node* new = (node*)malloc(sizeof(node));
    new->num = data;
    new->link = top;
    top = new;
}

int pop() {
    if (top == NULL) {
        return -1;
    }

    node* temp = top;
    int data = temp->num;
    top = temp->link;

    free(temp);
    return data;
}

int peek() {
    return (top == NULL) ? -1 : top->num;
}

void enQueue(Queue* q, int data) {
    node* new = (node*)malloc(sizeof(node));
    new->num = data;
    new->link = NULL;
    if (q->front == NULL) {
        q->front = q->rear = new;
    } else {
        q->rear->link = new;
        q->rear = new;
    }
}

int deQueue(Queue* q) {
    if (q->front == NULL) return -1;
    node* temp = q->front;
    int data = temp->num;
    q->front = q->front->link;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return data;
}

int main() {
    // 1. 변수 선언
    int N;  // 스택 수인지 판별할 수의 개수
    scanf("%d", &N);

    int target[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &target[i]);
    }

    int next_rq_val = 1; // RQ에는 1부터 N까지 순서대로 들어있음
    int target_idx = 0;
    int possible = 1;   // flag

    while (target_idx < N) {
        // 1. MS의 top이 현재 목표 숫자와 일치하면 바로 LQ로 이동(pop)
        if (top != NULL && peek() == target[target_idx]) {
            pop();
            target_idx++;
        }
        // 2. 일치하지 않으면 RQ에서 숫자를 가져와 MS에 보관(push)
        else if (next_rq_val <= N) {
            push(next_rq_val++);
        }
        // 3. 둘 다 불가능하면 이 수열은 만들 수 없음
        else {
            possible = 0;
            break;
        }
    }

    if (possible) {
        printf("POSSIBLE\n");
    } else {
        printf("IMPOSSIBLE\n");
    }

    return 0;
}