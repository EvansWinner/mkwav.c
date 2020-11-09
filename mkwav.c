// mkwav takes an input file of any type and arbitrarily tacks an RIFF
// 16 bit mono 44100 khz .wav file header to it and writes that to a
// new file.

// 	Evans Winner

//       2006.1.27: add use message and some comments.
//                  Compiled on Fedora Core 3 linux machine
//                  at home.
//       2020.11.09: Compile on Ubuntu and change docs. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *in, *out;
  int counter;
  int size = 0;
  int number;
  int *nm = &number;
  int *sz = &size;

  //  Make sure there are two input args.  If not, print use message.
  if (argc != 3) {
    printf("\n          `mkwav' v. 0.1.2\n");
    printf("\n Copies any arbitrary file to a new file with an\n");
    printf(" RIFF, 16 bit, mono, 44,100 khz .wav file header.\n");
    printf("\n           Use: mkwav infile outfile\n");
    printf("\n No error-checking.  Will overwrite output file.\n");
    printf("\n Use at own risk.             evans.winner@gmail.com\n");
    return 0;
  }

  // Make sure input file exists
  if (access(argv[1], R_OK) == -1) {
    printf("Input file does not exist\n");
    exit(1);
  }

  in = fopen(argv[1], "r");
  while (!feof(in)) {
    counter = fgetc(in);
    if (!feof(in))
      size++;
  }

  fclose(in);

  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  fputs("RIFF", out);
  size = (size + 36);
  fwrite(sz, 2, 1, out);
  number = 0;
  fwrite(nm, 2, 1, out);
  fputs("WAVEfmt ", out);
  number = 16;
  fwrite(nm, 2, 1, out);
  number = 0;
  fwrite(nm, 2, 1, out);
  number = 1;
  fwrite(nm, 2, 1, out);
  fwrite(nm, 2, 1, out);
  number = 44100;
  fwrite(nm, 2, 1, out);
  number = 0;
  fwrite(nm, 2, 1, out);
  number = 22664;
  fwrite(nm, 2, 1, out);
  number = 1;
  fwrite(nm, 2, 1, out);
  number = 2;
  fwrite(nm, 2, 1, out);
  number = 16;
  fwrite(nm, 2, 1, out);
  fputs("data", out);
  size = (size - 36);
  fwrite(sz, 2, 1, out);
  number = 0;
  fwrite(nm, 2, 1, out);

  // Here we're writing the old file to the new one after putting in
  // the new header.
  while (!feof(in)) {
    counter = fgetc(in);
    if (!feof(in))
      fputc(counter, out);
  }

  fclose(in);
  fclose(out);
  return 0;
}
