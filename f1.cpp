#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <deque>
#include <windows.h>
#include <time.h>

class Team;
class Driver;
class Race;

class Car{
    static int carCount;
    const int carId;

    std::string brand;
    char *model;
    int releaseDate;
    bool broken;
    float topSpeed;
    bool taken; // only one car shall be taken by a driver at a time

    public:
        static int getCarCount() { return Car::carCount;}
        const int getCarId(){return this->carId;}

        std::string getBrand() const{return this->brand;}
        const char* getModel(){return this->model;}
        std::string getCarName() const{std::string temp = this->brand + " " + std::string(this->model); return temp;}
        int getReleaseDate() const{return this->releaseDate;}
        bool getBroken() const{return this->broken;}
        float getTopSpeed() const{return this->topSpeed;}
        bool getTaken() const{if(this == nullptr){ std::cout << "AU"; return 0;} return this->taken;}

        void setBrand(const std::string& brand){this->brand = brand;}
        void setModel(char* model);
        void setReleaseDate(const int releaseDate){this->releaseDate = releaseDate;}                 
        void setBroken(const bool broken){this->broken = broken;}
        void setTopSpeed(const float topSpeed){this->topSpeed = topSpeed;}
        void setTaken(const bool taken){this->taken = taken;}

        Car();
        Car(std::string brand);
        Car(std::string brand, char* model, int releaseDate, float topSpeed);
        Car(const Car& obj);        
        ~Car();
        Car& operator=(const Car& obj);

        friend std::ostream& operator<<(std::ostream& out, const Car& obj);
        friend std::istream& operator>>(std::istream& in, Car& obj); // we give the address in order to change the data of the object

        Car operator +(float); // increases top speed
        friend Car operator+(float, Car); 
        Car operator -(float); // decreases top speed
        friend Car operator-(float, Car);
        Driver operator+(const Driver& driver); // adds a car to a driver object
        Car operator +(const Car& obj); // concatenates the car names, adds the top speed together
        Car& operator++(); // increases top speed
        Car operator++(int); 
        Car& operator--(); // decreases top speed
        Car operator--(int);

        bool operator<(const Car& obj) const; // compares top speed
        bool operator<=(const Car& obj) const;
        bool operator==(const Car& obj);
        bool operator>(const Car& obj) const;
        bool operator>=(const Car& obj) const;
        char operator [](int);

        std::string toString() const;
        operator std::string();
        operator std::string() const;
        operator int() const;
        operator bool() const;
};

int Car::carCount = 10000;

Car::Car():carId(carCount++)
{
    this->brand = "Unknown";
    this->model = new char[strlen("Unknown")+1];
    strcpy(this->model, "Unknown");
    this->releaseDate = 0;
    this->broken = false;
    this->topSpeed = 0;
}

Car::Car(std::string brand):carId(carCount++)
{
    this->brand = brand;
    this->model = new char[strlen("Unknown")+1];
    strcpy(this->model, "Unknown");
    this->releaseDate = 0;
    this->broken = false;
    this->topSpeed = 0;
    this->taken = 0;
}

Car::Car(std::string brand, char* model, int releaseDate, float topSpeed):carId(carCount++)
{
    this->brand = brand;
    this->model = new char[strlen(model) + 1];
    strcpy(this->model, model);
    this->releaseDate = releaseDate;
    this->broken = false;
    this->topSpeed = topSpeed;
    this->taken = 0;
}

Car::Car(const Car& obj):carId(carCount++)
{
    this->brand = obj.brand;
    this->model = new char[strlen(obj.model) + 1];
    strcpy(this->model, obj.model);
    this->releaseDate = obj.releaseDate;
    this->broken = 0;
    this->topSpeed = obj.topSpeed;
    this->taken = 0;
}

Car::~Car()
{
    if(this->model != nullptr)
    {
        delete[] this->model;
        this->model = nullptr;
    }
}

Car& Car::operator = (const Car& obj)
{
    if(this != &obj)
    {
        if(this->model != nullptr)
        {
            delete[] this->model;
            this->model = nullptr;
        }
        this->brand = obj.brand;
        this->model = new char[strlen(obj.model) + 1];
        strcpy(this->model, obj.model);
        this->releaseDate = obj.releaseDate;
        this->broken = obj.broken;
        this->topSpeed = obj.topSpeed;
        this->taken = obj.taken;
    }
    return *this;
}

void Car::setModel(char* model){
    if(this->model != nullptr)
    {
        delete[] this->model;
        this->model = nullptr;
    }
    this->model = new char[strlen(model) + 1];
    strcpy(this->model, model);
}

std::ostream& operator <<(std::ostream& out, const Car& car)
{
    out << "Car id: " << car.carId << '\n';
    out << "Car brand: " << car.brand << '\n';
    out << "Car model: " << car.model << '\n';
    out << "Car release date: " << car.releaseDate << '\n';
    out << "Car status: " << (car.broken ? "broken" : "not broken") << '\n';
    out << "Top speed: " << car.topSpeed << '\n';
    out << "Car taken: " << (car.taken ? "taken" : "not taken");
    return out;
}

std::istream& operator >>(std::istream& in,Car& car)
{
    std::cout << "Enter car brand: ";
    in.get();
    getline(in, car.brand);
    car.model = new char[100];
    std::cout << "Enter car model: ";
    in.get(car.model, 100);
    std::cout << "Enter car release date(Year): ";
    in >> car.releaseDate;
    car.broken = false;
    std::cout << "Enter car's top speed(Km/h): ";
    in >> car.topSpeed;
    car.taken = false;
    return in;
}

Car Car::operator+(float topSpeed){
    Car temp(*this);
    temp.topSpeed += topSpeed;
    return temp;
}

Car Car::operator-(float topSpeed){
    Car temp(*this);
    temp.topSpeed -= topSpeed;
    return temp;
}

Car operator+(float topSpeed, Car car){
    Car temp(car);
    temp.topSpeed += topSpeed;
    return temp;
}

Car operator-(float topSpeed, Car car){
    Car temp(car);
    temp.topSpeed -= topSpeed;
    return temp;
}

Car Car::operator+(const Car& car){
    Car temp(*this);
    temp.brand = this->brand + " & " + car.brand;
    if(temp.model != nullptr)
    {
        delete[] temp.model;
        temp.model = nullptr;
    }
    temp.model = new char[strlen(this->model) + strlen(car.model) + 1];
    strcpy(temp.model, this->model);
    strcat(temp.model, " & ");
    strcat(temp.model, car.model);
    temp.releaseDate = std::max(this->releaseDate, car.releaseDate);
    if(this->broken == true || car.broken == true)    
        temp.broken = true;
    else temp.broken = false;
    temp.topSpeed = this->topSpeed + car.topSpeed;
    if(this->taken == true || car.taken == true)    
        temp.taken = true;
    else temp.taken = false;
    return temp;
}

Car Car::operator++(int topSpeed){
    Car temp(*this);
    this->topSpeed++;
    return temp;
}

Car& Car::operator++(){
    this->topSpeed++;
    return *this;
}

Car Car::operator--(int topSpeed){
    Car temp(*this);
    this->topSpeed--;
    return temp;
}

Car& Car::operator--(){
    this->topSpeed--;
    return *this;
}

bool Car::operator<(const Car& obj) const{
    return this->topSpeed < obj.topSpeed;
}

bool Car::operator<=(const Car& obj) const{
    return this->topSpeed <= obj.topSpeed;
}

bool Car::operator>(const Car& obj) const{
    return this->topSpeed > obj.topSpeed;
}

bool Car::operator>=(const Car& obj) const{
    return this->topSpeed >= obj.topSpeed;
}

bool Car::operator==(const Car& obj){
    return this->topSpeed == obj.topSpeed;
}

char Car::operator[](int index){
    if(this->model == NULL)
        throw std::runtime_error("Unknown model");
    else{
        if(index < 0 || index >= strlen(this->model))
            throw std::runtime_error("Invalid index");
        return this->model[index];
    }
}

Car::operator int() const{
    return this->topSpeed;
}

Car::operator bool() const{
    return this->broken;
}

std::string Car::toString() const{
    std::string temp = this->brand;
    temp += "\nModel: " + std::string(this->model);
    temp += "\nRelease date: " + std::to_string(this->releaseDate);
    temp += "\nStatus: " + (this->broken) ? "broken" : "not broken";
    temp += "\nTop speed: " + std::to_string(this->topSpeed);
    temp += "\nTaken: " + (this->taken) ? "taken" : "not taken";
    return temp;
}

Car::operator std::string(){
    return this->toString();
}

Car::operator std::string() const{
    return this->toString();
}

class Driver{
        static int driverCount;
        const int driverId;

        std::string name;
        std::string distance = "";
        int raceWins;
        int podiumsNumber;
        float points;
        char type; // types: Primary (P), Reserve(R), Unknown(U); Only primary drivers are eligible for races
        int championshipsWon;
        int* championshipsYears;
        Car* car = nullptr;
    public:
        static int getDriverCount(){return Driver::driverCount;}
        int getDriverId() const{return this->driverId;}
        std::string getDriverName() const{return this->name;}
        const int* getChampionshipsYears() const{return this->championshipsYears;}
        char getType() const{return this->type;}
        float getPoints() const{return this->points;}
        int getPodiumsNumber() const{return this->podiumsNumber;}
        int getRaceWins() const{return this->raceWins;}
        std::string getDistance() const{return this->distance;}
        const Car* getCar() const{return this->car;}

        void setName(std::string name){this->name = name;}
        void setPoints(float points){this->points = points;}
        void setPodiumsNumber(int podiumsNumber){this->podiumsNumber = podiumsNumber;}
        void setRaceWins(int raceWins){this->raceWins = raceWins;}
        void setType(char type){this->type = type;}
        void setDistance(std::string distance){this->distance = distance;}
        void setChampionships(int championshipsWon, int* championshipsYears);
        void setCar(Car* car){if(this->car != nullptr) this->car->setTaken(0); this->car = car; if(car != nullptr)this->car->setTaken(true);}

        Driver();
        Driver(std::string name, int raceWins, int podiumsNumber, float points, char type, int championshipsWon, int* championshipsYears);
        Driver(std::string name, int raceWins, int podiumsNumber, float points, char type, int championshipsWon, int* championshipsYears, Car* car);
        Driver(const Driver& obj);
        ~Driver();
        Driver& operator =(const Driver& obj);

        friend std::ostream& operator <<(std::ostream& out, const Driver& driver);
        friend std::istream& operator >>(std::istream& in, Driver& driver);

        Driver operator +(float);
        friend Driver operator+(float, Driver);
        Driver operator -(float);
        friend Driver operator-(float, Driver);
        Driver operator+(const Driver& obj); // concatenates the driver names, adds the points, race wins and championship years together
        Team operator+(const Team& team); // Adds a driver to the team;
        Driver operator+(Car& car); // erases the previous car and adds the new one
        Race operator+(const Race& race); // Adds a driver to a race
        friend Driver Car::operator+(const Driver& driver);
        Driver& operator++(); // increases podiums number
        Driver operator++(int); 
        Driver& operator--(); // decreases podiums number
        Driver operator--(int);

        bool operator<(const Driver& obj) const; // compares race wins
        bool operator<=(const Driver& obj) const;
        bool operator==(const Driver& obj);
        bool operator>(const Driver& obj) const;
        bool operator>=(const Driver& obj) const;
        int operator [](int);

        std::string toString() const;
        operator std::string();
        operator std::string() const;
};

int Driver::driverCount = 10;

Driver::Driver():driverId(driverCount++){
    this->name = "Unknown";
    this->raceWins = 0;
    this->podiumsNumber = 0;
    this->points = 0;
    this->type = 'U'; 
    this->championshipsWon = 0;
    this->championshipsYears = nullptr;
    this->car = nullptr;
}

Driver::Driver(std::string name, int raceWins, int podiumsNumber, float points, char type, int championshipsWon, int* championshipsYears):driverId(driverCount++){
    this->name = name;
    this->raceWins = raceWins;
    this->podiumsNumber = podiumsNumber;
    this->points = points;
    this->type = type;
    this->championshipsWon = championshipsWon;
    this->championshipsYears = new int[championshipsWon];
    for(int i = 0; i < championshipsWon; ++i)
        this->championshipsYears[i] = championshipsYears[i];
    this->car = nullptr;
}

Driver::Driver(std::string name, int raceWins, int podiumsNumber, float points, char type, int championshipsWon, int* championshipsYears, Car* car):driverId(driverCount++)
{
    this->name = name;
    this->raceWins = raceWins;
    this->podiumsNumber = podiumsNumber;
    this->points = points;
    this->type = type;
    this->championshipsWon = championshipsWon;
    this->championshipsYears = new int[championshipsWon];
    for(int i = 0; i < championshipsWon; ++i)
        this->championshipsYears[i] = championshipsYears[i];
    this->car = car;
}

Driver::Driver(const Driver& obj):driverId(driverCount++)
{
    this->name = obj.name;
    this->raceWins = obj.raceWins;
    this->podiumsNumber = obj.podiumsNumber;
    this->points = obj.points;
    this->type = obj.type;
    this->championshipsWon = obj.championshipsWon;
    this->championshipsYears = new int[obj.championshipsWon];
    for(int i = 0; i < obj.championshipsWon; ++i)
        this->championshipsYears[i] = obj.championshipsYears[i];
    this->car = obj.car;
}

Driver::~Driver()
{
    if(this->championshipsYears != NULL)
    {
        delete[] this->championshipsYears;
        this->championshipsYears = NULL;
    }
}

Driver& Driver::operator =(const Driver& obj)
{
    if(this != &obj){
        if(this->championshipsYears != NULL)
        {
            delete[] this->championshipsYears;
            this->championshipsYears = NULL;
        }
        this->name = obj.name;
        this->raceWins = obj.raceWins;
        this->podiumsNumber = obj.podiumsNumber;
        this->points = obj.points;
        this->type = obj.type;
        this->championshipsWon = obj.championshipsWon;
        this->championshipsYears = new int[obj.championshipsWon];
        for(int i = 0; i < obj.championshipsWon; ++i)
            this->championshipsYears[i] = obj.championshipsYears[i];
        this->car = obj.car;
    }
    return *this;
}

void Driver::setChampionships(int championshipsWon, int* championshipsYears){
    if(this->championshipsYears != NULL)
    {
        delete[] this->championshipsYears;
        this->championshipsYears = NULL;
    }
    this->championshipsWon = championshipsWon;
    this->championshipsYears = new int[championshipsWon];
    for(int i = 0 ; i < this->championshipsWon; ++i)
        this->championshipsYears[i] = championshipsYears[i];
}

std::ostream& operator <<(std::ostream& out, const Driver& driver)
{
    out << "Driver id: " << driver.driverId << '\n';
    out << "Driver name: " << driver.name << "\n";
    out << "Driver points: " << driver.points << "\n";
    out << "Driver role: " << driver.type << "\n";
    out << "Driver race wins: " << driver.raceWins << "\n";
    out << "Driver podiums: " << driver.podiumsNumber << '\n';
    out << "Championships: " << driver.championshipsWon << "\n";
    if(driver.championshipsWon > 0)
    {   
        out << "Years that the championship has been won: ";
        for(int i = 0; i < driver.championshipsWon-1; ++i) out << driver.championshipsYears[i] << ", ";
        out << driver.championshipsYears[driver.championshipsWon-1] << '\n';
    }
    if(driver.car != nullptr)
        out << "Car: " << driver.car->getBrand() << " " << driver.car->getModel() << "\n";
    else out << "Car: Unknown";
    return out;
}

std::istream& operator >>(std::istream& in, Driver& driver)
{
    if(driver.championshipsYears != NULL)
        delete[] driver.championshipsYears;
    std::cout << "Enter driver's name: ";
    std::cin.get();
    getline(in, driver.name);
    std::cout << "Enter driver's race wins: ";
    in >> driver.raceWins;
    std::cout << "Enter driver's number of podiums: ";
    in >> driver.podiumsNumber;
    std::cout << "Enter driver's points: ";
    in >> driver.points;
    std::cout << "Enter driver's role(P - Primary, R - Reserve, U - Unknown): ";
    in >> driver.type;
    std::cout << "Enter driver's number of championships won: ";
    in >> driver.championshipsWon;
    if(driver.championshipsWon == 0)
        driver.championshipsYears = nullptr;
    else{
        driver.championshipsYears = new int[driver.championshipsWon];
        std::cout << "Enter the years that the championship has been won:\n";
    for(int i = 0; i < driver.championshipsWon; ++i)
        in >> driver.championshipsYears[i];
    }
    // in >> driver.car;
    return in;
}

Driver Driver::operator+(float points)
{
    Driver temp(*this);
    temp.points += points;
    return temp;
}

Driver operator+(float points, Driver driver)
{
    Driver temp(driver);
    temp.points += points;
    return driver;
}

Driver Driver::operator-(float points)
{
    Driver temp(*this);
    temp.points -= points;
    return temp;
}

Driver operator-(float points, Driver driver)
{
    Driver temp(driver);
    temp.points -= points;
    return driver;
}

Driver Driver::operator+(const Driver& driver)
{
    Driver temp(*this);
    temp.name += " & " + driver.name;
    temp.points += driver.points;
    temp.raceWins += driver.raceWins;
    temp.podiumsNumber += driver.podiumsNumber;
    if(driver.type == 'P' || temp.type == 'P')
        temp.type = 'P';
    else{
        if(driver.type == 'R' || temp.type == 'R')
            temp.type = 'R';
        else temp.type = 'U';
    }
    temp.championshipsWon += driver.championshipsWon;
    if(temp.championshipsYears != NULL)
    {
        delete[] temp.championshipsYears;
        temp.championshipsYears = NULL;
    }
    temp.championshipsYears = new int[temp.championshipsWon];
    int i, k = 0;
    for(i = 0; i < this->championshipsWon; ++i)
        temp.championshipsYears[i] = this->championshipsYears[i];
    for(int j = i; j < temp.championshipsWon; ++j)
        temp.championshipsYears[j] = driver.championshipsYears[k++];
    std::sort(temp.championshipsYears, temp.championshipsYears + temp.championshipsWon);
    // Car temp2;
    // temp2 = *(temp.car) + *(driver.car);
    // temp.car = &temp2;
    return temp;
}

Driver Driver::operator+(Car& car){
    Driver temp(*this);
    if(temp.car != nullptr)
        temp.car->setTaken(0);
    temp.car = &car;
    temp.car->setTaken(true);
    return temp;
}

Driver Car::operator+(const Driver& driver){
    Driver temp(driver);
    temp.car = &(*this);
    temp.car->setTaken(true);
    return temp;
}

Driver Driver::operator++(int){
    Driver temp(*this);
    this->raceWins++;
    return temp;
}

Driver& Driver::operator++(){
    this->raceWins++;
    return *this;
}

Driver Driver::operator--(int podiumsNumber){
    Driver temp(*this);
    this->podiumsNumber--;
    return temp;
}

Driver& Driver::operator--(){
    this->podiumsNumber--;
    return *this;
}

bool Driver::operator<(const Driver& obj) const{
    return this->raceWins < obj.raceWins;
}

bool Driver::operator<=(const Driver& obj) const{
    return this->raceWins <= obj.raceWins;
}

bool Driver::operator>(const Driver& obj) const{
    return this->raceWins > obj.raceWins;
}

bool Driver::operator>=(const Driver& obj) const{
    return this->raceWins >= obj.raceWins;
}

bool Driver::operator==(const Driver& obj){
    return this->raceWins == obj.raceWins;
}

int Driver::operator[](int index)
{
    if(this->championshipsYears == NULL)
        throw std::runtime_error("No championships");
    if(index < 0 || index > this->championshipsWon)
        throw std::runtime_error("invalid index");
    return this->championshipsYears[index];
}

std::string Driver::toString() const{
    std::string temp = this->name;
    temp += " " + std::to_string(this->raceWins);
    temp += " " + std::to_string(this->podiumsNumber);
    temp += " " + std::to_string(this->points);
    temp += " " + std::to_string(this->type);
    temp += " " + std::to_string(this->championshipsWon);
    for(int i = 0; i < this->championshipsWon; i++)
        temp += " " + std::to_string(this->championshipsYears[i]);
    temp += " " + this->car->getBrand();
    return temp;
}

Driver::operator std::string(){
    return this->toString();
}

Driver::operator std::string() const{
    return this->toString();
}

class Team{

        const int idTeam;
        static int teamCount;

        char *teamName;
        int championshipsNumber;
        int* championshipsYears;
        float points;
        int raceWins;
        std::vector<Driver*> drivers;
    public:
        static int getTeamCount(){return Team::teamCount;}
        const int getIdTeam(){return this->idTeam;}
        const char* getTeamName() const{return this->teamName;}
        int getChampionshipsNumber() const{return this->championshipsNumber;}
        const int* getChampionshipsYears() const{return this->championshipsYears;}
        float getPoints() const{return this->points;}
        int getRaceWins() const{return this->raceWins;}
        std::vector<Driver*> getDrivers() const{return this->drivers;}
        
        void setTeamName(char *teamName);
        void setChampionshipsYears(int championshipsNumber, int* championshipsYears);
        void setPoints(float points){this->points = points;}
        void setRaceWins(int raceWins){this->raceWins = raceWins;}
        void setDrivers(std::vector<Driver*> drivers){this->drivers = drivers;}
        void addDriver(Driver* driver);
        
        Team();
        Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, int raceWins);
        Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, int raceWins, const std::vector<Driver*>& drivers);
        Team(const Team& obj);
        Team& operator =(const Team& obj);
        ~Team();

        friend std::ostream& operator <<(std::ostream& out, const Team& team);
        friend std::istream& operator >>(std::istream& in, Team& team);
        Team operator +(float);
        friend Team operator +(float, Team);
        Team operator -(float);
        friend Team operator -(float, Team);
        friend Team Driver::operator+(const Team& team);
        Team operator +(const Team& obj); // concatenates the team names, adds the points, race wins and championships years together
        Team operator +(Driver& driver);
        Team& operator++(); // increases race wins
        Team operator++(int); 
        Team& operator--(); // decreases race wins
        Team operator--(int);
        bool operator<(const Team& obj) const;
        bool operator<=(const Team& obj) const;
        bool operator==(const Team& obj);
        bool operator>(const Team& obj) const;
        bool operator>=(const Team& obj) const;
        int operator [](int);

        std::string toString() const;
        operator std::string();
        operator std::string() const;
};
int Team::teamCount = 1000;

void Team::setTeamName(char* teamName){
    if(this->teamName != nullptr)
    {
        delete[] this->teamName;
        this->teamName = nullptr;
    }
    this->teamName = new char[strlen(teamName) + 1];
    strcpy(this->teamName, teamName);
}

void Team::addDriver(Driver* driver){
    bool duplicate = false;
    for(int i = 0; i < this->drivers.size(); ++i)
        if(driver->getDriverId() == this->drivers[i]->getDriverId())
            duplicate = true;
    if(duplicate == false)
        this->drivers.push_back(driver);
}

void Team::setChampionshipsYears(int championshipsNumber, int* championshipsYears)
{
    if(this->championshipsYears != NULL)
    {
        delete[] this->championshipsYears;
        this->championshipsYears = NULL;
    }
    this->championshipsNumber = championshipsNumber;
    this->championshipsYears = new int[championshipsNumber];
    for(int i = 0; i < this->championshipsNumber; ++i)
        this->championshipsYears[i] = championshipsYears[i];
}

Team::Team():idTeam(teamCount++){
    this->teamName = new char[strlen("Unknown") + 1];
    strcpy(this->teamName, "Unknown");
    this->championshipsNumber = 0;
    this->championshipsYears = nullptr;
    this->points = 0;
    this->raceWins = 0;
    this->drivers = {};
}

Team::Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, int raceWins):idTeam(teamCount++){
    this->teamName = new char[strlen(teamName) + 1];
    strcpy(this->teamName, teamName);
    this->championshipsNumber = championshipsNumber;
    this->championshipsYears = new int[championshipsNumber];
    for(int i = 0; i < championshipsNumber; i++)
        this->championshipsYears[i] = championshipsYears[i];
    this->points = points;
    this->raceWins = raceWins;
    this->drivers = {};
}

Team::Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, int raceWins, const std::vector<Driver*>& drivers):idTeam(teamCount++)
{
    this->teamName = new char[strlen(teamName) + 1];
    strcpy(this->teamName, teamName);
    this->championshipsNumber = championshipsNumber;
    this->championshipsYears = new int[championshipsNumber];
    for(int i = 0; i < championshipsNumber; i++)
        this->championshipsYears[i] = championshipsYears[i];
    this->points = points;
    this->raceWins = raceWins;
    this->drivers = drivers;
}

Team::Team(const Team& obj):idTeam(teamCount++){
    this->teamName = new char[strlen(obj.teamName) + 1];
    strcpy(this->teamName, obj.teamName);
    this->championshipsNumber = obj.championshipsNumber;
    this->championshipsYears = new int[obj.championshipsNumber];
    for(int i = 0; i < obj.championshipsNumber; i++)
        this->championshipsYears[i] = obj.championshipsYears[i];
    this->points = obj.points;
    this->raceWins = obj.raceWins;
    this->drivers = obj.drivers;
}

Team::~Team(){
    if(this->teamName != NULL)
    {
        delete[] this->teamName;
        this->teamName = NULL;
    }
    if(this->championshipsYears != NULL)
    {
        delete[] this->championshipsYears;
        this->championshipsYears = NULL;
    }
}

Team& Team::operator =(const Team& obj){
    if(this != &obj){
        if(this->teamName != NULL)
        {
            delete[] this->teamName;
            this->teamName = NULL;
        }
        if(this->championshipsYears != NULL)
        {
            delete[] this->championshipsYears;
            this->championshipsYears = NULL;
        }
        this->teamName = new char[strlen(obj.teamName) + 1];
        strcpy(this->teamName, obj.teamName);
        this->championshipsNumber = obj.championshipsNumber;
        this->championshipsYears = new int[obj.championshipsNumber];
        for(int i = 0; i < obj.championshipsNumber; i++)
            this->championshipsYears[i] = obj.championshipsYears[i];
        this->points = obj.points;
        this->raceWins = obj.raceWins;
        this->drivers = obj.drivers;
    }
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Team& team)
{
    out << "Team id: " << team.idTeam << '\n';
    out << "Team name: " << team.teamName << "\n";
    out << "Team points: " << team.points << "\n";
    out << "Team raceWins: " << team.raceWins << "\n";
    out << "Championships: " << team.championshipsNumber << "\n";
    if(team.championshipsNumber > 0)
    {   
        out << "Years that the championship has been won: ";
        for(int i = 0; i < team.championshipsNumber-1; ++i) out << team.championshipsYears[i] << ", ";
        out << team.championshipsYears[team.championshipsNumber-1] << '\n';
    }
    if(!team.drivers.empty())
    {
        out << "Drivers: ";
        for(int i = 0; i < team.drivers.size()-1; ++i)
            out << team.drivers[i]->getDriverName() << " & ";
        out << team.drivers[team.drivers.size()-1]->getDriverName();
    } else out << "No drivers found!\n";
    return out;
}

std::istream& operator >>(std::istream& in, Team& team)
{
    std::cout << "Enter team name: ";
    char temp[100];
    in.get();
    in.get(temp, 100);
    if(team.teamName != NULL)
    {
        delete[] team.teamName;
    }
    if(team.championshipsYears != NULL)
    {
        delete[] team.championshipsYears;
    }
    team.teamName = new char[strlen(temp) + 1];
    strcpy(team.teamName, temp);
    std::cout << "Enter team points: ";
    in >> team.points;
    std::cout << "Enter race wins: ";
    in >> team.raceWins;
    std::cout << "Enter number of championships: ";
    in >> team.championshipsNumber;
    if(team.championshipsNumber == 0)
        team.championshipsYears = nullptr;
    else{
        team.championshipsYears = new int[team.championshipsNumber];
        for(int i = 0; i < team.championshipsNumber; ++i)
        {
            std::cout << "Enter championship year " << i+1 <<": ";
            in >> team.championshipsYears[i];
        }
    }
    // std::cout << "Drivers: ";
    // in >> team.drivers;
    team.drivers = {};
    std::cout << '\n';
    return in;
}

Team Team::operator+(float points)
{
    Team temp(*this);
    temp.points = temp.points + points;
    return temp;
}

Team operator+(float points, Team obj)
{
    Team temp(obj);
    temp.points = temp.points + points;
    return temp;
}

Team Team::operator-(float points)
{
    Team temp(*this);
    temp.points = temp.points - points;
    return temp;
}

Team operator-(float points, Team obj)
{
    Team temp(obj);
    temp.points = temp.points - points;
    return temp;
}

Team Team::operator+(const Team& obj)
{
    Team temp(*this);
    if(temp.teamName != NULL)
    {
        delete[] temp.teamName;
        temp.teamName = NULL;
    }
    if(temp.championshipsYears != NULL)
    {
        delete[] temp.championshipsYears;
        temp.championshipsYears = NULL;
    }
    temp.teamName = new char[strlen(this->teamName) + strlen(obj.teamName) + 1];
    char temp2[strlen(this->teamName) + strlen(obj.teamName) + 1] = "";
    strcpy(temp2, this->teamName);
    strcat(temp2, " & ");
    strcat(temp2, obj.teamName);
    strcpy(temp.teamName, temp2);
    temp.championshipsNumber = this->championshipsNumber + obj.championshipsNumber;
    temp.championshipsYears = new int[temp.championshipsNumber];
    int i, k = 0;
    for(i = 0; i < this->championshipsNumber; ++i)
        temp.championshipsYears[i] = this->championshipsYears[i];
    for(int j = i; j < temp.championshipsNumber; ++j)
        temp.championshipsYears[j] = obj.championshipsYears[k++];
    std::sort(temp.championshipsYears, temp.championshipsYears + temp.championshipsNumber);
    temp.points = this->points + obj.points;
    temp.raceWins = this->raceWins + obj.raceWins;        
    temp.drivers.insert(temp.drivers.end(), obj.drivers.begin(), obj.drivers.end());
    return temp;
}

Team Team::operator +(Driver& driver){
    Team temp(*this);
    bool duplicate = false;
    for(int i = 0; i < temp.drivers.size(); ++i)
        if(driver.getDriverId() == temp.drivers[i]->getDriverId())
            duplicate = true;
    if(duplicate == false)
        temp.drivers.push_back(&driver);
    return temp;
}

Team& Team::operator++(){
    this->raceWins++;
    return *this;
}

Team Team::operator++(int){
    Team temp(*this);
    this->raceWins++;
    return temp;
}

Team& Team::operator--(){
    this->raceWins--;
    return *this;
}

Team Team::operator--(int){
    Team temp(*this);
    this->raceWins--;
    return temp;
}

bool Team::operator<(const Team& obj) const{
    return this->raceWins < obj.raceWins;
}

bool Team::operator<=(const Team& obj) const{
    return this->raceWins <= obj.raceWins;
}

bool Team::operator>(const Team& obj) const{
    return this->raceWins > obj.raceWins;
}

bool Team::operator>=(const Team& obj) const{
    return this->raceWins >= obj.raceWins;
}

bool Team::operator==(const Team& obj){
    return this->raceWins == obj.raceWins;
}

int Team::operator [](int index){
    if(this->championshipsYears == NULL)
        throw std::runtime_error("No championships");
    if(index < 0 || index > this->championshipsNumber)
        throw std::runtime_error("invalid index");
    return this->championshipsYears[index];
}

std::string Team::toString() const{
    std::string temp = this->teamName;
    temp += ", number of championships: " + std::to_string(this->championshipsNumber);
    temp += ", years the championship has been won:";
    for(int i = 0; i < this->championshipsNumber; ++i)
        temp += " " + std::to_string(this->championshipsYears[i]);
    temp += ", points: " + std::to_string(this->points);
    temp += ", race wins: " + std::to_string(raceWins);
    if(!drivers.empty())
    {
        temp += ", drivers:";
        for(auto driver: drivers)
            temp += " " + driver->getDriverName();
    }
    return temp;
}

Team::operator std::string(){
    return this->toString();
}

Team::operator std::string()const{
    return this->toString();
}

Team Driver::operator+(const Team& team){
    Team temp(team);
    bool duplicate = false;
    for(int i = 0; i < temp.getDrivers().size(); ++i)
        if(this->getDriverId() == temp.drivers[i]->getDriverId())
            duplicate = true;
    if(duplicate == false)
        temp.drivers.push_back(&(*this));
    return temp;
}

void clear_screen(char fill = ' ') { 
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);   
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

class Race{
    static int raceCount;
    const int raceId;

    int laps;
    std::vector<Driver*> driverList;
    Driver* winner;

public:
    static int getRaceCount(){return Race::raceCount;}
    const int getRaceId() const{return this->raceId;}
    int getLaps() const{return this->laps;}
    std::vector<Driver*> getDriverList() const{return this->driverList;}
    const Driver* getWinner() const{return this->winner;}

    void setLaps(int laps){this->laps = laps;}
    void setDriverList(std::vector<Driver*> driverList){this->driverList = driverList;}
    bool addDriver(Driver* driver){if(std::find(this->driverList.begin(), this->driverList.end(), driver) != this->driverList.end() || driver == nullptr) return false; 
                                    else this->driverList.push_back(driver); return true;}
    void setWinner(Driver* winner);
    bool removeDriver(Driver* driver);

    bool startRace();
    void printRace();

    Race();
    Race(int laps, std::vector<Driver*> driverList);
    Race(int laps, std::vector<Driver*> driverList, Driver* winner);
    Race(const Race& obj);
    Race& operator=(const Race& obj);
    ~Race();

    friend std::istream& operator>>(std::istream& in, Race& obj);
    friend std::ostream& operator<<(std::ostream& out, const Race& obj);
    Race operator+(int laps);
    friend Race operator+(int laps, Race obj);
    Race operator-(int laps);
    friend Race operator-(int laps, Race obj);
    Race operator+(Driver& obj);
    friend Race Driver::operator+(const Race& race);
    Race& operator++();
    Race operator++(int);
    Race& operator--();
    Race operator--(int);
    bool operator<(const Race& obj) const;
    bool operator<=(const Race& obj) const;
    bool operator>(const Race& obj) const;
    bool operator>=(const Race& obj) const;
    bool operator==(const Race& obj);
    Driver* operator[](int);

    std::string toString() const;
    operator std::string();
    operator std::string() const;
};

int Race::raceCount = 1000000;

void Race::setWinner(Driver* winner){
    if(std::find(this->driverList.begin(), this->driverList.end(), winner) != this->driverList.end())
        this->winner = winner;
    else this->winner = nullptr;
}

bool Race::removeDriver(Driver* driver){
    for(int i = 0; i < this->driverList.size(); ++i)
        if(this->driverList[i] == driver)
        {
            this->driverList.erase(std::remove(this->driverList.begin(), this->driverList.end(), driver), this->driverList.end());
            return true;
        }
    return false;
}

std::string putBlank(std::string temp)
{
    for(int i = 0; i < rand()%5+1; ++i)
        temp += " ";
    return temp;
}

std::string addSpaces(std::string obj, int count){
    std::string temp = "";
    for(int i = 0; i < count; i++)
        temp += " ";
    temp += obj;
    return temp;
}

void Race::printRace(){
    int max = 0;
    for(int i = 0; i < this->driverList.size(); ++i){
        if(this->driverList[i]->getDriverName().length() > max)
            max = this->driverList[i]->getDriverName().length();
    }
    for(int i = 0; i < this->driverList.size(); ++i){
        std::cout << addSpaces(this->driverList[i]->getDriverName(), max - this->driverList[i]->getDriverName().length()) << ":";
        std::cout << this->driverList[i]->getDistance() << "|-:o:>\n";
        this->driverList[i]->setDistance(putBlank(this->driverList[i]->getDistance()));
    }
}

bool Race::startRace(){
    if(this->driverList.size() < 2)
        return false;
    bool running = true;
    srand(time(NULL));
    while(running){
        clear_screen();
        this->printRace();
        Sleep(200);
        for(int i = 0; i < this->driverList.size(); ++i)
        {
            if(this->driverList[i]->getDistance().length() >= this->laps)
            {
                this->setWinner(this->driverList[i]);
                this->driverList[i]->setRaceWins(this->driverList[i]->getRaceWins() + 1);
                running = false;
            }
        }
    }
    for(int i = 0; i < this->driverList.size(); ++i)
        this->driverList[i]->setDistance("");
    return true;
}

Race::Race():raceId(raceCount++){
    this->laps = 0;
    this->driverList = {};
    this->winner = nullptr;
}

Race::Race(int laps, std::vector<Driver*> driverList):raceId(raceCount++){
    this->laps = laps;
    this->driverList = driverList;
    this->winner = nullptr;
}

Race::Race(int laps, std::vector<Driver*> driverList, Driver* winner):raceId(raceCount++){
    this->laps = laps;
    this->driverList = driverList;
    this->winner = winner;
}

Race::Race(const Race& obj):raceId(raceCount++){
    this->laps = obj.laps;
    this->driverList = obj.driverList;
    this->winner = obj.winner;
}

Race& Race::operator=(const Race& obj){
    if(this != &obj)
    {
        this->laps = obj.laps;
        this->driverList = obj.driverList;
        this->winner = obj.winner;
    }
    return *this;
}

Race::~Race(){
    this->driverList.clear();
    this->winner = nullptr;
}

std::istream& operator>>(std::istream& in, Race& obj)
{
    std::cout << "Enter number of laps: ";
    in >> obj.laps;
    obj.driverList = {};
    obj.winner = nullptr;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Race& obj)
{
    out << "Race id: " << obj.raceId << '\n';
    out << "Number of laps: " << obj.laps << '\n';
    if(!obj.driverList.empty())
    {
        out << "Drivers:\n";
        for(auto driver: obj.driverList)
            out << '\t' << driver->getDriverName() << '\n';
    }
    if(obj.winner != nullptr){
        out << "Winner: " << obj.winner->getDriverName();
    } else out << "Winner to be anounced!\n"; 
    return out;
}

Race Race::operator+(int laps){
    Race temp(*this);
    temp.laps = temp.laps + laps;
    return temp;
}

Race operator+(int laps, Race obj){
    Race temp(obj);
    temp.laps = temp.laps + laps;
    return temp;
}

Race Race::operator-(int laps){
    Race temp(*this);
    temp.laps = temp.laps - laps;
    return temp;
}

Race operator-(int laps, Race obj){
    Race temp(obj);
    temp.laps = temp.laps - laps;
    return temp;
}

Race Race::operator+(Driver& obj){
    Race temp(*this);
    bool duplicate = false;
    for(auto driver: this->driverList)
        if(driver->getDriverId() == obj.getDriverId())
            duplicate = true;
    if(duplicate == false)    
        temp.driverList.push_back(&obj);
    return temp;
}

Race Driver::operator+(const Race& race){
    Race temp(race);
    bool duplicate = false;
    for(auto driver: temp.driverList)
        if(driver->getDriverId() == this->driverId)
            duplicate = true;
    if(duplicate == false)    
        temp.driverList.push_back(&(*this));
    return temp;
}

Race& Race::operator++(){
    this->laps++;
    return *this;
}

Race Race::operator++(int laps){
    Race temp(*this);
    this->laps++;
    return temp;
}


Race& Race::operator--(){
    this->laps--;
    return *this;
}

Race Race::operator--(int laps){
    Race temp(*this);
    this->laps--;
    return temp;
}

bool Race::operator<(const Race& obj) const{
    return this->laps < obj.laps;
}

bool Race::operator<=(const Race& obj) const{
    return this->laps <= obj.laps;
}

bool Race::operator>(const Race& obj) const{
    return this->laps > obj.laps;
}

bool Race::operator>=(const Race& obj) const{
    return this->laps >= obj.laps;
}

bool Race::operator==(const Race& obj){
    return this->laps == obj.laps;
}

Driver* Race::operator[](int index)
{    if(this->driverList.empty())
        throw std::runtime_error("No drivers found!");
    else{
        if(index < 0 || index >= this->driverList.size())
            throw std::runtime_error("Invalid index");
        return this->driverList[index];}
}

std::string Race::toString() const{
    std::string temp = "Number of laps: " + std::to_string(this->laps);
    if(!this->driverList.empty()){
        temp += "\nDrivers:\n";
        for(auto driver: this->driverList)
            temp += "\t" + driver->getDriverName();
    }
    if(this->winner != nullptr)
        temp += "\nWinner: " + this->winner->getDriverName();
    return temp;
}

Race::operator std::string(){
    return this->toString();
}

Race::operator std::string() const{
    return this->toString();
}

class Menu{
    std::deque<Driver> drivers;
    std::deque<Car> cars;
    std::deque<Team> teams;
    Race race;
    bool raceStart = false;
    bool loadedData = false;
public:
    void run();

    Car* getCar(int id);
    Driver* getDriver(int id);
    Team* getTeam(int id);

    void driverMenu();
    void carMenu();
    void teamMenu();
    void raceMenu();

    void editCar(int id);
    void editDriver(int id);
    void editTeam(int id);
    void editRace(int id);

    bool removeCar(int id);
    bool removeDriver(int id);
    bool removeTeam(int id);
};

Car* Menu::getCar(int id){
    Car* car = nullptr;
    for(int i = 0; i < this->cars.size(); ++i)
        if(this->cars[i].getCarId() == id)
        {    
            car = &(this->cars[i]);
            break;
        }
    return car;
}

Driver* Menu::getDriver(int id){
    Driver* driver = nullptr;
    for(int i = 0; i < this->drivers.size(); ++i)
        if(this->drivers[i].getDriverId() == id)
        {    
            driver = &(this->drivers[i]);
            break;
        }
    return driver;
}

Team* Menu::getTeam(int id){
    Team* team = nullptr;
    for(int i = 0; i < this->teams.size(); ++i)
        if(this->teams[i].getIdTeam() == id)
        {    
            team = &(this->teams[i]);
            break;
        }
    return team;
}

bool Menu::removeCar(int id)
{
    for(int i = 0; i < this->cars.size(); ++i)
        if(this->cars[i].getCarId() == id)
        {   
            if(this->cars[i].getTaken() == 1)
            {
                for(int j = 0; j < this->drivers.size(); ++j)
                    if(this->drivers[j].getCar() == this->getCar(id))
                        this->drivers[j].setCar(nullptr);
            }
            this->cars.erase(this->cars.begin() + i);
            return true;
        }
    return false;
}

bool Menu::removeDriver(int id){
    for(int i = 0; i < this->drivers.size(); ++i)
        if(this->drivers[i].getDriverId() == id)
        {
            for(int j = 0; j < this->teams.size(); ++j)
                for(int k = 0; k < this->teams[j].getDrivers().size(); ++k)
                    if(this->teams[j].getDrivers()[k] == getDriver(id))
                        this->teams[j].getDrivers()[k] = nullptr;

            if(this->drivers[i].getCar() != nullptr)
                if(this->drivers[i].getCar()->getTaken() == 1)
                    for(int j = 0; j < this->cars.size(); ++j)
                        if(this->drivers[i].getCar() == &this->cars[j])
                            this->cars[j].setTaken(0);
            this->drivers.erase(this->drivers.begin() + i);
            return true;
        }
    return false;
}

bool Menu::removeTeam(int id){
    for(int i = 0; i < this->teams.size(); ++i)
        if(this->teams[i].getIdTeam() == id)
        {    
            this->teams.erase(this->teams.begin() + i);
            return true;
        }
    return false;
}

void Menu::run(){
    int command;
    bool running = true;
    clear_screen();
    // this->defaultData();
    while(running){
        std::cout << "0 - Exit\n";
        std::cout << "1 - Car menu\n";
        std::cout << "2 - Driver menu\n";
        std::cout << "3 - Team menu\n";
        std::cout << "4 - Race menu\n";
        std::cout << "Command: ";
        std::cin >> command;
        switch(command){
            case 0:{
                clear_screen();
                running = false;
                std::cout << "Bye! See ya!!!\n";
                break;
            }
            case 1:{
                clear_screen();
                this->carMenu();
                break;
            }
            case 2:{
                clear_screen();
                this->driverMenu();
                break;
            }
            case 3:{
                clear_screen();
                this->teamMenu();
                break;
            }
            case 4:{
                clear_screen();
                this->raceMenu();
                break;
            }
            default:{
                std::cout << "Invalid command!\n";
                break;
            }
            
        }
    }
}

void Menu::carMenu(){
    int command;
    bool running = true;
    while(running){
        std::cout << "0 - Back\n";
        std::cout << "1 - Add car\n";
        std::cout << "2 - Edit car(by ID)\n";
        std::cout << "3 - Print all cars\n";
        std::cout << "4 - Print car(by ID)\n";
        std::cout << "Command: ";
        std::cin >> command;
        switch(command){
            case 0:{
                clear_screen();
                running = false;
                break;
            }
            case 1:{
                Car car;
                clear_screen();
                std::cin >> car;
                this->cars.push_back(car);
                clear_screen();
                std::cout << "Car has been added!\n";
                break;
            }
            case 2:{
                clear_screen();
                for(int i = 0; i < this->cars.size(); ++i)
                    std::cout << this->cars[i].getCarName() << " - " << this->cars[i].getCarId() << "\n";
                int id;
                std::cout << "Id = ";
                std::cin >> id;
                clear_screen();
                if(getCar(id) != nullptr)
                    this->editCar(id);
                else std::cout << "INVALID ID\n";
                break;
            }
            case 3:{
                clear_screen();
                if(this->cars.size() == 0)
                    std::cout << "No cars yet!\n";
                else{
                for(int i = 0; i < this->cars.size(); ++i)
                    std::cout << this->cars[i] << '\n' << '\n';
                }
                break;
            }
            case 4:{
                clear_screen();
                for(int i = 0; i < this->cars.size(); ++i)
                    std::cout << this->cars[i].getCarName() << " - " << this->cars[i].getCarId() << "\n";
                int id;
                std::cout << "Id = ";
                std::cin >> id;
                clear_screen();
                if(getCar(id) != nullptr)
                    std::cout << *getCar(id) << '\n';
                else
                    std::cout << "Invalid ID!\n";
                std::cout << '\n';
                break;
            }
            default:{
                std::cout << "Invalid command!\n";
                break;
            }
            
        }
    }
}

void Menu::editCar(int id)
{
    int command;
    bool running = true;
    Car* car = this->getCar(id);
    while(running){
        std::cout << *(car) << '\n' << '\n';
        std::cout << "0 - Back\n";
        std::cout << "1 - Set brand name\n";
        std::cout << "2 - Set model name\n";
        std::cout << "3 - Set release date(Year)\n";
        std::cout << "4 - Set top speed(Km/h)\n";
        std::cout << "9 - Delete\n";
        std::cout << "Command: ";
        std::cin >> command;
        switch(command){
            case 0:{
                clear_screen();
                running = false;
                break;
            }
            case 1:{
                clear_screen();
                std::cout << "Enter new brand name: ";
                std::string brand;
                std::cin.get();
                getline(std::cin, brand);
                clear_screen();
                car->setBrand(brand);
                break;
            }
            case 2:{
                clear_screen();
                std::cout << "Enter new model name: ";
                char model[200];
                std::cin.get();
                std::cin.getline(model, 200);
                car->setModel(model);
                clear_screen();
                std::cout << "Model has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 3:{
                clear_screen();
                std::cout << "Enter new release year: ";
                int year;
                std::cin >> year;
                car->setReleaseDate(year);
                clear_screen();
                std::cout << "Release year has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 4:{
                clear_screen();
                std::cout << "Enter new top speed: ";
                int speed;
                std::cin >> speed;
                car->setTopSpeed(speed);
                clear_screen();
                std::cout << "Top speed has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 9:{
                clear_screen();
                std::cout << (this->removeCar(id) ? "Car has been removed succesfully\n" : "Invalid ID!\n") << '\n';
                running = false;
                break;
            }
            default:{
                std::cout << "Invalid command!\n";
                std::cout << '\n';
                break;
            }
            
        }
    }
}

void Menu::driverMenu(){
    int command;
    bool running = true;
    while(running){
        std::cout << "0 - Back\n";
        std::cout << "1 - Add driver\n";
        std::cout << "2 - Edit driver(by ID)\n";
        std::cout << "3 - Print all drivers\n";
        std::cout << "4 - Print driver(by ID)\n";
        std::cout << "5 - Read full stats for driver\n";
        std::cout << "Command: ";
        std::cin >> command;
        switch(command){
            case 0:{
                clear_screen();
                running = false;
                break;
            }
            case 1:{
                clear_screen();
                std::cout << "Enter driver's name: ";
                std::string name;
                std::cin.get();
                getline(std::cin, name);
                clear_screen();
                Driver temp;
                temp.setName(name);
                this->drivers.push_back(temp);
                std::cout << "Driver has been added!\n";
                std::cout << '\n';
                break;
            }
            case 2:{
                clear_screen();
                for(int i = 0; i < this->drivers.size(); ++i)
                    std::cout << this->drivers[i].getDriverName() << " - " << this->drivers[i].getDriverId() << "\n";
                int id;
                std::cout << "Id = ";
                std::cin >> id;
                clear_screen();
                if(getDriver(id) != nullptr)
                    this->editDriver(id);
                else std::cout << "INVALID ID\n" << '\n';
                break;
            }
            case 3:{
                clear_screen();
                if(this->drivers.size() == 0)
                    std::cout << "No drivers yet!\n" << '\n';
                else{
                    for(int i = 0; i < this->drivers.size(); ++i)
                        std::cout << this->drivers[i] << '\n' << '\n';
                }
                break;
            }
            case 4:{
                clear_screen();
                for(int i = 0; i < this->drivers.size(); ++i)
                    std::cout << this->drivers[i].getDriverName() << " - " << this->drivers[i].getDriverId() << "\n";
                int id;
                std::cout << "Id = ";
                std::cin >> id;
                clear_screen();
                if(getDriver(id) != nullptr)
                    std::cout << *getDriver(id);
                else
                    std::cout << "Invalid ID!\n";
                std::cout << '\n' << '\n';
                break;
            }
            case 5:{
                Driver driver;
                clear_screen();
                std::cin >> driver;
                this->drivers.push_back(driver);
                clear_screen();
                std::cout << "Driver has been added!\n";
                std::cout << '\n';
                break;
            }
            default:{
                std::cout << "Invalid command!\n";
                break;
            }
            
        }
    }
}

void Menu::editDriver(int id)
{
    int command;
    bool running = true;
    Driver* driver = this->getDriver(id);
    while(running){
        std::cout << *(driver) << '\n' << '\n';
        std::cout << "0 - Back\n";
        std::cout << "1 - Set driver's name\n";
        std::cout << "2 - Set race wins\n";
        std::cout << "3 - Set podiums number\n";
        std::cout << "4 - Set points\n";
        std::cout << "5 - Set type\n";
        std::cout << "6 - Set championships\n";
        std::cout << "7 - Set car\n";
        std::cout << "9 - Delete\n";
        std::cout << "Command: ";
        std::cin >> command;
        switch(command){
            case 0:{
                clear_screen();
                running = false;
                break;
            }
            case 1:{
                clear_screen();
                std::cout << "Enter new driver's name: ";
                std::string driverName;
                std::cin.get();
                getline(std::cin, driverName);
                clear_screen();
                driver->setName(driverName);
                break;
            }
            case 2:{
                clear_screen();
                std::cout << "Enter new number of race wins: ";
                int raceWins;
                std::cin >> raceWins;
                driver->setRaceWins(raceWins);
                clear_screen();
                std::cout << "Number of race wins has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 3:{
                clear_screen();
                std::cout << "Enter new podiums number: ";
                int podiumsNumber;
                std::cin >> podiumsNumber;
                driver->setPodiumsNumber(podiumsNumber);
                clear_screen();
                std::cout << "Number of podiums has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 4:{
                clear_screen();
                std::cout << "Enter new points: ";
                int points;
                std::cin >> points;
                driver->setPoints(points);
                clear_screen();
                std::cout << "Number of points has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 5:{
                clear_screen();
                std::cout << "Enter new type(P - Primary, R - Reserve, U - Unknown): ";
                char type;
                std::cin >> type;
                driver->setType(type);
                clear_screen();
                std::cout << "The type has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 6:{
                clear_screen();
                std::cout << "Enter new number of championships: ";
                int championshipsNumber, championshipsYears[100];
                std::cin >> championshipsNumber;
                std::cout << "Enter years that the championship has been won:\n";
                for(int i = 0; i < championshipsNumber; i++)
                    std::cin >> championshipsYears[i];
                driver->setChampionships(championshipsNumber, championshipsYears);
                clear_screen();
                std::cout << "Championships have been updated!\n";
                std::cout << '\n';
                break;
            }
            
            case 7:{
                clear_screen();
                std::cout << "Select a car for the driver to have:\n";
                for(int i = 0; i < this->cars.size(); ++i)
                    if(this->cars[i].getTaken() == false)
                        std::cout << '\t' << this->cars[i].getCarName() << " - " << this->cars[i].getCarId() << "\n";
                std::cout << "Id car: ";
                int idCar;
                std::cin >> idCar;
                driver->setCar(getCar(idCar));
                clear_screen();
                std::cout << "Car has been updated!\n";
                std::cout << '\n';
                break;
            }

            case 9:{
                clear_screen();
                if(this->removeDriver(id) == false)
                    std::cout << "Invalid ID!\n" << '\n';
                else
                std::cout << "Driver has been removed succesfully!\n" << '\n';
                running = false;
                break;
            }
            default:{
                std::cout << "Invalid command!\n";
                std::cout << '\n';
                break;
            }
            
        }
    }
}

void Menu::teamMenu(){
    int command;
    bool running = true;
    while(running){
        std::cout << "0 - Back\n";
        std::cout << "1 - Add team\n";
        std::cout << "2 - Edit team(by ID)\n";
        std::cout << "3 - Print all teams\n";
        std::cout << "4 - Print team(by ID)\n";
        std::cout << "Command: ";
        std::cin >> command;
        switch(command){
            case 0:{
                clear_screen();
                running = false;
                break;
            }
            case 1:{
                Team team; 
                clear_screen();
                std::cin >> team;
                this->teams.push_back(team);
                clear_screen();
                std::cout << "Team has been added!\n";
                std::cout << '\n';
                break;
            }
            case 2:{
                clear_screen();
                for(int i = 0; i < this->teams.size(); ++i)
                    std::cout << this->teams[i].getTeamName() << " - " << this->teams[i].getIdTeam() << "\n";
                int id;
                std::cout << "Id = ";
                std::cin >> id;
                clear_screen();
                if(getTeam(id) != nullptr)
                    this->editTeam(id);
                else std::cout << "INVALID ID\n" << '\n';
                break;
            }
            case 3:{
                clear_screen();
                if(this->teams.size() == 0)
                    std::cout << "No teams yet!\n" << '\n';
                else{
                    for(int i = 0; i < this->teams.size(); ++i)
                        std::cout << this->teams[i] << '\n' << '\n';
                }
                break;
            }
            case 4:{
                clear_screen();
                for(int i = 0; i < this->teams.size(); ++i)
                    std::cout << this->teams[i].getTeamName() << " - " << this->teams[i].getIdTeam() << "\n";
                int id;
                std::cout << "Id = ";
                std::cin >> id;
                clear_screen();
                if(getTeam(id) != nullptr)
                    std::cout << *getTeam(id) << '\n';
                else
                    std::cout << "Invalid ID!\n";
                std::cout << '\n';
                break;
            }
            default:{
                std::cout << "Invalid command!\n";
                std::cout << '\n';
                break;
            }
            
        }
    }
}

void Menu::editTeam(int id)
{
    int command;
    bool running = true;
    Team* team = this->getTeam(id);
    while(running){
        std::cout << *(team) << '\n' << '\n';
        std::cout << "0 - Back\n";
        std::cout << "1 - Set team's name\n";
        std::cout << "2 - Set race wins\n";
        std::cout << "3 - Set points\n";
        std::cout << "4 - Set championships\n";
        std::cout << "5 - Add driver\n";
        std::cout << "9 - Delete\n";
        std::cout << "Command: ";
        std::cin >> command;
        switch(command){
            case 0:{
                clear_screen();
                running = false;
                break;
            }
            case 1:{
                clear_screen();
                std::cout << "Enter new team name: ";
                char driverName[200];
                std::cin.get();
                std::cin.get(driverName, 200);
                team->setTeamName(driverName);
                clear_screen();
                std::cout << "Team name has been changed!\n";
                std::cout << '\n';
                break;
            }
            case 2:{
                clear_screen();
                std::cout << "Enter new number of race wins: ";
                int raceWins;
                std::cin >> raceWins;
                team->setRaceWins(raceWins);
                clear_screen();
                std::cout << "Number of race wins has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 3:{
                clear_screen();
                std::cout << "Enter new points: ";
                int points;
                std::cin >> points;
                team->setPoints(points);
                clear_screen();
                std::cout << "Number of points has been updated!\n";
                std::cout << '\n';
                break;
            }
            case 4:{
                clear_screen();
                std::cout << "Enter new number of championships: ";
                int championshipsNumber, championshipsYears[100];
                std::cin >> championshipsNumber;
                std::cout << "Enter years that the championship has been won:\n";
                for(int i = 0; i < championshipsNumber; i++)
                    std::cin >> championshipsYears[i];
                team->setChampionshipsYears(championshipsNumber, championshipsYears);
                clear_screen();
                std::cout << "Championships have been updated!\n";
                std::cout << '\n';
                break;
            }
            case 5:{
                clear_screen();
                std::cout << "Select a driver to add to the team:\n";
                for(int i = 0; i < this->drivers.size(); ++i)\
                    std::cout << '\t' << this->drivers[i].getDriverName() << " - " << this->drivers[i].getDriverId() << "\n";
                std::cout << "Id driver: ";
                int idDriver;
                std::cin >> idDriver;
                clear_screen();
                team->addDriver(getDriver(idDriver));
                std::cout << "Driver has been added!\n";
                std::cout << '\n';
                break;
            }
            case 9:{
                clear_screen();
                if(this->removeTeam(id) == false)
                    std::cout << "Invalid ID!\n" << '\n';
                else
                std::cout << "Team has been removed succesfully!\n" << '\n';
                running = false;
                break;
            }
            default:{
                std::cout << "Invalid command!\n";
                std::cout << '\n';
                break;
            }
            
        }
    }
}

void Menu::raceMenu()
{
    bool running = true;
    int command;
    while(running)
    {
        std::cout << "0 - Back\n";
        std::cout << "1 - Initiate race\n";
        std::cout << "2 - Add driver(by ID)\n";
        std::cout << "3 - Remove driver(by ID)\n";
        std::cout << "4 - Print drivers\n";
        std::cout << "5 - Print race settings\n";
        std::cout << "6 - Edit number of laps\n";
        std::cout << "7 - Start race\n";
        std::cout << "Command: ";
        std::cin >> command;
        switch(command){
            case 0:{
                clear_screen();
                Race temp;
                this->race = temp;
                running = false;
                break;
            }
            case 1:{
                clear_screen();
                this->race.setLaps(200);
                std::cout << "Race has been initialized!\n";
                std::cout << '\n';
                break;
            }
            case 2:{
                clear_screen();
                for(int i = 0; i < this->drivers.size(); ++i)
                    std::cout << this->drivers[i].getDriverName() << " - " << this->drivers[i].getDriverId() << "\n";
                int id;
                std::cout << "Id = ";
                std::cin >> id;
                clear_screen();
                if(getDriver(id) != nullptr){
                    this->race.addDriver(getDriver(id));
                    std::cout << "Driver has been added!\n";
                }
                else std::cout << "INVALID ID\n";
                std::cout << '\n';
                break;
            }
            case 3:{
                clear_screen();
                for(int i = 0; i < this->drivers.size(); ++i)
                    std::cout << this->drivers[i].getDriverName() << " - " << this->drivers[i].getDriverId() << "\n";
                int id;
                std::cout << "Id = ";
                std::cin >> id;
                clear_screen();
                if(getDriver(id) != nullptr)
                    (this->race.removeDriver(getDriver(id))) ? std::cout << "Driver has been removed\n" : std::cout << "Driver has not been found\n";
                else std::cout << "INVALID ID\n";
                std::cout << '\n';
                break;
            }
            case 4:{
                clear_screen();
                for(int i = 0; i < this->race.getDriverList().size(); ++i)
                    std::cout << this->race.getDriverList()[i]->getDriverName() << '\n'; 
                std::cout << '\n';
                break;
            }
            case 5:{
                clear_screen();
                std::cout << this->race << '\n';
                std::cout << '\n';
                break;
            }
            case 6:{
                clear_screen();
                std::cout << "Enter new number of laps: ";
                int laps;
                std::cin >> laps;
                this->race.setLaps(laps);
                clear_screen();
                std::cout << "Number of laps has been changed!\n";
                std::cout << '\n';
                break;
            }
            case 7:{
                clear_screen();
                this->race.startRace();
                clear_screen();
                std::cout << "The WINNER is: " << this->race.getWinner()->getDriverName() << "\n";
                std::cout << '\n';
                break;
            }
        }
    }
}

void TestTeam()
{
    Team first;
    char model[] = "Performance";
    char brand1[] = "Mercedes AMG", brand2[] = "Red Bull", brand3[] = "Aston Martin";
    std::string driverName1 = "Max Verstappen", driverName2 = "Lewis Hamilton", driverName3 = "Sergio Perez", driverName4 = "Lance Stroll";
        Car temp1(brand1, model, 2023, 420);
    Car temp2(brand2, model, 2000, 200);
    int years[] = {1998, 1999, 2000}, years1[] = {2004, 2007}, years2[] = {2000, 2017};
    Driver driver1(driverName1, 10, 12, 34.2, 'P', 2, years1, &temp1);
    Driver driver2(driverName2, 3, 3, 40, 'P', 2, years2, &temp2);
    Driver driver3(driverName3, 0, 2, 40, 'P', 3, years, &temp2);
    Team team1(brand2, 3, years, 42, 2, {&driver1}), team2(brand3, 2, years2, 60, 3, {&driver2});
    team1 = team1 + driver3;
    // team1 = driver3 + team1;
    // first = team1 + team2;
    std::cout << team1;
    // Team c(b), d, e(brand1, 0, years3, 15, 1), f;
    // std::cin >> d;
    // Team temp;
    // temp = team1 + team2;
    // std::cout << temp;
    // b.setBudget(2140);
    // b.setRaceWins(199);
    // std::cout << b;
}

void TestDriver()
{
    Driver a;
    // std::cout << a;
    int years[] ={2000, 2002, 2012}, years2[] = {2018, 2019};
    char name[] = "Performance";
    Car b("Mercedes AMG", name, 2023, 420);
    Car p("Audi", name, 2000, 200);
    Car *d;
    std::string lol = "Max Verstappen", pol = "Lewis Hamilton";
    int yea[] = {2020, 2021};
    Driver h(lol, 10, 12, 34.2, 'P', 2, yea, &b);
    Driver L(pol,  3, 3, 40, 'P', 2, years2, &p);
    h = p + h;
    std::cout << h;
    // std::cout << h+L;
    // std::cout << p.getCarId();
    // std::cin >> a; 
    // std::cout << a;
}

void TestCar()
{
    char model[] = "Aventor", model2[] = "TT Coupe";
    Car a,b("Lamborghini", model, 2000, 320);
    Car c("Audi", model2, 2012, 260), d;
    std::cout << a << b << c;
    // d = b+c;
    // int lro = d;
    // bool lro2 = d;
    // std :: cin >> d;
    // d.setModel(model);
    std::cout << b.getCarName();
}

void TestRace()
{
    char brand1[] = "Mercedes AMG", brand2[] = "Red Bull", brand3[] = "Aston Martin";
    int yea[] = {2020, 2021}, years[] ={2000, 2002, 2012}, years2[] = {2018, 2019};
    char name[] = "Performance";
    Car b("Mercedes AMG", name, 2023, 420);
    Car p("Audi", name, 2000, 200);   
    std::string lol = "Max Verstappen", pol = "Lewis Hamilton";
    Driver driver1(lol, 10, 12, 34.2, 'P', 2, yea, &b);
    Driver driver2(pol,  3, 3, 40, 'P', 2, years2, &p);
    Team team1(brand2, 3, years, 42, 2, {&driver1}), team2(brand3, 2, years2, 60, 3, {&driver2});
    Race race1(42, {&driver1});
    race1 = driver2 + race1;
    // race1.setWinner(&driver2);
    std::cout << race1;
}

int main()
{
    // TestCar();
    Menu menu;
    menu.run();
}
/*
class Track
{
    static int trackId;
    const int trackCount;

    char* name;
    float length;
    int cornersNumber;
    std::string surface;
    int laps;

    public:
        static int getTrackId(){return Track::trackId;}
        const char* getName(){return this->name;}
        const float getLength(){return this->length;}
        const int getCornersNumber(){return this->cornersNumber;}
        const std::string& getSurface(){return this->surface;}
        void setName(const char* name){this->name = new char[strlen(name) + 1];
                                       strcpy(this->name, name);}
        void setLength(const int length){this->length = length;}
        void setCornersNumber(const int cornersNumber){this->cornersNumber = cornersNumber;}                                       
        void setSurface(const std::string& surface){this->surface = surface;}
        void setLaps(const int laps){this->laps = laps;}        
        Track();
        Track(char* name, float length, int cornersNumber, std::string surface, int laps);
        Track(const Track& obj);
        ~Track();
        Track& operator =(const Track& obj);
        friend std::ostream& operator << (std::ostream& out, const Track& obj);
        friend std::istream& operator >>(std::istream& in, Track& obj); 
};

int Track::trackId = 100000;

Track::Track():trackCount(trackId++)
{
    this->name = new char[strlen("Unknown")+1];
    strcpy(this->name,"Unknown");
    this->length = 0;
    this->cornersNumber = 0;
    this->surface = "Unknown";
    this->laps = 0;
}

Track::Track(char* name, float length, int cornersNumber, std::string surface, int laps):trackCount(trackId++)
{
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
    this->length = length;
    this->cornersNumber = cornersNumber;
    this->surface = surface;
    this->laps = laps;
}

Track::Track(const Track& obj):trackCount(trackId++)
{
    this->name = new char[strlen(obj.name)+1];
    strcpy(this->name, obj.name);
    this->length = obj.length;
    this->cornersNumber = obj.cornersNumber;
    this->surface = obj.surface;
    this->laps = obj.laps;
}

Track::~Track()
{
    if(this->name != NULL)
    {
        delete[] this->name;
        this->name = NULL;
    }
}

Track& Track::operator=(const Track& obj)
{
    if(this != &obj)
    {
        if(this->name != NULL)
        {
            delete[] this->name;
            this->name = NULL;
        }
        this->name = new char[strlen(obj.name)+1];
        strcpy(this->name, obj.name);
        this->length = obj.length;
        this->cornersNumber = obj.cornersNumber;
        this->surface = obj.surface;
        this->laps = obj.laps;
    }
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Track& track)
{
    out << "Track name: " << track.name << '\n';
    out << "Track length: " << track.length << '\n';
    out << "Number of corners: " << track.cornersNumber << '\n';
    out << "Type of surface: " << track.surface << '\n';
    out << "Number of laps: " << track.laps << '\n';
    return out;
}

std::istream& operator >>(std::istream& in, Track& track)
{
    std::cout << "Enter track name: ";
    track.name = new char[100];
    in.get(track.name, 100);
    std::cout << "Enter track length: ";
    in >> track.length;
    std::cout << "Enter track's number of corners: ";
    in >> track.cornersNumber;
    std::cout << "Enter track's type of surface: ";
    in.get();
    getline(in, track.surface);
    std::cout << "Enter track's number of laps: ";
    in >> track.laps;
    return in;
}
*/
