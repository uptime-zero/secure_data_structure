/** 문제
 * 1. 결정 트리는 다중 분류 알고리즘으로 데이터 안에서 if/else 기반으로 규칙을 찾아 학습하여 트리 구조의 분류 규칙을 만든다.
 * 2. 이때 결정 트리의 구조는 규칙 조건을 나타내는 규칙 노드와 분류가 결정된 클래스값이 표시된 리프 노드로 구성된다.
 */

/** 입력 조건
 * 1. 첫째 줄에 노드의 개수 N이 주어진다. (3 <= N <= 30)
 * 2. 둘째 줄부터 N+1 번째 줄까지 노드 번호와 노드 내용이 주어진다. 단 노드 번호는 완전 이진 트리의 번호가 된다.
 * 3. N+2번째 줄에 규칙에 대한 답이 순서대로 주어진다.
 * > 9
 * > 1 날개가 있나요?
 * > 2 날 수 있나요?
 * > 3 털이 있나요?
 * > 4 까치
 * > 5 펭귄
 * > 6 빨리 움직이나요?
 * > 7 개구리
 * > 12 다람쥐
 * > 13 나무늘보
 * > false true false
 */

/** 출력 조건
 * 1. 첫째 줄에 결정된 클래스(리프 노드, 결정 노드)를 출력한다.
 * > 나무늘보
 */

#include <stdio.h>
#include <string.h>

#define MAX_NODES 32768 // 최악의 경우를 상정
#define MAX_STR_LEN 100

char tree[MAX_NODES][MAX_STR_LEN];

int main() {
    // 1. 변수 선언
    int N;
    scanf("%d", &N);

    if (N < 3 || N > 30) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
        int node_num;   // 노드 번호
        scanf("%d", &node_num); 
        scanf(" %[^\n]", tree[node_num]);   // 노드 번호에 넣을 내용 (질문 또는 결정)
    }

    int current_node = 1;
    char answer[6]; // true/false를 담을 문자열

    while (1) {
        if (strchr(tree[current_node], '?') == NULL) {  // 현재 노드에 물음표가 없다면 결정 노드이므로 break
            break;
        }

        if (scanf("%s", answer) == EOF) {   // 입력 데이터가 더이상 존재하지 않다면 break;
            break;
        }

        if (strcmp(answer, "true") == 0) {  // 입력한 내용이 true라면
            printf("현재 노드: tree[%d], 노드의 정보: %s\n", current_node, tree[current_node]);
            current_node = current_node * 2;    // 현재 노드에서 좌측 자식 노드로 이동
        } else {    // false라면
            printf("현재 노드: tree[%d], 노드의 정보: %s\n", current_node, tree[current_node]);
            current_node = current_node * 2 + 1;    // 현재 노드에서 우측 자식 노드로 이동
        }
    }

    printf("%s\n", tree[current_node]);
    return 0;
}