#pragma once
#include "BaseEngine.h"
#include "Context.h"
#include "SmallMedicineTile.h"
#include "SmallEnergyTile.h"
#include "LargeMedicineTile.h"
#include "LargeEnergyTile.h"
#include <map>
#include <memory>
#include <Windows.h>
#include "DataPair.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

using namespace std;
class Scyjl15Engine :
    public BaseEngine
{
private:
    map<string, vector<DataPair<int, int>*>> edgePointsMap;
    bool isPlaying;
public:
    Scyjl15Engine();
    ~Scyjl15Engine();
    const char mainMusicPath[50] = "music\\TimeBack.wav";
    void virtSetupBackgroundBuffer() override;
    void virtDrawStringsOnTop() override;
    void virtKeyUp(int iKeyCode) override;
	int virtInitialiseObjects() override;
    void virtMouseDown(int iButton, int iX, int iY) override;

    Context* m_Context=NULL;
    void virtKeyDown(int iKeyCode);
    void virtMainLoopDoBeforeUpdate() override;
    void setUpdatePeriod(int milliseconds);
    void copyAllBackgroundBuffer() override;
    void setBackgroundSurface(DrawingSurface* surface);
    vector<DataPair<int, int>*> getEdgePointsByName(string name);
    static void playMusic(const std::string& musicFilePath, const std::string& alias);
    static void playMusic(const std::string& alias);
    static void loadMusic(const std::string& musicFilePath, const std::string& alias);
    static void playMusicLoop(const std::string& musicFilePath, const std::string& alias);
    static void stopAndCloseMusic(const std::string& alias);
    bool getIsPlaying();
    void setIsPlaying(const bool playing);
    virtual void virtMouseWheel(int x, int y, int which, int timestamp) override;
};

