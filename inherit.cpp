#include <iostream>
#include <string>
using namespace std;

//父类，基类
class Base {
public:
   virtual void print() {
        cout << "父类::print()" << endl;
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
class Derived : public Base {
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

};

int main() {
    Derived d;
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

    //虚函数
    Base *p = new Derived();  // 父类指针指向子类对象，但是会产生执行期间的多态性问题，父类需要加virtual关键字
    p->print(); // 指向子类，实际是想调用子类的print()函数
    
    return 0;
}



