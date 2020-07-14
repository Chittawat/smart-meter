/*
 * Embedded.c
 *
 *  Created on: 31 Jan 2018
 *      Author: cp5g15 & jte1n17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/power.h>
#include <inttypes.h>
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "pictor.h"
#include "fonts/Mash.h"

#define FREQ 488
#define TONE_PRESCALER 1

char charge[]="Charging";
char off[]="Off      ";
char discharge[]="Discharge";
char A_per_S[] =" As ";
char blank[]="  ";
float *battery_value;
int bit=10;

// Interfacing Function /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Drawing Tool 1 - Drawing Rectangle Pixel==========================================================
void draw_rect(int leftside,int rightside, int topside, int bottomside,uint16_t col)
{
	rectangle r;
		r.left=leftside;
		r.right=rightside;
		r.top=topside;
		r.bottom=bottomside;
		fill_rectangle(r,col);
}

// Drawing Tool 2 - Drawing Square Pixel=============================================================
void draw_square(int x, int y,int w,uint16_t colour)
{
	draw_rect(x,x+w,y,y+w,colour);
}

// Drawing 1 - Vertical Line=========================================================================
void draw_vline(int x, int y,int z)
{
	rectangle r;
		r.left=x;
		r.right=y;
		r.top=z;
		r.bottom=z;
		fill_rectangle(r,WHITE);
}

// Drawing 2 - Horizontal Line=======================================================================
void draw_hline(int x, int y,int z)
{
	rectangle r;
		r.left=z;
		r.right=z;
		r.top=x;
		r.bottom=y;
		fill_rectangle(r,WHITE);
}

// Drawing 3 - Smart Meter Box=======================================================================
void draw_smeter(void){
	draw_rect(10,45,25,60,SKYBLUE);
	draw_rect(10,45,25,26,WHITE);
	draw_rect(10,45,59,60,WHITE);
	draw_rect(10,11,25,60,WHITE);
	draw_rect(44,45,25,60,WHITE);
	//side
	draw_rect(45,46,24,59,SKYBLUE);
	draw_rect(46,47,23,58,SKYBLUE);
	draw_rect(47,48,22,57,SKYBLUE);
	draw_rect(48,49,21,56,SKYBLUE);
	draw_rect(49,50,20,55,SKYBLUE);
	draw_rect(50,51,19,54,SKYBLUE);
	draw_rect(51,52,18,53,SKYBLUE);
	draw_rect(52,53,17,52,SKYBLUE);
	draw_rect(53,54,16,51,SKYBLUE);
	draw_rect(54,55,15,50,SKYBLUE);
	draw_rect(55,56,14,49,WHITE);
	//whiteside
	draw_rect(45,46,58,59,WHITE);
	draw_rect(46,47,57,58,WHITE);
	draw_rect(47,48,56,57,WHITE);
	draw_rect(48,49,55,56,WHITE);
	draw_rect(49,50,54,55,WHITE);
	draw_rect(50,51,53,54,WHITE);
	draw_rect(51,52,52,53,WHITE);
	draw_rect(52,53,51,52,WHITE);
	draw_rect(53,54,50,51,WHITE);
	draw_rect(54,55,49,50,WHITE);
	//top
	draw_rect(11,46,24,25,WHITE);
	draw_rect(12,47,23,24,WHITE);
	draw_rect(13,48,22,23,WHITE);
	draw_rect(14,49,21,22,WHITE);
	draw_rect(15,50,20,21,WHITE);
	draw_rect(16,51,19,20,WHITE);
	draw_rect(17,52,18,19,WHITE);
	draw_rect(18,53,17,18,WHITE);
	draw_rect(19,54,16,17,WHITE);
	draw_rect(20,55,15,16,WHITE);
	draw_rect(21,56,14,15,WHITE);
	//white
	draw_rect(12,45,24,25,SKYBLUE);
	draw_rect(13,46,23,24,SKYBLUE);
	draw_rect(14,47,22,23,SKYBLUE);
	draw_rect(15,48,21,22,SKYBLUE);
	draw_rect(16,49,20,21,SKYBLUE);
	draw_rect(17,50,19,20,SKYBLUE);
	draw_rect(18,51,18,19,SKYBLUE);
	draw_rect(19,52,17,18,SKYBLUE);
	draw_rect(20,53,16,17,SKYBLUE);
	draw_rect(21,54,15,16,SKYBLUE);
	//hook
	draw_rect(35,42,9,14,WHITE);
	draw_rect(36,41,6,9,WHITE);
	draw_rect(37,40,4,5,WHITE);
	//frame
	draw_rect(27,38,35,48,CHOCO);
	draw_rect(28,36,37,46,BLACK);
}

// Drawing 4 - Battery===============================================================================
void draw_batteryframe(void){
	draw_rect(10,35,268,308,WHITE); //frame
	draw_rect(18,27,263,268,WHITE); //top polar
	draw_rect(18,27,308,313,WHITE); //bottom polar
}

void draw_batterypolar(uint16_t colour){
	draw_rect(12,33,270,306,colour); //colour frame
	draw_rect(17,28,298,301,WHITE); //minus sign
	draw_rect(17,28,278,281,WHITE); //plus sign vertical
	draw_rect(21,24,274,285,WHITE); //plus sign horizontal
}

// Drawing 5 - Busbar Design (Lightning)=============================================================
void draw_busbar_dark(){ //Remove all drawing on the busbar column
	draw_rect(9,29,105,136,BLACK);
}

void draw_busbar(uint16_t colour){ //Full Lightning (Animation 1)
	//top half
	draw_rect(25,26,105,106,colour);
	draw_rect(24,26,106,107,colour);
	draw_rect(23,25,107,108,colour);
	draw_rect(22,25,108,109,colour);
	draw_rect(21,24,109,110,colour);
	draw_rect(20,24,110,111,colour);
	draw_rect(19,23,111,112,colour);
	draw_rect(18,23,112,113,colour);
	draw_rect(17,22,113,114,colour);
	draw_rect(16,22,114,115,colour);
	draw_rect(15,21,115,116,colour);
	draw_rect(14,21,116,117,colour);
	draw_rect(13,20,117,118,colour);
	//middle half
	draw_rect(12,29,118,119,colour);
	draw_rect(11,28,119,120,colour);
	draw_rect(10,27,120,121,colour);
	draw_rect(9,26,121,122,colour);
	//last half
	draw_rect(17,25,122,123,colour);
	draw_rect(17,24,123,124,colour);
	draw_rect(16,23,124,125,colour);
	draw_rect(16,22,125,126,colour);
	draw_rect(15,21,126,127,colour);
	draw_rect(15,20,127,128,colour);
	draw_rect(14,19,128,129,colour);
	draw_rect(14,18,129,130,colour);
	draw_rect(13,17,130,131,colour);
	draw_rect(13,16,131,132,colour);
	draw_rect(12,15,132,133,colour);
	draw_rect(12,14,133,134,colour);
	draw_rect(11,13,134,135,colour);
	draw_rect(11,12,135,136,colour);
	}

void draw_busbar2(uint16_t colour){ //Bottom slice of Lightning (Animation 2)
	draw_rect(14,19,105,106,colour);
	draw_rect(14,18,106,107,colour);
	draw_rect(13,17,107,108,colour);
	draw_rect(13,16,108,109,colour);
	draw_rect(12,15,109,110,colour);
	draw_rect(12,14,110,111,colour);
	draw_rect(11,13,111,112,colour);
	draw_rect(11,12,112,113,colour);
	}

void draw_busbar3(uint16_t colour){ //Half of Lightning (Animation 3)
	//middle half
	draw_rect(12,29,105,106,colour);
	draw_rect(11,28,106,107,colour);
	draw_rect(10,27,107,108,colour);
	draw_rect(9,26,108,109,colour);
	//last half
	draw_rect(17,25,109,110,colour);
	draw_rect(17,24,110,111,colour);
	draw_rect(16,23,111,112,colour);
	draw_rect(16,22,112,113,colour);
	draw_rect(15,21,113,114,colour);
	draw_rect(15,20,114,115,colour);
	draw_rect(14,19,115,116,colour);
	draw_rect(14,18,116,117,colour);
	draw_rect(13,17,117,118,colour);
	draw_rect(13,16,118,119,colour);
	draw_rect(12,15,119,120,colour);
	draw_rect(12,14,120,121,colour);
	draw_rect(11,13,121,122,colour);
	draw_rect(11,12,122,123,colour);
}

void draw_busbar4(uint16_t colour){	//Three Quarter of Lightning (Animation 4)
	draw_rect(19,23,105,106,colour);
	draw_rect(18,23,106,107,colour);
	draw_rect(17,22,107,108,colour);
	draw_rect(16,22,108,109,colour);
	draw_rect(15,21,109,110,colour);
	draw_rect(14,21,110,111,colour);
	draw_rect(13,20,111,112,colour);
	//middle half
	draw_rect(12,29,112,113,colour);
	draw_rect(11,28,113,114,colour);
	draw_rect(10,27,114,115,colour);
	draw_rect(9,26,115,116,colour);
	//last half
	draw_rect(17,25,116,117,colour);
	draw_rect(17,24,117,118,colour);
	draw_rect(16,23,118,119,colour);
	draw_rect(16,22,119,120,colour);
	draw_rect(15,21,120,121,colour);
	draw_rect(15,20,121,122,colour);
	draw_rect(14,19,122,123,colour);
	draw_rect(14,18,123,124,colour);
	draw_rect(13,17,124,125,colour);
	draw_rect(13,16,125,126,colour);
	draw_rect(12,15,126,127,colour);
	draw_rect(12,14,127,128,colour);
	draw_rect(11,13,128,129,colour);
	draw_rect(11,12,129,130,colour);
}

//Drawing 6 - Mains Design (A socket)================================================================
void draw_mains(void){
	draw_rect(125,145,107,129,WHITE);
	draw_rect(128,132,122,125,BLACK);
	draw_rect(138,142,122,125,BLACK);
	draw_rect(134,136,115,120,BLACK);
	draw_rect(140,143,110,115,BLACK);
	draw_rect(141,142,111,114,RED);
}

//Drawing 7 - Wind Design (3 slices of wind)=========================================================
void draw_wind(uint16_t colour){
	//Top slice of the wind=============================================
	draw_rect(34,40,166,167,colour);
	draw_rect(30,44,167,168,colour);
	draw_rect(27,47,168,169,colour);
	draw_rect(24,49,169,170,colour);
	draw_rect(22,82,170,171,colour);
	draw_rect(20,36,171,172,colour);
	draw_rect(18,32,172,173,colour);
	draw_rect(17,28,173,174,colour);
	draw_rect(16,25,174,175,colour);
	draw_rect(15,22,175,176,colour);
	draw_rect(14,20,176,177,colour);
	draw_rect(14,18,177,178,colour);
	draw_rect(13,16,178,179,colour);
	draw_rect(13,15,179,180,colour);
	draw_rect(13,14,180,181,colour);
	draw_rect(55,80,171,172,colour);
	draw_rect(57,77,172,173,colour);
	draw_rect(60,74,173,174,colour);
	draw_rect(64,70,174,175,colour);
	draw_rect(68,84,179,170,colour);
	draw_rect(72,86,168,169,colour);
	draw_rect(76,87,167,168,colour);
	draw_rect(79,88,166,167,colour);
	draw_rect(82,89,165,166,colour);
	draw_rect(84,90,164,165,colour);
	draw_rect(86,90,163,164,colour);
	draw_rect(88,91,162,163,colour);
	draw_rect(89,91,161,162,colour);
	draw_rect(90,91,160,161,colour);
	//Middle slice of the wind==========================================
	draw_rect(34,40,176,177,colour);
	draw_rect(30,44,177,178,colour);
	draw_rect(27,47,178,179,colour);
	draw_rect(24,49,179,180,colour);
	draw_rect(22,82,180,181,colour);
	draw_rect(20,36,181,182,colour);
	draw_rect(18,32,182,183,colour);
	draw_rect(17,28,183,184,colour);
	draw_rect(16,25,184,185,colour);
	draw_rect(15,22,185,186,colour);
	draw_rect(14,20,186,187,colour);
	draw_rect(14,18,187,188,colour);
	draw_rect(13,16,188,189,colour);
	draw_rect(13,15,189,190,colour);
	draw_rect(13,14,190,191,colour);
	draw_rect(55,80,181,182,colour);
	draw_rect(57,77,182,183,colour);
	draw_rect(60,74,183,184,colour);
	draw_rect(64,70,184,185,colour);
	draw_rect(68,84,189,180,colour);
	draw_rect(72,86,178,179,colour);
	draw_rect(76,87,177,178,colour);
	draw_rect(79,88,176,177,colour);
	draw_rect(82,89,175,176,colour);
	draw_rect(84,90,174,175,colour);
	draw_rect(86,90,173,174,colour);
	draw_rect(88,91,172,173,colour);
	draw_rect(89,91,171,172,colour);
	draw_rect(90,91,170,171,colour);
	//Bottom slice of the wind==========================================
	draw_rect(34,40,186,187,colour);
	draw_rect(30,44,187,188,colour);
	draw_rect(27,47,188,189,colour);
	draw_rect(24,49,189,190,colour);
	draw_rect(22,82,190,191,colour);
	draw_rect(20,36,191,192,colour);
	draw_rect(18,32,192,193,colour);
	draw_rect(17,28,193,194,colour);
	draw_rect(16,25,194,195,colour);
	draw_rect(15,22,195,196,colour);
	draw_rect(14,20,196,197,colour);
	draw_rect(14,18,197,198,colour);
	draw_rect(13,16,198,199,colour);
	draw_rect(13,15,199,200,colour);
	draw_rect(13,14,200,201,colour);
	draw_rect(55,80,191,192,colour);
	draw_rect(57,77,192,193,colour);
	draw_rect(60,74,193,194,colour);
	draw_rect(64,70,194,195,colour);
	draw_rect(68,84,189,190,colour);
	draw_rect(72,86,188,189,colour);
	draw_rect(76,87,187,188,colour);
	draw_rect(79,88,186,187,colour);
	draw_rect(82,89,185,186,colour);
	draw_rect(84,90,184,185,colour);
	draw_rect(86,90,183,184,colour);
	draw_rect(88,91,182,183,colour);
	draw_rect(89,91,181,182,colour);
	draw_rect(90,91,180,181,colour);
}

void draw_wind2(uint16_t colour){
	//Top slice of the wind=============================================
	draw_rect(30,33,167,168,colour);
	draw_rect(27,33,168,169,colour);
	draw_rect(24,33,169,170,colour);
	draw_rect(22,33,170,171,colour);
	draw_rect(20,33,171,172,colour);
	draw_rect(18,32,172,173,colour);
	draw_rect(17,28,173,174,colour);
	draw_rect(16,25,174,175,colour);
	draw_rect(15,22,175,176,colour);
	draw_rect(14,20,176,177,colour);
	draw_rect(14,18,177,178,colour);
	draw_rect(13,16,178,179,colour);
	draw_rect(13,15,179,180,colour);
	draw_rect(13,14,180,181,colour);
	//Middle slice of the wind==========================================
	draw_rect(30,33,177,178,colour);
	draw_rect(27,33,178,179,colour);
	draw_rect(24,33,179,180,colour);
	draw_rect(22,33,180,181,colour);
	draw_rect(20,33,181,182,colour);
	draw_rect(18,32,182,183,colour);
	draw_rect(17,28,183,184,colour);
	draw_rect(16,25,184,185,colour);
	draw_rect(15,22,185,186,colour);
	draw_rect(14,20,186,187,colour);
	draw_rect(14,18,187,188,colour);
	draw_rect(13,16,188,189,colour);
	draw_rect(13,15,189,190,colour);
	draw_rect(13,14,190,191,colour);
	//Bottom slice of the wind==========================================
	draw_rect(30,33,187,188,colour);
	draw_rect(27,33,188,189,colour);
	draw_rect(24,33,189,190,colour);
	draw_rect(22,33,190,191,colour);
	draw_rect(20,33,191,192,colour);
	draw_rect(18,32,192,193,colour);
	draw_rect(17,28,193,194,colour);
	draw_rect(16,25,194,195,colour);
	draw_rect(15,22,195,196,colour);
	draw_rect(14,20,196,197,colour);
	draw_rect(14,18,197,198,colour);
	draw_rect(13,16,198,199,colour);
	draw_rect(13,15,199,200,colour);
	draw_rect(13,14,200,201,colour);
}

void draw_wind3(uint16_t colour){
	//Top slice of the wind=============================================
	draw_rect(34,40,166,167,colour);
	draw_rect(30,44,167,168,colour);
	draw_rect(27,47,168,169,colour);
	draw_rect(24,49,169,170,colour);
	draw_rect(22,53,170,171,colour);
	draw_rect(20,36,171,172,colour);
	draw_rect(18,32,172,173,colour);
	draw_rect(17,28,173,174,colour);
	draw_rect(16,25,174,175,colour);
	draw_rect(15,22,175,176,colour);
	draw_rect(14,20,176,177,colour);
	draw_rect(14,18,177,178,colour);
	draw_rect(13,16,178,179,colour);
	draw_rect(13,15,179,180,colour);
	draw_rect(13,14,180,181,colour);
	//Middle slice of the wind==========================================
	draw_rect(34,40,176,177,colour);
	draw_rect(30,44,177,178,colour);
	draw_rect(27,47,178,179,colour);
	draw_rect(24,49,179,180,colour);
	draw_rect(22,53,180,181,colour);
	draw_rect(20,36,181,182,colour);
	draw_rect(18,32,182,183,colour);
	draw_rect(17,28,183,184,colour);
	draw_rect(16,25,184,185,colour);
	draw_rect(15,22,185,186,colour);
	draw_rect(14,20,186,187,colour);
	draw_rect(14,18,187,188,colour);
	draw_rect(13,16,188,189,colour);
	draw_rect(13,15,189,190,colour);
	draw_rect(13,14,190,191,colour);
	//Bottom slice of the wind==========================================
	draw_rect(34,40,186,187,colour);
	draw_rect(30,44,187,188,colour);
	draw_rect(27,47,188,189,colour);
	draw_rect(24,49,189,190,colour);
	draw_rect(22,53,190,191,colour);
	draw_rect(20,36,191,192,colour);
	draw_rect(18,32,192,193,colour);
	draw_rect(17,28,193,194,colour);
	draw_rect(16,25,194,195,colour);
	draw_rect(15,22,195,196,colour);
	draw_rect(14,20,196,197,colour);
	draw_rect(14,18,197,198,colour);
	draw_rect(13,16,198,199,colour);
	draw_rect(13,15,199,200,colour);
	draw_rect(13,14,200,201,colour);
}

void draw_wind4(uint16_t colour){
	//Top slice of the wind=============================================
	draw_rect(34,40,166,167,colour);
	draw_rect(30,44,167,168,colour);
	draw_rect(27,47,168,169,colour);
	draw_rect(24,49,169,170,colour);
	draw_rect(22,73,170,171,colour);
	draw_rect(20,36,171,172,colour);
	draw_rect(18,32,172,173,colour);
	draw_rect(17,28,173,174,colour);
	draw_rect(16,25,174,175,colour);
	draw_rect(15,22,175,176,colour);
	draw_rect(14,20,176,177,colour);
	draw_rect(14,18,177,178,colour);
	draw_rect(13,16,178,179,colour);
	draw_rect(13,15,179,180,colour);
	draw_rect(13,14,180,181,colour);
	draw_rect(55,73,171,172,colour);
	draw_rect(57,73,172,173,colour);
	draw_rect(60,73,173,174,colour);
	draw_rect(64,70,174,175,colour);
	draw_rect(68,73,179,170,colour);
	draw_rect(72,73,168,169,colour);
	//Middle slice of the wind==========================================
	draw_rect(34,40,176,177,colour);
	draw_rect(30,44,177,178,colour);
	draw_rect(27,47,178,179,colour);
	draw_rect(24,49,179,180,colour);
	draw_rect(22,73,180,181,colour);
	draw_rect(20,36,181,182,colour);
	draw_rect(18,32,182,183,colour);
	draw_rect(17,28,183,184,colour);
	draw_rect(16,25,184,185,colour);
	draw_rect(15,22,185,186,colour);
	draw_rect(14,20,186,187,colour);
	draw_rect(14,18,187,188,colour);
	draw_rect(13,16,188,189,colour);
	draw_rect(13,15,189,190,colour);
	draw_rect(13,14,190,191,colour);
	draw_rect(55,73,181,182,colour);
	draw_rect(57,73,182,183,colour);
	draw_rect(60,73,183,184,colour);
	draw_rect(64,70,184,185,colour);
	draw_rect(68,73,189,180,colour);
	draw_rect(72,73,178,179,colour);
	//Bottom slice of the wind==========================================
	draw_rect(34,40,186,187,colour);
	draw_rect(30,44,187,188,colour);
	draw_rect(27,47,188,189,colour);
	draw_rect(24,49,189,190,colour);
	draw_rect(22,73,190,191,colour);
	draw_rect(20,36,191,192,colour);
	draw_rect(18,32,192,193,colour);
	draw_rect(17,28,193,194,colour);
	draw_rect(16,25,194,195,colour);
	draw_rect(15,22,195,196,colour);
	draw_rect(14,20,196,197,colour);
	draw_rect(14,18,197,198,colour);
	draw_rect(13,16,198,199,colour);
	draw_rect(13,15,199,200,colour);
	draw_rect(13,14,200,201,colour);
	draw_rect(55,73,191,192,colour);
	draw_rect(57,73,192,193,colour);
	draw_rect(60,73,193,194,colour);
	draw_rect(64,70,194,195,colour);
	draw_rect(68,73,189,190,colour);
	draw_rect(72,73,188,189,colour);
}

//Drawing 8 - Solar Design (Circle with 8 triangles)=================================================
void draw_solar(uint16_t colour){
	//1st triangle======================================================
	draw_rect(183,184,169,170,colour);
	draw_rect(182,185,170,171,colour);
	draw_rect(181,186,171,172,colour);
	draw_rect(180,187,172,173,colour);
	//2nd triangle======================================================
	draw_rect(183,184,196,197,colour);
	draw_rect(182,185,195,196,colour);
	draw_rect(181,186,194,195,colour);
	draw_rect(180,187,193,194,colour);
	//3rd triangle======================================================
	draw_rect(172,173,180,187,colour);
	draw_rect(171,172,181,186,colour);
	draw_rect(170,171,182,185,colour);
	draw_rect(169,170,183,184,colour);
	//4th triangle======================================================
	draw_rect(194,195,180,187,colour);
	draw_rect(195,196,181,186,colour);
	draw_rect(196,197,182,185,colour);
	draw_rect(197,198,183,184,colour);
	//5th triangle======================================================
	draw_rect(190,195,171,172,colour);
	draw_rect(191,195,172,173,colour);
	draw_rect(192,195,173,174,colour);
	draw_rect(193,195,174,175,colour);
	draw_rect(194,195,175,176,colour);
	//6th triangle======================================================
	draw_rect(190,195,195,196,colour);
	draw_rect(191,195,194,195,colour);
	draw_rect(192,195,193,194,colour);
	draw_rect(193,195,192,193,colour);
	draw_rect(194,195,191,192,colour);
	//7th triangle======================================================
	draw_rect(170,171,191,192,colour);
	draw_rect(170,172,192,193,colour);
	draw_rect(170,173,193,194,colour);
	draw_rect(170,174,194,195,colour);
	draw_rect(170,175,195,196,colour);
	//8th triangle======================================================
	draw_rect(170,175,171,172,colour);
	draw_rect(170,174,172,173,colour);
	draw_rect(170,173,173,174,colour);
	draw_rect(170,172,174,175,colour);
	draw_rect(170,171,175,176,colour);
	//circle============================================================
	draw_rect(181,186,177,179,colour);
	draw_rect(179,188,179,181,colour);
	draw_rect(177,190,181,185,colour);
	draw_rect(179,188,185,187,colour);
	draw_rect(181,186,187,189,colour);
	}

void draw_solar2(uint16_t colour){ //slanted triangle(for animation)====
	//circle============================================================
	draw_rect(181,186,177,179,colour);
	draw_rect(179,188,179,181,colour);
	draw_rect(177,190,181,185,colour);
	draw_rect(179,188,185,187,colour);
	draw_rect(181,186,187,189,colour);
	//1st triangle======================================================
	draw_rect(178,179,169,170,colour);
	draw_rect(177,180,170,171,colour);
	draw_rect(177,181,171,172,colour);
	draw_rect(177,182,172,173,colour);
	draw_rect(176,179,173,174,colour);
	draw_rect(176,177,174,175,colour);
	//2nd triangle======================================================
	draw_rect(188,189,169,170,colour);
	draw_rect(187,190,170,171,colour);
	draw_rect(186,190,171,172,colour);
	draw_rect(185,190,172,173,colour);
	draw_rect(188,191,173,174,colour);
	draw_rect(190,191,174,175,colour);
	//3rd triangle======================================================
	draw_rect(177,178,196,197,colour);
	draw_rect(176,179,195,196,colour);
	draw_rect(176,180,194,195,colour);
	draw_rect(176,181,193,194,colour);
	draw_rect(175,178,192,193,colour);
	draw_rect(175,176,191,192,colour);
	//4th triangle======================================================
	draw_rect(188,189,196,197,colour);
	draw_rect(187,190,195,196,colour);
	draw_rect(186,190,194,195,colour);
	draw_rect(185,190,193,194,colour);
	draw_rect(188,191,192,193,colour);
	draw_rect(190,191,191,192,colour);
	//5th triangle======================================================
	draw_rect(172,173,176,179,colour);
	draw_rect(171,172,176,181,colour);
	draw_rect(170,171,177,181,colour);
	draw_rect(168,170,177,180,colour);
	draw_rect(167,168,178,179,colour);
	//6th triangle======================================================
	draw_rect(172,173,186,189,colour);
	draw_rect(171,172,184,189,colour);
	draw_rect(170,171,184,188,colour);
	draw_rect(168,170,185,188,colour);
	draw_rect(167,168,186,187,colour);
	//7th triangle======================================================
	draw_rect(193,194,176,179,colour);
	draw_rect(194,195,176,181,colour);
	draw_rect(195,196,177,181,colour);
	draw_rect(196,198,177,180,colour);
	draw_rect(198,199,178,179,colour);
	//8th triangle======================================================
	draw_rect(193,194,186,189,colour);
	draw_rect(194,195,184,189,colour);
	draw_rect(195,196,184,188,colour);
	draw_rect(196,198,185,188,colour);
	draw_rect(198,199,186,187,colour);
	}

// Drawing 9 - Smart Meter word (Animation)==========================================================
void draw_smart(uint16_t colour1,uint16_t colour2,uint16_t colour3,uint16_t colour4,uint16_t colour5){
	pictorDrawS("S", (point){70,10}, colour1, BLACK , Mash,3);
	pictorDrawS("M", (point){93,10}, colour2, BLACK , Mash,3);
	pictorDrawS("A", (point){116,10}, colour3, BLACK , Mash,3);
	pictorDrawS("R", (point){139,10}, colour4, BLACK , Mash,3);
	pictorDrawS("T", (point){161,10}, colour5, BLACK , Mash,3);
}

void draw_meter(uint16_t colour1,uint16_t colour2,uint16_t colour3,uint16_t colour4,uint16_t colour5){
	pictorDrawS("M", (point){70,40}, colour1, BLACK , Mash,3);
	pictorDrawS("E", (point){93,40}, colour2, BLACK , Mash,3);
	pictorDrawS("T", (point){116,40}, colour3, BLACK , Mash,3);
	pictorDrawS("E", (point){139,40}, colour4, BLACK , Mash,3);
	pictorDrawS("R", (point){161,40}, colour5, BLACK , Mash,3);
	pictorDrawS("G", (point){190,15}, WHITE, BLACK , Mash,6);
}

//Function for battery///////////////////////////////////////////////////////////////////////////////
//Charging state========================================================
void charging(void)
{
   *battery_value = *battery_value + 1;
	draw_batterypolar(YELLOW);
	PORTD |= _BV(1);// On Charge battery
	PORTD &= ~_BV(3);// Off discharge battery
	display_value(44,273,charge,blank); //Battery charging
}

//Discharging state=====================================================
void discharging(void)
{
	*battery_value = *battery_value - 1;
	draw_batterypolar(GREEN);
	PORTD &= ~_BV(1);// Off Charge battery
	PORTD |= _BV(3);// On discharge battery
	display_value(44,273,discharge,blank); //Battery discharging
}

//Battery turn off======================================================
void battery_off(void)
{
	draw_batterypolar(BLACK);
	PORTD &= ~_BV(1);// Off Charge battery
	PORTD &= ~_BV(3);// Off discharge battery
	display_value(44,273,off,blank); //Battery Off
}

//Display battery value=================================================
void battery_display(void)
{
	char battery_value_string[bit];
	int actual_battery=*battery_value;
	itoa(actual_battery,battery_value_string,10);
	display_value(58,293,battery_value_string,A_per_S);//Battery Value
}

// IL MATTO SYSTEM FUNCTION /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_adc(void){
	ADMUX = 0;
	ADMUX |= _BV(ADLAR); /* F_ADC = F_CPU/64 */
	ADCSRA |= _BV(ADEN); /* Enable ADC */
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
}

void channel_adc(uint8_t n)
{
	ADMUX= n;
}

uint16_t read_adc(void)
{
	ADCSRA |= _BV(ADSC); /* Start Conversions */
	while (ADCSRA&_BV(ADSC));
	return ADC;
}

void display_description(int x_axis, int y_axis, char description[]){
	display.x=x_axis;
	display.y=y_axis;
	display_string(description);
}

void display_value(int x_axis, int y_axis, char value[], char unit[]){
	display.x=x_axis;
	display.y=y_axis;
	display_string(value);
	display_string(unit);
}

void init_pwm(void)
{
	TCCR2A =_BV(COM2A1)|_BV(WGM20);//
	TCCR2B= _BV(CS20);
	OCR2A=0;
	DDRD |= _BV(7);
}

//Main Function
int main ()
{
	// PIN & IL MATTO INITIALISATION //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Power COmsumption Management
	power_spi_disable();

	//Initialise adc
	init_adc();

	//LCD Initialise
	init_pwm();
	init_lcd();

	// Pin Configuration

	DDRA &= ~_BV(1);
	DDRA &= ~_BV(3);
	DDRA &= ~_BV(5);
	DDRD |= _BV(0);
	DDRD |= _BV(2);
	DDRD |= _BV(4);

	DDRD |= _BV(1);
	DDRD |= _BV(3);


	// Value Initialisation //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//voltage
	int *voltage;
	uint16_t resultvoltage;
	uint32_t busvoltage,busvoltagedec;
	voltage=(int*)malloc(bit*sizeof(int));

	//current
	int *current;
	uint16_t resultcurrent;
	uint32_t buscurrent,buscurrentdec;
	current=(int*)malloc(bit*sizeof(int));

	   //power and energy*****************************************************************************************************************
    float *power;
    float power_new,power_old=0;
    power=(float*)malloc(bit*sizeof(float));

	//wind
	uint16_t resultwind;
	float *wind_value;
	float wind_value_new,wind_value_old=0;
	wind_value=(float*)malloc(bit*sizeof(float));

	//solar
	float *solar_value;
	uint16_t resultsolar;
	float solar_value_new,solar_value_old=0;
	solar_value=(float*)malloc(bit*sizeof(float));

	//main
	float *main_value;
	float main_value_new,main_value_old=0;
	main_value=(float*)malloc(bit*sizeof(float));

	//Battery
	battery_value=(float*)malloc(bit*sizeof(float));

	// LAYOUT STRING STORAGE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Title
	char title[]="TEAM G SMART METER";

	//Description
	char Busbar[]="=BUSBAR=";
	char VBusbar[]="V:";
	char IBusbar[]="I:";
	char Wind[]="=WIND=";
	char Solar[]="=SOLAR=";
	char Mains[]="=MAINS=";
	char Using[]="Using:";
	char Used[]="Used:";
	char Battery[]="=BATTERY=";
	char Load1[]="Load 1:";
	char Load2[]="Load 2:";
	char Load3[]="Load 3:";
	char Total[]="Total:";
	char currentlabel[]="I:";
	char Load[]="=LOAD=";
	char currentt[]="Current:";

	//Value representation String
	char high[]="On ";
	char low[] ="Off";

	//Unit String
	char Vrms[] = " V  ";
	char Irms[] =" mA  ";
	char Ampere[] =" A   ";
	char kWh[] =" kWh   ";
	char Watt[] = " W    ";

	//INTERFACE LAYOUT//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Title Team G Smart Meter
	draw_smeter();
	draw_vline(1,239,85);
	draw_vline(1,239,145);
	draw_vline(1,239,238);
	draw_hline(85,145,120);
	draw_hline(145,320,120);

	//Busbar Representation Section
	display_description(37,90,Busbar);
	display_description(42,110,VBusbar);
	display_description(42,125,IBusbar);

	//Mains Representation Section
	draw_mains();
	display_description(165,90,Mains);
	display_description(151,110,Using);
	display_description(151,125,Used);

	//wind Representation Section
	display_description(42,150,Wind); //Wind
	display_description(10,210,currentt);
	display_description(10,225,Total);//Total wind

	//solar Representation Section
	display_description (165,150,Solar); // Solar
	display_description(135,210,currentt);
	display_description(135,225,Total);//Total solar

	//Battery Representation Section
	display_description(38,245,Battery);
	draw_batteryframe();
	display_description(44,293,currentlabel);

	//Load Representation Section
	display_description(171,245,Load);
	draw_square(223,263,10,WHITE);
	draw_square(223,283,10,WHITE);
	draw_square(223,303,10,WHITE);
	display_description(140,265,Load1); //Load1
	display_description(140,285,Load2);//Load2
	display_description(140,305,Load3); //Load3

	// Value String Storage ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Value+Unit display
	char voltagestring[bit];
	char voltagestringdecimal[bit];
	char currentstring[bit];
	char currentstringdecimal[bit];
	char windstring[bit];
	char windstringdecimal[bit];
	char totalwindstring[bit];
	char totalwindstringdecimal[bit];
	char solarstring[bit];
	char solarstringdecimal[bit];
	char totalsolarstring[bit];
	char totalsolarstringdecimal[bit];
	char mainstring[bit];
	char mainstringdecimal[bit];
	char totalmainstring[bit];
	char totalmainstringdecimal[bit];
	char powerstring[bit];
	char powerstringdecimal[bit];
	char totalpowerstring[bit];
	char totalpowerstringdecimal[bit];
	char onedecimalpoint[]=".";
	char twodecimalpoint[]=".0";
	char threedecimalpoint[]=".00";

	//initialize battery
	int tot_battery_value = 0;
	*battery_value=0;
	battery_off();
	int i=0;
	int j=87;

	// CONVERTION SYSTEM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(;;){
		//convert to string
		//voltage bus
		channel_adc(0);
		for(i=0;i<=9;i++){
			float Max_voltage=0;
			resultvoltage=read_adc();
			if(resultvoltage>0){
			*voltage=(resultvoltage*3.3/1024)*1.5*1000;
			if (*voltage>=Max_voltage) {

				Max_voltage=*current;
			   }
			else
			  {*voltage=Max_voltage;}

			}
			else{*voltage=0;}
			_delay_ms(1);
		}

		busvoltage=*voltage/1000;
		busvoltagedec=*voltage%1000;
		itoa(busvoltage,voltagestring,10);
		itoa(busvoltagedec,voltagestringdecimal,10);
		if(busvoltagedec<10)
		{
			strcat(voltagestring,threedecimalpoint);
			strcat(voltagestring,voltagestringdecimal);
		}
		else if(busvoltagedec<100 &&busvoltagedec>=10)
		{
			strcat(voltagestring,twodecimalpoint);
			strcat(voltagestring,voltagestringdecimal);
		}
		else
		{
			strcat(voltagestring,onedecimalpoint);
			strcat(voltagestring,voltagestringdecimal);
		}

		display_value(55,110,voltagestring,Vrms); //VBus Bar

		ADMUX =0;
		channel_adc(2);
		resultcurrent=0;

		for(i=0;i<=9;i++){
			float Max_current=0;
			resultcurrent=read_adc();
			if(resultcurrent>0){
			*current=(((resultcurrent*3.3/1024))*2.6627+0.7092)*1000;

				if (*current>=Max_current) {

					Max_current=*current;
				}
				else
				{*current=Max_current;}
			}

		else{*current=0;}

			_delay_ms(1);
		}
		buscurrent=*current/1000;
		buscurrentdec=*current%1000;
		itoa(buscurrent,currentstring,10);
		itoa(buscurrentdec,currentstringdecimal,10);
		if(buscurrentdec<10)
		{
			strcat(currentstring,threedecimalpoint);
			strcat(currentstring,currentstringdecimal);
		}
		else if(buscurrentdec<100 &&buscurrentdec>=10)
		{
			strcat(currentstring,twodecimalpoint);
			strcat(currentstring,currentstringdecimal);
		}
		else
		{
			strcat(currentstring,onedecimalpoint);
			strcat(currentstring,currentstringdecimal);
		}
		display_value(55,125,currentstring,Ampere); //IBusBar

		*power=(*current)*(*voltage);
        int buspower=*power/1000;
        int buspowerdec=*power%1000;
        itoa(buspower,powerstring,10);
        itoa(buspowerdec,powerstringdecimal,10);
        if(buspowerdec<10)
        {
            strcat(powerstring,threedecimalpoint);
            strcat(powerstring,powerstringdecimal);
        }
        else if(buspowerdec<100 &&buspowerdec>=10)
        {
            strcat(powerstring,twodecimalpoint);
            strcat(powerstring,powerstringdecimal);
        }
        else
        {
            strcat(powerstring,onedecimalpoint);
            strcat(powerstring,powerstringdecimal);
        }
        // display_value(55,125,powerstring,Watt); //IBusBar

		ADMUX =0;

		//wind
		resultwind=0;
		channel_adc(4);
		resultwind=read_adc();
		*wind_value=(resultwind*3.3/1024)*2.05*0.511;
		int windpow3=(*wind_value)*1000;
		int actual_wind=windpow3/1000;
		int winddec = windpow3%1000;
		itoa(actual_wind,windstring,10);
		itoa(winddec,windstringdecimal,10);
		if(winddec<10)
		{
			strcat(windstring,threedecimalpoint);
			strcat(windstring,windstringdecimal);
		}
		else if(winddec<100 &&winddec>=10)
		{
			strcat(windstring,twodecimalpoint);
			strcat(windstring,windstringdecimal);
		}
		else
		{
			strcat(windstring,onedecimalpoint);
			strcat(windstring,windstringdecimal);
		}
		display_value(60,210,windstring,Ampere); //Wind

		//total wind
		wind_value_new=(*wind_value)+wind_value_old;
		wind_value_old = wind_value_new;
		uint32_t totalwindk=wind_value_new*10;
		uint32_t totalwind= totalwindk/10;
		uint32_t totalwinddec= totalwindk%10; //ISsue in insert decimal point
		itoa(totalwind,totalwindstring,10);
		itoa(totalwinddec,totalwindstringdecimal,10);
		strcat(totalwindstring,onedecimalpoint);
		strcat(totalwindstring,totalwindstringdecimal);

		display_value(60,225,totalwindstring,A_per_S);//Total wind

		ADMUX = 0;

		//solar
		*solar_value=0;
		channel_adc(6);
		resultsolar=read_adc();
		*solar_value=(resultsolar*3.3/1024)*1.1;
		int solarpow3=(*solar_value)*1000;
		uint32_t actual_solar=solarpow3/1000;
		uint32_t solardec = solarpow3%1000;
		itoa(actual_solar,solarstring,10);
		itoa(solardec,solarstringdecimal,10);
		if(solardec<10)
		{
			strcat(solarstring,threedecimalpoint);
			strcat(solarstring,solarstringdecimal);
		}
		else if(solardec<100 &&solardec>=10)
		{
			strcat(solarstring,twodecimalpoint);
			strcat(solarstring,solarstringdecimal);
		}
		else
		{
			strcat(solarstring,onedecimalpoint);
			strcat(solarstring,solarstringdecimal);
		}
		display_value(185,210,solarstring,Ampere); // Solar

		//total solar
		solar_value_new=(*solar_value)+solar_value_old;
		solar_value_old = solar_value_new;
		uint32_t totalsolark=solar_value_new*10;
		uint32_t totalsolar= (totalsolark)/10;
		uint32_t totalsolardec=0; //Issue in insert decimal point
		itoa(totalsolar,totalsolarstring,10);
		itoa(totalsolardec,totalsolarstringdecimal,10);
		strcat(totalsolarstring,onedecimalpoint);
		strcat(totalsolarstring,totalsolarstringdecimal);

		display_value(185,225,totalsolarstring,A_per_S);//Total solar

		//load1 theater
		float actual_load1;
		if(PINA & _BV(1)){
			draw_square(225,265,6,GREEN);
			actual_load1=0.8;
			PORTD |= _BV(0);
			display_value(190,265,high,blank); //Battery On/Off
		}
		else{
			draw_square(225,265,6,RED);
			actual_load1=0;
			PORTD &= ~_BV(0);
			display_value(190,265,low,blank); //Battery On/Off
		}

		//load2 life support
		float actual_load2;
		if(PINA & _BV(3)){
			draw_square(225,285,6,GREEN);
			actual_load2=1.8;
			PORTD |= _BV(2);
			display_value(190,285,high,blank); //Battery On/Off
		}
		else{
			draw_square(225,285,6,RED);
			actual_load2=0;
			PORTD &= ~_BV(2);
			display_value(190,285,low,blank); //Battery On/Off
		}

		//load3 ward
		float actual_load3;
		if(PINA & _BV(5)){
			draw_square(225,305,6,GREEN);
			PORTD |= _BV(4);
			actual_load3=1.4;
			display_value(190,305,high,blank); //Battery On/Off
		}
		else{
			draw_square(225,305,6,RED);
			actual_load3=0;
			PORTD &= ~_BV(4);
			display_value(190,305,low,blank); //Battery On/Off
		}

		float totalinput= *wind_value+*solar_value;
		float totalload = actual_load1+actual_load2+actual_load3;
		float left= totalinput-totalload;
		*main_value=0;

		//calculation=====================================================================================================
		if(busvoltage<=0.05){
			*main_value=0;
			battery_off();
		}
		else{
		    if(j<87){
			j++;
		    }
		    else{
		    	*power=(*current)*(*voltage);
		    	int buspower=*power/1000;
		    	int buspowerdec=*power%1000;
		    	itoa(buspower,powerstring,10);
		    	itoa(buspowerdec,powerstringdecimal,10);
		    	if(buspowerdec<10)
		    	{
		    		strcat(powerstring,threedecimalpoint);
		    		strcat(powerstring,powerstringdecimal);
		    	}
		    	else if(buspowerdec<100 &&buspowerdec>=10)
		    	{
		    		strcat(powerstring,twodecimalpoint);
		    		strcat(powerstring,powerstringdecimal);
		    	}
		    	else
		    	{
		    		strcat(powerstring,onedecimalpoint);
		    		strcat(powerstring,powerstringdecimal);
		    	}
		    	// display_value(55,125,powerstring,Watt); //IBusBar

				power_new=(*power/60)+power_old;
				power_old=power_new;
				uint32_t totalpowerk=power_new*10;
				uint32_t totalpower= totalpowerk/10;
				uint32_t totalpowerdec= totalpowerk%10; //ISsue in insert decimal point
				itoa(totalpower,totalpowerstring,10);
				itoa(totalpowerdec,totalpowerstringdecimal,10);
				strcat(totalpowerstring,onedecimalpoint);
				strcat(totalpowerstring,totalpowerstringdecimal);

				display_value(10,75,totalpowerstring,kWh);//energy display with battery

		       if (left>=1){
			  *main_value=0;
			  charging();
		        }
		      else if (left>0 && left<1){
			  *main_value=1-left;
			  charging();
		      }
		      else if (left==0){
			     if  (*battery_value>10){
				  *main_value=0;
				  battery_off();
			      }
			      else{
				  *main_value=1;
				   charging();
			       }
			    }
		      else if (left<0 && left>=(-1)){// -1<=left<0
			      if (*battery_value>10 && left<=(-0.9)){
				  *main_value=0;
				  discharging();
			       }
			      else{
				    if(*battery_value>0){
					*main_value=-left;
					battery_off();
				     }
				   else{
					 *main_value=1-left;
					  charging();
				    }
			    }
		    }
		      else if(left<=(-1) && left>=(-2)){//-2<=left<-1
			       if(*battery_value>10){
				   *main_value = -left-1;
			        discharging();
			       }
			       else if(*battery_value>=10){
				   *main_value = -left;
				   battery_off();
			       }
			       else{
				   *main_value = -left+1;
				   charging();
			        }
		        }
	       	  else if(left<=(-2) && left>=(-3)){//-3<=left<-2
			     if(*battery_value>10){
				*main_value = -left-1;
			    discharging();
			     }
			    else{
				*main_value = -left;
				battery_off();
			     }
		    }
		      else if(left<=(-3) && left>=(-4)){//-4<=left<-3
			     if(*battery_value>=1){
			    discharging();
			    *main_value = -left - 1;
			     }
			    else{
				     battery_off();
				   if(actual_load1==0){//when load 1 is off
					*main_value = 1.8;
				    }
				   else{
					*main_value = 2.6;
				    }
				   PORTD &= ~_BV(4);//turn off load 3
				  }
		        }
		      battery_display();
		      OCR2A=(*main_value*255)/3.3;
		      j=0;

			int mainpow3=(*main_value)*1000;
			uint32_t actual_main=mainpow3/1000;
			uint32_t maindec = mainpow3%1000;
			itoa(actual_main,mainstring,10);
			itoa(maindec,mainstringdecimal,10);
			if(maindec<10)
				{
				strcat(mainstring,threedecimalpoint);
				strcat(mainstring,mainstringdecimal);
				}
			else if(maindec<100 &&maindec>=10)
				{
				strcat(mainstring,twodecimalpoint);
				strcat(mainstring,mainstringdecimal);
				}
			else
				{
				strcat(mainstring,onedecimalpoint);
				strcat(mainstring,mainstringdecimal);
				}
				display_value(188,110,mainstring,Ampere); //Main
			  }
			//main used
			main_value_new=(*main_value)+main_value_old;
			main_value_old = main_value_new;
			uint32_t totalmaink=main_value_new*10;
			uint32_t totalmain= (totalmaink)/10;
			uint32_t totalmaindec=(totalmaink)%10;
			itoa(totalmain,totalmainstring,10);
			itoa(totalmaindec,totalmainstringdecimal,10);
			strcat(totalmainstring,onedecimalpoint);
			strcat(totalmainstring,totalmainstringdecimal);
			display_value(188,125,totalmainstring,A_per_S); //Mains Used
		}

		//Animation with 0.5 second delay ============================================================
		draw_wind(BLACK);
		draw_wind2(BLUE);
		draw_smart(WHITE,CYAN,GREEN,RED,MAGENTA);
		draw_meter(MAGENTA,WHITE,CYAN,GREEN,RED);
		draw_busbar_dark();
		draw_busbar2(YELLOW);
		draw_solar2(BLACK);
		draw_solar(RED);
		_delay_ms(100);
		draw_wind3(BLUE);
		draw_smart(MAGENTA,WHITE,CYAN,GREEN,RED);
		draw_meter(RED,MAGENTA,WHITE,CYAN,GREEN);
		draw_busbar_dark();
		draw_busbar3(YELLOW);
		draw_solar(BLACK);
		draw_solar2(ORANGE);
		_delay_ms(100);
		draw_wind4(BLUE);
		draw_smart(RED,MAGENTA,WHITE,CYAN,GREEN);
		draw_meter(GREEN,RED,MAGENTA,WHITE,CYAN);
		draw_busbar_dark();
		draw_busbar4(YELLOW);
		draw_solar2(BLACK);
		draw_solar(YELLOW);
		_delay_ms(100);
		draw_wind(BLUE);
		draw_smart(GREEN,RED,MAGENTA,WHITE,CYAN);
		draw_meter(CYAN,GREEN,RED,MAGENTA,WHITE);
		draw_busbar_dark();
		draw_busbar(YELLOW);
		draw_solar(BLACK);
		draw_solar2(RED);
		_delay_ms(100);
		draw_smart(CYAN,GREEN,RED,MAGENTA,WHITE);
		draw_meter(WHITE,CYAN,GREEN,RED,MAGENTA);
		draw_solar2(BLACK);
		draw_solar(ORANGE);
		_delay_ms(100);
		draw_smart(WHITE,WHITE,WHITE,WHITE,WHITE);
		draw_meter(WHITE,WHITE,WHITE,WHITE,WHITE);
		draw_solar(BLACK);
		draw_solar2(YELLOW);
	}

	//Free Memory
	free(voltage);
	free(current);
	free(battery_value);
	free(wind_value);
	free(solar_value);
	free(main_value);
	free(power);

	while(1);
	return 0;
}
