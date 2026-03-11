#include <iostream>
#include <string>
#include <unordered_map>


enum class Coin
{
    FIVE_CENTS,
    TEN_CENTS,
    TWENTY_CENTS,
    FIFTY_CENTS,
    EURO
};

enum class State
{
    IDLE,
    PROCESSING
};

class Item
{
    private:
        int price_;
        std::string code_;
    public:
        Item(std::string code, int price)
        : price_{price}, code_{code} {}
};

class Inventory
{
    private:
        std::unordered_map<std::string, Item> codeToItem;
        std::unordered_map<Item, int> itemToStock;
    public:
        Inventory(){};
};

class VendingMachine
{
    private:
        VendingMachine(){ std::cout << "Vending Machine Initialized." << std::endl; }
        ~VendingMachine(){ std::cout << "Vending Machine Destroyed." << std::endl; }
        

        Inventory stock;
        int money = 0;
        std::string selectedProduct = "";
        State currentState = State::IDLE;

    public:
        VendingMachine(const VendingMachine&) = delete;
        VendingMachine& operator=(const VendingMachine&) = delete;

        static VendingMachine& getInstance() 
        {
            static VendingMachine instance; 
            return instance;
        }

        void addMoney(Coin coin)
        {

        }

        void selectProduct(std::string productId)
        {

        }

        void refundMoney()
        {

        }

        void setItemcode(std::string id, Item item)
        {

        }
};

int main()
{
    VendingMachine& vendingMachine = VendingMachine::getInstance(); //Singleton Vending Machine

    return 0;
}