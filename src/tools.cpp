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
	int max = exonStarts.size() - 1;

	// we want to identify the index of the first coding exon
	while(cdsStart>exonStarts[currentExon]){
		// if we are on the last exon
		if(currentExon == max)
			break;
		// lookup next exon
		if(cdsStart<exonStarts[currentExon+1])
			// ATG is located in currentExon
			break;
		currentExon++;
	} 

	int endCoord = exonEnds[currentExon];

	return std::pair<int,int>(cdsStart+1,endCoord);
}

std::pair<int,int> lastCodingExon(char strand, int cdsEnd, std::vector<int> exonStarts, std::vector<int> exonEnds){
	
	if(strand != '+' && strand != '-')
		throw std::runtime_error( "Invalid strand value in gene table." );

	int currentExon = exonEnds.size() - 1;

	// we want to identify the index of the last coding exon
	while(cdsEnd<exonEnds[currentExon]){
		// if we are on the first exon
		if(currentExon == 0)
			break;
		// lookup next exon
		if(cdsEnd>exonEnds[currentExon-1])
			// ATG is located in currentExon
			break;
		currentExon--;
	}

	int endCoord = exonStarts[currentExon];

	return std::pair<int,int>(endCoord+1,cdsEnd);

}