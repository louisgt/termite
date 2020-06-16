#include "terminus.h"

Terminus::Terminus(std::string chrom, char strand, int start, int stop)
 : chrom_(chrom),
   strand_(strand),
   codingStart_(start),
   codingStop_(stop)
{}

Terminus::~Terminus()
{
	//std::cout << "ORF: destructor: destructing ORF " << CDS_start_ << "-" << CDS_end_ << std::endl;
}