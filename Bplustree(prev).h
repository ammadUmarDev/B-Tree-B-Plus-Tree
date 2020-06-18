

#include "LList.h"


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

const int max_childern = 4; //order of 5
const int min_childern = 2; //ceiling of 5/2

template <class T>
struct btree_node
{
	int number_of_childern;
	T node_keys[max_childern + 1];
	btree_node *child[max_childern + 1];
};

template <class T>
class btree
{
private:
	btree_node<dataID> *root;
	VECTOR<string> LinkLofData;
public:


	btree()
	{
		root = NULL;

	}


	void insert(dataID insObj)
	{
		insert_int_ID(insObj.ID);
		LinkLofData.createnode_with_node(insObj.address_node);
	}




	btree_node<dataID> getRoot()
	{}



	void insert_int_ID(int val)
	{
		int i;
		btree_node<dataID> *c, *n;
		int flag;
		flag = Set_Value_to_Node(val, root, &i, &c);
		if (flag)
		{
			n = new btree_node<dataID>;
			n->number_of_childern = 1;
			n->node_keys[1].ID = i;
			n->child[0] = root;
			n->child[1] = c;
			root = n;
		}
	}
	int Set_Value_to_Node(int val, btree_node<dataID> *n, int *p, btree_node<dataID> **c)
	{
		int k;
		if (n == NULL)
		{
			*p = val;
			*c = NULL;
			return 1;
		}
		else
		{
			if (searchnode(val, n, &k))
				cout << endl << "Key value already exists." << endl;
			if (Set_Value_to_Node(val, n->child[k], p, c))
			{
				if (n->number_of_childern < max_childern)
				{
					fillnode(*p, *c, n, k);
					return 0;
				}
				else
				{
					split(*p, *c, n, k, p, c);
					return 1;
				}
			}
			return 0;
		}
	}
	void fillnode(int val, btree_node<dataID> *c, btree_node<dataID> *n, int k)
	{
		int i;
		for (i = n->number_of_childern; i > k; i--)
		{

			n->node_keys[i + 1].ID = n->node_keys[i].ID;
			n->child[i + 1] = n->child[i];
		}
		n->node_keys[k + 1].ID = val;

		n->child[k + 1] = c;
		n->number_of_childern++;
	}
	void split(int val, btree_node<dataID> *c, btree_node<dataID> *n, int k, int *y, btree_node<dataID> **newnode)
	{
		int i, mid;

		if (k <= min_childern)
			mid = min_childern;
		else
			mid = min_childern + 1;

		*newnode = new btree_node<dataID>;

		for (i = mid + 1; i <= max_childern; i++)
		{
			(*newnode)->node_keys[i - mid].ID = n->node_keys[i].ID;

			(*newnode)->child[i - mid] = n->child[i];
		}

		(*newnode)->number_of_childern = max_childern - mid;
		n->number_of_childern = mid;

		if (k <= min_childern)
			fillnode(val, c, n, k);
		else
			fillnode(val, c, *newnode, k - mid);

		*y = n->node_keys[n->number_of_childern].ID;
		(*newnode)->child[0] = n->child[n->number_of_childern];
		n->number_of_childern--;
	}

	btree_node<dataID> * search(int val, btree_node<dataID> *root, int *pos)
	{
		if (root == NULL)
			return NULL;
		else
		{
			if (searchnode(val, root, pos))
				return root;
			else
				return search(val, root->child[*pos], pos);
		}
	}

	int searchnode(int val, btree_node<dataID> *n, int *pos)
	{
		if (val < n->node_keys[1].ID)
		{
			*pos = 0;
			return 0;
		}
		else
		{
			*pos = n->number_of_childern;
			while ((val < n->node_keys[*pos].ID) && *pos > 1)
				(*pos)--;
			if (val == n->node_keys[*pos].ID)
				return 1;
			else
				return 0;
		}
	}

	void display_tree()
	{
		display(root);
	}
	void display(btree_node<dataID> *root)
	{
		if (root != NULL)
		{
			int i = 0;
			for (i = 0; i < root->number_of_childern; i++)
			{
				display(root->child[i]);

				cout << root->node_keys[i + 1].ID << " ";
			}
			display(root->child[i]);
		}
	}


	~btree()
	{

	}

};


/*
void main()
{

btree<int> b;
int arr[] = { 27, 42, 22, 47, 32, 2, 51, 40, 13 };
int sz = sizeof(arr) / sizeof(int);
for (int i = 0; i < sz; i++)
{
string addnode = "haha";
dataID obj(arr[i], addnode);

}

cout << "B-tree of order 5:" << endl;
b.display_tree();

cout << endl;
b.display_tree();
}

*/