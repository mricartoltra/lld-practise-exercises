#include <vector>
#include <string>

class Vehicle
{
    private:
        VehicleSize size_;
        std::string licensePlate_;
    public:
        virtual ~Vehicle(){};

};

class Motorcycle : Vehicle
{
    public:
        Motorcycle(VehicleSize size, std::string licenseplate)
        : size_{size}, licensePlate_{licenseplate} 
        {};
};

class Car : Vehicle
{};

class Truck : Vehicle
{};

enum class VehicleSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class ParkingSpot
{
    private:

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