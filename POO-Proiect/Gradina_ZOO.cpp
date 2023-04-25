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
    string stareDeSanatate = "";
    static int numarAnimale;

public:
    Animale();
    Animale(string n, int v, string s, bool c);

    string getDenumire();
    int getVarsta();
    string getSpecie();
    bool getCarnivora();
    string getStareDeSanatate();
    void setStareDeSanatate(string stare);
    static int getNumarAnimale();
};

int Animale::numarAnimale = 0;

Animale::Animale()
{
    denumire = "";
    varsta = 0;
    specie = "";
    carnivora = false;
    numarAnimale++;
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
    if (carnivora != "Da" && carnivora != "da" && carnivora != "DA" && carnivora != "Nu" && carnivora != "nu" && carnivora != "NU")
    {
        throw invalid_argument("Optiunea trebuie sa fie Da sau Nu.");
    }

    if (carnivora == "Da" || carnivora == "da" || carnivora == "DA")
        animal.carnivora = true;
    else
        animal.carnivora = false;

    return is;
}

Animale::Animale(string n, int v, string s, bool c) : denumire(n), varsta(v), specie(s), carnivora(c)

                                                                                             string Animale::getDenumire()
{
    return denumire;
}

int Animale::getVarsta()
{
    return varsta;
}

int Animale::getNumarAnimale()
{
    return numarAnimale;
}

string Animale::getSpecie()
{
    return specie;
}

bool Animale::getCarnivora()
{
    return carnivora;
}

string Animale::getStareDeSanatate()
{
    return stareDeSanatate;
}

void Animale::setStareDeSanatate(string stare)
{
    stareDeSanatate = stare;
}

// Supraincarcare operator <<
ostream &operator<<(ostream &out, Animale &animal)
{
    out << "Denumire: " << animal.getDenumire() << endl;
    out << "Varsta: " << animal.getVarsta() << endl;
    out << "Specie: " << animal.getSpecie() << endl;
    out << "Carnivora: " << (animal.getCarnivora() ? "Da" : "Nu") << endl;
    if (animal.getStareDeSanatate() != "")
        out << "Stare de sanatate: " << animal.getStareDeSanatate() << endl;
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
    Animale *animal;
    string nume;
    int cantitate;

public:
    HranaAnimale(Animale *a, string n, int c);
    void HranaData(int c);
    void Afisare();
    void RezervareMancare();
};

HranaAnimale::HranaAnimale(Animale *a, string n, int c)
{
    animal = a;
    nume = n;
    cantitate = c;
}

// Scade cantitatea de hrana consumata din totalul de hrana
void HranaAnimale::HranaData(int canitate_consumata)
{
    cout << "Hrana pentru animalul " << animal->getDenumire() << ":" << endl;
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
        cout << "Fara mancare! Rezerva " << nume << " pentru " << animal->getDenumire() << "." << endl
             << "---------------------------" << endl
             << endl;
}

// Alocare dinamica pentru vector de obiecte
class Angajati
{
protected:
    Animale **animale;
    int numarAnimale;
    string nume;
    int salariu;
    static int numarAngajati; // VARIABILA STATICA

public:
    Angajati(string n, int s, int nr);
    Angajati(const Angajati &angajat);
    Angajati &operator=(const Angajati &angajat);
    void AnimaleIngrijite(int index, Animale *animal);
    void Salariu(int marire);
    void Salariu(double marire);
    void setSalariu(int salariu);
    int getSalariu();
    static int getNrAngajati();
    void Afisare();
    virtual ~Angajati();
};

int Angajati::numarAngajati = 0;

// Constructor cu parametri clasa Angajati
Angajati::Angajati(string n, int s, int nr)
{
    nume = n;
    salariu = s;
    numarAnimale = nr;
    animale = new Animale *[numarAnimale];
    numarAngajati++;
}

void Angajati::AnimaleIngrijite(int index, Animale *animal)
{
    animale[index] = animal;
}

// Supraincarcarea unei metode
void Angajati::Salariu(int marire)
{
    if (numarAnimale > 2)
        salariu = salariu + (marire * salariu) / 100;
    else
        cout << "Angajatul nu ingrijeste mai mult de 2 animale! Salariul a ramas nemodificat." << endl
             << "---------------------------" << endl
             << endl;
}

void Angajati::Salariu(double marire)
{
    if (numarAnimale > 2)
        salariu = salariu + marire * salariu;
    else
        cout << "Angajatul nu ingrijeste mai mult de 2 animale! Salariul a ramas nemodificat." << endl
             << "---------------------------" << endl
             << endl;
}

void Angajati::setSalariu(int s)
{
    if (s <= 0)
        throw domain_error("Salariul nu poate fi 0 sau negativ!");
    salariu = s;
}

int Angajati::getSalariu()
{
    return salariu;
}

void Angajati::Afisare()
{
    cout << "Nume: " << nume << endl;
    cout << "Salariu: " << salariu << endl;
    cout << "Animale ingrijite: ";
    for (int i = 0; i < numarAnimale; i++)
        if (i != numarAnimale - 1)
            cout << animale[i]->getDenumire() << ", ";
        else
            cout << animale[i]->getDenumire() << endl;
    cout << "---------------------------" << endl
         << endl;
}

// Copy constructor
Angajati::Angajati(const Angajati &angajat)
{
    nume = angajat.nume;
    salariu = angajat.salariu;
    numarAnimale = angajat.numarAnimale;
    animale = new Animale *[numarAnimale];
    for (int i = 0; i < numarAnimale; i++)
    {
        animale[i] = new Animale(*angajat.animale[i]);
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

        animale = new Animale *[numarAnimale];

        for (int i = 0; i < numarAnimale; i++)
        {
            animale[i] = new Animale(*angajat.animale[i]);
        }
    }

    return *this;
}

int Angajati::getNrAngajati()
{
    return numarAngajati;
}

// Destructor VIRTUAL - memoria alocata dinamic e eliberata
Angajati::~Angajati()
{
    delete[] animale;
    numarAngajati--;
}

class SalariuPreaMareException : public std::exception
{
public:
    virtual const char *what() const noexcept
    {
        return "Salariul angajatului este prea mare pentru a fi modificat de director!";
    }
};

// Mostenire 1
class Director : protected Angajati
{
public:
    Director();
    Director(string nume, int salariu);
    virtual ~Director() {}

    void schimbaSalariu(Angajati &a, int s)
    {
        if (s > 5000)
        {
            throw SalariuPreaMareException();
        }

        a.setSalariu(s);
    }
};

Director::Director(string nume, int salariu) : Angajati(nume, salariu, 0) {}

class Veterinar : public Animale, public Angajati
{
public:
    Veterinar(string nume, int salariu);
    virtual ~Veterinar() {}

    void examineaza(Animale &a, string stare)
    {

        a.setStareDeSanatate(stare);
    }
};

Veterinar::Veterinar(string nume, int salariu) : Angajati(nume, salariu, 0) {}

class SpatiiAnimale
{
private:
    int numar_animale;

protected:
    Animale animal;

public:
    SpatiiAnimale();
    SpatiiAnimale(Animale &a);
    void AdaugaAnimal(int nr_animale);
    void StergeAnimal(int nr_animale);
    void Afisare();
    virtual ~SpatiiAnimale() {}
};

SpatiiAnimale::SpatiiAnimale(Animale &a)
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

// Mostenire 2
class Acvatic : public SpatiiAnimale
{
private:
    int adancime;

public:
    Acvatic(Animale &a, int ad);
    ~Acvatic() {}
    void Afisare();
};

Acvatic::Acvatic(Animale &a, int ad) : SpatiiAnimale(a), adancime(ad)
{

    if (ad > 10)
        throw logic_error("Adancimea bazinului este prea mare!");
}

void Acvatic::Afisare()
{
    cout << "Denumirea animalului: " << animal.getDenumire() << endl;
    cout << "Adancime acvariu: " << adancime << endl
         << "---------------------------" << endl
         << endl;
}

// INTERFATA
class IContract
{
public:
    virtual void achizitieAnimale(Animale &a) = 0;
    virtual void achizitieHrana() = 0;
    virtual ~IContract() {}
};

class Achizitii : public IContract
{
public:
    void achizitieAnimale(Animale &a) override
    {
        cout << "A fost achizitionat animalul " << a.getDenumire() << endl;
    }

    void achizitieHrana() override
    {
        cout << "Achizitie hrana realizata." << endl;
    }
};

// Clasa de baza abstracta
class Program
{
protected:
    string oraInceput;
    string oraSfarsit;
    virtual void schimbareOraInceput(string oraI) = 0;
    virtual void schimbareOraSfarsit(string oraS) = 0;

public:
    Program();
    string getOraInceput();
    string getOraSfarsit();
};

Program::Program()
{
    oraInceput = "8:30";
    oraSfarsit = "17:30";
}

string Program::getOraInceput()
{
    return oraInceput;
}

string Program::getOraSfarsit()
{
    return oraSfarsit;
}

class ProgramVizite : public Program
{
public:
    virtual void schimbareOraInceput(string oraI)
    {
        oraInceput = oraI;
    }

    virtual void schimbareOraSfarsit(string oraS)
    {
        oraSfarsit = oraS;
    }
};

int main()
{ /*
     // Exemplu de afisare a unei cateogorii de animal
    Animale leu;
     cin >> leu;
     cout << endl
          << leu << "---------------------------" << endl
          << endl;



     // Metoda 1 - Venit total dupa vanzarea tuturor categoriilor de bilete
     BileteVandute();*/

    Animale leu("Leu", 5, "Mamifer", "Da");
    cout << leu
         << "---------------------------" << endl
         << endl;

    // Metoda 2 - Canitate disponibila de hrana pentru un animal anume
    HranaAnimale hrana(&leu, "Carne", 100);
    hrana.HranaData(20);
    hrana.Afisare();
    hrana.RezervareMancare();

    Angajati angajatZoo("John Smith", 4000, 3);
    Animale tigru("Tigru", 3, "Mamifer", true);
    Animale urs("Urs", 7, "Mamifer", true);

    angajatZoo.AnimaleIngrijite(0, &leu);
    angajatZoo.AnimaleIngrijite(1, &tigru);
    angajatZoo.AnimaleIngrijite(2, &urs);

    // Metoda 3 - Marire salariu daca ingrijeste mai mult de 2 animale
    angajatZoo.Salariu(0.2);
    angajatZoo.Salariu(50);
    angajatZoo.Afisare();

    // Apelez constructorul de copiere
    Angajati angajatZoo2 = angajatZoo;
    angajatZoo2.Afisare();

    Angajati angajatZoo3("Michael Davis", 4500, 2);
    angajatZoo3.AnimaleIngrijite(0, &tigru);
    angajatZoo3.AnimaleIngrijite(1, &leu);

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

    // ETAPA 2

    // MOSTENIRE
    Animale delfin("Delfin", 2, "Mamifer", "Da");
    Acvatic acvariu(delfin, 5);
    acvariu.Afisare();

    // MOSTENIRE

    Director director("Elon Musk", 7000);
    director.schimbaSalariu(angajatZoo3, 5000);
    angajatZoo3.Afisare();

    Veterinar vet("Alex Matei", 6000);
    vet.examineaza(leu, "Sanatos");
    cout << leu
         << "---------------------------" << endl
         << endl;

    // am sarit peste metoda protected

    Achizitii achizitii;
    achizitii.achizitieAnimale(leu);
    achizitii.achizitieHrana();
    cout << "---------------------------" << endl
         << endl;

    ProgramVizite prog;
    cout << "Ora de inceput a fost schimbata din " << prog.getOraInceput();
    prog.schimbareOraInceput("12:30");
    prog.schimbareOraSfarsit("19:30");
    cout << " in " << prog.getOraInceput();
    cout << endl
         << "---------------------------" << endl
         << endl;

    // am sarit peste POLIMORFISM LA EXECUTIE

    try
    {
        director.schimbaSalariu(angajatZoo3, 6000);
    }
    catch (const SalariuPreaMareException &e)
    {
        cout << "Exceptie: " << e.what() << endl
             << "---------------------------" << endl
             << endl;
    }

    Animale babuin;

    try
    {
        cin >> babuin;
    }
    catch (invalid_argument &ex)
    {
        cout << endl
             << "Exceptie: " << ex.what() << endl
             << "---------------------------" << endl
             << endl;
    }

    try
    {
        Acvatic acvariu1(delfin, 12);
    }
    catch (logic_error &ex)
    {
        cout << "Exceptie: " << ex.what() << endl
             << "---------------------------" << endl
             << endl;
    }

    try
    {
        angajatZoo2.setSalariu(-15);
    }
    catch (domain_error &ex)
    {
        cout << "Exceptie: " << ex.what() << endl
             << "Introduceti un salariu valid: ";
        int salariu;
        cin >> salariu;

        while (salariu <= 0)
        {
            cout << "Introduceti un salariu valid: ";
            cin >> salariu;
        }

        angajatZoo2.setSalariu(salariu);
        cout << "---------------------------" << endl
             << endl;
    }

    try
    {
        try
        {
            director.schimbaSalariu(angajatZoo3, 6000);
        }
        catch (const SalariuPreaMareException &e)
        {
            cout << "Exceptie: " << e.what() << endl;
            throw domain_error("Salariul nu a putut fi modificat!");
        }
    }
    catch (domain_error ex)
    {
        cout << "Exceptie2: " << ex.what() << endl;
    }

    cout << "Numarul de angajati este " << angajatZoo2.getNrAngajati() << endl;
    cout << "Numarul de animale este " << babuin.getNumarAnimale();

    return 0;
}
