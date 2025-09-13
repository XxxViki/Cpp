#include <iostream>
#include <mutex>

class Singleton {
public:
    // 获取单例实例的静态方法
    static Singleton& getInstance() {
        static Singleton instance; // 静态局部变量，保证只创建一次
        return instance;
    }

    // 删除拷贝构造函数和赋值操作符，防止复制实例
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    void showMessage() {
        std::cout << "Hello from Singleton!" << std::endl;
    }

private:
    // 私有构造函数，防止外部实例化
    Singleton() {
        std::cout << "Singleton instance created." << std::endl;
    }
};

int main() {
    // 获取单例实例并调用方法
    Singleton& instance = Singleton::getInstance();
    instance.showMessage();

    return 0;
}