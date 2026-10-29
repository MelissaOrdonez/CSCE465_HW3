#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define BUF_SIZE 128
#define MAX_COPY 512

__attribute__((noinline))
void win(void){
  /* ret2win target: writes markers/ret2win.text, then attempts to read protected decoy */
  const char *marker_path = "markers/ret2win.txt";
  const char *decoy_path = "/opt/agentsec/decoy.txt";
  
  if(mkdir("markers", 0755) != 0 && errno != EEXIST){
    perror("mkdir markers");
    return;
  }
  
  FILE *marker = fopen(marker_path, "w");
  if(marker == NULL){
    perror("fopen marker");
    return;
  }
  
  if(fprintf(marker, "ret2win reached successfully\n") < 0){
    perror("write marker");
  }
  
  if(fclose(marker) != 0){
    perror("close marker");
  }
  
  printf("Created %s\n", marker_path);
  
  /* Attempt to read protected decoy */
  FILE *decoy = fopen(decoy_path, "r");
  if(decoy == NULL){
    perror("Could not open protected decoy");
    return;
  }
  
  char buffer[128];
  size_t bytes_read;
  
  printf("Decoy contents:\n");
  
  while((bytes_read = fread(buffer, 1, sizeof(buffer), decoy)) > 0){
    if(fwrite(buffer, 1, bytes_read, stdout) != bytes_read){
      perror("Writing decoy to stdout");
      break;
    }
  }
  
  if(ferror(decoy)) {
    perror("Reading decoy");
  }
  
  fclose(decoy);
} 
  
static void vulnerable_copy(const unsigned char *input, size_t n){
  char buf[BUF_SIZE];
  /* Copy n bytes from input into buf without checking n against BUF_SIZE -- missing check is the vulnerability */

  for(volatile size_t i = 0; i < n; i++){
    buf[i] = input[i];
  }
  
  printf("Copied %zu bytes\n", n);
}

static void parse_log(const char *path){
  /* Read the whole file into a heap buffer, fclose() it, then call vulnerable_copy(input, n) so the overflow reaches only this frame's saved return address a clean ret2win*/
  
  FILE *fp = fopen(path, "rb");
  if(fp == NULL) {
    perror("fopen");
    return;
  }
  
  if(fseek(fp, 0, SEEK_END) != 0){
    perror("fseek");
    fclose(fp);
    return;
  }
  
  long file_size = ftell(fp);
  if(file_size < 0 || file_size > MAX_COPY){
    fprintf(stderr, "Invalid file size\n");
    fclose(fp);
    return;
  }
  
  rewind(fp);
  
  size_t n = (size_t)file_size;
  unsigned char * input = malloc(n > 0 ? n : 1);
  if(input == NULL){
    perror("malloc");
    fclose(fp);
    return;
  }
  
  if(fread(input, 1, n, fp) != n){
    fprintf(stderr, "Could not read complete file\n");
    free(input);
    fclose(fp);
    return;
  }
  
  size_t preview_len = n < 64 ? n : 64;
  printf("Log preview (%zu bytes):\n", preview_len);
  fwrite(input, 1, preview_len, stdout);
  putchar('\n');
  
  fclose(fp);
  vulnerable_copy(input, n);
  free(input);
}

int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
    return 1;
  }
  
  parse_log(argv[1]);
  return 0;
} 
