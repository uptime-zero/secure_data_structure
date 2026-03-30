cmake_minimum_required(VERSION 4.2)
project(secure_data_structure C)

set(CMAKE_C_STANDARD 99)

# chap* 폴더를 전부 자동으로 탐색
file(GLOB CHAP_DIRS "chap*")

foreach(CHAP_DIR ${CHAP_DIRS})
    # 폴더인지 확인
    if(IS_DIRECTORY ${CHAP_DIR})
        # 폴더 이름만 추출 (chap1, chap2 ...)
        get_filename_component(CHAP_NAME ${CHAP_DIR} NAME)

        # 해당 챕터 안의 모든 .c 파일 탐색
        file(GLOB C_FILES "${CHAP_DIR}/*.c")

        foreach(FILE ${C_FILES})
            # 확장자 제거한 파일명 추출 (ex01, ex02 ...)
            get_filename_component(FILE_NAME ${FILE} NAME_WE)

            # chap01_ex01 형태로 실행파일 등록
            add_executable(${CHAP_NAME}_${FILE_NAME} ${FILE})
        endforeach()
    endif()
endforeach()
