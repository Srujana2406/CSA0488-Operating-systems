#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msg_id;
    struct msg_buffer msg;

    key = ftok("msgq_program", 65);

    msg_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue ID: %d\n", msg_id);

    printf("Enter message to send: ");
    fgets(msg.msg_text, MAX_MSG_SIZE, stdin);

    msg.msg_type = 1;

    if (msgsnd(msg_id, (void *)&msg, MAX_MSG_SIZE, 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent: %s", msg.msg_text);

    return 0;
}

