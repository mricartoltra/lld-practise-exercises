
template <typename T>
class myDoublyLinkedList {
    struct Node{
        Node* next;
        Node* prev;
        T data;

        Node(const T& val) : data(val), next(nullptr), prev(nullptr){}
    };

    Node* head;
    Node* tail;
    size_t count;

public:
    myDoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~myDoublyLinkedList()
    {
        while (!empty()) {
            pop_front();
        }
    }

    //copy constructor
    myDoublyLinkedList(const myDoublyLinkedList<T>& rhs)
    {
        Node* curr = rhs.head;
        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    }

    //copy assignment
    myDoublyLinkedList& operator=(const myDoublyLinkedList<T>& rhs)
    {
        if(this != &rhs)
        {
            while (!empty()) {
                pop_front();
            }

            Node* curr = rhs.head;
            while (curr != nullptr) {
                push_back(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    //move constructor
    myDoublyLinkedList(myDoublyLinkedList<T>&& rhs) noexcept : head(rhs.head), tail(rhs.tail), count(rhs.count)
    {
        rhs.head = nullptr;
        rhs.tail = nullptr;
        rhs.count = 0;
    }

    //move assignment
    myDoublyLinkedList& operator=(myDoublyLinkedList<T>&& rhs) noexcept
    {
        if(this != &rhs)
        {
            while (!empty()) {
                pop_front();
            }

            head = rhs.head;
            tail = rhs.tail;
            count = rhs.count;

            rhs.head = nullptr;
            rhs.tail = nullptr;
            rhs.count = 0;
        }
        return *this;
    }

    void push_front(const T& val){

        Node* new_node = new Node(val);

        if(head!=nullptr)
        {
            Node* temp = head;
            head = new_node;
            head->next = temp;
            head->next->prev = head;
        }
        else
        {
            head = new_node;
            tail = new_node;
        }

        count++;
    }

    void push_back(const T& val){

        Node* new_node = new Node(val);

        if(tail!=nullptr)
        {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        else
        {
            head = new_node;
            tail = new_node;
        }

        count++;
    }

    void pop_front(){
        if(head != nullptr)
        {
            
            Node* temp = head;
            head = head->next;

            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }

            delete temp;

            count--;
        }
    }

    void pop_back(){
        if(tail != nullptr)
        {
            
            Node* temp = tail;
            tail->prev->next = nullptr;

            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr;
            }

            delete temp;

            count--;
        }
    }

    size_t size() const{ return count;}
    bool empty() const{ return count == 0;}

};