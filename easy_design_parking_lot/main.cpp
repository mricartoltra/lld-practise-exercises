#include <vector>
#include <string>
#include <stdexcept>

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

class Car : Vehicle
{
    public:
        Car(std::string licensePlate)
        : Vehicle(VehicleSize::MEDIUM, licensePlate) {};
};

class Truck : Vehicle
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
        int smallSpots_ = 0;
        int mediumSpots_ = 0;
        int largeSpots_ = 0;
    public:
        Level(int smallspots, int mediumspots, int largespots)
        : smallSpots_{smallspots}, mediumSpots_{mediumspots}, largeSpots_{largespots}
        {};
        
};

class IParkingStrategy
{
    public:
        void findSpot()
};

class IFeeStrategy
{

};

class ParkingLotSystem
{
    private:
        IParkingStrategy parkingStrategy;
        IFeeStrategy feeStrategy;
        std::vector<Level> floors;

    public:
        ParkingLotSystem(){};
        void Enter(VehicleType vehicle){};

};

int main()
{
    ParkingLotSystem parking;

}