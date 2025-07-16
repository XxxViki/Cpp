#include <iostream>
#include <string>
using namespace std;

//父类，基类
class Base {
public:
   virtual void print() {    //虚函数，允许子类重写
        cout << "父类::print()" << endl;
    }

    // 构造函数
    Base():x(0),y(0) {  //初始化成员变量
        cout << "父类构造函数" << endl;    
    }

    // 析构函数
    virtual ~Base() {  //父类析构函数需要加virtual关键字，确保子类析构函数被调用
        cout << "父类析构函数~Base()" << endl;
    }

    virtual void f() = 0; //纯虚函数，子类必须实现函数体，不能实例化

public: 
    int x;
    int getY() const { return y; }
protected:           //可以通过get方法访问，但不能在类外直接访问
    int y = 20;
    
    void Test() {
        cout << "父类的打印Test()受保护的成员函数" << endl;
    }

private:            //没有访问权限，只能在类内部访问
    int z;
    
};

class Base2 {
public:
   virtual void print() {
        cout << "父类::print()" << endl;
    }

    // 构造函数
    Base2():x(0),y(0) {
        cout << "父类构造函数" << endl;    
    }

    // 析构函数
     ~Base2() {
        cout << "父类析构函数~Base2()" << endl;
    }

public: 
    int x;
    int getY() const { return y; }

protected:           //可以通过get方法访问，但不能在类外直接访问
    int y = 20;
    
    void Test() {
        cout << "父类的打印Test()受保护的成员函数" << endl;
    }

private:            //没有访问权限，只能在类内部访问
    int z;
    
};

// 派生类，继承自Base类
class Derived : 
        public Base//,  // 单继承，继承自Base
     //   public Base2  // 多重继承，继承自Base和Base2,逗号隔开，会继承所有父类的成员变量和函数（有的不能访问）
{
public:
    void print() {
        cout << "子类::print()" << endl;
        //printf("x = %d, y = %d\n", x, y);  //y是受保护成员，可以访问,但不能直接在类外访问
        // printf("z = %d\n", z);       // z是父类的私有成员，不能访问，不被继承
    }
    void Test() {
        // Base::Test(); // 调用父类的Test()函数
        cout << "子类的的打印Test()成员函数，重写了父类的Test()函数" << endl;
    }

    Derived() {
        cout << "子类构造函数" << endl;
    }

    ~Derived() {    
        cout << "子类析构函数~Derived()" << endl;    //先构造父类，再构造子类，先析构子类，再析构父类
    }

    
    void f() { cout << "Base2::f()" << endl; } //实现虚函数

};

int main() {
    //Derived d;   //有继承的关系，默认会调用父类和子类的构造函数

/*
    d.x = 10;
    // d.y = 20;
    // d.z = 30; // 错误：私有成员不能在类外访问
    cout << "Base.y = " << d.getY() << endl; // 受保护成员可以访问
    //d.print();
    d.Test(); // 子类重写父类的Test()函数,重写了父类的Test()函数
    // Base类的成员变量
    // b.x = 10; // 公有成员可以访问
    // b.y = 20; // 错误：受保护成员不能在类外访问
    // b.z = 30; // 错误：私有成员不能在类外访问
    
    // Derived类的成员变量
    // d.x = 30; // 公有成员可以访问
    // d.y = 40; // 受保护成员可以在派生类中访问
    // d.z = 50; // 错误：私有成员不能在类外访问
*/
    //虚函数
    Base *p = new Derived();  // 父类指针指向子类对象，但是会产生执行期间的多态性问题，父类需要加virtual关键字
  //  p->print(); // 指向子类，实际是想调用子类的print()函数
    p->f(); // 指向子类，实际是想调用子类的f()函数

  //  delete p;  // 删除指针，父类不加virtual关键字，会导致子类无法析构，因为子类析构函数先于父类析构函数被调用
 

    return 0;
}