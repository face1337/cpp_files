#include <iostream>
using namespace std;

struct drzewoBST
{
	drzewoBST* up;
	drzewoBST* left;
	drzewoBST* right;
	int val;
};

void AddBstNode(drzewoBST*& root, int x); //Dodaj do drzewa

void DeleteLeaves(drzewoBST*& root); // usuñ liœcie które nie maj¹ dzieci

void inorder(drzewoBST* root); // wyœwietlanie drzewa  w inorder

drzewoBST* search(drzewoBST* root, int x); // znajdŸ adres danej wartosci i go zwroc lub null

drzewoBST* findMax(drzewoBST* root);

drzewoBST* findMin(drzewoBST* root);

//drzewoBST* findMin_Max(drzewoBST* root) ; // - do poprawki

void DelEvenLeaves(drzewoBST*& root); // usuwanie liœci których wartoœci s¹ parzyste


void delMax(drzewoBST*& root);


void delMin(drzewoBST*& root);


void delMax_and_Min(drzewoBST*& root); // usuwanie max oraz minimum


void delLeftsubtree(drzewoBST*& root); // usuwanie lewego poddrzewa


int main()
{
	drzewoBST *root = NULL;

	AddBstNode(root, 13);
	AddBstNode(root, 35);
//	AddBstNode(root, 3);
	AddBstNode(root, 2);
	AddBstNode(root, 0);
	AddBstNode(root, 10);
	AddBstNode(root, 20);
	AddBstNode(root, -3);
	AddBstNode(root, 1);
	AddBstNode(root, 7);
	AddBstNode(root, 14);
	AddBstNode(root, 15);
	AddBstNode(root, -7);
	AddBstNode(root, 50);
	AddBstNode(root, 66);




	inorder(root);

	//DeleteLeaves(root);
	cout << endl;
	//DelEvenLeaves(root);
	//delMax_and_Min(root);
	//delMin(root);
	delLeftsubtree(root);
	inorder(root);
	cout << endl;
	//findMax(root);
	//cout << search(root, 12);
	//findMin(root);


	return 0;
}

void AddBstNode(drzewoBST*& root, int x)
{
	if (root == NULL)
	{
		drzewoBST* w = new drzewoBST;
		w->left = NULL;
		w->right = NULL;
		w->val = x;
		root = w;
	}
	else
	{
		if (x >= root->val)
		{
			AddBstNode(root->right, x);
		}
		else
			AddBstNode(root->left, x);
	}
}

void DeleteLeaves(drzewoBST*& root)
{
	if (root->right == NULL && root->left == NULL)
	{
		delete root;
		root = NULL;
	}
	else
	{
		if (root->left)
			DeleteLeaves(root->left);
		if (root->right)
			DeleteLeaves(root->right);
	}
}

void inorder(drzewoBST* root)
{
	if (root)
	{
		inorder(root->left);
		cout << root->val << " ";
		inorder(root->right);
	}
}

drzewoBST* search(drzewoBST* root, int x)
{
	drzewoBST* p = root;
	if (p)
	{
		if (p->val == x)
		{
			return p;
		}

		else
		{
			if (x > p->val)
				search(p->right, x);
			else
			{
				search(p->left, x);
			}
		}

	}
	else
		return NULL;
}

drzewoBST* findMax(drzewoBST* root)
{
	drzewoBST* p = root;
	drzewoBST* max;
	//max = p;
	if (p)
	{
		if (p->right == NULL)
		{
			max = p;
			cout << "Max = " << max->val << endl;
			return max;
		}

		else
			findMax(p->right);
	}


}

drzewoBST* findMin(drzewoBST* root)
{
	drzewoBST* p = root;
	drzewoBST* min;
	if (p)
	{
		if (p->left == NULL)
		{
			min = p;
			cout << "Min = " << min->val << endl;
			return min;
		}
		else
			findMin(p->left);
	}
}

void DelEvenLeaves(drzewoBST*& root)
{
	if (root)
	{
		if (root->val % 2 == 0)
		{
			delete root;
			root = NULL;
		}
		else
		{
			if (root->left)
			{
				DelEvenLeaves(root->left);
			}
			if (root->right)
			{
				DelEvenLeaves(root->right);
			}
		}
	}
}

void delMax(drzewoBST*& root)
{
	if (root)
	{
		if (root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else
		{
			delMax(root->right);
		}
	}
}

void delMin(drzewoBST*& root)
{
	if (root)
	{
		if (root->left == NULL)
		{
			delete root;
			root = NULL;
		}
		else
		{
			delMin(root->left);
		}
	}
}

void delLeftsubtree(drzewoBST*& root)
{
	drzewoBST* p = root;
	if (p)
	{
		if (p->left)
		{
			delete p->left;
			p->left = NULL;
		}

	}
}

void delMax_and_Min(drzewoBST*& root) 
{
	if (root)
	{
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else
		{
			delMax_and_Min(root->left); // delete MIN;
			delMax_and_Min(root->right); // delete MAX;
		}
	}
}

//drzewoBST* findMin_Max(drzewoBST* root)  // - do poprawki
//{
//	drzewoBST* min;
//	drzewoBST* max;
//	if (root)
//	{
//		if (root->left == NULL)
//		{
//			min = root;
//			
//			
//			cout << "Min = " << min->val << endl;
//				
//
//			return min;
//
//		}
//		else if (root->right == NULL)
//		{
//			max = root;
//			cout << "Max = " << max->val << endl;
//			return max;
//		}
//		else
//		{
//			findMin_Max(root->left); // find min;
//			findMin_Max(root->right);// find max;
//		}
//
//	}
//}