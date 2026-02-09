
#include <iostream>
#include <list>

class Object
{
public:
    virtual ~Object() {};
};

class Line : public Object
{
public:
    virtual void draw() { std::cout << "draw" << std::endl; }
};

void drawObject(Object *obj)
{
    dynamic_cast<Line *>(obj)->draw();
}

int main()
{
    std::list<int *> objects;

    int *l = new int(18);
    objects.push_back(l);

    // search
    for (const auto &obj : objects)
    {
        if (*obj == *l)
        {
            std::cout << "found in objects" << std::endl;
        }
    }

    int *l2 = new int(4);
    for (const auto &obj : objects)
    {
        if (*obj != *l2)
        {
            std::cout << "not found in objects" << std::endl;
        }
    }

    return 0;
}
