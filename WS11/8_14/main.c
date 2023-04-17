#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ContactNode_struct {
   /* Define ContactNode struct here. */
   char* contactName;
   char* contactPhoneNumber;
   struct ContactNode_struct* nextNodePtr;
} ContactNode;

/* Define the functions here. */
void InitializeContactNode(ContactNode* thisNode, char* name, char* phone) {
   thisNode->contactName = name;
   thisNode->contactPhoneNumber = phone;
   thisNode->nextNodePtr = NULL;
}

void InsertAfter(ContactNode* thisNode, ContactNode* newNode) {
   ContactNode* tmpNext = NULL;
   tmpNext = thisNode->nextNodePtr;
   thisNode->nextNodePtr = newNode;
   newNode->nextNodePtr = tmpNext;
}

ContactNode* GetNext(ContactNode *thisNode) {
   return thisNode->nextNodePtr;
}

void PrintContactNode(ContactNode* thisNode) {
   printf("Name: %s\n", thisNode->contactName);
   printf("Phone number: %s\n", thisNode->contactPhoneNumber);
}

char* GetName(ContactNode *thisNode) {
   return thisNode->contactName;
}

char* GetPhoneNumber(ContactNode* thisNode) {
   return thisNode->contactPhoneNumber;
}

int main(void) {
   /* Type your code here. */
   ContactNode* headObj = NULL;
   ContactNode* currObj = NULL;
   ContactNode* lastObj = NULL;
   int i;

   for (i = 0; i < 3; ++i) {
      char* name = (char*)malloc(50*sizeof(char));
      char* phone = (char*)malloc(50*sizeof(char));
      // Get name
      fgets(name, 50, stdin);
      name[strcspn(name, "\n")] = '\0'; // remove newline from input
      // Get phone number
      fgets(phone, 50, stdin);
      phone[strcspn(phone, "\n")] = '\0'; // remove newline from input

      currObj = (ContactNode*) malloc(sizeof(ContactNode));
      InitializeContactNode(currObj, name, phone);

      if (lastObj != NULL) {
         InsertAfter(lastObj, currObj);
         lastObj = currObj;
      } else {
         headObj = currObj;
         lastObj = currObj;
      }
   }

   i = 1;
   currObj = headObj;
   while (currObj != NULL) {
      printf("Person %d: %s, %s\n", i, GetName(currObj), GetPhoneNumber(currObj));
      currObj = GetNext(currObj);
      ++i;
   }

   printf("\nCONTACT LIST\n");
   currObj = headObj;
   while (currObj != NULL) {
      PrintContactNode(currObj);
      currObj = GetNext(currObj);
      printf("\n");
   }

   return 0;
}
