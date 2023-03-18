#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

class Driver;
class Team{

        const int idTeam;
        static int teamCount;
        char *teamName;
        int championshipsNumber;
        int* championshipsYears;
        float points;
        int raceWins;
        // std::vector<Driver*> drivers;
    public:
        static int getTeamCount(){return Team::teamCount;}
        const int getIdTeam(){return this->idTeam;}
        const char* getTeamName(){return this->teamName;}
        const int getChampionshipsNumber(){return this->championshipsNumber;}
        const int* getChampionshipsYears() const{return this->championshipsYears;}
        const float getPoints(){return this->points;}
        const int getRaceWins(){return this->raceWins;}
        // std::vector<Driver> getDrivers(){return this->drivers;} PANA DEFINESC CLASA DRIVERS LE LAS COMENTATE
        void setTeamName(char *teamName){this->teamName = new char[strlen(teamName)+1]; strcpy(this->teamName, teamName);}
        void setChampionshipsYears(int championshipsNumber, int* championshipsYears);
        void setPoints(float points){this -> points = points;}
        void setRaceWins(int raceWins){this -> raceWins = raceWins;}
        // void setDrivers(std::vector<Driver> drivers){this->drivers = drivers;}
        
        Team();
        Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, int raceWins);
        // Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, double budget, int raceWins, const std::vector<Driver>& drivers);
        Team(const Team& obj);
        Team& operator =(const Team& obj);
        ~Team();

        friend std::ostream& operator <<(std::ostream& out, const Team& team);
        friend std::istream& operator >>(std::istream& in, Team& team);
        Team operator +(int);
        friend Team operator +(int, Team);
        Team operator +(const Team& obj); // concatenates the team names, adds the points, racewins and championshipsYears together
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
    teamName = new char[strlen("Unknown") + 1];
    strcpy(teamName, "Unknown");
    championshipsNumber = 0;
    championshipsYears = nullptr;
    points = 0;
    raceWins = 0;
}

Team::Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, int raceWins):idTeam(teamCount++){
    this -> teamName = new char[strlen(teamName) + 1];
    strcpy(this -> teamName, teamName);
    this -> championshipsNumber = championshipsNumber;
    this -> championshipsYears = new int[championshipsNumber];
    for(int i = 0; i < championshipsNumber; i++)
        this -> championshipsYears[i] = championshipsYears[i];
    this -> points = points;
    this -> raceWins = raceWins;
}

/*Team::Team(char* teamName, int championshipsNumber, int* championshipsYears, float points, int raceWins, const std::vector<Driver>& drivers):teamCount(idTeam++)
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

Team::Team(const Team& obj):idTeam(teamCount++){
    this -> teamName = new char[strlen(obj.teamName) + 1];
    strcpy(this -> teamName, obj.teamName);
    this -> championshipsNumber = obj.championshipsNumber;
    this -> championshipsYears = new int[obj.championshipsNumber];
    for(int i = 0; i < obj.championshipsNumber; i++)
        this -> championshipsYears[i] = obj.championshipsYears[i];
    this -> points = obj.points;
    this -> raceWins = obj.raceWins;
    // this -> drivers = obj.drivers;
}

Team::~Team(){
    teamCount--;
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
        this -> raceWins = obj.raceWins;
        // this -> drivers = obj.drivers;
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
    out << "\n";
    // out << "Drivers: " << team.drivers << "\n";
    return out;
}

std::istream& operator >>(std::istream& in, Team& team)
{
    std::cout << "Team name: ";
    char temp[100];
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
    std::cout << "Team points: ";
    in >> team.points;
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

Team Team::operator+(int points)
{
    Team temp(*this);
    temp.points = temp.points + points;
    return temp;
}

Team operator+(int points, Team obj)
{
    Team temp(obj);
    temp.points = temp.points + points;
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

int Team::operator [](int i){
    if(this->championshipsYears == NULL)
        throw std::runtime_error("No championships");
    if(i < 0 || i > this->championshipsNumber)
        throw std::runtime_error("invalid index");
    return this->championshipsYears[i];
}

std::string Team::toString() const{
    std::string temp = this->teamName;
    temp += " " + std::to_string(this->championshipsNumber);
    for(int i = 0; i < this->championshipsNumber; ++i)
        temp += " " + std::to_string(this->championshipsYears[i]);
    temp += " " + std::to_string(this->points);
    temp += " " + std::to_string(raceWins);
    return temp;
}

Team::operator std::string(){
    return this->toString();
}

Team::operator std::string()const{
    return this->toString();
}

class Car;

class Driver{
        static int driverCount;
        const int driverId;

        std::string name;
        int raceWins;
        int podiumsNumber;
        float points;
        int championshipsWon;
        int* championshipsYears;
        Car* car;
    public:
        static int getDriverCount(){return Driver::driverCount;}
        const int getDriverId(){return this->driverId;}
        const std::string getDriverName(){return this -> name;}
        const int* getChampionshipsYears(){return this -> championshipsYears;}
        const float getPoints(){return this -> points;}
        const int getPodiumsNumber(){return this -> podiumsNumber;}
        void setPoints(float points){this -> points = points;}
        void setPodiumsNumber(int podiumsNumber){this -> podiumsNumber = podiumsNumber;}
        void setRaceWins(int raceWins){this -> raceWins = raceWins;}
        Driver();
        Driver(std::string name, int raceWins, int podiumsNumber, float points, int championshipsWon, int* championshipsYears);
        Driver(std::string name, int raceWins, int podiumsNumber, float points, int championshipsWon, int* championshipsYears,Car* car);
        Driver(const Driver& obj);
        ~Driver();
        Driver& operator =(const Driver& obj);
        friend std::ostream& operator <<(std::ostream& out, const Driver& driver);
        friend std::istream& operator >>(std::istream& in, Driver& driver);
        Driver operator +(int);
        friend Driver operator +(int, Driver);
        Driver operator +(const Driver& obj); // concatenates the team names, adds the points, racewins and championshipsYears together
        Driver& operator++(); // increases race wins
        Driver operator++(int); 
        Driver& operator--(); // decreases race wins
        Driver operator--(int);
        bool operator<(const Driver& obj) const;
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
    this -> name = "Unknown";
    this -> raceWins = 0;
    this -> podiumsNumber = 0;
    this -> points = 0;
    this -> championshipsWon = 0;
    this -> championshipsYears = nullptr;
    this -> car = nullptr;
}

Driver::Driver(std::string name, int raceWins, int podiumsNumber, float points, int championshipsWon, int* championshipsYears):driverId(driverCount++){
    this -> name = name;
    this -> raceWins = raceWins;
    this -> podiumsNumber = podiumsNumber;
    this -> points = points;
    this -> championshipsWon = championshipsWon;
    this -> championshipsYears = new int[championshipsWon];
    for(int i = 0; i < championshipsWon; ++i)
        this -> championshipsYears[i] = championshipsYears[i];
    this -> car = nullptr;
}

Driver::Driver(std::string name, int raceWins, int podiumsNumber, float points, int championshipsWon, int* championshipsYears,Car* car):driverId(driverCount++)
{
    this -> name = name;
    this -> raceWins = raceWins;
    this -> podiumsNumber = podiumsNumber;
    this -> points = points;
    this -> championshipsWon = championshipsWon;
    this -> championshipsYears = new int[championshipsWon];
    for(int i = 0; i < championshipsWon; ++i)
        this -> championshipsYears[i] = championshipsYears[i];
    this -> car = car;
}

Driver::Driver(const Driver& obj):driverId(driverCount++)
{
    this -> name = obj.name;
    this -> raceWins = obj.raceWins;
    this -> podiumsNumber = obj.podiumsNumber;
    this -> points = obj.points;
    this -> championshipsWon = obj.championshipsWon;
    this -> championshipsYears = new int[obj.championshipsWon];
    for(int i = 0; i < obj.championshipsWon; ++i)
        this -> championshipsYears[i] = obj.championshipsYears[i];
    this -> car = obj.car;
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
        this -> raceWins = obj.raceWins;
        this -> podiumsNumber = obj.podiumsNumber;
        this -> points = obj.points;
        this -> championshipsWon = obj.championshipsWon;
        this -> championshipsYears = new int[obj.championshipsWon];
        for(int i = 0; i < obj.championshipsWon; ++i)
            this -> championshipsYears[i] = obj.championshipsYears[i];
        this -> car = obj.car;
    }
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Driver& driver)
{
    out << "Driver id: " << driver.driverId << '\n';
    out << "Driver name: " << driver.name << "\n";
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
    // out << "Car: " << driver.car << "\n";
    return out;
}

std::istream& operator >>(std::istream& in, Driver& driver)
{
    if(driver.championshipsYears != NULL)
        delete[] driver.championshipsYears;
    std::cout << "Enter driver's name: ";
    getline(in, driver.name);
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
    // in >> driver.car;
    return in;
}

class Car{
    static int carCount;
    const int carId;

    std::string brand;
    char *model;
    int releaseDate;
    bool broken;
    float topSpeed;

    public:
        static int getCarCount() { return Car::carCount;}
        const int getCarId(){return this->carId;}
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

int Car::carCount = 10000;

Car::Car():carId(carCount++)
{
    this -> brand = "Unknown";
    this -> model = new char[strlen("Unknown")+1];
    strcpy(this -> model, "Unknown");
    this -> releaseDate = 0;
    this -> broken = true;
    this -> topSpeed = 0;
}

Car::Car(std::string brand, char* model, int releaseDate, bool broken, float topSpeed):carId(carCount++)
{
    this -> brand = brand;
    this -> model = new char[strlen(model) + 1];
    strcpy(this -> model, model);
    this -> releaseDate = releaseDate;
    this -> broken = broken;
    this -> topSpeed = topSpeed;
}

Car::Car(const Car& obj):carId(carCount++)
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
*/
void TestTeam()
{
    Team a;
    int years[] ={2000, 2002, 2012}, years2[] = {1990, 1992, 1994}, years3[] = {};
    char name[] = "Mercedes AMG", name2[] = "Red Bull", name3[] = "Aston Martin";
    Team b(name, 3, years, 42, 2), h(name2, 3, years2, 60, 3);
    Team c(b), d, e(name3, 0, years3, 15, 1), f;
    // std::cin >> d;
    std::string lol;
    d = 3 + b;
    f = b + h;
    lol = b;
    std::cout << lol;
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
    Car b();
    std::string lol = "Max Verstappen";
    int yea[] = {2020, 2021};
    Driver c(lol, 52, 79, 201, 2, yea);
    // std::cin >> a; 
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
    // Track a,b(name, 56, 12, "Graphite", 58),c,d;
    // std::cin >> d;
    // std::cout << d;
}

int main()
{
    TestDriver();
}