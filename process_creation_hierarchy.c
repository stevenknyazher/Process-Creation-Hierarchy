#include <stdio.h>
#include <stdlib.h>

struct node {
    int parent;
    int first_child;
    int second_child;
    int third_child;
} *pcb = NULL;

int num_processes;
typedef struct node pcb_type;

void parameter() {
    printf("Enter the maximum number of processes: ");
    scanf("%d", &num_processes);
    printf("\n");
    
    pcb = (pcb_type*) malloc(num_processes * sizeof(pcb_type));
    
    pcb[0].parent = 0;
    pcb[0].first_child = -1;
    pcb[0].second_child = -1;
    pcb[0].third_child = -1;
    
    for (int i = 1; i < num_processes; i++) {
        pcb[i].parent = -1;
        pcb[i].first_child = -1;
        pcb[i].second_child = -1;
        pcb[i].third_child = -1;
    }
    return;
}

void printr() {
    int i;
    printf ("Process hierarchy:\n");
    for (i = 0; i < num_processes; i++) {
        if (pcb[i].parent != -1) {
            printf ("%d", pcb[i].parent);
        }
    }
    printf (" < Parent processes (Disregard first 0)\n↓\n0");
    for (i = 0; i < num_processes; i++) {
        if (pcb[i].first_child != -1) {
            printf ("%d", pcb[i].first_child);
        }
        if (pcb[i].third_child != -1) {
            printf ("%d", pcb[i].third_child);
        }
    }
    printf (" < Child processes (Disregard first 0)\n\n");
    return;
}

void create() {
    int p;
    int q = 1;
    int next_child;
    int num_children = 0;
    printf("Enter the parent process id: ");
    scanf("%d", &p);
    
    while (pcb[q].parent != -1) {
        q++;
    }
        
    pcb[q].parent = p;
    pcb[q].first_child = -1;
    pcb[q].third_child = -1;

    if (pcb[p].first_child == -1) {
        pcb[p].first_child = q;
        num_children = 1;
    } else {
        num_children = 2;
        next_child = pcb[p].first_child;
        while (pcb[next_child].third_child != -1 ) {
            next_child = pcb[next_child].third_child;
            num_children++;
        }
        pcb[next_child].third_child = q;
        pcb[q].second_child = next_child;
    }
    printf("Parent process %d created a new child process %d \n\n", p, q);
    return;
}


void destroy(int q) {
    if (q == -1) {
        return;
    } else {
        destroy(pcb[q].third_child);
        destroy(pcb[q].first_child);
        printf("Child process %d was destroyed \n", q);
        pcb[q].parent = -1;
        pcb[q].first_child = -1;
        pcb[q].second_child = -1;
        pcb[q].third_child = -1;
    }
    return;
}

void destroyer() {
    int p;
    printf("Enter the parent process whose descendants are to be destoryed: ");
    scanf("%d", &p);
    destroy(pcb[p].first_child);
    pcb[p].first_child = -1;
    printf("\n");
    return;
}

void quit() {
    if(pcb != NULL) free(pcb);
    return;
}

int main() {
    int choice;
    while (choice != 4) {
        printf("Process creation and destruction\n");
        printf("--------------------------------\n");
        printf("1) Enter parameters\n");
        printf("2) Create a new child process\n");
        printf("3) Destroy all descendants of a process\n");
        printf("4) Quit program and free memory\n\n");
        printf("Enter selection: ");
        scanf("%d", &choice);
        if (choice == 1) {
            parameter();
        } else if (choice == 2) {
            create();
            printr();
        } else if (choice == 3) {
            destroyer();
            printr();
        }
        else if (choice == 4) {
            quit();
        }
    }
    return 1;
}
