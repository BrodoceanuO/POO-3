#include <iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include <bits/stdc++.h>
#include <math.h>
#include <typeinfo>
#include <fstream>

using namespace std;

class PizzerieX;
class Bautura;

bool contains_number(const std::string &c)
{
    if (c.find('0') != std::string::npos ||
        c.find('1') != std::string::npos ||
        c.find('2') != std::string::npos ||
        c.find('3') != std::string::npos ||
        c.find('4') != std::string::npos ||
        c.find('5') != std::string::npos ||
        c.find('6') != std::string::npos ||
        c.find('7') != std::string::npos ||
        c.find('8') != std::string::npos ||
        c.find('9') != std::string::npos)
    {
        return true;
    }

    return false;
}

class Bautura
{
private:
    string nume;
    float pret;
public:
    Bautura(string nume,float Pret);
    Bautura();
    ~Bautura();
    friend istream& operator>>(istream& in,Bautura& ob);
    Bautura& operator=(Bautura& ob);
   // template<class T>
   // friend class Meniu;
};

Bautura::Bautura()
{
nume="Fara descriere";
pret=0;
}

Bautura::Bautura(string Nume,float Pret)
{
nume=Nume;
pret=Pret;
}

Bautura& Bautura::operator=(Bautura& ob)
{
nume=ob.nume;
pret=ob.pret;
return *this;
}

istream& operator>>(istream& in,Bautura& ob)
{
cout<<"Introduceti numele bauturii: "<<endl;
in>>ob.nume;
cout<<"Introduceti pretul bauturii: "<<endl;
in>>ob.pret;
return in;
}

Bautura::~Bautura()
{
pret=0;
}


class PretPizza
{
protected:
    float pret;
public:
    virtual float calcPret(float,float,float,float)=0;
};

class Ingredient
{
private:
    string nume;
    float pret;
    int cantitate;
    friend class Pizza;
public:
    Ingredient();
    ~Ingredient();
    Ingredient(string Nume,float Pret,int Cantitate);
    friend ostream& operator<<(ostream& out,Ingredient& ob);
    friend istream& operator>>(istream& in,Ingredient& ob);
    Ingredient operator=(const Ingredient& ob);
};

istream& operator>>(istream& in,Ingredient& ob)
{
cout<<"Introduceti numele ingredientului: ";
in>>ob.nume;
cout<<endl<<"Introduceti pretul ingredientului: ";
in>>ob.pret;
cout<<endl<<"Introduceti cantitatea inredientului: ";
in>>ob.cantitate;
cout<<endl;
return in;
}

Ingredient Ingredient::operator=(const Ingredient& ob)
{
nume=ob.nume;
pret=ob.pret;
cantitate=ob.cantitate;
return *this;
}


Ingredient::~Ingredient()
{
pret=0;
cantitate=0;
}

Ingredient::Ingredient()
{
nume="Fara descriere";
pret=0;
cantitate=0;
}

Ingredient::Ingredient(string Nume,float Pret,int Cantitate)
{
nume=Nume;
pret=Pret;
cantitate=Cantitate;
}

ostream& operator<<(ostream& out,Ingredient& ob)
{
out<<ob.nume<<" "<<ob.pret<<"$ "<<ob.cantitate<<"g"<<endl;
return out;
}


vector<Ingredient> lista_ingrediente(bool veg)
{
Ingredient salam("salam",10,50);
Ingredient cascaval("cascaval",12,70);
Ingredient faina("faina",1,100);
Ingredient apa("apa",0.1,50);
Ingredient mozzarella("mozzarella",15,70);
Ingredient rosie("rosie",3,50);
Ingredient sos_tomat("sos_tomat",5,50);
Ingredient usturoi("usturoi",2,25);
Ingredient sare("sare",1,20);
Ingredient carnati("carnati",3,10);
Ingredient sunca("sunca",2,10);
Ingredient muschi("muschi",2,10);
Ingredient porumb("porumb",1,20);
vector<Ingredient> Lista;
if (veg==0)
    {
    Lista.push_back(salam);
    Lista.push_back(carnati);
    Lista.push_back(sunca);
    Lista.push_back(muschi);
    }
Lista.push_back(porumb);
Lista.push_back(cascaval);
Lista.push_back(faina);
Lista.push_back(apa);
Lista.push_back(mozzarella);
Lista.push_back(rosie);
Lista.push_back(sos_tomat);
Lista.push_back(usturoi);
Lista.push_back(sare);
return Lista;
}

class Pizza: public PretPizza
{
private:
    string nume;
    vector<Ingredient> lista;
    bool online;
    float pret_manopera;
    int vanzari;
    bool veg;
public:
    Pizza();
    Pizza(string Nume,string Id,vector<Ingredient> Lista,bool online,float Pret_manopera);
    ~Pizza();
    float calcPret(float,float,float,float);
    friend ostream& operator<<(ostream& out,Pizza& ob);
    friend istream& operator>>(istream& in,Pizza& ob);
    Pizza& operator=(Pizza& ob);
    string get_nume(){return nume;}
    float get_pret(){return pret;}
    bool get_online(){return online;}
    int get_vanzari(){return vanzari;}
    void set_vanzari(int nr){vanzari=vanzari+nr;}
    vector<Ingredient> get_lista(){return lista;}
    bool get_veg(){return veg;}
    void operator+=(int nr);
friend class PizzerieX;
};

void Pizza::operator+=(int nr)
{
vanzari=vanzari+nr;
}

Pizza::~Pizza()
{

}

istream& operator>>(istream& in,Pizza& ob)
{
cout<<"Introduceti numele noului tip de Pizza:  ";
int error;
try
{
in>>ob.nume;
if (contains_number(ob.nume)==1)
    throw error;
}
catch(int)
{
cout<<"Contine numere! "<<endl;
}
cout<<endl<<"Introduceti pretul manoperei: ";
in>>ob.pret_manopera;
cout<<endl<<"Pizza a fost comandata online? y/n"<<endl;
char c;
tag:
in>>c;
if (c=='y')
    ob.online=true;
else if (c=='n')
    ob.online=false;
else
    {
    cout<<"Comanda invalida! ( y/n )"<<endl;
    goto tag;
    }
cout<<"Pizza este vegetariana? y/n"<<endl;
tag2:
in>>c;
if (c=='y')
    ob.veg=true;
else if (c=='n')
    ob.veg=false;
else
    {
    cout<<"Comanda invalida! ( y/n )"<<endl;
    goto tag2;
    }
bool veget=ob.veg;
vector<Ingredient> v=lista_ingrediente(veget);
tag0:cout<<"Lista de ingrediente posibile este urmatoarea: "<<endl<<endl;
for (int i=0;i<v.size();i++)
    cout<<i<<": "<<v[i];
cout<<"Introduceti numarul ingredientelor care vreti sa fie adaugate: ";
int j;
tag1:cin>>j;
vector<int>::iterator it;
if ((j<0 || j>v.size()) && v.size()!=0)
    {
    cout<<"Numarul nu este valid! Reintroduceti: "<<endl;
    goto tag1;
    }
else if (v.size()==0)
    {
    cout<<"Toate ingredientele au fost adaugate."<<endl;
    }
else
    {
    ob.lista.push_back(v[j]);
    v.erase(v.begin()+j);
    cout<<"Doriti sa mai adaugati un element ? y/n"<<endl;
    char c;
    in>>c;
    if (c!='y' && c!='n')
    {
        cout<<"Nu este o comanda valida! Am oprit introducerea!"<<endl;
        return in;
    }
    else if (c=='y')
        goto tag0;
    else if (c=='n')
        return in;
    }
return in;
}

Pizza& Pizza::operator=(Pizza& ob)
{
pret=ob.pret;
pret_manopera=ob.pret_manopera;
nume=ob.nume;
lista=ob.lista;
online=ob.online;
vanzari=ob.vanzari;
return *this;
}

float Pizza::calcPret(float coord_x=0,float coord_y=0,float x_p=0,float y_p=0)
{
pret=pret_manopera;
for (int i=0;i<lista.size();i++)
    {
    pret=pret+lista[i].pret;
    }
float dist;
if (online==true)
    {
    dist=sqrt(pow(coord_x-x_p,2)+pow(coord_y-y_p,2));
    int pr=(int)dist%10;
    float pret_initial=pret;
    for (int i=0;i<pr;i++)
        pret=pret+pret_initial*(0.05);
    }
return pret;
}

Pizza::Pizza()
{
pret=0;
pret_manopera=0;
nume="Fara descriere";
vanzari=0;
}

Pizza::Pizza(string Nume,string Id,vector<Ingredient> Lista,bool Online,float Pret_manopera)
{
pret=0;
nume=Nume;
lista=Lista;
online=Online;
pret_manopera=Pret_manopera;
vanzari=0;
}

ostream& operator<<(ostream& out,Pizza& ob)
{
out<<ob.nume<<endl;
out<<"Ingrediente: "<<endl<<endl;
for (int i=0;i<ob.lista.size();i++)
    out<<ob.lista[i];
cout<<endl<<"Pretul manoperei este: "<<ob.pret_manopera<<endl;
cout<<endl<<"Pret: "<<ob.pret<<"$"<<endl<<endl;
cout<<"Acest tip de pizza a fost vandut de "<<ob.vanzari<<" ori"<<endl;
return out;
}

void print_unordered_map(unordered_map<string,vector<Ingredient>> Lista_pizza)
{
unordered_map<string,vector<Ingredient>>::iterator it;
for (it = Lista_pizza.begin(); it!=Lista_pizza.end();it++)
    {
        cout << it->first<<endl<<endl;
        for (int i=0;i<it->second.size();i++)
            cout<<it->second[i];
        cout<<endl<<endl;
    }
}

template<class T>
class Meniu
{
    T* v;
    int n;
public:
    Meniu(T*,int);
    Meniu(int N);
    Meniu();
    ~Meniu();
    Meniu<T>& operator=(Meniu& ob);
    friend istream& operator>>(istream& in,const Meniu<T>& ob);
    friend istream& operator>>(istream& in,Meniu<Bautura>& ob); //specializare
    int set_n(int m){n=m;}
    int get_n(){return n;}

    template<class U>
    friend ostream& operator<<(ostream& out,const Meniu<U>& ob);

friend class PizzerieX;
friend istream& operator>>(istream& in,PizzerieX& ob);
};

template<class T>
Meniu<T>::Meniu(int N)
{
n=N;
v=new T[n];
}

template<class T>
ostream& operator<<(ostream& out,const Meniu<T>& ob)
{
out<<"Acest meniu contine "<<ob.n<<" tipuri de pizza"<<endl;
for (int i=0;i<ob.n;i++)
    out<<ob.v[i];
out<<endl;
return out;
}

template<class T>
istream& operator>>(istream& in,const Meniu<T>& ob)
{
T* new_vector;
new_vector=new T[ob.n+2];
for (int i=0;i<ob.n;i++)
    new_vector[i]=ob.v[i];
in>>new_vector[ob.n+1];
ob.v=&new_vector;
return in;
}

istream& operator>>(istream& in,Meniu<Bautura>& ob)
{
Bautura* new_vector;
new_vector=new Bautura[ob.n+2];
for (int i=0;i<ob.n;i++)
    new_vector[i]=ob.v[i];
in>>new_vector[ob.n+1];
ob.v=new_vector;
return in;
}

template<class T>
Meniu<T>::Meniu()
{
n=1;
v=NULL;
}

template<class T>
Meniu<T>& Meniu<T>::operator=(Meniu<T>& ob)
{
n=ob.n;
v=new T[ob.n];
for (int i=0;i<ob.n;i++)
    v[i]=ob.v[i];
return *this;
}

template<class T>
Meniu<T>::Meniu(T* vector_pizza,int marime)
{
n=marime;
v=new T[n];
for (int i=0;i<n;i++)
    v[i]=vector_pizza[i];
}

template<class T>
Meniu<T>::~Meniu()
{
delete[] v;
}


class PizzerieX
{
private:
    float coord_x;
    float coord_y;
    Meniu<Pizza> meniu;
    unordered_map<string,vector<Ingredient>> Lista_pizza;
    static int numar;
    const string proprietar="Steven King";
public:
    PizzerieX(float Coord_x,float Coord_y,Meniu<Pizza>& Men);
    ~PizzerieX();
    PizzerieX& operator=(PizzerieX& ob);
    const string get_proprietar(){return proprietar;}
    friend istream& operator>>(istream& in,PizzerieX& ob);
    static int get_numar(){return numar;}
    void file();
};

istream& operator>>(istream& in,PizzerieX& ob)
{
in>>ob.coord_x;
in>>ob.coord_y;
int n;
Pizza temp;
cout<<"Cate tipuri de pizza va avea meniul?"<<endl;
cin>>ob.meniu.n;
for (int i=0;i<n;i++)
    {
    cin>>temp;
    ob.meniu.v[i]=temp;
    }
for (int i=0;i<ob.meniu.n;i++)
    {
    ob.Lista_pizza.emplace(ob.meniu.v[i].get_nume(),ob.meniu.v[i].get_lista());
    }
return in;
}


PizzerieX& PizzerieX::operator=(PizzerieX& ob)
{
coord_x=ob.coord_x;
coord_y=ob.coord_y;
meniu=ob.meniu;
Lista_pizza=ob.Lista_pizza;
numar=ob.numar;
return *this;
}

PizzerieX::PizzerieX(float Coord_x,float Coord_y,Meniu<Pizza>& Men)
{
coord_x=Coord_x;
coord_y=Coord_y;
meniu=Men;
for (int i=0;i<meniu.n;i++)
    Lista_pizza.emplace(meniu.v[i].nume,meniu.v[i].lista);
numar++;
}

PizzerieX::~PizzerieX()
{

}

int PizzerieX::numar=0;

void PizzerieX::file()
{
ofstream f;
f.open("Pizza_Vegetariana.txt");
float suma=0;
for (int i=0;i<(*this).meniu.n;i++)
    {
     if ((*this).meniu.v[i].veg==true)
         {
            f<<(*this).meniu.v[i].nume<<"  "<<(*this).meniu.v[i].pret<<"\n";
            suma=suma+(*this).meniu.v[i].vanzari*(*this).meniu.v[i].pret;
         }
    }
f<<"\n"<<"suma este: "<<suma<<endl;
f.close();
}

int main()
{
float x_p,y_p;
int error1;
vector<Pizza> pizza;
cout<<"Introduceti coordonatele Pizzeriei dumneavoastra: "<<endl;
cout<<"coordoanata x: ";
try
{
cin>>x_p;
if (typeid(x_p)!=typeid(float))
    throw error1;
}
catch(int)
{
    cout<<"Input invalid!"<<endl;
    return 0;
}
cout<<endl<<"coordonata y: ";
try
{
cin>>y_p;
if (typeid(y_p)!=typeid(float))
    throw error1;
}
catch(int)
{
    cout<<"Input invalid!"<<endl;
    return 0;
}
cout<<endl;
char c;
Pizza* prototip;
Pizza Temp;
int increment;
int nr_produs;
while (c!='X')
    {
     cout<<"Introduceti comanda dorita: "<<endl;
     cin>>c;
     switch (c)
        {
        case 'a':
            cout<<"Ati ales sa adaugati o pizza la meniul pizzeriei: "<<endl;
            prototip = new Pizza();
            cin>>*prototip;
            Temp=*prototip;
            pizza.push_back(Temp);
            break;
        case 'b':
            cout<<"Ati ales sa calculati pretul pizzelor din lista curenta: "<<endl;
            for (int i=0;i<pizza.size();i++)
            {
                if (pizza[i].get_pret()!=0)
                    continue;
                if (pizza[i].get_online()==1)
                {
                    cout<<"Pizza "<<pizza[i].get_nume()<<" a fost comandata online, introduceti coordonatele cumparatorului: "<<endl;
                    float x,y;
                    cout<<"coordoanata x: ";
                    try
                    {
                    cin>>x;
                    if (typeid(x)!=typeid(float))
                        throw error1;
                    }
                    catch(int)
                    {
                        cout<<"Input invalid!"<<endl;
                        return 0;
                    }
                    cout<<endl<<"coordonata y: ";
                    try
                    {
                    cin>>y;
                    if (typeid(y)!=typeid(float))
                        throw error1;
                    }
                    catch(int)
                    {
                        cout<<"Input invalid!"<<endl;
                        return 0;
                    }
                    cout<<endl;
                    pizza[i].calcPret(x,y,x_p,y_p);
                }
                else
                    pizza[i].calcPret();
            }
        break;
        case 'c':
            cout<<"Ati ales sa afisati lista de pizza ce se va afla in meniul pizzeriei: "<<endl;
            for (int i=0;i<pizza.size();i++)
                cout<<pizza[i]<<endl;
            break;
        case 'd':
            cout<<"Ati ales sa incrementati vanzarea unui produs: "<<endl;
            cout<<"Introduceti numarul produsului incrementat: "<<endl;
            try
            {
            int error2;
            cin>>nr_produs;
            if (nr_produs < 0 || nr_produs > pizza.size())
                throw error1;
            }
            catch(int)
            {
                cout<<"Nu ati introdus ceva valid!"<<endl;
                return 0;
            }
            cout<<"Cu cat doriti sa incremenetati? "<<endl;
            cin>>increment;
            //pizza[nr_produs].set_vanzari(increment);
            pizza[nr_produs]+=increment;
            break;
        }
    }
Pizza* p_array=&pizza[0];
Meniu<Pizza> meniu(p_array,pizza.size());
cout<<meniu;
PizzerieX restaurant(x_p,y_p,meniu);
restaurant.file();
cout<<"Sunt deschise "restaurant.get_numar()<<" restaurante"<<endl;
/*Meniu<Bautura> bauturi(2); // meniu poate lua mai multe tipuri de obiecte
for (int i=0;i<2;i++)
    cin>>bauturi;
if (typeid(restaurant)==typeid(meniu))
    cout<<"Produsele sunt diferite"<<endl; */
return 0;
}
