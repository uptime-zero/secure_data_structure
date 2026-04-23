/* 문제
1. 게임 화면은 1*1 크기의 칸으로 이뤄진 5*10 크기로 세로 칸에 들어간 구슬의 숫자로 점수를 계산
2. 구슬에는 1~5의 번호가 적혀있고, 한 칸을 차지하며 세로 줄의 가장 아래 칸부터 쌓임
3. 게임 시작 시 각 세로 칸에 최대 3개의 구슬이 들어있는 상태로 시작함 (0은 구슬이 없는 상태)
4. 세로 칸의 맨 위에 있는 구슬의 번호와 같은 번호의 구슬을 넣으면 두 개의 구슬이 함께 사라짐
5. 게임이 끝나면 각 세로 칸에 들어 있는 구슬의 개수로 점수를 계산하고, 점수는 각 세로 칸마다 다름
*/

/* 입력 조건
1. 첫째 줄에 핀볼의 시작 상태가 주어짐
    > 0 0 0 0 0 0 0 2 0 4 2 0 5 3 1
2. 둘째 줄에 각 세로 칸의 점수를 나타내는 숫자 다섯 개가 주어짐
    > 30 20 40 10 20
3. 셋째 줄에 구슬의 번호와 구슬이 들어갈 세로 칸 번호의 숫자로 구성된 10쌍의 숫자가 주어짐
    > 5 1, 3 5, 3 2, 2 3, 4 2, 3 4, 5 4, 5 3, 2 1, 1 3
식: 세로 칸에 할당된 점수 * 세로 칸에 들어 있는 구슬 번호를 더한 값 = 세로 칸의 점수
*/

/* 출력 조건
- 각 세로 칸의 점수를 출력함
> (270점, 140점, 40점, 50점, 168점)
*/

/* 접근 방법
- 구슬이 들어갈 때 세로 줄의 가장 아래 칸부터 쌓임
    -> stack
- 세로 칸의 맨 위에 있는 구슬의 번호와 같은 번호의 구슬이 만나면 두 두슬이 함께 사라짐
    -> peek로 확인한 결과가 현재 들어오는 구슬의 번호와 같다면 stack에서 pop하고 구슬을 넣지 않음
- 첫째 줄에 핀볼의 시작 상태가 주어짐
    -> 3행 5열로 읽어서 push
- 배열과 구조체 중 어떤 방법을 사용하는 것이 좋을까에 대한 고찰
    -> 배열만 사용하게 되면 스택, 각 스택의 top level, 각 스택이 부여받은 score를 모두 인자로 넘겨야 함
    -> 구조체 사용 시 열 하나를 하나의 스택으로 관리하여 넘길 수 있음
*/

#include <stdio.h>

#define COLS 5   // 세로 칸 개수
#define ROWS 10  // 각 칸의 최대 높이

// 세로 칸 하나를 표현하는 구조체
typedef struct {
    int data[ROWS]; // 구슬 데이터
    int top;        // 현재 맨 위 인덱스 (-1이면 빈 스택)
    int score;      // 해당 칸의 점수 단가
} Lane;

int isEmpty(Lane* lane) {
    return lane->top == -1;
}

int isFull(Lane* lane) {
    return lane->top == ROWS - 1;
}

int peek(Lane* lane) {
    if (isEmpty(lane)) return -1;
    return lane->data[lane->top];
}

void push(Lane* lane, int ball) {
    if (isFull(lane)) return;
    lane->data[++(lane->top)] = ball;
}

void pop(Lane* lane) {
    if (isEmpty(lane)) return;
    lane->top--;
}

// 시작 상태로 스택 초기화
void initLanes(Lane lanes[]) {
    // 15개의 숫자가 입력됨 -> 3행 5열로 변환
    int pinBalls[3][COLS];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < COLS; j++) {
            scanf("%d", &pinBalls[i][j]);
        }
    }

    // push 진행
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < COLS; j++) {
            // 0이 아닐 경우에만 push
            if (pinBalls[i][j] != 0) {
                push(&lanes[j], pinBalls[i][j]);
            }
        }
    }
}

// 각 칸의 점수 단가 입력
void initScores(Lane lanes[]) {
    for (int i = 0; i < COLS; i++) {
        scanf("%d", &lanes[i].score);
    }
}

// 구슬 10쌍 처리
// 입력 형식: 5 1, 3 5, 3 2, ...
void processPlayBalls(Lane lanes[]) {
    for (int i = 0; i < 10; i++) {
        int ball, col;
        char comma;

        if (i < 9) {
            scanf("%d %d,", &ball, &col); // 숫자 두 개 읽고 쉼표까지 소비
        } else {
            scanf("%d %d", &ball, &col);   // 마지막 쌍은 쉼표 없음
        }

        col--;

        // peek한 값이 현재 구슬 번호와 같으면 pop, 아니면 push
        if (peek(&lanes[col]) == ball) {
            pop(&lanes[col]);
        } else {
            push(&lanes[col], ball);
        }
    }
}

// 최종 점수 계산 및 출력
void printScores(Lane lanes[]) {
    printf("(");
    for (int i = 0; i < COLS; i++) {
        // 구슬 번호 전부 더하기
        int sum = 0;
        for (int j = 0; j <= lanes[i].top; j++) {
            sum += lanes[i].data[j];
        }
        int total = lanes[i].score * sum; // 칸 점수 × 번호 합계
        if (i < COLS - 1) {
            printf("%d점, ", total);
        } else {
            printf("%d점", total);
        }
    }
    printf(")\n");
}

int main() {
    // 5개 세로 칸 초기화
    Lane lanes[COLS];
    for (int i = 0; i < COLS; i++) {
        lanes[i].top = -1;  // 빈 스택
        lanes[i].score = 0;
    }

    initLanes(lanes);       // 시작 상태 초기화
    initScores(lanes);      // 점수 단가 입력
    processPlayBalls(lanes); // 구슬 10쌍 처리
    printScores(lanes);     // 결과 출력

    return 0;
}
