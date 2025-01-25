#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_LINE_LENGTH 1024
#define MAX_ARGUMENTS 10

// Function to call the appropriate function based on the function name
// Code snippets are not provided for print_message and add_like
void callFunction(char *funcName, char **args, int argCount) {
    
    if (strcmp(funcName, "testingParser") == 0) {
        if (argCount >= 2) {
            testingParser(atoi(args[0]), args[1]);
        } else {
            printf("Invalid arguments for function: %s\n", funcName);
        }
    } 
    
    // UNCOMMENT ME AFTER YOU HAVE WRITTEN MY FUNCTION

     else if (strcmp(funcName, "create_user") == 0) {
         if (argCount >= 2) {
             create_user(args[0], args[1]);
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "print_users") == 0) {
         if (argCount >= 0) {
             print_users();
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "search_user_by_name") == 0) {
         if (argCount >= 1) {
             search_user_by_name(args[0]);
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "search_user_by_email") == 0) {
         if (argCount >= 1) {
             search_user_by_email(args[0]);
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "delete_user") == 0) {
         if (argCount >= 1) {
             delete_user(search_user_by_name(args[0]));
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "change_user_name") == 0) {
         if (argCount >= 2) {
             change_user_name(search_user_by_name(args[0]), args[1]);
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "change_user_email") == 0) {
         if (argCount >= 2) {
             change_user_email(search_user_by_name(args[0]), args[1]);
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "add_friend") == 0) {
         if (argCount >= 2) {
             add_friend(search_user_by_name(args[0]), search_user_by_name(args[1]));
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

    // else if (strcmp(funcName, "delete_friend") == 0) {
    //     if (argCount >= 2) {
    //         delete_friend(search_user_by_name(args[0]), search_user_by_name(args[1]));
    //     } else {
    //         printf("Invalid arguments for %s\n", funcName);
    //     }
    // } 

     else if (strcmp(funcName, "print_friends") == 0) {
         if (argCount >= 1) {
             print_friends(search_user_by_name(args[0]));
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "print_mutual_friends") == 0) {
         if (argCount >= 2) {
             print_mutual_friends(mutual_friends(search_user_by_name(args[0]), search_user_by_name(args[1])));
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "create_message") == 0) {
         if (argCount >= 3) {
             create_message(search_user_by_name(args[0]), search_user_by_name(args[1]), args[2]);
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "display_chat") == 0) {
         if (argCount >= 2) {
             display_chat(search_user_by_name(args[0]), search_user_by_name(args[1]));
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

     else if (strcmp(funcName, "new_post") == 0) {
         if (argCount >= 2) {
             new_post(search_user_by_name(args[0]), args[1]);
         } else {
             printf("Invalid arguments for %s\n", funcName);
         }
     }

    // else if (strcmp(funcName, "display_feed") == 0) {
    //     if (argCount >= 1) {
    //         display_feed(search_user_by_name(args[0]));
    //     } else {
    //         printf("Invalid arguments for %s\n", funcName);
    //     }
    // } 

    else {
        printf("Unknown function: %s\n", funcName);
    }
}

int main() {
    FILE *file = fopen("test_cases.csv", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        char *funcName = NULL;
        char *args[MAX_ARGUMENTS];
        int argCount = 0;

        token = strtok(line, ",\n");
        while (token != NULL) {
            if (funcName == NULL) {
                funcName = token;
            } else {
                args[argCount++] = token;
            }
            token = strtok(NULL, ",\n");
        }

        if (funcName != NULL) {
            callFunction(funcName, args, argCount);
        }
    }

    fclose(file);
    return 0;
}
