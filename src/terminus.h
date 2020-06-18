#ifndef TERMINUS_H
#define TERMINUS_H

#include "tools.h"

class Terminus 
{
public:
    Terminus(std::string, char, int, int);
    ~Terminus(); 

    void setStart(int start) {codingStart_ = start;}
    void setStop(int stop) {codingStop_ = stop;}

    int getStart() const {return codingStart_;}
    int getStop() const {return codingStop_;}

    std::string getChr() const {return chrom_;}
    char getStrand() const {return strand_;}

    int codingRange() const {return codingStop_ - codingStart_;}

    std::pair<int,int> getWindowN(int) const;
    std::pair<int,int> getWindowC(int) const;


protected:
    std::string chrom_;
    char strand_;

    // start and end of coding sequence for given terminal exon
    int codingStart_;
    int codingStop_;

    static const int DOWNSTREAM_PAD = 6;

    

};

#endif