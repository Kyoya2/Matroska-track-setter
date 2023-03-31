#pragma once
#include "Common.h"

class EBML;
class EbmlBody final
{


};

class EbmlDocument final
{
public:
    EbmlDocument(std::iostream& stream);

public:
    shared_ptr<EBML> ebml;
    EbmlBody body;
};