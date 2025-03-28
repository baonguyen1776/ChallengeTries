#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct TrieNode {
    TrieNode* child[26];
    bool isEnd;
};

TrieNode* createNode() {
    TrieNode* newNode = new TrieNode();
    newNode->isEnd = false;
    for (int i = 0; i < 26; i++) 
        newNode->child[i] = nullptr;
    return newNode;
}

void insertNode(TrieNode* pRoot, string data) {
    TrieNode* pCur = pRoot;
    for (char ch : data) {
        int idx = ch - 'a';
        if (!pCur->child[idx])
            pCur->child[idx] = createNode();
        pCur = pCur->child[idx];
    }
    pCur->isEnd = true;
}

TrieNode* get(TrieNode* p, string data, int d) {
    if (!p)
        return nullptr;
    if ((size_t)d == data.length())
        return p;
    char c = data[d];
    return get(p->child[c - 'a'], data, d + 1);
}

TrieNode* findNode(TrieNode* pRoot, string data) {
    TrieNode* p = get(pRoot, data, 0);
    return (p && p->isEnd) ? p : nullptr;
}

void readFile(TrieNode* &pRoot, string filename) {
    ifstream fIn(filename);
    if (!fIn.is_open()) {
        cout << "Cannot open file!\n";
        return;
    }
    string data;
    while (getline(fIn, data)) {
        insertNode(pRoot, data);
    }
}

TrieNode* del(TrieNode* p, const string& key, int d) {
    if (p == nullptr) 
        return nullptr;

    if ((size_t)d == key.length()) 
        p->isEnd = false;
    else {
        char c = key[d];
        p->child[c - 'a'] = del(p->child[c - 'a'], key, d + 1);
    }
    if (p->isEnd) 
        return p;
    for (int c = 0; c < 26; c++) 
        if (p->child[c] != nullptr)
            return p;
    delete p;
    return nullptr;
}

void Deletion(TrieNode*& root, const string& key) {
    root = del(root, key, 0);
}


int main() {
    TrieNode* pRoot = createNode();
    string filename = "data.txt";
    readFile(pRoot, filename);
    cout << (findNode(pRoot, "aaron") ? "Tìm thấy 'aaron'" : "Không tìm thấy 'aaron'") << endl;
    Deletion(pRoot, "aaron");
    cout << (findNode(pRoot, "aaron") ? "Tìm thấy 'aaron'" : "Không tìm thấy 'aaron'") << endl;
    return 0;
}
