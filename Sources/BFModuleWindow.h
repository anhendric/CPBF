#ifndef BF_MODULE_WINDOW_H
#define BF_MODULE_WINDOW_H

#include "ClassPad.h"

class BFModuleWindow: public CPModuleWindow
{
	public:
		BFModuleWindow(PegRect rect, CPMainFrame* frame);
		~BFModuleWindow() {}
		
		PegEditBox *tb;
		
		void RunBrainfuck();
		
		bool firstdrawn;
		unsigned short *ptr;
		
		SIGNED Message(const PegMessage &Mesg);
		void AddUI();
};

#endif
