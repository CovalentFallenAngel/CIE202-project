#pragma once
#include "CMUgraphicsLib/CMUgraphics.h"


//The folowing struct contains all game configurations
// (MAY be loaded from a configuration file later)
__declspec(selectany) //This line to prevent "redefinition error"
struct 		
{
	int	windWidth=1366, windHeight=600,	//Window width and height
		wx=5, wy=5,			//Window starting coordinates

		//The window is divded into 3 areas: toolbar, Working area, and statusbar
		toolBarHeight=70,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		toolbarItemWidth = 63,			//Width of each icon in toolbar
		statusBarHeight=50;	//Status Bar Height
	
	int remainingHeight = windHeight - toolBarHeight - statusBarHeight;

	int gridHeight = int(remainingHeight * (2 / 3.0)); 		//The grid is where bricks can be drawn

	//Default colors
	color	penColor = RED,			//color used to draw borders/write messages
			fillColor = RED,			//shapes fill color (Default)
			bkGrndColor= LAVENDER,		//Screen Background color
			statusBarColor = LIGHTSEAGREEN;	//background color of the status
	int penWidth=1;			//width of the pen that draws shapes


	color gridDotsColor = RED;
	int gridSpacing=30;	//spacing between grid points

	////// Configuration for the composite shapes //////
	// default Ref Point for any newly created shape 
	int RefX = windWidth *  (2.0 / 3);
	int RefY = windHeight * (0.5);

	////-----  Sign Shape Confoguration ---------////
	// For the Sign shape, define width and height of both rectangles
	struct {
		int baseWdth = 20, baseHeight = 80;
		int topWdth = 100, topHeight = 50;
	}sighShape;

	struct {
		int basewdth = 50, basehght = 50;
		int side_length = 50;
	}Homeshape;
	
	struct {
		int headDiameter = 30; 
		int height = 100, width = 50;
		int armLength = 10, armWidth = 20;
		int legLength = 20, legWidth = 10;
	}Person;
	
	struct {
		int headDiameter = 50;
		int side_lenght=50;
	}ice_cream;

	struct {
		int side_length = 50;
		int basewdth = 20, basehght = 50;
	}Tree;
	struct
	{
		int side_length = 30;
		int Rbase_length = 15,Rhght=50;
		int Lbase_length = 15,Lhght=50;
		int basewdth = 30, basehght = 70;
	}Rocket;

	struct 
	{
		int T1base_length = 15, T1hght = 25;
		int Radius = 10;
		int R1wdth = 50, R1hght = 20;
		int R2wdth = 70, R2hght = 20;
	}Car;
}config;


enum toolbarItem //The items of the  toolbar (you should add more items)
{
	//Note: Items are ordered here as they appear in the toolbar
	//If you want to change the toolbar items order, just change the order here
	ITM_SIGN,		//Sign shape item

			//Exit item
	//TODO: Add more items names here

		//no. of toolbar items ==> This should be the last line in this enum
	ITM_ICE,
	ITM_CAR,
	ITM_Person,
	ITM_Home,
	ITM_Rocket,
	ITM_Tree,
	ITM_Inc,
	ITM_Dec,
	ITM_Rotate,
	ITM_Flip,
	ITM_Ref,
	ITM_Hint,
	ITM_del,
	ITM_SGL,
	ITM_SAL,
	ITM_Load,
	ITM_EXIT,
	ITM_CNT
};



