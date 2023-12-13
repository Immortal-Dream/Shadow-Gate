#include "header.h"
#include "FileUtils.h"


/*
    read data from file to map 
*/
map<string, string> FileUtils::readFromFile(string fileName)
{
    ifstream inputFile;
    map<string, string> fileData;
    inputFile.open(fileName);
    string line;
    while (getline(inputFile,line))
    {
        vector<string> data = split(line, "=");
        fileData.insert(pair<string,string>(data[0], data[1]));
    }
    inputFile.close();
	return fileData;
}

map<int, string> FileUtils::readPairFromFile(string fileName)
{
    ifstream inputFile;
    map<int, string> fileData;
    inputFile.open(fileName);
    string line;
    while (getline(inputFile, line))
    {
        vector<string> data = split(line, "=");
        fileData.insert(pair<int, string>(stoi(data[0]), data[1]));
    }
    inputFile.close();
    return fileData;
}

/*
    save data from map to file, with file path
*/
void FileUtils::saveMapToFile(map<string, string> fileMap, string filePath)
{
    map<string, string>::iterator iter;
    iter = fileMap.begin();
    ofstream outfile;
    outfile.open(filePath);
    while (iter != fileMap.end())
    {
        outfile << iter->first << "=" << iter->second;
        iter++;
    }
    outfile.close();
}
/*
    split the string str according to pattern, return the split 
    strings with a string vertor
*/
vector<string> FileUtils::split(const string& str, const string& pattern)
{
    vector<string> stringVector;
    if (str == "")
        return stringVector;
    
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while (pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        stringVector.push_back(temp);
        
        strs = strs.substr(pos + 1, strs.size());
        pos = strs.find(pattern);
    }

    return stringVector;
}

/*
* save image's edge pixel points (the outer points with colour)to csv file which will be used in 
* pixel-perfect detection
*/
void FileUtils::saveImageDataToCSV(string imagePath, string imageName)
{
    SimpleImage image = ImageManager::loadImage(imagePath, true);
    shared_ptr<RawImageData> theData = image.getRawImageData();
    fstream outfile;
    outfile.open("data/"+imageName+".csv", ios::out | ios::app);
    int middlePoint = image.getHeight() / 2;
    // get the mask colour and mask colour is not regarded as edge points.
    int maskColor = theData->getRawPixelColour(theData->getWidth() - 1, theData->getHeight() - 1);
    for (int xOffset = 0; xOffset < image.getWidth(); xOffset++)
    {
        int yMin = middlePoint;
        int yMax = middlePoint;
        for (int yOffset = 0; yOffset < image.getWidth(); yOffset++) {
            int pixel = theData->getRawPixelColour(xOffset, yOffset);
            if (pixel!=maskColor)
            {
                if (yOffset < yMin) {
                    yMin = yOffset;
                }
                else if (yOffset > yMax) {
                    yMax = yOffset;
                }
            }
        }
        // if the tangent line have two intersections with the irregular shape, save the points
        if (yMin != yMax)
        {
            outfile << xOffset << "," << yMin << endl;
            outfile << xOffset << "," << yMax << endl;
        }
    }
    

    outfile.close();
}
/*
* load edge points from the file
*/
vector<DataPair<int, int>*> FileUtils::loadEdgePoints(string path)
{
    vector<DataPair<int, int>*> edgePoints;
    ifstream inputFile;
    inputFile.open(path);
    string line;
    while (getline(inputFile, line))
    {
        if (line == "") {
            continue;
        }
        vector<string> data = split(line, ",");
        int x = stoi(data[0]);
        int y = stoi(data[1]);
        DataPair<int, int>* pair = new DataPair<int, int>(x, y);
        edgePoints.push_back(pair);
    }
    inputFile.close();
    return edgePoints;
}
/*
* clear all data pair in a array
*/
void FileUtils::clearPairsInVector(vector<DataPair<int, int>*> pairs)
{
    for (int i = 0; i < pairs.size(); i++)
    {
        delete pairs[i];
        pairs[i] = nullptr;
    }
}
void FileUtils::clearPairsInVector(vector<DataPair<string, int>*> pairs)
{
    for (int i = 0; i < pairs.size(); i++)
    {
        delete pairs[i];
        pairs[i] = nullptr;
    }
}
map<string, vector<DataPair<int, int>*>> FileUtils::getEdgePointsMap()
{
    map<string, vector<DataPair<int, int>*>> edgePointsMap;
    string nameArray[6] = {"Orc","Skeleton","Warrior","Behemoth","Goblin","Wizard"};
    string pathPrefix = "data/";
    string fileType = ".csv";
    for each (string name in nameArray)
    {
        string path = pathPrefix + name + fileType;
        edgePointsMap.insert(pair<string, vector<DataPair<int, int>*>>(name,loadEdgePoints(path)));
    }
    return edgePointsMap;
}
/*
* load top three scores from the file
*/
vector<DataPair<string, int>*> FileUtils::loadScores()
{
    vector<DataPair<string, int>*> scores;
    ifstream inputFile;
    inputFile.open("data/HighScore.csv");
    string line;
    while (getline(inputFile, line))
    {
        if (line == "") {
            continue;
        }
        vector<string> data = split(line, ",");
        DataPair<string, int>* pair = new DataPair<string, int>(data[0], stoi(data[1]));
        scores.push_back(pair);
    }
    inputFile.close();
    return scores;
}

/*
* save the current score to file if it is one of top3 highest scores
*/
void FileUtils::saveScore(int newScore)
{
    vector<DataPair<string, int>*> scoreList;
    scoreList = loadScores();
    map<string, string> gameSettings = FileUtils::readFromFile("data/game_setting.txt");
    string currentName = gameSettings["player name"];
    DataPair<string, int>* pair = new DataPair<string, int>(currentName, newScore);
    scoreList.push_back(pair);

    // save new top3 scores to file using bubble sort
    ofstream fileStream;
    fileStream.open("data/HighScore.csv");
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < scoreList.size(); j++) 
        {
            if (scoreList[j]->getSecond() > scoreList[i]->getSecond())
            {
                DataPair<string, int>* temp = scoreList[i];
                scoreList[i] = scoreList[j];
                scoreList[j] = temp;
            }
        }
        fileStream << scoreList[i]->getFirst() << "," << scoreList[i]->getSecond() << endl;
    }

    clearPairsInVector(scoreList);
    fileStream.close();
}



