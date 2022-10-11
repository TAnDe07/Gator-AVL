//
// Created by tanad on 9/18/2022.
// SEPTIK MODULE 4, 5
// MODULE 4, 5 LECTURE SLIDES
//
//
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

#ifndef PROJECT1_MYAVLTREE_H
#define PROJECT1_MYAVLTREE_H

#endif //PROJECT1_MYAVLTREE_H

class MyAVLTree{
private:
    struct Node {
        string name;
        int ID;
        Node* left;
        Node* right;
        Node(string x, int y) : name(x), ID(y), left(nullptr), right(nullptr){}
    };
    Node* root = nullptr;

    //helper functions definition
    MyAVLTree:: Node* helperInsert(Node * helperRoot, string name, int ID);
    void helperSearchName(Node * helperRoot, string name);
    MyAVLTree::Node* helperSearchID(Node * helperRoot, int ID);
    int getHeight(Node * helperRoot);
    void inorderHelper(Node* helperRoot, vector<Node*>& students);
    void preorderHelper(Node* helperRoot, vector<Node*>& students);
    void postorderHelper(Node* helperRoot, vector<Node*>& students);
    MyAVLTree::Node* isBalanced(Node* helperRoot, int ID);
    int isAVL(Node* helperRoot);
    int levelCountHelper (Node* helperRoot);
    MyAVLTree::Node* leftRotation (Node* helperNode);
    MyAVLTree::Node* rightRotation (Node* node);
    MyAVLTree::Node* leftRightRotation (Node* helperNode);
    MyAVLTree::Node* rightLeftRotation (Node* helperNode);
    string removeIDHelper (Node* helperRoot, int ID);
    string removeInorderHelper (Node* helperRoot, int n);
    MyAVLTree::Node* destruct (Node* &helperRoot, int ID);

public:

    void insert(string x, int ID);

    void searchName (string name);

    string searchID (int ID);

    vector<string> inorder ();

    void preorder ();

    void postorder ();

    void levelCount ();

    void removeID (int ID);

    void removeInorder (int n);

};

//Insert
void MyAVLTree::insert(string x, int ID) {

    //calls helper method
    this->root = helperInsert(this->root, x, ID);
    cout << "successful" << endl;

}

MyAVLTree::Node* MyAVLTree::helperInsert(MyAVLTree::Node *helperRoot, string name, int ID) {
    // if tree is empty, insert at root
    if(helperRoot == nullptr) {
        return new Node(name, ID);
    }
    // if id is less than current id, go to left subtree
    else if (helperRoot->ID > ID) {
        helperRoot->left = helperInsert(helperRoot->left, name, ID);
    }
    // if id is greater than current id, go to right subtree
    else if (helperRoot->ID < ID){
        helperRoot->right = helperInsert(helperRoot->right, name, ID);
    }
    // if id is equal to current id, print unsuccessful, and return
    else if (helperRoot->ID == ID) {
        cout << "unsuccessful" << endl;
        return helperRoot;
    }
    //balance tree after insertion
    return isBalanced(helperRoot, ID);
}

//Search name
void MyAVLTree::searchName(string name) {
    //call helper function
    helperSearchName(root, name);
}

void MyAVLTree::helperSearchName(MyAVLTree::Node *helperRoot, string name) {
    vector<Node*> students;
    inorderHelper(helperRoot, students);
    int temp = 0;
    string ID2;
    string normalID = "";

    //search through inorder vector for name
    for (int i = 0; i < students.size(); ++i) {
        if (students.at(i)->name == name) {
            ID2 = to_string(students.at(i)->ID);
            if (ID2.length() < 8) {
                for (int j = 0; j < 8 - ID2.length(); ++j) {
                    normalID += '0';
                }
                normalID += ID2;
                cout << normalID << endl;
            }
            else {
                cout << students.at(i)->ID << endl;
            }
            temp = 1;
        }
    }
    if (temp == 0) {
        cout << "unsuccessful" << endl;
    }
}

//Search ID
string MyAVLTree::searchID(int ID) {
    //call helper function
    Node* IDFound = helperSearchID(this->root, ID);
    if (IDFound!= nullptr) {
        return IDFound->name;
    }
    return "unsuccessful";
}

MyAVLTree::Node* MyAVLTree::helperSearchID(MyAVLTree::Node *helperRoot, int ID) {
    Node * temp = helperRoot;
    //while id is not found
    while (temp != nullptr && temp->ID != ID ) {
        //if id is greater than current id, go to right subtree
        if(temp->ID < ID) {
            temp = temp->right;
        }
        //if id is less than current id, go to left subtree
        else {
            temp = temp->left;
        }
    }
    //if id is found
    if (temp != nullptr && temp->ID == ID) {
        return temp;
    }
    return nullptr;
}

//inorder : change back to void or change
vector<string> MyAVLTree::inorder() {
    vector<Node*> students;
    inorderHelper(root, students); //calls and stores info inorder

    //for catch test cases (remove)
    vector<string> names;
    for (int i = 0; i < students.size(); ++i) {
        names.push_back(students.at(i)->name);
    }

    // print the inorder
    if (students.size() != 0) {
        int i = 0;
        for (i = 0; i < students.size() - 1; ++i) {
            string curName = students.at(i)->name;
            cout << curName << ", ";
            cout.flush(); //https://stackoverflow.com/questions/14858262/stdcout-wont-print
        }
        cout << students.at(i)->name << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }

    //for catch test cases (remove)
    return names;
}

void MyAVLTree::inorderHelper(MyAVLTree::Node *helperRoot, vector<Node*>& students) {
    //if tree is empty
    if (helperRoot == nullptr) {
        return;
    }
    //gets reference of info inorder and stores them in vector
    inorderHelper(helperRoot->left, students);
    students.push_back(helperRoot);
    inorderHelper(helperRoot->right, students);
}

//preorder
void MyAVLTree::preorder() {
    vector<Node*> students;
    preorderHelper(root, students); //calls and stores info preorder


    // print the preorder
    if (students.size() != 0) {
        int i = 0;
        for (i = 0; i < students.size() - 1; ++i) {
            string curName = students.at(i)->name;
            cout << curName << ", ";
            cout.flush(); //https://stackoverflow.com/questions/14858262/stdcout-wont-print
        }
        cout << students.at(i)->name << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }

}

void MyAVLTree::preorderHelper(MyAVLTree::Node *helperRoot, vector<Node*>& students) {
    //tree is empty
    if (helperRoot == nullptr) {
        return;
    }
    //gets reference of info preorder and stores them in vector
    students.push_back(helperRoot);
    preorderHelper(helperRoot->left, students);
    preorderHelper(helperRoot->right, students);

}

//postorder
void MyAVLTree::postorder() {
    vector<Node*> students;
    postorderHelper(root, students); //calls and stores info postorder

    // print postorder
    if (students.size() != 0) {
        int i = 0;
        for (i = 0; i < students.size() - 1; ++i) {
            string curName = students.at(i)->name;
            cout << curName << ", ";
            cout.flush(); //https://stackoverflow.com/questions/14858262/stdcout-wont-print
        }
        cout << students.at(i)->name << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

void MyAVLTree::postorderHelper(MyAVLTree::Node *helperRoot, vector<Node*> & students) {
    //tree is empty
    if (helperRoot == nullptr) {
        return;
    }
    //gets reference of info postorder and stores them in vector
    postorderHelper(helperRoot->left, students);
    postorderHelper(helperRoot->right, students);
    students.push_back(helperRoot);
}

//height of tree
int MyAVLTree::getHeight(MyAVLTree::Node *helperRoot) {
    if (helperRoot == nullptr) {
        return 0;
    }
    else {
        return 1 + std::max(getHeight(helperRoot->left), getHeight(helperRoot->right));
    }
}

//check if tree is avl (balanced)
int MyAVLTree::isAVL(MyAVLTree::Node *helperRoot) {
    if (helperRoot == nullptr) {
        return 0;
    }
    int lHeight = getHeight(helperRoot->left);
    int rHeight = getHeight(helperRoot->right);
    int height = (lHeight - rHeight);

    return height;
}

//perform rotations to balance the tree
MyAVLTree::Node* MyAVLTree::isBalanced(MyAVLTree::Node *helperRoot, int ID) {
    int AVLBalance = isAVL(helperRoot);
    if (AVLBalance == 0) {
        return helperRoot;
    }
    if (AVLBalance < -1) {
        if (isAVL(helperRoot->right) >= 1) {
            return rightLeftRotation(helperRoot);
        }
        else {
            return leftRotation(helperRoot);
        }
    }
    else if (AVLBalance > 1) {
        if (isAVL(helperRoot->left) <= -1) {
           return leftRightRotation(helperRoot);
        }
        else {
           return rightRotation(helperRoot);
        }
    }
    else {
        return helperRoot;
    }
}

//level count
void MyAVLTree::levelCount() {
    cout << levelCountHelper(root) << endl;
}

int MyAVLTree::levelCountHelper(MyAVLTree::Node *helperRoot) {
   //level order traversal to get level count
    if (helperRoot == nullptr) {
        return 0;
    }
    int level = 0;
    queue<Node*> data;
    data.push(helperRoot);
    while (!data.empty()) {
        int size = data.size();
        for (int i = 0; i < size; ++i) {
            Node* nNode = data.front();
            data.pop();
            if (nNode->left != nullptr) {
                data.push(nNode->left);
            }
            if (nNode->right != nullptr) {
                data.push(nNode->right);
            }
        }
        level++;
    }
    return level;
}

//rotations
MyAVLTree::Node* MyAVLTree::leftRotation (Node* helperNode) {

    Node* right = helperNode->right;
    helperNode->right = right->left;
    right->left = helperNode;
    return right;
}

MyAVLTree::Node* MyAVLTree::rightRotation (Node* helperNode) {

    Node* left = helperNode->left;
    helperNode->left = left->right;
    left->right = helperNode;
    return left;
}

MyAVLTree::Node* MyAVLTree::leftRightRotation (Node* helperNode) {

    helperNode->left = leftRotation(helperNode->left);
    return rightRotation(helperNode);
}

MyAVLTree::Node* MyAVLTree::rightLeftRotation (Node* helperNode) {
    helperNode->right = rightRotation(helperNode->right);
    return leftRotation(helperNode);
}

//destructor
MyAVLTree::Node* MyAVLTree::destruct(Node* &helperRoot, int ID) {
    //looks for node
    if (helperRoot == nullptr) {
        return nullptr;
    }
    else if (helperRoot->ID > ID) {
        destruct(helperRoot->left, ID);
    }
    else if (helperRoot->ID < ID) {
        destruct(helperRoot->right, ID);
    }
    //node found, deletes based on different cases
    else {
        //leaf node
        if (helperRoot->right == nullptr && helperRoot->left == nullptr) {
            delete helperRoot;
            helperRoot = nullptr;
            return helperRoot;
        }
        //node with one child
        else if (helperRoot->left != nullptr && helperRoot->right == nullptr) {
            delete helperRoot->right;
            helperRoot = helperRoot->left;
            return helperRoot;
        }
        //node with one child
        else if (helperRoot->left == nullptr && helperRoot->right != nullptr) {
            delete helperRoot->left;
            helperRoot = helperRoot->right;
            return helperRoot;
        }
        //node with two children
        else {
            //look for inorder successor to replace node
            if (helperRoot->right->left == nullptr) {
                delete helperRoot->right->left;
                Node* temp = helperRoot;
                temp = helperRoot->right;
                temp->left = helperRoot->left;
                delete helperRoot;
                return temp;
            }
            else {
                Node* temp = helperRoot->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                 helperRoot = temp;
                return helperRoot;
            }
        }
    }

    return helperRoot;
}

//remove ID
void MyAVLTree::removeID (int ID) {
    //call helper method
    string isIDRemoved = removeIDHelper(root, ID);
    cout << isIDRemoved << endl;
}

string MyAVLTree::removeIDHelper(MyAVLTree::Node *helperRoot, int ID) {
    //calls destructor if id is found
    Node* IDFound = helperSearchID(helperRoot, ID);
    if (IDFound == nullptr) {
        return "unsuccessful";
    }
    root = destruct(helperRoot, ID);
    return "successful";
}

//remove inorder
void MyAVLTree::removeInorder (int n) {
    //call helper function
    string isRemoved = removeInorderHelper(root, n);
    cout << isRemoved << endl;
}

string MyAVLTree::removeInorderHelper(MyAVLTree::Node *helperRoot, int n) {
    vector<Node*> temp;
    inorderHelper(helperRoot, temp); //get inorder of tree

    for (int i = 0; i < temp.size(); ++i) {
        //call destructor if n node is found
        if (i == n) {
            this->root = destruct(helperRoot, temp.at(i)->ID);
            return "successful";

        }
    }
    return "unsuccessful";

}




