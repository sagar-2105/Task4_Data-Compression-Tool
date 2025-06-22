#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compress using RLE
void compressFile(const char *inputFile, const char *compressedFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(compressedFile, "w");

    if (in == NULL || out == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char ch, prev;
    int count = 1;

    prev = fgetc(in);
    while ((ch = fgetc(in)) != EOF) {
        if (ch == prev) {
            count++;
        } else {
            fprintf(out, "%d%c", count, prev);
            prev = ch;
            count = 1;
        }
    }
    // Write the last sequence
    fprintf(out, "%d%c", count, prev);

    fclose(in);
    fclose(out);
    printf("File compressed successfully.\n");
}

// Function to decompress RLE compressed file
void decompressFile(const char *compressedFile, const char *outputFile) {
    FILE *in = fopen(compressedFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int count;
    char ch;

    while (fscanf(in, "%d%c", &count, &ch) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("File decompressed successfully.\n");
}

int main() {
    int choice;
    char inputFile[100], compressedFile[100], outputFile[100];

    printf("Run-Length Encoding (RLE) Tool\n");
    printf("------------------------------\n");
    printf("1. Compress File\n");
    printf("2. Decompress File\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter input text file name: ");
        scanf("%s", inputFile);
        printf("Enter output compressed file name: ");
        scanf("%s", compressedFile);
        compressFile(inputFile, compressedFile);
    } else if (choice == 2) {
        printf("Enter compressed file name: ");
        scanf("%s", compressedFile);
        printf("Enter output decompressed file name: ");
        scanf("%s", outputFile);
        decompressFile(compressedFile, outputFile);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
