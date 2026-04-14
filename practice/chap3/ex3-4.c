#include <stdio.h>

int insertElement(int L[], int size, int data) {
    int i, k = 0, move = 0;

    /* 현재 배열에서 값이 들어가 있는 크기
     * 예를 들어 전체 크기가 10인 배열에 원소가 5개 들어가 있을 경우
     * 현재 크기 = 5 | 인덱스 = 4
     */
    for (i = 0; i < size; i++) {
        if (L[i] <= data && data <= L[i + 1]) {  // 정렬된 배열에서 data의 값의 위치를 구하기 위함
            k = i + 1;  // i 번째 위치 다음에 data가 위치할 예정이기 때문에 1을 더해준다.
            break;
        }
    }

    if (i == size) {
        k = i + 1;
    }

    // size는 항상 인덱스보다 1 크기 때문에 기존 요소들의 인덱스 위치가 1씩 늘어나게 된다.
    for (i = size; i > k; i--) {
        L[i] = L[i - 1];
        move++;
    }

    L[k] = data;
    return move;
}

int deleteElement(int L[], int size, int data) {
    int i, k = 0, move = 0;
    for (i = 0; i < size; i++) {
        if (L[i] == data) {
            k = i;
            break;
        }
    }

    if (i == size) {
        k = size;
    }

    // 요소 삭제의 경우 덮어쓰면 되기 때문에 역방향으로 반복문을 만들 필요가 없음
    for (i = k; i < size; i++) {
        L[i] = L[i + 1];
        move++;
    }

    return move;
}

int main() {
    int arr[10] = {10, 20, 40, 50};
    int count = 4;

    insertElement(arr, 4, 30);
    count++;

    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}