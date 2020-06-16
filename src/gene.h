#ifndef GENE_H
#define GENE_H

#include "orf.h"

const int RESERVE_ORF_NUM(2);

class Gene 
{
public:
	Gene();
    Gene(std::string, std::pair<int,int>, std::pair<int,int>, std::string);
    ~Gene(); 

    std::string getName() const {return name_;}

    std::vector<ORF> getORFs() const {return ORFs_;}

    int numORFs() const {return ORFs_.size();}

    void addORF(std::pair<int,int>,std::pair<int,int>,std::string);

    void searchORFs(std::pair<int,int>,std::pair<int,int>,std::string);

protected:
    std::string name_;
    //Array of ORFs
    std::vector<ORF> ORFs_;
};

#endif