#pragma once
#include "header.h"

#include "SimpleImage.h"
#include "ImageManager.h"
#include <map>
#include <fstream>
#include <vector>
#include "DataPair.h"
using namespace std;
class FileUtils
{
public:
	static map<string, string> readFromFile(string fileName);
	static map<int, string> readPairFromFile(string fileName);
	static void saveMapToFile(map<string,string> fileMap, string filePath);
	static vector<string> split(const string& str, const string& pattern);
	static void saveImageDataToCSV(string imagePath,string imageName);
	static vector<DataPair<int, int>*> loadEdgePoints(string path);
	static void clearPairsInVector(vector<DataPair<int, int>*> pairs);
	static void clearPairsInVector(vector<DataPair<string, int>*> pairs);
	static map<string, vector<DataPair<int, int>*>> getEdgePointsMap();
	static vector<DataPair<string, int>*> loadScores();
	static void saveScore(int newScore);
};

