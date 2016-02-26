#include "AnimationCompose.h"

int main(int argc, char* argv[])
{
	CString curName;
	CString curFloder;
	CAnimationCompose compose;
	CAnimationCompose::splitFlieNameAndFolder(argv[0], curName, curFloder);
	
	std::cout << "input target name" << std::endl;
	CString targetFolderName;
	std::cin >> targetFolderName;
		
	CAnimationCompose::instancePtr()->setImgNumPerRowAndCol(3,4);
	if (CAnimationCompose::instancePtr()->compose(curFloder, targetFolderName))
		std::cout << "compose success to "+curFloder+"out/"+targetFolderName << std::endl;
	else
		std::cout << "compose failed" << std::endl;
	getchar();
	getchar();
	
	return 0;
}