#include "orf.h"


ORF::ORF(){
	//std::cout << "ORF: default ctor" << std::endl;
}

ORF::ORF(std::pair<int,int> first, std::pair<int,int> last, std::string chrom)
{
	//std::cout << "ORF: explicit ctor: constructing ORF " << nterm << "-" << cterm << std::endl;
	firstExon_ = first;
	lastExon_ = last;
	chr_ = chrom;
}

ORF::~ORF()
{
	//std::cout << "ORF: destructor: destructing ORF " << CDS_start_ << "-" << CDS_end_ << std::endl;
}