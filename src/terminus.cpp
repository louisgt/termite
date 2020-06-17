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