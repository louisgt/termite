#include "include/csv.h"
#include "gene.h"

using namespace io;

// Column separator for gene table
const char SEP = '\t';

void readToMap(const std::string file, std::map<std::string,Gene> &gm){
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

	 	// try to find gene in map
	 	auto it = gm.find(name);

	 	// gene found
	 	if(it != gm.end()){
      		it->second.searchTermini(chr, strand, firstExon, lastExon);
	 	}

	 	// add gene
    	else {
    		gm.emplace(std::piecewise_construct, 
	 		std::forward_as_tuple(name), 
	 		std::forward_as_tuple(name, chr, strand, firstExon, lastExon));
    	}
	}
}

void summarize(const std::map<std::string,Gene> &gm){
	int totalTerm = 0;
	int totalN = 0;
	int totalC = 0;
	for (const auto &pair : gm) {
        	totalTerm += pair.second.totalTermini();
        	totalN += pair.second.numN();
        	totalC += pair.second.numC();
    }

    std::cout << "Gene map has size " << gm.size() << std::endl;
    std::cout << "There are " << totalN << " distinct N-termini" << std::endl;
    std::cout << "There are " << totalC << " distinct C-termini" << std::endl;
    std::cout << "There are " << totalTerm << " distinct termini in total" << std::endl;
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

	int guideLen = 20;

	std::map<std::string,Gene> geneMap;

	//------ READ GENE TABLE TO MAP
	//------ ADD ORFs

	readToMap("src/hg38.gene_table", geneMap);

	//------ MAIN

	for (const auto &pair : geneMap) {
		std::cout << pair.first << std::endl;
		//std::cout << "NTERM list" << std::endl;
		// for termini in gene
		for (const auto &t : pair.second.getNTermini()) {
			std::cout << t.getChr() << ":" << t.getStart() << "-" << t.getStop() << std::endl;

			// fetch the sequence of N-terminal exons

			auto window = t.getWindowN(guideLen);

			char cmd[512];
			sprintf(cmd, "./bin/twoBitToFa -seq=%s -start=%s -end=%s data/raw/hg38.2bit stdout", t.getChr().c_str(),
			std::to_string(window.first).c_str(),
			std::to_string(window.second).c_str());
			auto result = exec(cmd);
			std::cout << result << std::endl;

		}
		//std::cout << "CTERM list" << std::endl;
		// for termini in gene
		for (const auto &t : pair.second.getCTermini()) {
			std::cout << t.getChr() << ":" << t.getStart() << "-" << t.getStop() << std::endl;

			// fetch the sequence of C-terminal exons
			auto window = t.getWindowN(guideLen);
			
			char cmd[512];
			sprintf(cmd, "./bin/twoBitToFa -seq=%s -start=%s -end=%s data/raw/hg38.2bit stdout", t.getChr().c_str(),
			std::to_string(window.first).c_str(),
			std::to_string(window.second).c_str());
			auto result = exec(cmd);
			std::cout << result << std::endl;

		}
	}

	summarize(geneMap);

    return 0;
}
















