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

    // findGuides
    // instead of getWindow
    int findGuides(int,int,bool);

    int searchWindow(std::pair<int,int>, bool);

    // need a method that takes a string sequence
        // thread through sequence in search of PAMs
        // when PAM is found, create a guide instance and push to vector

    std::pair<int,int> getWindowN(int, int) const;
    std::pair<int,int> getWindowC(int, int) const;


protected:
    std::string chrom_;
    char strand_;

    // start and end of coding sequence for given terminal exon
    int codingStart_;
    int codingStop_;

    static const int DOWNSTREAM_PAD = 6;
    static const char *REVERSE_COMP;

};

#endif