#include <iostream>
#include <string>

using namespace std;

//生成一个拷贝构造函数的例子
class Person {
public:    
    //构造函数，参数是字符串
    Person(const string& name) : m_name(name) {}  //构造函数初始化成员

    //拷贝构造函数
    //参数是同类的引用，通常是const引用
    Person(const Person& other) : m_name(other.m_name) {} 

    void print() const {
        cout << "Name: " << m_name << endl;
    }

    //传值调用拷贝构造函数的方式
    void copy(Person other) {
        m_name = other.m_name;
        cout << "拷贝构造函数 " << m_name << endl;
        }

    ~Person() {
        cout << "Destructor called for " << m_name << endl;
    }

private:
    string m_name;
};

int main() {
    Person p1("Alice");
    p1.print();

    Person p2(p1); //调用拷贝构造函数,以p1为参数初始化p2
    p2.print();

    Person *p3 = new Person("Bob");  //动态分配内存,隐性调用拷贝构造函数
    p3->print();

    Person p4("Xxx");   
    p4.copy(p1); //调用拷贝构造函数,以p1为参数初始化p4
    p4.copy(*p3); //调用拷贝构造函数,以p3为参数初始化p4,需要取出指针的值，注意函数参数类型，
    p4.print();

    delete p3;
    //动态分配内存的对象需要手动释放
    //否则会造成内存泄漏    

    return 0;
}