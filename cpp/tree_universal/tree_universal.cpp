
#include "common.h"

using namespace std;

using NodeT = shared_ptr<NodeTree<int>>;

bool isUniversalTree(NodeT root)
{
    if (root == nullptr)
        return true;

    if (root->left && root->value != root->left->value)
        return false;

    if (root->right && root->value != root->right->value)
        return false;

    if (isUniversalTree(root->left) && isUniversalTree(root->right))
    {
        return true;
    }

    return false;
}

int countUniversalTrees(NodeT root)
{
    if (root == nullptr)
        return 0;

    auto count = countUniversalTrees(root->left) + countUniversalTrees(root->right);

    if (isUniversalTree(root))
    {
        ++count;
    }

    return count;
}

struct Res
{
    int count;
    bool isUniversalTree;
};

Res getUniversalTrees(NodeT root)
{
    if (root == nullptr)
        return {0, true};

    auto resLeft = getUniversalTrees(root->left);
    auto resRight = getUniversalTrees(root->right);

    Res resToReturn = {resLeft.count + resRight.count, resLeft.isUniversalTree && resRight.isUniversalTree};

    if (root->left && root->value != root->left->value)
        resToReturn.isUniversalTree = false;

    if (root->right && root->value != root->right->value)
        resToReturn.isUniversalTree = false;

    if (resToReturn.isUniversalTree)
        ++resToReturn.count;

    return resToReturn;
}

int main()
{
    auto root = make_shared<NodeTree<int>>(1);

    root->left = make_shared<NodeTree<int>>(4);
    root->right = make_shared<NodeTree<int>>(3);

    root->left->left = make_shared<NodeTree<int>>(4);
    root->left->right = make_shared<NodeTree<int>>(4);

    root->right->left = make_shared<NodeTree<int>>(6);
    root->right->right = make_shared<NodeTree<int>>(7);

    root->left->left->left = make_shared<NodeTree<int>>(4);
    root->left->left->right = make_shared<NodeTree<int>>(4);

    root->left->right->left = make_shared<NodeTree<int>>(4);
    root->left->right->right = make_shared<NodeTree<int>>(4);

    root->right->left->left = make_shared<NodeTree<int>>(6);
    root->right->left->right = make_shared<NodeTree<int>>(6);

    root->right->right->left = make_shared<NodeTree<int>>(7);
    root->right->right->right = make_shared<NodeTree<int>>(7);

    breadthSearch(root);

    int count = countUniversalTrees(root);
    cout<<"Amount of universal trees "<<count<<endl;

    auto res = getUniversalTrees(root);
    cout<<"Amount of universal trees (2) "<<res.count<<endl;

    return 0;
}
