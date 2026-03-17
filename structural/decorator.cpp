/*
It is a structural design pattern which allows us to add new behavoir to objects dynamically at
runtime without modifying their original structure
 */

// wants to follow open close principle and single responsibilty principle
// debugging is hard

#include <iostream>
using namespace std;

// class PlainPizza
// {
// };

// class CheesePizza : public PlainPizza
// {
// };

// class CheeseOlivePizza : public CheesePizza
// {
// };

// class OlivePizza : public PlainPizza
// {
// };

// so everytime a add a topping the classes increase by 2^N

class Pizza
{
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
    virtual ~Pizza() = default;
};

// Concrete Base
class MargreetaPizza : public Pizza
{
public:
    string getDescription() override
    {
        return "Margreeta Pizza";
    }

    double getCost() override
    {
        return 200.0;
    }
};

// Base Decorator
class PizzaDecorator : public Pizza
{
protected:
    Pizza *pizza;

public:
    PizzaDecorator(Pizza *pizza) : pizza(pizza) {}

    string getDescription() override
    {
        return pizza->getDescription();
    }

    double getCost() override
    {
        return pizza->getCost();
    }
};

// Concrete Decorator
class ExtraCheese : public PizzaDecorator
{
public:
    ExtraCheese(Pizza *pizza) : PizzaDecorator(pizza) {}

    string getDescription() override
    {
        return pizza->getDescription() + " + Extra Cheese";
    }

    double getCost() override
    {
        return pizza->getCost() + 50.0;
    }
};

class Olives : public PizzaDecorator
{
public:
    Olives(Pizza *pizza) : PizzaDecorator(pizza) {}

    string getDescription() override
    {
        return pizza->getDescription() + " + Olives";
    }

    double getCost() override
    {
        return pizza->getCost() + 30.0;
    }
};

int main()
{
    Pizza *pizza = new MargreetaPizza();

    pizza = new ExtraCheese(pizza);
    pizza = new Olives(pizza);

    cout << pizza->getDescription() << endl;
    cout << pizza->getCost() << endl;

    return 0;
}