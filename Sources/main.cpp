#include "ClassPad.h"
#include "BFModuleWindow.h"

void PegAppInitialize(PegPresentationManager *pPresentation)
{
	// create some simple Windows: 
	PegRect Rect;
	Rect.Set(MAINFRAME_LEFT, MAINFRAME_TOP, MAINFRAME_RIGHT, MAINFRAME_BOTTOM);

	CPMainFrame *mw = new CPMainFrame(Rect);

	PegRect ChildRect = mw->FullAppRectangle();

	BFModuleWindow *sw = new BFModuleWindow(ChildRect, mw);
	
	mw->SetTopWindow(sw);
	mw->SetMainWindow(sw);
	
	pPresentation->Add(mw);
};


//////////////////////////////////////////////////////////////////

extern "C" char *ExtensionGetLang(ID_MESSAGE MessageNo)
{
	return "";
}

//////////////////////////////////////////////////////////////////
