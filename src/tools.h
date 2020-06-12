#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::vector<int> scanExons(std::string exonList);

std::pair<int,int> firstCodingExon(char,int,std::vector<int>,std::vector<int>);
std::pair<int,int> lastCodingExon(char,int,std::vector<int>,std::vector<int>);

#endif