#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdint.h> 
#include <inttypes.h>

typedef int bool;
#define true 1
#define false 0

bool is_utf8(uint8_t c) { 

  if (c == 0)
    return false; 
  
  if (c >> 7 == 0)
    return false; 
  
  if (c >> 6 == 2) /* continuation character */
    return false; 

  if (c >> 5 == 6)
    return true; 

  if (c >> 4 == 14) 
    return true; 

  if (c >> 3 == 30) 
    return true; 
}

int utf8_count(char *c) { 

  int count = 0; 

  while(*c != '\0') {
    
    if (is_utf8(*c)) { 
      count++;
    }
    c++;
  }

  return count;
}

int main(int argc, char **argv) {
  
  FILE* f = stdin;

  int read;
  int count; 
  char *line = NULL; 
  size_t len = 0; 


  while((read = getline(&line, &len, f) != -1)) { 
    
    count = utf8_count(line);

    printf("%d\n", count);

  }

  if (line) { 
    free(line);
  }

}
