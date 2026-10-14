# Social Media Platform (C)

A small social network engine written in C, using hand-built data structures: users, friendships, messaging, posts, likes and a feed. A driver program reads commands from a CSV file and runs them, which makes the whole system scriptable and easy to test.

## Features

| Area | What it does |
| --- | --- |
| **User profiles** | Create, rename, change the email of and delete users. IDs are generated automatically. Users are kept in an **AVL tree** so they print in sorted order. |
| **Friendships** | Add and remove friends (a graph stored as linked lists) and print a user's friends in order. |
| **Search** | Find a user by name or by email. |
| **Mutual friends** | Compute and print the friends two users share. |
| **Messaging** | Each friendship has its own **FIFO queue** of messages, and a chat prints in the order it was sent. |
| **Posts and likes** | Users create posts (up to 256 characters) and other users like them. |
| **Feed** | Display a user's feed. |

## Files

| File | Purpose |
| --- | --- |
| `functions.h` | Data structures (`User`, `Post`, `Message`, AVL `Node`, `Queue`, `FriendNode`) and function prototypes |
| `functions.c` | Implementations of everything above |
| `main.c` | Driver: reads `test_cases.csv` line by line and calls the matching function |
| `CMakeLists.txt` | Builds the `assignment` executable |
| `output.txt` | Example output from a run |

## Building and running

```bash
cmake -S . -B build
cmake --build build
cd build && ./assignment
```

The driver opens **`test_cases.csv`** from the working directory, so put one beside the executable. Each line is a function name followed by its arguments:

```
create_user,Alisa,alisa@example.com
create_user,Gavin,gavin@example.com
add_friend,Alisa,Gavin
print_users
```

Users are referenced by name in commands like `add_friend`, `delete_user` and `change_user_name`.

## Notes

`main.c` calls a helper, `testingParser`, whose prototype is commented out in `functions.h`. Older compilers only warn about this, but newer ones (GCC 14 and later) treat the implicit declaration as an error. If you hit it, uncomment the prototype in `functions.h`.
