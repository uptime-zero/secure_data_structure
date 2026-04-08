/* 문제
1. 보물상자는 원형으로 놓여 있음
2. 보물상자를 열면 다음에 열어야 하는 보물상자의 위치가 적힌 종이가 있음
3. 이때 오른쪽으로 이동하는 경우 `숫자`로 적혀있고, 왼쪽으로 이동하는 경우 `-숫자`로 적혀있음
3. 이미 열어 놓은 보물상자는 위치 계산에서 제외
*/

/* 입력 조건
- 첫째 줄에 보물상자의 개수(N)가 주어짐 (1 <= N <= 10)
- 둘째 줄에 각 보물상자 안에 들어 있는 다음 보물상자 위치를 나타내는 숫자 N개가 주어짐
*/

/* 출력 조건
- 첫째 줄에 보물상자를 여는 순서를 출력
*/

/* 접근 방법
- 보물상자가 원형으로 놓여있다
   -> 원형 연결 리스트
- 다음 보물상자의 위치는 정수 값이다
   -> 양방향
- 이미 열어 놓은 보물상자는 위치 계산에서 제외한다.
   -> 탐색 완료한 상자는 링크 제외
- 선언한 보물상자의 개수는 고정적임. 추가되거나 하지 않음
   -> 고정적인 크기를 가짐
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Treasure {
    int id;  // 현재 보물상자의 번호
    int move;  // 다음 보물상자의 위치
    struct Treasure *l_link;
    struct Treasure *r_link;
} treasure;


int main() {
    // 1. 보물상자 개수 선언
    int N;
    scanf("%d", &N);

    // 2. 입력 값 검증
    if (N < 1 || N > 10) {
        printf("Invalid input");
        return 1;
    }

    // 3. 구조체 메모리 할당 및 데이터 초기화
    treasure* nodes = malloc(sizeof(treasure) * N);
    for (int i = 0; i < N; i++) {
        nodes[i].id = i + 1;
        scanf("%d", &nodes[i].move);
    }
    
    // 4. 이중 원형 연결 리스트 연결
    for (int i = 0; i < N; i++) {
        nodes[i].l_link = &nodes[(i - 1 + N) % N];
        nodes[i].r_link = &nodes[(i + 1) % N];
    }
    
    treasure* curr = &nodes[0];

    // 5. 보물상자 열기 로직
    for (int i = 0; i < N; i++) {
        printf("%d ", curr->id);

        // 마지막 상자는 계산할 필요 없음
        if (i == N - 1) {
            break;
        }
        
        int next = curr->move;

        // 현재 상자를 연결 고리에서 제거 (건너뛰기 설정)
        curr->l_link->r_link = curr->r_link;  // 열린 상자의 왼쪽 상자의 오른쪽 링크를 열린 상자의 오른쪽 링크로 재설정
        curr->r_link->l_link = curr->l_link;  // 열린 상자의 오른쪽 상자의 왼쪽 링크를 열린 상자의 왼쪽 링크로 재설정

        // 이동
        if (next > 0) {
            for (int j = 0; j < next; j++) {
                curr = curr->r_link;
            }
        } else {
            for (int j = 0; j < abs(next); j++) {
                curr = curr->l_link;
            }
        }
    }
    
    // 6. 메모리 해제
    // malloc 선언 시 고정 크기로 생성했기 때문에 한 번에 해제할 수 있음
    free(nodes);
    
    return 0;
}