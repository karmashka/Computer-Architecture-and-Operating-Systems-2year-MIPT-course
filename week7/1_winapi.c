//
// Created by karmashka on 09.11.2019.
//

#include <windows.h>
#include <stdio.h>
#include <stdint.h>


struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 1;
    }
    HANDLE fileHandle = CreateFileA(
            argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        return -1;
    }

    struct Item it;
    BOOL success = TRUE;
    int bytes_read;

    while (1) {
        success = ReadFile(fileHandle, &it , 8, (LPDWORD)&bytes_read, NULL);
        if (!success || bytes_read < 8) {
            break;
        }
        printf("%d ", it.value);
        if (it.next_pointer == 0) {
            break;
        }
        LARGE_INTEGER offset;
        offset.LowPart = it.next_pointer;
        offset.HighPart = 0;

        SetFilePointerEx(fileHandle, offset, NULL, FILE_BEGIN);

    }

    CloseHandle(fileHandle);
    return 0;
}
