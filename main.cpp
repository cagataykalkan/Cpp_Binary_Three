#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Node {
    int plakaKodu;
    Node* left;
    Node* right;

    Node(int plakaKodu)
        : plakaKodu(plakaKodu), left(nullptr), right(nullptr) {}
};

// Yeni düğümü ağaca eklemek için kullanılır
Node* insertNode(Node* root, int plakaKodu) {
    if (root == nullptr) {
        return new Node(plakaKodu);
    }

    if (plakaKodu < root->plakaKodu) {
        root->left = insertNode(root->left, plakaKodu);
    } else {
        root->right = insertNode(root->right, plakaKodu);
    }

    return root;
}

// Dosyadan plaka kodlarını okuyarak ağaç oluşturur
Node* buildTree(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Dosya açılamadı!" << endl;
        return nullptr;
    }

    string line;
    vector<int> plakaKodlari;

    while (getline(inputFile, line)) {
        int plakaKodu = stoi(line);
        plakaKodlari.push_back(plakaKodu);
    }

    inputFile.close();

    Node* root = nullptr;
    for (const auto& plaka : plakaKodlari) {
        root = insertNode(root, plaka);
    }

    return root;
}

// Ağacı daha güzel bir formatta görüntülemek için kullanılan fonsiyon
void printTreeHelper(Node* root, const string& prefix, bool isLeft) {
    if (root == nullptr) {
        return;
    }

    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->plakaKodu << endl;

    if (root->left || root->right) {
        string newPrefix = prefix + (isLeft ? "│   " : "    ");
        printTreeHelper(root->left, newPrefix, true);
        printTreeHelper(root->right, newPrefix, false);
    }
}

// Ağacı görüntülemek için kullanılan fonsiyon
void printTree(Node* root) {
    printTreeHelper(root, "", false);
}

// Ağacın derinliğini hesaplayan fonsiyon
int getTreeDepth(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = getTreeDepth(root->left);
    int rightDepth = getTreeDepth(root->right);

    return max(leftDepth, rightDepth) + 1;
}

// Ağacın dengeli olup olmadığını kontrol eden fonsiyon
bool isBalanced(Node* root) {
    if (root == nullptr) {
        return true;
    }

    int leftDepth = getTreeDepth(root->left);
    int rightDepth = getTreeDepth(root->right);

    if (abs(leftDepth - rightDepth) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return true;
    }

    return false;
}

// Belirli bir plaka koduna sahip düğümü arayan işlev
Node* searchNode(Node* root, int plakaKodu) {
    if (root == nullptr || root->plakaKodu == plakaKodu) {
        return root;
    }

    if (plakaKodu < root->plakaKodu) {
        return searchNode(root->left, plakaKodu);
    } else {
        return searchNode(root->right, plakaKodu);
    }
}

// Belirli bir düğümün seviyesini bulan fonsiyon
int getNodeLevel(Node* root, int plakaKodu, int level = 0) {
    if (root == nullptr) {
        return -1;
    }

    if (root->plakaKodu == plakaKodu) {
        return level;
    }

    int leftLevel = getNodeLevel(root->left, plakaKodu, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }

    int rightLevel = getNodeLevel(root->right, plakaKodu, level + 1);
    return rightLevel;
}

// Ağacı önceden düzenlenmiş bir formatta önceden sıralanmış şekilde dolaşan fonsiyon
void preorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->plakaKodu << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    cout << root->plakaKodu << " ";
    inorderTraversal(root->right);
}

void postorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->plakaKodu << " ";
}

int main() {
    string dosyaAdi = "sehir_plaka_kodlari.txt";
    Node* root = buildTree(dosyaAdi);

    if (root == nullptr) {
        return 1;
    }

    cout << "İkili ağacın görüntüsü:" << endl;
    printTree(root);

    int agacinDerinligi = getTreeDepth(root);
    cout << "Ağacın derinliği: " << agacinDerinligi << endl;

    bool agacDengeliMi = isBalanced(root);
    cout << "Ağaç dengeli mi: " << (agacDengeliMi ? "Evet" : "Hayır") << endl;

    int plaka1, plaka2;
    cout << "Plaka 1: ";
    cin >> plaka1;
    cout << "Plaka 2: ";
    cin >> plaka2;

    Node* dugum1 = searchNode(root, plaka1);
    Node* dugum2 = searchNode(root, plaka2);

    if (dugum1 != nullptr && dugum2 != nullptr) {
        int seviye1 = getNodeLevel(root, plaka1);
        int seviye2 = getNodeLevel(root, plaka2);
        cout << "Plaka 1 seviye: " << seviye1 << ", Plaka 2 seviye: " << seviye2 << endl;
        cout << "Seviye farkı: " << abs(seviye1 - seviye2) << endl;
    } else {
        cout << "Girilen plaka kodu bulunamadı!" << endl;
    }
    
    cout<<"*---------------------------------------------------------------------------------*"<<endl;
    cout<< "\t Preorder sıralaması: ";
    preorderTraversal(root);
    cout << endl;
    
    cout<<"*---------------------------------------------------------------------------------*"<<endl;
    cout << "\t Inorder sıralaması: ";
    inorderTraversal(root);
    cout << endl;

    cout<<"*---------------------------------------------------------------------------------*"<<endl;
    cout << "\t Postorder sıralaması: ";
    postorderTraversal(root);
    cout << endl;
    
    cout<<"*---------------------------------------------------------------------------------*"<<endl;
    return 0;
}
