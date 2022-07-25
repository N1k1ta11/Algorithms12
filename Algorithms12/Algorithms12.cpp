#include <iostream>
using namespace std;

struct Tree
{
	int value;
	Tree* right;
	Tree* left;
};

Tree* insertTree(Tree* root, int n)
{
	Tree* newTree = new Tree;
	newTree->value = n;
	newTree->left = NULL;
	newTree->right = NULL;
	Tree* current = root;
	Tree* parent = root;
	if (root == NULL)
	{
		root = newTree;
	}
	else
	{
		while (current->value != n)
		{
			parent = current;
			if (current->value > n)
			{
				current = current->left;
				if (current == NULL)
				{
					parent->left = newTree;
					return root;
				}
			}
			else
			{
				current = current->right;
				if (current == NULL)
				{
					parent->right = newTree;
					return root;
				}
			}
		}
	}
	return root;
}

void printTree(Tree* root)
{
	if (root)
	{
		cout << root->value;
		if (root->left || root->right)
		{
			cout << "(";
			if (root->left)
			{
				printTree(root->left);
			}
			else
			{
				cout << "NULL";
			}
			cout << ",";
			if (root->right)
			{
				printTree(root->right);
			}
			else
			{
				cout << "NULL";
			}
			cout << ")";
		}
	}
}

void fillTree(int size, Tree* root)
{
	for (int i = 0; i < size; i++)
	{
		insertTree(root, rand() % 1000);
	}
}

int countNodes(Tree* node)
{
	if (node == NULL)
	{
		return 0;
	}
	int left = 0;
	int right = 0;
	if (node->left != NULL)
	{
		left = countNodes(node->left);
	}
	if (node->right != NULL)
	{
		right = countNodes(node->right);
	}
	if (left > right)
	{
		return 1 + left;
	}
	else
	{
		return 1 + right;
	}
}

bool isBalanceRoot(Tree* root)
{
	return abs(countNodes(root->left) - countNodes(root->right)) <= 1;
}

Tree* getSuccessor(Tree* node)
{
	Tree* current = node->right; // текущий
	Tree* parent = node;
	Tree* s = node;//наилучший на данный момент элемент

	while (current!=NULL)
	{
		parent = s;
		s = current;
		current = current->left;
	}

	if (s != node->right)
	{
		parent->left = s->right;
	}
	return s;
}

bool del(Tree* root, int value)
{
	Tree* current = root; //текущий 
	Tree* parent = root;//родительский
	bool isLeftChild = true;

	while (current->value != value)
	{
		parent = current;
		if (value < current->value)
		{
			current = current->left;
			isLeftChild = true;
		}
		else
		{
			current = current->right;
			isLeftChild = false;
		}
		if (current == NULL)
		{
			return false;
		}
	}

	if (current->left == NULL && current->right == NULL)
	{
		if (current == root)
		{
			root = NULL;
		}
		else if (isLeftChild)
		{
			parent->left = NULL;
		}
		else
		{
			parent->right = NULL;
		}
	}

	else if (current->right == NULL)
	{
		if (isLeftChild)
		{
			parent->left = current->left;
		}
		else
		{
			parent->right = current->left;
		}
	}

	else if (current->left == NULL)
	{
		if (isLeftChild)
		{
			parent->left = current->right;
		}
		else
		{
			parent->right = current->right;
		}
	}

	else
	{
		Tree* successor = getSuccessor(current);//самый подходящий узел
		if (current == root)
		{
			root = successor;
		}
		else if (isLeftChild)
		{
			parent->left = successor;
		}
		else
		{
			parent->right = successor;
		}
		successor->left = current->left;
	}
	return true;
}

void Task1()
{
	const int size = 10000;
	int balanced = 0;
	srand(time(0));
	for (int i = 0; i < 50; i++)
	{
		Tree* root = NULL;
		root = insertTree(root, rand() % 1000);
		for (int j = 0; j < size; j++)
		{
			insertTree(root, rand() % 1000);
		}
		if (isBalanceRoot(root))
		{
			balanced++;
		}
	}
	cout << balanced * 0.5<<"%\n";
}

//Бинарный поиск в дереве 
bool binSerch(Tree* root, int value)
{
	if (root == NULL)
	{
		return false;
	}
	if (root->value == value)
	{
		return true;
	}
	Tree* current = root;
	while (current->value != value)
	{
		if (value < current->value)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
		if (current == NULL)
		{
			return false;
		}
	}
}

bool recBinSerch(Tree* root, int value)
{
	if (root == NULL)
	{
		return false;
	}
	if (root->value == value)
	{
		return true;
	}
	bool res;
	Tree* current = root;

	if (current->value > value)
	{
		return recBinSerch(current->left, value);
	}
	else
	{
		return recBinSerch(current->right, value);
	}

}

int main()
{

	Task1();
	Tree* tr = NULL;
	tr = insertTree(tr, 10);
	insertTree(tr, 5);
	insertTree(tr, 13);
	insertTree(tr, 12);
	insertTree(tr, 15);
	insertTree(tr, 11);
	insertTree(tr, 14);
	insertTree(tr, 16);
	del(tr, 16);
	printTree(tr);
	cout << endl;
	//Task2
	cout << boolalpha << recBinSerch(tr, 120) << endl;
	cout << boolalpha << recBinSerch(tr, 100)<<endl;
}