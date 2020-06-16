#ifndef TERMINUS_H
#define TERMINUS_H

#include "tools.h"

class Terminus 
{
public:
    Terminus(std::string, char, int, int);
    ~Terminus(); 

    //void setStart(int start) {codingStart_ = start;}
    //void setStop(int stop) {codingStop_ = stop;}

    int getStart() const {return codingStart_;}
    int getStop() const {return codingStop_;}

    std::string getChr() const {return chrom_;}
    char getStrand() const {return strand_;}


protected:
    std::string chrom_;
    char strand_;

    // start and end of coding sequence for given terminal exon
    int codingStart_;
    int codingStop_;

    

};

#endif