#include <iostream>
#include <map>

constexpr double pi = 3.14;

class Shape {
public:
    // Wirtualna funkcja wypisująca informacje o kształcie
    virtual std::ostream& out(std::ostream& s) const = 0;

    // Wirtualna funkcja wczytująca informacje o kształcie
    virtual std::istream& inp(std::istream& s) = 0;

    // Wirtualna funkcja obliczająca obwód kształtu
    virtual double perimeter() const = 0;

    // Wirtualna funkcja obliczająca powierzchnię kształtu
    virtual double surface() const = 0;

    // Statyczna funkcja wczytująca dane dla kształtu
    static void input(Shape& shape, std::istream& s);
};

// Przeciążony operator << do wypisywania informacji o kształcie
std::ostream& operator<<(std::ostream& s, const Shape& sh) {
    return sh.out(s);
}

// Przeciążony operator >> do wczytywania informacji o kształcie
std::istream& operator>>(std::istream& s, Shape& sh) {
    return sh.inp(s);
}

// Klasa reprezentująca okrąg
class Circle : public Shape {
private:
    double radius;

public:
    // Konstruktor inicjalizujący promień okręgu
    Circle(double r) : radius(r) {}

    // Wirtualna funkcja wypisująca informacje o okręgu
    virtual std::ostream& out(std::ostream& s) const {
        return s << "Circle"
                 << "("
                 << "radius:" << radius << ", "
                 << "perimeter:" << perimeter() << ", "
                 << "surface:" << surface()
                 << ")";
    }

    // Wirtualna funkcja wczytująca informacje o okręgu
    virtual std::istream& inp(std::istream& s) {
        return s >> radius;
    }

    // Wirtualna funkcja obliczająca obwód okręgu
    virtual double perimeter() const {
        return 2 * pi * radius;
    }

    // Wirtualna funkcja obliczająca powierzchnię okręgu
    virtual double surface() const {
        return pi * radius * radius;
    }
};

// Statyczna funkcja wczytująca dane dla kształtu
void Shape::input(Shape& shape, std::istream& s) {
    s >> shape;
}

int main() {
    // Inicjalizacja obiektu klasy Circle
    Circle circle(0.0);

    // Wypisanie informacji o obiekcie przed wczytaniem danych
    std::cout << "Before input:" << std::endl;
    std::cout << circle << std::endl;

    // Wczytanie danych dla obiektu Circle
    std::cout << "Input circle data: ";
    Shape::input(circle, std::cin);

    // Wypisanie informacji o obiekcie po wczytaniu danych
    std::cout << std::endl << "After input:" << std::endl;
    std::cout << circle << std::endl;

    return 0;
}
