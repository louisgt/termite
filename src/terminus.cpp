#include "terminus.h"

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

std::pair<int,int> Terminus::getWindowN(const int guideLen) const{
	int upstream_padding = guideLen - 3;
	return std::pair<int,int>(codingStart_ - upstream_padding, codingStop_ + Terminus::DOWNSTREAM_PAD);
}

std::pair<int,int> Terminus::getWindowC(const int guideLen) const{
	int upstream_padding = guideLen - 6;
	return std::pair<int,int>(codingStart_ - upstream_padding, codingStop_ + Terminus::DOWNSTREAM_PAD);
}