#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include<iomanip>
#include "estemmer.h"
int cluss[50]{ -1,-1,-1,-1,-1,-1,-1,-1};
using namespace std;
int len[50] = { 0 }, fsize = 0, maxsize = 0, curr_file, stopf ;
int n = 0;
string stopwor[500] = { " " };
int stoplen = 0;
string training_set[8][2] = { {"tranining_set/arts.txt","ART"},{"tranining_set/business.txt","BUSINESS"},{"tranining_set/nature.txt","NATURE"},{"tranining_set/politics.txt","POLITICS"},{"tranining_set/science.txt","SCIENCE"},{"tranining_set/sports.txt","SPORTS"} ,{"tranining_set/tech.txt","TECH"},{"tranining_set/weather.txt","WEATHER"} };
struct word
{
	string word;
	int filefreq[50] = { 0 };
	float TF_IDF = 0;
	
};
string filesn[50];
word w[10000];
void stopwords() {
	ifstream stop;
	stop.open("stopwords.txt", ios::beg);
	stop.seekg(0);
	string  y;
		while (!stop.eof())
		{
			stop >> y;
			stemmer(y);
			stopwor[stoplen] = y;
			stoplen++;
		}
		stop.close();

}

void d_sort(int f) {

	for (int i = 0; i < fsize; i++)
	{
		int counter = 0;
		for (int j = 0; j < n; j++)
		{
			if (w[i].filefreq[j])
				counter++;
		}
		float idf = 0;
		idf = log10(1 / (float(counter) / n));
		w[i].TF_IDF = w[i].filefreq[f] * idf;

	}
	//sorting
	for (int j = 1; j < fsize; j++)
	{
		word key;
		key = w[j];
		int i = j - 1;
		while (i >= 0 && w[i].TF_IDF > key.TF_IDF)
		{
			w[i + 1] = w[i];

			i--;

		}
		w[i + 1] = key;

	}
}
void display(int f) {

	cout <<"\t\t\t\t\t*********************************************\n\t\t\t\t\t---------------DOCUMENT::" << filesn[f] << " ------------\n\t\t\t\t\t**********************************************\n\n";
	for (int x = fsize; x >= fsize-50; x--)
	{
		if (w[x].filefreq[f])
		{

			float weight = float(w[x].filefreq[f]) / float(len[f]);
			cout << setw(20)<<"|  WORD::>>" << w[x].word << setw(30-(w[x].word).length()) << " | FREQUENCY :: "<< w[x].filefreq[f] <<  "\t| WEIGHT :: " << weight << "\t| TF-IDF ::" << w[x].TF_IDF << "\t|\n";
		}
	}
}

void filter_tokens(string filename, int file_no) {
	ifstream infile;
	infile.open(filename, ios::beg);
	infile.seekg(0);
	string x, y;
	while (infile.good())
	{
		infile >> x;
		stemmer(x);
		len[file_no]++;
		bool isin = false;
		for (int s = 0; s < stoplen; s++)
		{

			y = stopwor[s];
			if (x == y)
			{
				break;
			}
		}
		

		if (x!=y)
		{
			if (fsize == 0)
			{
				w[fsize].word = x; w[fsize].filefreq[file_no] = 1; fsize++;
			}
			else
			{

				for (int j = 0; j <= fsize; j++)
				{

					if (w[j].word == x)
					{

						w[j].filefreq[file_no]++;
						goto end;

					}



				}
				w[fsize].word = x; w[fsize].filefreq[file_no] = 1; fsize++;
			}
		end:
			cout << "";
		}
	}
	infile.close();
}
void training() {
	n = 0;
	for (int i = 0; i < 8; i++)
	{
		filter_tokens(training_set[i][0], n);
		n++;
		cout << n << endl;
	}
	stopf = n;

}
float jack_sim(int f1,int f2) {
	float  uni = 0, x=0;
	for (int i = 0; i < fsize; i++)
	{
		x += (w[i].filefreq[f1] && w[i].filefreq[f2]);
		uni+= (w[i].filefreq[f1] || w[i].filefreq[f2]);
	}
	return x / uni;
}
float cos_simlarity(int f1,int f2) {
	float dot = 0, norm1=0,norm2=0;
	for (int i = 0; i < fsize; i++)
	{
		if (w[i].filefreq[f1] )
		{
			dot += w[i].filefreq[f1] * w[i].filefreq[f2];
			norm1+=w[i].filefreq[f1]*w[i].filefreq[f1];
			norm2+=w[i].filefreq[f2]*w[i].filefreq[f2];
		}
	}
	return cos(dot/(sqrt(norm1)*sqrt(norm2)));
}



string classify(string filename) {
	filter_tokens(filename, n);
	curr_file = n;
	n++;
	int x_index=0;
	float max=0;
	for (int i = 0; i < stopf; i++)
	{
		float sim = jack_sim(i, curr_file);
		if (sim>max)
		{
			x_index = i;
			max = sim;
		}
	}
	cluss[curr_file] = x_index;
	filesn[curr_file] = filename;
	return training_set[x_index][1];
}