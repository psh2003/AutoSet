#define _CRT_SECURE_NO_WARNINGS
#define MAX 80
#define MSIZE 16777216  // 16�ް��� �޸� ���� ����
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

    printf("������Ʈ �̸��� �Է��ϼ���\n");
    scanf("%s", name);

    strcat(tempPath, name);
    printf(tempPath);
    int nResult = _mkdir(tempPath);

    if (nResult == 0)
    {
        printf("���� ���� ����\n");
    }
    else if (nResult == -1)
    {
        perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ��\n");
        printf("errorno : %d", errno);
        system("pause > nul");
        return 0;
    }

    strcat(tempPath, "\\workspace");
    printf(tempPath);
    int nResult1 = _mkdir(tempPath);

    if (nResult1 == 0)
    {
        printf("���� ���� ����\n");
    }
    else if (nResult1 == -1)
    {
        perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ��\n");
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
        printf("������ ����Ǿ����ϴ�.\n");
    else {
        switch (e) {
        case  1: fputs("���� ������ �� �� �����ϴ�.\n", stderr); break;
        case  2: fputs("��� ���Ͽ� �� �� �����ϴ�. �б� ����?\n", stderr); break;
        case  3: fputs("���� ����, ��ũ �뷮 �ʰ�?\n", stderr); break;
        case  4: fputs("���� ��ο� ��� ��ΰ� �����մϴ�\n", stderr); break;
        case 10: fputs("�޸𸮰� �����մϴ�\n", stderr); break;
        default: fputs("�� �� ���� ����\n", stderr); break;
        }
    }

    int Result1 = _chdir(strChangeDir);
    strcpy(target,name);
    strcat(target, "\\apache-tomcat-8.5.73.zip");
    int f = fileCopy("D:\\Code\\apache-tomcat-8.5.73.zip", target);

    if (f == 0)
        printf("������ ����Ǿ����ϴ�.\n");
    else {
        switch (f) {
        case  1: fputs("���� ������ �� �� �����ϴ�.\n", stderr); break;
        case  2: fputs("��� ���Ͽ� �� �� �����ϴ�. �б� ����?\n", stderr); break;
        case  3: fputs("���� ����, ��ũ �뷮 �ʰ�?\n", stderr); break;
        case  4: fputs("���� ��ο� ��� ��ΰ� �����մϴ�\n", stderr); break;
        case 10: fputs("�޸𸮰� �����մϴ�\n", stderr); break;
        default: fputs("�� �� ���� ����\n", stderr); break;
        }
    }

    system("pause > nul");
    return 0;
}


// ���� ���� �Լ��� ��ü
int fileCopy(const char* src, const char* dst) {
    FILE* in, * out;
    char* buf;
    size_t len;
    
    if (!_strcmpi(src, dst)) return 4; // ������ �纻 ������ �����ϸ� ����

    if ((in = fopen(src, "rb")) == NULL) return 1; // ���� ���� ����
    if ((out = fopen(dst, "wb")) == NULL) { fclose(in); return 2; } // ��� ���� �����

    if ((buf = (char*)malloc(MSIZE)) == NULL) { fclose(in); fclose(out); return 10; } // ���� �޸� �Ҵ�
    printf("���� ������...\n");
    while ((len = fread(buf, sizeof(char), sizeof(buf), in)) != NULL)
        if (fwrite(buf, sizeof(char), len, out) == 0) {
            fclose(in); fclose(out);
            free(buf);
            _unlink(dst); // ������ ���� ����� ����
            return 3;
        }
    fclose(in); fclose(out);
    free(buf); // �޸� �Ҵ� ����

    return 0;
}