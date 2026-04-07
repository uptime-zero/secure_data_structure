// 선택한 노래만 선택한 순서대로 반복 재생
// 음악 제목은 a-zA-Z (알파벳 대소문자)로만 이뤄져 있음

// 입력 조건
// 첫째 줄에 음악 목록에 있는 음악 개수 N과 반복 재생할 음악 개수 K가 주어짐 (1 <= N <= 52, 1 <= K <= 52)
// 둘째 줄에 연속 재생할 음악 제목 K개가 주어짐

// 출력 조건
// 첫째 줄에 반복 재생 목록에 있는 노래 제목을 출력

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. 노드 구조체 정의
typedef struct Node {
    char data[100];      // 음악 제목을 저장할 배열 (알파벳 대소문자)
    struct Node* link;   // 다음 노드의 주소를 가리키는 포인터
} node;

int main() {
    int N, K;
    node *head = NULL;   // 리스트의 시작점(첫 번째 노래)을 가리키는 포인터
    node *tail = NULL;   // 리스트의 끝점(마지막 노래)을 가리키는 포인터

    // 2. 전체 음악 개수 N과 재생할 음악 개수 K 입력받기
    scanf("%d %d", &N, &K);
    if (N < 1 || N > 52 || N < 1 || K > 52) {
        printf("음악 개수는 1이상 52이하여야 합니다.\n");
        return 1;
    }

    // 3. K개의 음악 제목을 입력받아 리스트 만들기
    for (int i = 0; i < K; i++) {
        char input[100];

        // 새 노드 생성: 메모리에서 node 크기만큼 공간을 빌려옵니다.
        node* newNode = malloc(sizeof(node));

        // 제목 입력 및 유효성 검증
        scanf("%s", input);
        for (int j = 0; j < strlen(input); j++) {
            if (!isalpha(input[j])) {
                printf("음악 제목은 알파벳 대소문자여야 합니다.");
            }
        }

        // 배열 이름은 상수 포인터이기 때문에 대입 연산자로 문자열을 한 번에 넣을 수 없어서 strcpy 사용
        strcpy(newNode->data, input);

        // 새로 만든 노드는 다음 연결 대상이 없으므로 NULL로 설정
        newNode->link = NULL;

        if (head == NULL) {  // 리스트가 비었을 경우
            head = newNode;
        } else {  // 리스트에 값이 있을 경우
            tail->link = newNode;
        }

        tail = newNode;  // tail을 새로운 노드의 가장 끝 값으로 업데이트
    }

    // 4. 원형 연결 (마지막 곡의 다음 곡이 처음 곡이 되도록)
    if (tail != NULL) {
        tail->link = head;
    }

    // 5. 출력: 반복 재생 목록 확인하기
    // 리스트를 한 바퀴(K번) 돌면서 저장된 노래 제목을 출력합니다.
    if (head != NULL) {
        node* curr = head; // 현재 위치를 추적할 포인터를 첫 번째 노드로 설정
        for (int i = 0; i < K; i++) {
            printf("%s ", curr->data); // 현재 노드의 노래 제목 출력
            curr = curr->link;         // 다음 노드로 이동 (마지막에선 다시 head로 이동함)
        }
    }

    // 6. 메모리 해제
    free(head);

    return 0;
}