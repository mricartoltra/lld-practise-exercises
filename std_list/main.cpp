
template <typename T>
class myDoublyLinkedList {
    struct Node{
        Node* next;
        Node* prev;
        T data;

        Node(const T& val) : data(val), next(nullptr), prev(nullptr){}
    };


};