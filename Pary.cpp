#include <iostream>  // Biblioteka umożliwiająca wyświetlanie tekstu na ekranie.
#include <vector>  // Biblioteka umożliwiająca używanie wektorów, czyli struktur przechowujących zbiory elementów.
#include <algorithm>  // Biblioteka zawierająca różne algorytmy, takie jak sortowanie i tasowanie.
#include <random>  // Biblioteka służąca do generowania liczb pseudolosowych.
#include <unordered_set>  // Biblioteka umożliwiająca używanie zbiorów nieuporządkowanych, w których każdy element może występować tylko raz.

// Klasa reprezentująca parę zwierząt.
class ParaZwierzat {
public:
    ParaZwierzat(long long numer) : numer_(numer) {}  // Konstruktor klasy, ustawia numer pary zwierząt.

    long long getNumer() const {  // Metoda zwracająca numer pary zwierząt.
        return numer_;
    }

private:
    long long numer_;  // Pole przechowujące numer pary zwierząt.
};

// Funkcja generująca pary zwierząt na podstawie podanej liczby par.
std::vector<ParaZwierzat> generujParyZwierzat(int liczbaPar) {
    std::vector<ParaZwierzat> paryZwierzat;  // Tworzenie pustego zbioru par zwierząt.

    // Generowanie par zwierząt i dodawanie ich do wektora.
    for (long long i = 1; i <= liczbaPar; ++i) {
        paryZwierzat.emplace_back(i);  // Dodawanie pierwszego zwierzęcia w parze.
        paryZwierzat.emplace_back(i);  // Dodawanie drugiego zwierzęcia w parze.
    }

    return paryZwierzat;  // Zwracanie wektora par zwierząt.
}

// Funkcja sprawdzająca, które pary zwierząt brakuje.
void sprawdzBrakujacePary(const std::vector<ParaZwierzat>& paryZwierzat, int liczbaPar) {
    std::unordered_set<long long> obecnosc;  // Tworzenie zbioru, który będzie przechowywał numery par zwierząt.

    // Dodawanie numerów par zwierząt do zbioru.
    for (const ParaZwierzat& para : paryZwierzat) {
        long long numer = para.getNumer();  // Pobieranie numeru pary zwierząt.
        if (obecnosc.find(numer) == obecnosc.end()) {  // Sprawdzenie, czy para zwierząt już wystąpiła.
            obecnosc.insert(numer);  // Jeśli nie, dodaj ją do zbioru.
        } else {  // Jeśli para zwierząt już wystąpiła...
            obecnosc.erase(numer);  // ...usuń ją ze zbioru.
        }
    }

    if (!obecnosc.empty()) {  // Jeśli zbiór nie jest pusty, to oznacza, że brakuje par zwierząt.
        std::cout << "Brakuje par zwierzat: ";
        for (long long para : obecnosc) {  // Wyświetlenie numerów brakujących par zwierząt.
            std::cout << para << " ";
        }
        std::cout << std::endl;
    } else {  // W przeciwnym razie wszystkie pary zwierząt są na miejscu.
        std::cout << "Nie brakuje zadnej pary zwierzat." << std::endl;
    }
}

int main() {
    int liczbaPar;

    std::cout << "Podaj liczbe par zwierzat, ktore Noe zabiera na arke: ";  // Prośba o wpisanie liczby par zwierząt.
    std::cin >> liczbaPar;  // Wczytanie liczby par zwierząt.

    std::vector<ParaZwierzat>
        paryZwierzat = generujParyZwierzat(liczbaPar);  // Wygenerowanie par zwierząt na podstawie podanej liczby.
    
    std::random_device rd;  // Inicjalizacja generatora liczb pseudolosowych.
    std::mt19937 g(rd());  // Tworzenie obiektu generatora liczb pseudolosowych.
    std::shuffle(paryZwierzat.begin(), paryZwierzat.end(), g);  // Mieszanie par zwierząt w wektorze.

    if (!paryZwierzat.empty()) {  // Sprawdzenie, czy wektor nie jest pusty.
        paryZwierzat.pop_back();
        paryZwierzat.pop_back();
        paryZwierzat.pop_back();// Usunięcie ostatniej pary zwierząt.
    }

    std::cout << "Pary zwierzat na arce Noego (po wymieszaniu i usunieciu ostatniego wyrazu):\n";  // Wyświetlenie komunikatu.
    for (const ParaZwierzat& zwierze : paryZwierzat) {  // Dla każdej pary zwierząt w wektorze...
        std::cout << zwierze.getNumer() << " ";  // ...wyświetlenie numeru pary.
    }
    std::cout << std::endl;  // Przejście do nowej linii.

    sprawdzBrakujacePary(paryZwierzat, liczbaPar);  // Wywołanie funkcji sprawdzającej, które pary zwierząt brakuje.

    return 0;  // Zakończenie działania programu.
}