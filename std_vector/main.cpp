//Implementing vector
#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class myVector {
private:
    size_t capacity_ = 0;
    size_t size_ = 0;
    T* data_ = nullptr;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]); 
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity; 
    }

    void cleanup() {
        delete[] data_;
        data_ = nullptr;
    }

public:
    myVector() : capacity_(1), size_(0), data_(new T[1]()) {}

    myVector(size_t size, const T& val) : capacity_(size), size_(size), data_(new T[size]) {
        for(size_t i = 0; i < size_; ++i) {
            data_[i] = val;
        }
    }

    //rule of 5
    //Destructor
    ~myVector() {
        cleanup();
    }

    //Copy Constructor
    myVector (const myVector<T>& rhs) : capacity_(rhs.capacity_), size_(rhs.size_), data_(new T[rhs.capacity_]) {
        std::copy(rhs.data_, rhs.data_ + rhs.size_, data_);
    }

    //Copy Assignment
    myVector& operator=(const myVector<T>& rhs) {
        if (this != &rhs) {
            cleanup();
            
            capacity_ = rhs.capacity_;
            size_ = rhs.size_;
            data_ = new T[capacity_];
            std::copy(rhs.data_, rhs.data_ + rhs.size_, data_);
        }
        return *this;
    }

    //Move Constructor
    myVector (myVector<T>&& rhs) noexcept : capacity_(rhs.capacity_), size_(rhs.size_), data_(rhs.data_) {
        rhs.capacity_ = 0;
        rhs.size_ = 0;
        rhs.data_ = nullptr;
    }

    //Move Assigment
    myVector& operator=(myVector<T>&& rhs) {
        if (this != &rhs) {
            cleanup();
            
            capacity_ = rhs.capacity_;
            size_ = rhs.size_;
            data_ = rhs.data_;

            rhs.capacity_ = 0;
            rhs.size_ = 0;
            rhs.data_ = nullptr;
        }
        return *this;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_] = value;
        size_++;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--; 
            //In a production vector, I would have to call the destructor of the popped element
        }
    }

    void clear() {
        size_ = 0;
    }

    void reserve(size_t cap) {
        if (cap > capacity_) {
            resize(cap);
        }
    }

    bool empty() const {
        return size_ == 0;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of bounds!");
        return data_[index];
    }

    T& front() { return data_[0]; }
    T& back()  { return data_[size_ - 1]; }

    T* begin() { return data_; }
    T* end()   { return data_ + size_; }
};

int main()
{
    //test myVector
    myVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    for(int* it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " "; 
    }
    //Output: 10 20 30
}