#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

struct LinkedList* createLinkedList() {
    struct LinkedList* newList = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    newList->head = NULL;
    return newList;
}

void insertAtPosition(struct LinkedList* list, int data, int pos) {
    struct Node* newNode = createNode(data);
    
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    
    if (pos == 1) {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
        return;
    }
    
    struct Node* current = list->head;
    for (int i = 1; i < pos - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Invalid position for insertion!\n");
        free(newNode);
        return;
    }
    
    newNode->prev = current;
    newNode->next = current->next;
    
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    
    current->next = newNode;
}

void deleteAtPosition(struct LinkedList* list, int pos) {
    if (list->head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    struct Node* current = list->head;
    for (int i = 1; i < pos && current != NULL; i++) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Invalid position for deletion!\n");
        return;
    }
    
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    
    free(current);
}

void printList(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    struct LinkedList* list = createLinkedList();
    
    int numElements, data;
    printf("Enter the number of elements: ");
    scanf("%d", &numElements);
    
    for (int i = 0; i < numElements; i++) {
        
        scanf("%d", &data);
        insertAtPosition(list, data, i + 1);
    }
    
    printList(list);
    
    int insertData, insertPos;
    printf("Enter element to insert: ");
    scanf("%d", &insertData);
    printf("Enter position for insertion: ");
    scanf("%d", &insertPos);
    insertAtPosition(list, insertData, insertPos);
    
    printList(list);
    
    int pos;
    printf("Enter position for deletion: ");
    scanf("%d", &pos);
    deleteAtPosition(list, pos);
    
    printf("List after deletion: ");
    printList(list);
    
    freeList(list);
    
    return 0;
}
