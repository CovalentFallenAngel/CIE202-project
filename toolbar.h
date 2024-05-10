#pragma once
#include "gameConfig.h"
#include <thread>
////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
class game;
class toolbar
{

private:
	int height, width;	
	int count;
	string toolbarItemImages[ITM_CNT]; //array to hold paths to images of diffrent items in the toolbar
	game* pGame;

public:
	toolbar(game* r_pGame);
	void drawdata();
	toolbarItem getItemClicked(int x);	//handles clicks on toolbar icons, returns the "enum" of the clicekd item
};

