#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif



#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int compareHashes(const void *a, const void *b)
{
    const char *ha = (const char *)a;
    const char *hb = (const char *)b;
    return strcmp(ha, hb);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    //char **hashes = loadFile(argv[1], &size);
    // CHALLENGE1: Sort the hashes using qsort.
    qsort(hashes, size, sizeof(hashes[0]), compareHashes);
    // TODO
    // Open the password file for reading.
    FILE *passwordFile = fopen(argv[2], "r");
    if (!passwordFile)
    {
        perror("Failed to open password file.");
        free2D(hashes);
        exit(1);
    }
    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    // CHALLENGE1: Use binary search instead of linear search.
    int crackedCount = 0;
    char password[PASS_LEN];
    while (fgets(password, sizeof(password), passwordFile)) {
        password[strcspn(password, "\n")] = '\0';

        char hash[HASH_LEN];
        md5(password, hash);
        char *found = substringSearch2D(hash, hashes, size);
        if (found) {
            crackedCount++;
        }
        
    }

    // TODO
    // When done with the file:
    //   Close the file
    fclose(passwordFile);
    //   Display the number of hashes found.
    printf("Cracked %d hashes.\n", crackedCount);
    //   Free up memory.
    free2D(hashes);
}
