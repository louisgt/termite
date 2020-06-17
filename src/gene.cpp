#include "gene.h"

Gene::Gene(const std::string name, const std::string chrom, const char strand, const std::pair<int,int> first, const std::pair<int,int> last)
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

void Gene::addN(const std::string chrom, const char strand, const int first, const int last){
	N_.emplace_back(chrom, strand, first, last);
}

void Gene::addC(const std::string chrom, const char strand, const int first, const int last){
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

void Gene::searchTermini(const std::string chrom, const char strand, const std::pair<int,int> firstExon, const std::pair<int,int> lastExon){
	// we need to consider orientation of the coding sequence
	if(strand == '+'){
    	searchN(chrom, strand, firstExon.first, firstExon.second);
		searchC(chrom, strand, lastExon.first, lastExon.second);
    }
    else{
    	searchN(chrom, strand, lastExon.first, lastExon.second);
    	searchC(chrom, strand, firstExon.first, firstExon.second);	
    }
	
}

// IMPORTANT NOTE
// At first glance there is a great deal of code duplication in the search algorithm
// However refactoring is complex and will likely lead to a contrived search function with lots of bool arguments...
// 	...given that we search must search two different named vectors, and cannot go around strandedness
// For now, limiting the number of arguments is more readable, thus readability overrules DRY in this cas

void Gene::searchN(const std::string chrom, const char strand, const int start, const int stop){
 	for (auto& t : N_){

 		// consider pseudoautosomal genes (exist on X and Y chr)
 		if(t.getChr() != chrom || t.getStrand() != strand)
 			continue;

 		// we will only consider the Start position for tagging
 		if(strand == '+'){
 			if(t.getStart() == start)
 			{
 				if(stop - start > t.codingRange())
 					t.setStop(stop);
 				return;
 			}
 		}
 		// we need to account for strand
 		else{
 			if(t.getStop() == stop){
 				if(stop - start > t.codingRange())
 					t.setStart(start);
 				return;		
 			} 	 	
 		}
 	}
 	addN(chrom, strand, start, stop);
}

void Gene::searchC(const std::string chrom, const char strand, const int start, const int stop){
 	for (auto& t : C_){

 		// consider pseudoautosomal genes (exist on X and Y chr)
 		if(t.getChr() != chrom || t.getStrand() != strand)
 			continue;

 		// we will only consider the Stop position for tagging
 		if(strand == '+'){
 			if(t.getStop() == stop)
 			{
 				if(stop - start > t.codingRange())
 					t.setStart(start);
 				return;
 			}	
 		}
 		// thus we need to account for strand
 		else{
 			if(t.getStart() == start)
 			{
 				if(stop - start > t.codingRange())
 					t.setStop(stop);
 				return;
 			}
 		} 	
 	}
 	addC(chrom, strand, start, stop);
}
