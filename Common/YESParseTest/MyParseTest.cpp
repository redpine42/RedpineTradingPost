/* Calculate an expression read from stdin or from the arguments passed to
 * the program (using stringstream's)
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include "MyLexer.hpp"
#include "MyParser.hpp"
#include "MyParserTokenTypes.hpp"

int main( int argc, char* argv[] )
{
	ANTLR_USING_NAMESPACE(std)
	ANTLR_USING_NAMESPACE(antlr)
	char * filePath = getenv("YesConfig");
	
	char * doneStr = new char[1];

	if(0 == filePath)
	{
		cout << "ERROR!!!! Enviornment Variable \"YesConf\" is not set!" << endl;
		cin >> doneStr;
		return -1;
	}
	try
	{
		std::string fileName = filePath;
		ifstream istrm(fileName.c_str());
		if(istrm.is_open() )
		{
			MyLexer lexer(istrm);
	
			MyParser parser(lexer);

			// Parse the input expression
			while(lexer.done != true)
			{
				parser.fileparser();
			}
		}
		else
		{
			std::cout << "Failed To Open File: " << fileName << std::endl;
			cerr << "Press Enter!" << std::endl;
			cin.getline(doneStr,1);
			return -1;
		}
	}
	catch(ANTLRException& e)
	{
		cerr << "Parse exception: " << e.toString() << endl;
	    cerr << "Press Enter!" << std::endl;
	    cin.getline(doneStr,1);
		return -1;
	}
	catch(exception& e)
	{
		cerr << "exception: " << e.what() << endl;
	    cerr << "Press Enter!" << std::endl;
	    cin.getline(doneStr,1);
		return -1;
	}
	cout << "Press Enter!" << std::endl;
	cin.getline(doneStr,1);
	return 0;
}
