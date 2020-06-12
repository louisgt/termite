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

std::pair<int,int> firstCodingExon(char strand, int cdsStart, std::vector<int> exonStarts, std::vector<int> exonEnds){
	
	if(strand != '+' && strand != '-')
		throw std::runtime_error( "Invalid strand value in gene table." );

	int currentExon = 0;

	// we want to identify the index of the first coding exon
	while(cdsStart>exonStarts[currentExon]){
		// lookup next exon
		if(cdsStart<exonStarts[currentExon+1])
			// ATG is located in currentExon
			break;
		currentExon++;
	} 

	int endCoord = exonEnds[currentExon];

	if(strand == '+')
		return std::pair<int,int>(cdsStart,endCoord);
	else
		// 'cdsStart' is the end of the coding sequence
		return std::pair<int,int>(cdsStart+1,endCoord);
}

std::pair<int,int> lastCodingExon(char strand, int cdsEnd, std::vector<int> exonStarts, std::vector<int> exonEnds){
	
	if(strand != '+' && strand != '-')
		throw std::runtime_error( "Invalid strand value in gene table." );

	if(strand == '+'){
		
		return std::pair<int,int>(1,1);
	}
	else{
		
		return std::pair<int,int>(1,1);
	}
}