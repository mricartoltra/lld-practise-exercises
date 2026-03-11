#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>

enum class VehicleSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class Vehicle
{
    private:
        VehicleSize size_;
        std::string licensePlate_;
    public:
        Vehicle(VehicleSize size, std::string licensePlate) 
        : size_(size), licensePlate_(licensePlate) {}

        virtual ~Vehicle(){};
        VehicleSize GetSize() const {return size_;}
        std::string GetLicensePlate() const {return licensePlate_;}
};

class Motorcycle : public Vehicle
{
    public:
        Motorcycle(std::string licensePlate)
        : Vehicle(VehicleSize::SMALL, licensePlate) {};
};

class Car : public Vehicle
{
    public:
        Car(std::string licensePlate)
        : Vehicle(VehicleSize::MEDIUM, licensePlate) {};
};

class Truck : public Vehicle
{
    public:
        Truck(std::string licensePlate)
        : Vehicle(VehicleSize::LARGE, licensePlate) {};
};







class ParkingSpot
{
    private:
        VehicleSize spotSize_;
        std::string spotId_;
        bool isOccupied_;
        Vehicle* parkedVehicle_;
    
    public:
        ParkingSpot(VehicleSize size, std::string id)
        : spotSize_{size}, spotId_{id}, isOccupied_{false}, parkedVehicle_{nullptr} {};

        void parkVehicle(Vehicle *vehicle)
        {
            if (vehicle == nullptr) throw std::invalid_argument("Cannot park a non-existent vehicle.");
            if (vehicle->GetSize() != spotSize_) throw std::invalid_argument("Vehicle size does not match parking spot size.");
            if (isOccupied_) throw std::logic_error("Parking spot is already occupied.");
            isOccupied_ = true;
            parkedVehicle_ = vehicle;
        }

        void freeSpace()
        {
            isOccupied_ = false;
            parkedVehicle_ = nullptr;
        }

        bool isAvailable() {return !isOccupied_;}

};

class Level
{
    private:
        int id = 0;
        std::vector<std::unique_ptr<ParkingSpot>> smallSpots_;
        std::vector<std::unique_ptr<ParkingSpot>> mediumSpots_;
        std::vector<std::unique_ptr<ParkingSpot>> largeSpots_;

    public:
        Level(int level, int smallspots, int mediumspots, int largespots) : id{level}
        {
            for(int i = 0; i<smallspots; i++)
            {
                smallSpots_.push_back(std::make_unique<ParkingSpot>(VehicleSize::SMALL, id+"_s_"+i));
            }
            for(int i = 0; i<mediumspots; i++)
            {
                mediumSpots_.push_back(std::make_unique<ParkingSpot>(VehicleSize::MEDIUM, id+"_m_"+i));
            }
            for(int i = 0; i<largespots; i++)
            {
                largeSpots_.push_back(std::make_unique<ParkingSpot>(VehicleSize::LARGE  , id+"_l_"+i));
            }
        };
        
};

class IParkingStrategy
{
    public:
        virtual ~IParkingStrategy() {}
        virtual ParkingSpot findSpot(const Vehicle vehicle) = 0;
};

class DefaultParkingStrategy : public IParkingStrategy
{
    public:
        DefaultParkingStrategy() {}
        ParkingSpot findSpot(const Vehicle vehicle)
        {
            return;
        }
};



class IFeeStrategy
{
    public:
        virtual ~IFeeStrategy() {}
        virtual void calculateFee(const Vehicle* vehicle) = 0;

};
class FlatRateFee : public IFeeStrategy
{
    public:
        FlatRateFee(){}
        void calculateFee(const Vehicle* vehicle) override
        {
            //fix rate doesnt matter
            std::cout<<"The parking ticket is 5€"<<std::endl;
        }
};
class SizeSpecificFlatRateFee : public IFeeStrategy
{
    public:
        SizeSpecificFlatRateFee(){}
        void calculateFee(const Vehicle* vehicle) override
        {
            //fix rate doesnt matter
            VehicleSize size = vehicle->GetSize();
            if(size == VehicleSize::SMALL) std::cout<<"The parking ticket is 2€"<<std::endl;
            else if(size == VehicleSize::MEDIUM) std::cout<<"The parking ticket is 5€"<<std::endl;
            else if(size == VehicleSize::LARGE) std::cout<<"The parking ticket is 10€"<<std::endl;
        }
};

class ParkingLotSystem
{
    private:
        std::unique_ptr<IParkingStrategy> parkingStrategy_;
        std::unique_ptr<IFeeStrategy> feeStrategy_;
        
        std::vector<std::unique_ptr<Level>> floors_;

    public:
        ParkingLotSystem(IParkingStrategy* p, IFeeStrategy* f, int floors, int sSpots, int mSpots, int lSpots)
        : parkingStrategy_{p}, feeStrategy_{f} 
        {
            for(int i = 0; i<floors; i++)
            {
                floors_.push_back(std::make_unique<Level>(i, sSpots, mSpots, lSpots));
            }
        };

        void Enter(Vehicle vehicle){};

};

int main()
{
    std::unique_ptr<DefaultParkingStrategy> pStrategy = std::make_unique<DefaultParkingStrategy>();
    std::unique_ptr<FlatRateFee> fStrategy = std::make_unique<FlatRateFee>();
    int floors = 5;
    int small_spots = 10; // per floor
    int medium_spots = 100;
    int large_spots = 3;
    std::unique_ptr<ParkingLotSystem> parking = std::make_unique<ParkingLotSystem>(pStrategy, fStrategy, floors, small_spots, medium_spots, large_spots);

    Car myCar("CAR-123");
    Motorcycle myMoto("MTO-999");
    Truck myTruck("TRK-555");
    
    parking->Enter(myCar);
    parking->Enter(myMoto);
    parking->Enter(myTruck);

    return 0;
}