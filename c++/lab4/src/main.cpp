#include <iostream>
#include <fstream>
#include "./point/point.hpp"
#include "./circle/circle.hpp"
#include "./list/list.hpp"
using namespace std;

int main() {

	List l;

    std::cout << "=== Добавление элементов ===" << std::endl;
    Circle c1(Point(0, 0), 5);
    Circle c2(Point(1, 2), 3);
    Circle c3(Point(-1, 4), 7);
    Circle c4(Point(2, 2), 5); 
    Circle c5(Point(0, 0), 5); 

    l.push_back(c1);
    l.push_back(c2);
    l.push_front(c3);
    l.push_back(c4);
    l.push_back(c5);

    cout << "\nСписок после добавления элементов:" << endl;
    l.print();
    cout << "Размер списка: " << l.get_size() << endl;

    cout << "\n=== Сортировка по площади ===" << endl;
    l.sort_by_area();
    l.print();

    cout << "\n=== Удаление первого элемента с радиусом 5 и центром (0,0) ===" << endl;
    Circle removeTest(Point(0, 0), 5);
    bool removed = l.remove_first(removeTest);
    cout << "Удаление успешно: " << (removed ? "да" : "нет") << endl;
    l.print();
    cout << "Размер списка: " << l.get_size() << endl;

    cout << "\n=== Удаление всех элементов с радиусом 5 ===" << endl;
    Circle removeAllTest(Point(0,0),5); 
    size_t count = l.remove_all(removeAllTest);
    cout << "Количество удалённых элементов: " << count << endl;
    l.print();
    cout << "Размер списка: " << l.get_size() << endl;

    cout << "\n=== Очистка списка ===" << endl;
    l.clear();
    l.print();
    cout << "Размер списка после очистки: " << l.get_size() << endl;

    cout << "\n=== Тест записи и чтения из файла ===" << endl;
    l.push_back(c1);
    l.push_back(c2);
    l.push_back(c3);
    l.print_to_file("./public/circles.txt");
    
    List l2;
    l2.read_from_file("./public/circles.txt");
    cout << "\nСписок, прочитанный из файла:" << endl;
    l2.print();
    cout << endl;

    cout << "Итератор:" << endl;
    for (List::Iterator it = l.begin(); it != l.end(); ++it) {
        (*it).print();
    }
    cout << endl;

    std::ofstream fout("./public/circles.txt");
    if (fout) {
        l.write_to(fout);
        fout.close();
    }

    ifstream fin("./public/circles.txt");
    if (fin) {
        l.read_from(fin);
        fin.close();
        l.print();
        cout << endl;
    }
  


	return 0;
}
