#ifndef QUINE_MCCLUSKEY_ITEM_H
#define QUINE_MCCLUSKEY_ITEM_H

#include <vector>
#include <string>

class Item
{
private:
    bool isUsed;
    std::vector<int> binaryCode;
    std::vector<int> itemContain;

public:
    explicit Item();
    Item(int, int);
    ~Item() = default;
    Item & operator=(const Item &);

    bool get_isUsed();
    std::vector<int> get_binaryCode();
    std::vector<int> get_itemContain();

    void set_isUsed(bool);
    void set_binaryCode(const std::vector<int> &);
    void set_itemContain(const std::vector<int> &);

    bool isItemContain(int);
    int numOfOne();
    static bool combain(const Item &a, const Item &b, Item &result);
    std::string toString();
};

#endif //QUINE_MCCLUSKEY_ITEM_H