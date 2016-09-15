/*
===========================================================================================================

Title : Student Sorting
File Name : StudentSortingProject.cpp

App Type : Console Application (Non-GUI)

Functionality : 1. Takes Student File Name as input. Student File (TXT) should have records in the format:
<Last Name>, <First Name>, <Score>
2. Reads records from file, processes in the following order:
a. Sort Students by Score (Top Scorer comes first)
b. If two ore more students have equal scores, sort by their Last Name in Ascending Order
3. Write the sorted output to <Input_File_Name>_Graded.txt (_Graded will be suffixed to the file name)
4. Return with a success message.

Sorting Technique : Bubble Sort (Simple and efficient for small sorts)

Author :	Naveen Jothiram
First Version Creation Date : 14-Sep-2016


===========================================================================================================
*/

#include "stdafx.h"


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Structure to store Student First Name, Student Last Name and Student Score
struct StudentDet
{
	string studFName;
	string studLName;
	int Score;
};

//Function to sort the student list based on score, with highest score as first array element(Descending). 
//In case of equal score, students would be sorted based on second name, in Ascending Order
void fn_sortStudent(StudentDet* pSource, int iArraySize)
{
	StudentDet Temp;

	for (int i = 0; i<iArraySize - 1; i++)
	{
		for (int j = i + 1; j<iArraySize; j++)
		{
			if (pSource[i].Score < pSource[j].Score)
			{
				Temp.Score = pSource[i].Score;
				Temp.studFName = pSource[i].studFName;
				Temp.studLName = pSource[i].studLName;

				pSource[i].Score = pSource[j].Score;
				pSource[i].studFName = pSource[j].studFName;
				pSource[i].studLName = pSource[j].studLName;

				pSource[j].Score = Temp.Score;
				pSource[j].studFName = Temp.studFName;
				pSource[j].studLName = Temp.studLName;

				fn_sortStudent(pSource, iArraySize);
			}
			else if (pSource[i].Score == pSource[j].Score)
			{
				if (strcmp(pSource[j].studLName.c_str(), pSource[i].studLName.c_str()) < 0)
				{
					Temp.Score = pSource[i].Score;
					Temp.studFName = pSource[i].studFName;
					Temp.studLName = pSource[i].studLName;

					pSource[i].Score = pSource[j].Score;
					pSource[i].studFName = pSource[j].studFName;
					pSource[i].studLName = pSource[j].studLName;

					pSource[j].Score = Temp.Score;
					pSource[j].studFName = Temp.studFName;
					pSource[j].studLName = Temp.studLName;

				}
			}
		}
	}
}
int main()
{
	string sFileNm;   //Name of the file
	string sFileData; 	//Data from the file

	ifstream istrmFileOpen;
	int iRecCnt = 0;	//Counts the number of records in the file

	cout << "Enter file name : ";
	cin >> sFileNm;
	cout << endl;

	istrmFileOpen.close();

	if (sFileNm != "")
	{
		istrmFileOpen.open(sFileNm.c_str());

		if (istrmFileOpen.is_open())
		{
			//File Line Format is <field1>, <field2>, <field3>
			while (!istrmFileOpen.eof())
			{
				sFileData = "";
				istrmFileOpen >> sFileData; //Extract field1
				if (sFileData == "")
					break;

				istrmFileOpen >> sFileData; //Extract field2
				istrmFileOpen >> sFileData; //Extract field3

											//Now complete line is read (after extracting all three fields). 
				iRecCnt++;
			}
		}
		else
		{
			cout << "Could not open file " << sFileNm;
			istrmFileOpen.close();

			exit(0);
		}
	}
	else
	{
		cout << "Invalid file name" << endl;
		exit(0);
	}
	istrmFileOpen.close();

	StudentDet *pStudArray = new StudentDet[iRecCnt];   //Stores all student information

	istrmFileOpen.open(sFileNm, ios::in);
	//istrmFileOpen.open("C:\\testscr.txt", ios::in);

	if (!istrmFileOpen.is_open())
		exit(0);

	int iTempCnt = 0;
	int iCommaLoc = 0;

	while (!istrmFileOpen.eof())
	{
		//Read Last Name
		sFileData = "";
		istrmFileOpen >> sFileData;
		if (sFileData == "")
			break;

		iCommaLoc = sFileData.find(",", 0);
		pStudArray[iTempCnt].studLName = sFileData.substr(0, iCommaLoc);

		//Read First Name
		sFileData = "";
		istrmFileOpen >> sFileData;
		iCommaLoc = sFileData.find(",", 0);
		pStudArray[iTempCnt].studFName = sFileData.substr(0, iCommaLoc);

		//Read Score
		sFileData = "";
		istrmFileOpen >> sFileData;
		pStudArray[iTempCnt].Score = atoi(sFileData.c_str());

		iTempCnt++;

	}

	istrmFileOpen.close();

	fn_sortStudent(pStudArray, iRecCnt);

	string sOutFileNm = sFileNm.substr(0, sFileNm.length() - 4) + "_Graded.txt"; //Use the same file name and append _Graded
	ofstream ostrmOutputFile(sOutFileNm);

	if (ostrmOutputFile.fail())
	{
		cout << "Could not write to file" << endl;
		exit(0);
	}

	for (int i = 0; i < iRecCnt; i++)
	{
		ostrmOutputFile << pStudArray[i].studLName << ", " << pStudArray[i].studFName << ", " << pStudArray[i].Score << endl;
	}
	ostrmOutputFile.close();
	cout << "Sorted output is directed to " << sOutFileNm << endl;

	delete[] pStudArray;
	pStudArray = NULL;

	return 0;
}


