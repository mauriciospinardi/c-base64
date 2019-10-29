#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

#define MAX_FILE_NAME_SIZE 256
#define HTML_DATA_URL_MASK "<img src=\"data:image/bmp;base64, %s\"/>"

int
main(int argc, char *argv[])
{
    FILE *hFileHandle;
    char *pszBase64;
    char *pszHTML;
    unsigned char *pszFileContent;
    unsigned long uiFileSize;

    /* Step 1: read input from file */

    hFileHandle = fopen("sample.bmp", "rb");
    if (!hFileHandle) {
        printf("\r\nDEBUG::fopen() failed!");
        return EXIT_FAILURE;
    }

    if (fseek(hFileHandle, 0L, SEEK_END)) {
        printf("\r\nDEBUG::fseek() failed!");
        return EXIT_FAILURE;
    }

    uiFileSize = ftell(hFileHandle);

    printf("\r\nDEBUG::uiFileSize [%lu]", uiFileSize);

    pszFileContent = (unsigned char *) malloc(sizeof(unsigned char) * uiFileSize);
    if (!pszFileContent) {
        printf("\r\nDEBUG::malloc() failed!");
        return EXIT_FAILURE;
    }

    if (fseek(hFileHandle, 0L, SEEK_SET)) {
        printf("\r\nDEBUG::fseek() failed!");
        return EXIT_FAILURE;
    }

    if (fread(pszFileContent, sizeof(unsigned char), uiFileSize, hFileHandle) != uiFileSize) {
        printf("\r\nDEBUG::fread() failed!");
        return EXIT_FAILURE;
    }

    if (fclose(hFileHandle)) {
        printf("\r\nDEBUG::fclose() failed!");
        return EXIT_FAILURE;
    }

    /* Step 2: encode and write output to file */

    pszBase64 = b64_encode(pszFileContent, uiFileSize);

    hFileHandle = fopen("sample.html", "w");
    if (!hFileHandle) {
        printf("\r\nDEBUG::fopen() failed!");
        return EXIT_FAILURE;
    }

    uiFileSize = strlen(pszBase64);

    pszHTML = (char *) malloc(sizeof(char) * (36 + uiFileSize + 1));
    pszHTML[36 + uiFileSize] = '\0';
    sprintf(pszHTML, HTML_DATA_URL_MASK, pszBase64);

    if (fwrite(pszHTML, sizeof(unsigned char), uiFileSize + 36, hFileHandle) != uiFileSize + 36) {
        printf("\r\nDEBUG::fwrite() failed!");
        return EXIT_FAILURE;
    }

    if (fclose(hFileHandle)) {
        printf("\r\nDEBUG::fclose() failed!");
        return EXIT_FAILURE;
    }

    free(pszBase64);

    return EXIT_SUCCESS;
}
