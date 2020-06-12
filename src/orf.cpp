#include "orf.h"


ORF::ORF(){
	//std::cout << "ORF: default ctor" << std::endl;
}

ORF::ORF(int nterm, int cterm)
{
	//std::cout << "ORF: explicit ctor: constructing ORF " << nterm << "-" << cterm << std::endl;
	CDS_start_ = nterm;
	CDS_end_ = cterm;
}

ORF::~ORF()
{
	//std::cout << "ORF: destructor: destructing ORF " << CDS_start_ << "-" << CDS_end_ << std::endl;
}