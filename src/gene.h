#ifndef GENE_H
#define GENE_H

#include "terminus.h"

const int RESERVE_TERM_NUM(2);

class Gene 
{
public:
    Gene(std::string, std::string, char, std::pair<int,int>, std::pair<int,int>);
    ~Gene(); 

    std::string getName() const {return name_;}

    std::vector<Terminus> &getNTermini() {return N_;}
    std::vector<Terminus> &getCTermini() {return C_;}
    
    std::vector<Terminus> getNTermini() const {return N_;}
    std::vector<Terminus> getCTermini() const {return C_;}

    int numN() const {return N_.size();}
    int numC() const {return C_.size();}

    int totalTermini() const {return N_.size() + C_.size();}

    void addN(std::string, char, int, int);
    void addC(std::string, char, int, int);

    void searchTermini(std::string, char, std::pair<int,int>, std::pair<int,int>);

    void searchN(std::string, char, int, int);
    void searchC(std::string, char, int, int);


protected:
    std::string name_;

    std::vector<Terminus> C_;
    std::vector<Terminus> N_;
};

#endif