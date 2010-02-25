/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

namespace vapor {

//-----------------------------------//

// Swaps the endianness of a long.
long endian_swap(long i);

//-----------------------------------//

template< typename T >
T str_to_num(const std::string& s)
{
	std::stringstream ss(s);
	T num; ss >> num; 
	assert(!ss.fail());
	return num;
}

//-----------------------------------//

template< typename T >
std::string num_to_str(const T& t)
{
	std::ostringstream oss;
	oss << t; 
	assert(!oss.fail());
	return oss.str();
}

//-----------------------------------//

std::string wstrtostr(const std::wstring &wstr);

//-----------------------------------//

std::wstring strtowstr(const std::string &str);

//-----------------------------------//

std::vector<std::string>& split(const std::string& s, char delim, 
								std::vector<std::string>& elems);

//-----------------------------------//

std::vector<std::string> split(const std::string& s, char delim);

//-----------------------------------//

} // end namespace