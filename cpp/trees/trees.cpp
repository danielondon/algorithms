
#include "common.h"

using namespace std;

template <class T>
void preOrder(shared_ptr<NodeTree<T>> root)
{
    if (root == nullptr)
        return;

    cout<<root->value<<" ";
    preOrder(root->left);
    preOrder(root->right);
}

template <class T>
void postOrder(shared_ptr<NodeTree<T>> root)
{
    if (root == nullptr)
        return;

    postOrder(root->left);
    postOrder(root->right);
    cout<<root->value<<" ";
}

template <class T>
void inOrder(shared_ptr<NodeTree<T>> root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);
    cout<<root->value<<" ";
    inOrder(root->right);
}

int main()
{
    auto root = make_shared<NodeTree<int>>(1);

    root->left = make_shared<NodeTree<int>>(2);
    root->right = make_shared<NodeTree<int>>(3);

    root->left->left = make_shared<NodeTree<int>>(4);
    root->left->right = make_shared<NodeTree<int>>(5);

    root->right->left = make_shared<NodeTree<int>>(6);
    root->right->right = make_shared<NodeTree<int>>(7);

    root->left->left->left = make_shared<NodeTree<int>>(8);
    root->left->left->right = make_shared<NodeTree<int>>(9);

    root->left->right->left = make_shared<NodeTree<int>>(10);
    root->left->right->right = make_shared<NodeTree<int>>(11);

    root->right->left->left = make_shared<NodeTree<int>>(12);
    root->right->left->right = make_shared<NodeTree<int>>(13);

    root->right->right->left = make_shared<NodeTree<int>>(14);
    root->right->right->right = make_shared<NodeTree<int>>(15);

    cout<<endl<<"Preorder: ";
    preOrder(root);
    cout<<endl<<"Inorder: ";
    inOrder(root);
    cout<<endl<<"Postorder: ";
    postOrder(root);
    cout<<endl<<"Breath Search: "<<endl;
    breadthSearch(root);
    cout<<endl;
}
