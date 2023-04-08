#include <iostream>
#include <cstring>
using namespace std;

class Animale
{
    friend istream &operator>>(istream &is, Animale &animal);
    string denumire;
    int varsta;
    string specie;
    bool carnivora;

public:
    Animale();
    Animale(string n, int v, string s, bool c);

    string getDenumire();
    int getVarsta();
    string getSpecie();
    bool getCarnivora();
};

Animale::Animale()
{
    denumire = "";
    varsta = 0;
    specie = "";
    carnivora = true;
}

istream &operator>>(istream &is, Animale &animal)
{
    cout << "Denumirea animalului: ";
    is >> animal.denumire;
    cout << "Varsta: ";
    is >> animal.varsta;
    cout << "Specia animalului: ";
    is >> animal.specie;
    cout << "Este carnivora: ";
    string carnivora;
    is >> carnivora;
    if (carnivora == "Da")
        animal.carnivora = true;
    else
        animal.carnivora = false;

    return is;
}

Animale::Animale(string n, int v, string s, bool c) : denumire(n), varsta(v), specie(s), carnivora(c) {}

string Animale::getDenumire()
{
    return denumire;
}

int Animale::getVarsta()
{
    return varsta;
}

string Animale::getSpecie()
{
    return specie;
}

bool Animale::getCarnivora()
{
    return carnivora;
}

// Supraincarcare operator <<
ostream &operator<<(ostream &out, Animale &animal)
{
    out << "Denumire: " << animal.getDenumire() << endl;
    out << "Varsta: " << animal.getVarsta() << endl;
    out << "Specie: " << animal.getSpecie() << endl;
    out << "Carnivora: " << (animal.getCarnivora() ? "Da" : "Nu") << endl;
    return out;
}

class Bilete
{
    friend istream &operator>>(istream &is, Bilete &bilet);
    int pret;
    string tip;
    int numar_vandute;

public:
    Bilete();
    Bilete(int p, string tip);
    void Cumpara(int n);
    int Venit();
};

// Constructor fara parametru pentru clasa Bilete
Bilete::Bilete()
{
    pret = 0;
    tip = "";
    numar_vandute = 0;
}

// Constructor cu parametru pentru clasa Bilete
Bilete::Bilete(int p, string t)
{
    pret = p;
    tip = t;
    numar_vandute = 0;
}

// Supraincarcare operator >>
istream &operator>>(istream &is, Bilete &bilet)
{
    cout << "Categoria de bilete: ";
    is >> bilet.tip;
    cout << "Pretul biletului: ";
    is >> bilet.pret;
    cout << "Introduceti cate bilete de acest tip s-au vandut: ";
    is >> bilet.numar_vandute;

    return is;
}

void Bilete::Cumpara(int n)
{
    numar_vandute += n;
}

int Bilete::Venit()
{
    return pret * numar_vandute;
}

void BileteVandute()
{
    int venitTotal = 0, i, nrCategorii = 2;

    for (i = 1; i <= nrCategorii; i++)
    {
        Bilete bilet;
        cin >> bilet;

        venitTotal += bilet.Venit();
        cout << endl;
    }

    cout << "Venitul pentru toate tipurile de bilete este: " << venitTotal << endl
         << "---------------------------" << endl
         << endl;
    ;
}

class HranaAnimale
{
    Animale animal;
    string nume;
    int cantitate;

public:
    HranaAnimale(Animale a, string n, int c);
    void HranaData(int c);
    void Afisare();
    void RezervareMancare();
};

HranaAnimale::HranaAnimale(Animale a, string n, int c)
{
    animal = a;
    nume = n;
    cantitate = c;
}

// Scade cantitatea de hrana consumata din totalul de hrana
void HranaAnimale::HranaData(int canitate_consumata)
{
    cout << "Hrana pentru animalul " << animal.getDenumire() << ":" << endl;
    cout << "Cantitate initiala: " << cantitate << endl;
    cantitate -= canitate_consumata;
}

void HranaAnimale::Afisare()
{
    cout << "Tip hrana: " << nume << endl;
    cout << "Cantitate disponibila: " << cantitate << endl
         << "---------------------------" << endl
         << endl;
}

void HranaAnimale::RezervareMancare()
{
    if (cantitate == 0)
        cout << "Fara mancare! Rezerva " << nume << " pentru " << animal.getDenumire() << "." << endl
             << "---------------------------" << endl
             << endl;
}

// Alocare dinamica pentru vector de obiecte
class Angajati
{
    string nume;
    int salariu;
    Animale *animale;
    int numarAnimale;

public:
    Angajati(string n, int s, int nr);
    Angajati(const Angajati &angajat);
    Angajati &operator=(const Angajati &angajat);
    void AnimaleIngrijite(int index, Animale animal);
    void Salariu(int marire);
    void Salariu(double marire);
    void Afisare();
    ~Angajati();
};

// Constructor cu parametri clasa Angajati
Angajati::Angajati(string n, int s, int nr)
{
    nume = n;
    salariu = s;
    numarAnimale = nr;
    animale = new Animale[numarAnimale];
}

void Angajati::AnimaleIngrijite(int index, Animale animal)
{
    animale[index] = animal;
}

// Supraincarcarea unei metode
void Angajati::Salariu(int marire)
{
    if (numarAnimale > 2)
        salariu = salariu + (marire * salariu) / 100;
    else
        cout<<"Angajatul nu ingrijeste mai mult de 2 animale! Salariul a ramas nemodificat."<< endl
        << "---------------------------" << endl
        << endl;
}

void Angajati::Salariu(double marire)
{
    if (numarAnimale > 2)
        salariu = salariu + marire * salariu;
    else
        cout<<"Angajatul nu ingrijeste mai mult de 2 animale! Salariul a ramas nemodificat."<< endl
        << "---------------------------" << endl
        << endl;
}

void Angajati::Afisare()
{
    cout << "Nume: " << nume << endl;
    cout << "Salariu: " << salariu << endl;
    cout << "Animale ingrijite: ";
    for (int i = 0; i < numarAnimale; i++)
        if (i != numarAnimale - 1)
            cout << animale[i].getDenumire() << ", ";
        else
            cout << animale[i].getDenumire() << endl;
    cout << "---------------------------" << endl
         << endl;
}

// Copy constructor
Angajati::Angajati(const Angajati &angajat)
{
    nume = angajat.nume;
    salariu = angajat.salariu;
    numarAnimale = angajat.numarAnimale;
    animale = new Animale[numarAnimale];
    for (int i = 0; i < numarAnimale; i++)
    {
        animale[i] = angajat.animale[i];
    }
}

// Operator=
Angajati &Angajati::operator=(const Angajati &angajat)
{
    if (this != &angajat)
    {
        delete[] animale;

        nume = angajat.nume;
        salariu = angajat.salariu;
        numarAnimale = angajat.numarAnimale;

        animale = new Animale[numarAnimale];

        for (int i = 0; i < numarAnimale; i++)
        {
            animale[i] = angajat.animale[i];
        }
    }

    return *this;
}

// Destructor - memoria alocata dinamic e eliberata
Angajati::~Angajati()
{
    delete[] animale;
}

class SpatiiAnimale
{
private:
    Animale animal;
    int numar_animale;

public:
    SpatiiAnimale();
    SpatiiAnimale(Animale a);
    void AdaugaAnimal(int nr_animale);
    void StergeAnimal(int nr_animale);
    void Afisare();
};

SpatiiAnimale::SpatiiAnimale(Animale a)
{
    animal = a;
    numar_animale = 0;
}

void SpatiiAnimale::AdaugaAnimal(int nr_animale)
{
    numar_animale += nr_animale;
}

void SpatiiAnimale::StergeAnimal(int nr_animale)
{
    numar_animale -= nr_animale;
}

void SpatiiAnimale::Afisare()
{

    cout << "In spatiul amenajat pentru animalul " << animal.getDenumire() << " sunt " << numar_animale << " animale." << endl
         << "---------------------------" << endl
         << endl;
}

int main()
{
    // Exemplu de afisare a unei cateogorii de animal
    Animale leu; 
    cin >> leu;
    cout << endl
         << leu << "---------------------------" << endl
         << endl;

    // Metoda 1 - Venit total dupa vanzarea tuturor categoriilor de bilete
    BileteVandute();

    // Metoda 2 - Canitate disponibila de hrana pentru un animal anume
    HranaAnimale hrana(leu, "Carne", 100);
    hrana.HranaData(20);
    hrana.Afisare();
    hrana.RezervareMancare();

    Angajati angajatZoo("John Smith", 4000, 3);
    Animale tigru("Tigru", 3, "Mamifer", true);
    Animale urs("Urs", 7, "Mamifer", true);

    angajatZoo.AnimaleIngrijite(0, leu);
    angajatZoo.AnimaleIngrijite(1, tigru);
    angajatZoo.AnimaleIngrijite(2, urs);

    // Metoda 3 - Marire salariu daca ingrijeste mai mult de 2 animale
    angajatZoo.Salariu(0.2);
    angajatZoo.Salariu(50);
    angajatZoo.Afisare();

    // Apelez constructorul de copiere
    Angajati angajatZoo2 = angajatZoo;
    angajatZoo2.Afisare();

    Angajati angajatZoo3("Michael Davis", 6500, 2);
    angajatZoo3.AnimaleIngrijite(0, tigru);
    angajatZoo3.AnimaleIngrijite(1, leu);

    // operatorul de atribuire=
    angajatZoo = angajatZoo3;

    angajatZoo.Afisare();
    angajatZoo3.Afisare();

    // Metoda 4 - Adaugare/Eliminare animale (d)in spatiul special amenajat
    SpatiiAnimale spatiu(leu);
    spatiu.AdaugaAnimal(3);
    spatiu.Afisare();
    spatiu.StergeAnimal(1);
    spatiu.Afisare();

   
    return 0;
}
