//|=================== TEMA 3 POO ======================|// 
//| link GitHub:                                        |//
//|     https://github.com/dulumanandrada/Tema3_POO     |//
//|                                                     |//
//|=====================================================|//


#include <iostream>
#include <cstring>
#include <vector>
#include <vector>
#include <typeinfo>

using namespace std;



//==================== LOCUINTA ====================//
//clasa abstracta --->vazuta ca interfata ---> nu poate instantia obiecte
class Locuinta
{
    //encapsulare 
protected:    
    string numeClient;
    int suprafataUtila;
    float discount;

public:
    virtual void citire();
    virtual void afisare();
    friend istream& operator>> (istream&, Locuinta&);
    friend ostream& operator<< (ostream&, Locuinta&);
    virtual float CalculChirie() = 0;

    //get-eri:
    string getNumeClient(){return numeClient;}

    bool operator== (Locuinta& l1)
    {
        return numeClient == l1.numeClient && suprafataUtila == l1.suprafataUtila && discount == l1.discount;
    }

    Locuinta& operator= (Locuinta& l)
    {
        if(this != &l)
        {
            this->numeClient = l.numeClient;
            this->suprafataUtila = l.suprafataUtila;
            this->discount = l.discount;
        }
        return *this;
    }
    
    //constructori:
    Locuinta()
    {
        numeClient = "";
        suprafataUtila = 0;
        discount = 0;
    }

    Locuinta(string s, int sU, float d)
    {
        numeClient = s;         
        suprafataUtila = sU;    
        discount = d;          
    }

    Locuinta(const Locuinta& l)
    {
        numeClient = l.numeClient;
        suprafataUtila = l.suprafataUtila;
        discount = l.discount;
    }

    ///=> memory leak ------> se rezolva prin destructor virtual:
    virtual ~Locuinta() {cout << "~Locuinta \n";}
};


void Locuinta::citire()
{
    //exceptiile:
    bool ok = 0;
    do
    {
        if(ok > 0) cout << "Incercati din nou: \n";
        try
        {
            cout << "Nume client: ";
            cin >> numeClient;
            for(int i = 0; numeClient[i]; i++)
                if(isalpha(numeClient[i]) == 0) throw -9;     

            cout << "Suprafata utila: ";
            cin >> suprafataUtila;    
            if(suprafataUtila < 0) throw -1;
        
            cout << "Discount: ";
            cin >> discount;
            if(discount > 100) throw -13;
            else if(discount < 0) throw -14;  
            ok = 0;
        }
    
        catch(int n)
        {
            if(n == -1)
                cout << "Valoarea introdusa pentru suprafata utila este invalida! Aceasta nu poate fi un numar negativ! \n";
            else if(n == -9) cout << "Numele introdus este unul invalid! \n";
            else if(n == -13) cout << "Valoarea introdusa pentru discount este invalida! Aceasta nu poate fi mai mare de 100%! \n";
            else if(n == -14) cout << "Valoarea introdusa pentru discount este invalida! Aceasta nu poate fi una negativa! \n";
            ok = 1;
        }
    }while(ok != 0);
}

void Locuinta::afisare()
{
    cout << "Nume client: ";
    cout << numeClient << "\n";
    cout << "Suprafata utila: ";
    cout << suprafataUtila << "\n";
    cout << "Discount: ";
    cout << discount << "\n"; 
}

istream& operator>> (istream& in, Locuinta& l)
{
    //exceptiile:
    bool ok = 0;
    do
    {
        if(ok > 0) cout << "Incercati din nou: \n";
        try
        {
            cout << "Nume client: ";
            in >> l.numeClient;
            for(int i = 0; l.numeClient[i]; i++)
                if(isalpha(l.numeClient[i]) == 0) throw -9;     

            cout << "Suprafata utila: ";
            in >> l.suprafataUtila;    
            if(l.suprafataUtila < 0) throw -1;
        
            cout << "Discount: ";
            in >> l.discount;
            if(l.discount > 100) throw -13;
            else if(l.discount < 0) throw -14;  
            ok = 0;
        }
    
        catch(int n)
        {
            if(n == -1)
                cout << "Valoarea introdusa pentru suprafata utila este invalida! Aceasta nu poate fi un numar negativ! \n";
            else if(n == -9) cout << "Numele introdus este unul invalid! \n";
            else if(n == -13) cout << "Valoarea introdusa pentru discount este invalida! Aceasta nu poate fi mai mare de 100%! \n";
            else if(n == -14) cout << "Valoarea introdusa pentru discount este invalida! Aceasta nu poate fi una negativa! \n";
            ok = 1;
        }
    }while(ok != 0);
    return in;
}

ostream& operator<< (ostream& out, Locuinta& l)
{
    cout << "Nume client: ";
    out << l.numeClient << "\n";
    cout << "Suprafata utila: ";
    out << l.suprafataUtila << "\n";
    cout << "Discount: ";
    out << l.discount << "\n";
    return out;
}



//================== APARTAMENT ===================//
class Apartament: public Locuinta
{
    int etaj;

public:
    void citire();
    void afisare();
    friend istream& operator>> (istream&, Apartament&);
    friend ostream& operator<< (ostream&, Apartament&);
    float CalculChirie();

    Apartament& operator= (Apartament& a)
    {
        if(this != &a)
        {
            this->Locuinta::operator=(a);
            this->etaj = a.etaj;
        }
        return *this;
    }

    bool operator== (Apartament& a)
    {
        return Locuinta::operator==(a) && etaj == a.etaj;
    }

    //constructori:
    Apartament():Locuinta()
    {
        etaj = 0;
    }
    Apartament(string s, int sU, float d, int e);

    ///destructor:
    ~Apartament() {cout << "~Apartament \n";}
};

Apartament:: Apartament(string s, int sU = 0, float d = 0, int e = 0): Locuinta(s, sU, d)
{
    etaj = e;
}

void Apartament::citire()
{
    Locuinta::citire();
    cout << "Etaj: ";
    cin >> etaj;
}

void Apartament::afisare()
{
    cout << "Locuinta de tip: Apartament \n";
    Locuinta::afisare();
    cout << "Etaj: ";
    cout << etaj << "\n";
}

istream& operator>> (istream& in, Apartament& a)
{
    in >> dynamic_cast<Locuinta&> (a);
    cout << "Etaj: ";
    in >> a.etaj;
    return in;
}

ostream& operator<< (ostream& out, Apartament& a)
{
    out << "Locuinta de tip: Apartament \n";
    out << dynamic_cast<Locuinta&> (a);
    out << "Etaj: ";
    out << a.etaj << "\n";
    return out;
}


float Apartament::CalculChirie()
{
    try
    {
        float pret;
        int d;
        cout << "Care este tariful actual pentru chirie /mp? (nr. intreg) \n";
        cin >> pret;
        cout << "Se aplica discountul pentru fiecare locuinta? 1-da 0-nu \n";
        cin >> d;
        if(pret > 0 && (d == 0 || d == 1)) 
        {
            float chirie;
            chirie = pret * suprafataUtila * (1 - d * discount / 100.0);
            return chirie; 
        }
        else throw 23;
    }
    catch(int x)
    {
        if(x == 23) cout << "ERROR! Valoarea chiriei pe mp nu poate fi <= 0, iar discountul diferit de 0 sau 1. \n";
    }  
}


//===================== CASA =====================//
class Casa: public Locuinta
{
    int suprafataCurte;
    int nrEtaje;
    float *suprafataEtaj;

public:
    void citire();
    void afisare();
    friend istream& operator>> (istream&, Casa&);
    friend ostream& operator<< (ostream&, Casa&);
    float CalculChirie();

    Casa& operator= (Casa& c)
    {
        if(this != &c)
        {
            this->Locuinta::operator=(c);
            this->suprafataCurte = c.suprafataCurte;
            this->nrEtaje = c.nrEtaje;
            for(int i = 0; i < c.nrEtaje; i++)
            {
                this->suprafataEtaj[i] = c.suprafataEtaj[i];
            }
        }
        return *this;
    }

    //constructori:
    Casa():Locuinta()
    {
        suprafataCurte = 0;
        nrEtaje = 0;
        suprafataEtaj = 0;
    }

    Casa(string s, int sU, float d, int sC, int nE, float *sE);

    ///destructor:
    ~Casa() {cout << "~Casa \n";}
};

Casa:: Casa(string s, int sU = 0, float d = 0, int sC = 0, int nE = 0, float *sE = NULL): Locuinta(s, sU, d)
{
    suprafataCurte = sC;
    nrEtaje = nE;
    suprafataEtaj = new float[nrEtaje + 1];
    sE = new float[nE + 1];
    for(int i = 0; i < nrEtaje; i++)
        suprafataEtaj[i] = sE[i];

}

void Casa::citire()
{
    Locuinta::citire();
    bool ok = 0;
    do
    {
        if(ok > 0) cout << "Incercati din nou: \n";
        try
        {
            cout << "Suprafata curte: ";
            cin >> suprafataCurte;
            if(suprafataCurte < 0) throw -20; 
            cout << "Numarul de etaje: \n";
            cin >> nrEtaje;
            suprafataEtaj = new float[nrEtaje + 1];
            cout << "\nSuprafata fiecarui etaj in parte: \n";
            for(int i = 0; i < nrEtaje; i++)
                {
                    cout << "etaj " << i + 1 << ". ";
                    cin >> suprafataEtaj[i];
                }
            ok = 0;
        }
        catch(int x)
        {
            if(x == -20) 
                cout << "Valoarea introdusa pentru suprafata de curte este invalida! Aceasta nu poate fi un numar negativ! \n"; 
            ok = 1;
        }
        
    } while (ok != 0);
}

void Casa::afisare()
{
    cout << "Locuinta de tip: Casa \n";
    Locuinta::afisare();
    cout << "Suprafata curte: ";
    cout << suprafataCurte << "\n";
    cout << "Numarul de etaje: \n";
    cout << nrEtaje;
    cout << "Suprafata fiecarui etaj in parte: \n";
    for(int i = 0; i < nrEtaje; i++)
    {
        cout << "etaj " << i + 1 << ". ";
        cout << suprafataEtaj[i] << "\n";
    }
}

istream& operator>> (istream& in, Casa& c)
{
    in >> dynamic_cast<Locuinta&> (c);
    bool ok = 0;
    do
    {
        if(ok > 0) cout << "Incercati din nou: \n";
        try
        {
            cout << "Suprafata curte: ";
            in >> c.suprafataCurte;
            if(c.suprafataCurte < 0) throw -20; 
            cout << "Numarul de etaje: \n";
            in >> c.nrEtaje;
            c.suprafataEtaj = new float[c.nrEtaje + 1];
            cout << "\nSuprafata fiecarui etaj in parte: \n";
            for(int i = 0; i < c.nrEtaje; i++)
                {
                    cout << "etaj " << i + 1 << ". ";
                    in >> c.suprafataEtaj[i];
                }
            ok = 0;
        }
        catch(int x)
        {
            if(x == -20) 
                cout <<"Valoarea introdusa pentru suprafata de curte este invalida! Aceasta nu poate fi un numar negativ! \n"; 
            ok = 1;
        }
        
    } while (ok != 0);
    return in;
}

ostream& operator<< (ostream& out, Casa& c)
{
    out << "Locuinta de tip: Casa \n";
    out << dynamic_cast<Locuinta&> (c);
    out << "Suprafata curte: ";
    out << c.suprafataCurte << "\n";
    out << "Numarul de etaje: \n";
    out << c.nrEtaje;
    out << "Suprafata fiecarui etaj in parte: \n";
    for(int i = 0; i < c.nrEtaje; i++)
    {
        out << "etaj " << i + 1 << ". ";
        out << c.suprafataEtaj[i] << "\n";
    }
    return out;
}

float Casa::CalculChirie()
{
    try
    {
        float pret;
        int d;
        cout << "Care este tariful actual pentru chirie /mp? (nr. intreg) \n";
        cin >> pret;
        cout << "Se aplica discountul pentru fiecare locuinta? 1-da 0-nu \n";
        cin >> d;
        if(pret > 0 && (d == 0 || d == 1)) 
        {
            float chirie;
            chirie = pret * (suprafataUtila + 0.2 * suprafataCurte) * (1 - d * discount / 100.0);
            return chirie; 
        }
        else throw 23;
    }
    catch(int x)
    {
        if(x == 23) cout << "ERROR! Valoarea chiriei pe mp nu poate fi <= 0, iar discountul diferit de 0 sau 1. \n";
    }  
}


//==========================
template <class T>
class Gestiune
{
    vector <pair< int, T>> G;
    static int ID;
    int id;

public:
    void citire();
    void afisare();

    //constructori
    Gestiune();
};

template <class T>
int Gestiune<T>::ID=0;

template <class T>
Gestiune<T>::Gestiune(){}

template <class T>
void Gestiune<T>::citire()
{
    T t;
    int nrl;
    cout << "Numarul de locuinte : ";
    cin >> nrl;
    for(int i = 0; i < nrl; i++)
    {
        cin >> t;
        Gestiune<T>::ID++;
        G.push_back(make_pair(ID, t));
    }

}

template <class T>
void Gestiune<T>::afisare()
{
    for(int i = 0; i < G.size(); i++)
    {
        cout << G[i].first << ". ";
        (G[i].second).afisare();
        cout << "\n";
    }
}

//========= specializare tipul Casa
template<>
class Gestiune<Casa>
{
    Casa c;
    vector < pair<Casa, float>> casa;
    int nrc;
    float schirie;
    float total;

public:
    void citire();
    void afisare();

    //constructor
    Gestiune()
    {
        nrc = 0;
        total = 0;
    }

};

void Gestiune<Casa>::citire()
{
    cout << "Nr de case: \n";
    cin >> nrc;
    for(int i = 1; i <= nrc; i++)
    {
        cin >> c;
        schirie = c.CalculChirie();
        total += schirie;
        casa.push_back(make_pair(c, schirie));
    }
}

void Gestiune<Casa>::afisare()
{
    cout << "Numarul de case : " << nrc << "\n";
    for(int i = 0; i < casa.size(); i++)
    {
        (casa[i].first).afisare();
        cout << "Chiria = " << (casa[i].second) << "\n\n";
    }

    cout << "Totalul incasat din inchirierea caselor = " << total << "\n";
}


int main()
{
    Gestiune<Apartament> ap;
    Gestiune<Casa> ca;
    ap.citire();
    ca.citire();

    ap.afisare();
    ca.afisare();
    return 0;
}

