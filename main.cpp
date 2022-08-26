#include "ClassicalVisitor.hpp"
#include "MetaVisitor.hpp"

using namespace std;

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
    Sphere sphere;

    JMetaVisitor::MetaVisitor meta_visitor;
    // meta_visitor.PushElement(&tri, &sphere);

    // auto tri_behavior = [](Triangle* elem) { cout << "elem behavior : " << "draw " << elem->name << endl; };
    // auto sphere_behavior = [](Sphere* elem) { cout << "elem behavior : " << "draw " << elem->name << endl; };
    auto tri_behavior = []() { cout << "elem behavior : " << "draw 1"<< endl; };
    auto sphere_behavior = []() { cout << "elem behavior : " << "draw 2" << endl; };
    meta_visitor.RegisterBehavior(tri_behavior, tri_behavior);

    // meta_visitor.execute()

    return 0;
}