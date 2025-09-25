#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Structure for message
struct message {
    long msg_type;       // Message type
    char msg_text[100];  // Message content
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Step 1: Generate unique key
    key = ftok("progfile", 65); // "progfile" can be any file

    // Step 2: Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Step 3: Prepare message
    msg.msg_type = 1; // Message type 1
    strcpy(msg.msg_text, "Hello from parent via message queue!");

    // Step 4: Send message
    msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
    printf("Message sent to queue: %s\n", msg.msg_text);

    // Step 5: Receive message
    struct message rcv_msg;
    msgrcv(msgid, &rcv_msg, sizeof(rcv_msg.msg_text), 1, 0);
    printf("Message received from queue: %s\n", rcv_msg.msg_text);

    // Step 6: Destroy message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

