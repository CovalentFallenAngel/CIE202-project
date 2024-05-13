#include "toolbar.h"
#include "game.h"
#include <thread>
//#include "grid.h"


////////////////////////////////////////////////////  class toolbar   //////////////////////////////////////////////
toolbar::toolbar(game* pG)
{	
	height = config.toolBarHeight;
	width = config.windWidth;
	this->pGame = pG;
	window* pWind = pGame->getWind();	
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each toolbar item
	toolbarItemImages[ITM_SIGN] = "images\\toolbarItems\\toolbar_sign.jpg";
	toolbarItemImages[ITM_ICE] = "images\\toolbarItems\\ice_cream.jpg";
	toolbarItemImages[ITM_CAR] = "images\\toolbarItems\\car.jpg";
	toolbarItemImages[ITM_Person] = "images\\toolbarItems\\Pearson.jpg";
	toolbarItemImages[ITM_Home] = "images\\toolbarItems\\Home.jpg";
	toolbarItemImages[ITM_Rocket] = "images\\toolbarItems\\Rocket.jpg";
	toolbarItemImages[ITM_Tree] = "images\\toolbarItems\\Tree.jpg";
	toolbarItemImages[ITM_Inc] = "images\\toolbarItems\\plus.jpg";
	toolbarItemImages[ITM_Dec] = "images\\toolbarItems\\minus.jpg";
	toolbarItemImages[ITM_Rotate] = "images\\toolbarItems\\rotate.jpg";
	toolbarItemImages[ITM_Flip] = "images\\toolbarItems\\Flip.jpg";
	toolbarItemImages[ITM_Ref] = "images\\toolbarItems\\refresh.jpg";
	toolbarItemImages[ITM_Hint] = "images\\toolbarItems\\hint.jpg";
	toolbarItemImages[ITM_del] = "images\\toolbarItems\\Delete.jpg";
	toolbarItemImages[ITM_SGL] = "images\\toolbarItems\\SGL.jpg";
	toolbarItemImages[ITM_SAL] = "images\\toolbarItems\\save.jpg";
	toolbarItemImages[ITM_EXIT] = "images\\toolbarItems\\toolbar_Exit.jpg";
	//TODO: Prepare image for each toolbar item and add it to the list
	//Draw toolbar item one image at a time
	for (int i = 0; i < ITM_CNT; i++) {
		pWind->DrawImage(toolbarItemImages[i], i * config.toolbarItemWidth, 0, config.toolbarItemWidth, height);
		count = i;
	}

	int xString = config.toolbarItemWidth * (count + 1);
	pWind->SetBrush(LAVENDER);
	pWind->SetPen(LAVENDER);
	pWind->DrawCircle(xString+50, 25 , 50 , FILLED);

	pWind->SetPen(BLACK, 3);
	pWind->SetFont(20, BOLD, MODERN, "Arial");
	pWind->DrawString(xString, 0, "   Lives");
	pWind->DrawString(xString, 20, "Level =  ");
	pWind->DrawString(xString, 40, "Score =  ");
	pWind->DrawString(xString + 100, 0, "Steps =  ");
	pWind->DrawString(xString + 100, 20, "Timer = ");
	pWind->DrawString(xString + 100, 40, "xsteps = ");

	int xInteger = (xString + 65);
	pWind->DrawInteger(xString, 0, pGame->getLives());
	pWind->DrawInteger(xInteger, 20, pGame->getLevel());
	pWind->DrawInteger(xInteger, 40, pGame->getScore());
	pWind->DrawInteger(xInteger + 100, 0, pGame->get_steps());
	pWind->DrawInteger(xInteger + 100, 40, pGame->get_xsteps());
	thread think_thread(&game::thinkTimer, pGame, xInteger, pGame);
	think_thread.detach();



	//Draw a line under the toolbar
	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, height,width , height);
}


//handles clicks on toolbar icons, returns itm_cnt if the click is not inside the toolbar
toolbarItem toolbar::getItemClicked(int x)
{
	
	if (x > ITM_CNT * config.toolbarItemWidth)	//click outside toolbar boundaries
		return ITM_CNT;
	
	
	//Check whick toolbar item was clicked
	//==> This assumes that toolbar items are lined up horizontally <==
	//Divide x coord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

	return (toolbarItem)(x / config.toolbarItemWidth);

}

