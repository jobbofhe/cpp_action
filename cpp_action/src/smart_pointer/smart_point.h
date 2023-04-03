// #ifndef SMART_POINTER_SMART_POINT_H_
// #define SMART_POINTER_SMART_POINT_H_

// #include "shared_ptr_impl.h"

// int TestSharedPtr() { 
//     SharedPtr<Person> ptr1(new Person()); 
//     SharedPtr<Person> ptr2(ptr1); 
//     SharedPtr<Person> ptr3; 
//     ptr3 = ptr2; 
    
//     std::cout << "use_cout: " << ptr1.use_count() << std::endl; 
//     std::cout << "use_cout: " << ptr2.use_count() << std::endl; 
//     std::cout << "use_cout: " << ptr3.use_count() << std::endl; 
//     return 0; 
// }

// void TestSmartPointer() {
//     TestSharedPtr();
// }

// # endif // SMART_POINTER_SMART_POINT_H_