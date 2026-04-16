#include <atomic>
#include <utility>

template <typename T>
class myUnique_pointer
{
    private:
        T* pointer = nullptr;

    public:
        explicit myUnique_pointer(T* ptr = nullptr) : pointer(ptr){}

        ~myUnique_pointer() {
            delete pointer;
        }

        //Copy
        myUnique_pointer (const myUnique_pointer<T>& object) = delete;
        myUnique_pointer& operator=(const myUnique_pointer<T>& object) = delete;

        //Move
        myUnique_pointer (myUnique_pointer<T>&& object) noexcept
            : pointer(std::exchange(object.pointer,nullptr))
        {}
        
        myUnique_pointer& operator=(myUnique_pointer<T>&& object) noexcept
        {
            if (this == &object) {
                return *this; 
            }

            delete pointer;

            pointer = object.pointer;
            object.pointer = nullptr;

            return *this;
        }

        T& operator*() const { return *pointer;}
        
        T* operator->() const { return pointer;}

        //TODO
        // get(), release(), reset()
};

struct ControlBlock {
    std::atomic<int> strong_count{0};
    std::atomic<int> weak_count{0};

    ControlBlock(int sc) : strong_count(sc), weak_count{} {}
    ControlBlock(int sc, int wc) : strong_count(sc), weak_count(wc) {}
};

template <typename T>
class myShared_pointer
{
    private:
        T* pointer = nullptr;
        ControlBlock* ctrl_block = nullptr;

        void cleanup()
        {
            if (ctrl_block) {
                ctrl_block->strong_count--;
                if(ctrl_block->strong_count == 0) {
                    delete pointer;
                    if(ctrl_block->weak_count == 0) delete ctrl_block;
                }
            }
        }

        void increment()
        {
            if (ctrl_block)
            {
                ctrl_block->strong_count++;
            }
        }

    public:
        explicit myShared_pointer(T* ptr = nullptr) : pointer(ptr)
        {
            if (ptr)
            {
                increment();
            }
        }

        ~myShared_pointer()
        {
            cleanup();
        }

        //Copy incrementing
        myShared_pointer (const myShared_pointer<T>& other) noexcept
        {
            pointer = other.pointer;
            ctrl_block = other.ctrl_block;
            increment();
        }

        myShared_pointer& operator=(const myShared_pointer<T>& other)noexcept
        {
            if (this != &other) {
                cleanup();
                
                pointer = other.pointer;
                ctrl_block = other.ctrl_block;
                increment();
            }
            return *this;
        }

        //Move stealing
        myShared_pointer (myShared_pointer<T>&& other) noexcept
        {
            pointer = other.pointer;
            ctrl_block = other.ctrl_block;

            other.pointer = nullptr;
            other.ctrl_block = nullptr;
        }

        myShared_pointer& operator=(myShared_pointer<T>&& other) noexcept
        {
            if (this != &other) 
            {
                cleanup();
                
                pointer = other.pointer;
                ctrl_block = other.ctrl_block;
                
                other.pointer = nullptr;
                other.ctrl_block = nullptr;
            }
            return *this;
        }

        T& operator*() const { return *pointer;}
        
        T* operator->() const { return pointer;}
};

template <typename T>
class myWeak_pointer
{
    private:
        T* pointer = nullptr;
        ControlBlock* ctrl_block = nullptr;

        void cleanup()
        {
            if (ctrl_block) {
                ctrl_block->weak_count--;
                if (ctrl_block->strong_count == 0 && ctrl_block->weak_count == 0) {
                    delete ctrl_block; 
                }
            }
        }

        void increment()
        {
            if (ctrl_block)
            {
                ctrl_block->weak_count++;
            }
        }


    public:
        explicit myWeak_pointer(const myShared_pointer<T>& shared)
        {
            pointer = shared.pointer;
            ctrl_block = shared.ctrl_block;
            if (ctrl_block)
            {
                ctrl_block->weak_count++;
            }
        }

        ~myWeak_pointer()
        {
            cleanup();
        }

        //Copy
        myWeak_pointer(const myWeak_pointer<T>& other) noexcept
        {
            pointer = other.pointer;
            ctrl_block = other.ctrl_block;
            increment();
        }

        myWeak_pointer& operator=(const myWeak_pointer<T>& other) noexcept
        {
            if(this != &other)
            {
                cleanup();

                pointer = other.pointer;
                ctrl_block = other.ctrl_block;
                increment();
            }

            return *this;
        }

        myWeak_pointer(myWeak_pointer<T>&& other) noexcept
        {
            pointer = other.pointer;
            ctrl_block = other.ctrl_block;
            
            other.pointer = nullptr;
            other.ctrl_block = nullptr;
        }

        myWeak_pointer& operator=(myWeak_pointer<T>&& other) noexcept
        {
            if (this != &other) 
            {
                cleanup();
                
                pointer = other.pointer;
                ctrl_block = other.ctrl_block;
                
                other.pointer = nullptr;
                other.ctrl_block = nullptr;
            }

            return *this;
        }
};

int main(void)
{

};