#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// Utility function to test parser
void testingParser(int arg1, char *arg2) {
    printf("The parser was called with arguments: %d and %s\n", arg1, arg2);
}

//Variables
static struct Node* root = NULL; //Root of the AVL tree for users

static int user_ID = 0; //To assign unique user IDs
static int message_ID = 0;
static int post_ID = 0;

//Helper Functions
int max(int a, int b);
int height(struct Node *N);
struct Node* newNode(User * user);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* node, User* user);
struct Node* FindMin(struct Node *node);
struct Node* delete(struct Node* node, User* user);
void print_users_recursive(struct Node* node);

//User Profiles Management
User* create_user(const char* name, const char* email); // int user_id is auto-generated to be unique
void add_friend(User* user1, User* user2); // users user1 and user2 are now friends
void delete_friend(User* user1, User* user2); // users user1 and user2 are no longer friends
void delete_user(User* user); // user is deleted
void print_users(); // prints all usernames in ascending order
void change_user_name(User* user, char* new_name);
void change_user_email(User* user, char* new_email);
void print_friends(User* user); // prints user's friends in ascending order

//Search Functionality
User* search_user_by_name(const char* name);
User* search_user_by_email(const char* email);

//Mutual Friends
User** mutual_friends(User* user1, User* user2); // returns an array of pointers to the mutual friends
void print_mutual_friends(User** friends); // prints mutual friends' usernames in ascending order

//Messaging System
Message* create_message(User* sender, User* receiver, const char* content); // int message_id is auto-generated to be unique
void print_message(Message* message);
void display_chat(User* user1, User* user2); // print messages in FIFO

//Posts
Post* new_post(User* user, const char* content); // post id is auto-generated to be unique

//Like System
void add_like(Post* post, User* user); // user is the individual who liked the post

//Feed Generation
void display_feed(User* user1);

// WRITE FUNCTIONS BELOW

//Helper functions
//Return maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

//Return the height of the AVL tree (recursive)
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return 1+max(height(N->left), height(N->right));
}

//Allocates a new node with the given user and NULL left and right pointers
struct Node* newNode(User * user)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->user = user;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;

    return node;
}

//Right rotates subtree rooted with y
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
// Perform rotation
    x->right = y;
    y->left = T2;
// Update heights
    y->height = height(y);
    x->height = height(x);
// Return new root
    return x;
}

//Left rotates subtree rooted with x
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
// Perform rotation
    y->left = x;
    x->right = T2;
// Update heights
    x->height = height(x);
    y->height = height(y);
// Return new root
    return y;
}

//Get balance factor of node N (recursive)
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

//Insert a user in the subtree rooted with node and returns the new root of the subtree (recursive)
struct Node* insert(struct Node* node, User* user)
{
    //Insert node into BST as usual
    if (node == NULL)
        return(newNode(user));

    if (strcmp(user->name, node->user->name) < 0) //user->name is lexicographically less than node->user->name
        node->left = insert(node->left, user);
    else if (strcmp(user->name, node->user->name) > 0) //user->name is lexicographically greater than node->user->name
        node->right = insert(node->right, user);
    else //user->name == node->user->name, not allowed
        return node;

    //Update height of ancestor node
    node->height = height(node);

    //Get balance factor of node to check if it became unbalanced
    int balance = getBalance(node);
    //If this node becomes unbalanced, then there are 4 cases
    //Left-Left Case
    if ((balance > 1) && (strcmp(user->name, node->left->user->name) < 0))
        return rightRotate(node);
    //Right-Right Case
    if ((balance < -1) && (strcmp(user->name, node->right->user->name) > 0))
        return leftRotate(node);
    //Left-Right Case
    if ((balance > 1) && (strcmp(user->name, node->left->user->name) > 0))
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //Right-Left Case
    if ((balance < -1) && (strcmp(user->name, node->right->user->name) < 0))
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node; //return the (unchanged) node pointer
}

struct Node* FindMin(struct Node *node)
{
    if(node==NULL) {
        return NULL;
    } else if(node->left != NULL) {
        return FindMin(node->left);
    }
    else
        return node;
}

struct Node* delete(struct Node* node, User* user){
    struct Node *temp = NULL;

    if(node==NULL) {
        return NULL;
    } else if (strcmp(user->name, node->user->name) < 0) {
        node->left = delete(node->left, user);
    } else if (strcmp(user->name, node->user->name) > 0) {
        node->right = delete(node->right, user);
    } else {
        if (node->right && node->left) {
            temp = FindMin(node->right);
            node->user = temp->user;
            node->right = delete(node->right, temp->user);
        } else {
            //Only 1 or 0 children

            if (node->left == NULL) {
                temp = node->right;
            }
            else if (node->right == NULL) {
                temp = node->left;
            }

            free(node); /* temp is no longer required */
            return temp;
        }
    }

    //Update height of ancestor node
    node->height = height(node);

    //Get balance factor of node to check if it became unbalanced
    int balance = getBalance(node);

    //If this node becomes unbalanced, then there are 4 cases
    //Left-Left Case
    if ((balance > 1) && (strcmp(user->name, node->left->user->name) < 0))
        return rightRotate(node);
    //Right-Right Case
    if ((balance < -1) && (strcmp(user->name, node->right->user->name) > 0))
        return leftRotate(node);
    //Left-Right Case
    if ((balance > 1) && (strcmp(user->name, node->left->user->name) > 0))
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //Right-Left Case
    if ((balance < -1) && (strcmp(user->name, node->right->user->name) < 0))
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//User Profiles Management
User* create_user(const char* name, const char* email) {
    //Create a new user
    User* newUser = (User*)malloc(sizeof(User));
    if (newUser == NULL) {
        return NULL;
    }

    //Check if user already exists
    if (search_user_by_name(name) != NULL) {
        return NULL;
    } else {
        strcpy(newUser->name, name); //Assign user's name
    }
    if (search_user_by_email(email) != NULL) {
        return NULL;
    } else {
        strcpy(newUser->email, email); //Assign user's email

    }

    user_ID++;
    newUser->user_id = user_ID; //Assign a unique user ID

    newUser->friends = NULL;
    newUser->posts = NULL;

    root = insert(root, newUser); //Insert into AVL tree

    return newUser;
}

void delete_user(User* user) {
    if (user == NULL) {
        return;
    }

    root = delete(root, user);
    free(user);
}

void change_user_name(User* user, char* new_name) {
    // Remove the user from the AVL tree
    root = delete(root, user);

    // Update the name
    strcpy(user->name, new_name);

    // Reinsert the user into the AVL tree
    root = insert(root, user);
}

void change_user_email(User* user, char* new_email) {
    strcpy(user->email, new_email);
}

User* search_user_by_name(const char* name) {
    struct Node* ptr = root;

    while (ptr != NULL) {

        if (strcmp(name, ptr->user->name) == 0) {
            return ptr->user; //found
        } else if (strcmp(name, ptr->user->name) < 0) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }

    return NULL;
}

User* search_user_by_email(const char* email) {
    struct Node* ptr = root;

    while (ptr != NULL) {

        if (strcmp(email, ptr->user->email) == 0) {
            return ptr->user; //found
        } else if (strcmp(email, ptr->user->email) < 0) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }

    return NULL;
}

void print_users_recursive(struct Node* node) {
    if (node == NULL) return;

    print_users_recursive(node->left); //Traverse left subtree
    printf("%s,", node->user->name); //Print user name
    print_users_recursive(node->right); //Traverse right subtree
}

//In-order Traversal of the AVL tree of type user structs
void print_users() {
    print_users_recursive(root); //Start traversal from the global root
    printf("\n");
}

struct FriendNode* check_if_friends(User* user1, User* user2) {
    struct FriendNode* curr = user1->friends;

    while (curr != NULL) {
        if (curr->user == user2) {
            return curr; //Friendship found
        }
        curr = curr->next;
    }
    return NULL; //Friendship does not exist
}

void add_friend(User* user1, User* user2) {
    //Check if they are already friends
    if (check_if_friends(user1, user2) != NULL) {
        return;
    }

    //Add user2 to user1's linked list of friends
    struct FriendNode* newFriend = (struct FriendNode*)malloc(sizeof(struct FriendNode));

    newFriend->user = user2;
    newFriend->next = user1->friends;
    newFriend->chat.front = NULL;
    newFriend->chat.end = NULL;
    newFriend->chat.num_messages = 0;
    user1->friends = newFriend;

    //Add user1 to user2's linked list of friends
    newFriend = (struct FriendNode*)malloc(sizeof(struct FriendNode));

    newFriend->user = user1;
    newFriend->next = user2->friends;
    newFriend->chat.front = NULL;
    newFriend->chat.end = NULL;
    newFriend->chat.num_messages = 0;
    user2->friends = newFriend;
}

void delete_friend(User* user1, User* user2) {
    // Remove user2 from user1's friends list
    struct FriendNode** curr = &(user1->friends);
    while (*curr != NULL) {
        if ((*curr)->user == user2) {
            struct FriendNode* temp = *curr;
            *curr = (*curr)->next;
            free(temp);
            break;
        }
        curr = &((*curr)->next);
    }

    // Remove user1 from user2's friends list
    curr = &(user2->friends);
    while (*curr != NULL) {
        if ((*curr)->user == user1) {
            struct FriendNode* temp = *curr;
            *curr = (*curr)->next;
            free(temp);
            break;
        }
        curr = &((*curr)->next);
    }
}

void print_friends(User* user) {
    if (user == NULL) {
        return;
    }

    struct FriendNode* curr = user->friends;
    if (curr == NULL) {
        return;
    }

    while (curr != NULL) {
        printf("%s", curr->user->name); //Print friend's name
        if (curr->next != NULL) {
            printf(","); //Add comma if it is not the last friend
        }
        curr = curr->next;
    }

    printf("\n");

}

User** mutual_friends(User* user1, User* user2) {
    User** mutual_friends = (User**)malloc(10000*sizeof(User*));
    if (mutual_friends == NULL) {
        return NULL;
    }

    int a = 0;

    struct FriendNode* curr = user1->friends;

    while (curr != NULL) {
        struct FriendNode* curr2 = user2->friends;
        while (curr2 != NULL) {
            if (strcmp(curr->user->name, curr2->user->name) == 0) {
                mutual_friends[a] = curr->user;
                a++;
                break;
            }
            curr2 = curr2->next;
        }
        curr = curr->next;
    }

    mutual_friends[a] = NULL;


    return mutual_friends;
}

void print_mutual_friends(User** friends) {
    if (friends == NULL || friends[0] == NULL) { //Check if no mutual friends (corner case)
        return;
    }

    for (int i = 0; friends[i] != NULL; i++) {
        printf("%s", friends[i]->name); //Print the current mutual friend's name
        if (friends[i + 1] != NULL) {   //Add comma if not the last mutual friend
            printf(", ");
        }
    }
    printf("\n");
}

Message* create_message(User* sender, User* receiver, const char* content) {
    // Ensure sender and receiver are friends
    struct FriendNode* friendship = check_if_friends(sender, receiver);
    struct FriendNode* friendship2 = check_if_friends(receiver, sender);
    if (friendship == NULL || friendship2 == NULL) {
        return NULL;
    }

    Message* newMessage = (Message*)malloc(sizeof(Message));
    if (newMessage == NULL) {
        return NULL;
    }

    message_ID++;

    newMessage->message_id = message_ID;
    newMessage->sender = sender;
    newMessage->receiver = receiver;
    strcpy(newMessage->content, content);
    newMessage->next = NULL;

    Queue* chats[2] = {&(friendship->chat), &(friendship2->chat)};
    //Add the message to BOTH chat queues
    for (int i = 0; i < 2; i++) {
        Queue* chat = chats[i];
        if (chat->end == NULL) { //This means it is the first message in the queue
            chat->front = chat->end = newMessage;
        } else {
            chat->end->next = newMessage;
            chat->end = newMessage;
        }
        chat->num_messages++;

        //Delete oldest message if capacity goes over 50
        if (chat->num_messages > 50) {
            Message* temp = chat->front;
            chat->front = chat->front->next;
            free(temp);
            chat->num_messages--;
        }
    }

    return newMessage;
}

void print_message(Message* message) {
    if (message == NULL) {
        return;
    }

    printf("[%s:]%s,", message->sender->name, message->content);

}
void display_chat(User* user1, User* user2) {
    // Ensure user1 and user2 are friends
    struct FriendNode* friendship = check_if_friends(user1, user2);
    if (friendship == NULL) {
        return;
    }

    // Get the chat queue
    Queue* chat = &(friendship->chat);

    //Check if no messages in queue
    if (chat->front == NULL) {
        return;
    }

    Message* curr = chat->front;

    //Display all messages in the chat between users
    while (curr != NULL) {
        printf("[%s:]%s,", curr->sender->name, curr->content);
        curr = curr->next;
    }
    printf("\n");
}

Post* new_post(User* user, const char* content) {
    //Create a new post
    Post* newPost = (Post*)malloc(sizeof(Post));
    if (newPost == NULL) {
        return NULL;
    }

    newPost->user = user; //Assign post's user
    strcpy(newPost->content, content); //Assign post's content
    newPost->num_likes = 0;
    newPost->likers = NULL;

    post_ID++;

    newPost->post_id = post_ID;

    newPost->next = user->posts;
    user->posts = newPost;

    return newPost;
}

void add_like(Post* post, User* user) {

    LikerNode* curr = post->likers;

    //Check if user has already liked the post
    while (curr != NULL) {
        if (curr->liker == user) {
            return;
        }
        curr = curr->next;
    }

    LikerNode* newLiker = (LikerNode*)malloc(sizeof(LikerNode));
    if (newLiker == NULL) {
        return;
    }

    newLiker->liker = user;
    newLiker->next = post->likers;
    post->likers = newLiker;

    // Increment the like count
    post->num_likes++;


}

void display_feed(User* user1) {

}