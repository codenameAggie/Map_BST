#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
#include<fstream>
#include<string>
#include<sstream>


using namespace std;

enum color {red, black};

template <typename T>
struct Node
{
	T value;
	Node<T>* left;
	Node<T>* right;
    Node<T>* parent;

    int search_time;
    color node_color; //don't need to worry about this for the regular BTree

    Node(T val = T(), Node<T>* l = NULL, Node<T>* r = NULL, Node<T>* p = NULL, color col = color::red)
		: value(val), left(l), right(r), parent(p), search_time(0), node_color(col) {}

	Node(const Node<T>* other)
	{
		value = other.value;
		node_color = other.node_color;
		search_time = other.search_time;
	}

	bool is_leaf(){return (left == 0 && right == 0);}
};

template <typename T>
struct BTree
{
protected:

	
public:
	Node<T>* root;
	int size;

	//size helper////////////////////////////////////////////////
	int get_size() { 
		//size = 0;
		return size_helper(root);
	}
	int size_helper(Node<T>* temp) {
		if (temp == NULL) {
			return 0;
		}
		else {
			return 1 + size_helper(temp->left) + size_helper(temp->right);
		}
	}
	/////////////////////////////////////////////////////////////////
    BTree() : root(NULL),size(0){}
	BTree(const BTree<T>& other);				//done
	BTree<T>& operator=(const BTree<T>& other); //done
	Node<T>* get_root(){return root;}			//done
	const Node<T>* get_root() const {return root;} //done
	
	virtual Node<T>* insert(T obj);//	  done
	Node<T>* search(T obj);//			  work on the search time
	void update_search_times();//			?
	float get_average_search_time();//		?
    ostream& inorder(ostream& out);//		?
    virtual ostream& print_level_by_level(ostream& out);// ?

private:
	void copy_helper(Node<T>*& copy_to, const Node<T>* copy_from); //keep the relative parent children
	virtual Node<T>* insert_helper(T obj, Node<T>* node); //		done
	Node<T>* search_helper(T obj, Node<T>* node);					//search time
	ostream& inorder_helper(ostream& out, Node<T>* node);			//?
	void update_search_times_helper(Node<T>* node, int depth);		//?
	float get_total_search_time(Node<T>* node);							//?
	virtual void pretty_print_node(ostream& out,Node<T>* node);		//?
};

template <typename T>
ostream& operator<<(ostream& out, BTree<T>& tree)
{
	tree.inorder(out);
	return out;
}

template <typename T>
ostream& operator<<(ostream& out, Node<T> node)
{
	return out << "( " << node.value << ", " << node.search_time << ", " << node.node_color << " )";
}

template <typename T>
void BTree<T>::pretty_print_node(ostream& out,Node<T>* node)
{
	out << node->value << "["<<node->search_time<<"] ";
}

template <typename T>
istream& operator>>(istream& in, BTree<T>& tree)
{
	int count = 0;
	vector<T> temp_values;
	string temp;
	while (!in.eof()) {
	getline(in, temp);
	int value;
	stringstream temp_SS(temp);
	temp_SS >> value;
	temp_values.push_back(value);
	count++;
	//cout << value << endl;
	tree.insert(value);
	//cout << "This is the value of the root" << tree.get_root()->value << endl;
	}
	//
	if (count < 16) {
		cout << endl << "Here is the inputs from the file: " << endl;
		for (int i = 0; i < temp_values.size(); i++) {
			cout << temp_values.at(i) <<" ";
		}
		cout << endl;
	}
	return in;

	/*string temp;
	while (!in.eof()) {
		getline(in, temp);
		int value;
		stringstream temp_SS(temp);
		temp_SS >> value;
		cout << value << endl;
		tree.insert(value);
		cout << "This is the value of the root" << tree.get_root()->value << endl;
	}
	return in;*/
}

template <typename T>
BTree<T>::BTree(const BTree<T>& other)
	: root(0)
{
	//size = other.get_size();
	if (other.get_root() == nullptr) {
		this->root = nullptr;
	}
	else {
		copy_helper(root, other.get_root());
	}

}

template <typename T>
BTree<T>& BTree<T>::operator=(const BTree<T>& other)
{
	/*
		complete this assignment operator
		make sure when copying nodes to copy
			the value
			the relative parent, and left and right children
			the node_color
				not important for this part but will be used later
	*/
	if (other.get_root() == nullptr) {
		return nullptr;
	}
	else {
		return copy_helper(this->get_root(), other->get_root());
	}
}

template <typename T>
void BTree<T>::copy_helper(Node<T>*& copy_to, const Node<T>* copy_from)// const
{
	if (copy_from == nullptr) {
		copy_to = nullptr;
	}
	else {
		
		insert(copy_from->value);

		///////////////////
		copy_helper(copy_to->left, copy_from->left);
		copy_helper(copy_to->right, copy_from->right);
	}
}


template <typename T>
Node<T>* BTree<T>::insert_helper(T obj, Node<T>* curr)
{ 
	if (curr == NULL) {
		size++;
		curr = new Node<T>(obj); //create new node
		//cout << "Value for the current node: " << curr->value <<endl;
		if (root == nullptr) {
		root = curr;
		root->search_time = 1;
		}
		//curr = new Node<T>(obj);

		return curr;
	}
	else if (obj < curr->value) {
		
		//curr->search_time++;
		if (curr->left == nullptr)
		{
			Node<T>* temp2 = new Node<T>(obj);
			temp2->parent = curr;
			curr->left = temp2;
			temp2->search_time = curr->search_time + 1;
			return temp2;
		}
		return insert_helper(obj, curr->left);
		
		//curr->left = insert_helper(obj, curr->left);
	}
	else if (obj > curr->value) {
		
		//curr->search_time++;
		if (curr->right == nullptr) {
			Node<T>* temp3 = new Node<T>(obj);
			temp3->parent = curr;
			curr->right = temp3;
			temp3->search_time = curr->search_time + 1;
			return temp3;
		}
		return insert_helper(obj, curr->right);
		
		//curr->right = insert_helper(obj, curr->right);
	}
	//return curr;
	//else { cerr << "Duplicate item " << endl; }
}

template <typename T>
Node<T>* BTree<T>::insert(T obj)
{
    /*
		insert a node into the tree
		first find where the node should go
		then modify pointers to connect your new node 
	*/
    return insert_helper(obj, root);
}

template <typename T>
Node<T>* BTree<T>::search_helper(T obj, Node<T>* node)
{
	while (node != NULL) {
		if (obj < node->value) return search_helper(obj, node->left);//node = node->left;
		else if (obj > node->value) return search_helper(obj, node->right);
		else return node;
	}
	//cerr << "Not found " << endl;
	return nullptr;
}

template <typename T>//done
Node<T>* BTree<T>::search(T obj)
{
	if (root == nullptr) {
		//cerr << "Empty tree" << endl; //this part was changed to return null
		//pointer instead of error for PA6
		return nullptr;
	}
	return search_helper(obj, root);;
}	
/////////////////////////////ADDing a new search function














template <typename T> //?
void BTree<T>::update_search_times_helper(Node<T>* node, int depth)
{

}

template <typename T> //?
void BTree<T>::update_search_times()
{
	if (this->get_root() == nullptr) {
		cerr << "Empty Tree" << endl;
	}
	else {

	}
}

template <typename T>
ostream& BTree<T>::inorder_helper(ostream& out, Node<T>* node)
{
	if (node != nullptr)
	{
		inorder_helper(out, node->left);
		out << *node <<endl;
		inorder_helper(out, node->right);
	}
    return out;
}

template <typename T>
ostream& BTree<T>::inorder(ostream& out)
{
	/*
		print your nodes in infix order
		if our tree looks like 

		4
		2 6
		1 3 5 7

		we should get

		1 2 3 4 5 6 7 
	*/
	
	out << "Value \t Search Cost" << endl;
	inorder_helper(out, root);
	return out;
}

template <typename T>
ostream& BTree<T>::print_level_by_level(ostream& out)
{
	/*
		print the tree using a BFS 
		output should look like this if we dont have a full tree

		4
		2 6
		1 X 5 7
		X X X X X X X 9

		it will be helpfull to do this part iterativly, 
		so do the BFS with the std stack data structure.

		it may also be helpfull to put the entire tree into a vector 
		(probably google this if you dont know how to do it)
	*/
	//int termi;
	vector<Node<T>*> vec1;
	vec1.push_back(root);
	vector<Node<T>*> vec2;
	Node<T> X;
	//X->value = 'X';
	while (true)
	{
		bool keep_going = false;
		for (int i = 0; i < vec1.size(); i++) {
			if (vec1.at(i) != NULL) {
				keep_going = true;
			}
		}
		if (!keep_going) {
			break;
		}

		//find all children in v1, add them to v2
		for (int i = 0; i < vec1.size(); i++) {
			if (vec1.at(i) == NULL) {
				vec2.push_back(NULL);
				vec2.push_back(NULL);
			}
			else {
				vec2.push_back(vec1.at(i)->left);
				vec2.push_back(vec1.at(i)->right);
			}
		}
		//print v1
		for (int i = 0; i < vec1.size(); i++) {
			if (vec1.at(i) == NULL) {
				out << "X ";
				//pretty_print_node(out, )
			}
			else {
				//out << vec1.at(i)->value << " ";
				pretty_print_node(out, vec1.at(i));
			}
		}
		out << endl;
		//put v2 in v1
		vec1 = vec2;
		//clear v2
		vec2.clear();

	}
    return out;
}
/*
	take two vectors and fill the first one with the first set of nodes and the second one with the children of the last nodes; print the first vector and make the second vector the first vector and the termination is when all are null; they contain nodes

*/

template <typename T>
float BTree<T>::get_total_search_time(Node<T>* node)
{
	if (node == nullptr) {
		return 0;
	}
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
}

template <typename T>
float BTree<T>::get_average_search_time()
{
    return (this->get_total_search_time(this->root)/this->get_size());
}

/*
Things to take care of:
1. copy assignment and constructor relative parent and children //dones
2. Figure out the search time //done
3. outputs
4. average time
5. print level by level
6. size///////is it a good function?


*/



#endif