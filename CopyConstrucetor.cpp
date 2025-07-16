#include <iostream>
#include <string>

using namespace std;

class CopyConstructor {
public: 
    CopyConstructor(string str) {
        cout << "Copy constructor called" << endl;  
        this->str = str;
        }
        CopyConstructor(const CopyConstructor& obj) {
        cout << "Copy constructor called" << endl;  
        this->str = obj.str;
        }
private:
    string str;
};

int main() {
    CopyConstructor obj1("Hello");
    CopyConstructor obj2(obj1);
    return 0;
    }