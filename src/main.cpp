#include "include/csv.h"
#include "gene.h"

using namespace io;

// Column separator for gene table
const char SEP = '\t';

void readToMap(std::string file, std::map<std::string,Gene> &gm){
	CSVReader<11,trim_chars<' '>, no_quote_escape<SEP>> in(file);
  	in.read_header(io::ignore_extra_column, "name", "accession", "chrom", "strand","txStart",
  											"txEnd","cdsStart","cdsEnd","exonCount","exonStarts","exonEnds");

  	std::string name, accession, chr;
  	char strand; 
  	int txStart, txEnd, cdsStart, cdsEnd, exonCount;
  	std::string exonStarts, exonEnds;
  	std::vector<int> exonStartCoords, exonEndCoords;

  	// Read file and create gene instances with separate ORFs
  	while(in.read_row(name, accession, chr, strand, txStart, txEnd, cdsStart, cdsEnd, exonCount, exonStarts, exonEnds)){
	 	
	 	exonStartCoords = scanExons(exonStarts);
	 	exonEndCoords  = scanExons(exonEnds);

	 	std::pair<int,int> firstExon;
	 	std::pair<int,int> lastExon;

	 	// find coding exons and create pairs
	 	try{
	 		firstExon = firstCodingExon(strand,cdsStart,exonStartCoords,exonEndCoords);
	 		lastExon = lastCodingExon(strand,cdsEnd,exonStartCoords,exonEndCoords);
	 	}
	 	catch(const std::invalid_argument& e){
	 		std::cerr << "Exception thrown: " << e.what() << std::endl;
	 	}

	 	//std::cout << name << std::endl;
	 	//std::cout << firstExon.first << "-" << firstExon.second << std::endl;
	 	std::cout << lastExon.first << "-" << lastExon.second << std::endl;

	 	// try to find gene in map
	 	auto it = gm.find(name);

	 	if(it != gm.end()){
	 		//std::cout << name << " is an element of mymap." << std::endl;
      		// compare with existing ORFs for that gene
      		it->second.searchORFs(firstExon,lastExon,chr);
	 	}

    	else {
    		//std::cout << name << " is not an element of mymap." << std::endl;
    		gm.emplace(std::piecewise_construct, 
	 		std::forward_as_tuple(name), 
	 		std::forward_as_tuple(name, firstExon, lastExon, chr));
    	}
	}
}

void summarize(std::map<std::string,Gene> &gm){
	int totalORF = 0;
	for (const auto &pair : gm) {
        	totalORF+= pair.second.numORFs();
    }

    std::cout << "Gene map has size " << gm.size() << std::endl;
    std::cout << "There are " << totalORF << " distinct ORFs in total" << std::endl;
}

std::string exec(const char* cmd) {
    std::array<char, 512> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main () {

	std::map<std::string,Gene> geneMap;

	//------ READ GENE TABLE TO MAP
	//------ ADD ORFs

	readToMap("src/sample.gene_table", geneMap);
	summarize(geneMap);

	//------ MAIN

	// for gene in map
	for (const auto &pair : geneMap) {

		// for ORF in gene
		for (const auto &o : pair.second.getORFs()) {
			//std::cout << o.getChrom() << ":" << o.getStart() << "-" << o.getEnd() << std::endl;
			// fetch the sequence of terminal exons
			char cmd[512];
			sprintf(cmd, "./bin/twoBitToFa -seq=%s -start=%s -end=%s data/raw/hg38.2bit stdout", o.getChrom().c_str(),
			std::to_string(o.getLast().first).c_str(),
			std::to_string(o.getLast().second).c_str());
			auto result = exec(cmd);
			std::cout << result << std::endl;

		}
	}

    return 0;
}
















