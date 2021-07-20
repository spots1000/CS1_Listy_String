/*
  Anthony Dalia
  an694448
  Program #3 - ListyStrings
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"

#define MAX_LEN 1024

// Requried Function Signatures
int processInputFile(char *filename);
ListyString *createListyString(char *str); // Done
ListyString *destroyListyString(ListyString *listy); // Done
ListyString *cloneListyString(ListyString *listy); // Done
void replaceChar(ListyString *listy, char key, char *str);
void reverseListyString(ListyString *listy); // Done
ListyString *listyCat(ListyString *listy, char *str); // Done
int listyCmp(ListyString *listy1, ListyString *listy2); // Done
int listyLength(ListyString *listy); // Done
void printListyString(ListyString *listy); // Done
double difficultyRating(void); // Done
double hoursSpent(void); // Done

int main(int argc, char *argv[]) // Completed - Formatting and Rumtime Check Required
{
  char *fileName;

  // Scan in the File
  fileName = argv[1];

  // Call the Process Input
  processInputFile(fileName);

  return 0;
}

int processInputFile(char *filename)
{
  FILE *ifp = NULL;
  char *inptStr, key;
  int i;
  ListyString *listy, *newListy;

  // Create the string to store input
  inptStr = malloc(sizeof(char) * MAX_LEN);

  // Attempt to open the file
  ifp = fopen(filename, "r");{}

  // Check if the file is open
  if (ifp == NULL)
  {
    free(inptStr);
    return 1;
  }

  // Scan in the first line of the file
  fscanf(ifp, "%s", inptStr);

  // Create a listyString from that string
  listy = createListyString(inptStr);

  // Scan in the remaining commands
  while (fscanf(ifp, "%c", &key) != EOF)
  {
    // Basic commands first
    if (key == '!')
    {
      printListyString(listy);
    }
    else if (key == '?')
    {
      printf("%d\n", listyLength(listy));
    }
    else if (key == '~')
    {
      reverseListyString(listy);

    }
    else if (key == '-')
    {
      // Scan in the key we require
      fscanf(ifp, " %c", &key);

      // Delete instances from string
      replaceChar(listy, key, "");
    }
    else if (key == '+')
    {
      // Scan in the string we require
      fscanf(ifp, " %s", inptStr);

      // Concatenate to the end of the string
      listyCat(listy, inptStr);
    }
    else if (key == '@')
    {
      // Scan in the key and string
      fscanf(ifp, " %c", &key);
      fscanf(ifp, "%s", inptStr);

      replaceChar(listy, key, inptStr);
    }
  }

  free(inptStr);
  fclose(ifp);
  return 0;
}

ListyString *createListyString(char *str)
{
  ListyString *listy;
  ListyNode *newNode, *curNode;
  int slen, i;

  // Create the base
  listy = malloc(sizeof(ListyString));

  //We have a null string so do things a bit differently
  if (str == NULL || str == "")
  {
    listy->head = NULL;
    listy->length = 0;
    return listy;
  }

  // Get the length of the list
  slen = strlen(str);

  // Create the head
  listy->length = slen;

  // Loop through creating a node for each char
  for (i = 0; i < slen; i++)
  {
    newNode = malloc(sizeof(ListyNode));
    newNode->data = str[i];

    // Add it to the correct position
    if (i == 0)
      listy->head = newNode;
    else
      curNode->next = newNode;

    curNode = newNode;
  }

  // Return the full listystring
  return listy;
}

ListyString *destroyListyString(ListyString *listy)
{

  ListyNode *curNode, *nextNode;

  //  Check for a null listy
  if ( listy == NULL || listy->head == NULL)
    return NULL;

  // Set the first node to the head
  curNode = listy->head;

  // Loop through the listy freeing all nodes
  while (curNode != NULL)
  {
    nextNode = curNode->next;
    free(curNode);
    curNode = nextNode;
  }

  // Free the base string
  free(listy);
  return NULL;
}

void printListyString(ListyString *listy)
{
  int i, len;

  // Check for NULL
  if (listy == NULL || listy->head == NULL)
  {
    printf("(empty string)\n");
    return;
  }

  // Declare the head of the list and set up our loop
  ListyNode *curNode = listy->head;
  len = listy->length;

  // Loop through printing the list
  for(i = 0; i < len; i++)
  {
    printf("%c", curNode->data);
    curNode = curNode->next;
  }

  printf("\n");
  return;
}

ListyString *cloneListyString(ListyString *listy)
{
  ListyString *newListy;
  ListyNode *curNode_new, *newNode_new, *curNode_old;
  int i=0, len = listy->length;

  // Check for a NULL input
  if ( listy == NULL )
    return NULL;

  // Create a new listystring
  newListy = malloc(sizeof(ListyString));
  newListy->length = listy->length;
  newListy->head = NULL;

  // Set the start points for our loop
  curNode_new = newListy->head;
  curNode_old = listy->head;

  // Loop through generating each node
  for (i = 0; i < len; i++)
  {
    newNode_new = malloc(sizeof(ListyNode));
    newNode_new->data = curNode_old->data;

    if (i==0)
      newListy->head = newNode_new;
    else
      curNode_new->next = newNode_new;

    curNode_new = newNode_new;
    curNode_old = curNode_old->next;
  }

  return newListy;
}

int listyLength(ListyString *listy)
{
  if (listy == NULL)
    return -1;
  else if (listy->head == NULL)
    return 0;
  else
    return listy->length;
}

void reverseListyString(ListyString *listy)
{
  int i, len;
  ListyNode *curNode,*newNode;
  char *dataArray;

  // Ensure listy is not null
  if(listy == NULL || listy->head == NULL)
    return;

  // Set up the array
  dataArray = malloc(sizeof(char) * listy->length);

  // Len
  len = listy->length;

  // Loop through adding the vals to the array
  curNode = listy->head;
  for(i = 0; i < len; i++)
  {
    dataArray[i] = curNode->data;
    curNode = curNode->next;
  }

  // Add the nodes back in reverse order.
  curNode = listy->head;
  for(i=len-1; i >= 0; i--)
  {
    curNode->data = dataArray[i];
    curNode = curNode->next;
  }

  free(dataArray);
  return;
}

ListyNode *locPrev(ListyString *listy, ListyNode *target)
{
  ListyNode *prevNode, *curNode;

  //Check for NULL
  if (listy == NULL || target == NULL)
  {
    return NULL;
  }

  //Ensure the target is not the head
  if ( target == listy->head )
  {
    return NULL;
  }

  //Set up our loop
  prevNode = listy->head;
  curNode = listy->head->next;

  //Run the loop
  while (curNode != NULL)
  {
    if (curNode == target)
    {
      return prevNode;
    }
    else
    {
      curNode = curNode->next;
      prevNode = prevNode->next;
    }
  }
}

void replaceChar(ListyString *listy, char key, char *str)
{
  int i=0;
  ListyNode *curNode, *newNode, *prevNode, *delNode, *afterNode;

  //See if we will replace or remove
  curNode = listy->head;
  if (str == "" || str == NULL)
  {
    //Remove char
    while ( curNode != NULL )
    {
      if( curNode->data == key )
      {
        //Set up for relinking
        prevNode = locPrev(listy, curNode);
        afterNode = curNode->next;
        delNode = curNode;

        //See if curNode was positioned at the head
        if (prevNode == NULL)
        {
          //Relink accordingly
          listy->head = afterNode;
        }
        else
        {
          //Do a normal relink
          prevNode->next = afterNode;
        }

        //Move up the system after we've completed the relink
        curNode = curNode->next;

        //Delete the old node
        free(delNode);
        delNode = NULL;

        //Update our length parameter
        listy->length--;
      }
      else
      {
        curNode = curNode->next;
      }
    }
  }
  else
  {
    //Replace char
    while ( curNode != NULL )
    {
      if( curNode->data == key )
      {

        // Set up for relinking
        prevNode = locPrev(listy, curNode);
        afterNode = curNode->next;
        i = 0;

        // The string contains more then 0 values
        if ( str[i] != '\0' )
        {
          //Set the first value of the str to replace our current node
          curNode->data = str[i];
          i++;

          //Loop through the remaining parts of the str until we run out of charecters
          while (str[i] != '\0')
          {
            //Create a new node
            newNode = malloc(sizeof(ListyNode));
            listy->length++;

            //Populate our new node
            newNode->data = str[i];

            //Relink our new node
            curNode->next = newNode;
            newNode->next = afterNode;

            //Move up the chain
            curNode = curNode->next;
            i++;
          }

        }
      }
      curNode = curNode->next;
    }
  }
  fflush(stdout);
}

ListyString *listyCat(ListyString *listy, char *str) // Completed - Formatting and Rumtime Check Required
{
  int listyNull=0, strNull=0, nullStart=0, i=0;
  ListyNode *curNode, *listTail;

  // Check if STR and Listy are null
  if ( listy == NULL )
    listyNull = 1;
  if ( str == NULL )
    strNull = 1;

  // Make a desisision
  if ( listyNull == 1 && strNull == 1 )
  {
    return NULL;
  }
  else if ( listyNull == 1 && strNull == 0 )
  {
    return createListyString(str);
  }
  else if ( listyNull == 0 && strNull == 1 )
  {
    return listy;
  }

  // Locate the tail of the listy
  if( listy->head == NULL )
  {
    listTail = NULL;
    nullStart = 1;
  }
  else
  {
    curNode = listy->head;
    while ( curNode->next != NULL )
    {
      curNode = curNode->next;
    }
    listTail = curNode;
  }

  // Loop through STR adding it to the listy
  while ( str[i] != '\0' )
  {

    curNode = malloc(sizeof(ListyNode));
    curNode->data = str[i];
    curNode->next = NULL;

    if ( nullStart == 1 )
    {
      listy->head = curNode;
      listTail = curNode;
      nullStart = 0;
    }
    else
    {
      listTail->next = curNode;
      listTail = listTail->next;
    }

    listy->length++;
    i++;
  }

  return listy;
}

int listyCmp(ListyString *listy1, ListyString *listy2) // Completed - Formatting and Rumtime Check Required
{
  int l1Null=0, l2Null=0;
  int l1Empty=0, l2Empty=0;
  int l1Len, l2Len, i;
  ListyNode *l1_curNode, *l2_curNode;

  // Check both for NULL listy
  if ( listy1 == NULL )
    l1Null = 1;

  if ( listy2 == NULL )
    l2Null = 1;

  // See if we can make a decision from that alone:
  if ( l1Null == 1 && l2Null == 1 )
  {
    return 0; //  They are both NULL so equiviant
  }
  else if ( l1Null == 1 || l2Null == 1)
  {
    return -1; // Only one is NULL so non-equivilant
  }

  // Check if both strings are empty
  if ( listy1->head == NULL )
    l1Empty = 1;

  if ( listy2->head == NULL )
    l2Empty = 1;

  // See if we can make another descision:
  if ( l1Empty == 1 && l2Empty == 1 )
  {
    return 0; //  Both lists are empty strings so eqivilant
  }
  else if ( l1Empty == 1 || l2Empty == 1 )
  {
    return -1; //  Only one listy is an empty string so non-equivilant
  }

  // Get the length of both strings
  l1Len = listy1->length;
  l2Len = listy2->length;

  // See if we can make another descision:
  if ( l1Len != l2Len )
  {
    return -1; //  Both strings are different lengths
  }

  // Loop through both lists comparing the charecters:
  l1_curNode = listy1->head;
  l2_curNode = listy2->head;
  for (i = 0; i < l1Len; i++)
  {
    char l1Data, l2Data;

    // Pull in the data for both nodes
    l1Data = l1_curNode->data;
    l2Data = l2_curNode->data;

    // Compare the data
    if ( l1Data != l2Data )
      return -1; //  The charecters are not equal at this node position

    // Advance the nodes
    l1_curNode = l1_curNode->next;
    l2_curNode = l2_curNode->next;
  }

  // We have checked everything else so the listys must be equal
  return 0;
}

double difficultyRating(void) // Completed - Formatting and Rumtime Check Required
{
  return 2.0;
}

double hoursSpent(void) // Completed - Formatting and Rumtime Check Required
{
  return 15.0;
}
