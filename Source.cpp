#include"clustering.h"
#include<Windows.h>


int main()
{
	stopwords();

	string filename = "1";
	ifstream f1;
	cout << "please wait wile training is being proceecing\n";
	training();
	cout << "traing is done successfully\n";
	
	for (int f = 0; f < 50; f++)
	{

	filename = "d" + to_string(f) + ".txt";
		f1.open(filename);
		if (!f1.is_open())
		{
			cout << "can't open file::" << filename << endl;
			//cout << "enter a valid filename\n";
			f1.close();
			continue;
		}
		f1.close();
		cout << "processing file ::" << filename<<endl;
		//filter_tokens(filename, n);
		//n++;
		//system("cls");
		//system("color 0f");
		cout << endl<<classify(filename)<<endl;
		//display_all();
		//d_sort(curr_file);
		//display(curr_file);

	}
	for (int v = 0; v < stopf; v++)
	{
		cout << ":::\n_________________________\n";
		cout << training_set[v][1] <<endl;
		for (int l= stopf; l < n; l++)
		{
			if (cluss[l]==v)
			{
				cout << filesn[l] << "| ";
			}
		}
	}
		RE:
	cout << "\n\n\n\n\t\t\t\t\t=+=+*********************************************+=+=\n\n\n";
	
	cout << "\t\t\t~~: SELECT TOPIC TO PRINT ITS FILES::\n\t 0: TO PRINT ALL FILES\n\t\t\t\t 1: TO PRINT ART'S FILES\n\t\t\t\t 2: TO PRINT BUSINESS'S FILES\n\t\t\t\t 3: TO PRINT NATURE'S FILES"
		<< "\n\t\t\t\t 4: TO PRINT POLITICS'S FILES\n\t\t\t\t 5: TO PRINT SCIENCE FILES\n\t\t\t\t 6: TO PRINT SPORTS'S FILES\n\t\t\t\t 7: TO PRINT TECHNOLOGY'S FILES\n\t\t\t\t 8: TO PRINT WEATHER'S FILES\n\t\t\t\t\t\t::::::::";
	int choice;
	cin >> choice;
	if (9 > choice &&choice> 0)
	{
		system("cls");
//	system("color 02");
		cout << "\n_______________________________________________________________________\n" << "\n\t\t\tFILES FOR ::" << training_set[(choice-1)][1] << "::\n_______________________________________________________________________\n\t\t";
		for (int ox = 1; ox < n; ox++)
		{
			if (cluss[ox] == (choice - 1))
			{
				d_sort(ox);
				display(ox);
			}

		}
	}
	else if ( choice == 0 )
	{
		system("cls");
	//system("color 02");
		for (int cl = 0; cl < 8; cl++) {
			cout << "\n\t\t\tFILES FOR ::" << training_set[cl][1] << "::\n_______________________________\n";
			for (int ds = 8; ds < n; ds++)
			{
				if (cluss[ds] == cl) {
					d_sort(ds);
					display(ds);
				}
			}
		}
	}
	else {
		system("cls");
		cout << "\n\n\t\t\tENTER A VALID NUMBER PLEASE FORM 0:7\n";
		goto RE;
	}
	int con;
	cout << "\n\t\t\tPRESS :1: TO CONTIUE || :ANY: TO HALT THE PROGRAM :: "; cin >> con;
	if (con==1)
	{
		goto RE;
	}
	return 0;
	//	n--;
	//}
	

}