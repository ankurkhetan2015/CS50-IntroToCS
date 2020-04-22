#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover [forensic image]\n");
        return 1;
    }
    // Read the input raw file passed in command argument
    char *forensicImage = argv[1];

    // Block size 512B used in FAT file system to write in units of 512B
    int block_size = 512;
    char filename[8];
    int imageNumber = 0;

    // Open input file
    FILE *inptr = fopen(forensicImage, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open the forensic image to read from%s.\n", forensicImage);
        return 1;
    }

    // Output file initially pointing to NULL, helps to tackle first image file
    FILE *outptr = NULL;

    // Declare a buffer of type BYTE and of size given block_size to read from input file in blocks
    BYTE block[block_size];

    while (true)
    {
        fread(block, sizeof(BYTE), block_size, inptr); // read a block from input file

        if (feof(inptr)) // check if we have reached the end of input file
        {
            break;
        }

        // when encountering signature of start of JPEG file, close previous file; will skip for 1st image file as initially outptr is NULL
        if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && ((block[3] & 0xf0) == 0xe0) && (outptr != NULL))
        {
            fclose(outptr);
            imageNumber++; // increment the number of image file saved to save file name accordingly
        }

        // when encountering signature of start of JPEG file, create a new file to start writing in it
        if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && ((block[3] & 0xf0) == 0xe0))
        {
            sprintf(filename, "%03i.jpg", imageNumber); // choses the desired file name
            outptr = fopen(filename, "w"); // creates and open a file in write mode
        }

        if (outptr != NULL) // if outfile is not pointing to NULL, write on the file
        {
            fwrite(block, sizeof(BYTE), block_size, outptr);
        }
    }

    // Close any remaining output file
    fclose(outptr);

    // Close infile
    fclose(inptr);

    return 0;
}