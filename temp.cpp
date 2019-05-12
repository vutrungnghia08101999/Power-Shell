#include <windows.h>
#include <stdio.h>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
     HANDLE hDisk;
     BYTE Buf[512];
     DWORD byteread, i;
     hDisk = CreateFile("\\\\.\\PhysicalDrive1", GENERIC_READ,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL, OPEN_EXISTING, 0, NULL);
     if (hDisk == INVALID_HANDLE_VALUE)
          printf("Loi thiet bi");
     else
     {
          ReadFile(hDisk, Buf, 512, &byteread, NULL);
          for (i = 0; i < 512; i++){
               if(i%16 == 0)
                    printf("\n");
               printf("%4X", Buf[i]);
          }
               
          CloseHandle(hDisk);
     }
     cin.get();
     return 0;
}
