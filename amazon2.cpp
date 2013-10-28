#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <queue>
#include <sstream>


using namespace std;


vector < string > GetEliminationResult(vector < string > matrixString,
 										int numOfColumn, int numOfRow, int hitXIndex, int hitYIndex)
{
    /*
    matrixString is an array of strings. Each string is a space seperated string like this "1 1 2 4". 
    It is a row of the matrix
    numOfColumn: Number of the columns in the matrix
    numOfRow: Number of rows in the matrix
    hitXIndex: the x index of the hit position
    hitYIndex: the y index of the hit position
    */
    vector<vector<int> > colorMatrix;
    // convert string matrix to integer matrix
    for(int i = 0; i < numOfRow; ++i)
    {
    	string rowStr = matrixString[i];
    	vector<int> rowColor;
    	int color = 0;
    	for(int j = 0; j < rowStr.length(); ++j)
    	{
    		if(rowStr[j] != ' ')
    		{
    			color = color*10+rowStr[j]-'0';
    		}
    		else
    		{
    			rowColor.push_back(color);
    			color = 0;
    		}
    	}
    	rowColor.push_back(color);
    	colorMatrix.push_back(rowColor);
    }

    // bfs
    queue<pair<int, int> > nodeQueue;
    nodeQueue.push(make_pair(hitYIndex, hitXIndex));
    int target = colorMatrix[hitYIndex][hitXIndex];
    colorMatrix[hitYIndex][hitXIndex] = 0;
    while(!nodeQueue.empty())
    {
    	pair<int, int> node = nodeQueue.front();
    	nodeQueue.pop();
    	if(node.first > 0 && colorMatrix[node.first-1][node.second] == target)
    	{
    		nodeQueue.push(make_pair(node.first-1, node.second));
    		colorMatrix[node.first-1][node.second] = 0;
    	}
    	if(node.first < numOfRow-1 && colorMatrix[node.first+1][node.second] == target)
    	{
    		nodeQueue.push(make_pair(node.first+1, node.second));
    		colorMatrix[node.first+1][node.second] = 0;
    	}
    	if(node.second > 0 && colorMatrix[node.first][node.second-1] == target)
    	{
    		nodeQueue.push(make_pair(node.first, node.second-1));
    		colorMatrix[node.first][node.second-1] = 0;
    	}
    	if(node.second < numOfColumn-1 && colorMatrix[node.first][node.second+1] == target)
    	{
    		nodeQueue.push(make_pair(node.first, node.second+1));
    		colorMatrix[node.first][node.second+1] = 0;
    	}
    }

    // down the non-zero elements
    for(int i = 0; i < numOfColumn; ++i)
    {
    	int countOfZero = 0;
    	for(int j = numOfRow-1; j >= 0; --j)
    	{
    		if(colorMatrix[j][i] != 0)
    		{
    			colorMatrix[j+countOfZero][i] = colorMatrix[j][i];
    		}
    		else
    		{
    			++countOfZero;
    		}
    	}
    	while(countOfZero > 0)
    	{
    		colorMatrix[--countOfZero][i] = 0;
    	}
    }

    vector<string> result;
    for(int i = 0; i < numOfRow; ++i)
    {
    	stringstream ss;
    	for(int j = 0; j < numOfColumn; ++j)
    	{
    		ss << colorMatrix[i][j];
    		if(j < numOfColumn-1)
    		{
    			ss << ' ';
    		}
    	}
    	result.push_back(ss.str());
    }

    return result;
}


int main()
{
	vector<string> matrixString;
	matrixString.push_back("33 33 33 11 22 33");
	matrixString.push_back("11 11 33 11 11 33");
	matrixString.push_back("33 33 33 11 33 33");
	matrixString.push_back("33 11 11 33 33 22");
	matrixString.push_back("33 11 11 33 23 23");
	matrixString.push_back("33 33 33 33 23 33");
	vector<string> result = GetEliminationResult(matrixString, 6, 6, 4, 3);
	for(int i = 0; i < result.size(); ++i)
	{
		cout << result[i] << endl;
	}

	return 0;
}
