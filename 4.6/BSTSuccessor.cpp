#include <iostream>
#include <memory>
#include <queue>
#include <exception>


template<typename T>
struct Node
{
    Node(T val) : value(val) { }
    Node(T val, const std::shared_ptr<Node<T>> & nodesParent) : value(val), parent(nodesParent) { }
    T value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;
};

template<typename T>
class BST
{
public:
    using NodePtr = std::shared_ptr<Node<T>>;
private:
    NodePtr root;

    void addRecursive(T value, const NodePtr & node) {
        if (value < node->value) {
            if (!node->left)
                node->left = std::make_shared<Node<T>>(value, node);
            else
                addRecursive(value, node->left);
        } else {
            if (!node->right)
                node->right = std::make_shared<Node<T>>(value, node);
            else
                addRecursive(value, node->right);
        }
    }

    T findMin(const NodePtr & node)
    {
        if (node->left)
            return findMin(node->left);
        return node->value;
    }

    NodePtr getNodeRecursive(T value, const NodePtr & node)
    {
        if (node->value == value)
            return node;
        if (value < node->value && node->left)
            return getNodeRecursive(value, node->left);

        if (node->right)
            return getNodeRecursive(value, node->right);
        throw std::runtime_error("Node with value " + std::to_string(value) + " not found!");
    }

public:

    void add(T value) {
        if (!root)
            root = std::make_shared<Node<T>>(value);
        else
            addRecursive(value, root);
    }

    void print()    // BFS printing
    {
        int depth = 0;
        std::queue<std::pair<const NodePtr, int>> queue;
        queue.push(std::make_pair(root, depth));
        while (!queue.empty())
        {
            const auto & front = queue.front();

            if (front.second > depth) {
                std::cout<<std::endl;
                ++depth;
            }

            std::cout<<"\t"<<front.first->value;

            if (front.first->left) {
                queue.push(std::make_pair(front.first->left, depth+1));
            }
            if (front.first->right) {
                queue.push(std::make_pair(front.first->right, depth+1));
            }
            queue.pop();
        }

        std::cout<<std::endl;
    }

    T findSuccessor(T value)
    {
        const auto & node = getNode(value);
        if (node->right)
            return findMin(node->right);
        if (node->parent->parent)
            return node->parent->parent->value;
        throw std::runtime_error("Node successor for value " + std::to_string(value) + " not found!");
    }


    NodePtr getNode(T value)
    {
        return getNodeRecursive(value, root);
    }
};

int main()
{
    BST<int> bst;
    bst.add(5);
    bst.add(6);
    bst.add(3);
    bst.add(1);
    bst.add(4);

    bst.print();

    std::cout<<bst.findSuccessor(3)<<std::endl;
    std::cout<<bst.findSuccessor(4)<<std::endl;
    std::cout<<bst.findSuccessor(6)<<std::endl;

    return 0;
}
