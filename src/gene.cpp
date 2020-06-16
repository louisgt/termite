#include "gene.h"

Gene::Gene(std::string name, std::string chrom, char strand, std::pair<int,int> first, std::pair<int,int> last)
 : name_(name)
{
    N_.reserve(RESERVE_TERM_NUM);
    C_.reserve(RESERVE_TERM_NUM);
    
    if(strand == '+'){
    	addN(chrom, strand, first.first, first.second);
    	addC(chrom, strand, last.first, last.second);
    }
    else{
    	addN(chrom, strand, last.first, last.second);
    	addC(chrom, strand, first.first, first.second);
    }
}


Gene::~Gene()
{
	//std::cout << "Gene: destructor: destructing gene " << name_ << std::endl;
}

void Gene::addN(std::string chrom, char strand, int first, int last){
	N_.emplace_back(chrom, strand, first, last);
}

void Gene::addC(std::string chrom, char strand, int first, int last){
	C_.emplace_back(chrom, strand, first, last);
}


// IMPORTANT NOTE 1
// For the human reference genome, there is a very small set of gene names that are found on more than 1 chromosome
// the overwhelming majority of those genes are found in the pseudoautosomal regions of the X and Y chromosomes
// the remainder are most likely annotation errors from UCSC/Ensembl (see olfactory receptor genes like OR4F16)
// 
// scenario #1: we add duplicate sequences and get duplicate guides
// ex: gene SHOX found on chrX and chrY
// added to the gene map once, but termini are added separately for each chromosomal entry

// sc

// IMPORTANT NOTE 2
// For the human reference genome, there is a small set of gene names that are found on both strands of the same chromosome
// the overwhelming majority of those genes seem to be misannotation between paralogs
// the remainder are most likely annotation errors from UCSC/Ensembl (see olfactory receptor genes like OR4F16)
//  
// scenario #1: we register both strands get duplicate guides mapping to the misannotated gene
// ex: genes VCY and VCY1B
// each one has an additional entry mapping to the other, but they are on opposite strands so there are 4 entries instead of 2

void Gene::searchTermini(std::string chrom, char strand, std::pair<int,int> firstExon, std::pair<int,int> lastExon){
	if(strand == '+'){
    	searchN(chrom, strand, firstExon.first, firstExon.second);
		searchC(chrom, strand, lastExon.first, lastExon.second);
    }
    else{
    	searchN(chrom, strand, lastExon.first, lastExon.second);
    	searchC(chrom, strand, firstExon.first, firstExon.second);	
    }
	
}

void Gene::searchN(std::string chrom, char strand, int start, int stop){
 	for (const auto& t : N_){

 		if(t.getChr() != chrom)
 			continue;

 		if(t.getStrand() != strand)
 			continue;

 		// we will only consider the Start position for tagging
 		if(strand == '+'){
 			if(t.getStart() == start)
 				return;
 		}
 		// thus we need to account for strand
 		else{
 			if(t.getStop() == stop)
 				return;
 		} 	 	
 	}
 	addN(chrom, strand, start, stop);
}

void Gene::searchC(std::string chrom, char strand, int start, int stop){
 	for (const auto& t : C_){

 		if(t.getChr() != chrom)
 			continue;

 		if(t.getStrand() != strand)
 			continue;

 		// we will only consider the Stop position for tagging
 		if(strand == '+'){
 			if(t.getStop() == stop)
 				return;
 		}
 		// thus we need to account for strand
 		else{
 			if(t.getStart() == start)
 				return;
 		} 	
 	}
 	addC(chrom, strand, start, stop);
}
