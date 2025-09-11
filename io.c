
#include <errno.h>
#include <unistd.h>

#include "io.h"

/* Reads next char from stdin. If no more characters, it returns EOF */
int read_char() {
    unsigned char c;  
    ssize_t n = read(0, &c, 1);   // read 1 byte stdin

    if (n <= 0) {                 // if read() returns 0 or -1 (EOF)
        return EOF;               // signal end of input
    }

    return c;                     // return the character as an int
}

/* Writes c to stdout.  If no errors occur, it returns 0, otherwise EOF */
int
write_char(char c) {

  ssize_t error = write(1, &c, 1);
  
  if(error == -1){
    return EOF;
  }
  
  return 0;

}

/* Writes a null-terminated string to stdout.  If no errors occur, it returns 0, otherwise EOF */
int
write_string(char* s) {

  int lenght = 0;

  while (s[lenght] != '\0') {
    lenght++;
  }

  ssize_t error = write(1, s, lenght);

  if(error == -1){
    return EOF;
  }

  return 0;
}

/* Writes n to stdout (without any formatting).   
 * If no errors occur, it returns 0, otherwise EOF
 */
int
write_int(int n) {

  if(n >= 10){
    write_int(n/10);
  }

  ssize_t error = write_char('0' + (n % 10));
  
  
  if(error == 0){
    return 0;
  }
  
  return EOF;

