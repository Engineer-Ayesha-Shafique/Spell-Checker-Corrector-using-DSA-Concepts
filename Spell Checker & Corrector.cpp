// Dsa Cep.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace std;
using namespace std;

class treeNode
{
public:
    treeNode* left;
    treeNode* right;
    string data;
    treeNode* parent; // opptional
};

class BST
{

public:
    treeNode* root;
    string tra = "";
    BST()
    {
        root = NULL;
    }

    ////////// Inorder Traversal

    void InorderTraverse(treeNode* n)
    {
        if (n != NULL)
        {
            InorderTraverse(n->left);
            cout << n->data << " " << endl;
            tra += n->data;
            tra += " ";
            InorderTraverse(n->right);
        }
    }

    ////////// Postorder Traversal

    void PostorderTraverse(treeNode* n = NULL)
    {
        if (n == NULL)
        {
            n = root;
        }
        else
        {
            PostorderTraverse(n->left);
            PostorderTraverse(n->right);
            cout << n->data << " ";
        }
    }

    ////////// Preorder Traversal

    void PreorderTraverse(treeNode* n)
    {
        if (n != NULL)
        {
            cout << n->data << " ";
            PreorderTraverse(n->left);
            PreorderTraverse(n->right);
        }
    }

    ////////// Insert in Tree

    void insert(string m)
    {
        treeNode* z = new treeNode();
        z->data = m;
        z->left = NULL;
        z->right = NULL;

        treeNode* y = NULL;
        treeNode* x = root;

        while (x != NULL)
        {

            y = x;
            if (x->data.compare(z->data) > 0)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (root == NULL)
            root = z;
        else if (y->data.compare(z->data) < 0)
            y->right = z;
        else
            y->left = z;
    }

    ////////// Min Tree

    string TreeMin(treeNode* x = NULL)
    {
        if (x == NULL) //  to make function usable for both kind of function calls use in this code
            x = root;
        while (x->left != NULL)
            x = x->left;
        return x->data;
    }

    ////////// Max Tree

    string TreeMax(treeNode* x = NULL)
    {
        if (x == NULL)
            x = root;
        while (x->right != NULL)
            x = x->right;
        return x->data;
    }

    /////////// Tree Search

    treeNode* search(string s)
    {
        treeNode* x = root;

        while (x != NULL)
        {
            if (s.compare(x->data) > 0)
                x = x->right;
            else if (s.compare(x->data) < 0)
                x = x->left;
            else if (s.compare(x->data) == 0)
                break;
        }
        return x;
    }

    ////////// Predecessor of x

    treeNode* Predecessor(string x)
    {
        treeNode* c = search(x);
        if (c->left != NULL)
        {
            string val = TreeMax(c->left);

            // TreeMin will return the minimum value not node containing that value, but this function has to return the node. How to handle it without changing TreeMin
            treeNode* rightSubTree = c->left;
            treeNode* predNode = NULL;
            while (rightSubTree->right != NULL)
            {
                predNode = rightSubTree;
                rightSubTree = rightSubTree->right;
            }
            return rightSubTree;
        }
        treeNode* y = c->parent;
        while (y != NULL && c == y->left)
        {
            c = y;
            y = y->parent;
        }
        return y;
    }

    ////////// Successor of x

    treeNode* Successor(string x)
    {
        treeNode* c = search(x);
        if (c->right != NULL)
        {
            string val = TreeMin(c->right);
            treeNode* leftSubTree = c->right;

            while (leftSubTree->left != NULL)
            {
                leftSubTree = leftSubTree->left;
            }
            return leftSubTree;
        }
        treeNode* y = c->parent;
        while (y != NULL && c == y->right)
        {
            c = y;
            y = y->parent;
        }
        return y;
    }

    ////////// Delete from tree

    treeNode* deleteNode(treeNode* t, string x)
    {
        treeNode* temp;
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            t->left = deleteNode(t->left, x);
        else if (x > t->data)
            t->right = deleteNode(t->right, x);
        else if (t->left && t->right)
        {
            string val = TreeMin(t->right);
            temp = search(val);
            t->data = temp->data;
            t->right = deleteNode(t->right, t->data);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

};

class spellchecker {
    BST bst;
    BST near;
public:

    bool bsearch(string s) {
        if (bst.search(s)) {
            return true;
        }
        else {
            return false;
        }
    }
    bool nsearch(string s) {
        if (near.search(s)) {
            return true;
        }
        else {
            return false;
        }
    }
    void readdict(string dictfilename) {
        stringstream buffer;
        buffer << ifstream(dictfilename).rdbuf();
        string txtstr = buffer.str();
        istringstream ss(txtstr);
        string word;
        while (ss >> word) {
            if (!bsearch(word)) {
                bst.insert(word);
            }
        }
    }

    string remSpecialChar(string s)
    {
        string str = "";
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            if (s[i] >= 'A' and s[i] <= 'Z')
                str += s[i];
            else if (s[i] >= 'a' and s[i] <= 'z')
                str += s[i];
            else if (s[i] == ' ')
                str += s[i];

        }
        return str;
    }

    string readinputfile(string inpfilename) {
        stringstream bufferin;
        bufferin << ifstream(inpfilename).rdbuf();
        string result = remSpecialChar(bufferin.str());
        //lowercase
        for (int i = 0; i < result.length(); i++)
        {
            result[i] = tolower(result[i]);
        }
        return result;
    }

    bool hasEnding(string const& fullString, string const& ending) {
        if (fullString.length() >= ending.length()) {
            return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
        }
        else {
            return false;
        }
    }

    string processing(string word) {
        string editedword;
        string newstr = "";
        newstr += word;
        newstr += " ";
        if (hasEnding(word, "ing")) {
            editedword = word;
            string suffix = "ing";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += " ";
        }
        if (hasEnding(word, "ing")) {
            editedword = word;
            string suffix = "ing";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += "e ";
        }
        if (hasEnding(word, "es")) {
            editedword = word;
            string suffix = "es";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += " ";
        }
        if (hasEnding(word, "es")) {
            editedword = word;
            string suffix = "es";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += "s ";
        }
        if (hasEnding(word, "s")) {
            editedword = word;
            string suffix = "s";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += " ";
        }
        if (hasEnding(word, "ies")) {
            editedword = word;
            string suffix = "ies";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += "y ";
        }
        if (hasEnding(word, "ly")) {
            editedword = word;
            string suffix = "ly";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += " ";
        }
        if (hasEnding(word, "ed")) {
            editedword = word;
            string suffix = "ed";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += " ";
        }
        if (hasEnding(word, "ed")) {
            editedword = word;
            string suffix = "ed";
            string res = editedword.substr(0, editedword.length() - suffix.length());
            newstr += res;
            newstr += "e ";
        }
        return newstr;
    }


    void addtofile(string dict, string newword) {
        ofstream file_out;
        file_out.open(dict, std::ios_base::app);
        file_out << newword << endl;
        bst.insert(newword);
    }

    bool searchword(string dict, string strword) {
        istringstream ss(processing(strword));
        string word;
        while (ss >> word) {
            if (bsearch(word))
                return true;
        }
        return false;
    }



    int skipByOneChar(string first, string second, int n)
    {
        int imbalance = 0;
        int a = 0;
        int b = 0;
        for (int i = 0; i < n && imbalance <= 1; ++i) {
            if (first[a] == second[b]) {
                // When both string character at position a and b is same
                a++;
                b++;
            }
            else {
                a++;
                imbalance++;
            }
        }
        if (imbalance == 0)
            // In case, last character is extra in first string
            return 1;
        return imbalance;
    }
    bool differBySingleChar(string first, string second) {
        // Get the size of given string 
        int n = first.length();
        int m = second.length();
        int imbalance = 0;
        if (n == m) {
            // Case A when both string are equal size
            for (int i = 0; i < n && imbalance <= 1; ++i) {
                if (first[i] != second[i])
                    imbalance++;
            }
        }
        else if (n - m == 1 || m - n == 1) {
            // When one string contains extra character
            if (n > m)
                imbalance = this->skipByOneChar(first, second, m);
            else
                imbalance = this->skipByOneChar(second, first, n);
        }
        if (imbalance == 1)
            return true;
        else
            return false;
    }
    bool isSubstring(string s1, string s2) {
        int j;
        int l1 = s1.length();
        int l2 = s2.length();
        if (l1 == 1)
            return false;
        for (int i = 0; i <= l2 - l1; i++) {
            for (j = 0; j < l1; j++) {
                if (s2[i + j] != s1[j]) {
                    break;
                }
            }
            if (j == l1) {
                return true;
            }
        }

        return false;
    }
    int matching_characters(string s1, string s2) {
        sort(begin(s1), end(s1));
        sort(begin(s2), end(s2));
        std::string intersection;
        std::set_intersection(begin(s1), end(s1), begin(s2), end(s2),
            back_inserter(intersection));
        return intersection.length();
    }
    bool matchedchar(string s1, string s2) {
        int l1 = s1.length();
        int l2 = s2.length();
        int dif = l2 - l1;
        int a = 0;
        if (l1 + 1 >= l2) {
            a = l1;
            return false;
        }
        else if (l2 >= l1) {
            a = l2;
            int h = a * 0.85;

            int noofmatches = matching_characters(s1, s2);
            if (noofmatches >= h)
                return true;
            else if (noofmatches >= a)
                return true;
            else if (noofmatches < a)
                return false;
        }
    }
    void Traverse(treeNode* n, string word) {
        if (n != NULL)
        {
            Traverse(n->left, word);
            bool a = differBySingleChar(n->data, word);
            bool b = isSubstring(n->data, word);
            bool c = matchedchar(n->data, word);

            if (a || b || c)
                near.insert(n->data);
            Traverse(n->right, word);
        }
    }



    void findandreplace(string replaceStr, string replacementStr) {
        ifstream filein("input.txt");
        ofstream fileout("temp.txt");
        string strTemp;
        while (filein >> strTemp)
        {
            if (strTemp == replaceStr) {
                strTemp = replacementStr;
            }
            strTemp += " ";
            fileout << strTemp;
        }
        filein.close();
        fileout.close();
        char file[] = "input.txt";
        int result = remove(file);
        rename("temp.txt", "input.txt");

    }


    void search(string dict, string inp) {
        cout << "----------------------------------------------------------------------------------------" << endl;
        cout << "|-------------------------Welcome to Spell Checker & Corrector-------------------------|" << endl;
        cout << "----------------------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << ">>> Instructions :" << endl;
        cout << "   ->All the incorrect words are shown you one by one." << endl;
        cout << "   ->You have two options!" << endl;
        cout << "      1) You think your word is correct, then press 1 when you are asked: " << endl;
        cout << "           'Do you want to save word in dictionary, if you think it's correct [1 / 0]?'" << endl;
        cout << "      2) You found that your word is incorrect, then press 0 when you are asked: " << endl;
        cout << "           'Do you want to save word in dictionary, if you think it's correct [1 / 0]?'" << endl;
        cout << "         *In 2nd option nearby words will be suggessted!" << endl;
        cout << "         *Incase you entered word which is not enlisted in nearby words, it will ask again." << endl;
        cout << "         *Incase you entered word which is enlisted in nearby words, then all the occurences" << endl;
        cout << "            of incorrect word will be replaced by correct word" << endl;
        cout << "         *Incase there is no nearby word you will be asked to enter an alternated word." << endl;
        cout << endl;
        cout << "Best of luck !!!!" << endl;
        cout << endl;
        readdict(dict);
        string replace = "";
        istringstream ss(readinputfile(inp));
        string word;
        string remdup = "";
        while (ss >> word) {
            if (remdup.find(word) == string::npos) {
                if (searchword(dict, word))
                    int a = 0;
                else {
                    cout << word << " not found" << endl;
                    cout << "Do you want to save the " << word << " in dictionary, if you think it's correct [1/0]?" << endl;
                    string v ;
                    cin >> v;
                    cout << endl;
                    if (v == "1") {
                        addtofile(dict, word);
                        cout << "     >>>" << word << " is added to the dictionary" << endl;
                    }
                    else if (v == "0") {
                        bool ai = true;
                        cout << ">>> Nearby words are :" << endl;
                        cout << endl;
                        string pstr = processing(word);
                        Traverse(bst.root, pstr);
                        near.InorderTraverse(near.root);
                        string check = near.tra;
                        if (check == "") {
                            cout << "No nearby words!!" << endl;
                            cout << "Please enter alternate word : ";
                            cin >> replace;
                            remdup += word;
                            remdup += " ";
                            findandreplace(word, replace);
                            cout << "     >>>All occurences of '" << word << "' in " << inp << " is replaced by '" << replace << "'" << endl;
                            cout << endl;
                            ai = false;
                        }
                        near.root = NULL;


                        
                        while (ai) {
                            cout << "Please enter correct word from the list of nearby word : ";
                            cin >> replace;
                            cout << endl;
                            istringstream pp(check);
                            string w;
                            while (pp >> w) {
                                if (w == replace)
                                    ai = false;
                            }
                            if (ai) {

                                cout << "     >>>>As you enter a word incorrect nearby word !!!!" << endl;
                                cout << endl;
                            }
                            else {
                                remdup += word;
                                remdup += " ";
                                findandreplace(word, replace);
                                cout << "     >>>All occurences of '" << word << "' in " << inp << " is replaced by '" << replace << "'" << endl;
                                cout << endl;
                            }
                        }
                    }
                }
            }
        }
    }


};


int main()
{
    spellchecker sc;
    sc.search("dict.txt", "input.txt");

}