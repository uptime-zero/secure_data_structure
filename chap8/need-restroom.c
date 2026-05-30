#include <stdio.h>

#define MAX 51

// 그래프의 인접 행렬 및 상태 관리 배열
int graph[MAX][MAX];    // graph[u][v] = 1이면 u와 v는 연결된 상태
int visited[MAX];       // 방문한 건물인지 확인 (중복 탐색 방지)
int parent[MAX];        // 경로 역추적을 위해 각 노드에 도달하기 직전의 노드를 저장
int N, M;               // N: 건물의 총 개수, M: 도로의 총 개수

// BFS 탐색을 위한 큐(Queue)와 인덱스
int queue[MAX];
int head = 0;
int tail = 0;

int isQueueFull() {
    return tail >= MAX;
}

int isQueueEmpty() {
    return head >= tail;
}

// 큐 삽입 함수
void enQueue(int node) {
    if (isQueueFull()) {
        printf("큐가 가득 찼습니다.\n");
        return;
    }
    queue[tail++] = node;
}

int deQueue() {
    if (isQueueEmpty()) {
        printf("큐가 비어있습니다.\n");
        return -1;
    }
    return queue[head++];
}

int main() {
    // 1. 입력 받기: 건물의 개수 N과 도로의 개수 M
    if (scanf("%d %d", &N, &M) != 2) {
        printf("잘못된 입력입니다.\n");
        return 1;
    }

    // 입력값 범위 유효성 검증
    if (N < 1 || N > 50) {
        printf("N은 1 이상 50 이하여야 합니다.\n");
        return 1;
    }

    if (M < 1 || M > 50) {
        printf("M은 1 이상 50 이하여야 합니다.\n");
        return 1;
    }

    // 2. 그래프 구성: 인접 행렬(graph)에 연결 정보 저장
    for (int i = 0; i < M; i++) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) {
            printf("잘못된 입력입니다.\n");
            return 1;
        }

        // 노드 번호 범위 유효성 검증
        if (u < 1 || u > N || v < 1 || v > N) {
            printf("노드 번호는 1 이상 %d 이하여야 합니다.\n", N);
            return 1;
        }

        // 자기 자신과의 연결 방지
        if (u == v) {
            printf("자기 자신과는 연결할 수 없습니다.\n");
            return 1;
        }

        graph[u][v] = 1; // 양방향 도로이므로
        graph[v][u] = 1; // 양쪽 모두 1로 표기
    }

    // 3. BFS 초기 설정
    enQueue(1);           // 시작 위치(건물 1)를 큐에 삽입
    visited[1] = 1;       // 시작 위치 방문 체크
    parent[1] = -1;       // 시작점은 이전 노드가 없으므로 -1로 초기화

    // BFS 수행
    while (!isQueueEmpty()) {
        int u = deQueue(); // 현재 위치를 큐에서 추출

        if (u == -1) {
            break; // deQueue 실패 시 종료
        }

        // 현재 위치가 도착지(화장실, 건물 N)라면 탐색 중단
        if (u == N) {
            break;
        }

        // 현재 위치(u)와 연결된 모든 건물(v) 탐색
        for (int v = 1; v <= N; v++) {
            // 연결되어 있고(graph[u][v] == 1) 아직 방문하지 않은 건물이라면
            if (graph[u][v] == 1 && !visited[v]) {
                visited[v] = 1;       // 방문 처리
                parent[v] = u;        // v에 도달하기 직전 위치(u)를 부모로 기록 (역추적용)
                enQueue(v);           // 다음 탐색을 위해 큐에 삽입
            }
        }
    }

    // 경로 도달 가능 여부 확인
    if (!visited[N]) {
        printf("경로가 존재하지 않습니다.\n");
        return 1;
    }

    // 4. 경로 역추적
    // parent 배열에는 도착점에서 시작점까지 연결된 이정표가 저장되어 있음
    int path[MAX];
    int count = 0;
    int curr = N; // 도착지점부터 거꾸로 추적 시작

    // 시작점의 부모값(-1)이 나오기 전까지 반복
    while (curr != -1) {
        path[count++] = curr;
        curr = parent[curr]; // 현재 노드의 부모 노드로 계속 이동
    }

    // [출력]: 경로가 도착점->시작점 순으로 저장되어 있으므로, 역순으로 출력
    // 문제 출력 형식: (start, end) 형태
    for (int i = count - 1; i > 0; i--) {
        // path[i]가 이전 위치, path[i-1]이 다음 위치
        printf("(%d, %d)\n", path[i], path[i - 1]);
    }

    return 0;
}