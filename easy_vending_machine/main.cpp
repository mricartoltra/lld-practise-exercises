#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>


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
        std::string name_;
    public:
        Item(std::string id, std::string name, int price)
        : price_{price}, code_{id}, name_{name} {}

        int GetPrice() {return price_;}
        std::string GetId() {return code_;}
        std::string GetName() {return name_;}
};

class Inventory
{
    private:
        std::unordered_map<std::string, std::shared_ptr<Item>> codeToItem;
        std::unordered_map<std::shared_ptr<Item>, int> itemToStock;

    public:
        Inventory(){};
        void addItem(std::string id, std::string name, int price)
        {
            //Assuming there is not checks for possible ID's any string is valid
            codeToItem[id] = std::make_shared<Item>(id, name, price);
            itemToStock[codeToItem[id]] = 0;
        }

        void removeItem(std::string id)
        {
            //if(codeToItem[id] == nullptr) throw std::invalid_argument("Error: Invalid ID");
            itemToStock[codeToItem[id]] = 0;
            codeToItem[id] = nullptr;
        }

        void modifyItem(std::string id, int newprice)
        {
            if(codeToItem[id] == nullptr) throw std::invalid_argument("Error: Invalid ID");
            std::string name = codeToItem[id]->GetName();
            removeItem(id);
            addItem(id, name, newprice);
        }

        void addStock(std::string id, int amount)
        {
            if(codeToItem[id] == nullptr) throw std::invalid_argument("Error: Invalid ID");
            itemToStock[codeToItem[id]] += amount;
        }

        bool isAvailable(std::string id)
        {
            return itemToStock[codeToItem[id]] > 0;
        }

        void sellOne(std::string id)
        {
            itemToStock[codeToItem[id]]--;
        }

        std::shared_ptr<Item> GetItemInfo(std::string id)
        {
            // if not exist return nullptr
            // TODO
            return codeToItem[id];
        }
};

class VendingMachine
{
    private:
        VendingMachine(){ std::cout << "Vending Machine Initialized." << std::endl; }
        ~VendingMachine(){ std::cout << "Vending Machine Destroyed." << std::endl; }
        

        Inventory* inventory;
        int balance = 0;
        std::vector<Coin> coins_;
        std::string selectedItemCode = "";
        State currentState = State::IDLE;

        void refundBalance()
        {
            for(int i = 0; i<coins_.size(); i++)
            {
                std::cout<<"Dispensing a coin to the client."<<std::endl;
            }
            coins_.clear();
        }

        void dispense(std::string id)
        {
            std::string name = inventory->GetItemInfo(id)->GetName();
            std::cout<<"Dispensing a "<<name<< " to the client."<<std::endl;
            inventory->sellOne(id);
        }

    public:
        VendingMachine(const VendingMachine&) = delete;
        VendingMachine& operator=(const VendingMachine&) = delete;

        static VendingMachine& getInstance() 
        {
            static VendingMachine instance; 
            return instance;
        }

        void AddMoney(Coin coin)
        {
            if(coin == Coin::FIVE_CENTS) balance+=5;
            else if(coin == Coin::TEN_CENTS) balance+=10;
            else if(coin == Coin::TWENTY_CENTS) balance+=20;
            else if(coin == Coin::FIFTY_CENTS) balance+=50;
            else if(coin == Coin::EURO) balance+=100;
            coins_.push_back(coin);
        }

        void SelectProduct(std::string id)
        {
            //check if it is a valid id
            if(inventory->GetItemInfo(id) ==nullptr) throw std::invalid_argument("Wrong item ID.");
            //check if stock
            if(inventory->isAvailable(selectedItemCode)) throw std::invalid_argument("No stock.");
        }

        void ConfirmSelection()
        {
            if(selectedItemCode == "") throw std::invalid_argument("You must select an item first.");
            if(balance < inventory->GetItemInfo(selectedItemCode)->GetPrice()) throw std::invalid_argument("Not enough funds.");

            currentState = State::PROCESSING;
            dispense(selectedItemCode);
            selectedItemCode="";

            //Maybe add possibility of tracking balance, for now there is no change in the machine.
            balance = 0;
            coins_.clear();
            currentState = State::IDLE;
        }

        void Cancel()
        {
            //return money
            if(!coins_.empty()) refundBalance();
            //unselect
            selectedItemCode = "";
        }

        void SetNewItemcode(std::string id, std::string name, int price)
        {
            inventory->addItem(id, name, price);
        }

        void RemoveItemCode(std::string id)
        {
            inventory->removeItem(id);
        }

        void ModifyItem(std::string id, int newprice)
        {
            inventory->modifyItem(id,newprice);
        }

        void AddStock(std::string id, int amount)
        {
            inventory->addStock(id, amount);
        }
};

int main()
{
    VendingMachine& vendingMachine = VendingMachine::getInstance(); //Singleton Vending Machine

    //Populate the machine and do some testing

    return 0;
}