
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
  ssize_t error = write(1, &c, 1);    // Write 1 char to stdout
  
  if(error == -1){                    // If we get -1 we got a error else we return 0
    return EOF;
  }
  
  return 0;

}

/* Writes a null-terminated string to stdout.  If no errors occur, it returns 0, otherwise EOF */
int
write_string(char* s) {
  int lenght = 0;                         // We need to find the length of our string so we know how many bytes to write

  while (s[lenght] != '\0') {             // Run a while loop that keeps incrementing our lenght counter as long as we havent reach the end '\0'
    lenght++;
  }
  ssize_t error = write(1, s, lenght);    // Now we know the length so we can write s out on stdout 
  if(error == -1){                        // If we got -1 then we have a error else we return 0
    return EOF;
  }

  return 0;
}

/* Writes n to stdout (without any formatting).   
 * If no errors occur, it returns 0, otherwise EOF
 */
int
write_int(int n) {
  char buffer[12];                                    // Our buffer that is gonna hold our int number. Its 12 as that is enough to display 32-bit int
  int i = 0;                                          // i is for Index tracking. Later also used for write to see how many bytes to write
    
  if (n == 0) {                                       // Only for the case the number is actually 0
    buffer[i] = '0';
    i++;
  } 
  if (n < 0) {                                        // In our case checking for negative number is not actually needed but its very good to have
    buffer[i] = '-';
    i++;
    n = -n;
  }
  int start = i;                                      // We save the start if the int is a negative number we cant start at - when reversing our buffer
  while (n > 0) {
    buffer[i] = (n % 10) + '0';                       // Fill our buffer with the int starting from right going to the left of the int
    n /= 10;
    i++;
  }
  /*                                                  // Now we need to reverse our buffer as we have stored the number the other way around */
  for (int b = start, t = i - 1; b < t; b++, t--) {
    char temp = buffer[b];                            // b is Bottom and t is Top. 
    buffer[b] = buffer[t];                            // They take the bottom and top char and switch places and then go 1 step closer to the middle
    buffer[t] = temp;                                 // As bottom gets overwrite we need to save that value, which is what temp does
  }
  ssize_t error = write(1, buffer, i);                // We write from the buffer and use i here to indicate how many bytes it should write
  if (error == -1) {                                    // Error handeling
    return EOF;
  }
    return 0;
}

