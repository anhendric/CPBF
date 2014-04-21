#include "BFModuleWindow.h"
#include "PegTextStream.h"
#include "brainfuck.h"

#define IDB_RUN 2001

extern PegFont LuaFont2;
extern PegBitmap gbboutonBitmap;

static PegTextStream dmp;
static BFModuleWindow *env;

// Brainfuck input
void bf_in(unsigned char *ptr)
{
    while(1)
    {
        // Perform a message pump
        PegMessage pSend;
        while(env->MessageQueue()->PopNoIdle(&pSend)) 
        {
            int iReturn = env->Presentation()->DispatchMessage(env->Presentation(), &pSend);
            if (iReturn) return;
        }
        if (GetSystemMessage(&pSend,IM_RCVTMO_POL))
        {
            if (pSend.wType==HM_SYS_CLEAR) pSend.pTarget = env;
            
            if (pSend.wType==HM_SYS_CLOSE)
            {
                env->MessageQueue()->Push(pSend); 
                return;
            }
            
            // Return if any key has been pressed
            if (pSend.wType==PM_KEY && pSend.iData<=0xFF)
            {
                *ptr = pSend.iData;
                env->MessageQueue()->Push(pSend); 
                return;
            }
            
            env->MessageQueue()->Push(pSend);
        }
    }
}

// Brainfuck output
void bf_out(unsigned char *ptr)
{
    // Process all messages first (prevents from displaying this character before the character entered with an eventual previous input command)
    env->MessageQueue()->Flush();
    
    dmp << (char)(*ptr);
}

BFModuleWindow::BFModuleWindow(PegRect rect, CPMainFrame* frame):CPModuleWindow(rect,0,0,frame)
{
    tb = NULL;
    firstdrawn = false;
    env = this;
}

void BFModuleWindow::AddUI()
{
    PegRect r = GetToolbarButtonRect();
    tb = new PegEditBox(mReal);
    tb->SetFont(&LuaFont2);
    tb->SetScrollMode(WSM_AUTOVSCROLL);
    Add(tb);
    
    PegBitmapButton *b = new PegBitmapButton(r, &gbboutonBitmap,IDB_RUN);
    //PegTextButton* b = new PegTextButton(1,1, "Run", IDB_RUN,AF_ENABLED|TT_COPY);
	m_ui->AddToolbarButton(b);
	
	dmp.SetTarget(tb);
}

void BFModuleWindow::RunBrainfuck()
{
	unsigned short buffer[1024];
	unsigned char table[256] = {0};
	
	dmp << "\n";
	
	if(!tb->DataGet()) return;
	
	switch(brainfuck_compile(tb->DataGet(), buffer))
	{
	    case BF_ERR_MISSING_LOOP_START:
	        dmp << "Error: Missing [ symbol";
	        return;
        case BF_ERR_MISSING_LOOP_END:
	        dmp << "Error: Missing ] symbol";
            return;
	}
	
	BF_FUNCTION fptr = (BF_FUNCTION)buffer;
	
	CalcBusyDispON();
	fptr(table, bf_in, bf_out);
	CalcBusyDispOFF();
}

SIGNED BFModuleWindow::Message(const PegMessage &Mesg)
{
	switch(Mesg.wType)
  	{
  	    case PM_SIZE:
  	        if(tb)
            {
                tb->Resize(Mesg.Rect);
            }    
  	        break;
		case SIGNAL( IDB_RUN, PSF_CLICKED):
		    RunBrainfuck();
			break;
		default:								
			return CPModuleWindow::Message(Mesg);
 	}
 	return 0;
}

