#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;

		bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));

		cout << "Erasing b" << endl;
    bt.remove('b');

}