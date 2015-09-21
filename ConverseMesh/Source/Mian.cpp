#include "DreamMeshConverse.h"

int main(int argc, char* argv[])
{
	CDreamMeshConverse converse;

	CString fileName;
	while (std::cin>>fileName)
	{
		converse.converseToBinary(fileName);
	}
	
	return 0;
}