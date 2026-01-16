Bài 1
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};

void DuyetTruoc(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    DuyetTruoc(root->left);
    DuyetTruoc(root->right);
}

void DuyetGiua(Node* root) {
    if (root == NULL) return;
    DuyetGiua(root->left);
    cout << root->data << " ";
    DuyetGiua(root->right);
}

void DuyetSau(Node* root) {
    if (root == NULL) return;
    DuyetSau(root->left);
    DuyetSau(root->right);
    cout << root->data << " ";
}

void heapify(Node* root) {
    if (root == NULL) return;

    Node* largest = root;

    if (root->left && root->left->data > largest->data)
        largest = root->left;

    if (root->right && root->right->data > largest->data)
        largest = root->right;

    if (largest != root) {
        swap(root->data, largest->data);
        heapify(largest);
    }
}

void buildHeap(Node* root) {
    if (root == NULL) return;
    buildHeap(root->left);
    buildHeap(root->right);
    heapify(root);
}

int main() {
    Node* root = new Node(4);
    root->left = new Node(16);
    root->right = new Node(14);
    root->left->left = new Node(2);
    root->left->right = new Node(8);

    cout << "DuyetTruoc: ";
    DuyetTruoc(root);
    cout << endl;

    cout << "DuyetGiua: ";
    DuyetGiua(root);
    cout << endl;

    cout << "DuyetSau: ";
    DuyetSau(root);
    cout << endl;

    buildHeap(root);

    cout << "Duyet truoc sau khi vun dong: ";
    DuyetTruoc(root);

    return 0;
}
Bài 2: 
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};

bool isSameTree(Node* t1, Node* t2) {
    if (t1 == NULL && t2 == NULL) return true;
    if (t1 == NULL || t2 == NULL) return false;
    if (t1->data != t2->data) return false;
    return isSameTree(t1->left, t2->left) &&
           isSameTree(t1->right, t2->right);
}

int main() {
    Node* t1 = new Node(1);
    t1->left = new Node(2);
    t1->right = new Node(3);

    Node* t2 = new Node(1);
    t2->left = new Node(2);
    t2->right = new Node(3);

    if (isSameTree(t1, t2))
        cout << "Hai cay giong nhau";
    else
        cout << "Hai cay khong giong nhau";

    return 0;
}

Bài 3:
#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* left;
    Node* right;

    Node(int v, Node* l, Node* r)
    {
        value = v;
        left = l;
        right = r;
    }
};

class BSTree
{
private:
    Node* root;

public:
    BSTree()
    {
        root = NULL;
    }

    ~BSTree()
    {
        makeEmpty(root);
    }

    bool isEmpty()
    {
        return root == NULL;
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    void insert(int val1)
    {
        insert(val1, root);
    }

    Node* search(int val2)
    {
        return search(val2, root);
    }

    void makeEmpty(Node*& t)
    {
        if (t == NULL) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }

    void insert(int val1, Node*& t)
    {
        if (t == NULL)
            t = new Node(val1, NULL, NULL);
        else if (val1 < t->value)
            insert(val1, t->left);
        else if (val1 > t->value)
            insert(val1, t->right);
    }

    Node* search(int val2, Node* t)
    {
        if (t == NULL) return NULL;
        if (t->value == val2) return t;
        if (val2 < t->value)
            return search(val2, t->left);
        return search(val2, t->right);
    }
};

void PREORDER_travl(Node* t)
{
    if (t == NULL) return;
    cout << t->value << " ";
    PREORDER_travl(t->left);
    PREORDER_travl(t->right);
}

void INORDER_travl(Node* t)
{
    if (t == NULL) return;
    INORDER_travl(t->left);
    cout << t->value << " ";
    INORDER_travl(t->right);
}

void POSTORDER_travl(Node* t)
{
    if (t == NULL) return;
    POSTORDER_travl(t->left);
    POSTORDER_travl(t->right);
    cout << t->value << " ";
}

int main()
{
    BSTree bst;

    bst.insert(5);
    bst.insert(6);
    bst.insert(3);
    bst.insert(8);
    bst.insert(7);
    bst.insert(4);
    bst.insert(2);

    Node* root = bst.search(5);
    cout << "duyet cay thu tu truoc" << endl;
    PREORDER_travl(root);
    cout << endl;

    Node* n1 = bst.search(4);
    Node* n2 = bst.search(9);

    if (n1 != NULL)
        cout << "Node có gia tri = 4 la " << n1->value << endl;
    if (n2 == NULL)
        cout << "Khong tim thay node co gia tri =9" << endl;

    bst.makeEmpty();
    if (bst.isEmpty())
        cout << "Cay da bi xoa rong" << endl;

    return 0;
}
