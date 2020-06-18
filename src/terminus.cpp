#include "terminus.h"

const char *Terminus::REVERSE_COMP = " | ./bin/faRc -keepCase stdin stdout";

Terminus::Terminus(const std::string chrom, const char strand, const int start, const int stop)
 : chrom_(chrom),
   strand_(strand),
   codingStart_(start),
   codingStop_(stop)
{}

Terminus::~Terminus()
{
	//std::cout << "ORF: destructor: destructing ORF " << CDS_start_ << "-" << CDS_end_ << std::endl;
}


int Terminus::findGuides(const int guideLen, const int maxNtCut, const bool isCTerm){
	// STEP 1 find window size for search step
	int upstream_padding = guideLen - 3;
	if(isCTerm)
		upstream_padding -= 3;

	std::pair<int,int> positiveStrand(codingStart_ - upstream_padding, codingStop_ + Terminus::DOWNSTREAM_PAD);
	std::pair<int,int> negativeStrand(codingStart_ - Terminus::DOWNSTREAM_PAD, codingStop_ + upstream_padding);

	int numFWD = searchWindow(positiveStrand,false);
	int numREV = searchWindow(negativeStrand,true);
}

int Terminus::searchWindow(const std::pair<int,int> window, const bool isNegative){

	char cmd[512];

	sprintf(cmd, "./bin/twoBitToFa -noMask -seq=%s -start=%s -end=%s data/raw/hg38.2bit stdout%s", chrom_.c_str(),
	std::to_string(window.first).c_str(),
	std::to_string(window.second).c_str(), isNegative ? Terminus::REVERSE_COMP : "");

	auto result = exec(cmd);

	std::cout << result << std::endl;

}