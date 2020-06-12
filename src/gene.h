#ifndef GENE_H
#define GENE_H

#include "orf.h"

const int RESERVE_ORF_NUM(2);

class Gene 
{
public:
	Gene();
    Gene(std::string, int, int);
    ~Gene(); 

    std::string getName() const {return name_;}

    std::vector<ORF> getORFs() const {return ORFs_;}

    int numORFs() const {return ORFs_.size();}

    void addORF(int,int);

    void searchORFs(int,int);

protected:
    std::string name_;
    //Array of ORFs
    std::vector<ORF> ORFs_;
};

#endif