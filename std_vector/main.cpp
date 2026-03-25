#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename T>
class MKVector {
private:
    T* data_; //here I store the dynamically allocated data
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity)
    {
        T* temp = new T[new_capacity];

        for (size_t i = 0; i < size_; ++i) {
            temp[i] = std::move(data_[i]);
        }

        delete[] data_;

        data_ = temp;
        capacity_ = new_capacity;
    }

public:
    MKVector() : data_(nullptr), size_(0), capacity_(0) {}

    //rule of 5
    ~MKVector() {
        delete[] data_; 
    }

    MKVector(const MKVector& other) : size_(other.size_), capacity_(other.capacity_) {

        data_ = new T[capacity_];

        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    MKVector& operator=(const MKVector& other) {
        if (this == &other) {
            return *this; 
        }

        delete[] data_; 

        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        
        return *this;
    }

    MKVector(MKVector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    MKVector& operator=(MKVector&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] data_; 

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    //some useful functions
    void push_back(const T& value)
    {
        if(size_ == capacity_)
        {
            reallocate(capacity_ == 0 ? 1 : 2 * capacity_);
        }

        data_[size_++] = value;
    }
    void push_back(T&& value)
    {
        if(size_ == capacity_)
        {
            reallocate(capacity_ == 0 ? 1 : 2 * capacity_);
        }

        data_[size_++] = std::move(value);
    }

    void pop_back()
    {
        if(size_== 0) return;
        --size_;
    }

    size_t size() const {return size_;}
    size_t capacity() const {return capacity_;}
    bool empty() const {return size_ == 0;}

    T& operator[](size_t index) {return data_[index];}
    const T& operator[](size_t index) const {return data_[index];}
    
    T& at(size_t index)
    {
        if(index >= size_) throw std::out_of_range("Index out of bounds");
        return data_[index];
    }
    const T& at(size_t index) const
    {
        if(index >= size_) throw std::out_of_range("Index out of bounds");
        return data_[index];
    } 

    using iterator = T*;
    using const_iterator = const T*;

    iterator begin() { return data_; }
    iterator end() { return data_ + size_; }

    const_iterator begin() const { return data_; }
    const_iterator end() const { return data_ + size_; }
};


int main()
{
    MKVector<int> myVec;
    myVec.push_back(10);
    myVec.push_back(20);

    for (int val : myVec) {
        std::cout<<val<<std::endl;
    }
}