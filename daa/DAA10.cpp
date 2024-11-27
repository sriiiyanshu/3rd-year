#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

// Naive String Matching Algorithm
void naiveStringMatch(const string& text, const string& pattern) {
    int m = pattern.length();
    int n = text.length();
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            cout << "Naive: Pattern found at index " << i << endl;
        }
    }
}

// Rabin-Karp Algorithm
void rabinKarp(const string& text, const string& pattern) {
    int m = pattern.length();
    int n = text.length();
    const int d = 256; // Number of characters in the input alphabet
    const int q = 101; // A prime number for hashing
    int h = 1;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text

    // Calculate the value of h = d^(m-1) % q
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate initial hash values for pattern and first window of text
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            // Check for characters one by one
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                cout << "Rabin-Karp: Pattern found at index " << i << endl;
            }
        }
        // Calculate hash value for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) {
                t += q;
            }
        }
    }
}

// Knuth-Morris-Pratt (KMP) Algorithm
void computeLPSArray(const string& pattern, vector<int>& lps) {
    int len = 0; // Length of previous longest prefix suffix
    lps[0] = 0; // LPS[0] is always 0
    int i = 1;
    int m = pattern.length();

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmp(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> lps(m);

    computeLPSArray(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            cout << "KMP: Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text, pattern;
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;

    // Naive String Matching
    auto start = high_resolution_clock::now();
    naiveStringMatch(text, pattern);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Naive execution time: " << duration << " microseconds" << endl << endl;

    // Rabin-Karp Algorithm
    start = high_resolution_clock::now();
    rabinKarp(text, pattern);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start).count();
    cout << "Rabin-Karp execution time: " << duration << " microseconds" << endl << endl;

    // KMP Algorithm
    start = high_resolution_clock::now();
    kmp(text, pattern);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start).count();
    cout << "KMP execution time: " << duration << " microseconds" << endl << endl;

    return 0;
}
