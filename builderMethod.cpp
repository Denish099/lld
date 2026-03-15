#include <iostream>
using namespace std;

class BurgerMeal
{
private:
    string bunType;
    string patty;

    bool hasCheese;
    vector<string> toppings;
    string side;
    string drink;

public:
    class BurgerBuilder
    {
    private:
        string bunType;
        string patty;

        bool hasCheese = false;
        vector<string> toppings;
        string side = "";
        string drink = "";

        friend class BurgerMeal;

    public:
        BurgerBuilder(string bunType, string patty)
            : bunType(bunType), patty(patty) {}

        BurgerBuilder &withCheese(bool hasCheese)
        {
            this->hasCheese = hasCheese;
            return *this;
        }

        BurgerBuilder &withToppings(vector<string> toppings)
        {
            this->toppings = toppings;
            return *this;
        }

        BurgerBuilder &withSide(string side)
        {
            this->side = side;
            return *this;
        }

        BurgerBuilder &withDrink(string drink)
        {
            this->drink = drink;
            return *this;
        }

        BurgerMeal build()
        {
            return BurgerMeal(*this);
        }
    };

    BurgerMeal(const BurgerBuilder &builder)
    {
        bunType = builder.bunType;
        patty = builder.patty;
        hasCheese = builder.hasCheese;
        toppings = builder.toppings;
        side = builder.side;
        drink = builder.drink;
    }
};

int main()
{
    BurgerMeal plainBurger = BurgerMeal::BurgerBuilder("wheat", "veg").build();

    BurgerMeal burgerWithCheese = BurgerMeal::BurgerBuilder("wheat", "veg")
                                      .withCheese(true)
                                      .build();

    vector<string> toppings = {"lettuce", "onion", "jalapeno"};
    BurgerMeal loadedBurger = BurgerMeal::BurgerBuilder("multigrain", "chicken")
                                  .withCheese(true)
                                  .withToppings(toppings)
                                  .withSide("fries")
                                  .withDrink("coke")
                                  .build();

    return 0;
}
