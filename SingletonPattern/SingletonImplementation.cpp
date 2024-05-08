#include <iostream>
#include <string>
using namespace  std;
class Singleton 
{
    private:
        static Singleton* instance;
        string data;
        Singleton(const string& value) : data(value) {}
        Singleton(const Singleton&) = delete;
        Singleton& operator = (const Singleton&) = delete;
    public: 
        static  Singleton* getInstance(const string& value)
        {
            if(instance == nullptr)
            {
                instance = new Singleton(value);
            }
            return instance;
        }
        // Function display data
        void showData() const {
            cout << "The Data is: " << data<< endl;
        }


};
// Singleton* Singleton::instance = nullptr;
int main()
{
    Singleton* s1 = Singleton::getInstance("Singleton data");
    s1->showData();
    Singleton* s2 =Singleton::getInstance("Another Data");
    s2->showData();
}