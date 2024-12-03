#include <iostream>
#include <vector>
#include <math.h>
#include <climits>
using namespace std;

class child
{
public:
    child* parent = nullptr;
    child* left = nullptr;
    child* right = nullptr;//Создание ссылки на следующий элемент
    int data = 0;
    int balance_level = 1;
};

class root
{
private:
    child* primaryRoot;//Указатель на первый элемент
    
    int max_vector(vector<int> matrix) {
    int max = INT_MIN;
    for (int i = 0; i < matrix.size(); i++) {
        if (max < matrix[i]) {
            max = matrix[i];
        }
    }
    return max;
}

    void getData(child* these_child, int space, int position, vector<int>& vec_data, vector<int>& vec_level, vector<int>& vec_position)
    {
        vec_data.push_back(these_child->data);
        vec_level.push_back(space);
        vec_position.push_back(position);
        if (these_child->left != nullptr)
        {
            getData(these_child->left, space + 1, position * 2, vec_data, vec_level, vec_position);
        }
        if (these_child->right != nullptr)
        {
            getData(these_child->right, space + 1, position * 2 + 1, vec_data, vec_level, vec_position);
        }
    }

public:
    root()//Конструктор списка
    {
        child* rootParent = nullptr;//Указатель на первый элемент
    }

    void insert(int data)
    {
        child* newChild = new child;
        child* currentParent = primaryRoot;
        if (primaryRoot == nullptr)
        {
            primaryRoot = newChild;
            primaryRoot->data = data;
        }
        else
        {
            bool parentless = true;
            while (parentless)
            {
                if (data <= currentParent->data)
                {
                    if (currentParent->left == nullptr)
                    {
                        currentParent->left = newChild;
                        newChild->parent = currentParent;
                        newChild->data = data;
                        parentless = false;
                    }
                    else
                    {
                        currentParent = currentParent->left;
                    }
                }
                else if (data > currentParent->data)
                {
                    if (currentParent->right == nullptr)
                    {
                        currentParent->right = newChild;
                        newChild->parent = currentParent;
                        newChild->data = data;
                        parentless = false;
                    }
                    else
                    {
                        currentParent = currentParent->right;
                    }
                }
            }
        }
    }

    child* findElem(int search_data)
    {
        child* thisParent = primaryRoot;
        bool search = true;
        while (search)
        {
            if (search_data == thisParent->data)
            {
                return (thisParent);
                cout << thisParent->data << endl << thisParent->left << endl << thisParent->right;
            }
            else if (search_data <= thisParent->data)
            {
                thisParent = thisParent->left;
            }
            else
            {
                thisParent = thisParent->right;
            }
        }
    }


    void delete_child(int data)
    {
        child* thisParent;
        child* thisSwapParent;
        thisParent = findElem(data);
        if (thisParent->left != nullptr and thisParent->right != nullptr)
        {
            thisSwapParent = thisParent->right;
            while (thisSwapParent->left != nullptr)
            {
                thisSwapParent = thisSwapParent->left;
            }
            if (thisParent->left != thisSwapParent)
            {
                thisSwapParent->left = thisParent->left;
            }
            if (thisParent->right != thisSwapParent)
            {
                thisSwapParent->right = thisParent->right;
            }
            thisSwapParent->parent->left = nullptr;
            thisSwapParent->parent = thisParent->parent;
            if (thisParent != primaryRoot)
            {
                if (thisParent->parent->data >= thisParent->data)
                {
                    thisParent->parent->left = thisSwapParent;
                }
                else
                {
                    thisParent->parent->right = thisSwapParent;
                }
            }
            if (thisParent == primaryRoot)
            {
                primaryRoot = thisSwapParent;
            }
            delete thisParent;
        }
        else if (thisParent->left != nullptr)
        {
            thisParent->left->parent = thisParent->parent;
            thisParent->parent->left = thisParent->left;
            thisSwapParent = thisParent->parent;
            if (thisParent == primaryRoot)
            {
                primaryRoot = thisSwapParent;
            }
            delete thisParent;
        }
        else if (thisParent->right != nullptr)
        {
            thisParent->right->parent = thisParent->parent;
            thisParent->parent->right = thisParent->right;
            thisSwapParent = thisParent->parent;
            if (thisParent == primaryRoot)
            {
                primaryRoot = thisSwapParent;
            }
            delete thisParent;
        }
        else
        {
            if (thisParent != primaryRoot)
            {
                if (thisParent->parent->data >= thisParent->data)
                {
                    thisParent->parent->left = nullptr;
                }
                else
                {
                    thisParent->parent->right = nullptr;
                }
            }
            delete thisParent;
        }
    }

    void print_tree()
    {
        int space = 0;
        int position = 0;
        vector<int> vec_data;
        vector<int> vec_level;
        vector<int> vec_position;
        getData(primaryRoot, space, position, vec_data, vec_level, vec_position);
        for (int i = 0; i < vec_data.size(); i++) {
            cout << vec_data.at(i) << "|" << vec_level.at(i) << "|" << vec_position.at(i) << " ";
        }
        cout << "\n";
        int max_level = max_vector(vec_level);
        int generationWidth = 6 * pow(2, max_level);
        int inGenerationStep = 6 * pow(2, max_level);
        for (int level = 0; level <= max_level; level++) {
            inGenerationStep /= 2;
            int counter_position = 0;
            int new_position = inGenerationStep;
            for (int j = 1; j <= generationWidth; j++) {
                if (j == new_position) {
                    bool check_position = false;
                    int index_position;
                    for (int k = 0; k < vec_data.size(); k++) {
                        if (level == vec_level[k] and counter_position == vec_position[k]) {
                            check_position = true;
                            index_position = k;
                            break;
                        }
                    }
                    if (check_position) {
                        cout << vec_data[index_position];
                        counter_position++;
                    }
                    else {
                        cout << " ";
                        counter_position++;
                    }
                    new_position += inGenerationStep * 2;
                }
                else {
                    cout << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    /*void inorderTrav() {
        inorderTrav()
    }*/

    child* getRootParent() {
        return primaryRoot;
    }
    void print_test() {
        int space = 0;
        int position = 0;
        vector<int> matrix_data;
        vector<int> matrix_level;
        vector<int> matrix_position;
        getData(primaryRoot, space, position, matrix_data, matrix_level, matrix_position);
        cout << max_vector(matrix_level);
    }
};

void inorderTrav(child* node) {
    if (node->left)
        inorderTrav(node->left);
    cout << node->data << " ";
    if (node->right)
        inorderTrav(node->right);
}

void preorderTrav(child* node) {
    cout << node->data << " ";
    if (node->left)
        preorderTrav(node->left);
    if (node->right)
        preorderTrav(node->right);
    
}

void postorderTrav(child* node) {
    if (node->left)
        postorderTrav(node->left);
    if (node->right)
        postorderTrav(node->right);
    cout << node->data << " ";
}

void printCurrentLevel(child* root, int level);
int height(child* node);

void printLevelOrder(child* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printCurrentLevel(root, i);
        cout << '\n';
    }

}

void printCurrentLevel(child* root, int level) {
    if (root == nullptr)
        return;
    if (level == 1)
        cout << root->data << " ";
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

int height(child* node) {
    if (node == nullptr)
        return 0;
    else {
        int lheight = height(node->left);
        int rheight = height(node->right);
        return (lheight > rheight) ? (lheight + 1) :
            (rheight + 1);
    }
}

int main()
{
    int data;
    root Root;
    for (int i = 0; i < 10; i++)
    {
        data = rand() % 100;
        Root.insert(data);
        //Root.print_tree();
    }
    cout << "inorder traversal: ";
    inorderTrav(Root.getRootParent());
    cout << "\nprenorder traversal: ";
    preorderTrav(Root.getRootParent());
    cout << "\npostorder traversal: ";
    postorderTrav(Root.getRootParent());
    //cout << " depth: ";
    //Root.print_test();
    cout << "\nBFS:\n";
    printLevelOrder(Root.getRootParent());
}