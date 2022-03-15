#include <iostream>
using namespace std;

class Student {
    string name;
    string group;
    string spec;
public:
    Student(string name = "", string group = "", string spec = "") :name(name), group(group), spec(spec) {
    }
    friend ostream& operator<<(ostream& out, Student& val)
    {
        out << "Имя: " << val.name << " "
            << "Группа: " << val.group << " "
            << "Специальность: " << val.spec << "." << endl;
        return out;
    }
    friend istream& operator>>(istream& in, Student& val)
    {
        cout << "Имя, Группа, Специальность: ";
        in >> val.name >> val.group >> val.spec;
        return in;
    }
    bool operator==(Student& val)
    {
        return ((name == val.name) && (group == val.group) && (spec == val.spec));
    }
    bool operator!=(Student& val)
    {
        return !((name == val.name) && (group == val.group) && (spec == val.spec));
    }
};

//класс узел
template<class T>
class Node {
public:
    T daTa;
    int Key;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    ~Node()
    {
        cout << "* destrucror Node" << endl;
    }
    Node(T x = 0, int keya = 0)
    {
        Key = keya;
        daTa = x;
    }
    friend
        ostream& operator<<(ostream& out, Node<T>* val)
    {
        return out << val->Key << " :  " << val->daTa;
    }
};

template<class T>
class BTree
{
private:
    Node<T>* root = nullptr;
public:
    Node<T>* GetRoot()
    {
        return root;
    }
    void Add(T x, int keya)
    {
        Node<T>* tmp = new Node<T>(x, keya);
        Add(tmp, root);
    }
    Node<T>* operator[](int keya)
    {
        return find(keya, root);
    }
    void print()
    {
        print(root);
    }
    ~BTree()
    {
        destr(root);
    }
private:
    void destr(Node<T>* Root)
    {
        if (!Root) return;
        //сначала пройтись по всем левым
        destr(Root->left);
        //потом по всем правым
        destr(Root->right);
        //потом удалять сам элемент и идти на верх
        delete Root;
    }
    void Add(Node<T>* x, Node<T>*& Root)
    {
        //добавление реализовано через ключи(индексы)
        if (Root == nullptr)
        {
            Root = x;
        }
        else if (Root->Key > x->Key)
        {
            Add(x, Root->left);
        }
        else if (Root->Key < x->Key)
        {
            Add(x, Root->right);
        }
    }
    Node<T>* find(int key, Node<T>* root)
    {
        if (root == nullptr)
            return root;
        else if (root->Key == key)
            return root;
        else if (root->left)
            find(key, root->left);
        else if (root->right)
            find(key, root->right);
    }
    void print(Node<T>* Root)
    {
        if (!Root) return;
        print(Root->left);
        cout << Root->daTa << " ";
        print(Root->right);
    }
};

class Menu {
public:
    string a;
    Menu(string b) : a(b)
    {}
    int select() {
        int x;
        cout << a;
        cin >> x;
        return x;
    }
};

int main()
{
    setlocale(LC_ALL, "");

    BTree<Student> tree;
    int i = 0;
    Menu m("\n1. Добавить студентов в список.\n2. Показать список.              \n3. Поиск студента в списке        \n0. Выход.                       \n\nСделайте выбор: ");
    bool t = true;
    Student daT;
    int key;
    while (t)
    {
        switch (m.select())
        {
        case 1:
            cout << "Введите номер студента: ";
            cin >> key;
            cout << "Введите данные: " << endl;
            cin >> daT;
            tree.Add(daT, key);
            break;
        case 2:
            tree.print();
            cout << endl;
            break;
        case 3:
            cout << "Номер студента: ";
            cin >> key;
            cout << tree[i]->daTa << endl;
            break;
        case 0:
            t = !t;
        }
        system("pause");
        system("cls");
    }
}
