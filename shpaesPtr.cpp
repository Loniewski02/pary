#include <map> // Biblioteka do obsługi asocjacyjnej struktury danych map
#include <cmath> // Biblioteka matematyczna, zawiera funkcje matematyczne, takie jak sqrt czy pow
#include <vector> // Biblioteka do obsługi dynamicznych tablic, umożliwia używanie vector
#include <memory> // Biblioteka do obsługi inteligentnych wskaźników, takich jak shared_ptr
#include <iostream> // Biblioteka do obsługi strumieni wejścia/wyjścia, umożliwia korzystanie z cout i cin

using namespace std;

//constexpr uzywac do dynamiocznie liczonych stalych np. dla cos(-1)

double pi = 3.14;

// virtual: Wskazuje, że funkcja jest wirtualna i może być przesłaniana w klasach pochodnych
// .ostream &:Zwraca referencję do obiektu strumienia wyjściowego, umożliwiając łańcuchowe użycie operatora <<.
// const: Oznacza, że funkcja nie modyfikuje żadnych składowych obiektu klasy. Jest to zabezpieczenie przed przypadkowymi modyfikacjami obiektu, gdy jest używany w kontekście obiektu typu const.
// static: Oznacza, że jest to metoda statyczna, co oznacza, że nie jest związana z konkretnym obiektem klasy, a z samą klasą. Może być wywoływana bez potrzeby tworzenia instancji obiektu klasy.
// shared_ptr<Shape>: Oznacza, że metoda zwraca obiekt typu shared_ptr, który jest inteligentnym wskaźnikiem do obiektu klasy Shape. Wskazuje, że ta metoda może zwracać wskaźnik do dowolnej klasy dziedziczącej po Shape, ponieważ shared_ptr obsługuje polimorfizm.



class Shape{
    public:
        virtual ostream &out(ostream &s)const = 0;
        virtual istream &inp(istream &s) = 0;
        virtual double perimeter()const = 0;
        virtual double surface()const = 0;
        static shared_ptr<Shape> input(istream &s);
        template<typename T> static shared_ptr<Shape> make(istream &s);
};

ostream &operator<<(ostream &s, const Shape &sh) {return sh.out(s);}
istream &operator>>(istream &s, Shape &sh) {return sh.inp(s);}


class Circle :public Shape{
    private:
        double radius;
        
    public:
        virtual ostream &out(ostream &s)const{
            return s
                << "Circle"
                << "("
                << "radius:" << radius << ", "
                << "perimeter:" << perimeter() << ", "
                << "surface:" << surface()
                << ")";
        }
        virtual istream &inp(istream &s) { return s >> radius; }
        virtual double perimeter()const { return 2*pi*radius; };
        virtual double surface()const { return pi*radius*radius; };
};

class Rectangle :public Shape{
    private:
        double sideA, sideB;
        
    public:
    virtual ostream &out(ostream &s)const {
       return s 
             <<"Rectangle"
            <<"("
            << "sideA:" << sideA << ", "
            << "sideB:" << sideB << ", "
            << "perimeter:" << perimeter() << ", "
            << "surface:" << surface()
            << ")";
    }
    virtual istream &inp(istream &s) { return s>>sideA>>sideB; };
    virtual double perimeter()const { return 2*(sideA + sideB); };
    virtual double surface()const { return sideA*sideB; };
};

class Triangle :public Shape{
    private: 
        double sideA, sideB, sideC;
        
    public:
        virtual ostream &out(ostream &s)const{
           return s
                << "Triangle"
                << "("
                << "sideA:" << sideA << ", "
                << "sideB" << sideB << ", "
                << "sideC"<< sideC << ", "
                << "perimeter"<< perimeter() << ", "
                << "surface"<< surface()
                << ")";
        }
        virtual istream &inp(istream &s) { return s>>sideA>>sideB>>sideC; }
        virtual double perimeter()const { return sideA+sideB+sideC; };
        virtual double surface()const {return (sideA+sideB+sideC)/2; };
};

shared_ptr<Shape> Shape::input(istream &s){
    typedef shared_ptr<Shape> creator(istream &s); //Tworzy alias creator dla funkcji, która przyjmuje strumień wejściowy (istream &s) i zwraca współdzielony wskaźnik do obiektu klasy Shape. dzieki creator mozemy dynamicznie dodawac nowe rodzaje ksztalotow w mapie
    typedef map<string, creator*> ShapeMap; // Tworzy alias ShapeMap dla mapy, w której kluczem jest ciąg znaków (string), a wartością jest wskaźnik do funkcji creator.
    static ShapeMap Creators{
        {"circle", Shape::make<Circle>},
        {"rectangle", Shape::make<Rectangle>},
        {"triangle", Shape::make<Triangle>},
    }; //Inicjalizuje statyczną mapę Creators za pomocą listy inicjalizacyjnej, która przypisuje dla każdego rodzaju kształtu odpowiednią funkcję tworzącą.
    
    string kind;
    s >> kind; //wczytanie ksztaltu ze strumienia wejsciowego
    ShapeMap::iterator f = Creators.find(kind); //Szuka w mapie funkcji tworzącej dla danego rodzaju kształtu.
    if(f == Creators.end()) return nullptr;//Jeśli nie znaleziono funkcji tworzącej, zwraca nullptr, co oznacza, że nie udało się utworzyć obiektu.
    return f->second(s);// Wywołuje funkcję tworzącą dla danego rodzaju kształtu i zwraca utworzony obiekt za pomocą współdzielonego wskaźnika.
}


//funkcja tworząca 
template<typename T> shared_ptr<Shape> Shape::make(istream &s){
    shared_ptr<Shape> shp = make_shared<T>(); // Tworzenie współdzielonego wskaźnika do obiektu danego typu T (Circle, Rectangle, Triangle)
    s >> *shp; // Wczytywanie informacji o kształcie z strumienia wejściowego
    return shp; // Zwracanie utworzonego obiektu
}

int main(){
    vector<shared_ptr<Shape>> shapes;
    
        
    while(true){
        cout << "Input shape: ";
        shared_ptr<Shape> sh = Shape::input(cin);//wczytanie i utworzenie obiektu kształtu, który jest przechowywany w zmiennej sh jako współdzielony wskaźnik.

        if(sh==nullptr) break;
        
        shapes.push_back(sh); //dodanie obiektu kształtu do wektora shapes
    }
    
    cout << endl << "Container:"<<endl;
    
    for(const auto& sh : shapes)
        cout << *sh << endl;
        
    //Wartość auto oznacza, że typ zmiennej jest dedukowany przez kompilator. const oznacza, że referencja jest stała, co oznacza, że zawartość wektora nie będzie modyfikowana przez tę pętlę.
        
    return 0;
}
