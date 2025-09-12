
/* You are not allowed to use <stdio.h> */
#include "io.h"
#include <stdlib.h>       // Used for malloc and free


/**
 * @name  main
 * @brief This function is the entry point to your program
 * @return 0 for success, anything else for failure
 *
 *
 * Then it has a place for you to implementation the command 
 * interpreter as  specified in the handout.
*/

  /*-----------------------------------------------------------------
   *TODO:  You need to implement the command line driver here as
   *       specified in the assignment handout.
   *
   * The following pseudo code describes what you need to do
   *  
   *  Declare the counter and the collection structure variables
   *
   *
   *  In a loop
   *    1) Read a command from standard in using read_char function
   *    2) If the command is not 'a', 'b', 'c': then break the loop
   *    3) Process the command as specified in the handout
   *  End loop
   *
   *  Print your collection of elements as specified in the handout
   *    as a comma delimited series of integers
   *-----------------------------------------------------------------*/


// We decided to use a double linked list so we have to create 2 structs, the hole list(collection) and each note(Saved counter value)

typedef struct Node{
  int value;               // Saves the counter value
  struct Node *next;      // Points to the next Node (Next value in collection)
  struct Node *prev;      // Points to the prev Node (Prev value in collection)
} Node;


typedef struct {
  Node *head;             // Keeps the start of the collection
  Node *tail;             // Keeps the end of the collection 
} List;




// To keep things clean and easier to correct errors we have created functions to use with the linked list.
// With pointers you can quickly loss sight of what is happening and this prevents that for us


void add_counter(List *collection, int value){
  Node *new_node = malloc(sizeof(Node));            // When adding a counter value we have to create a new node, so we "memory allocate"
  new_node->value = value;                          // We set the new nodes values
  new_node->next = NULL;                            
  new_node->prev = collection->tail;                // Make sure our new node points to the one behind it

  if(collection->tail){                             // We check if the collection has any nodes in it
    collection->tail->next = new_node;              // If yes we make sure that the last node in the collections next pointer is pointing to the new node
  } else {
    collection->head = new_node;                    // Else we make sure that the head of the collection is pointing to the new node
  }

  collection->tail = new_node;                      // And in the end we make sure that our new tail of our collection is our new counter value
}


void remove_counter(List *collection){

  if (!collection->tail) return;                     // If there is no tail the collection is empty so we cant remove any and just dont do anything

  Node *deleted_node = collection->tail;             // We get the last node in the list 
  collection->tail = deleted_node->prev;             // We move the tail of the list back one step

  if (collection->tail) {                            // We check if that made the list empty or not
    collection->tail->next = NULL;                   // If no the new tail has to point to nothing
  } else {
    collection->head = NULL;                         // If yes then we make sure the head points to nothing
  }

  free(deleted_node);                                // Now we release the memory from the old note as we dont need it anymore
}



void print_collection(List *collection){

  Node *current = collection->head;                 // We get the start of the collection

  while (current) {                                 // As long as we counter values (nodes) we will keep printing 

    write_int(current->value);                      // We write out the int value of the current node using our own write_int function

    if (current->next) {                            // If there is still more counter values after then we add a "," as asked
      write_char(',');
    }

    current = current->next;                        // Set the current to the next node

    }
    write_char(';');                                // Ask ask we will end with the prober formating and symbols
    write_char('\n');                               // + new line
}



// Here starts the main function

int
main()
{
  List my_collection = {0};                         // Create our collection using our structed
  int counter = 0;                                  // and our counter

  while(1){                                         // Keep the while loop running until terminated
    char current_char = read_char();                // Read next char, using our own read_char function

    if(current_char == 'a'){                        // If char was 'a' we will add the current counter value to the collection with our function 
      add_counter(&my_collection, counter);
      counter++;

      continue;

    } else if(current_char == 'b'){                 // If the char was 'b' we increment the counter
      counter++;
      continue;

    } else if(current_char == 'c'){                 // If the char was 'c' we remove the last counter value in the collection, if any

      remove_counter(&my_collection);
      counter++;

      continue;

    } else if(current_char == 'q'){                 // If q we terminate
      
      // Typing anything other then 'a', 'b' or 'c' would terminat the program but since q is represtentet as our quit we have made it clear
      // That there is a seperation between them. If wanted it could be made so only q terminats and any other char wouldnt do anything

      break;

    } else {                                        // Typing anything else also terminate

      // Countinue would probaly be a better method making sure that only 4 chars have a effect but the assignemt asked for any other to also terminate

      break;
      // countinue;

    }

  }

  // Now we write the resualt after the program was terminated
  write_string("count = ");
  write_int(counter);
  write_char('\n');

  write_string("collection = ");
  print_collection(&my_collection);

  return 0;
}
