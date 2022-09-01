#include "ClassicalVisitor.hpp"
#include "MetaVisitor.hpp"
#include "VTable.hpp"

using namespace std;
using namespace Jason;

struct IShape { virtual ~IShape() = default; };

struct Triangle : IShape { string name = "Triangle"; };
struct Sphere : IShape { string name = "Sphere"; };

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
    Triangle tri2;
    Sphere sphere1;
    Sphere sphere2;
    IShape ishape;

    MetaVisitor meta_visitor;
    auto triangle_behavior = [](Triangle* elem) -> void { cout << "elem is : " << elem->name << endl; };
    auto sphere_behavior = [](Sphere* elem) -> void { cout << "elem is : " << elem->name << endl; };
    meta_visitor.RegisterBehaviors(triangle_behavior, sphere_behavior);

    meta_visitor.Visit(&tri1);
    meta_visitor.Visit(&sphere1);

    return 0;
}