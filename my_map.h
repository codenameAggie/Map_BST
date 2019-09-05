#ifndef MY_MAP_H
#define MY_MAP_H

#include "BTree.h"
#include "key_value.h"
#include <iterator> 
#include <vector>
using namespace std;

template <typename T, typename E>
struct my_map
{
	///////////////////////////////////////////////////////////////////////////////// 
    class map_iter : public iterator<input_iterator_tag, key_value<T,E>>
    {   
    private:
        vector<Node<key_value<T,E>>*> prev_nodes;

    public:
        Node<key_value<T,E>>* node;

        map_iter(Node<key_value<T,E>>* x) :node(x){}
        map_iter(const map_iter& iter) : node(iter.node){}
        map_iter& operator++()
        {
            //FINISH THIS FUNCTION
            //should go to the next node in the inorder traversal
			prev_nodes.push_back(node);
			node = find_next(node);
            return *this;
        }
        map_iter operator++(int) {map_iter tmp(*this); operator++(); return tmp;} //Done //creates a temp map_iter using the object it is in and calls ++ and returns the temp obj;
        bool operator==(const map_iter& rhs) const {return node == rhs.node;}  /////Done
        bool operator!=(const map_iter& rhs) const {return node != rhs.node;} //////Done
        key_value<T,E>& operator*() {return node->value;}					////////Done
		
		Node<key_value<T, E>>* GET_small(Node<key_value<T, E>>* curr) { return find_smallest_child(curr); }


    private:
        void go_to_begining();
        Node<key_value<T,E>>* find_next(Node<key_value<T,E>>* curr); //////////////////// outside class  ///////////Needs work
        Node<key_value<T,E>>* find_smallest_child(Node<key_value<T,E>>* curr); ////////// outside class  ///////////Needs work
        bool is_node_in_prev_nodes(Node<key_value<T,E>>* curr);            ////////////// outside class  ///////////Needs work
    }; ////////////////////////////////////////////////////////////////////////////////// end of iterator ///////////Needs work


    BTree<key_value<T, E>> container;

    my_map() : container() { }
    my_map(const my_map<T, E>& other);          
    my_map<T, E>& operator=( const my_map<T, E>& other );

    E& operator[](T search_key);

    map_iter begin() //////This traverses the tree to the leftmost child;
    {
        //FINISH THIS FUNCTION
        //should return the first node in the inorder traversal
		map_iter temp(this->container.get_root());
		return temp.GET_small(this->container.get_root());
    }

    map_iter end()
    {
        return map_iter(NULL);
    }
}; //end of the map struct

template <typename T, typename E>
ostream& operator<<(ostream& out,  my_map<T, E>& map)
{
    out <<endl << "The map: " <<endl;
     out << map.container;
    out << "Done with printing" <<endl;
    return out;
}

template <typename T, typename E>
my_map<T,E>::my_map(const my_map<T, E>& other)
    :   container(other.container)   
{}

template <typename T, typename E>
my_map<T, E>& my_map<T,E>::operator=( const my_map<T, E>& other )
{
     BTree<key_value<T, E>> container(other.container);
     return *this;
}



template <typename T, typename E>
E& my_map<T,E>::operator[](T search_key)
{
    //FINISH THIS FUNCTION
    //this should search for search_key
    //if it doesent find it, then insert a new key_value into the tree

	//This if statement searches for the item and if it wasnt found
	//it will insert a new node with the search key and the default element
	//and it returns the base case of the data element

	key_value<T, E>* empty_node = new key_value<T, E>(search_key, E());
	E* temp = new E();
	if (this->container.search(*empty_node) == nullptr) {
		temp = &(this->container.insert(*empty_node)->value.value);
		return *temp;
	}
	else {
		temp = &(this->container.search(*empty_node)->value.value);
			return *temp;
	}
	
	//return temp;
	//return search_Node.value;
}

template <typename T, typename E>
Node<key_value<T,E>>* my_map<T,E>::map_iter::find_next(Node<key_value<T,E>>* curr)
{
    //this should find the next node in the inorder traversal
	Node<key_value<T, E>>* temp;
	bool right_visited = is_node_in_prev_nodes(curr->right);
	
	//if node == null

	if (node == NULL)
		return NULL;

	//bool parent_and_left_visited = is_node_in_prev_nodes(curr->right) && is_node_in_prev_nodes(curr->parent->left);
	
	if (curr->right != nullptr && !right_visited) { //means that parent is visited
		return find_smallest_child(node->right);
	}
	else if (is_node_in_prev_nodes(curr->parent)) { //means that parent is visited
		return find_next(curr->parent);
	}
	else {
		return curr->parent;
	}


}

template <typename T, typename E>
bool my_map<T,E>::map_iter::is_node_in_prev_nodes(Node<key_value<T,E>>* curr)
{
    //this should check if a node has already been visited
    //you can do this with the prev nodes vector, or find a faster way
	for (int i = 0; i < prev_nodes.size(); i++) {
		if (curr == prev_nodes.at(i)) {
			return true;
		}
	}
	return false;
}

template <typename T, typename E>
void my_map<T,E>::map_iter::go_to_begining()
{
    //this will go to the beginning of the inorder traversal
	//leftmost child:
	node = find_smallest_child(container.get_root());
}

template <typename T, typename E> //****************************** Done
Node<key_value<T,E>>* my_map<T,E>::map_iter::find_smallest_child(Node<key_value<T,E>>* curr)
{
    //this function finds the smallest child of curr
	 //if you are null then the parent is what needs to be returned
	//if its not null then call func on the left node
	//Node<key_value<T, E>>* temp = curr;
	if (curr->left == nullptr) {
		return curr;
	}
	else {
		return find_smallest_child(curr->left);
	}
}

#endif