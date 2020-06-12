#include "gene.h"


Gene::Gene(){
	//std::cout << "Gene: default ctor. " << std::endl;
}


Gene::Gene(std::string name, int nterm, int cterm, std::string chrom)
{
	//std::cout << "Gene: explicit ctor: constructing gene " << name << std::endl;
    name_ = name;
    ORFs_.reserve(RESERVE_ORF_NUM);
    addORF(nterm,cterm,chrom);
}


Gene::~Gene()
{
	//std::cout << "Gene: destructor: destructing gene " << name_ << std::endl;
}

void Gene::addORF(int start, int end, std::string chrom){
	ORFs_.emplace_back(start,end,chrom);
}

void Gene::searchORFs(int start, int end, std::string chrom){
	//std::cout << "Searching ORFs..." << std::endl;
	for (const auto& o : ORFs_){
	 	if(o.getStart() == start && o.getEnd() == end && o.getChrom() == chrom){
			std::cout << "An accession of gene " << name_ << " with the same range already exists in map" << std::endl;
			//std::cout << "Stopping search." << std::endl;
			return;
		}
	}
	std::cout << "NO accession of gene " << name_ << " with the same range already exists in map" << std::endl;
	addORF(start,end,chrom);
}