/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "vapor/PCH.h"

namespace vapor {

//-----------------------------------//

long endian_swap(long i)
{
	unsigned char b1, b2, b3, b4;

	b1 = i & 255;
	b2 = ( i>>8 )  & 255;
	b3 = ( i>>16 ) & 255;
	b4 = ( i>>24 ) & 255;

	return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
}

//-----------------------------------//

#ifdef VAPOR_PLATFORM_WINDOWS

std::string wstrtostr(const std::wstring &wstr)
{
    // Convert a Unicode string to an ASCII string
    std::string strTo;
    char *szTo = new char[wstr.length() + 1];
    szTo[wstr.size()] = '\0';
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
    strTo = szTo;
    delete[] szTo;
    return strTo;
}

#endif

//-----------------------------------//

#ifdef VAPOR_PLATFORM_WINDOWS

std::wstring strtowstr(const std::string &str)
{
    // Convert an ASCII string to a Unicode String
    std::wstring wstrTo;
    wchar_t *wszTo = new wchar_t[str.length() + 1];
    wszTo[str.size()] = L'\0';
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszTo, (int)str.length());
    wstrTo = wszTo;
    delete[] wszTo;
    return wstrTo;
}

#endif

//-----------------------------------//

std::vector<std::string>& split(const std::string &s, char delim, 
								std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    
	while(std::getline(ss, item, delim)) 
	{
        elems.push_back(item);
    }
    
	return elems;
}

//-----------------------------------//

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

//-----------------------------------//

} // end namespace