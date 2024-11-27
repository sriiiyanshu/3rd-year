#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

int flag = 0;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void printHuffmanCodes(Node* root, string str, char characters[], string huffmanCode[], int &index) {
    if (!root) return;

    if (!root->left && !root->right) {
        characters[index] = root->ch;
        huffmanCode[index] = str;
        index++;
    }

    printHuffmanCodes(root->left, str + "0", characters, huffmanCode, index);
    printHuffmanCodes(root->right, str + "1", characters, huffmanCode, index);
}

void buildHuffmanTree(string text) {

    int freq[128] = {0};


    for (char ch : text) {
        freq[(int)ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            pq.push(new Node((char)i, freq[i]));
        }
    }


    while (pq.size() != 1) {

        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* node = new Node('\0', left->freq + right->freq);
        node->left = left;
        node->right = right;

        pq.push(node);
    }

    Node* root = pq.top();

    char characters[128];
    string huffmanCode[128];
    int index = 0;

    if (flag == 0)
    {
    printHuffmanCodes(root, "", characters, huffmanCode, index);

    cout << "Huffman Codes are:\n";
    for (int i = 0; i < index; i++) {
        cout << characters[i] << ": " << huffmanCode[i] << "\n";
    }

   //size of original string in bits
    int originalSize = text.length() * 8; 

    string encodedString;
    int encodedSize = 0;
    for (char ch : text) {
        for (int i = 0; i < index; i++) {
            if (characters[i] == ch) {
                encodedString += huffmanCode[i];
                encodedSize += huffmanCode[i].length(); // Each character's code length in bits
                break;
            }
        }
    }

    cout << "\nEncoded string is:\n" << encodedString << "\n";

    cout << "\nOriginal string size: " << originalSize << " bits\n";
    cout << "Encoded string size: " << encodedSize << " bits\n\n";
    }
    flag++; 
}

string generateRandomString(int size) {
    string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    for (int i = 0; i < size; i++) {
        result += charset[rand() % charset.size()];
    }
    return result;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Original code for user input and Huffman encoding
    string text;
    cout << "Enter a string to encode using Huffman Coding: ";
    getline(cin, text);

    buildHuffmanTree(text);

    // Benchmark Huffman encoding for random strings of different sizes
    int sizes[] = {500, 1000, 1500, 2000};

    cout << "\n\nFor Huffman Coding on Random Strings:" << endl;

    for (int i = 0; i < 4; ++i) {
        int size = sizes[i];
        string randomString = generateRandomString(size);

        auto start = high_resolution_clock::now();
        buildHuffmanTree(randomString);
        auto end = high_resolution_clock::now();

        auto time_spent = duration_cast<nanoseconds>(end - start).count();
        cout << "\nThe elapsed time for a string of " << size << " characters is " << time_spent << " nanoseconds" << endl;
    }

    cout<<endl;
    return 0;
}
