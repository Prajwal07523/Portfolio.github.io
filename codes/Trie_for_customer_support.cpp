#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    string answer;
    bool isEndOfQuestion;

    TrieNode() : isEndOfQuestion(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string question, string answer) {
        TrieNode* currentNode = root;
        for (char c : question) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                currentNode->children[c] = new TrieNode();
            }
            currentNode = currentNode->children[c];
        }
        currentNode->isEndOfQuestion = true;
        currentNode->answer = answer;
    }

    string search(string question) {
        TrieNode* currentNode = root;
        for (char c : question) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                return "Question not found.";
            }
            currentNode = currentNode->children[c];
        }
        if (currentNode->isEndOfQuestion) {
            return currentNode->answer;
        } else {
            return "Question not found.";
        }
    }
};

int main() {
    Trie faqTrie;

    // Inserting some FAQs and their answers
    faqTrie.insert("What are your delivery hours?", "Our delivery hours are from 9 AM to 9 PM.");
    faqTrie.insert("How can I track my order?", "You can track your order using the tracking link sent to your email.");
    faqTrie.insert("What is your return policy?", "You can return any item within 14 days of delivery for a full refund.");

    // Searching for answers
    string query1 = "What are your delivery hours?";
    string query2 = "How can I track my order?";
    string query3 = "What is your return policy?";
    string query4 = "How can I contact support?";

    cout << "Query: " << query1 << "\nAnswer: " << faqTrie.search(query1) << endl;
    cout << "Query: " << query2 << "\nAnswer: " << faqTrie.search(query2) << endl;
    cout << "Query: " << query3 << "\nAnswer: " << faqTrie.search(query3) << endl;
    cout << "Query: " << query4 << "\nAnswer: " << faqTrie.search(query4) << endl;

    return 0;
}
