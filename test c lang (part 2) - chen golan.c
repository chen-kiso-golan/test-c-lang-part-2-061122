#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <psapi.h>
#include <time.h>
#pragma warning(disable:4996)

void diviedStr(char str[100]) {
    char str1[50];
    char str2[50];
    char* strPtr = str;

    strncpy(str1, strPtr, strlen(str) / 2);
    str1[(strlen(str) / 2)] = NULL;
    strPtr = strPtr + (strlen(str) / 2);
    strcpy(str2, strPtr);

    printf("str1 is: %s\n", str1);
    printf("str2 is: %s\n", str2);
}

void diviedStrLeft(char str[100]) {

    if (strlen(str) == 1) {
        printf("end of string devision.\n");
        return;
    }

    char str1[50];
    char* strPtr = str;

    strncpy(str1, strPtr, strlen(str) / 2);
    str1[(strlen(str) / 2)] = NULL;

    printf("str1 (left) is: %s\n", str1);
   
    diviedStrLeft(str1);
    
}

int Add222(int num) {
    printf("%d\n", num);
 
    return (num < 100) ? (Add222(num + 1)) : printf("done");
}

struct Loto
{
    int LotoNumber;
    char LotoDate[100];
    //int WinningNumbers[6];
    //int StrongNumber;
    //int WinnerLoto;
    //int WinnerDubleLoto;
    struct Loto* Next;
    struct Loto* Prev;
};

struct Loto* Tail = NULL;
struct Loto* Head = NULL;
struct Loto* previtem = NULL;

void AddItem(int lotonumber,char lotodate[100])
{

    struct Loto* curr = NULL;


    curr = (struct Loto*)malloc(sizeof(struct Loto));
    curr->LotoNumber = lotonumber;
    strcpy(curr->LotoDate, lotodate);

    if (Head == NULL) {
        Head = curr;
        Tail = curr;
        curr->Prev = NULL;
        curr->Next = NULL;
        previtem = curr;
    }
    else
    {
        curr->Next = NULL;
        curr->Prev = previtem;
        previtem->Next = curr;
        Tail = curr;
        previtem = curr;
    }
}

void LoadFile()
{
    char str [1000];
    char lotonumber[100];
    char lotodate[100];
    char winningnumbers[10];
    char strongnumber[10];
    char winnerloto[10];
    char winnerdubleloto[10];
    
    char* token = strtok(str, ",");

    FILE* f = fopen("lotto.txt", "r");
    if (f) {

        fgets(str, 1000, f);

        while (fgets(str, 1000, f) != NULL)
        {

            token = strtok(str, ",");
            strcpy(lotonumber, token);
            token = strtok(NULL, ",");
            strcpy(lotodate, token);
            for (int i = 0; i < 6; i++) {
                token = strtok(NULL, ",");
                strcpy(winningnumbers, token);
            }
            token = strtok(NULL, ",");
            strcpy(strongnumber, token);
            token = strtok(NULL, ",");
            strcpy(winnerloto, token);
            token = strtok(NULL, ",");
            strcpy(winnerdubleloto, token);
            AddItem(atoi(lotonumber), lotodate);
        }
    }
}

void GetLotoDateByNumber(int lotonumber)
{
    struct Loto* currentItem1 = Head;
    struct Loto* Search = Head;

    while (Search->Next != NULL)
    {
        Search = currentItem1;
        currentItem1 = currentItem1->Next;

        if (Search->LotoNumber == lotonumber) {
            printf("the loto you chose is:\n loto number: %d\n loto date: %s\n", Search->LotoNumber, Search->LotoDate);
        }
    }

}

void FreeList()
{
    struct Loto* currentItem1 = Head;
    struct Loto* FreeItem = Head;

    while (currentItem1 != NULL)
    {
        FreeItem = currentItem1;
        currentItem1 = currentItem1->Next;
        free(FreeItem);
    }
}


int main()
{

    char strOrg[100];

  //Q1:
    printf("enter a string of letters:\n");
    gets(strOrg);
    diviedStr(strOrg);
    printf("\n\n\n");
   
  //Q2:
    printf("enter a new string of letters:\n");
    gets(strOrg);
    diviedStrLeft(strOrg);
    printf("\n\n\n");
    
  //Q3:
    Add222(1);
    printf("\n\n\n");

  //Q4:
    char UserRispon = 0;
    int a;

    while (UserRispon != 'Q' || 'q') {
        printf("*MENU*\n~ Type the Option For Execution ~\nN.Which lottery number are you interested in?\nQ.Quit\ntype here:");
        UserRispon = getch();
        printf("\n\n\n");
        Sleep(1000);
        switch (UserRispon)
        {
        case 'N':
            Sleep(1000);
            LoadFile();
            printf("\n\nthe file was loded and the list was made.\n\n");
            Sleep(1000);
            printf("\n\nchoose a lotto number (BETWEEN 1841-3523):\n\n");
            scanf("%d", &a);
            GetLotoDateByNumber(a);
            printf("\n\n");
            Sleep(1000);
            break;
        case 'Q':
            FreeList();
            printf("\n\nGood Bye!\n\n");
            Sleep(1000);
            return;
        default:
            printf("invalid key");
            printf("\n\n");
            break;
        }
    }


    return 0;
}
