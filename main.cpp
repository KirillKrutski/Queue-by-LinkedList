#include <iostream>
class Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        next = nullptr;
    }
};

class QueueLinkedList {
public:
    Node* head;
    Node* tail;

public:
    QueueLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void enqueue(int data) {
        Node* new_node = new Node(data);
        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    int dequeue() {
        if (!head) {
            std::cout << "Queue is empty" << std::endl;
            return -1;
        }
        int data = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return data;
    }

    void display() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void insert_before_negative(int data) {
        Node* current = head;
        Node* previous = nullptr;
        while (current) {
            if (current->data < 0) {
                Node* new_node = new Node(data);
                new_node->next = current;
                if (current == head) {
                    head = new_node;
                } else {
                    previous->next = new_node;
                }
                return;
            }
            previous = current;
            current = current->next;
        }
        enqueue(data);
    }

    void remove_negatives() {
        while (head && head->data < 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        Node* current = head;
        Node* previous = nullptr;
        while (current) {
            if (current->data < 0) {
                previous->next = current->next;
                delete current;
                current = previous->next;
            } else {
                previous = current;
                current = current->next;
            }
        }
    }

    int count_occurrences(int target) {
        int count = 0;
        Node* current = head;
        while (current) {
            if (current->data == target) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    void recursive_delete(Node* node) {
        if (!node)
            return;
        recursive_delete(node->next);
        delete node;
    }
};

int main() {
    QueueLinkedList queue;
    int value;
    std::cout << "Enter values (0 to stop): ";
    std::cin >> value;
    while (value != 0) {
        queue.enqueue(value);
        std::cin >> value;
    }

    std::cout << "Queue before insertion: ";
    queue.display();

    queue.insert_before_negative(1);
    std::cout << "Queue after insertion: ";
    queue.display();

    queue.remove_negatives();
    std::cout << "Queue after removing negatives: ";
    queue.display();

    int target;
    std::cout << "Enter a number to count its occurrences: ";
    std::cin >> target;
    int occurrences = queue.count_occurrences(target);
    std::cout << "Number of occurrences of " << target << ": " << occurrences << std::endl;

    queue.recursive_delete(queue.head);
    queue.display(); // Should print nothing, as the list is empty after deletion.

    return 0;
}
