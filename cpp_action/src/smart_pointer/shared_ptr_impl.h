#include <iostream>

class Person { 
public: 
    Person()  { id_ = 0; } 
    Person(int id) : id_(id) {} 
    void Print() { std::cout << "id: " << id_ << std::endl; } 
private: int id_; 

}; 

class SharedCount { 
public: 
    SharedCount() : count_(1) {} 
    void count_add() { ++this->count_; } 
    int64_t count_reduce() { return --this->count_; } 
    int64_t get_count() { return this->count_; } 
    
private: 
    int64_t count_; 

}; 

template<typename T>
class SharedPtr { 
public: 
    explicit SharedPtr(T* ptr = nullptr) noexcept : ptr_(ptr) { 
        std::cout << "constructor..." << std::endl; 
        if (ptr) { SharedCount_ = new SharedCount(); 
        } 
    } 
    
    ~SharedPtr() { 
        std::cout << "destructor..." << std::endl; 
        if (ptr_ && !SharedCount_->count_reduce()) { 
            delete ptr_; delete SharedCount_; 
        } 
    } 
    
    T& operator*() const noexcept { return *ptr_; } 
    T* operator->() const noexcept { return ptr_; } 
    T* get() const noexcept { return ptr_; } 
    
    SharedPtr(const SharedPtr<T>& other) noexcept { 
        std::cout << "copy..." << std::endl; 
        ptr_ = other.ptr_; 
        if (ptr_) { 
            other.SharedCount_->count_add(); 
            SharedCount_ = other.SharedCount_; 
        } 
    } 
    
    // move 
    SharedPtr(const SharedPtr<T>&& other) noexcept { 
        std::cout << "move..." << std::endl; 
        ptr_ = other.ptr_; 
        if (ptr_) { 
            SharedCount_ = other.SharedCount_; 
            other.ptr_ = nullptr; 
            other.SharedCount_ = nullptr; 
        } 
    } 

    void swap(SharedPtr<T>& rhs) noexcept {
        using std::swap;
        swap(this->ptr_, rhs.ptr_);
        swap(this->SharedCount_, rhs.SharedCount_);
    }

    // assign 
    SharedPtr<T>& operator=(const SharedPtr<T>& other) noexcept { 
        std::cout << "operator=: " << std::endl;
        if (this == &other) {
            return *this;
        }

        // 创建一个临时变量，用 other 初始化，tmp 与 this交换完成之后，就相当于将 other 赋值给了 this, 
        // 然后除了这个作用域， tmp 自动析构
        SharedPtr<T> tmp(other);
        tmp.swap(*this);
    }

    // // assign 
    // SharedPtr<T>& operator=(const SharedPtr<T>& other) noexcept { 
    //     std::cout << "operator=: " << std::endl; 
    //     if (this == &other) { 
    //         return *this; 
    //     } 
        
    //     if (!other.ptr_) { 
    //         if (this->ptr_ != nullptr) 
    //         { 
    //             // 当前对象(被赋值对象)如果不为空，且计数为 0，需要先 delete 
    //             if (this->SharedCount_->count_reduce() == 0) { 
    //                 delete this->ptr_; 
    //                 delete this->SharedCount_; 
    //                 this->ptr_ = nullptr; 
    //                 this->SharedCount_ = nullptr; 
    //             } 
    //         } 
    //         this->ptr_ = other.ptr_; 
    //         this->SharedCount_ = other.SharedCount_; 
    //     } else { 
    //         if (this->ptr_ != nullptr) { 
    //             if (this->SharedCount_->count_reduce() == 0) { 
    //                 delete this->ptr_; 
    //                 delete this->SharedCount_; 
    //                 this->ptr_ = nullptr; 
    //                 this->SharedCount_ = nullptr; 
    //             } 
    //         } 
    //         this->ptr_ = other.ptr_; 
    //         this->SharedCount_ = other.SharedCount_; 
            
    //         // 赋值后, 本类计数器需要+1 
    //         this->SharedCount_->count_add(); 
    //     }
        
    //     return *this; 
    // } 
    
    int64_t use_count() const noexcept { 
        if (ptr_) { 
            return SharedCount_->get_count(); 
        } else { 
            return 0; 
        } 
    } 
    
private: 
    T* ptr_; 
    SharedCount* SharedCount_; 
}; 

int TestSharedPtr() { 
    SharedPtr<Person> ptr1(new Person()); 
    SharedPtr<Person> ptr2(new Person());
    SharedPtr<Person> ptr3; 
    ptr3 = ptr2; 
    
    std::cout << "use_cout: " << ptr1.use_count() << std::endl; 
    std::cout << "use_cout: " << ptr2.use_count() << std::endl; 
    std::cout << "use_cout: " << ptr3.use_count() << std::endl; 
    return 0; 
}

void TestSmartPointer() {
    TestSharedPtr();
}

// int main() { 
//     SharedPtr<Person> ptr1(new Person()); 
//     SharedPtr<Person> ptr2(ptr1); 
//     SharedPtr<Person> ptr3; 
//     ptr3 = ptr2; 
    
//     std::cout << "use_cout: " << ptr1.use_count() << std::endl; 
//     std::cout << "use_cout: " << ptr2.use_count() << std::endl; 
//     std::cout << "use_cout: " << ptr3.use_count() << std::endl; 
//     return 0; 
// }

