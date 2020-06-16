#ifndef ORF_H
#define ORF_H

#include "tools.h"

class ORF 
{
public:
	ORF();
    ORF(std::pair<int,int>, std::pair<int,int>, std::string);
    ~ORF(); 

    int getStart() const {return firstExon_.first;}
    int getEnd() const {return lastExon_.second;}
    std::pair<int,int> getFirst() const {return firstExon_;}
    std::pair<int,int>  getLast() const {return lastExon_;}
    std::string getChrom() const {return chr_;}

protected:
    std::pair<int,int> firstExon_;
    std::pair<int,int> lastExon_;
    std::string chr_;
};

#endif