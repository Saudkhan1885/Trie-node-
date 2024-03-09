#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// TrieNode class definition
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool end_marker;

    TrieNode() : end_marker(false) {}
};

// Trie class definition
class Trie {
private:
    TrieNode* starting_node;

public:
    Trie() {
        starting_node = new TrieNode();
    }

    // Insert a word into the trie
    int insert(const string word) {
    if (word.length() > 15) {
        cout << "\t\tError: Word length exceeds the maximum allowed (15 characters).\n";
        return 0;
    }

    TrieNode* current = starting_node;
    for (char ch : word) {
        // Convert uppercase characters to lowercase
        ch = tolower(ch);

        // Check if the character is a lowercase letter
        if (islower(ch)) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
    }
    current->end_marker = true;
    return 1;
}

    // Search for a word in the trie
    bool search(const string& word) {
        TrieNode* current = starting_node;
        for (char ch : word) {
            
            if (current->children.find(ch) == current->children.end()) {
                cout<<ch<<endl;
                return false; // Prefix not found
            }
            
            current = current->children[ch];
        }
       
        return current->end_marker; // Check if it's the end of a word
    }

    // Retrieve words with a given prefix
   

    vector<string> search_with_prefix(const string& prefix) {
        TrieNode* current = starting_node;
        for (char ch : prefix) {     
            if (current->children.find(ch) == current->children.end()) {
                vector<string> emptyVector;
                return emptyVector; // Prefix not found
            }
        
            current = current->children[ch];
        }
        //after this the prefix exist actually so it called the collectword func.
        vector<string> recommendation;
        collectWords(current, prefix, recommendation);
        return recommendation;
    }

private:
    // Helper function for collecting words with a given prefix
    void collectWords(TrieNode* node, const string& currentPrefix, vector<string>& recommendation) {
        if (node->end_marker) {
            
            recommendation.push_back(currentPrefix);
        }

        for (const auto& child : node->children) {
            cout<<child.first<<endl;
            collectWords(child.second, currentPrefix + child.first, recommendation);
        }
    }
};

// Function to display the Trie menu
void displayMenu() {
    cout << "\n\t\t-----------------------------\n";
    cout << "\t\t          Trie Menu\n";
    cout << "\t\t-----------------------------\n";
    cout << "\t\t1. Insert a word\n";
    cout << "\t\t2. Search for a word\n";
    cout << "\t\t3. Words with prefix\n";
    cout << "\t\t4. Quit\n";
    cout << "\t\t-----------------------------\n";
}

int main() {
    Trie trie;

    char choice;
    do {
        displayMenu();
        cout << "\t\tEnter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case '1': {
                string word;
                cout << "\t\tEnter the word to insert: ";
                cin >> word;
                int checker;
                
                checker=trie.insert(word);
                if(checker==1){
                cout << "\t\tWord inserted successfully.\n";
                }
               
                break;
            }

            case '2': {
                string word;
                cout << "\t\tEnter the word to search: ";
                cin >> word;
                for (char &ch : word) {
                 ch = tolower(ch);
                 }
                if (trie.search(word)) {
                    cout << "\t\tWord \"" << word << "\" found!\n";
                } else {
                    cout << "\t\tWord \"" << word << "\" not found.\n";
                }
                break;
            }

            case '3': {
                string prefix;
                cout << "\t\tEnter the prefix: ";
                cin >> prefix;
               for (char &ch : prefix) {
                 ch = tolower(ch);
                 }
                vector<string> recommendation = trie.search_with_prefix(prefix);
                if (recommendation.empty()) {
                    cout << "\t\tNo words found with the given prefix \"" << prefix << "\".\n";
                } else {
                    cout << "\t\tWords with the prefix \"" << prefix << "\":\n";
                    for (const string& word : recommendation) {
                        cout << "\t\t  " << word << "\n";
                    }
                }
                break;
            }

            case '4': {
                cout << "\t\tExiting the program. Thank you!\n";
                break;
            }

            default:
                cout << "\t\tInvalid choice. Please enter a number between 1 and 4.\n";
                break;
        }

        // Clear input buffer to handle non-integer inputs
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice != '4');

    return 0;
}
