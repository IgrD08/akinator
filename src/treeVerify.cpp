#include "../include/fileUtility.h"

bool fileOpening(FILE **fp, const char *fileName, const char *fileFlag)
{
    if ((*fp = fopen(fileName, fileFlag)) == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open file %s\n", fileName);

        return 1;
    }

    return 0;
}

bool closeFile(FILE **fp)
{
    if (fclose(*fp) == EOF)
    {
        fprintf(stderr, "ERROR: Failed to close file\n");

        return 1;
    }

    return 0;
}
