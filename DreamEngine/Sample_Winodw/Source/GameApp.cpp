#include "AppBase.h"
#include "GameListener.h"

#if defined(_DEBUG) && defined(_WIN32)
    
//#pragma  comment(lib,  "D:/Visual Leak Detector/lib/Win32/vld.lib")
#endif  
 
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{   
	//CRoot rot;    
	CAppBase app;      
	CGameListener gameListener ;
	   
	app.run(&gameListener);         
	    
	app.shutDown();   
	return 0;     
}  