// Klasa implementuj¹ca listê 2 - kierunkow¹.Klasa powinna umo¿liwiaæ :
//
//	-Dodawanie, kasowanie i odczytywanie elementu z pocz¹tku, z koñca listy i w miejscu
//	 wskazywanym przez wskaŸnik na element listy(ew.iterator).
//	- Funkcjê opró¿niaj¹c¹ listê
//	- Funkcjê o wartoœciach logicznych informuj¹c¹, czy dany element nale¿y do listy
//	- Funkcjê usuwaj¹c¹ element(y) o danej wartoœci z listy(jeœli je zawiera)
//	- Wypisz zawartoœæ listy(odpowiedni operator biblioteki iostream)
//	- Informacja, ile elementów lista zawiera.
//
//Klasa iteratorów(inteligentnych wskaŸników) :
//	-powinna umo¿liwiaæ poruszanie siê po kolejnych elementach listy, za pomoc¹ operatorów
//	 ++ oraz - -(w wersji pre - i post - ), w sposób kompatybilny z wskaŸnikami do tablicy, np.
//	 odczytanie elementu oraz przejœcie na kolejny powinno byæ postaci* ptr++.
//	- przeci¹¿one operatory porównania(<, >, >= , <= , == , != ), informuj¹ce, który z iteratorów
//	 pokazuje odpowiednio wczeœniejszy, póŸniejszy itp.element listy.
//	- przeci¹¿one operatory + i - , +=, -= umo¿liwiaj¹ce przeskok o dan¹ liczbê elementów listy.
//	 Odpowiadaj¹ca konstrukcja wskaŸnika predefiniowanego to np.ptr = ptr + 5.
//	- metody umo¿liwiaj¹ce przeskok iteratora na pocz¹tek, koniec, i n - ty element listy

#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    void insertAtBeginning(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->prev = nullptr;
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
    }
    Node* insertAtEnd(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->prev = tail;
        newNode->next = nullptr;
        if (tail != nullptr) {
            tail->next = newNode;
        }
        tail = newNode;
        if (head == nullptr) {
            head = newNode;
        }
        return newNode;
    }

    void insertAt(Node* node, int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->prev = node->prev;
        newNode->next = node;
        if (node->prev != nullptr) {
            node->prev->next = newNode;
        }
        node->prev = newNode;
        if (node == head) {
            head = newNode;
        }
    }
    void deleteAtBeginning() {
        if (head == nullptr) {
            return;
        }
        Node* nodeToDelete = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        if (nodeToDelete == tail) {
            tail = nullptr;
        }
        delete nodeToDelete;
    }
    void deleteAtEnd() {
        if (tail == nullptr) {
            return;
        }
        Node* nodeToDelete = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        if (nodeToDelete == head) {
            head = nullptr;
        }
        delete nodeToDelete;
    }
    void deleteAt(Node* node) {
        if (node == nullptr) {
            return;
        }
        if (node == head) {
            deleteAtBeginning();
            return;
        }
        if (node == tail) {
            deleteAtEnd();
            return;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }
    void print() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    // odczytywanie pierwszego elementu listy
    int getFront() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    // odczytywanie ostatniego elementu listy
    int getBack() {
        if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    // odczytywanie elementu z podanej pozycji
    int getAtPosition(Node* iterator) {
        if (iterator == nullptr) {
            throw std::out_of_range("Iterator is null");
        }
        return iterator->data;
    }

    void clearList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    bool contains(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void remove(int value) {
        Node* current = head;

        // Przegl¹damy listê, dopóki nie dojdziemy do koñca
        while (current != nullptr) {
            // Jeœli wartoœæ wêz³a jest równa wartoœci, któr¹ chcemy usun¹æ
            if (current->data == value) {
                Node* prev = current->prev;
                Node* next = current->next;

                // Usuwamy bie¿¹cy wêze³, aktualizuj¹c wskaŸniki prev i next
                if (prev != nullptr) {
                    prev->next = next;
                }
                else {
                    // Usuwamy pierwszy element
                    head = next;
                }

                if (next != nullptr) {
                    next->prev = prev;
                }
                else {
                    // Usuwamy ostatni element
                    tail = prev;
                }

                // Zwolniamy pamiêæ bie¿¹cego wêz³a
                delete current;

                // Przerywamy pêtlê, aby usun¹æ tylko pierwsze wyst¹pienie wartoœci
                // Jeœli chcemy usun¹æ wszystkie wyst¹pienia wartoœci, nale¿y usun¹æ ten wiersz
                break;
            }

            current = current->next;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& list) {
        Node* current = list.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

    int size() const {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    Node* getFrontNode() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return head;
    }

    class Iterator {
    private:
        Node* ptr;

    public:
        Iterator(Node* node) : ptr(node) {}

        int& operator*() const {
            return ptr->data;
        }

        Iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        // operator porównania <
        bool operator<(const Iterator& other) const {
            return ptr < other.ptr;
        }

        // operator porównania >
        bool operator>(const Iterator& other) const {
            return ptr > other.ptr;
        }

        // operator porównania <=
        bool operator<=(const Iterator& other) const {
            return ptr <= other.ptr;
        }

        // operator porównania >=
        bool operator>=(const Iterator& other) const {
            return ptr >= other.ptr;
        }

        // operator porównania ==
        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }

        // operator porównania !=
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

        Iterator operator+(int n) {
            Iterator itr = *this;
            for (int i = 0; i < n; i++) {
                itr.ptr = itr.ptr->next;
                if (itr.ptr == nullptr) {
                    throw out_of_range("Iterator out of range");
                }
            }
            return itr;
        }
        Iterator operator-(int n) {
            Iterator itr = *this;
            for (int i = 0; i < n; i++) {
                itr.ptr = itr.ptr->prev;
                if (itr.ptr == nullptr) {
                    throw out_of_range("Iterator out of range");
                }
            }
            return itr;
        }
        Iterator& operator+=(int n) {
            for (int i = 0; i < n; i++) {
                ptr = ptr->next;
                if (ptr == nullptr) {
                    throw out_of_range("Iterator out of range");
                }
            }
            return *this;
        }
        Iterator& operator-=(int n) {
            for (int i = 0; i < n; i++) {
                ptr = ptr->prev;
                if (ptr == nullptr) {
                    throw out_of_range("Iterator out of range");
                }
            }
            return *this;
        }

    };


    // Zwraca iterator na pierwszy element listy
    Iterator begin() const {
        return Iterator(head);
    }

    // Zwraca iterator na element za ostatnim elementem listy
    Iterator end() const {
        return Iterator(tail->next);
    }
};

int main() {
    DoublyLinkedList list;
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.print(); // Output: 10 20 30 40
    list.deleteAtBeginning();
    list.deleteAtEnd();
    list.print(); // Output: 20 30
    Node* node = list.insertAtEnd(50);
    list.insertAt(node, 45);
    list.print(); // Output: 20 30 50 45
    list.deleteAt(node);
    list.print(); // Output: 20 30 45

    Node* node1 = list.insertAtEnd(10);
    Node* node2 = list.insertAtEnd(20);
    Node* node3 = list.insertAtEnd(30);
    std::cout << "First element: " << list.getFront() << std::endl;
    std::cout << "Last element: " << list.getBack() << std::endl;
    std::cout << "Element at position 2: " << list.getAtPosition(node2) << std::endl;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    std::cout << "List contains 20: " << list.contains(20) << std::endl;
    std::cout << "List contains 40: " << list.contains(40) << std::endl;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    std::cout << "Before removing 20: ";
    list.print();

    list.remove(20);

    std::cout << "After removing 20: ";
    list.print();

    std::cout << "List contents: " << list << std::endl;

    std::cout << "List size: " << list.size() << std::endl;

    list.clearList();

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    DoublyLinkedList::Iterator it = list.begin();
    std::cout << "List content: ";
    while (it != list.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    DoublyLinkedList::Iterator it1 = list.begin();
    DoublyLinkedList::Iterator it2 = list.end();
    if (it1 < it2) {
        std::cout << "it1 jest wczeœniejszy od it2" << std::endl;
    }

    list.clearList();


    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    // Porównanie wartoœci przechowywanych w ró¿nych wêz³ach listy
    if (list.getFront() < list.getBack()) {
        cout << "Wartosc przechowywana w pierwszym wezle jest mniejsza niz wartosc przechowywana w ostatnim wezle" << endl;
    }

    // Porównanie wartoœci wprowadzonej przez u¿ytkownika z wartoœciami przechowywanymi w liœcie
    int userValue;
    cout << "Podaj liczbe: ";
    cin >> userValue;

    if (list.contains(userValue)) {
        cout << "Podana liczba wystepuje w liscie" << endl;
    }
    else {
        cout << "Podana liczba nie wystepuje w liscie" << endl;
    }

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.insertAtEnd(50);
    // Przesuniêcie wskaŸnika o 3 pozycje w prawo
    Node* ptr = list.getFrontNode();
    ptr += 3;

    // Wyœwietlenie wartoœci wêz³a
    cout << "Wartosc wskazywanego wezla: " << ptr->data << endl;

    // Przesuniêcie wskaŸnika o 2 pozycje w lewo
    ptr -= 2;

    // Wyœwietlenie wartoœci wêz³a
    cout << "Wartosc wskazywanego wezla: " << ptr->data << endl;

    // Przesuniêcie wskaŸnika o 1 pozycjê w prawo za pomoc¹ skróconego przypisania z dodawaniem
    ptr += 1;

    // Wyœwietlenie wartoœci wêz³a
    cout << "Wartosc wskazywanego wezla: " << ptr->data << endl;

    // Przesuniêcie wskaŸnika o 2 pozycje w lewo za pomoc¹ skróconego przypisania z odejmowaniem
    ptr -= 2;

    // Wyœwietlenie wartoœci wêz³a
    cout << "Wartosc wskazywanego wezla: " << ptr->data << endl;

    return 0;
}