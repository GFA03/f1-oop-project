#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <string.h>
/// NU UITA SA BAGI SI BOOL

class Driver;
class Team{

        const int teamCount;
        static int idTeam;
        char *teamName;
        int championshipsNumber;
        int* championshipsYears;
        float points;
        double budget;
        int raceWins;
        // std::vector<Driver> drivers;
    public:
        static int getIdTeam(){return Team::idTeam;}
        const char* getTeamName(){return this->teamName;}
        const int* getChampionshipsYears(){return this->championshipsYears;}
        const float getPoints(){return this->points;}
        void setPoints(float points){this -> points = points;}
        void setBudget(double budget){this -> budget = budget;}
        void setRaceWins(int raceWins){this -> raceWins = raceWins;}
        // std::vector<Driver> getDrivers(){return this->drivers;} PANA DEFINESC CLASA DRIVERS LE LAS COMENTATE
        Team();
        Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, double budget, int raceWins);
        // Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, double budget, int raceWins, const std::vector<Driver>& drivers);
        Team(const Team& obj);
        ~Team();
        Team& operator =(const Team& obj);
        friend std::ostream& operator <<(std::ostream& out, const Team& team);
        friend std::istream& operator >>(std::istream& in, Team& team);
};
int Team::idTeam = 1000;

Team::Team():teamCount(idTeam++){
    teamName = new char[strlen("Unknown") + 1];
    strcpy(teamName, "Unknown");
    championshipsNumber = 0;
    championshipsYears = nullptr;
    points = 0;
    budget = 0;
    raceWins = 0;
}

Team::Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, double budget, int raceWins):teamCount(idTeam++){
    this -> teamName = new char[strlen(teamName) + 1];
    strcpy(this -> teamName, teamName);
    this -> championshipsNumber = championshipsNumber;
    this -> championshipsYears = new int[championshipsNumber];
    for(int i = 0; i < championshipsNumber; i++)
        this -> championshipsYears[i] = championshipsYears[i];
    this -> points = points;
    this -> budget = budget;
    this -> raceWins = raceWins;
}

/*Team::Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, double budget, int raceWins, const std::vector<Driver>& drivers):teamCount(idTeam++)
{
    this -> teamName = new char[strlen(teamName) + 1];
    strcpy(this -> teamName, teamName);
    this -> championshipsNumber = championshipsNumber;
    this -> championshipsYears = new int[championshipsNumber];
    for(int i = 0; i < championshipsNumber; i++)
        this -> championshipsYears[i] = championshipsYears[i];
    this -> points = points;
    this -> budget = budget;
    this -> raceWins = raceWins;
    this -> drivers = drivers;
}*/

Team::Team(const Team& obj):teamCount(idTeam++){
    this -> teamName = new char[strlen(obj.teamName) + 1];
    strcpy(this -> teamName, obj.teamName);
    this -> championshipsNumber = obj.championshipsNumber;
    this -> championshipsYears = new int[obj.championshipsNumber];
    for(int i = 0; i < obj.championshipsNumber; i++)
        this -> championshipsYears[i] = obj.championshipsYears[i];
    this -> points = obj.points;
    this -> budget = obj.budget;
    this -> raceWins = obj.raceWins;
    // this -> drivers = obj.drivers;
}

Team::~Team(){
    if(this -> teamName != NULL)
    {
        delete[] this -> teamName;
        this -> teamName = NULL;
    }
    if(this -> championshipsYears != NULL)
    {
        delete[] this -> championshipsYears;
        this -> championshipsYears = NULL;
    }
}

Team& Team::operator =(const Team& obj){
    if(this != &obj){
        if(this -> teamName != NULL)
        {
            delete[] this -> teamName;
            this -> teamName = NULL;
        }
        if(this -> championshipsYears != NULL)
        {
            delete[] this -> championshipsYears;
            this -> championshipsYears = NULL;
        }
        this -> teamName = new char[strlen(obj.teamName) + 1];
        strcpy(this -> teamName, obj.teamName);
        this -> championshipsNumber = obj.championshipsNumber;
        this -> championshipsYears = new int[obj.championshipsNumber];
        for(int i = 0; i < obj.championshipsNumber; i++)
            this -> championshipsYears[i] = obj.championshipsYears[i];
        this -> points = obj.points;
        this -> budget = obj.budget;
        this -> raceWins = obj.raceWins;
        // this -> drivers = obj.drivers;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Team& team)
{
    out << "Team id: " << team.idTeam << '\n';
    out << "Team name: " << team.teamName << "\n";
    out << "Team points: " << team.points << "\n";
    out << "Team budget: " << team.budget << "\n";
    out << "Team raceWins: " << team.raceWins << "\n";
    out << "Championships: " << team.championshipsNumber << "\n";
    if(team.championshipsNumber > 0)
    {   
        out << "Years that the championship has been won: ";
        for(int i = 0; i < team.championshipsNumber-1; ++i) out << team.championshipsYears[i] << ", ";
        out << team.championshipsYears[team.championshipsNumber-1] << '\n';
    }
    out << "\n";
    // out << "Drivers: " << team.drivers << "\n";
    return out;
}

std::istream& operator >>(std::istream& in, Team& team)
{
    std::cout << "Team name: ";
    char aux[100];
    in.get(aux, 100);
    if(team.teamName != NULL)
    {
        delete[] team.teamName;
    }
    if(team.championshipsYears != NULL)
    {
        delete[] team.championshipsYears;
    }
    team.teamName = new char[strlen(aux) + 1];
    strcpy(team.teamName, aux);
    std::cout << "Team points: ";
    in >> team.points;
    std::cout << "Team budget: ";
    in >> team.budget;
    std::cout << "Race wins: ";
    in >> team.raceWins;
    std::cout << "Number of championships: ";
    in >> team.championshipsNumber;
    team.championshipsYears = new int[team.championshipsNumber];
    for(int i = 0; i < team.championshipsNumber; ++i)
    {
        std::cout << "Championship year: ";
        in >> team.championshipsYears[i];
    }
    // std::cout << "Drivers: ";
    // in >> team.drivers;
    std::cout << '\n';
    return in;
}

class Driver{
        static int driverId;
        const int driverCount;

        std::string name;
        std::string birthDate;
        int raceWins;
        int podiumsNumber;
        float points;
        int championshipsWon;
        int* championshipsYears;
        Team team;
    public:
        static int getDriverId(){return Driver::driverId;}
        const char* getDriverName(){return this -> name.c_str();}
        const int* getChampionshipsYears(){return this -> championshipsYears;}
        const float getPoints(){return this -> points;}
        const int getPodiumsNumber(){return this -> podiumsNumber;}
        void setPoints(float points){this -> points = points;}
        void setPodiumsNumber(int podiumsNumber){this -> podiumsNumber = podiumsNumber;}
        void setRaceWins(int raceWins){this -> raceWins = raceWins;}
        Driver();
        Driver(std::string name, std::string birthDate, int raceWins, int podiumsNumber, float points, int championshipsWon, int* championshipsYears);
        Driver(std::string name, std::string birthDate, int raceWins, int podiumsNumber, float points, int championshipsWon, int* championshipsYears,const Team& team);
        Driver(const Driver& obj);
        ~Driver();
        Driver& operator =(const Driver& obj);
        friend std::ostream& operator <<(std::ostream& out, const Driver& driver);
        friend std::istream& operator >>(std::istream& in, Driver& driver);
};

int Driver::driverId = 10;

Driver::Driver():driverCount(driverId++){
    this -> name = "Unknown";
    this -> birthDate = "Unknown";
    this -> raceWins = 0;
    this -> podiumsNumber = 0;
    this -> points = 0;
    this -> championshipsWon = 0;
    this -> championshipsYears = nullptr;
    this -> team = {};
}

Driver::Driver(std::string name, std::string birthDate, int raceWins, int podiumsNumber, float points, int championshipsWon, int* championshipsYears):driverCount(driverId++){
    this -> name = name;
    this -> birthDate = birthDate;
    this -> raceWins = raceWins;
    this -> podiumsNumber = podiumsNumber;
    this -> points = points;
    this -> championshipsWon = championshipsWon;
    this -> championshipsYears = new int[championshipsWon];
    for(int i = 0; i < championshipsWon; ++i)
        this -> championshipsYears[i] = championshipsYears[i];
}

Driver::Driver(std::string name, std::string birthDate, int raceWins, int podiumsNumber, float points, int championshipsWon, int* championshipsYears,const Team& team):driverCount(driverId++)
{
    this -> name = name;
    this -> birthDate = birthDate;
    this -> raceWins = raceWins;
    this -> podiumsNumber = podiumsNumber;
    this -> points = points;
    this -> championshipsWon = championshipsWon;
    this -> championshipsYears = new int[championshipsWon];
    for(int i = 0; i < championshipsWon; ++i)
        this -> championshipsYears[i] = championshipsYears[i];
    this -> team = team;
}

Driver::Driver(const Driver& obj):driverCount(driverId++)
{
    this -> name = obj.name;
    this -> birthDate = obj.birthDate;
    this -> raceWins = obj.raceWins;
    this -> podiumsNumber = obj.podiumsNumber;
    this -> points = obj.points;
    this -> championshipsWon = obj.championshipsWon;
    this -> championshipsYears = new int[obj.championshipsWon];
    for(int i = 0; i < obj.championshipsWon; ++i)
        this -> championshipsYears[i] = obj.championshipsYears[i];
    this -> team = obj.team;
}

Driver::~Driver()
{
    if(this -> championshipsYears != NULL)
    {
        delete[] this -> championshipsYears;
        this -> championshipsYears = NULL;
    }
}

Driver& Driver::operator =(const Driver& obj)
{
    if(this != &obj){
        if(this -> championshipsYears != NULL)
        {
            delete[] this -> championshipsYears;
            this -> championshipsYears = NULL;
        }
        this -> name = obj.name;
        this -> birthDate = obj.birthDate;
        this -> raceWins = obj.raceWins;
        this -> podiumsNumber = obj.podiumsNumber;
        this -> points = obj.points;
        this -> championshipsWon = obj.championshipsWon;
        this -> championshipsYears = new int[obj.championshipsWon];
        for(int i = 0; i < obj.championshipsWon; ++i)
            this -> championshipsYears[i] = obj.championshipsYears[i];
        this -> team = obj.team;
        // this -> drivers = obj.drivers;
    }
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Driver& driver)
{
    out << "Driver id: " << driver.driverId << '\n';
    out << "Driver name: " << driver.name << "\n";
    out << "Driver birth date: " << driver.birthDate << "\n";
    out << "Driver points: " << driver.points << "\n";
    out << "Driver raceWins: " << driver.raceWins << "\n";
    out << "Driver podiums: " << driver.podiumsNumber << '\n';
    out << "Championships: " << driver.championshipsWon << "\n";
    if(driver.championshipsWon > 0)
    {   
        out << "Years that the championship has been won: ";
        for(int i = 0; i < driver.championshipsWon-1; ++i) out << driver.championshipsYears[i] << ", ";
        out << driver.championshipsYears[driver.championshipsWon-1] << '\n';
    }
    out << "\n";
    // out << "Team: " << driver.team << "\n";
    return out;
}

std::istream& operator >>(std::istream& in, Driver& driver)
{
    if(driver.championshipsYears != NULL)
        delete[] driver.championshipsYears;
    std::cout << "Enter driver's name: ";
    getline(in, driver.name);
    std::cout << "Enter driver's birth date:";    
    getline(in, driver.birthDate);
    std::cout << "Enter driver's raceWins: ";
    in >> driver.raceWins;
    std::cout << "Enter driver's number of podiums: ";
    in >> driver.podiumsNumber;
    std::cout << "Enter driver's points: ";
    in >> driver.points;
    std::cout << "Enter driver's number of championships won: ";
    in >> driver.championshipsWon;
    driver.championshipsYears = new int[driver.championshipsWon];
    for(int i = 0; i < driver.championshipsWon; ++i)
        in >> driver.championshipsYears[i];
    // in >> driver.team;
    return in;
}

class Car{
    static int carId;
    const int carCount;

    std::string brand;
    char *model;
    int releaseDate;
    bool broken;
    float topSpeed;

    public:
        static int getCarId() { return Car::carId;}
        const char* getBrand() {return this -> brand.c_str();}
        const char* getModel() {return this -> model;}
        const int getReleaseDate() {return this -> releaseDate;}
        const bool getBroken() {return this -> broken;}
        const float getTopSpeed() {return this -> topSpeed;}
        void setBrand(const std::string& brand){this->brand = brand;}
        void setModel(char* model){this -> model = new char[strlen(model)+1];
                                   strcpy(this->model, model);}
        void setReleaseDate(const int releaseDate){this->releaseDate = releaseDate;}                 
        void setBroken(const bool broken){this->broken = broken;}
        void setTopSpeed(const float topSpeed){this->topSpeed = topSpeed;}
        Car();
        Car(std::string brand, char* model, int releaseDate, bool broken, float topSpeed);
        Car(const Car& obj);        
        ~Car();
        Car& operator=(const Car& obj);
        friend std::ostream& operator<<(std::ostream& out, const Car& obj);
        friend std::istream& operator>>(std::istream& in, Car& obj);
};

int Car::carId = 10000;

Car::Car():carCount(carId++)
{
    this -> brand = "Unknown";
    this -> model = new char[strlen("Unknown")+1];
    strcpy(this -> model, "Unknown");
    this -> releaseDate = 0;
    this -> broken = true;
    this -> topSpeed = 0;
}

Car::Car(std::string brand, char* model, int releaseDate, bool broken, float topSpeed):carCount(carId++)
{
    this -> brand = brand;
    this -> model = new char[strlen(model) + 1];
    strcpy(this -> model, model);
    this -> releaseDate = releaseDate;
    this -> broken = broken;
    this -> topSpeed = topSpeed;
}

Car::Car(const Car& obj):carCount(carId++)
{
    this -> brand = obj.brand;
    this -> model = new char[strlen(obj.model) + 1];
    strcpy(this -> model, obj.model);
    this -> releaseDate = obj.releaseDate;
    this -> broken = obj.broken;
    this -> topSpeed = obj.topSpeed;
}

Car::~Car()
{
    if(this -> model != nullptr)
    {
        delete[] this -> model;
        this -> model = nullptr;
    }
}

Car& Car::operator = (const Car& obj)
{
    if(this != &obj)
    {
        if(this -> model != nullptr)
        {
            delete[] this -> model;
            this -> model = nullptr;
        }
        this -> brand = obj.brand;
        this -> model = new char[strlen(obj.model) + 1];
        strcpy(this -> model, obj.model);
        this -> releaseDate = obj.releaseDate;
        this -> broken = obj.broken;
        this -> topSpeed = obj.topSpeed;
    }
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Car& car)
{
    out << "Car brand: " << car.brand << '\n';
    out << "Car model: " << car.model << '\n';
    out << "Car release date: " << car.releaseDate << '\n';
    out << "Car status: " << (car.broken ? "broken" : "not broken") << '\n';
    out << "Top speed: " << car.topSpeed << '\n';
    return out;
}

std::istream& operator >>(std::istream& in,Car& car)
{
    std::cout << "Enter car brand: ";
    getline(in, car.brand);
    car.model = new char[100];
    std::cout << "Enter car model: ";
    in.get(car.model, 100);
    std::cout << "Enter car release date: ";
    in >> car.releaseDate;
    std::cout << "Enter car's status *Broken*(True = 1, False = 0): ";
    in >> car.broken;
    std::cout << "Enter car's top speed: ";
    in >> car.topSpeed;
    return in;
}

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
        const char* getName(){return this -> name;}
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
    this -> name = new char[strlen("Unknown")+1];
    strcpy(this->name,"Unknown");
    this -> length = 0;
    this -> cornersNumber = 0;
    this -> surface = "Unknown";
    this -> laps = 0;
}

Track::Track(char* name, float length, int cornersNumber, std::string surface, int laps):trackCount(trackId++)
{
    this -> name = new char[strlen(name)+1];
    strcpy(this->name, name);
    this -> length = length;
    this -> cornersNumber = cornersNumber;
    this -> surface = surface;
    this -> laps = laps;
}

Track::Track(const Track& obj):trackCount(trackId++)
{
    this -> name = new char[strlen(obj.name)+1];
    strcpy(this->name, obj.name);
    this -> length = obj.length;
    this -> cornersNumber = obj.cornersNumber;
    this -> surface = obj.surface;
    this -> laps = obj.laps;
}

Track::~Track()
{
    if(this -> name != NULL)
    {
        delete[] this->name;
        this -> name = NULL;
    }
}

Track& Track::operator=(const Track& obj)
{
    if(this != &obj)
    {
        if(this -> name != NULL)
        {
            delete[] this->name;
            this -> name = NULL;
        }
        this -> name = new char[strlen(obj.name)+1];
        strcpy(this->name, obj.name);
        this -> length = obj.length;
        this -> cornersNumber = obj.cornersNumber;
        this -> surface = obj.surface;
        this -> laps = obj.laps;
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

void TestTeam()
{
    Team a;
    int years[] ={2000, 2002, 2012};
    char name[] = "Mercedes AMG";
    Team b(name, 3, years, 42, 13000000, 2);
    Team c(b), d;
    // std::cin >> d;
    std::cout << d.getIdTeam();
    // b.setBudget(2140);
    // b.setRaceWins(199);
    // std::cout << b;
}

void TestDriver()
{
    Driver a;
    // std::cout << a;
    int years[] ={2000, 2002, 2012};
    char name[] = "Mercedes AMG";
    Team b(name, 3, years, 42, 13000000, 2);
    std::string lol = "Max Verstappen";
    std::string date = "03/09/1988";
    int yea[] = {2020, 2021};
    Driver c(lol, date, 52, 79, 201, 2, yea, b);
    std::cin >> a; 
    std::cout << a;
}

void TestCar()
{
    char model[] = "Aventador";
    Car a,b("Lamborghini", model, 2012, false, 320);
    Car c(b),d;
    d = a;
    // std :: cin >> d;
    std::cout << b;
}

void TestTrack()
{
    char name[] = "Buircrsa";
    Track a,b(name, 56, 12, "Graphite", 58),c,d;
    std::cin >> d;
    std::cout << d;
}

int main()
{
    TestTrack();
}