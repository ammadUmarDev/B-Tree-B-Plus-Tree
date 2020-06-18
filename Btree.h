


	// SP.cpp : Defines the entry point for the console application.
	//

#include "LList.h"
#include "stdafx.h"
#include <stdlib.h>

	const int max_childern = 4; //order of 5
const int min_childern = 2; //ceiling of 5/2

struct btree_node
{
	int number_of_childern;
	int node_keys[max_childern + 1];
	btree_node *child[max_childern + 1];
};
class btree
{
private:
	btree_node *root;
public:


	btree()
	{
		root = NULL;
	}

	void insert_int_ID(int val)
	{
		int i;
		btree_node *c, *n;
		int flag;
		flag = Set_Value_to_Node(val, root, &i, &c);
		if (flag)
		{
			n = new btree_node;
			n->number_of_childern = 1;
			n->node_keys[1] = i;
			n->child[0] = root;
			n->child[1] = c;
			root = n;
		}
	}
	int Set_Value_to_Node(int val, btree_node *n, int *p, btree_node **c)
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
	void fillnode(int val, btree_node *c, btree_node *n, int k)
	{
		int i;
		for (i = n->number_of_childern; i > k; i--)
		{
			n->node_keys[i + 1] = n->node_keys[i];
			n->child[i + 1] = n->child[i];
		}
		n->node_keys[k + 1] = val;
		n->child[k + 1] = c;
		n->number_of_childern++;
	}
	void split(int val, btree_node *c, btree_node *n, int k, int *y, btree_node **newnode)
	{
		int i, mid;

		if (k <= min_childern)
			mid = min_childern;
		else
			mid = min_childern + 1;

		*newnode = new btree_node;

		for (i = mid + 1; i <= max_childern; i++)
		{
			(*newnode)->node_keys[i - mid] = n->node_keys[i];
			(*newnode)->child[i - mid] = n->child[i];
		}

		(*newnode)->number_of_childern = max_childern - mid;
		n->number_of_childern = mid;

		if (k <= min_childern)
			fillnode(val, c, n, k);
		else
			fillnode(val, c, *newnode, k - mid);

		*y = n->node_keys[n->number_of_childern];
		(*newnode)->child[0] = n->child[n->number_of_childern];
		n->number_of_childern--;
	}

	btree_node * search(int val, btree_node *root, int *pos)
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
	int searchnode(int val, btree_node *n, int *pos)
	{
		if (val < n->node_keys[1])
		{
			*pos = 0;
			return 0;
		}
		else
		{
			*pos = n->number_of_childern;
			while ((val < n->node_keys[*pos]) && *pos > 1)
				(*pos)--;
			if (val == n->node_keys[*pos])
				return 1;
			else
				return 0;
		}
	}

	void display_tree()
	{
		display(root);
	}
	void display(btree_node *root)
	{
		if (root != NULL)
		{
			int i = 0;
			for (i = 0; i < root->number_of_childern; i++)
			{
				display(root->child[i]);
				cout << root->node_keys[i + 1] << " ";
			}
			display(root->child[i]);
		}
		cout << "endl";
	}


	~btree()
	{

	}

};
/*

void main()
{
	btree b;
	int arr[] = { 27, 42, 22, 47, 32, 2, 51, 40, 13 };
	int sz = sizeof(arr) / sizeof(int);
	for (int i = 0; i < sz; i++)
		b.insert_int_ID(arr[i]);
	cout << "B-tree of order 5:" << endl;
	b.display_tree();

	b.display_tree();
}

*/