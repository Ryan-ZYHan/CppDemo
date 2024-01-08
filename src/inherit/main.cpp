/* 测试利用反射，根据字符串创建对应的类 */
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include <iostream>

class Base
{
public:
    virtual void doSomething() = 0;
    virtual ~Base() {}
};

class Factory
{
public:
    using Creator = std::function<std::unique_ptr<Base>()>;

    static std::unique_ptr<Base> createObject(const std::string &className)
    {
        auto g = getRegistry();
        auto it = getRegistry().find(className);
        if (it != getRegistry().end())
        {
            return it->second();
        }
        return nullptr; // 处理未知类名的情况
    }

    template <typename T>
    static bool registerClass(const std::string &className)
    {
        getRegistry()[className] = []() -> std::unique_ptr<Base>
        { return std::make_unique<T>(); };
        return true;
    }

private:
    static std::unordered_map<std::string, Creator> &getRegistry()
    {
        static std::unordered_map<std::string, Creator> registry;
        return registry;
    }
};

class ClassA : public Base
{
public:
    ClassA()
    {
        // Factory::registerClass<ClassA>("ClassA");
    }

    void doSomething() override
    {
        std::cout << "class a" << std::endl;
    }
};

class ClassB : public Base
{
public:
    ClassB()
    {
        // Factory::registerClass<ClassB>("ClassB");
    }

    void doSomething() override
    {
        std::cout << "class b" << std::endl;
    }
};

class ClassC : public Base
{
public:
    ClassC()
    {
        // Factory::registerClass<ClassC>("ClassC");
    }

    void doSomething() override
    {
        std::cout << "class c" << std::endl;
    }
};

bool classAInitializer1 = Factory::registerClass<ClassA>("ClassA");
bool classAInitializer2 = Factory::registerClass<ClassB>("ClassB");
bool classAInitializer3 = Factory::registerClass<ClassC>("ClassC");

int main()
{
    std::unique_ptr<Base> objA = Factory::createObject("ClassA");
    std::unique_ptr<Base> objB = Factory::createObject("ClassB");
    std::unique_ptr<Base> objC = Factory::createObject("ClassC");

    // 检查并使用对象
    if (objA)
    {
        objA->doSomething();
    }

    if (objB)
    {
        objB->doSomething();
    }

    if (objC)
    {
        objC->doSomething();
    }

    return 0;
}
