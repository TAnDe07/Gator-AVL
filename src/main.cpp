#include "MyAVLTree.h"
#include <sstream>
#include <cctype>
// help from Rutvi Shukla-TA with parsing input


/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

// remove quotation marks from Name
string removeQuotation (string nameInfo) {
    string name;
    for (int i = 1; i < nameInfo.length() - 1; ++i) {
        name += nameInfo.at(i);
    }
    return name;
}

//Verify is ID is valid
bool isNum(string ID){
    bool isID = true;
    for (int i = 0; i < ID.length(); ++i) {
        if (!isalnum(ID.at(i))) {
            cout << "unsuccessful" << endl;
            isID = false;
            break;
        }
    }
    return isID;
}

//Verify if name is valid
bool isAlpha(string name ) {
    bool isName = true;
    for (int i = 0; i < name.length(); ++i) {
        if (!isalpha(name.at(i)) && !isspace(name.at(i))) {
            cout << "unsuccessful" << endl;
            isName = false;
            break;
        }
    }
    return isName;
}

int main(){

    string instruction = ""; //get first word of instruction
    string lineCount; //get number of lines of instructions
    string fullInstructions; //get line of instruction
    string gatorID = ""; //store ID to be inserted
    string gatorName = ""; //store name to be inserted

    MyAVLTree* tree = new MyAVLTree(); //creates tree


    getline(cin, lineCount);

    for (int i = 0; i < stoi(lineCount); ++i) {
        //get line of instruction
        getline(cin, fullInstructions);
        instruction = fullInstructions.substr(0,fullInstructions.find_first_of(" "));

        // search
        if (instruction == "search") {

            gatorName = fullInstructions.substr(fullInstructions.find_first_of(" ") + 1, fullInstructions.find_first_of("\n"));

            // if Name
            if (gatorName.at(0) == '"' && gatorName.at(gatorName.length() - 1) == '"') {

                // removes quotation marks from string
                string name = removeQuotation(gatorName);

                // checks for valid letter input
                bool isName = isAlpha(name);

                // if valid letter input search for name in tree
                if (isName) {
                    tree->searchName(name);
                }
            }
            //if ID
            else if (gatorName.length() == 8 && (gatorName.at(0) != '"' && gatorName.at(gatorName.length() - 1) != '"')){

                // checks is string is all numbers
                bool isID = isNum(gatorName);

                // if valid ID input, search for string in tree
                if (isID) {
                    cout << tree->searchID(stoi(gatorName)) << endl;
                }
            }
            else {
                // if not ID or Name
                cout << "unsuccessful" << endl;
            }
        }
        // Insert
        else if (instruction == "insert") {

            string nameID = fullInstructions.substr(fullInstructions.find_first_of("\""), fullInstructions.find_first_of("\n"));

            gatorName = nameID.at(0);
            int index = 1;
            while (nameID.at(index) != '\"') {
                gatorName += nameID.at(index);
                index++;
            }
            gatorName += nameID.at(index);
            index++;
            gatorID = nameID.substr(index + 1, nameID.find_first_of("\n"));

            //if correct format
            if (gatorID.length() != 8 || (gatorName.at(0) != '"' && gatorName.at(gatorName.length()) != '"')) {
                cout << "unsuccessful" << endl;
            }
            else {
                // is name and ID are valid?
                bool isID = isNum(gatorID);
                bool isName;
                string name;
                if (isID) {
                    name = removeQuotation(gatorName);
                    isName = isAlpha(name);
                    if (stoi(gatorID) == 0) {
                        isID = false;
                    }
                }
                if (isID && isName) {
                    //insert info in tree
                    if (tree->searchID(stoi(gatorID)) == "unsuccessful") {
                        tree->insert(name, stoi(gatorID));
                    }
                    else {
                        cout << "unsuccessful" << endl;
                    }
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }

        }
        // print level count
        else if (instruction == "printLevelCount") {
            tree->levelCount();
        }
        // print inorder
        else if (instruction == "printInorder") {
            tree->inorder();
        }
        // print preorder
        else if (instruction == "printPreorder") {
            tree->preorder();
        }
        // print postorder
        else if (instruction == "printPostorder") {
            tree->postorder();
        }
        // remove inorder
        else if (instruction == "remove") {
           gatorID = fullInstructions.substr(fullInstructions.find_first_of(" ") + 1, fullInstructions.find_first_of("\n"));
            // is ID valid? if yes, removes it
            if (isNum(gatorID) && gatorID.length() == 8) {
                tree->removeID(stoi(gatorID));
            }
        }
        // remove
        else if (instruction == "removeInorder") {
            string nID;
            nID = fullInstructions.substr(fullInstructions.find_first_of(" ") + 1, fullInstructions.find_first_of("\n"));
            //if ID is valid, removes it
            if (isNum(nID)) {
                tree->removeInorder(stoi(nID));
            }
        }
        // if instruction is invalid
        else {
            cout << "unsuccessful" << endl;
        }

    }

	return 0;
}