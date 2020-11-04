#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define block 512

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r"); //Specifies 'stream' to pull data from
    if (inptr == NULL)
    {
        printf("Could not open %s\n", infile);
        return 1;
    }

    int jpegcount = 0;
    bool imagefound = false;
    int blockcount = 0;

    BYTE buffer[block]; //Create a memory buffer
    FILE *outptr = NULL; //Create empty outfile pointer

    while (fread(&buffer, sizeof(block), 1, inptr) == 1)
        //Jump in chunks of 512 bytes; store in buffer in chunks of 512 bytes,
        //for 1 block at a time, from inptr 'stream' -> return value is a number

    {

        if (
            buffer[0] == 0xff  //Check if header bytes are JPEG
            && buffer[1] == 0xd8
            && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0) //Bitwise arithmetic - look at first 4 bits and set remaining 4 bits to zero
        {
            if (imagefound == true) //if JPEG has alreeady been found; only need to modify first image vs all subsequent images
            {
                fclose(outptr); //Start of an image has been found, so close current image being written to
            }

            else //if first JPEG, create a new first file and write in it
            {
                imagefound = true;
            }

            char filename[8]; //8 bytes for each file name

            sprintf(filename, "%03i.jpg", jpegcount); //Print to string; print to name of parameter, format, number to use

            outptr = fopen(filename, "w"); //Opens out file and names it with the output from sprintf above

            jpegcount++; //Increment to change name
        }
        if (imagefound == true)
        {
            fwrite(&buffer, sizeof(block), 1, outptr); //Write to the outptr in a block pulled from buffer
        }
        //Jump to top and start at next block



    }

    if (outptr == NULL)
    {
        fclose(outptr);
    }
    if (inptr == NULL)
    {
        fclose(inptr);
    }
    return 0;



}

