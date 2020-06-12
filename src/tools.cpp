#include "tools.h"

// Scan a string that contains exon start/end coordinates
// Push coordinates as int in vector
std::vector<int> scanExons(std::string exonList){
	std::stringstream exons(exonList);
	std::vector<int> result;

	while(exons.good())
	{
    	std::string substr;
    	getline(exons, substr, ',');

    	// Check that chopped string is not empty 
    	if(substr.find_first_not_of(' ') != std::string::npos)
		{
    		result.push_back(std::stoi(substr));
		}
	}

	return result;
}