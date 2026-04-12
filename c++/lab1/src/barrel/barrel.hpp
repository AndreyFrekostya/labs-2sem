#include <iostream>

class Barrel {
private:
    double volume;       
    double alcohol;     

public:
    Barrel(double total_volume, double alcohol_volume = 0.0);

    ~Barrel();

    double get_volume() const;          
    double get_alcohol() const;         
    double get_water() const;           
    double get_concentration() const;   

    void pour_into(Barrel &other, double amount); 

    void print() const;
};

