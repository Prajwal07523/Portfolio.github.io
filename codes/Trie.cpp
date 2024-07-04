#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

    void collectAllWords(TrieNode* node, string prefix, vector<string>& words) {
        if (node->isEndOfWord) {
            words.push_back(prefix);
        }
        for (auto& child : node->children) {
            collectAllWords(child.second, prefix + child.first, words);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* currentNode = root;
        for (char ch : word) {
            if (currentNode->children.find(ch) == currentNode->children.end()) {
                currentNode->children[ch] = new TrieNode();
            }
            currentNode = currentNode->children[ch];
        }
        currentNode->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* currentNode = root;
        for (char ch : word) {
            if (currentNode->children.find(ch) == currentNode->children.end()) {
                return false;
            }
            currentNode = currentNode->children[ch];
        }
        return currentNode->isEndOfWord;
    }

    vector<string> autoComplete(const string& prefix) {
        vector<string> words;
        TrieNode* currentNode = root;
        for (char ch : prefix) {
            if (currentNode->children.find(ch) == currentNode->children.end()) {
                return words;
            }
            currentNode = currentNode->children[ch];
        }
        collectAllWords(currentNode, prefix, words);
        return words;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("band");
    trie.insert("bandana");

    cout << "Search for 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    cout << "Search for 'app': " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "Search for 'banana': " << (trie.search("banana") ? "Found" : "Not Found") << endl;
    cout << "Search for 'band': " << (trie.search("band") ? "Found" : "Not Found") << endl;
    cout << "Search for 'bandana': " << (trie.search("bandana") ? "Found" : "Not Found") << endl;
    cout << "Search for 'bandit': " << (trie.search("bandit") ? "Found" : "Not Found") << endl;

    vector<string> autoCompleteWords = trie.autoComplete("ban");
    cout << "Auto-complete suggestions for 'ban':" << endl;
    for (const string& word : autoCompleteWords) {
        cout << word << endl;
    }

    return 0;
}
