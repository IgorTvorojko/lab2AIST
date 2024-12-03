#include <iostream>
#include <vector>
#include <climits>
using namespace std;
enum Color { RED, BLACK };

struct node
{
    int data;
    Color color;
    node* left;
    node* right;
    node* parent;

    node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree
{
private:
    node* primaryRoot;

    void rotateLeft(node*& nod)
    {
        node* node_right = nod->right;
        nod->right = node_right->left;

        if (nod->right != nullptr)
        {
            nod->right->parent = nod;
        }

        node_right->parent = nod->parent;

        if (nod->parent == nullptr)
        {
            primaryRoot = node_right;
        }
        else if (nod == nod->parent->left)
        {
            nod->parent->left = node_right;
        }
        else
        {
            nod->parent->right = node_right;
        }

        node_right->left = nod;
        nod->parent = node_right;
    }

    void rotateRight(node*& nod)
    {
        node* node_left = nod->left;
        nod->left = node_left->right;

        if (nod->left != nullptr)
        {
            nod->left->parent = nod;
        }

        node_left->parent = nod->parent;

        if (nod->parent == nullptr)
        {
            primaryRoot = node_left;
        }
        else if (nod == nod->parent->left)
        {
            nod->parent->left = node_left;
        }
        else {
            nod->parent->right = node_left;
        }

        node_left->right = nod;
        nod->parent = node_left;
    }

    void fixViolation(node*& nod)
    {
        node* parent = nullptr;
        node* grandparent = nullptr;

        while ((nod != primaryRoot) && (nod->color == RED) && (nod->parent->color == RED))
        {
            parent = nod->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left)
            {
                node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED)
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    nod = grandparent;
                }
                else
                {
                    if (nod == parent->right)
                    {
                        rotateLeft(parent);
                        nod = parent;
                        parent = nod->parent;
                    }
                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    nod = parent;
                }
            }
            else
            {
                node* uncle = grandparent->left;

                if ((uncle != nullptr) && (uncle->color == RED))
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    nod = grandparent;
                }
                else {
                    if (nod == parent->left)
                    {
                        rotateRight(parent);
                        nod = parent;
                        parent = nod->parent;
                    }
                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    nod = parent;
                }
            }
        }
        primaryRoot->color = BLACK;
    }

public:
    RedBlackTree() : primaryRoot(nullptr) {}

    void insert(const int& data)
    {
        node* newnode = new node(data);
        primaryRoot = BSTInsert(primaryRoot, newnode);
        fixViolation(newnode);
    }

    node* BSTInsert(node* root, node* newnode)
    {
        if (root == nullptr)
        {
            return newnode;
        }

        if (newnode->data < root->data)
        {
            root->left = BSTInsert(root->left, newnode);
            root->left->parent = root;
        }
        else if (newnode->data > root->data)
        {
            root->right = BSTInsert(root->right, newnode);
            root->right->parent = root;
        }

        return root;
    }

    int max_vector(vector<int> vec)
    {
        int mx = INT_MIN;
        for (int i = 0; i < vec.size(); i++)
        {
            if (mx < vec[i])
            {
                mx = vec[i];
            }
        }
        return mx;
    }
    void get_data(node* these_child, int space, int position, vector<int>& vec_data, vector<int>& vec_level, vector<int>& vec_position)
    {
        vec_data.push_back(these_child->data);
        vec_level.push_back(space);
        vec_position.push_back(position);
        if (these_child->left != nullptr)
        {
            get_data(these_child->left, space + 1, position * 2, vec_data, vec_level, vec_position);
        }
        if (these_child->right != nullptr)
        {
            get_data(these_child->right, space + 1, position * 2 + 1, vec_data, vec_level, vec_position);
        }
    }

    void print_tree()
    {
        int space = 0;
        int position = 0;
        vector<int> vec_data;
        vector<int> vec_level;
        vector<int> vec_position;
        get_data(primaryRoot, space, position, vec_data, vec_level, vec_position);
        for (int i = 0; i < vec_data.size(); i++)
        {
            cout << vec_data.at(i) << "|" << vec_level.at(i) << "|" << vec_position.at(i) << " ";
        }
        cout << "\n";
        int max_level = max_vector(vec_level);
        int generationWidth = 6 * pow(2, max_level);
        int inGenerationStep = 6 * pow(2, max_level);
        for (int level = 0; level <= max_level; level++)
        {
            inGenerationStep /= 2;
            int counter_position = 0;
            int new_position = inGenerationStep;
            for (int j = 1; j <= generationWidth; j++)
            {
                if (j == new_position)
                {
                    bool check_position = false;
                    int index_position;
                    for (int k = 0; k < vec_data.size(); k++)
                    {
                        if (level == vec_level[k] and counter_position == vec_position[k])
                        {
                            check_position = true;
                            index_position = k;
                            break;
                        }
                    }
                    if (check_position)
                    {
                        cout << vec_data[index_position];
                        counter_position++;
                    }
                    else
                    {
                        cout << " ";
                        counter_position++;
                    }
                    new_position += inGenerationStep * 2;
                }
                else
                {
                    cout << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    node* getRoot(){
        return primaryRoot;
    }
    void print_test() {
    int space = 0;
    int position = 0;
    vector<int> vec_data;
    vector<int> vec_level;
    vector<int> vec_position;
    get_data(primaryRoot, space, position, vec_data, vec_level, vec_position);
    cout << max_vector(vec_level);
    }
};



void inorderTrav(node* node) {
    if (node->left)
        inorderTrav(node->left);
    cout << node->data << " ";
    if (node->right)
        inorderTrav(node->right);
}

void preorderTrav(node* node) {
    cout << node->data << " ";
    if (node->left)
        preorderTrav(node->left);
    if (node->right)
        preorderTrav(node->right);

}

void postorderTrav(node* node) {
    if (node->left)
        postorderTrav(node->left);
    if (node->right)
        postorderTrav(node->right);
    cout << node->data << " ";
}

void printCurrentLevel(node* root, int level);
int height(node* node);

void printLevelOrder(node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printCurrentLevel(root, i);
        cout << '\n';
    }

}

void printCurrentLevel(node* root, int level) {
    if (root == nullptr)
        return;
    if (level == 1)
        cout << root->data << " ";
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

int height(node* node) {
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
    RedBlackTree rbt;
    for (int i = 0; i < 10; i++)
    {
        data = rand() % 100;
        rbt.insert(data);
        //rbt.print_tree();
    } 
    cout << "inorder traversal: ";
    inorderTrav(rbt.getRoot());
    cout << "\npreorder traversal: ";
    preorderTrav(rbt.getRoot());
    cout << "\npostorder traversal: ";
    postorderTrav(rbt.getRoot());
    //cout << " depth: ";
    //rbt.print_test();
    cout << "\nBFS:\n";
    printLevelOrder(rbt.getRoot());
}