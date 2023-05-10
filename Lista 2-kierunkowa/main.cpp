// Klasa implementuj�ca list� 2 - kierunkow�.Klasa powinna umo�liwia� :
//
//	-Dodawanie, kasowanie i odczytywanie elementu z pocz�tku, z ko�ca listy i w miejscu
//	 wskazywanym przez wska�nik na element listy(ew.iterator).
//	- Funkcj� opr�niaj�c� list�
//	- Funkcj� o warto�ciach logicznych informuj�c�, czy dany element nale�y do listy
//	- Funkcj� usuwaj�c� element(y) o danej warto�ci z listy(je�li je zawiera)
//	- Wypisz zawarto�� listy(odpowiedni operator biblioteki iostream)
//	- Informacja, ile element�w lista zawiera.
//
//Klasa iterator�w(inteligentnych wska�nik�w) :
//	-powinna umo�liwia� poruszanie si� po kolejnych elementach listy, za pomoc� operator�w
//	 ++ oraz - -(w wersji pre - i post - ), w spos�b kompatybilny z wska�nikami do tablicy, np.
//	 odczytanie elementu oraz przej�cie na kolejny powinno by� postaci* ptr++.
//	- przeci��one operatory por�wnania(<, >, >= , <= , == , != ), informuj�ce, kt�ry z iterator�w
//	 pokazuje odpowiednio wcze�niejszy, p�niejszy itp.element listy.
//	- przeci��one operatory + i - , +=, -= umo�liwiaj�ce przeskok o dan� liczb� element�w listy.
//	 Odpowiadaj�ca konstrukcja wska�nika predefiniowanego to np.ptr = ptr + 5.
//	- metody umo�liwiaj�ce przeskok iteratora na pocz�tek, koniec, i n - ty element listy

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

        // Przegl�damy list�, dop�ki nie dojdziemy do ko�ca
        while (current != nullptr) {
            // Je�li warto�� w�z�a jest r�wna warto�ci, kt�r� chcemy usun��
            if (current->data == value) {
                Node* prev = current->prev;
                Node* next = current->next;

                // Usuwamy bie��cy w�ze�, aktualizuj�c wska�niki prev i next
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

                // Zwolniamy pami�� bie��cego w�z�a
                delete current;

                // Przerywamy p�tl�, aby usun�� tylko pierwsze wyst�pienie warto�ci
                // Je�li chcemy usun�� wszystkie wyst�pienia warto�ci, nale�y usun�� ten wiersz
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

        // operator por�wnania <
        bool operator<(const Iterator& other) const {
            return ptr < other.ptr;
        }

        // operator por�wnania >
        bool operator>(const Iterator& other) const {
            return ptr > other.ptr;
        }

        // operator por�wnania <=
        bool operator<=(const Iterator& other) const {
            return ptr <= other.ptr;
        }

        // operator por�wnania >=
        bool operator>=(const Iterator& other) const {
            return ptr >= other.ptr;
        }

        // operator por�wnania ==
        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }

        // operator por�wnania !=
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
        std::cout << "it1 jest wcze�niejszy od it2" << std::endl;
    }

    list.clearList();


    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    // Por�wnanie warto�ci przechowywanych w r�nych w�z�ach listy
    if (list.getFront() < list.getBack()) {
        cout << "Wartosc przechowywana w pierwszym wezle jest mniejsza niz wartosc przechowywana w ostatnim wezle" << endl;
    }

    // Por�wnanie warto�ci wprowadzonej przez u�ytkownika z warto�ciami przechowywanymi w li�cie
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
    // Przesuni�cie wska�nika o 3 pozycje w prawo
    Node* ptr = list.getFrontNode();
    ptr += 3;

    // Wy�wietlenie warto�ci w�z�a
    cout << "Wartosc wskazywanego wezla: " << ptr->data << endl;

    // Przesuni�cie wska�nika o 2 pozycje w lewo
    ptr -= 2;

    // Wy�wietlenie warto�ci w�z�a
    cout << "Wartosc wskazywanego wezla: " << ptr->data << endl;

    // Przesuni�cie wska�nika o 1 pozycj� w prawo za pomoc� skr�conego przypisania z dodawaniem
    ptr += 1;

    // Wy�wietlenie warto�ci w�z�a
    cout << "Wartosc wskazywanego wezla: " << ptr->data << endl;

    // Przesuni�cie wska�nika o 2 pozycje w lewo za pomoc� skr�conego przypisania z odejmowaniem
    ptr -= 2;

    // Wy�wietlenie warto�ci w�z�a
    cout << "Wartosc wskazywanego wezla: " << ptr->data << endl;

    return 0;
}