#include "LList.h"

#include "Btreeplus.h"
#include "Btree.h"

int  ExtractID(string data)
{
int i = 0;
for (; data[i] != ','; i++)
{
/* Since in csv format, files are comma separated
* therefore we are shifting to the first comma
* as first column is for ID.
*/

}

string ext = data.substr(0, i);

return stoi(ext);
}

void WriteFile(string data, int num, BpTree *BPTREE)
{

ofstream myFile;
string fname = "Datafiles//Node";

std::stringstream stream;
stream << fname << num;
stream << ".txt";

string file = stream.str();

myFile.open(file.c_str());

myFile << data;
//cout << "\n";


int a = num;
stringstream ss;
ss << a;
string str = ss.str();


string addressofkey = "E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\node" + str + "txt";
dataID new_obj;
new_obj.ID = num;
new_obj.address_node->data = addressofkey;


BPTREE->insert(new_obj);

myFile.close();

}


void readFile(string path, BpTree *BPTREE)
{
cout << endl << "Read Initialted! of file:" << path << endl;
ifstream myFile;
string line;
int counter = 0;
myFile.open(path);

if (!myFile)
{
cout << "FILE NOT FOUND!" << endl;
exit(-1);
}

getline(myFile, line);
while (!myFile.eof())
{
getline(myFile, line);
counter++;
}

//cout << "COUNTER of 18 hazar : " << counter << endl;	// company main employment k baad :D

int i = 0;
myFile.clear();
myFile.seekg(0, ios::beg);
getline(myFile, line);

while (i < counter - 1)
{
getline(myFile, line);

int NodeNum = ExtractID(line);

//cout << NodeNum << endl;

WriteFile(line, NodeNum, BPTREE);
i++;
}

myFile.close();
cout << endl << "Read Successful! of file:" << path << endl;


}

char  createtree()
{
	int oop;
	int degree;
	cout << " Select the following options : \n Enter '1' to create btree \n Enter '2' to create b + tree.\n ";
	cin >> oop;

	if (oop == 1)
	{
		cout << "Enter degree of your  Btree " << endl;
		cin >> degree;
		//BpTree treeBP(degree);
		btree treeB;
		return 'b';
		//ok
		//IDHER B TREE BANAO NOT B PLUS


		/////HELLOO HELLOOO MERA PHONE OFF HO GAYA HAI NO CHARGING 
	}
	else
	{
		cout << "Enter degree of your B+tree " << endl;
		cin >> degree;
		BpTree treeBP(degree);
		return 's';
		
		//btree tree;
	}
}

void interface_tree()
{
	
	printf("-------------------------------------------\nGreeting User! \nWelcome to DSDB! \n-------------------------------------------\n");
	
	
	printf("Enter Degree of your Tree:\n ");
	int deg;
	cin >> deg;

	cout << "Select the following: "<<endl<<"1: To Create B+ tree"<<endl<<"2:To Create B tree: " << endl;
	int select_tree;
	cin >> select_tree;
	if (select_tree == 1)
	{
		BpTree treeBP(deg);
		cout << "B+TREE IS CREATED" << endl;

		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_1.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_2.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_3.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_4.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_5.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_6.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_7.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_8.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_9.csv", &treeBP);
		readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_10.csv", &treeBP);
		
		bool sara_trash = false;
		while (!sara_trash)
		{


			cout << "Select the following: " << endl << "1:To Point-Search" << endl << "2:To Range Search" << endl << "3:To Insert/Update" << endl << "4:To Traverse Your Desired Tree. \n" << endl;
			int select_f1;
			cin >> select_f1;
			if (select_f1 == 1)
			{
				cout << "POINT-SEARCH" << endl;
				cout << "Enter ID to be Searched : \n";
				int ID_ins;
				cin >> ID_ins;
				BpTreeNode<dataID>* temp;
				temp = treeBP.searchsFile(ID_ins);
			}
			else if (select_f1 == 2)
			{
				cout << "RANGE SEARCH" << endl;
				cout << "Enter Range of Values you want to Search : \n";
				cout << "Enter lower bound : \n";
				int lbb;
				cin >> lbb;
				cout << "Enter uper bound : \n";
				int upbb;
				cin >> upbb;
				treeBP.ranga_tree(lbb, upbb);/////////////fowork

			}
			else if (select_f1 == 3)
			{
				cout << "UPDATE" << endl;
				cout << "Enter key to be Inserted : \n";
				int key_ins;
				cin >> key_ins;
				treeBP.insert_ID(key_ins);
			}
			else if (select_f1 == 4)
			{
				cout << "TREE TRAVERSED" << endl;
				treeBP.traverse_tree();
			}

			cout << "\nTo Continue?\n  Enter 0(YES) or 1(NO):";
				cin >> sara_trash;
		}
	}

	if (select_tree == 2)
	{
		btree treeB;

		cout << "BTREE IS CREATED" << endl;

		bool sara_trash = false;
		while (!sara_trash)
		{

			cout << "Select the following: " << endl << "1: To Point-Search" << endl << "2:To Insert/Update" << endl << "3:To Traverse your desired Tree. \n" << endl;
			int select_f2;
			cin >> select_f2;
			if (select_f2 == 1)
			{
				cout << "POINT-SEARCH" << endl;

				cout << "Enter ID to be Searched : \n";
				int ID_ins;
				cin >> ID_ins;

			}


			if (select_f2 == 2)
			{
				cout << "Enter Range of Values you want to Search : \n";

				cout << "Enter key to be Inserted : \n";
				int key_ins;
				cin >> key_ins;
				treeB.insert_int_ID(key_ins);

			}
			if (select_f2 == 3)
			{
				treeB.display_tree();
				cout << "TREE TRAVERSED" << endl;

			}


			cout << "To Continue?\n  Enter 0(YES) or 1(NO):";
			cin >> sara_trash;

		}

		
	}
	cout << "THANK YOU FOR YOUR TIME !!!!!!" << endl;



}


void main()
{


	/*
BpTree booty(5);  // A B-Tree with minium degree 3
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_1.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_2.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_3.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_4.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_5.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_6.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_7.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_8.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_9.csv", &booty);
readFile("E:\\Visual studio 2015 Projects\\SP\\SP\\datafiles\\InputFiles\\NCHS_-_Leading_Causes_of_Death__United_States_10.csv", &booty);

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
t.traverse_tree();
cout << endl;


VECTORVV<VECTOR<int>> AV;  // 2D vector class
AV = t.findkeys_withnode(); 
cout << endl;

	AV.displayD();
	cout << endl;

	cout << "count:" << AV.getCount();



/*
int k = 15;
string str_add1;
str_add1 = t.searchsFile(k);
cout << str_add1 << endl;

k = 10;
str_add1 = t.searchsFile(k);
cout << str_add1 << endl;
*/


	interface_tree();


system("pause");

}

