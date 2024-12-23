#include <iostream>
#include <algorithm>

using namespace std;
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    //khởi tạo node
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};
class AVLTree {
private:
    Node* root;
    // chiều cao của cây
    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    // tính toán cân bằng cây
    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }
    // Hàm xoay đơn sang phải
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        // Xoay
        x->right = y;
        y->left = T2;
        // Cập nhật chiều cao
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        // Trả về node mới
        return x;
    }
    // Hàm xoay đơn sang trái
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        // Xoay
        y->left = x;
        x->right = T2;
        // Cập nhật chiều cao
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        // Trả về node mới
        return y;
    }
    // Hàm xoay kép trái-phải
    Node* rotateLeftRight(Node* node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Hàm xoay kép phải-trái
    Node* rotateRightLeft(Node* node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    // Hàm chèn giá trị vào cây
    Node* insert(Node* node, int key) {
        // 1. Thực hiện chèn giống cây nhị phân tìm kiếm
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);

        // 2. Cập nhật chiều cao của node
        node->height = max(height(node->left), height(node->right)) + 1;

        // 3. Kiểm tra cân bằng của node để thực hiện xoay nếu cần
        int balance = getBalance(node);

        // Nếu node mất cân bằng, có 4 trường hợp

        // Trường hợp 1: Left Left
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Trường hợp 2: Right Right
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Trường hợp 3: Left Right
        if (balance > 1 && key > node->left->key)
            return rotateLeftRight(node);

        // Trường hợp 4: Right Left
        if (balance < -1 && key < node->right->key)
            return rotateRightLeft(node);

        // Trả về node nếu không cần xoay
        return node;
    }
    // Duyệt cây theo thứ tự
    void inorderTraversal(Node* node) {
        if (node == nullptr)
            return;
        inorderTraversal(node->left);
        cout << node->key << " ";
        inorderTraversal(node->right);
    }
public:
    // Constructor
    AVLTree() : root(nullptr) {}
    // Hàm chèn giá trị vào cây
    void insert(int key) {
        root = insert(root, key);
    }
    // Hàm in cây theo thứ tự duyệt
    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }
};
int main() {
    AVLTree tree;
    // Dãy số cần chèn vào cây
    int values[] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        tree.insert(values[i]);
    }
    // In cây theo thứ tự duyệt
    cout << "In-order traversal của cây AVL: ";
    tree.inorder();
    return 0;
}