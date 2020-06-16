#include "gene.h"


Gene::Gene(){
	//std::cout << "Gene: default ctor. " << std::endl;
}


Gene::Gene(std::string name, std::pair<int,int> first, std::pair<int,int> last, std::string chrom)
{
	//std::cout << "Gene: explicit ctor: constructing gene " << name << std::endl;
    name_ = name;
    ORFs_.reserve(RESERVE_ORF_NUM);
    addORF(first,last,chrom);
}


Gene::~Gene()
{
	//std::cout << "Gene: destructor: destructing gene " << name_ << std::endl;
}

void Gene::addORF(std::pair<int,int> first, std::pair<int,int> last, std::string chrom){
	ORFs_.emplace_back(first,last,chrom);
}

void Gene::searchORFs(std::pair<int,int> first, std::pair<int,int> last, std::string chrom){
	//std::cout << "Searching ORFs..." << std::endl;
	for (const auto& o : ORFs_){
	 	if(o.getStart() == first.first && o.getEnd() == last.second && o.getChrom() == chrom){
			//std::cout << "An accession of gene " << name_ << " with the same range already exists in map" << std::endl;
			//std::cout << "Stopping search." << std::endl;
			return;
		}
	}
	//std::cout << "NO accession of gene " << name_ << " with the same range already exists in map" << std::endl;
	addORF(first,last,chrom);
}