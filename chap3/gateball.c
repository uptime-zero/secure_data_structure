// 공은 항상 (1, 1) 위치에서 시작
// 스윙 기록(L, R, U, D)을 순서대로 따라가면서 공을 이동
// 각 칸의 경계선마다 게이트(ㅁ) 가 설치되어 있음
// 이동하려는 방향에 게이트가 있으면 → 이동 가능
// 이동하려는 방향에 게이트가 없으면(벽) → 헛스윙, 제자리

// 입력 조건
// 첫째 줄에 훈련장의 크기를 나타내는 N이 주어짐 (1 <= N <= 50)
// 둘째 줄에 스윙 기록이 주어짐 (1 <= 스윙 횟수 <= 50)

// 출력 조건
// 첫째 줄에 공의 마지막 위치를 (x, y) 형태로 출력

#include <stdio.h>
#include <string.h>

int main() {
    // 1. 변수 선언
    int N;  // 훈련장의 크기
    int row = 1, col = 1;  // 현재 공의 위치, 공의 시작 위치는 항상 (1, 1)
    char swings[51];  // 스윙 획수 최대 50번 + '\0' 저장을 위해 51로 선언
    int len;  // 스윙 횟수

    // 2. 입력
    scanf("%d", &N);
    scanf("%s", swings);

    // 3. 스윙 횟수 구하기
    len = strlen(swings);

    // 4. 기록 처리
    for (int i = 0; i < len; i++) {
        // 이동해야 하는 방향
        char swing = swings[i];

        // 5. 이동 로직 작성
        // 위: row 값이 1보다 커야 이동 가능
        // 아래: row 값이 N보다 작아야 이동 가능
        // 왼쪽: col 값이 1보다 커야 이동 가능
        // 오른쪽: col 값이 N보다 작아야 이동 가능
        if (swing == 'U') {
            if (row > 1) {
                row--;
            }
        } else if (swing == 'D') {
            if (row < N) {
                row++;
            }
        } else if (swing == 'L') {
            if (col > 1) {
                col--;
            }
        } else if (swing == 'R') {
            if (col < N) {
                col++;
            }
        }
    }

    // 6. (x, y) 형식으로 출력
    printf("(%d, %d)\n", row, col);

    return 0;
}
