/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	Simple console print demo
	-- dovoto


---------------------------------------------------------------------------------*/
#include <nds.h>

#include <stdio.h>

volatile int frame = 0;

//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}
	
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	iprintf("Hi I'm Steve,\nand this is my first program\nfor DS\n");
	iprintf("\x1b[32mso while I'm here I guess I\nshould say ");
	iprintf("\x1b[32;1mHello World!\x1b[39m");
 
	while(1) {
	
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;

		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;columnH 
		iprintf("\x1b[8;0HHere's the number of the Frame\nthat you are looking at\n");
		iprintf("\x1b[10;0H\x1b[31;1m Frame = %d\x1b[39m",frame);
		iprintf("\x1b[12;0HSo entertaining right.\n");
		iprintf(" \x1b[14;0HTouch the screen and these\nchange\n");
		iprintf(" \x1b[16;0H\x1b[34;1m Touch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
		iprintf(" Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);	
		iprintf(" \x1b[18;0H\x1b[39mThe first column is the 'raw'\nvalue and the second isn't\nand I have no idea what the\ndiffernce is.");
	
	}

	return 0;
}
