#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Node {
    unsigned long long data;
    Node* next = NULL;
    Node* prev = NULL;
};

class List {
public:
    Node* head;
    Node* tail;

public:
    List() {
        head = NULL;
        tail = NULL;
    }

    void PrintList() {
        Node* temp = head;
        if (temp != NULL) {
            while (temp != NULL) {
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
        cout << endl;
    }
};

struct Iterator {

    Node* node;
    int id;
};

void push_front(List* lst, unsigned long long num) {

    Node* node = new Node;
    node->data = num;

    if (lst->head == NULL) {
        lst->head = node;
        lst->tail = node;
        lst->head->prev = NULL;
        lst->tail->next = NULL;
    }

    else {
        lst->head->prev = node;
        node->next = lst->head;
        lst->head = node;

    }
};

void push_back(List* lst, unsigned long long num) {

    Node* node = new Node;

    if (lst->head == NULL) {
        push_front(lst, num);
        delete node;
        return;
    }

    node->data = num;

    lst->tail->next = node;
    node->prev = lst->tail;
    lst->tail = node;

};

void incert(List* lst, unsigned long long num, Node* node) {

    if (lst->head == NULL) {
        push_front(lst, num);
        return;
    }

    if (lst->head == node) {
        push_front(lst, num);
        return;
    }
    if (node == lst->tail) {
        push_back(lst, num);
        return;
    }

    if (node == NULL) {
        return;
    }

    else {
        Node* tmp = new Node;
        tmp->data = num;
        tmp->next = node->next;
        tmp->prev = node;
        tmp->next->prev = tmp;
        node->next = tmp;
    }
};

void todelete(List* lst, Node* node) {

    if (node->next == NULL && node->prev == NULL) {
        lst->head = NULL;
        lst->tail = NULL;
    }

    else if (node->next == NULL) {
        lst->tail = lst->tail->prev;
        lst->tail->next = NULL;
    }

    else if (node->prev == NULL) {
        lst->head = lst->head->next;
        lst->head->prev = NULL;
    }

    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }
};

void iters(List* lst, Iterator** arr, int& kol, int id, char command[3]) {
    for (int i = 0; i < kol; i++) {
        if (arr[i]->id == id) {
            if (command[0] == 'B') {
                arr[i]->node = lst->head;
                return;
            }

            else if (command[0] == 'E') {
                arr[i]->node = lst->tail;
                return;
            }
        }
    }

    Iterator* tmp = new Iterator;

    tmp->id = id;

    arr[kol] = tmp;
    if (command[0] == 'B') {
        arr[kol]->node = lst->head;
        kol++;
    }

    else if (command[0] == 'E') {
        arr[kol]->node = lst->tail;
        kol++;
    }

    else {
        for (int i = 0; i < kol; i++) {
            if (arr[i]->id == atoi(command)) {

                arr[kol]->node = arr[i]->node;
            }
        }
        kol++;
    }
};

void deletebyiterator(List* lst, Iterator** arr, int id, int kol) {

    Node* tmp = new Node;

    for (int i = 0; i < kol; i++) {
        if (arr[i]->id == id) {
            tmp = arr[i]->node;

            for (int j = 0; j < kol; j++) {
                if (arr[j]->node == tmp) {

                    if (arr[j]->node->next != NULL) {
                        arr[j]->node = arr[j]->node->next;
                    }

                    else if (arr[j]->node->prev != NULL) {
                        arr[j]->node = arr[j]->node->prev;
                    }

                    else {
                        arr[j]->node = NULL;
                    }
                }
            }
        }
    }
    todelete(lst, tmp);
};

int main() {

    int kol = 0, x;
    List* lst = new List;
    Iterator* arr[10] = {};
    char command[100];

    while (true)
    {
        scanf("%s", command);

        if (feof(stdin) != 0)
        {
            break;
        }

        if (command[0] == '.') {
            cin >> command;
            if (command[0] == 'B') {
                cin >> command;
                push_front(lst, atoll(command));

            }

            else if (command[0] == 'E') {
                cin >> command;
                incert(lst, atoll(command), lst->tail->prev);
            }

            else {
                for (int i = 0; i < kol; i++) {
                    if (arr[i]->id == atoi(command)) {
                        cin >> command;
                        incert(lst, atoll(command), arr[i]->node->prev);
                        break;
                    }
                }
            }
        }

        else if (command[0] == 'A') {
            cin >> command;
            if (command[0] == 'B') {
                cin >> command;
                incert(lst, atoll(command), lst->head);
            }

            else if (command[0] == 'E') {

                cin >> command;
                push_back(lst, atoll(command));
            }

            else {
                for (int i = 0; i < kol; i++) {
                    if (arr[i]->id == atoi(command)) {
                        cin >> command;
                        incert(lst, atoll(command), arr[i]->node);
                        break;
                    }

                }
            }
        }

        else if (command[0] == 'P') {
            cin >> command;
            if (command[0] == 'A') {
                lst->PrintList();
            }

            else {
                for (int i = 0; i < kol; i++) {
                    if (arr[i]->id == atoi(command)) {
                        cout << arr[i]->node->data << " ";
                        cout << endl;
                    }
                }
            }
        }

        else if (command[0] == 'R') {
            cin >> command;
            if (command[0] == 'B') {
                todelete(lst, lst->head);
            }

            else if (command[0] == 'E') {
                todelete(lst, lst->tail);
            }

            else {
                deletebyiterator(lst, arr, atoi(command), kol);
            }
        }

        else if (command[0] == 'i') {
            cin >> x;
            cin >> command;
            iters(lst, arr, kol, x, command);
        }

        else if (command[0] == '+') {
            cin >> command;
            for (int i = 0; i < kol; i++) {
                if (arr[i]->id == atoi(command)) {
                    if (arr[i]->node->next != NULL) {
                        arr[i]->node = arr[i]->node->next;
                    }
                }
            }
        }

        else if (command[0] == '-') {
            cin >> command;
            for (int i = 0; i < kol; i++) {
                if (arr[i]->id == atoi(command)) {
                    if (arr[i]->node->prev != NULL) {
                        arr[i]->node = arr[i]->node->prev;
                    }
                }
            }
        }
    }
    return 0;
}