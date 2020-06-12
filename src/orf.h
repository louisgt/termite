#ifndef ORF_H
#define ORF_H

#include "tools.h"

class ORF 
{
public:
	ORF();
    ORF(int, int);
    ~ORF(); 

    int getStart() const {return CDS_start_;}
    int getEnd() const {return CDS_end_;}

protected:
    int CDS_start_;
    int CDS_end_;
};

#endif