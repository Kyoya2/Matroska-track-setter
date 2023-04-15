#pragma once
#include "Common.h"
#include "EbmlMatroskaElements.auto.h"

class EbmlBody final
{
private:
    EbmlBody(EbmlDocumentInfoBlockPtr info_block);

public:

    
    friend class EbmlDocument;
};

class EbmlDocument final
{
public:
    EbmlDocument(std::iostream& stream) :
        ebml(nullptr),
        body(_s_initialize(stream, ebml))
    {}

private:
    // Initializes the given EBML element and returns 
    static EbmlDocumentInfoBlockPtr _s_initialize(std::iostream& stream, shared_ptr<EBML>& ebml_header);

public:
    shared_ptr<EBML> ebml;
    EbmlBody body;
};