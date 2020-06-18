#include "LList.h"
#include "LLdoubleV.h"



//--------------------------------------------------------------------------------------------

class dataID
{
public:
	int ID;
	VectorNode<string>* address_node;

	dataID(int pID, string pST)
	{
		address_node = new VectorNode<string>;
		address_node->data = pST;
		address_node->next = NULL;

		ID = pID;
	}

	dataID()
	{
		address_node = new VectorNode<string>;
		address_node->data = "icry";
		address_node->next = NULL;
	}




};

//--------------------------------------------------------------------------------------------


// A BpTree node 
template <class T>
class BpTreeNode
{
	T *arr_keys;             // An array of keys 

	int min_degree;            // Minimum degree (defines the range for number of keys) 

	BpTreeNode **arr_childern; // An array of child pointers 

	int num_child;             // Current number of keys 

	bool isleaf;               // Is true when node is leaf. Otherwise false 

public:


	BpTreeNode(int t1, bool leaf1)
	{

		min_degree = t1;
		isleaf = leaf1;


		arr_keys = new T[2 * min_degree - 1];
		arr_childern = new BpTreeNode *[2 * min_degree];


		num_child = 0;
	}

	
	BpTreeNode<dataID>* search(int k)
	{
		// Find the first key greater than or equal to k 
		int j = 0;
		while (j < num_child && k > arr_keys[j].ID)
			j++;

		// If the found key is equal to k, return this node 
		if (arr_keys[j].ID == k)
			return this;

		// If key is not found here and this is a leaf node 
		if (isleaf == true)
			return NULL;

		// Go to the appropriate child 
		return arr_childern[j]->search(k);
	}

	void insertNonFull(int k)
	{
		// Initialize index as index of rightmost element 
		int i = num_child - 1;
		int z = i + 1;
		// If this is a leaf node 
		if (isleaf == true)
		{
			// The following loop does two things 
			// a) Finds the location of new key to be inserted 
			// b) Moves all greater keys to one place ahead 
			while (i >= 0 && arr_keys[i].ID > k)
			{
				
				arr_keys[z].ID = arr_keys[i].ID;
				i--;
			}

			// Insert the new key at found location 
			arr_keys[z].ID = k;
			num_child = num_child + 1;
		}
		else // If this node is not leaf 
		{
			// Find the child which is going to have the new key 
			while (i >= 0 && arr_keys[i].ID > k)
				i--;

			// See if the found child is full 
			if (arr_childern[z]->num_child == 2 * min_degree - 1)
			{
				// If the child is full, then split it 
				splitChild(z, arr_childern[z]);

				// After split, the middle key of C[i] goes up and 
				// C[i] is splitted into two.  See which of the two 
				// is going to have the new key 
				if (arr_keys[z].ID < k)
					i++;
			}
			arr_childern[z]->insertNonFull(k);
		}
	}


	void splitChild(int i, BpTreeNode *y)
	{
		// Create a new node which is going to store (t-1) keys 
		// of y 
		BpTreeNode *z = new BpTreeNode(y->min_degree, y->isleaf);
		z->num_child = min_degree - 1;

		// Copy the last (t-1) keys of y to z 
		for (int j = 0; j < min_degree - 1; j++)
			z->arr_keys[j].ID = y->arr_keys[j + min_degree].ID;

		// Copy the last t children of y to z 
		if (y->isleaf == false)
		{
			for (int j = 0; j < min_degree; j++)
				z->arr_childern[j] = y->arr_childern[j + min_degree];
		}

		// Reduce the number of keys in y 
		y->num_child = min_degree - 1;

		// Since this node is going to have a new child, 
		// create space of new child 
		for (int j = num_child; j >= i + 1; j--)
			arr_childern[j + 1] = arr_childern[j];

		// Link the new child to this node 
		arr_childern[i + 1] = z;

		// A key of y will move to this node. Find location of 
		// new key and move all greater keys one space ahead 
		for (int j = num_child - 1; j >= i; j--)
			arr_keys[j + 1].ID = arr_keys[j].ID;

		// Copy the middle key of y to this node 
		arr_keys[i].ID = y->arr_keys[min_degree - 1].ID;

		// Increment count of keys in this node 
		num_child = num_child + 1;
	}



	friend class BpTree;
};


//--------------------------------------------------------------------------------------------



// A BTree 
class BpTree
{
	BpTreeNode<dataID> *root; // Pointer to root node 
	int min_degree;  // Minimum degree 
	VECTOR<string> LinkLofData; //link list of files

public:

	BpTree(int para_degree)
	{

		min_degree = para_degree;
		root = NULL;
	}

	
	bool isEmpty()
	{
		if (root == NULL)
			return true;
		else
			return false;
	}

	BpTreeNode<dataID>* searchsFile(int k) //search for a value K and returns address of node file
	{
		BpTreeNode<dataID>* ret_temp;
		ret_temp= root->search(k);
		
		return ret_temp;
		

	}

	void insert(dataID kk)  //inserts dataID
	{
		insert_ID(kk.ID);
		LinkLofData.createnode_with_node(kk.address_node);
	}

	void insert_ID(int k)
	{
		// If tree is empty 
		if (isEmpty())
		{
			// Allocate memory for root 
			root = new BpTreeNode<dataID>(min_degree, true);
			root->arr_keys[0].ID = k;  // Insert key 
			root->num_child = 1;  // Update number of keys in root 
		}
		else // If tree is not empty 
		{
			// If root is full, then tree grows in height 
			if (root->num_child == 2 * min_degree - 1)
			{
				// Allocate memory for new root 
				BpTreeNode<dataID> *s = new BpTreeNode<dataID>(min_degree, false);

				// Make old root as child of new root 
				s->arr_childern[0] = root;

				// Split the old root and move 1 key to the new root 
				s->splitChild(0, root);

				// New root has two children now.  Decide which of the 
				// two children is going to have new key 
				int i = 0;
				if (s->arr_keys[0].ID < k)
					i++;
				s->arr_childern[i]->insertNonFull(k);

				// Change root 
				root = s;
			}
			else  // If root is not full, call insertNonFull for root 
				root->insertNonFull(k);
		}
	}


	//--------------------------------------------------------------------------------------------

	void TraverseKeys(BpTreeNode<dataID>* nodePtr, VECTOR<int> &outputK, int key)    //takes a node and saves its neighboring keys in outputK vector
	{
		//BpTreeNode<dataID>* tempPtr = nodePtr;
		if (nodePtr)
		{
			VECTOR<int> tempV;
			for (int i = 0; i < 2 * min_degree - 1; i++)
			{

				tempV.createnode(nodePtr->arr_keys[i].ID);
			}
			for (int i = 0; i < 2 * min_degree - 1; i++)
			{
				if (nodePtr->arr_keys[i].ID == key)
				{

					outputK = tempV;
					return;
				}
			}
			for (int i = 0; i < 2 * min_degree - 1; ++i)
			{
				TraverseKeys(nodePtr->arr_childern[i], outputK, key);
			}
		}
		return;
	}

	VECTOR< int> Findkeys_withkey(dataID key) //give id and it finds node with that id (one of array of keys) and returns a vector with all the keys that node has
	{

		VECTOR <int> returnKeys;
		TraverseKeys(root, returnKeys, key.ID);   //saves neighbors of given key in vector
		return returnKeys;

	}


	void findkeys_withnode(BpTreeNode<dataID>* nodeptr, VECTORVV<VECTOR<int>> &array_of_Vectors)  //here we 
	{

		// There are n keys and n+1 children, travers through n keys 
		// and first n children 
		int i;
		for (i = 0; i < nodeptr->num_child; i++)
		{
			// If this is not leaf, then before printing key[i], traverse the subtree rooted with child C[i]. 
			if (nodeptr->isleaf == false) 
			{
				findkeys_withnode(nodeptr->arr_childern[i], array_of_Vectors);
				cout << " " << nodeptr->arr_keys[i].ID;   //prints each key
				VECTOR<int> temp;
				temp = Findkeys_withkey(nodeptr->arr_keys[i]); //saves keys neighbor of i key
				array_of_Vectors.createnode(temp);
			}
		}

		// Print the subtree rooted with last child 
		if (nodeptr->isleaf == false)
			findkeys_withnode(nodeptr->arr_childern[i], array_of_Vectors);
	}

	VECTORVV<VECTOR<int>> findkeys_withnode()
	{
		VECTORVV<VECTOR<int>> array_of_Vectors;

		findkeys_withnode(root,array_of_Vectors);
		return array_of_Vectors;
	}

	//--------------------------------------------------------------------------------------------
	void ranga_tree(int lb, int ub)
	{
		if (!isEmpty())
		{
			range(root, lb, ub);
		}

	}


	void range(BpTreeNode<dataID>* nodeptr, int lowbound, int upbound)
	{
		// There are n keys and n+1 children, travers through n keys 
		// and first n children 
		int i;
		for (i = 0; i < nodeptr->num_child; i++)
		{
			// If this is not leaf, then before printing key[i], traverse the subtree rooted with child C[i]. 
			if (nodeptr->isleaf == false)
				range(nodeptr->arr_childern[i], lowbound, upbound);
			if (nodeptr->arr_keys[i].ID >= lowbound && nodeptr->arr_keys[i].ID <= upbound)
				cout << " " << nodeptr->arr_keys[i].ID;
		}

		// Print the subtree rooted with last child 
		if (nodeptr->isleaf == false)
			range(nodeptr->arr_childern[i], lowbound, upbound);
	}



	//--------------------------------------------------------------------------------------------
	void traverse_tree()
	{
		if (!isEmpty())
		{
			traverse(root);
		}

	}


	void traverse(BpTreeNode<dataID>* nodeptr)
	{
		// There are n keys and n+1 children, travers through n keys 
		// and first n children 
		int i;
		for (i = 0; i < nodeptr->num_child; i++)
		{
			// If this is not leaf, then before printing key[i], traverse the subtree rooted with child C[i]. 
			if (nodeptr->isleaf == false)
				traverse(nodeptr->arr_childern[i]);
			cout << " " << nodeptr->arr_keys[i].ID;
		}

		// Print the subtree rooted with last child 
		if (nodeptr->isleaf == false)
			traverse(nodeptr->arr_childern[i]);
	}


};

/*
int main()
{
	BpTree t(3); // A B-Tree with minium degree 3

	dataID a(4, "haha");
	dataID b(10, "haha");
	dataID c(20, "haha");
	dataID d(5, "haha");
	t.insert(a);
	t.insert(b);
	t.insert(c);
	t.insert(d);

	cout << "Traversal of the constucted tree is ";
	t.traverse();
	
	/*
	int k = 15;
	string str_add1;
	str_add1 = t.searchsFile(k);
	cout << str_add1 << endl;

	k = 10;
	str_add1 = t.searchsFile(k);
	cout << str_add1 << endl;
	
	return 0;
}

*/