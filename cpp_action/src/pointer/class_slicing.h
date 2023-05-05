#ifndef CLASS_SLICING_H_
#define CLASS_SLICING_H_

#include <iostream>

class BaseObject {
public:
    virtual void foo() const  {std::cout << "BaseObject" << std::endl;}
    virtual void func_1() const  {std::cout << "BaseObject" << std::endl;}
};

class IInterface {
public:
    virtual  void foo() const  {std::cout << "IInterface" << std::endl;}
    virtual  void func_1() const  {std::cout << "IInterface" << std::endl;}
};

//
// whether it is always safe to do self check in equality operator
//
class Operator : public BaseObject,  public IInterface
{
public:
    Operator() {}
    void foo() const override {std::cout << "Operator" << std::endl;}
    void func_1() const override {std::cout << "Operator" << std::endl;}
    bool operator==(const Operator &rhs) const
    {
        auto p_rhs = &rhs;
        printf("this: %p\n" , this);
        printf("&rhs: %p\n",  p_rhs);
        if (this == p_rhs)
        {
            std::cout << "this == &rhs for both objects, as expected" << std::endl;
            return true;
        }
        return false;
    }
    bool equal_op(const IInterface &rhs) const
    {
        auto p_rhs = &rhs;
        printf("this: %p\n" , this);
        printf("&rhs: %p\n",  p_rhs);
        if (this == p_rhs)
        {
            std::cout << "1: this == &rhs for object and interface, UNEXPECTED (because of RTTI?), now check 'const void *' version" << std::endl;
            if (static_cast<const void *>(this) == static_cast<const void *>(p_rhs))
            {
                std::cout << "static_cast<const void *>(this) == static_cast<const void *>(p_rhs), WEIRD" << std::endl;
            }
            else
            {
                std::cout << "static_cast<const void *>(this) == static_cast<const void *>(p_rhs), it makes sense" << std::endl;
            }
            return true;
        }
        return false;
    }
    bool equal_op_p(const IInterface *rhs) const
    {
        printf("this: %p\n" , this);
        printf("rhs: %p\n",  rhs);
        if (this == rhs)
        {
            std::cout << "2: this == rhs for object and interface, UNEXPECTED (because of RTTI?), now check 'const void *' version" << std::endl;
            if (static_cast<const void *>(this) == static_cast<const void *>(rhs))
            {
                std::cout << "static_cast<const void *>(this) == static_cast<const void *>(rhs), WEIRD" << std::endl;
            }
            else
            {
                std::cout << "static_cast<const void *>(this) == static_cast<const void *>(rhs), it makes sense" << std::endl;
            }
            return true;
        }
        return false;
    }

    // bool equal_op(const BaseObject& rhs) const
    // {
    //     auto p_rhs = &rhs;
    //     printf("this: %p\n" , this);
    //     printf("&rhs: %p\n",  p_rhs);
    //     if (this == p_rhs)
    //     {
    //         std::cout << "4: this == &rhs for object and interface, UNEXPECTED (because of RTTI?), now check 'const void *' version" << std::endl;
    //         if (static_cast<const void *>(this) == static_cast<const void *>(p_rhs))
    //         {
    //             std::cout << "static_cast<const void *>(this) == static_cast<const void *>(p_rhs), WEIRD" << std::endl;
    //         }
    //         else
    //         {
    //             std::cout << "static_cast<const void *>(this) == static_cast<const void *>(p_rhs), it makes sense" << std::endl;
    //         }
    //         return true;
    //     }
    //     return false;
    // }

};

/*
this: 000000232798FD78
&rhs: 000000232798FD78
this == &rhs for both objects, as expected
this: 000000232798FD78
&rhs: 000000232798FD90
this == &rhs for object and interface, UNEXPECTED (because of RTTI?), now check 'const void *' version
static_cast<const void *>(this) == static_cast<const void *>(p_rhs), it makes sense
this: 000000232798FD78
&rhs: 000000232798FD90
this == &rhs for object and interface, UNEXPECTED (because of RTTI?), now check 'const void *' version
static_cast<const void *>(this) == static_cast<const void *>(p_rhs), it makes sense
this: 000000232798FD78
rhs: 000000232798FD90
this == rhs for object and interface, UNEXPECTED (because of RTTI?), now check 'const void *' version
static_cast<const void *>(this) == static_cast<const void *>(rhs), it makes sense
//*/

void _ASSERT_VOID(bool flag) {
    std::cout << "flag: " <<  flag << std::endl;
}

void SelfCheckInEqualityOperatorTest()
{
    Operator op;
    _ASSERT_VOID(op == op && op.equal_op(op));

    // base class point to derived class, 
	// BaseObject *bObj = &op;
	// _ASSERT_VOID(op.equal_op(*bObj));

	// 期望的是，op 地址和 inter 地址不一样，因为一个是基类，一个是派生类，按理说两个指针不是同一个东西，但是我们看到了，实际上两个地址一样
    IInterface *inter = &op;
    _ASSERT_VOID(&op == inter);

    _ASSERT_VOID(op.equal_op(*inter));
    _ASSERT_VOID(op.equal_op_p(inter));
}


#endif