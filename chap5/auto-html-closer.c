/* 문제
1. stack의 종료 태그에는 종료 태그가 따로 있는 유형과 시작 태그에서 닫을 수 있는 두 가지 유형이 존재
2. 종료 태그가 따로 있는 유형의 경우 [enter] 시 자동으로 해당 태그에 맞는 종료 태그를 입력함
*/

/* 입력 조건
1. 첫째 줄부터 종료 태그 없는 stack 코드가 주어진다. 
    - 단, 종료 태그를 넣고 싶은 자리에 [enter]를 치고 입력이 끝나면 마침표를 입력한다.
2. 입력 예시
```
<body> <div> <img src="demo.jpg"/> [enter]
<div> <a href="https://www.hanbit.co.kr/acadamy/"> 한빛아카데미 [enter]
[enter]
[enter]
.
```
*/

/* 출력 조건
1. 첫째 줄부터 종료 태그가 추가된 stack 코드를 출력한다.
2. 출력 예시
```
<body> <div> <img src="demo.jpg"> </div> <div> <a href="https://www.hanbit.co.kr/acadamy/"> 한빛아카데미 </a> </div> </body>
```
*/

/* 접근 방법
- 종료 태그의 경우 나중에 열린 태그를 먼저 닫아야 함
    -> stack
- 종료 태그엔 두 가지 유형이 존재함
    -> 종료 태그가 별도로 필요한 경우에만 스택에 push
- 종료 태그를 입력하고 싶은 곳에 [enter]
    -> [enter]를 입력하면 stack에서 pop
- 입력이 끝나면 마침표를 입력
    -> 마침표 입력 시 stack이 빌 때까지 pop
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100   // 스택에 담을 수 있는 최대 태그 개수
#define MAX_LINE_LENGTH 1024 // 한 줄에 입력받을 수 있는 최대 문자 길이

char stack[MAX_STACK_SIZE][50]; // 태그 이름(문자열)을 저장하는 2차원 배열 스택
int top = -1;                   // 스택의 최상단을 가리키는 인덱스 (빈 상태는 -1)

void push(char* tag) {
    if (top < MAX_STACK_SIZE - 1) {
        strcpy(stack[++top], tag);
    } else {
        printf("\n저장 가능한 스택의 크기를 넘어섰습니다. 더 이상 저장할 수 없습니다.\n");
        return;
    }
}

char* pop() {
    return (top >= 0) ? stack[top--] : NULL;
}

// 태그 전체(<div class="abc">)에서 순수 이름(div)만 뽑아내는 함수
void extract_tag_name(char* full_tag, char* res) {      // full_tag: 전체 태그 문자열(<div>), res: 실제 태그의 이름만 저장할 공간
    int i = 0, j = 0;

    // '<' 나 '/' 기호는 건너뜀
    while (full_tag[i] == '<' || full_tag[i] == '/') {
        i++;    // 태그의 이름이 시작되는 위치
    }

    // 공백, '>', '/'를 만나기 전까지의 문자가 실제 태그 이름
    while (full_tag[i] != ' ' && full_tag[i] != '>' && full_tag[i] != '/' && full_tag[i] != '\0') {     // 공백: 속성, /: 스스로 닫히는 태그, >: 닫힘 태그
        res[j++] = full_tag[i++];   // full_tag[1] = 'd' -> res[j++] = res[0] = 'd'
    }

    res[j] = '\0'; // 문자열 끝 표시
}

int main() {
    char line[MAX_LINE_LENGTH];              // 사용자로부터 입력받은 한 줄을 저장하는 버퍼
    char result[MAX_LINE_LENGTH * 8] = "";   // 최종 조립된 전체 코드를 저장할 큰 버퍼

    while (1) {
        // 입력을 받음 (입력이 없으면 종료)
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        
        // 줄바꿈 문자(\n)를 제거하여 순수 문자열만 남김
        // 입력 버퍼에서 개행 문자 전까지의 개수를 구하면 항상 입력 버퍼에 들어간 길이 - 1이 됨.
        // 이는 인덱스에서 마지막 위치여서 자연스레 입력 배열 상의 마지막(개행 문자)을 널 문자로 바꿀 수 있다.
        line[strcspn(line, "\n")] = '\0';   

        // 1. 종료 조건: 마침표(.)만 입력되면 루프 탈출
        if (strcmp(line, ".") == 0) {   // line에 입력된 문자열이 "."과 같다면 strcmp에 의해 0을 반환함
            break;
        }

        // 2. 엔터만 입력된 경우 (빈 줄 처리)
        if (strlen(line) == 0) {    // 입력된 문자열의 길이가 0일 경우
            char* tag = pop();      // 스택에서 태그 하나를 꺼냄

            if (tag) {
                strcat(result, "</"); strcat(result, tag); strcat(result, "> ");
            }

            continue;
        }

        // 3. 일반 텍스트 및 태그 분석
        char* ptr = line;         // 문자열 내에서 '<' 기호를 찾기 위해 움직이는 탐색 포인터. 
        char* last_ptr = line;    // 마지막으로 결과 버퍼(result)에 복사했던 지점을 기억하는 포인터.

        // line 문자열 안에서 '<' 기호를 찾을 때까지 반복
        while ((ptr = strchr(ptr, '<')) != NULL) {  // 문자열 내 '<'를 찾아서 해당 위치의 주소를 저장함
            // last_ptr부터 '<' 기호 전까지의 일반 문자/공백 길이를 계산
            int text_len = ptr - last_ptr;
            if (text_len > 0) {
                // 태그 앞에 있던 공백이나 텍스트를 결과 버퍼에 그대로 복사
                strncat(result, last_ptr, text_len);    // 출력 버퍼에 last_ptr 위치 뒤로 text_len 개를 복사한다는 의미
            }

            // '>' 기호를 찾아 태그의 끝을 확인
            char* end_ptr = strchr(ptr, '>');       // 문자열 내 '>'를 찾아서 해당 위치의 주소를 저장함
            if (end_ptr) {
                int tag_len = end_ptr - ptr + 1;    // <div>라면 end_ptr(104) - ptr(100) + 1 = 4 + 1 = 5 (`<div>` 길이와 같음)
                char full_tag[100];                 // 추출된 태그 전체 문자열 임시 저장
                
                strncpy(full_tag, ptr, tag_len);    // 전체 태그에 ptr(100)부터 tag_len(5) 개수만큼 복사
                full_tag[tag_len] = '\0';           // [0] ~ [4]: 태그가 저장된 곳, [lag_len] = [5]에 널 문자를 넣어 문자열의 끝을 표시

                strcat(result, full_tag); // 결과 버퍼에 태그 추가

                // 여는 태그이면서 동시에 셀프 클로징(/>) 태그가 아닐 때만 스택에 저장
                if (full_tag[1] != '/' && full_tag[tag_len - 2] != '/') {
                    char tag_name[50];
                    extract_tag_name(full_tag, tag_name); // 이름만 추출 (예: div)
                    push(tag_name);                       // 스택에 push
                }
                
                ptr = end_ptr + 1; // 다음 탐색 지점 설정
                last_ptr = ptr;    // 처리 완료 지점 갱신
            } else {
                ptr++; // 닫는 괄호가 없으면 다음 문자로 이동
            }
        }
        
        // 태그 탐색이 끝난 후 줄 뒷부분에 남은 텍스트를 복사
        strcat(result, last_ptr);

        // 한 줄 입력(엔터)이 끝날 때마다 스택에서 가장 최근 태그 하나를 닫아줌
        char* tag = pop();
        if (tag) {
            strcat(result, " </"); strcat(result, tag); strcat(result, "> ");
        }
    }

    // 4. 전체 입력 종료 후 스택에 남은 모든 태그를 순서대로 닫아줌
    while (top >= 0) {
        strcat(result, "</"); strcat(result, pop()); strcat(result, "> ");
    }

    // 최종 완성된 결과 출력
    printf("%s\n", result);
    return 0;
}