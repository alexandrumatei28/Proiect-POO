#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

class Animal
{
    friend istream &operator>>(istream &is, Animal &animal);
    string denumire;
    int varsta;
    string specie;
    bool carnivora;
    string stareDeSanatate = "";
    static int numarAnimale;

public:
    Animal();
    Animal(string n, int v, string s, bool c);

    string getDenumire() const;
    int getVarsta() const;
    string getSpecie();
    bool getCarnivora();
    string getStareDeSanatate();
    void setStareDeSanatate(string stare);
    static int getNumarAnimale();
};

int Animal::numarAnimale = 0;

Animal::Animal()
{
    denumire = "";
    varsta = 0;
    specie = "";
    carnivora = false;
    numarAnimale++;
}

istream &operator>>(istream &is, Animal &animal)
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

Animal::Animal(string n, int v, string s, bool c) : denumire(n), varsta(v), specie(s), carnivora(c) {}

string Animal::getDenumire() const
{
    return denumire;
}

int Animal::getVarsta() const
{
    return varsta;
}

int Animal::getNumarAnimale()
{
    return numarAnimale;
}

string Animal::getSpecie()
{
    return specie;
}

bool Animal::getCarnivora()
{
    return carnivora;
}

string Animal::getStareDeSanatate()
{
    return stareDeSanatate;
}

void Animal::setStareDeSanatate(string stare)
{
    stareDeSanatate = stare;
}

// Supraincarcare operator <<
ostream &operator<<(ostream &out, Animal &animal)
{
    out << "Denumire: " << animal.getDenumire() << endl;
    out << "Varsta: " << animal.getVarsta() << endl;
    out << "Specie: " << animal.getSpecie() << endl;
    out << "Carnivora: " << (animal.getCarnivora() ? "Da" : "Nu") << endl;
    if (animal.getStareDeSanatate() != "")
        out << "Stare de sanatate: " << animal.getStareDeSanatate() << endl;
    return out;
}

class Bilet
{
    friend istream &operator>>(istream &is, Bilet &bilet);
    int pret;
    string tip;
    int numar_vandute;

public:
    Bilet();
    Bilet(int p, string tip);
    void Cumpara(int n);
    int Venit();
};

// Constructor fara parametru pentru clasa Bilete
Bilet::Bilet()
{
    pret = 0;
    tip = "";
    numar_vandute = 0;
}

// Constructor cu parametru pentru clasa Bilete
Bilet::Bilet(int p, string t)
{
    pret = p;
    tip = t;
    numar_vandute = 0;
}

// Supraincarcare operator >>
istream &operator>>(istream &is, Bilet &bilet)
{
    cout << "Categoria de bilete: ";
    is >> bilet.tip;
    cout << "Pretul biletului: ";
    is >> bilet.pret;
    cout << "Introduceti cate bilete de acest tip s-au vandut: ";
    is >> bilet.numar_vandute;

    return is;
}

void Bilet::Cumpara(int n)
{
    numar_vandute += n;
}

int Bilet::Venit()
{
    return pret * numar_vandute;
}

void BileteVandute()
{
    int venitTotal = 0, i, nrCategorii = 2;

    for (i = 1; i <= nrCategorii; i++)
    {
        Bilet bilet;
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
    Animal *animal;
    string nume;
    int cantitate;

public:
    HranaAnimale(Animal *a, string n, int c);
    void HranaData(int c);
    void Afisare();
    void RezervareMancare();
};

HranaAnimale::HranaAnimale(Animal *a, string n, int c)
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
class Angajat
{
protected:
    Animal **animale;
    int numarAnimale;
    string nume;
    int salariu;
    static int numarAngajati; // VARIABILA STATICA

public:
    Angajat(){};
    Angajat(string n, int s, int nr);
    Angajat(const Angajat &angajat);
    Angajat &operator=(const Angajat &angajat);
    void AnimaleIngrijite(int index, Animal *animal);
    void Salariu(int marire);
    void Salariu(double marire);
    void setSalariu(int salariu);
    int getSalariu() const;
    static int getNrAngajati(); 
    void Afisare();
    virtual ~Angajat();
};

int Angajat::numarAngajati = 0;

// Constructor cu parametri clasa Angajati
Angajat::Angajat(string n, int s, int nr)
{
    nume = n;
    salariu = s;
    numarAnimale = nr;
    animale = new Animal *[numarAnimale];
    numarAngajati++;
}

void Angajat::AnimaleIngrijite(int index, Animal *animal)
{
    animale[index] = animal;
}

// Supraincarcarea unei metode
void Angajat::Salariu(int marire)
{
    if (numarAnimale > 2)
        salariu = salariu + (marire * salariu) / 100;
    else
        cout << "Angajatul nu ingrijeste mai mult de 2 animale! Salariul a ramas nemodificat." << endl
             << "---------------------------" << endl
             << endl;
}

void Angajat::Salariu(double marire)
{
    if (numarAnimale > 2)
        salariu = salariu + marire * salariu;
    else
        cout << "Angajatul nu ingrijeste mai mult de 2 animale! Salariul a ramas nemodificat." << endl
             << "---------------------------" << endl
             << endl;
}

void Angajat::setSalariu(int s)
{
    if (s <= 0)
        throw domain_error("Salariul nu poate fi 0 sau negativ!");
    salariu = s;
}

int Angajat::getSalariu() const
{
    return salariu;
}

void Angajat::Afisare()
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
Angajat::Angajat(const Angajat &angajat)
{
    nume = angajat.nume;
    salariu = angajat.salariu;
    numarAnimale = angajat.numarAnimale;
    animale = new Animal *[numarAnimale];
    for (int i = 0; i < numarAnimale; i++)
    {
        animale[i] = new Animal(*angajat.animale[i]);
    }
}

// Operator=
Angajat &Angajat::operator=(const Angajat &angajat)
{
    if (this != &angajat)
    {
        delete[] animale;

        nume = angajat.nume;
        salariu = angajat.salariu;
        numarAnimale = angajat.numarAnimale;

        animale = new Animal *[numarAnimale];

        for (int i = 0; i < numarAnimale; i++)
        {
            animale[i] = new Animal(*angajat.animale[i]);
        }
    }

    return *this;
}

int Angajat::getNrAngajati()
{
    return numarAngajati;
}

// Destructor VIRTUAL - memoria alocata dinamic e eliberata
Angajat::~Angajat()
{
    delete[] animale;
    numarAngajati--;
}


//EXCEPTIE facuta de mine
class SalariuPreaMareException : public std::exception
{
public:
    virtual const char *what() const noexcept
    {
        return "Salariul angajatului este prea mare pentru a fi modificat de director!";
    }
};

// Mostenire 1  - Design pattern SINGLETON - pentru a avea o singura instanta a clasei Director
class Director : protected Angajat
{
    static Director* instance;
    Director(const string& nume, int salariu);
    Director() {};
    static int numarInstante;

public:
    static int getNrInstante();

    static Director* getInstance(const std::string& nume, int varsta) {
        if (instance == nullptr) {
            instance = new Director(nume, varsta);
        }
        return instance;
    }
    
    virtual ~Director() {}

    void schimbaSalariu(Angajat &a, int s)
    {
        if (s > 5000)
        {
            throw SalariuPreaMareException();
        }

        a.setSalariu(s);
    }
};


int Director::numarInstante = 0;
int Director::getNrInstante()
{
    return numarInstante;
}


Director* Director::instance = nullptr;
Director::Director(const string& nume, int salariu) : Angajat(nume, salariu, 0) { numarInstante++;}

class Veterinar : public Animal, public Angajat
{
public:
    Veterinar(){};
    Veterinar(string nume, int salariu);
    virtual ~Veterinar() {}
   

    void examineaza(Animal &a, string stare)
    {

        a.setStareDeSanatate(stare);
    }
};

Veterinar::Veterinar(string nume, int salariu) : Angajat(nume, salariu, 0) {}


class SpatiuAnimale
{
private:
    int numar_animale;

protected:
    Animal animal;

public:
    SpatiuAnimale(){};
    SpatiuAnimale(Animal &a);
    void AdaugaAnimal(int nr_animale);
    void StergeAnimal(int nr_animale);
    void Afisare();
    virtual ~SpatiuAnimale() {}
};

SpatiuAnimale::SpatiuAnimale(Animal &a)
{
    animal = a;
    numar_animale = 0;
}

void SpatiuAnimale::AdaugaAnimal(int nr_animale)
{
    numar_animale += nr_animale;
}

void SpatiuAnimale::StergeAnimal(int nr_animale)
{
    numar_animale -= nr_animale;
}

void SpatiuAnimale::Afisare()
{

    cout << "In spatiul amenajat pentru animalul " << animal.getDenumire() << " sunt " << numar_animale << " animale." << endl
         << "---------------------------" << endl
         << endl;
}

// Mostenire 2
class Acvatic : public SpatiuAnimale
{
private:
    int adancime;

public:
    Acvatic(){};
    Acvatic(Animal &a, int ad);
    ~Acvatic() {
        cout<<"Destructor Acvatic apelat.";
    }
    void Afisare();
};

Acvatic::Acvatic(Animal &a, int ad) : SpatiuAnimale(a), adancime(ad)
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
    virtual void achizitieAnimale(Animal &a) = 0;
    virtual void achizitieHrana() = 0;
    virtual ~IContract() {}
};

class Achizitii : public IContract
{
public:
    void achizitieAnimale(Animal &a) override
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


//ETAPA 3

template <typename T>
class Lista {
private:
    struct Nod {
        T element;
        Nod* urmator;
        Nod(const T& element, Nod* urmator = nullptr)
            : element(element), urmator(urmator) {}
    };

    Nod* primul;
    int dimensiune;

public:
    Lista() : primul(nullptr), dimensiune(0) {}

    void adauga(const T& element) {
        Nod* nod = new Nod(element, primul);
        primul = nod;
        dimensiune++;
    }

    Nod* inceput() const { return primul; }

};


// metoda template
template <typename T>
double calculeazaMediaSalariilor(const Lista<T>& angajati) {
    double sumaSalarii = 0;
    int numarAngajati = 0;

    for (auto i = angajati.inceput(); i != nullptr; i = i->urmator) {
        const Angajat* angajat = i->element;
        sumaSalarii += angajat->getSalariu();
        numarAngajati++;
    }

    if (numarAngajati > 0) {
        return sumaSalarii / numarAngajati;
    } else {
        return 0;
    }
}


double calculeazaMediaVarsta(const vector<Animal*>& animale) {
    int numarAnimale = animale.size();
    int sumaVarste = 0;

    
    for (const Animal* animal : animale) {
        sumaVarste += animal->getVarsta();
    }

    double mediaVarsta = sumaVarste / numarAnimale;

    return mediaVarsta;
}


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


    vector<Animal*> animale;

    Animal leu("Leu", 5, "Mamifer", "Da");
    cout << leu
         << "---------------------------" << endl
         << endl;

    // Metoda 2 - Canitate disponibila de hrana pentru un animal anume
    HranaAnimale hrana(&leu, "Carne", 100);
    hrana.HranaData(20);
    hrana.Afisare();
    hrana.RezervareMancare();

    Angajat angajatZoo("John Smith", 4000, 3);
    Animal tigru("Tigru", 3, "Mamifer", true);
    Animal urs("Urs", 7, "Mamifer", true);

    angajatZoo.AnimaleIngrijite(0, &leu);
    angajatZoo.AnimaleIngrijite(1, &tigru);
    angajatZoo.AnimaleIngrijite(2, &urs);

    // Metoda 3 - Marire salariu daca ingrijeste mai mult de 2 animale
    angajatZoo.Salariu(0.2);
    angajatZoo.Salariu(50);
    angajatZoo.Afisare();

    // Apelez constructorul de copiere
    Angajat angajatZoo2 = angajatZoo;
    angajatZoo2.Afisare();

    Angajat angajatZoo3("Michael Davis", 4500, 2);
    angajatZoo3.AnimaleIngrijite(0, &tigru);
    angajatZoo3.AnimaleIngrijite(1, &leu);

    // operatorul de atribuire=
    angajatZoo = angajatZoo3;

    angajatZoo.Afisare();
    angajatZoo3.Afisare();

    // Metoda 4 - Adaugare/Eliminare animale (d)in spatiul special amenajat
    SpatiuAnimale spatiu(leu);
    spatiu.AdaugaAnimal(3);
    spatiu.Afisare();
    spatiu.StergeAnimal(1);
    spatiu.Afisare();

    // ETAPA 2

    // MOSTENIRE
    Animal delfin("Delfin", 2, "Mamifer", "Da");
    Acvatic acvariu(delfin, 5);
    acvariu.Afisare();

    // MOSTENIRE

    Director* director = Director::getInstance("Elon Musk", 7000);
    director->schimbaSalariu(angajatZoo3, 5000);
    angajatZoo3.Afisare();

    Veterinar vet("Alex Matei", 6000);
    vet.examineaza(leu, "Sanatos");
    cout << leu
         << "---------------------------" << endl
         << endl;


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

    //Destructor virtual
    SpatiuAnimale* pSpatiu = new Acvatic(delfin,10);
    delete pSpatiu;
     cout << endl<<"---------------------------" << endl
         << endl;

    try
    {
        director->schimbaSalariu(angajatZoo3, 6000);
    }
    catch (const SalariuPreaMareException &e)
    {
        cout << "Exceptie: " << e.what() << endl
             << "---------------------------" << endl
             << endl;
    }

    Animal babuin;

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
            director->schimbaSalariu(angajatZoo3, 6000);
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
          cout << "---------------------------" << endl
             << endl;
    }

    cout << "Numarul de angajati este " << angajatZoo2.getNrAngajati() << endl
      << "---------------------------" << endl
             << endl;
    cout << "Numarul de animale este " << babuin.getNumarAnimale() << endl
      << "---------------------------" << endl
             << endl;

  

    // ETAPA 3


    // template si metoda template
    Lista<Angajat*> angajati;
    angajati.adauga(new Veterinar("Ion Popescu", 3000));
    angajati.adauga(new Veterinar("Maria Ionescu", 2500));
    angajati.adauga(new Veterinar("Dan Stroe", 4500));

    /*for (auto i = angajati.inceput(); i != nullptr; i = i->urmator) {
    cout << i->element->getSalariu()<< endl;
    }*/

    cout << "Numarul de angajati este " << angajatZoo2.getNrAngajati() << endl
      << "---------------------------" << endl
             << endl;

    
    //am folosit clasa si metoda template pentru a calcula salariul mediu al angajatilor
    double mediaSalariilor = calculeazaMediaSalariilor(angajati);
        cout << "Media salariilor angajatilor: " << mediaSalariilor << endl
      << "---------------------------" << endl<< endl;



    
    animale.push_back(&leu);
    animale.push_back(&tigru);
    animale.push_back(&urs);
    animale.push_back(&delfin);

    double media = calculeazaMediaVarsta(animale);
        cout << "Media varstei animalelor este: " << media << endl
      << "---------------------------" << endl<< endl;


    
    //https://stackoverflow.com/questions/33314653/sorting-a-vector-of-custom-objects-by-overloading
    sort(animale.begin(),animale.end(), [](const Animal* lhs, const Animal* rhs){return lhs->getVarsta() < rhs->getVarsta();});


    for (const Animal* animal : animale) {
         cout<<"Denumire animal: "<<animal->getDenumire()<<" | Varsta: ";
        cout<<animal->getVarsta()<<endl;
    } 
    cout<< "---------------------------" << endl<< endl;


    // VECTOR STL
    //Smart pointer UNIQUE
      vector<unique_ptr<Animal>> ani;
    ani.push_back(make_unique<Animal>("Girafa", 2, "Mamifer", "Nu"));
    ani.push_back(make_unique<Animal>("Zebra", 7, "Mamifer", "Nu"));
    ani.push_back(make_unique<Animal>("Jaguar", 5, "Mamifer", "Da"));

for (const auto& animal : ani) {
        animal->getDenumire();
    }

   //cout<< director->getNrInstante();

    return 0;
}
