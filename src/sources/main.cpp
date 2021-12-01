#include "bin_tree.hpp"
#include <random>

#include <iostream>
#include <fstream>


using namespace cv;

#define M 1000

#define  N 65535

int main(){

    std::random_device rd;
    std::mt19937 mersenne(rd());


    BT::BinaryTree<int> bt{};
    bt.insert(7);
    bt.insert(11);
    bt.insert(9);
    bt.insert(8);
    bt.insert(10);
    bt.insert(13);
    bt.insert(12);
    bt.insert(14);
    bt.insert(16);
    bt.insert(56);

    std::cout<<"Inorder: \n";
    bt.inorder_print(bt.root.get());
    std::cout<<std::endl;
    std::cout<<"Preorder: \n";
    bt.reverse_inorder_print(bt.root.get());
    std::cout<<std::endl;

    std::cout<<"Tree: \n";
    bt.print(bt.root.get());
    std::cout<<std::endl;
    bt.delete_(7);
    std::cout<<"Tree without 7: \n";
    bt.print(bt.root.get());
    std::cout<<"Tree without 13: \n";
    bt.delete_(13);
    bt.print(bt.root.get());

    std::cout<<"Successor of 9 is: "<<bt.successor(9)->data<<std::endl;
    std::cout<<"Predecessor of 56 is: "<<bt.predecessor(56)->data<<std::endl;

    std::cout<< "\nTree height: "<< bt.height(bt.root.get())<<std::endl;
    std::cout<< "\nPrinted tree by layers: \n";
    bt.print_by_layer(bt.root.get());

    std::cout<< "\n\nPretty printed tree by layers: \n";
    bt.pretty_print_by_layer(bt.root.get());

    std::vector<int> heights;
    std::vector<BT::BinaryTree<int>> trees;

    for(size_t  i = 0; i< M; i++)
    {
        trees.push_back(BT::BinaryTree<int>{});
        for(size_t j =0; j< N; j++){
            trees[i].insert(mersenne());
        }
    }

    for(size_t i = 0; i< M; i++)
    {
        heights.push_back(trees[i].height(trees[i].root.get()));
    }




    std::ofstream myfile ("data.txt");
    if (myfile.is_open())
    {
        for(auto i : heights)
        {
            myfile<<i<<",";
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
}