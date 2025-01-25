// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    // add attributes
    int user_id; //Unique user ID
    char name[50]; //User name
    char email[50]; //User email

    struct FriendNode* friends; //Linked list of user friends
    struct Post* posts; //Linked list of user posts
} User;

typedef struct {
    User* liker;
    struct LikerNode* next;
} LikerNode;

typedef struct {
    // add attributes
    int post_id; //Unique post ID
    User* user; //Poster
    int num_likes; //Number of users who liked the post
    char content[257]; //Post content (256 chars max & 1 for null)

    LikerNode* likers; //Head of linked list of users that liked the post
    struct Post* next; //Pointer to the next post
} Post;

typedef struct Message {
    // add attributes
    int message_id;
    User* sender;
    User* receiver;
    char content[257];
    struct Message* next; //Pointer to the next message for linked list functionality
} Message;

struct Node {
    User* user; //Pointer to user data
    struct Node* left; //Left node
    struct Node* right; //Right node
    int height; //Node height
};

typedef struct {
    struct Message *front; //Oldest message
    struct Message *end; //Most recent message added
    int num_messages;
} Queue;

typedef struct FriendNode { //call graphNode
    User* user; //Pointer to friend user
    Queue chat;
    struct FriendNode* next; //Pointer to next friend in linked list of friends
};

//void testingParser(int arg1, char *arg2);

//Helper functions
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
//add an edge in graph, add a queue for chat
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

#endif
