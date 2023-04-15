#include "EbmlDocument.h"

EbmlDocumentInfoBlockPtr EbmlDocument::_s_initialize(std::iostream& stream, shared_ptr<EBML>& ebml_header)
{
	auto info_block = EbmlDocumentInfoBlockPtr(new EbmlDocumentInfoBlock(stream));
	ebml_header = shared_ptr<EBML>(new EBML(info_block));
	ebml_header->
	return info_block;
}
