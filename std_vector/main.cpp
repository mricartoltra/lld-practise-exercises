//Implementing vector


template<typename T>
class myVector {
private:
    size_t* capacity_ = nullptr;
    size_t* size_ = nullptr;
    T* data_ = nullptr;

    void allocate(T& value)
    {

    }

    void resize(size_t size)
    {

    }

public:
    myVector(){}

    myVector(size_t size, size_t val){}

    //rule of 5
    //Destructor
    ~myVector(){}

    //Copy Constructor
    myVector (const myVector<T>& rhs) {

    }
    //Copy Assignment
    myVector& operator=(const myVector<T>& rhs) {
        return this*;
    }
    //Move Constructor
    myVector (myVector<T>&& rhs) {

    }
    //Move Assigment
    myVector& operator=(myVector<T>&& rhs) {
        return this*;
    }

    void push_back(T& value)
    {
        if(size_ == capacity_){
            resize(capacity_*2);
        }
        
        allocate(value);
        size_++;
    }

    void pop_back()
    {

    }

    void clear()
    {

    }

    void reserve(size_t cap)
    {

    }

    bool empty()
    {
        return !size_;
    }

    T& operator[](size_t index)
    {

    }

    T& at(size_t index)
    {

    }

    T& front()
    {

    }

    T& back()
    {

    }

    T* begin()
    {

    }

    T* end()
    {

    }
};

int main()
{
    //test myVector
}