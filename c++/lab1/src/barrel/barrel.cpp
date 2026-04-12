#include "barrel.hpp"
using namespace std;

Barrel::Barrel(double total_volume, double alcohol_volume) {
    volume=total_volume;
    alcohol=alcohol_volume;

    if (alcohol > volume) alcohol = volume; 

    cout << "Конструктор бочки\n";
}

Barrel::~Barrel() {
    cout << "Деструктор Barrel\n";
}

double Barrel::get_volume() const { return volume; }
double Barrel::get_alcohol() const { return alcohol; }
double Barrel::get_water()  const { return volume - alcohol; }
double Barrel::get_concentration() const { 
    if (volume == 0) return 0;
    return (alcohol / volume) * 100.0; 
}

void Barrel::pour_into(Barrel &other, double amount) {
    if (amount > volume) amount = volume;

    double alcohol_to_transfer = (alcohol / volume) * amount;

    alcohol -= alcohol_to_transfer;
    volume -= amount;

    other.alcohol += alcohol_to_transfer;
    other.volume += amount;
}

void Barrel::print() const {
    std::cout << "Бочка: объем=" << volume << "л, спирт=" << alcohol << "л, концентрация=" << get_concentration() << "%\n";
}
