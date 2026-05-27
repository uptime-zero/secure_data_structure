/** 문제
 * (1,1)에서 (N,N)까지 미로를 탈출하는 경로를 출력한다.
 * 0은 지나갈 수 있는 공간, 1은 지나갈 수 없는 벽이다.
 * 시작점에서부터 이동 가능한 길을 찾아 도착점까지 이동한다.
 * 최단 거리 등의 조건이 없기 때문에 dfs, bfs 어떤 것을 사용해도 크게 상관 없다.
 */

/** 접근 방법
 * 정점의 크기가 크지 않음.
 * 그래프의 정점이 격자 형태, 즉 정점 자체가 좌표로 표현되는 형태임
 * 인접 정점을 탐색하는 경우 배열이 더 직관적이고, 빠름
 * -> 배열 방식으로 구현
 */

/** 입력 조건
 * 1. 첫째 줄에 미로의 크기 N이 주어진다. (N <= MAX)
 * 2. 둘째 줄부터 N+1줄까지 미로 지도는 한 줄에 N개 숫자로 주어진다.
 * > 5
 * > 0 1 1 0 1
 * > 0 0 0 1 1
 * > 0 1 0 1 0
 * > 0 0 0 1 1
 * > 0 0 0 0 0
 */

/** 출력 조건
 * 1. 첫째 줄에 미로 탈출 경로 좌표를 출력한다.
 * > (1,1) (2,1) (2,2) (2,3) (3,3) (4,3) (5,3) (5,4) (5,5)
 */

#include <stdio.h>
#define MAX 20

typedef struct {
    int row;
    int col;
} Pos;  // position

Pos queue[MAX * MAX];
int head = -1;
int tail = -1;

int N;
int map[MAX][MAX];
int isVisited[MAX][MAX];
Pos parent[MAX][MAX];
int counter = 1;

void enQueue(int row, int col) {
    if (tail < (MAX * MAX) - 1) { 
        queue[++tail] = (Pos){row, col};
    }
}

Pos deQueue() {
    if (head <= tail) {
        return queue[++head];
    }
}

void bfs() {
    enQueue(0, 0);  // 시작점 좌표 큐에 삽입
    isVisited[0][0] = 1;    // 시작점 방문 체크
    parent[0][0] = (Pos){-1, -1}; // 시작점의 부모는 없음

    // 방향 벡터: 우->하->좌->상 순서 (순서는 크게 의미없음)
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};

    while (head < tail) {   // 큐에 내용이 남아있지 않으면 종료
        // 현재 위치를 얻기 위해서 deQueue()
        Pos curr = deQueue();

        // 현재 위치가 도착점이라면 반복문을 빠져나감
        if (curr.row == N - 1 && curr.col == N - 1) {
            break;
        }

        // 현재 위치를 기준으로 방향 벡터 값을 더해서 갈 수 있는 길을 탐색하는 과정
        for (int i = 0; i < 4; i++) {
            // curr = (0, 0) 일 때
            // 첫 번째 탐색: (0, 0) + (dr[0], dc[0]) => (0, 0) + (0, 1) => (0, 1) 탐색 (오른쪽 이동)
            // 두 번째 탐색: (0, 0) + (dr[1], dc[1]) => (0, 0) + (1, 0) => (1, 0) 탐색 (아래 이동)
            // 세 번째 탐색: (0, 0) + (dr[2], dc[2]) => (0, 0) + (0, -1) => (0, -1) 탐색 (왼쪽 이동)
            // 네 번째 탐색: (0, 0) + (dr[3], dc[3]) => (0, 0) + (-1, 0) => (-1, 0) 탐색 (위 이동)
            int nr = curr.row + dr[i];
            int nc = curr.col + dc[i];

            // 맵 범위 밖으로 나가지 않는지 확인
            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                // 막혀있지 않은지 확인
                if (map[nr][nc] == 0) {
                    // 방문한 적이 있는지 확인
                    if (!isVisited[nr][nc]) {
                        counter++;
                        isVisited[nr][nc] = 1;  // 현재 위치 방문함 체크
                        parent[nr][nc] = curr;  // 현재 위치(curr)를 부모로 기록. 출력 역탐색 시 사용
                        enQueue(nr, nc);        // 현재 위치에서 재탐색을 위해 다시 큐에 삽입
                    }
                }
            }
        }
    }
}

int main() {
    // 미로의 크기 입력 받음
    scanf("%d", &N);

    // 입력 값 검증
    if (N < 0 && N > 20) {
        return 1;
    }

    // 미로의 길 입력 받음
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &map[i][j]);

    // BFS 시작
    bfs();

    // 도착점에 방문하지 않았다면 탐색 실패
    if (!isVisited[N - 1][N - 1]) {
        printf("경로가 없습니다.");
        return 1;
    }

    // 경로 역추적
    // 이때 parent에는 bfs로 탐색하여 이동한 경로가 저장되어 있지만 역순으로 타고 올라갈 때 도착->시작까지 체이닝되는 경로는 단 하나임
    // 이게 가능한 이유는 논리적으로 같은 위치에 도달할 수 있더라도 물리적으로는 deQueue로 나오는 순서와 방문 여부 체크를 통해 먼저 도착한 경로만 선점하기 때문
    Pos path[MAX * MAX];    // 역순으로 저장된 parent를 다시 시작점부터 도착점까지의 순서로 저장할 때 사용
    int count = 0;          // 반복할 횟수 카운팅
    int curr_row = N - 1;   // 현재 행의 위치
    int curr_col = N - 1;   // 현재 열의 위치
    
    while (curr_row != -1) {    // 시작점의 부모 값 (-1, -1)이 나오기 전까지 탐색
        path[count++] = (Pos){curr_row, curr_col};
        Pos p = parent[curr_row][curr_col]; // parent[0][0] = {-1, -1} 처럼 parent에는 현재 위치한 좌표를 인덱스로 접근 시 이전에 위치한 좌표의 내용이 값으로써 나온다.
        curr_row = p.row;   // 현재 위치 재설정을 통해 계속 탐색을 이어갈 수 있음
        curr_col = p.col;
    }

    // 결과 출력
    for (int i = count - 1; i >= 0; i--) {
        printf("(%d, %d) ", path[i].row + 1, path[i].col + 1);  // 출력 시 좌표는 (1, 1)부터 시작이기 때문에 +1 해줌
    }

    printf("\ncounter: %d", counter);

    return 0;
}