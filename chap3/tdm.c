// TDM(Term-Document Matrix)에서 0이 아닌 값만 추출해서 출력

// 입력 조건
// N개의 단어, 단어 목록
// M개의 문서
// N×M 행렬 (각 단어가 각 문서에 몇 번 나오는지)

// 출력 조건
// 0이 아닌 원소만 단어 문서번호 빈도수 형태로 출력

#include <stdio.h>
#include <windows.h>

typedef struct {
    int row;
    int col;
    int val;
} Element;

int main() {
    // 입출력 시 한글 깨짐 방지
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // 1. 변수 선언
    int N, M;  // 단어(N) 및 문서 개수(M)
    char terms[31][21];  // 단어 개수와 단어의 길이
    Element sparse_matrix[1500];  // 전체 크기 (N과 M을 입력받고 선언하는 것이 제일 좋긴 함 -> malloc 또는 sparse_matrix[N * M])
    int count = 0;  // 실제로 저장된 원소 개수

    // 2. 단어 개수, 단어, 문서 개수 입력
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", terms[i]);
    }

    scanf("%d", &M);

    // 3. TDM을 읽으면서 0이 아닌 것만 바로 희소 행렬에 저장
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int input_value;
            scanf("%d", &input_value);

            if (input_value != 0) {
                sparse_matrix[count].row = i;
                sparse_matrix[count].col = j;
                sparse_matrix[count].val = input_value;
                count++; // 저장된 원소 개수 증가
            }
            // 0이면 저장 안 함
        }
    }

    // 4. 희소 행렬을 순서대로 출력
    for (int i = 0; i < count; i++) {
        printf("%s 문서%d %d\n",
            terms[sparse_matrix[i].row],   // 행 번호 → 단어
            sparse_matrix[i].col + 1,      // 열 번호 → 문서번호 (1부터 시작)
            sparse_matrix[i].val
        );
    }

    return 0;
}
