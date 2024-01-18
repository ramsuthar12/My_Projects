#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<string> words;

class HybridNode {
public:
    string key;  
    string element;  
    HybridNode* parent;
    HybridNode* left_child;
    HybridNode* right_child;
    HybridNode* next_node;
    char colour = 'R';
    // string name = "here" ;

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};

    int ll = 0 ; // Left-Left Rotation flag
    int rr = 0 ; // Right-Right Rotation flag
    int lr = 0 ; // Left-Right Rotation flag
    int rl = 0 ; // Right-Left Rotation flag
    // HybridNode* temp = root;

void printPreorder(HybridNode* node)
{
    if (node == nullptr)
    return;

    // Deal with the node
    cout << node->key << " ";

    // Recur on left subtree
    printPreorder(node->left_child);

    // Recur on right subtree
    printPreorder(node->right_child);
}

class RedBlackTree {
private:
    HybridNode* root;

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;
    }

    void setRoot(HybridNode* node) {
        root = node;
    }

    HybridNode* rotateLeft(HybridNode* node) {
        HybridNode* x = node->right_child;
        HybridNode* y = x->left_child;
        x->left_child = node;
        node->right_child = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return x;
    }

    // Function to perform Right Rotation
    HybridNode* rotateRight(HybridNode* node) {
        HybridNode* x = node->left_child;
        HybridNode* y = x->right_child;
        x->right_child = node;
        node->left_child = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return x;
    }

    HybridNode* insertinTree(HybridNode* root, string k1 , string e1){
        int f = 0; // Flag to check RED-RED conflict
        if (root == nullptr)
            return new HybridNode(k1,e1);
        else if (k1.compare(root->key) < 0) {
            // cout << "Go to left child" << endl;
            root->left_child = insertinTree(root->left_child, k1, e1);
            root->left_child->parent = root;
            if (root != this->root) {
                if (root->colour == 'R' && root->left_child->colour == 'R'){
                // cout << "hi" << endl;
                    f = 1;
                }
            }
        }
        else if(k1.compare(root->key) > 0){
            // cout << "Go to right child" << endl;
            // cout << "R is -- " << root->key << endl;
            root->right_child = insertinTree(root->right_child, k1, e1);
            // cout << "R is -- " << root->key << endl;
            // cout << "R R is -- " << root->right_child->key << endl;
            root->right_child->parent = root;
            if (root != this->root) {
                if (root->colour == 'R' && root->right_child->colour == 'R'){
                // cout << "hi" << endl;
                    f = 1;
                }
            }
        }
        // Perform rotations
        if (ll) {
            // cout << "left ll" << endl;
            root = rotateLeft(root);
            root->colour = 'B';
            root->left_child->colour = 'R';
            ll = false;
        } else if (rr) {
            // cout << "right right rr" << endl;
            root = rotateRight(root);
            root->colour = 'B';
            root->right_child->colour = 'R';
            rr = false;
        } else if (rl) {
            // cout << "right left rl" << endl;
            root->right_child = rotateRight(root->right_child);
            root->right_child->parent = root;
            root = rotateLeft(root);
            root->colour = 'B';
            root->left_child->colour = 'R';
            rl = false;
        } else if (lr) {
            // cout << "left right lr" << endl;
            root->left_child = rotateLeft(root->left_child);
            root->left_child->parent = root;
            root = rotateRight(root);
            root->colour = 'B';
            root->right_child->colour = 'R';
            lr = false;
        }
        // if (f == true){
        //     cout << "f is true" << endl;
        // }
        // Handle RED-RED conflicts
            // cout << "R is -- " << root->key << endl;
        if (f == 1) {
            // cout << "f is true" << endl;
            if (root->parent->right_child == root) {
                if (root->parent->left_child == nullptr || root->parent->left_child->colour == 'B') {
                    if (root->left_child != nullptr && root->left_child->colour == 'R')
                        rl = true;
                    else if (root->right_child != nullptr && root->right_child->colour == 'R')
                        ll = true;
                } else {
                    root->parent->left_child->colour = 'B';
                    root->colour = 'B';
                    if (root->parent != this->root)
                        root->parent->colour = 'R';
                }
            } else {
                if (root->parent->right_child == nullptr || root->parent->right_child->colour == 'B') {
                    if (root->left_child != nullptr && root->left_child->colour == 'R')
                        rr = true;
                    else if (root->right_child != nullptr && root->right_child->colour == 'R')
                        lr = true;
                } else {
                    root->parent->right_child->colour = 'B';
                    root->colour = 'B';
                    if (root->parent != this->root)
                        root->parent->colour = 'R';
                }
            }
            f = false;
        }
        // cout << "Here root is -- " << root->key << endl;
        return root;
}



    HybridNode* insert(string key, string element) {
        if (root == nullptr) {
            root = new HybridNode(key,element);
            root->colour = 'B';
        } else{
            // cout << "in else case" << endl;
            cout << "root is -- " << root->key << endl; 
            root = insertinTree(root, key, element);
        }
        // setRoot(insertinTree(root, key , element));
        // cout << "root is -- " << getRoot()->key << endl;
        // cout << "root colour is -- " << getRoot()->colour << endl;
        return root;
    }

    bool deleteNode(string key) {
        // Implement Red-Black Tree deletion
    }

    void traverseUp(HybridNode* node) {
        // Traverse up the tree from the given node to the root
    }

    void traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
    }

    vector<string> preOrderTraversal(HybridNode* node, int depth) {
        // Perform in-order traversal staying within specified depth
    }
    HybridNode* search(string key) {
        // Implement Red-Black Tree search
    }
    
    int blackheight(HybridNode* node){
        // Implement blackheight
    }
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {
        word = word_val;
    }

    string getWord() {
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {
        return chapter_word_counts;
    }

    void addOccurrence(string chapter, int word_count) {
        // Add a chapter's word count for this word
    }

    string toString() {
        // Return a string representation of the IndexEntry
        // Modify the implementation as needed for specific use cases
        return "";
    }
};

class Lexicon {
private:
    RedBlackTree red_black_tree;

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {
        return red_black_tree;
    }

    void readChapter(string chapter_name, vector<string> words) {
        ifstream chap("abc.txt");
        string ss;
        string word = "";
        getline(chap,ss);
        for(int i = 0 ; i<ss.size() ; i++){
            if (ss[i] > 90 && ss[i] < 97 || ss[i] < 64 || ss[i] > 122 ){
                ss[i] = ' ';
            }
        }
        for(int i = 0 ; i<ss.size() ; i++){
            if(ss[i] != ' '){
                word = word + ss[i];
            }
            else{
                cout << "word is -- " <<  word <<  endl;
                red_black_tree.insert(word, chapter_name);
                // cout << "Here also" << endl;
                word = "" ;
            }
        }
        cout << endl << "Preorder trav" << endl;
        printPreorder(red_black_tree.getRoot());
    }

    void pruneRedBlackTree() {
        // Prune the Red-Black Tree by deleting common words
    }

    vector<IndexEntry> buildIndex() {
        // Build the index using the remaining words in the Red-Black Tree
    }
};

extern Lexicon lexicon;

int main(){
    cout << "Hi" << endl;
    Lexicon lx;
    lx.readChapter("Chapter1.txt",words);
    cout << endl << "Hello" << endl;
    return 0;
}