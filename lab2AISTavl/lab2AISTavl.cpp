#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct node {
    int data;
    unsigned char height;
    node* left;
    node* right;
    node(int k) { data = k; left = right = 0; height = 1; }
};

int max_vector(vector<int> vec) {
    int max = INT_MIN;
    for (int i = 0; i < vec.size(); i++) {
        if (max < vec[i]) {
            max = vec[i];
        }
    }
    return max;
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

void print_tree(node* root_parent)
{
    int space = 0;
    int position = 0;
    vector<int> vec_data;
    vector<int> vec_level;
    vector<int> vec_position;
    get_data(root_parent, space, position, vec_data, vec_level, vec_position);
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

unsigned char height(node* p)
{
    return p ? p->height : 0;
}

int bfactor(node* p)
{
    return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) return new node(k);
    if (k < p->data)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
    return p->left ? findmin(p->left) : p;
}


node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->data)
        p->left = remove(p->left, k);
    else if (k > p->data)
        p->right = remove(p->right, k);
    else //  k == p->data 
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if (!r) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void print_test(node* root_parent)
{
    int space = 0;
    int position = 0;
    vector<int> vec_data;
    vector<int> vec_level;
    vector<int> vec_position;
    get_data(root_parent, space, position, vec_data, vec_level, vec_position);
    cout << max_vector(vec_level);
}

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
int depth(node* node);

void printLevelOrder(node* root) {
    int h = depth(root);
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

int depth(node* node) {
    if (node == nullptr)
        return 0;
    else {
        int lheight = depth(node->left);
        int rheight = depth(node->right);
        return (lheight > rheight) ? (lheight + 1) :
            (rheight + 1);
    }
}

int main()
{
    int data;
    node* root;
    data = rand() % 100;
    node tree(data);
    root = &tree;
    for (int i = 1; i < 10; i++)
    {
        data = rand() % 100;
        root = insert(root, data);
        //print_tree(root);
    }
    cout << "inorder traversal: ";
    inorderTrav(root);
    cout << "\npreorder traversal: ";
    preorderTrav(root);
    cout << "\npostorder traversal: ";
    postorderTrav(root);
    //cout << " depth: ";
    //print_test(root);
    cout << "\nBFS\n";
    printLevelOrder(root);
}