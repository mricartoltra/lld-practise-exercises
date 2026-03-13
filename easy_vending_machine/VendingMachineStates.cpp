#include <memory>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

class Inventory
{
    private:
        std::unordered_map<std::string, int> idToStock;

    public:
        Inventory(){}
};

class State
{
    public:
        State(){}
        virtual ~State(){};
        virtual void SelectProduct(std::string id) = 0;
        virtual void AddMoney(int money) = 0;
        virtual void DeliverProduct() = 0;
        virtual void RefundMoney() = 0;


};
class WaitingProductState : public State
{
    public:
        WaitingProductState() : State() {}
        void SelectProduct(std::string id) override {
            //
        };
        void AddMoney(int money) override {
            throw std::invalid_argument("No Product Selected");
        };
        void DeliverProduct() override {
            throw std::invalid_argument("No Product Selected");
        };
        void RefundMoney() override {
            throw std::invalid_argument("No Money to return");
        };
};
class WaitingMoneyState : public State
{
    private:
        std::string id_;
        int balance = 0;
    public:
        WaitingMoneyState(std::string id) : State(), id_{id} {}
        void SelectProduct(std::string id) override {
            throw std::invalid_argument("Already Selected");
        };
        void AddMoney(int money) override {
            balance += money;
        };
        void DeliverProduct() override {
            //if balance is >= then deliver and return extra money
        };
        void RefundMoney() override {
            std::cout<<"Returned "<<balance<<" euros."<<std::endl;
            balance = 0;
        };
};
class DeliveringProductState : public State
{
    public:
        DeliveringProductState() : State() {}
        void SelectProduct(std::string id) override {
            throw std::invalid_argument("Processing");
        };
        void AddMoney(int money) override {
            throw std::invalid_argument("Processing");
        };
        void DeliverProduct() override {
            throw std::invalid_argument("Processing");
        };
        void RefundMoney() override {
            throw std::invalid_argument("Processing");
        };
};


class VendingMachine
{
    private:
        Inventory* inventory_;
        State* state_;

    public:
        VendingMachine(Inventory* inventory)
        : inventory_{inventory}
        {
            state_ = new WaitingProductState();
        }

        void AddProduct(std::string id, std::string name, int price){}
        void AddStock(){}
        
        //state dependant
        void SelectProduct(std::string id){
            state_->SelectProduct(id);
        }
        void AddMoney(int money){
            state_->AddMoney(money);
        }
        void DeliverProduct(){
            state_->DeliverProduct();
        }
        void RefundMoney(){}
};

int main()
{
    std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
    std::unique_ptr<VendingMachine> vendingMachine = std::make_unique<VendingMachine>(inventory);


    return 0;
}