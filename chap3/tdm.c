// TDM(Term-Document Matrix)에서 0이 아닌 값만 추출해서 출력

// 입력 조건
// N개의 단어, 단어 목록
// M개의 문서
// N×M 행렬 (각 단어가 각 문서에 몇 번 나오는지)

// 출력 조건
// 0이 아닌 원소만 단어 문서번호 빈도수 형태로 출력

#include <stdio.h>
#include <windows.h>

int main() {
    // 입출력 시 한글 깨짐 방지
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // 1. 변수 선언
    int N, M;  // 단어(N) 및 문서 개수(M)
    char terms[31][21];  // 단어 개수와 단어의 길이
    int matrix[31][51];  // 전체 크기 (단어 개수 * 문서 개수)

    // 2. 단어 개수, 단어, 문서 개수 입력
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s", terms[i]);
    }

    scanf("%d", &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // 3. 0이 아닌 값만 출력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] == 0) {
                continue;
            }
            printf("%s 문서%d %d\n", terms[i], j + 1, matrix[i][j]);
        }
    }

    return 0;
}
