#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Check for single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover file.raw\n");
        return 1;
    }

    // Open raw file and check it exists
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read 512 bytes into buffer, repeat until end of card
    uint8_t buffer[512];
    bool foundJPEG = false;
    int fileCount = 0;
    char output[8];
    FILE *img;

    while (fread(&buffer, sizeof(uint8_t), 512, raw))
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (!foundJPEG)
            {
                sprintf(output, "%03i.jpg", fileCount);
                img = fopen(output, "w");
                if (img == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }

                fwrite(&buffer, sizeof(uint8_t), 512, img);
                foundJPEG = true;
                fileCount += 1;
            }

            else
            {
                // Close previous file and write to new file
                fclose(img);
                sprintf(output, "%03i.jpg", fileCount);
                img = fopen(output, "w");
                if (img == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }
                fwrite(&buffer, sizeof(uint8_t), 512, img);
                fileCount += 1;
            }

        }

        // Not new JPEG
        else
        {
            // If already found JPEG
            if (foundJPEG)
            {
                // Write to current file
                fwrite(&buffer, sizeof(uint8_t), 512, img);
            }
        }


    }

    fclose(raw);
}