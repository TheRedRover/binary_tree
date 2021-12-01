#pragma once
#include <iostream>
#include <memory>
#include <string>
#include<vector>
#include <unordered_map>

namespace BT {

    template<typename T>
    struct Node
    {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(T d);
    };

    template<typename T>
    struct BinaryTree
    {
        std::unique_ptr<Node<T>> root;

        void insert(T new_node_data);
        void delete_(T data_to_delete);


        void print( const Node<T>* node, const std::string& prefix="", bool isLeft=false);
        void inorder_print(Node<T> * node, const std::string & direction="");
        void reverse_inorder_print(BT::Node<T> *node, const std::string & direction="");

        Node<T> * search(T key);

        Node<T> * successor(T key);

        Node<T> * predecessor(T key);

        int height(Node<T> * node);

        void print_by_layer(Node <T> *root_);

        void pretty_print_by_layer(Node <T> *root_);


    private:
        void insert(T new_node_data, Node<T> * leaf);
        void print_current_level(Node <T> *root_, int level);

        void preorder(Node<T>* root_, int level, std::unordered_map<int, std::vector<T>> &map);
    };
}

template<typename T>
void BT::BinaryTree<T>::insert(T new_node_data, Node<T> * leaf) {
    if(new_node_data < leaf->data){
        if(leaf->left != nullptr){
            insert(new_node_data, leaf->left.get());
        }else{
            leaf->left = std::make_unique<Node<T>>(new_node_data);
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
        }
    }else if(new_node_data >= leaf->data){
        if(leaf->right != nullptr){
            insert(new_node_data, leaf->right.get());
        }else{
            leaf->right = std::make_unique<Node<T>>(new_node_data);
            leaf->right->right = nullptr;
            leaf->right->left = nullptr;
        }
    }
}

template<typename T>
void BT::BinaryTree<T>::insert(T new_node_data) {
    if(root != nullptr){
        insert(new_node_data, root.get());
    }else{
        root = std::make_unique<Node<T>>(new_node_data);
        root->left = nullptr;
        root->right = nullptr;
    }
}

template<typename T>
void BT::BinaryTree<T>::delete_(T data_to_delete) {
    Node<T> * tmp = root.get();
    Node<T> * parent = tmp;
    if(data_to_delete==root->data) {
        tmp = tmp->right.get();
        while(tmp->left!= nullptr)
        {
            parent = tmp;
            tmp = tmp->left.get();
        }
        if(tmp->right!= nullptr)
        {
            tmp->left = std::move(root->left);
            root = std::move(root->right);
        }
        else
        {
            tmp->left = std::move(root->left);
            tmp->right = std::move(root->right);
            root = std::move(parent->left);
        }
    }
    else{
        parent = tmp;
        tmp = tmp->right.get();
        while (tmp->data!=data_to_delete and tmp!= nullptr)
        {
            if(data_to_delete<tmp->data)
            {
                parent = tmp;
                tmp = tmp->left.get();
            }
            else if (data_to_delete>tmp->data)
            {
                parent = tmp;
                tmp = tmp->right.get();
            }
        }
        if(tmp== nullptr)
        {
            return;
        }

        if(tmp->right== nullptr && tmp->left== nullptr)
        {
            if(parent->data>data_to_delete)
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
        }
        else if (tmp->right== nullptr)
        {
            if(parent->data>data_to_delete)
            {
                parent->left = std::move(tmp->left);
            }
            else
            {
                parent->right = std::move(tmp->left);
            }
        }
        else if (tmp->left== nullptr)
        {
            if(parent->data>data_to_delete)
            {
                parent->left = std::move(tmp->right);
            }
            else
            {
                parent->right = std::move(tmp->right);
            }
        }

        else{
            Node<T> * new_tmp = tmp;
            Node<T> * new_par = parent;
            new_tmp = tmp->right.get();
            new_par = tmp;
            while(new_tmp->left!= nullptr)
            {
                new_par = new_tmp;
                new_tmp = new_tmp->left.get();
            }

            if(new_tmp->right!= nullptr)
            {
                new_tmp->left = std::move(tmp->left);
                if(parent->data>data_to_delete)
                {
                    parent->left = std::move(tmp->right);
                }
                else {
                    parent->right = std::move(tmp->right);
                }
            }
            else
            {
                new_tmp->right = std::move(tmp->right);
                new_tmp->left = std::move(tmp->left);
                if(parent->data>data_to_delete)
                {
                    parent->left = std::move(new_par->left);
                }
                else {
                    parent->right = std::move(new_par->left);
                }
            }
        }
    }

}

template<typename T>
void BT::BinaryTree<T>::inorder_print(Node<T> * node,const std::string & direction) {
    if (node == nullptr)
    {
        return;
    }
    inorder_print(node->left.get(), "left");
    std::cout <<direction+": "<< node->data << ";   ";
    inorder_print(node->right.get(), "right");
}

template<typename T>
void BT::BinaryTree<T>::reverse_inorder_print(BT::Node<T> *node, const std::string & direction) {
    if (node == nullptr)
    {
        return;
    }
    reverse_inorder_print(node->right.get(), "right");
    std::cout <<direction+": "<< node->data << ";   ";
    reverse_inorder_print(node->left.get(), "left");
}


template<typename T>
BT::Node<T> * BT::BinaryTree<T>::search(T key) {
    Node<T> * node = root.get();
    while (node!= nullptr)
    {
        if(node->data==key)
        {
            return node;
        }
        else if(node->data<key)
        {
            node = node->right.get();
        }
        else if(node->data>key)
        {
            node = node->left.get();
        }
    }
    return nullptr;
}

template<typename T>
void BT::BinaryTree<T>::print(const BT::Node<T> *node, const std::string &prefix, bool isLeft) {
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->data << std::endl;

        // enter the next tree level - left and right branch
        print( node->left.get(),prefix + (isLeft ? "│   " : "    "),  true);
        print( node->right.get(),prefix + (isLeft ? "│   " : "    "),  false);
    }
}

template<typename T>
BT::Node<T> *BT::BinaryTree<T>::successor(T key) {

    Node<T> * current = search(key)->right.get();
    if(current== nullptr)
        return nullptr;
    while(current->left!= nullptr){
        current = current->left.get();
    }
    return current;
}

template<typename T>
BT::Node<T> *BT::BinaryTree<T>::predecessor(T key) {
    if(key==root->data && root.get()->left== nullptr)
        return nullptr;
    Node<T> * current = root.get();
    Node<T> * max = root.get();
    while(current!= nullptr and current->data!=key)
    {
        if(max->data<current->data && current->data<key)
            max = current;
        if(current->data>key)
        {
            current = current->left.get();
        }
        else{
            current = current->right.get();
        }
    }
    current = current->left.get();
    if(current== nullptr)
        return max;
    while(current->left!= nullptr){
        current = current->left.get();
    }
    return current;
}

template<typename T>
int BT::BinaryTree<T>::height(Node<T> * node) {
    if (node == nullptr)
        return 0;
    else {
        /* compute the height of each subtree */
        int lheight = height(node->left.get());
        int rheight = height(node->right.get());

        /* use the larger one */
        if (lheight > rheight) {
            return (lheight + 1);
        }
        else {
            return (rheight + 1);
        }
    }
}

template<typename T>
void BT::BinaryTree<T>::print_by_layer(Node<T>* root_)
{
    int h = height(root_);
    int i;
    for (i = 1; i <= h; i++)
        print_current_level(root_, i);
}


template<typename T>
void BT::BinaryTree<T>::print_current_level(Node<T>* root_, int level)
{
    if (root_ == NULL)
        return;
    if (level == 1)
        std::cout << root_->data << " ";
    else if (level > 1) {
        print_current_level(root_->left.get(), level - 1);
        print_current_level(root_->right.get(), level - 1);
    }
}

template<typename T>
void BT::BinaryTree<T>::pretty_print_by_layer(Node<T>* root_)
{
    // create an empty map to store nodes between given levels
    std::unordered_map<int, std::vector<T>> map;

    // traverse the tree and insert its nodes into the map
    // corresponding to their level
    preorder(root_, 1, map);

    // iterate through the map and print all nodes between given levels
    for (int i = 1; map[i].size() > 0; i++)
    {
        for (int j: map[i]) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
void BT::BinaryTree<T>::preorder(BT::Node<T> *root_, int level, std::unordered_map<int, std::vector<T>> &map) {
    if (root_ == nullptr) {
        return;
    }

    // insert the current node and its level into the map
    map[level].push_back(root_->data);

    // recur for the left and right subtree by increasing the level by 1
    preorder(root_->left.get(), level + 1, map);
    preorder(root_->right.get(), level + 1, map);
}


template<typename T>
BT::Node<T>::Node(T data) {
    this->data = data;
}