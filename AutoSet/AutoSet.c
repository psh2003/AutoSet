#define _CRT_SECURE_NO_WARNINGS
#define MAX 80
#define MSIZE 16777216  // 16메가로 메모리 버퍼 지정
#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif
int fileCopy(const char* src, const char* dst);
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <direct.h>		//mkdir
#include <errno.h>		//errno
#include <string.h>
int copy(char* exist, char* anew);
int main(void)
{
    char name[MAX]="";
    char tempPath[MAX] = "D:\\Code\\";

    printf("프로젝트 이름을 입력하세요\n");
    scanf("%s", name);

    strcat(tempPath, name);
    printf(tempPath);
    int nResult = _mkdir(tempPath);

    if (nResult == 0)
    {
        printf("폴더 생성 성공\n");
    }
    else if (nResult == -1)
    {
        perror("폴더 생성 실패 - 폴더가 이미 있거나 부정확함\n");
        printf("errorno : %d", errno);
        system("pause > nul");
        return 0;
    }

    strcat(tempPath, "\\workspace");
    printf(tempPath);
    int nResult1 = _mkdir(tempPath);

    if (nResult1 == 0)
    {
        printf("폴더 생성 성공\n");
    }
    else if (nResult1 == -1)
    {
        perror("폴더 생성 실패 - 폴더가 이미 있거나 부정확함\n");
        printf("errorno : %d", errno);
        system("pause > nul");
        return 0;
    }
    char strChangeDir[_MAX_PATH] = { "D:\\Code" };

    int Result = _chdir(strChangeDir);
    char target[MAX];
    strcpy(target, name);
    strcat(target, "\\eclipse-jee-2020-06-R-win32-x86_64.zip");
    int e = fileCopy("D:\\Code\\eclipse-jee-2020-06-R-win32-x86_64.zip", target);

    if (e == 0)
        printf("파일이 복사되었습니다.\n");
    else {
        switch (e) {
        case  1: fputs("원본 파일을 열 수 없습니다.\n", stderr); break;
        case  2: fputs("대상 파일에 쓸 수 없습니다. 읽기 전용?\n", stderr); break;
        case  3: fputs("쓰기 에러, 디스크 용량 초과?\n", stderr); break;
        case  4: fputs("원본 경로와 대상 경로가 동일합니다\n", stderr); break;
        case 10: fputs("메모리가 부족합니다\n", stderr); break;
        default: fputs("알 수 없는 에러\n", stderr); break;
        }
    }

    int Result1 = _chdir(strChangeDir);
    strcpy(target,name);
    strcat(target, "\\apache-tomcat-8.5.73.zip");
    int f = fileCopy("D:\\Code\\apache-tomcat-8.5.73.zip", target);

    if (f == 0)
        printf("파일이 복사되었습니다.\n");
    else {
        switch (f) {
        case  1: fputs("원본 파일을 열 수 없습니다.\n", stderr); break;
        case  2: fputs("대상 파일에 쓸 수 없습니다. 읽기 전용?\n", stderr); break;
        case  3: fputs("쓰기 에러, 디스크 용량 초과?\n", stderr); break;
        case  4: fputs("원본 경로와 대상 경로가 동일합니다\n", stderr); break;
        case 10: fputs("메모리가 부족합니다\n", stderr); break;
        default: fputs("알 수 없는 에러\n", stderr); break;
        }
    }

    system("pause > nul");
    return 0;
}


// 파일 복사 함수의 본체
int fileCopy(const char* src, const char* dst) {
    FILE* in, * out;
    char* buf;
    size_t len;
    
    if (!_strcmpi(src, dst)) return 4; // 원본과 사본 파일이 동일하면 에러

    if ((in = fopen(src, "rb")) == NULL) return 1; // 원본 파일 열기
    if ((out = fopen(dst, "wb")) == NULL) { fclose(in); return 2; } // 대상 파일 만들기

    if ((buf = (char*)malloc(MSIZE)) == NULL) { fclose(in); fclose(out); return 10; } // 버퍼 메모리 할당
    printf("복사 진행중...\n");
    while ((len = fread(buf, sizeof(char), sizeof(buf), in)) != NULL)
        if (fwrite(buf, sizeof(char), len, out) == 0) {
            fclose(in); fclose(out);
            free(buf);
            _unlink(dst); // 에러난 파일 지우고 종료
            return 3;
        }
    fclose(in); fclose(out);
    free(buf); // 메모리 할당 해제

    return 0;
}