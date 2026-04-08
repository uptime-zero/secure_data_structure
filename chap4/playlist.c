/* 문제 
1. 선택한 노래만 선택한 순서대로 반복 재생
2. 음악 제목은 a-zA-Z (알파벳 대소문자)로만 이뤄져 있음
*/

/* 입력 조건
- 첫째 줄에 음악 목록에 있는 음악 개수 N과 반복 재생할 음악 개수 K가 주어짐 (1 <= N <= 52, 1 <= K <= 52)
- 둘째 줄에 연속 재생할 음악 제목 K개가 주어짐
*/

/* 출력 조건
- 첫째 줄에 반복 재생 목록에 있는 노래 제목을 출력
*/

/* 점근 방법
- 선택한 노래만 순서대로 반복 재생
   - 선택한 노래 이외는 생각하지 않아도 됨
   - 반복 재생이기 때문에 원형 연결 리스트
   - 역방향으로 재생된다는 조건이 없으므로 단방향
- 음악 제목은 알파벳으로만 이뤄져 있음
   - 알파벳으로만 이뤄져 있는지 검증 필요
- 재생 목록의 크기
   - 두 번째 줄에서 입력 받는 노래 제목이 곧 반복하려는 노래 제목이기 때문에 의미 없음
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Track {
    char data[100];      // 음악 제목을 저장할 배열 (알파벳 대소문자)
    struct Track* link;   // 다음 트랙의 주소를 가리키는 포인터
} track;

int main() {
    // 1. 변수 선언
    int N, K;
    track *head = NULL;   // 리스트의 시작점을 가리키는 포인터
    track *curr = NULL;   // 리스트의 현재 위치을 가리키는 포인터

    // 2. 전체 음악 개수 N과 재생할 음악 개수 K 입력받기
    scanf("%d %d", &N, &K);

    // 3. 입력 값 유효성 검증
    if (N < 1 || N > 52 || N < 1 || K > 52) {
        printf("음악 개수는 1이상 52이하여야 합니다.\n");
        return 1;
    }

    // 4. K개의 음악 제목을 입력받아 리스트 만들기
    for (int i = 0; i < K; i++) {
        char input[100];

        track* newTrack = malloc(sizeof(track));

        // 5. 제목 입력 및 유효성 검증
        scanf("%s", input);
        for (int j = 0; j < strlen(input); j++) {
            if (!isalpha(input[j])) {
                printf("음악 제목은 알파벳 대소문자여야 합니다.");
            }
        }
        
        strcpy(newTrack->data, input);  // 배열 이름은 상수 포인터이기 때문에 대입 연산자로 문자열을 한 번에 넣을 수 없어서 strcpy 사용

        newTrack->link = NULL;  // 새로 만든 노드는 다음 연결 대상이 없으므로 NULL로 설정

        if (head == NULL) {  // 리스트가 비었을 경우
            head = newTrack;
        } else {  // 리스트에 값이 있을 경우 curr이 가리키는 트랙의 다음 트랙을 새로 만든 트랙의 주소로 설정
            curr->link = newTrack;
        }

        curr = newTrack;  // curr 최신화
    }

    // 4. 원형 연결 (마지막 곡의 다음 곡이 처음 곡이 되도록)
    if (curr != NULL) {
        curr->link = head;
    }

    // 5. 출력: 반복 재생 목록 확인하기
    if (head != NULL) {
        track* curr = head; // 현재 위치를 추적할 포인터를 첫 번째 노드로 설정
        for (int i = 0; i < K; i++) {
            printf("%s ", curr->data); // 현재 노드의 노래 제목 출력
            curr = curr->link;         // 다음 노드로 이동 (마지막에선 다시 head로 이동함)
        }
    }

    // 6. 메모리 해제
    curr = head;
    for (int i = 0; i < K; i++) {
        track* tmp = curr->link;
        free(curr);
        curr = tmp;
    }
    

    return 0;
}