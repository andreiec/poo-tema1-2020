#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct nod{
    int val;
    nod* next;
};

// La crearea unei multimi noi, se apeleaza functia transformareMultime automat
// Daca acest lucru nu se doreste, atunci o simpla comentare a liniei 41 este suficienta
class MultimeDinamica{

private:
    int n;
    nod* start;

public:
    // Constructor
    MultimeDinamica(){
        this -> n = 0;
        this -> start = NULL;
    }

    // Constructor (la final apelam functia transformareMultime)
    MultimeDinamica(int n, vector<int> v) {
        this -> n = n;
        this -> start = NULL;

        // Cream lista invers intrucat este necesar sa retinem adresa primului
        // element din lista, adica adresa ultimului nod creat.
        for (vector<int>::iterator i = v.end() - 1; i != v.begin() - 1; i--) {
            nod *temp = new nod;
            temp -> val = *i;
            temp -> next = start;
            start = temp;
        }

        transformareMultime();
    }

    // Copy Constructor
    // Mai intai copiem primul element iar apoi iteram prin fiecare nod.
    // Salvam in 'last' adresa nodului creat precedent astfel incat
    // Sa putem sa completam campul 'next'.
    MultimeDinamica(const MultimeDinamica &muldin) {
        setLength(muldin.getLength());
        nod* s = muldin.getStart();

        nod* temp = new nod;
        nod* last = NULL;

        setStart(temp);

        while(s) {
            last = temp;
            temp -> val = s -> val;
            s = s -> next;

            temp = new nod;
            last -> next = temp;
        }
        last -> next = NULL;
    }

    // Destructor
    ~MultimeDinamica(){
        nod *n = this -> start;
        this -> n = 0;
        while(n){
            nod *deleteMe = n;
            n = n -> next;
            delete deleteMe;
        }
    }

    // Returneaza lungimea
    int getLength() const{
        return this -> n;
    }

    // Returneaza adresa primului element
    nod* getStart() const{
        return this -> start;
    }

    void setLength(int n) {
        this -> n = n;
    }

    void setStart(nod *p) {
        this -> start = p;
    }

    // Functie de transformare in multime
    void transformareMultime() {

        // Salvam aici valorile diferite
        unordered_set<int> viz;
        nod* curr = this -> start;
        nod* last = NULL;

        // Noua lungime
        int n = 0;

        // Luam fiecare nod si verificam daca am mai dat de el
        // Adica daca se afla in viz.
        while(curr != NULL) {
            if (viz.find(curr -> val) != viz.end()) {
                last -> next = curr -> next;
                delete(curr);
            }else{
                viz.insert(curr -> val);
                last = curr; n++;
            }
            curr = last -> next;
        }
        setLength(n);
    }

    // Overload + operator
    MultimeDinamica operator+(MultimeDinamica muldin) {

        // Cream un obiect M, si doua copii pentru primul element si al doilea (A si B)
        // "Lipim" a doua copie la prima si apelam transformareMultime pentru duplicate

        MultimeDinamica M;
        MultimeDinamica A(*this);
        MultimeDinamica B(muldin);

        M.setStart(A.getStart());

        nod* s1 = A.getStart();
        nod* s2 = B.getStart();

        while(s1 -> next != NULL) {
            s1 = s1 -> next;
        }

        // Ultimul element din A va avea ca 'next' primul din B
        s1 -> next = s2;

        M.transformareMultime();

        return M;
    }

    // Overload * operator
    MultimeDinamica operator*(MultimeDinamica muldin) {

        MultimeDinamica M;
        MultimeDinamica A(*this);
        MultimeDinamica B(muldin);

        M.setStart(A.getStart());

        nod* s1 = A.getStart();
        nod* s2 = B.getStart();
        nod* last = NULL;

        while (s1 != NULL) {
            s2 = B.getStart();
            int gasit = 0;

            // Cautam in B, pe rand, valorile din A
            while (s2 != NULL && gasit == 0) {
                if (s1 -> val == s2 -> val) {
                    gasit = 1;
                }
                s2 = s2 -> next;
            }

            // Daca nu gasim stergem din A si facem verificare daca este primul element
            // Daca da este destul doar sa incrementam inceputul listei
            if (gasit == 0) {
                if (last == NULL) {
                    M.setStart(s1 -> next);
                }else{
                    last -> next = s1 -> next;
                    delete s1;
                }
            }else{
                last = s1;
            }
            s1 = s1 -> next;
        }

        M.transformareMultime();

        return M;
    }

    MultimeDinamica operator-(MultimeDinamica muldin) {

        MultimeDinamica M;
        MultimeDinamica A(*this);
        MultimeDinamica B(muldin);

        M.setStart(A.getStart());

        nod* s1 = A.getStart();
        nod* s2 = B.getStart();
        nod* last = NULL;

        while (s1 != NULL) {
            s2 = B.getStart();
            int gasit = 0;

            // Cautam in B, pe rand, valorile din A
            while (s2 != NULL && gasit == 0) {
                if (s1 -> val == s2 -> val) {
                    gasit = 1;
                }
                s2 = s2 -> next;
            }

            // Daca gasim stergem din A si facem verificare daca este primul element
            // Daca da este destul doar sa incrementam inceputul listei
            if (gasit == 1) {
                if (last == NULL) {
                    M.setStart(s1 -> next);
                }else{
                    last -> next = s1 -> next;
                    delete s1;
                }
            }else{
                last = s1;
            }
            s1 = s1 -> next;
        }

        M.transformareMultime();

        return M;

    }

    // Functie de afisare
    void afisareMultime(){
        nod* n = start;
        while(n) {
            cout << n -> val << " ";
            n = n -> next;
        } cout << endl;
        delete n;
    }
};

int main()
{
    cout << "A: ";
    MultimeDinamica A(5, {5, 3, 4, 2, 3});
    A.afisareMultime();

    cout << "B: ";
    MultimeDinamica B(A);
    B.afisareMultime();
    cout << endl;

    MultimeDinamica C(4, {1, 3, 2, 3});
    MultimeDinamica D(5, {4, 2, 3, 6, 7});

    cout << "C: ";
    C.afisareMultime();
    cout << "D: ";
    D.afisareMultime();

    MultimeDinamica E = C + D;
    cout << endl << "E (C+D): ";
    E.afisareMultime();
    cout << "Cu lungimea: " << E.getLength() << endl;

    MultimeDinamica F = C * D;
    cout << endl << "F (C*D): ";
    F.afisareMultime();
    cout << "Cu lungimea: " << F.getLength() << endl;

    MultimeDinamica G = D - C;
    cout << endl << "G (D-C): ";
    G.afisareMultime();
    cout << "Cu lungimea: " << G.getLength() << endl;

    return 0;
}
