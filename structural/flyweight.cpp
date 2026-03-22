/*
it is a structural design pattern which is used to minimize memory usuage or computational cost
by sharing as much as data as possible with similar objects

think of it as a data reuse pattern,if many objects are similar, store their common data in one
place and share it across objects


intrisic attributes -> these are common and reusable properties
extrinic attributes -> these are context specific and different for each object
*/

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;

class TreeType
{
private:
    string name;
    string color;
    string texture;

public:
    TreeType(string name, string color, string texture)
        : name(name), color(color), texture(texture) {}

    void draw(int x, int y)
    {
        cout << "Drawing " << name << " tree at (" << x << ", " << y << ")\n";
    }
};

class TreeFactory
{
private:
    unordered_map<string, shared_ptr<TreeType>> treeTypes;

public:
    shared_ptr<TreeType> getTreeType(string name, string color, string texture)
    {
        string key = name + "_" + color + "_" + texture;

        if (treeTypes.find(key) == treeTypes.end())
        {
            treeTypes[key] = make_shared<TreeType>(name, color, texture);
        }

        return treeTypes[key];
    }
};

class Tree
{
private:
    int x;
    int y;
    shared_ptr<TreeType> type;

public:
    Tree(int x, int y, shared_ptr<TreeType> type)
        : x(x), y(y), type(type) {}

    void draw()
    {
        type->draw(x, y);
    }
};

class Forest
{
private:
    vector<unique_ptr<Tree>> trees;
    TreeFactory factory;

public:
    void plantTree(int x, int y, string name, string color, string texture)
    {
        auto type = factory.getTreeType(name, color, texture);
        trees.push_back(make_unique<Tree>(x, y, type));
    }

    void draw()
    {
        for (auto &tree : trees)
        {
            tree->draw();
        }
    }
};

int main()
{
    Forest forest;

    forest.plantTree(1, 2, "Oak", "Green", "Rough");
    forest.plantTree(3, 4, "Oak", "Green", "Rough");
    forest.plantTree(5, 6, "Pine", "Dark Green", "Smooth");

    forest.draw();

    return 0;
}