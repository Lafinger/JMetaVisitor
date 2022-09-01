#pragma once

#include <string>
#include <iostream>

namespace Jason {

namespace JClassicalVisitor {
    class Triangle;
    class Polygon;
    class Cat;
    class Dog;

    class IVisitor
    {
    public:
        virtual ~IVisitor() = default;
        virtual void Visit(Triangle* triangle) = 0;
        virtual void Visit(Polygon* polygon) = 0;
        virtual void Visit(Cat* cat) = 0;
        virtual void Visit(Dog* dog) = 0;
    };

    class IElement
    {
    public:
        virtual ~IElement() = default;
        virtual void Accept(IVisitor* visitor) = 0;
    };

    class Figure : public IElement {};
    class Triangle : public Figure
    {
    public:
        std::string name{ "Figure" };
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }
    };
    class Polygon : public Figure
    {
    public:
        std::string name{ "Polygon" };
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }
    };

    class Animal : public IElement {};
    class Cat : public Animal
    {
    public:
        std::string name{ "Cat" };
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }
    };
    class Dog : public Animal
    {
    public:
        std::string name{ "Dog" };
        void Accept(IVisitor* visitor) override
        {
            visitor->Visit(this);
        }
    };

    class Draw : public IVisitor
    {
    public:
        ~Draw() {};
        void Visit(Triangle* triangle) override
        {
            std::cout << "Draw : " << triangle->name << std::endl;
        }
        void Visit(Polygon* polygon) override
        {
            std::cout << "Draw : " << polygon->name << std::endl;
        }
        void Visit(Cat* cat) override {}
        void Visit(Dog* dog) override {}
    };

    class Serialize : public IVisitor
    {
    public:
        ~Serialize() {};
        void Visit(Triangle* triangle) override
        {
            std::cout << "Serialize : " << triangle->name << std::endl;
        }
        void Visit(Polygon* polygon) override
        {
            std::cout << "Serialize : " << polygon->name << std::endl;
        }
        void Visit(Cat* cat) override
        {
            std::cout << "Serialize : " << cat->name << std::endl;
        }
        void Visit(Dog* dog) override
        {
            std::cout << "Serialize : " << dog->name << std::endl;
        }
    };
} // JClassicalVisitor
} // Jason


