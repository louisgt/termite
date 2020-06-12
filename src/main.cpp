#include "include/csv.h"
#include "gene.h"

using namespace io;

// Column separator for gene table
const char SEP = '\t';

int main () {


	std::map<std::string,Gene> geneMap;

	//------ INIT READER

	// 

    CSVReader<11,trim_chars<' '>, no_quote_escape<SEP>> in("src/sample.gene_table");

  	in.read_header(io::ignore_extra_column, "name", "accession", "chrom", "strand","txStart",
  											"txEnd","cdsStart","cdsEnd","exonCount","exonStarts","exonEnds");

  	std::string name, accession, chr;
  	char strand; 
  	int txStart, txEnd, cdsStart, cdsEnd, exonCount;
  	std::string exonStarts, exonEnds;

  	std::vector<int> exonStartCoords, exonEndCoords;

  	

  	//------ READ-EVAL LOOP

  	// Read file and create gene instances with separate ORFs
  	while(in.read_row(name, accession, chr, strand, txStart, txEnd, cdsStart, cdsEnd, exonCount, exonStarts, exonEnds)){
	 	exonStartCoords = scanExons(exonStarts);
	 	exonEndCoords  = scanExons(exonEnds);

	 	int orf_start = exonStartCoords[0];
	 	int orf_end = exonEndCoords.back();

	 	// try to find gene in map
	 	auto it = geneMap.find(name);

	 	// gene has been found
	 	if(it != geneMap.end()){
	 		std::cout << name << " is an element of mymap." << std::endl;
      		// compare with existing ORFs for that gene
      		it->second.searchORFs(orf_start,orf_end);
	 	}

    	else {
    		std::cout << name << " is not an element of mymap." << std::endl;
    		geneMap.emplace(std::piecewise_construct, 
	 		std::forward_as_tuple(name), 
	 		std::forward_as_tuple(name, orf_start, orf_end));
    	}
	}

	//------ MAIN

	int totalORF = 0;
	for (const auto &pair : geneMap) {
        	totalORF+= pair.second.numORFs();
    }

    std::cout << "Gene map has size " << geneMap.size() << std::endl;
    std::cout << "There are " << totalORF << " distinct ORFs in total" << std::endl;
    return 0;
}
















