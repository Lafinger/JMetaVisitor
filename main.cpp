#include "ClassicalVisitor.hpp"
#include "MetaVisitor.hpp"
#include "VTable.hpp"

using namespace std;
using namespace Jason;

struct IShape { virtual ~IShape() = default; };

struct Triangle : IShape { string name = "Triangle"; int id = 0; };
struct Sphere : IShape { string name = "Sphere"; float f = 1.2; };



int main()
{
    // JClassicalVisitor
    cout << "---------------- Test JClassicalVisitor -----------------" << endl;
    JClassicalVisitor::Triangle triangle;
    JClassicalVisitor::Polygon polygon;
    JClassicalVisitor::Cat cat;
    JClassicalVisitor::Dog dog;
    JClassicalVisitor::Draw draw;
    JClassicalVisitor::Serialize serialize;
    triangle.Accept(&draw);
    polygon.Accept(&draw);
    triangle.Accept(&serialize);
    polygon.Accept(&serialize);
    cat.Accept(&serialize);
    dog.Accept(&serialize);

    // JMetaVisitor
    cout << "---------------- Test MetaVisitor -----------------" << endl;
    Triangle tri1;
    Sphere sphere1;

    MetaVisitor meta_visitor;
    auto NR_triangle_behavior = [](Triangle* elem) -> decltype(auto) { cout << "elem id is : " << elem->id << endl; };
    auto NR_sphere_behavior = [](Sphere* elem) -> decltype(auto) { cout << "elem id is : " << elem->f << endl; };
    auto R_triangle_behavior = [](Triangle* elem) -> decltype(auto) { return elem->id; };
    auto R_sphere_behavior = [](Sphere* elem) -> decltype(auto) { return elem->f; };
    meta_visitor.RegisterBehaviors(R_triangle_behavior, R_sphere_behavior);

    void* ret1 = nullptr;
    void* ret2 = nullptr;
    meta_visitor.Visit(&tri1, ret1);
    meta_visitor.Visit(&sphere1, ret2);

    // Todo : Convert type of function's return automatically
    cout << *(int*)ret1 << endl;
    cout << *(float*)ret2 << endl;

    // fix memory leak
    if (ret1) 
        delete (int*)ret1;
    if (ret2) 
        delete (float*)ret2;


    return 0;
}