
# 每日问题

# 引用相关 （20200312）

Q: 引用是变量的别名，指针存放的是变量的地址,引用直接访问到变量，指针间接访问到变量，指针存储变量的地址很好理解，请问引用这种可以直接访问变量的底层逻辑是怎么实现的？

A： 所以说这些概念真的误导人，你这段话哪里看来的。。。引用本质上就是指针，它访问的时候跟指针一模一样就是用的地址，引用和指针都是通过地址直接访问到变量。
    用唯一的特殊性是它没有办法声明为空，字面上给人感觉总是指向一个存在的东西，但是实际上你也可以把一个空指针解引用赋给一个引用。另外const引用这个常用套路你也知道了，
    所以引用本质上是个语法糖，没有任何新鲜的，增加可读性，可维护性而已，没有它，日子一样过。当然，等到了右值引用就是另一个世界了，那个太复杂了。

# 线程安全 (20200313)

Q:  类似 br_tensorflow 中 BrKernelUtil 类，仅仅是一些接口, 这些接口的数据是外部 class 传入的；针对这种接口类，怎么保证线程安全；我有几个思路： 
    1）这种接口类本身就不应该存在，外部 class 的数据，以及对于这些数据的修改，都应该成为该 class 自身的成员函数，并且做好线程安全的控制； 
    2）另一个思路是, 针对 BrKernelUtil 的接口做线程安全的操作，对传入的数据加锁； 
    3）还有一个思路就是， 针对存在多线程，调用 BrKernelUtil 类中的接口的时候，直接对接口加锁， 比如 直接对 ReorderD2D() ， 加锁； 
    
问题是： 上述思路，是不是第一个更正确点？ 后面两种有点挫。 另外我们在设计一个纯接口的类的时候，怎么注意做到线程安全？

A: 通常是套路1，然后这个类里面的这些函数本质上是全局函数，就是一系列线程安全函数的组合，但是那样的话还是会断片，因为一套组合拳打下来，中间可能被打断。
    所以你原先的思路，单例，然后进入这堆函数的时候加锁就显得合理了，一套组合拳只要加一次锁，但是带来的困惑是，所有拥有数据的类的成员函数在别处，被别的线程调用时，
    如果类本身没有锁，还是有线程问题，那么又回到了套路1，所以感觉最终还是套路1胜出。
    
    加锁永远是对逻辑加锁，而这些逻辑必然操作数据，因为只有数据才有竞争，数据又是归一些类拥有，所以套路1就显得合理了。


# marco and #define （20200314)

Q:《Effective C++》中建议，形似函数的宏，最好改用 inline 函数替换 #define. 我们都知道， inline 和 #define 都比普通函数更高效；
    我发现在我们的代码仓中很多都是 #define 形式的函数，而不是 inline ！

    问题是：inline 和 #define 这两种形式，我们在开发过程中，要确定在什么场景下使用更合理？

A: 只要能写成函数，必然inline，效率和宏一样，还多了各种check，真实debug的时候也是会有堆栈，可能是IDE帮忙产生的。没法写成函数，或者有些是代码片段，
    不得已才用宏。宏更灵活，不拘泥，所以使用场景也很多，也可以大幅减少代码重复。 

```shell
附说明：
1.宏（#define）和内联函数（inline）的理解以及区别：

宏
缺点：
    1.宏没有类型检测，不安全
    2.宏是在预处理时进行简单文本替换，并不是简单的参数传递（很难处理一些特定情况。例如：Add(z++)）
    3.使代码变长
    4.宏不能进行调试
    5.当预处理搜索#define定义的符号时，字符串常量并不被搜索

优点：
    1.加快了代码的运行效率
    2.让代码变得更加的通用

内联函数
类中的成员函数是默认的内联函数
内联函数内不准许有循环语句和开关语句
内联函数的定义必须出现在第一次调用内联函数之前


缺点：
    代码变长，占用更多内存

优点：
    1.有类型检测，更加的安全
    2.内联函数是在程序运行时展开，而且是进行的是参数传递
    3.编译器可以检测定义的内联函数是否满足要求，如果不满足就会当作普通函数调用（内联函数不能递归，内联函数不能太大）

对比
相同点：
两者都是可以加快程序运行效率，使代码变得更加通用

不同点：
    1.内联函数的调用是传参，宏定义只是简单的文本替换
    2.内联函数可以在程序运行时调用，宏定义是在程序编译进行
    3.内联函数有类型检测更加的安全，宏定义没有类型检测
    4.内联函数在运行时可调式，宏定义不可以
    5.内联函数可以访问类的成员变量，宏不可以
    6.类中的成员函数是默认的内联函数
```

# Singleton (20200315)

Q: 在上次我写了 singleton 之后（缺少一次 nullptr 判断）， 我今天再本地新写了一个简单的测试例子，就当前这种例子而言，这个 singleton 还有什么优化的空间吗？或者说目前还有没有缺点？
```c++
class Singleton {
private:
	Singleton() {
		std::cout << "Singleton: constructor called" << std::endl;
	}
	~Singleton() {
		std::cout << "Singleton: destructor called" << std::endl;
	}
	Singleton(Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:
	static Singleton& GetInstance() {
		static Singleton instance_;
		return instance_;
	}
};
```
A: 打印输出结尾用endl。private函数写下面。这两个delete不对，想想哪里不对，争取换个写法，继承自 noncopyable 类。instance函数是对的，变量名字不好。
    这个测试没有意义，要多线程。查一下singleton最初的来源。


# About delete (20200316)
Q:  从昨天写 singleton ， 我使用了 'xxx() = delete;'， 我今天测试了两种情况：delete 构造函数'xx() = delete;' 和直接将构造函数放作为 private  成员，
    都能达到阻止调用构造函数的目的， 但是这两种报错内容不同， 请问两种方式有没有区别？建议用哪一种？

```c++
// 1
class DeleteTest {
public:
	DeleteTest() {}

    DeleteTest(DeleteTest&) = delete;
    DeleteTest& operator=(const DeleteTest&) = delete;
};

// 2
class DeleteTest2 {
public:
	DeleteTest2() {}

private:
    DeleteTest2(DeleteTest2&) {}
    DeleteTest2& operator=(const DeleteTest2&) {}
};

void KeywordDeleteTest() {
	DeleteTest t1; 
	DeleteTest t2 = t1; // error C2280: “DeleteTest::DeleteTest(DeleteTest &)”: 尝试引用已删除的函数

	DeleteTest2 tt1;
	DeleteTest2 tt2 = tt1; // error C2248: “DeleteTest2::DeleteTest2”: 无法访问 private 成员(在“DeleteTest2”类中声明)
}
```

A: 第一种是现代，第二种是老派额写法。没区别，效果一样；个人喜欢第二种。

# Singleton 2 (20200317) 

Q: 今天我想问一个非技术细节的问题，就是我平时发现实现一种功能，其实代码有多种写法， 就像这两天正在深究的 Singleton ，网上各种帖子有个不同的写法；我的问题就是，像这种固定模式的代码，有没有那个你学习过的书籍或者开源项目，比较好的展示了各种设计模式的高效写法，让人一看这就是优秀代码！可以推荐我去学习学习， 多读读 standard library 代码有必要吗？ 

A： 比如singleton，你可以用DCLP写两个版本，然后它还有篇论文，又写两个，boost源码里抄一个，现代的写法最后一个。多读boost源码。

# Singleton 3 DCLP (20230320) 

Q: 在继续了解 Singleton 之后，在一些帖子中，我了解到，诸如如下代码，也并非线程安全，原因是 inst = new Singleton(); 这条语句存在三条操作指令：
1) 分配 Singleton 对象的内存；
2) 构造一个 Singleton 对象；
3) 让 inst 指向这块被分配的内存; 
线程不安全的原因是，第2、3两步骤顺序不确定，存在 inst 指针已经被赋值，但是对象还没有被构造。这时候如果出现另一个线程调用 GetInstance() , 此时第一个 inst == nullptr 结果为 false; 所以返回得 inst 是一个还未构造得对象，程序大概率 crash； 我的问题是： 1）这种 CPU 调用乱序是什么原因造成的？ 2）C++11 规定了新的内存模型，保证了执行上述3个步骤的时候不会发生线程切换，相当这个初始化过程是“原子性”的的操作，这里 C++11 之后使用了什么新的内存模型，可以避免 CPU 调用乱序问题呢？ 

```c++ 
Singleton* Singleton::GetInstance() { 
    if (inst == nullptr) { 
        std::lock_guard<std::mutex> guard(lock_); 
        if (inst == nullptr) 
            inst = new Singleton(); 
    } 
    return inst; 
} 

```
A: 
- CPU在OS上执行的时候，OS很自私，它只管自己爽，会有各种优化策略，使得乱序，所以任意两行代码或者两行汇编都会被颠倒，这就是我们用各种技术保证memory order的原因，一般LA和SR，你自行查下这两个简写。
- 这个代码没有到CPU级别就必须加锁，你都好几行代码了，当然没有原子性。3. 这个实现我很不满意，暴露了很多问题，比如写法的细节，lock guard必须要模板参数吗？一定要出现new吗？谁去delete呢，太不智能了吧，继续改，继续写。
- 11的singleton跟内存模型没有关系，是什么来着？你随便找个repo搜一下GetInstance()就可以找到答案。
- DCLP的论文


# Noncopyable (20230321)
Q: 我把昨天的例子，重新写一下： 增加了智能指针、 使用了 Noncopyable； 问题是： constexpr NonCopyable() = default; 这里写成 “ NonCopyable() = default; ” 发现编译执行也没问题；这里 constexpr 我查到含义是（编译阶段就能够确定其值的常量）， 但是在这个类里面，这么使用的好处是什么呢？ 还有一个更正一下， 昨天我问 lock_guard 不需要参数是c++14 才有的。 今天我编译发现，不用参数 c++14编译会报错；c++17 是不需要参数的。 
// g++ singleton_with_shared_ptr.cc --std=c++14 -o main // Error 
// singleton_with_shared_ptr.cc:32:21: error: missing template arguments before ‘_’ // g++ singleton_with_shared_ptr.cc --std=c++17 -o main // OK



# (20230322) 
```c++ 
std::unique_ptr<Singleton> Singleton::GetInstance() { if (!inst_) { std::lock_guard _(lock_); if (!inst_) { inst_ = std::make_unique<Singleton>(); } } return inst_; } 

``` 
// 现象 
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = Singleton; _Dp = std::default_delete<Singleton>]’ return inst_; 

// 原因 
这里因为我继承了 NonCopyable ，所以直接 return 会编译报错； 如果我不继承 NonCopyable， 虽然可以编译通过，但是就违反了一开始 NonCopyable 的原则； ```c++ std::unique_ptr<Singleton>&& Singleton::GetInstance() { if (!inst_) { std::lock_guard _(lock_); if (!inst_) { inst_ = std::make_unique<Singleton>(); } } return std::move(inst_); } ``` 

// 现象 
Singleton 访问 inst_ 已经为 nullptr； 

// 原因 
move 之后， Singleton 中的静态变量 [static std::unique_ptr<Singleton> inst_;] 已经被析构了； 问题： 如果返回 inst_.get() 其实也不合理，会将直接将罗指针暴露给用户。这里列出来的三种返回值方式，都不靠谱； 所以我认为使用 unique_ptr 来实现 Singleton 是不合适的，不知道我这个想法对吗？


# const (20230323)
Q: <<Effective C++>> (55) 中，有句话：“bitwise constness 正是 C++ 对常量性的定义，因此 const 成员函数不可以更改对象内 non-static 成员变量”。 这句话反过来理解，就是 const 可以修改 static 成员变量，我写了个测试，确实如此。 我的问题是， const 的常量性让人理解为不可以被修改， 但是 const 成员函数，为什么设计一个功能要去修改 static 成员变量呢？这种设计的出发点是什么？为了解决什么问题呢？


A: const 属性本质上限制的是 this, type: const Obj * const this, 访问 static func or data 的时候不用 this，所以没有任何限制。逻辑上也通，static data == global data, any func can update it.


# const function(20230324)
Q: const 修饰成员函数，表示这个函数不修改对象内部某些变量的状态；而 mutable 又允许 const 成员函数，去修改这些内部变量， 这两者之前有啥关系？这个 mutable 主要在什么场景使用？

A: TODO

# mutable （20230327）
Q: 上一个问题， mutable 和 const 我已经搞明白了， 今天我看到 suinfer 中有一段代码， 有点疑惑，这个 mutable 和 const 共同修饰一个变量的必要性是什么？

``` c++
mutable const char* p;
```

A: const 修饰指针指向的内容， 加上 mutable 之后，就是说， const 成员函数可以修改指针的指向；

# NVR (20230328)
Q: C++ 编译器对于以值传递方式返回的 class object， 都会通过优化程序，加上额外的 reference 参数， 就是 NRV 优化操作。一般的，我理解的以值传递方式返回，应该也不存在什么问题；这里进行 NRV 优化除了减少 copy，还有其他的设计目标吗？ 另外编译器自动进行 NRV 的前提条件是什么？这种优化选项是编程人员可控的吗？

A:是 RVO 和 NRVO , 就是为了减少拷贝，我们不可控，编译器生成的代码。

# noexcept （20230329）
Q:  关于 noexcept 关键字， 我看建议在以下几个场景使用：move constructor、move assignment、destructor （编译器默认会加）。我写了一个测试 vector 需要扩容的例子， 确实发现了效率更高，会主动调用 move constructor; 我的问题是：如果我在实际应用中，声明的 noexcept 函数，确实抛出异常，然后被终止了。在这种情况下，如果我的代码调用链路很长，系统岂不是会过早的就被终止！所以当我们开发过程中，是否需要对很底层的接口声明为 noexcept 呢？ 除了以上三种情况，还有什么需要注意的吗?

A: 众说纷纭，专家组也没有说清楚，建议看看 suinfer repo 中 suinfer_common.h 几个函数的写法，算是总结；


# shared_ptr （20230330）

```c++
#include <iostream>

class Person { 
public: 
    Person()  { id_ = 0; } 
    Person(int id) : id_(id) {} 
    void Print() { std::cout << "id: " << id_ << std::endl; } 
private: int id_; 

}; 

class shared_count { 
public: 
    shared_count() : count_(1) {} 
    void count_add() { ++this->count_; } 
    int64_t count_reduce() { return --this->count_; } 
    int64_t get_count() { return this->count_; } 
    
private: 
    int64_t count_; 

}; 

template<typename T>
class shared_ptr { 
public: 
    explicit shared_ptr(T* ptr = nullptr) noexcept : ptr_(ptr) { 
        std::cout << "constructor..." << std::endl; 
        if (ptr) { shared_count_ = new shared_count(); 
        } 
    } 
    
    ~shared_ptr() { 
        std::cout << "destructor..." << std::endl; 
        if (ptr_ && !shared_count_->count_reduce()) { 
            delete ptr_; delete shared_count_; 
        } 
    } 
    
    T& operator*() const noexcept { return *ptr_; } 
    T* operator->() const noexcept { return ptr_; } 
    T* get() const noexcept { return ptr_; } 
    
    shared_ptr(const shared_ptr<T>& other) noexcept { 
        std::cout << "copy..." << std::endl; 
        ptr_ = other.ptr_; 
        if (ptr_) { 
            other.shared_count_->count_add(); 
            shared_count_ = other.shared_count_; 
        } 
    } 
    
    // move 
    shared_ptr(const shared_ptr<T>&& other) noexcept { 
        std::cout << "move..." << std::endl; 
        ptr_ = other.ptr_; 
        if (ptr_) { 
            shared_count_ = other.shared_count_; 
            other.ptr_ = nullptr; 
            other.shared_count_ = nullptr; 
        } 
    } 
    
    // assign 
    shared_ptr<T>& operator=(const shared_ptr<T>& other) noexcept { 
        std::cout << "operator=: " << std::endl; 
        if (this == &other) { 
            return *this; 
        } 
        
        if (!other.ptr_) { 
            if (this->ptr_ != nullptr) 
            { 
                // 当前对象(被赋值对象)如果不为空，且计数为 0，需要先 delete 
                if (this->shared_count_->count_reduce() == 0) { 
                    delete this->ptr_; 
                    delete this->shared_count_; 
                    this->ptr_ = nullptr; 
                    this->shared_count_ = nullptr; 
                } 
            } 
            this->ptr_ = other.ptr_; this->shared_count_ = other.shared_count_; 
        } else { 
            if (this->ptr_ != nullptr) { 
                if (this->shared_count_->count_reduce() == 0) { 
                    delete this->ptr_; delete this->shared_count_; this->ptr_ = nullptr; this->shared_count_ = nullptr; 
                } 
            } this->ptr_ = other.ptr_; this->shared_count_ = other.shared_count_; 
            
            // 赋值后, 本类计数器需要+1 
            this->shared_count_->count_add(); 
        }
        
        return *this; 
    } 
    
    int64_t use_count() const noexcept { if (ptr_) { return shared_count_->get_count(); } else { return 0; } } 
    
private: 
    T* ptr_; 
    shared_count* shared_count_; 
}; 

int main() { 
    shared_ptr<Person> ptr1(new Person()); 
    shared_ptr<Person> ptr2(ptr1); 
    shared_ptr<Person> ptr3; 
    ptr3 = ptr2; 
    
    std::cout << "use_cout: " << ptr1.use_count() << std::endl; 
    std::cout << "use_cout: " << ptr2.use_count() << std::endl; 
    std::cout << "use_cout: " << ptr3.use_count() << std::endl; 
    return 0; 
}
```

# 继承 基类中存在析构函数，如何避免错误 delete （20230403）

```c++
class MyString : public std::string {
private:
    class xxx;
};

{
    MyString *my_str = new MyString();
    std::string str = my_str;
    delete str;
}

```
如上情况，因为 std::string 包 non-virtual 的析构函数，delete str 会造 MyString 部分成员泄露；
诸如上述情况， 我们在开发过程中，如果想要继承系统或者其他人写的 class， 如果对方的 class 存在 non-virtual 析构函数；
我们怎么避免上述情况的发生？C++ 有没有‘禁止继承’这种形式的机制？

Q: final 可以阻止类继承，可以阻止虚函数重载，按时一个类的析构函数如果是 non-virtual , final 就失去了作用。是不是可以说，如果一个类要作为基类，一定要把析构函数
作为 virtual 函数？

A:
yes

# shared_ptr 指向多个基础类指针

```c++
char* chr = new chr;
std::shared_ptr<char> p1(chr);
std::shared_ptr<char> p2(chr);

// result 
// free(): double free detected in tcache 2
// Aborted (core dumped)
```
Q: why?
A: (void)p2.release(), 事实上，不要写出这样的代码


#  std::atomic 为什么比 mutex 高效

(20230410) 
```c++ 
// case 1 
class Obj{ public: Counter() { std::mutex mtx; std::lock_guard _(mtx); ++count; } private: int count; }; 
// case 2 
class Obj{ public: Counter() { ++count; } private: std::atomic<int> count; }; 
``` 
Q：
针对 std::atomic 和 std::mutex 我做了测试, 我发现 std::atomic 效率更高；这里我有两个问题： 
1. 为什么 std::atomic<int> count; 效率会更高，他的原理是什么？ 
2. std::atomic 除了能对基础类型诸如 int 进行原子操作外， C++ 有没有引申出来对复杂变量的原子操作, 例如 std::atomic<Object> Obj ?

A: 
简单理解， atomic 是在 cpu 指令级别上实现锁，所以必不可少的内存栅栏带来流水线随时外，几乎可以认为没有什么额外开销；而 mutex 光是在内核中睡眠/唤醒
一下，就至少是微秒级别的时间开销，更别说额外的调用和封装、判断了；


# final c++11 singleton
(20230411) 
```c++
#include <iostream>
#include <vector>
#include <thread>

#define DISALLOW_COPY_AND_ASSIGN(ClassName) \
  ClassName(const ClassName&) = delete;     \
  void operator=(const ClassName&) = delete

class MyEngine {
  DISALLOW_COPY_AND_ASSIGN(MyEngine);
public:
  MyEngine() = default;
  ~MyEngine(){};
  static MyEngine& Instance() {
    static MyEngine engine;
    return engine;
  }
  void Print() { std::cout << "id_: " << id_ << std::endl; }
private:
  const std::string id_;
};

void Func() {
  MyEngine& ins = MyEngine::Instance();
  std::cout << "ins: " << &ins << std::endl;
}
int main(int argc, char const* argv[]) {
  const int loop_number = 100;
  std::vector<std::thread> vec_td;
  for (size_t i = 0; i < loop_number; ++i) {
    vec_td.push_back(std::thread(Func));
  }
  for (size_t ix = 0; ix < loop_number; ++ix) {
    vec_td[ix].join();
  }
  return 0;
}
```


# DCLP with atomic

(20230412)

```c++
#include <mutex>
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

class Singleton {
public:
  Singleton() {}
  static Singleton* GetInstance() {
    // 当前线程中读或写不能被重排到此加载前
    Singleton* internal = pInstance_.load(std::memory_order_acquire);
    if (!internal) {
      std::lock_guard<std::mutex> _(mutex_);
      // 没有同步或顺序制约，仅对此操作要求原子性
      internal = pInstance_.load(std::memory_order_relaxed);
      if (!internal) {
        internal = new Singleton;
        // 当前线程中的读或写不能被重排到此存储后
        pInstance_.store(internal, std::memory_order_release);
      }
    }
    return pInstance_;
  }
private:
  Singleton(Singleton&) {}
  Singleton& operator=(const Singleton&) {}
  static std::atomic<Singleton*> pInstance_;
  static std::mutex mutex_;
};

std::atomic<Singleton*> Singleton::pInstance_(nullptr);
std::mutex Singleton::mutex_;
void Func() {
  Singleton* ins = Singleton::GetInstance();
  std::cout << "instance:  " << &ins << std::endl;
}

int main(int argc, char const* argv[]) {
  const int loop_number = 1000;
  std::vector<std::thread> vec_td;
  for (size_t i = 0; i < loop_number; ++i) {
    vec_td.push_back(std::thread(Func));
  }
  for (size_t ix = 0; ix < loop_number; ++ix) {
    vec_td[ix].join();
  }
  return 0;
}
// g++ dclp_with_atomic.cc -std=c++11 -lpthread -o main
```

A：
返回引用，不要指针，需要释放，static inline 就不用类外再定义了
测试用例: reserve, emplace back, modern for loop

改后：

```c++
# version 2
class Singleton {
public:
  Singleton() {}
  static Singleton* GetInstance() {
    // 当前线程中读或写不能被重排到此加载前
    Singleton* internal = pInstance_.load(std::memory_order_acquire);
    if (!internal) {
      std::lock_guard<std::mutex> _(mutex_);
      // 没有同步或顺序制约，仅对此操作要求原子性
      internal = pInstance_.load(std::memory_order_relaxed);
      if (!internal) {
        internal = new Singleton;
        // 当前线程中的读或写不能被重排到此存储后
        pInstance_.store(internal, std::memory_order_release);
      }
    }
    return pInstance_;
  }
private:
  Singleton(Singleton&) {}
  Singleton& operator=(const Singleton&) {}
  static inline std::atomic<Singleton*> pInstance_;
  static std::mutex mutex_;
};
std::mutex Singleton::mutex_;
void Func() {
  Singleton* ins = Singleton::GetInstance();
  std::cout << "instance:  " << &ins << std::endl;
}
int main(int argc, char const* argv[]) {
  const int loop_number = 1000;
  std::vector<std::thread> vec_td;
  vec_td.reserve(loop_number);
  for (size_t i = 0; i < loop_number; ++i) {
    vec_td.emplace_back(std::thread(Func));
  }
  for (auto& td : vec_td) {
    td.join();
  }
  return 0;
}
```

# T&&
(20230413)

Q: 
另外今天看书，遇到一个问题，不太理解应用在哪里，关于 Universal reference; 
```c++ 
void Function(Object&& obj);    // Rvalue ref 
Object&& obj = Object();        // Rvalue ref 
auto&& obj2 = obj;              // Universal ref 
``` 

一开始很迷惑，同样的 T&&， 为啥不一样，查阅资料之后大概明白了 函数模板参数为 T&&, 并且 T 需要推导得出，则是 Universal ref; 如果对象被声明为 auto&&，则是 Universal ref; 如果声明的形式不是标准 type&&, 或者类型不需要推导， 则 type&&是 Rvalue ref; 我的问题是： 虽然明白了怎么判断 Universal ref 和 Rvalue ref, 但是 Universal ref 的应用场景是什么，为什么需要这么一个设计？

A：
用在 STL 源码内部，为了完美转发， 可以参考 vector 源码看看；


(20230419)


```c++
void FuncA(Object boj);
void FuncB(const Object& obj);
```
Q: 为什么以 pass-by-value 的形式传递参数，会调用拷贝构造函数，而以 pass-by-reference 的形式传递参数却不会？这个背后的原理是什么？我在哪里能查到实现的源码呢？
  

# const ref 做参数能避免函数参数切个问题
（20230504）

```c++
class Base {};
class Derived {};

// by value
void Func(Base b);

// by reference
void FuncB(const Base& b);
```
Q：
以 pass by value 方式传递函数参数，会引起对象切割问题（slicing）：derived class 以 by value 传递，如果他被视为一个 base class，那么本身 derived class 独有的方法就会被切割掉。书中说以 by reference const 方式传递会避免这个问题？原因是什么呢？ 如果上述 FuncB(), 我传递一个 derived 的 引用，是不是也会发生切割？

A:
引用就是指针，RTTI 会帮你自动做多态相关的所有事情，比如从这个指针地址进行偏移，直到即将调用的函数对应的 obj 的地址，然后找到虚表地址，从表里面拿到那个 obj 的各个函数地址。其实就是在这个指针相关的所有代码之处，插入了很多转换代码。再给你看个极端的例子。

（20230505）

# 直接在构造时指定初始值
Q:
"通过 default 构造函数构造一个对象然后对它的成员变量赋值" 比 “直接在构造时指定初始值” 效率差；
我理解：前者先调用一次 default 构造函数，然后在调用 copy 进行赋值；后者构造的时候指定初始值，只调用了一次 copy 直接赋值；
我的问题是：我这样理解对不对？另外，前者调用默认的 default 构造函数时候，编译器做了什么事情？为什么后者的构造没有这个多余的操作？

A：
后者初始化时候就同时赋值，那个内存写一次，前者初始化赋随机值，后面再次赋值，写两次。


(20230508)
书中说要尽量写 “异常安全”的代码，但是我在各种帖子中看到说：使用异常，会导致性能降低，同时debug更方便（如果使用了异常，那么追踪后可能获取的是catch throw点，没意义）；
我的问题是：
平时写代码比较好的习惯是什么？尽量都写异常安全的代码（追求强异常安全，还是弱异常安全）？还是有所取舍？

