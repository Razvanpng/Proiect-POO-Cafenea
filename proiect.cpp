#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

// Clasele pentru angajati, produse, comenzi si evenimente
class Angajat {
protected:
    std::string nume;
    std::string functie;
    std::string ora_inceput;
    std::string ora_sfarsit;

public:
    Angajat(std::string nume, std::string functie, std::string ora_inceput, std::string ora_sfarsit)
        : nume(nume), functie(functie), ora_inceput(ora_inceput), ora_sfarsit(ora_sfarsit) {}

    virtual void afiseaza() const {
        std::cout << "Nume: " << nume << ", Functie: " << functie
                  << ", Ora inceput: " << ora_inceput << ", Ora sfarsit: " << ora_sfarsit << std::endl;
    }

    std::string getNume() const {
        return nume;
    }

    std::string getFunctie() const {
        return functie;
    }

    std::string getOraInceput() const {
        return ora_inceput;
    }

    std::string getOraSfarsit() const {
        return ora_sfarsit;
    }
};

class Barista : public Angajat {
public:
    Barista(std::string nume, std::string ora_inceput, std::string ora_sfarsit)
        : Angajat(nume, "Barista", ora_inceput, ora_sfarsit) {}
};

class Manager : public Angajat {
public:
    Manager(std::string nume, std::string ora_inceput, std::string ora_sfarsit)
        : Angajat(nume, "Manager", ora_inceput, ora_sfarsit) {}
};

class Ospatar : public Angajat {
public:
    Ospatar(std::string nume, std::string ora_inceput, std::string ora_sfarsit)
        : Angajat(nume, "Ospatar", ora_inceput, ora_sfarsit) {}
};

class Produs {
private:
    std::string nume;
    double pret;
    int cantitate;

public:
    Produs(std::string nume, double pret, int cantitate)
        : nume(nume), pret(pret), cantitate(cantitate) {}

    void afiseaza() const {
        std::cout << "Produs: " << nume << ", Pret: " << pret << " RON"
                  << ", Cantitate: " << cantitate << std::endl;
    }

    std::string getNume() const {
        return nume;
    }

    double getPret() const {
        return pret;
    }

    int getCantitate() const {
        return cantitate;
    }

    void adaugaCantitate(int cant) {
        cantitate += cant;
    }

    void eliminaCantitate(int cant) {
        if (cantitate >= cant)
            cantitate -= cant;
    }
};

class Comanda {
private:
    std::string numeClient;
    std::vector<Produs> produse;
    double pretTotal;

public:
    Comanda(std::string numeClient, const std::vector<Produs>& produse)
        : numeClient(numeClient), produse(produse), pretTotal(0.0) {
        calculeazaPretTotal();
    }

    void calculeazaPretTotal() {
        pretTotal = std::accumulate(produse.begin(), produse.end(), 0.0,
            [](double sum, const Produs& produs) {
                return sum + produs.getPret() * produs.getCantitate();
            });
    }

    double getPretTotal() const {
        return pretTotal;
    }

    std::string getNumeClient() const {
        return numeClient;
    }

    void afiseaza() const {
        std::cout << "Nume Client: " << numeClient << ", Pret Total: " << pretTotal << " RON" << std::endl;
    }
};

class Eveniment {
private:
    std::string nume;
    std::string data;
    double cost;

public:
    Eveniment(std::string nume, std::string data, double cost)
        : nume(nume), data(data), cost(cost) {}

    void afiseaza() const {
        std::cout << "Eveniment: " << nume << ", Data: " << data
                  << ", Cost: " << cost << " RON" << std::endl;
    }

    double getCost() const {
        return cost;
    }

    std::string getNume() const {
        return nume;
    }

    std::string getData() const {
        return data;
    }
};

class Cafenea {
private:
    std::string oras;
    std::vector<Angajat*> angajati;
    std::vector<Produs> produse;
    std::vector<Comanda> comenzi;
    std::vector<Eveniment> evenimente;

public:
    Cafenea(std::string oras) : oras(oras) {}

    // Functiile pentru gestionarea angajatilor
    void adaugaAngajat(Angajat* angajat) {
        angajati.push_back(angajat);
    }

    void stergeAngajat(const std::string& nume) {
        angajati.erase(std::remove_if(angajati.begin(), angajati.end(),
            [&nume](Angajat* angajat) {
                return angajat->getNume() == nume;
            }), angajati.end());
    }

    void afiseazaAngajati() const {
        for (const auto& angajat : angajati) {
            angajat->afiseaza();
        }
    }

    std::vector<Angajat*> getAngajati() const {
        return angajati;
    }

    // Functiile pentru gestionarea produselor
    void adaugaProdus(const Produs& produs) {
        produse.push_back(produs);
    }

    void eliminaProdus(const std::string& nume) {
        produse.erase(std::remove_if(produse.begin(), produse.end(),
            [&nume](Produs& produs) {
                return produs.getNume() == nume;
            }), produse.end());
    }

    void afiseazaProduse() const {
        for (const auto& produs : produse) {
            produs.afiseaza();
        }
    }

    std::vector<Produs> getProduse() const {
        return produse;
    }

    // Functiile pentru gestionarea comenzilor
    void adaugaComanda(const Comanda& comanda) {
        comenzi.push_back(comanda);
    }

    void afiseazaComenzi() const {
        for (const auto& comanda : comenzi) {
            comanda.afiseaza();
        }
    }

    std::vector<Comanda> getComenzi() const {
        return comenzi;
    }

    // Functiile pentru gestionarea evenimentelor
    void adaugaEveniment(const Eveniment& eveniment) {
        evenimente.push_back(eveniment);
    }

    void afiseazaEvenimente() const {
        for (const auto& eveniment : evenimente) {
            eveniment.afiseaza();
        }
    }

    std::vector<Eveniment> getEvenimente() const {
        return evenimente;
    }

    // Functia pentru calcularea profitului zilnic
    double calculeazaProfitZilnic() const {
        double profit = 0.0;
        for (const auto& comanda : comenzi) {
            profit += comanda.getPretTotal();
        }
        return profit;
    }

    // Functia pentru generarea raportului financiar
    void genereazaRaportFinanciar() const {
        double venituri = calculeazaProfitZilnic();
        double cheltuieli = std::accumulate(evenimente.begin(), evenimente.end(), 0.0,
            [](double sum, const Eveniment& eveniment) {
                return sum + eveniment.getCost();
            });
        double profit = venituri - cheltuieli;
        std::cout << "Venituri: " << venituri << " RON, Cheltuieli: " << cheltuieli
                  << " RON, Profit: " << profit << " RON" << std::endl;
    }
};

// Functie pentru citirea unui fisier CSV
std::vector<std::vector<std::string>> citesteCSV(const std::string& numeFisier) {
    std::vector<std::vector<std::string>> date;
    std::ifstream fisier(numeFisier);
    std::string linie;

    while (std::getline(fisier, linie)) {
        std::stringstream ss(linie);
        std::string camp;
        std::vector<std::string> rand;

        while (std::getline(ss, camp, ',')) {
            rand.push_back(camp);
        }

        date.push_back(rand);
    }

    return date;
}

// Functie pentru scrierea angajatilor intr-un fisier CSV
void scrieAngajatiCSV(const std::string& numeFisier, const std::vector<Angajat*>& angajati) {
    std::ofstream fisier(numeFisier);
    for (const auto& angajat : angajati) {
        fisier << angajat->getNume() << ","
               << angajat->getFunctie() << ","
               << angajat->getOraInceput() << ","
               << angajat->getOraSfarsit() << "\n";
    }
}

// Functie pentru scrierea produselor intr-un fisier CSV
void scrieProduseCSV(const std::string& numeFisier, const std::vector<Produs>& produse) {
    std::ofstream fisier(numeFisier);
    for (const auto& produs : produse) {
        fisier << produs.getNume() << ","
               << produs.getPret() << ","
               << produs.getCantitate() << "\n";
    }
}

// Functie pentru scrierea comenzilor intr-un fisier CSV
void scrieComenziCSV(const std::string& numeFisier, const std::vector<Comanda>& comenzi) {
    std::ofstream fisier(numeFisier);
    for (const auto& comanda : comenzi) {
        fisier << comanda.getNumeClient() << ","
               << comanda.getPretTotal() << "\n";
    }
}

// Functie pentru scrierea evenimentelor intr-un fisier CSV
void scrieEvenimenteCSV(const std::string& numeFisier, const std::vector<Eveniment>& evenimente) {
    std::ofstream fisier(numeFisier);
    for (const auto& eveniment : evenimente) {
        fisier << eveniment.getNume() << ","
               << eveniment.getData() << ","
               << eveniment.getCost() << "\n";
    }
}

void scrieRaportFinanciarCSV(const std::string& numeFisier, const Cafenea& cafenea) {
    std::ofstream fisier(numeFisier);
    if (!fisier.is_open()) {
        std::cerr << "Nu s-a putut deschide fisierul " << numeFisier << " pentru scriere.\n";
        return;
    }

    double venituri = cafenea.calculeazaProfitZilnic();
    double cheltuieli = std::accumulate(cafenea.getEvenimente().begin(), cafenea.getEvenimente().end(), 0.0,
        [](double sum, const Eveniment& eveniment) {
            return sum + eveniment.getCost();
        });
    double profit = venituri - cheltuieli;

    fisier << "venituri,cheltuieli,profit\n";
    fisier << venituri << "," << cheltuieli << "," << profit << "\n";
    
    fisier.close();
    std::cout << "Raportul financiar a fost salvat in " << numeFisier << ".\n";
}


// Meniu interactiv
void meniu(Cafenea& cafenea) {
    int optiune;
    do {
        std::cout << "\n--- Cafeneaua Van ---\n";
        std::cout << "1. Adauga Angajat\n";
        std::cout << "2. Sterge Angajat\n";
        std::cout << "3. Afiseaza Angajati\n";
        std::cout << "4. Adauga Produs\n";
        std::cout << "5. Elimina Produs\n";
        std::cout << "6. Afiseaza Produse\n";
        std::cout << "7. Adauga Comanda\n";
        std::cout << "8. Afiseaza Comenzi\n";
        std::cout << "9. Adauga Eveniment\n";
        std::cout << "10. Afiseaza Evenimente\n";
        std::cout << "11. Calculeaza Profit Zilnic\n";
        std::cout << "12. Genereaza Raport Financiar\n";
        std::cout << "0. Iesire\n";
        std::cout << "Alege o optiune: ";
        std::cin >> optiune;

        switch (optiune) {
            case 1: {
                std::string nume, functie, ora_inceput, ora_sfarsit;
                std::cout << "Introdu numele angajatului: ";
                std::cin >> nume;
                std::cout << "Introdu functia (Barista, Manager, Ospatar): ";
                std::cin >> functie;
                std::cout << "Introdu ora de inceput: ";
                std::cin >> ora_inceput;
                std::cout << "Introdu ora de sfarsit: ";
                std::cin >> ora_sfarsit;
                if (functie == "Barista") {
                    cafenea.adaugaAngajat(new Barista(nume, ora_inceput, ora_sfarsit));
                } else if (functie == "Manager") {
                    cafenea.adaugaAngajat(new Manager(nume, ora_inceput, ora_sfarsit));
                } else if (functie == "Ospatar") {
                    cafenea.adaugaAngajat(new Ospatar(nume, ora_inceput, ora_sfarsit));
                }
                scrieAngajatiCSV("angajati.csv", cafenea.getAngajati());
                break;
            }
            case 2: {
                std::string nume;
                std::cout << "Introdu numele angajatului de sters: ";
                std::cin >> nume;
                cafenea.stergeAngajat(nume);
                scrieAngajatiCSV("angajati.csv", cafenea.getAngajati());
                break;
            }
            case 3: {
                cafenea.afiseazaAngajati();
                break;
            }
            case 4: {
                std::string nume;
                double pret;
                int cantitate;
                std::cout << "Introdu numele produsului: ";
                std::cin >> nume;
                std::cout << "Introdu pretul: ";
                std::cin >> pret;
                std::cout << "Introdu cantitatea: ";
                std::cin >> cantitate;
                cafenea.adaugaProdus(Produs(nume, pret, cantitate));
                scrieProduseCSV("produse.csv", cafenea.getProduse());
                break;
            }
            case 5: {
                std::string nume;
                std::cout << "Introdu numele produsului de eliminat: ";
                std::cin >> nume;
                cafenea.eliminaProdus(nume);
                scrieProduseCSV("produse.csv", cafenea.getProduse());
                break;
            }
            case 6: {
                cafenea.afiseazaProduse();
                break;
            }
            case 7: {
                std::string numeClient;
                std::vector<Produs> produse;
                std::string numeProdus;
                double pret;
                int cantitate;
                std::cout << "Introdu numele clientului: ";
                std::cin >> numeClient;
                char cont;
                do {
                    std::cout << "Introdu numele produsului: ";
                    std::cin >> numeProdus;
                    std::cout << "Introdu pretul: ";
                    std::cin >> pret;
                    std::cout << "Introdu cantitatea: ";
                    std::cin >> cantitate;
                    produse.push_back(Produs(numeProdus, pret, cantitate));
                    std::cout << "Mai adauga un produs? (y/n): ";
                    std::cin >> cont;
                } while (cont == 'y');
                cafenea.adaugaComanda(Comanda(numeClient, produse));
                scrieComenziCSV("comenzi.csv", cafenea.getComenzi());
                break;
            }
            case 8: {
                cafenea.afiseazaComenzi();
                break;
            }
            case 9: {
                std::string nume, data;
                double cost;
                std::cout << "Introdu numele evenimentului: ";
                std::cin >> nume;
                std::cout << "Introdu data: ";
                std::cin >> data;
                std::cout << "Introdu costul: ";
                std::cin >> cost;
                cafenea.adaugaEveniment(Eveniment(nume, data, cost));
                scrieEvenimenteCSV("evenimente.csv", cafenea.getEvenimente());
                break;
            }
            case 10: {
                cafenea.afiseazaEvenimente();
                break;
            }
            case 11: {
                std::cout << "Profit Zilnic: " << cafenea.calculeazaProfitZilnic() << " RON\n";
                break;
            }
            case 12: {
                cafenea.genereazaRaportFinanciar();
                break;
            }
            case 0:
                std::cout << "Iesire...\n";
                break;
            default:
                std::cout << "Optiune invalida!\n";
        }
    } while (optiune != 0);
}

// Functie pentru a crea fisierele CSV daca nu exista
void creeazaFisiereCSV() {
    std::vector<std::string> fisiere = {
        "angajati.csv", "produse.csv", "comenzi.csv", "evenimente.csv", "raport_financiar.csv"
    };

    for (const auto& fisier : fisiere) {
        std::ofstream outFile(fisier, std::ios::app);
        if (!outFile) {
            std::cerr << "Eroare la crearea fisierului: " << fisier << std::endl;
        }
    }
}

void testeazaAplicatia() {
    Cafenea cafenea("Bucuresti");

    // Teste pentru angajati
    cafenea.adaugaAngajat(new Barista("Ion Popescu", "08:00", "16:00"));
    cafenea.adaugaAngajat(new Manager("Maria Ionescu", "09:00", "17:00"));
    cafenea.adaugaAngajat(new Ospatar("Vasile Georgescu", "10:00", "18:00"));
    cafenea.adaugaAngajat(new Barista("Ana Marin", "08:00", "16:00"));
    cafenea.stergeAngajat("Ion Popescu");
    cafenea.stergeAngajat("Maria Ionescu");

    // Teste pentru produse
    cafenea.adaugaProdus(Produs("Espresso", 5.50, 100));
    cafenea.adaugaProdus(Produs("Cappuccino", 7.00, 50));
    cafenea.adaugaProdus(Produs("Latte", 6.50, 30));
    cafenea.adaugaProdus(Produs("Mocha", 8.00, 20));
    cafenea.eliminaProdus("Espresso");
    cafenea.eliminaProdus("Latte");

    // Teste pentru comenzi
    std::vector<Produs> produseComanda1 = { Produs("Cappuccino", 7.00, 1), Produs("Mocha", 8.00, 1) };
    std::vector<Produs> produseComanda2 = { Produs("Cappuccino", 7.00, 2), Produs("Mocha", 8.00, 2) };
    cafenea.adaugaComanda(Comanda("Ana Popa", produseComanda1));
    cafenea.adaugaComanda(Comanda("Ion Marin", produseComanda2));

    // Teste pentru evenimente
    cafenea.adaugaEveniment(Eveniment("Degustare de cafea", "2025-01-15", 500.0));
    cafenea.adaugaEveniment(Eveniment("Workshop de barista", "2025-02-20", 800.0));

    // Teste pentru afisare si calculare
    cafenea.afiseazaAngajati();
    cafenea.afiseazaProduse();
    cafenea.afiseazaComenzi();
    cafenea.afiseazaEvenimente();
    std::cout << "Profit Zilnic: " << cafenea.calculeazaProfitZilnic() << " RON\n";
    cafenea.genereazaRaportFinanciar();
}

int main() {
    // Matrice de testare
    std::cout << "Inceperea matricei de testare...\n";
    testeazaAplicatia();
    std::cout << "Matricea de testare a fost finalizata.\n";

    // Creare si initializare fisiere CSV
    std::ofstream angajatiCSV("angajati.csv");
    angajatiCSV << "nume,functie,ora_inceput,ora_sfarsit\n";
    angajatiCSV.close();

    std::ofstream produseCSV("produse.csv");
    produseCSV << "nume,pret,cantitate\n";
    produseCSV.close();

    std::ofstream comenziCSV("comenzi.csv");
    comenziCSV << "numeClient,produse,pretTotal\n";
    comenziCSV.close();

    std::ofstream evenimenteCSV("evenimente.csv");
    evenimenteCSV << "nume,data,cost\n";
    evenimenteCSV.close();

    std::ofstream rapoarteCSV("rapoarte_financiare.csv");
    rapoarteCSV << "venituri,cheltuieli,profit\n";
    rapoarteCSV.close();

    std::cout << "Fisierele CSV au fost create cu succes.\n";

    // Meniu interactiv
    Cafenea cafenea("Bucuresti");
    meniu(cafenea);

    // Salvarea datelor in fisiere CSV
    scrieAngajatiCSV("angajati.csv", cafenea.getAngajati());
    scrieProduseCSV("produse.csv", cafenea.getProduse());
    scrieComenziCSV("comenzi.csv", cafenea.getComenzi());
    scrieEvenimenteCSV("evenimente.csv", cafenea.getEvenimente());

    // Salvarea raportului financiar in fisierul CSV
    scrieRaportFinanciarCSV("rapoarte_financiare.csv", cafenea);

    return 0;
}
