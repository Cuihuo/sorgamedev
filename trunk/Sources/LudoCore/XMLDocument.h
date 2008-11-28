#pragma once

#ifdef _WIN32
#include <atlbase.h>
#include <xmllite.h>
#endif
#include "XMLDataNode.h"

class XMLDocument
{
public:
    XMLDocument(const wchar_t *filename);
    virtual ~XMLDocument();

    const XMLDataNode*                   GetDataNode(const wchar_t *element, int index = 0) const;
    const XMLDataNode*                   GetDataNode(const wchar_t *category, const wchar_t *element, int index = 0) const;
    const XMLDataNode*                   GetDataNode(const wchar_t *category, const wchar_t *section, const wchar_t *element, int index = 0) const;
    unsigned int                         GetNumDataNodes(const wchar_t *element) const;
    const XMLDataNode*                   GetRoot() const;
    bool                                 IsValid() const;

private:
    // Disable the copy constructors and assignment operator
    XMLDocument(XMLDocument &copy);
    XMLDocument& operator=(XMLDocument &copy);

    void                                        BuildDocument(const void *buffer, int size);

    typedef CComPtr<IXmlReader>                 XMLReaderPtr;
    typedef CComPtr<IStream>                    XMLFileStream;
    XMLReaderPtr                                CreateXMLReader(const void *buffer, int size);
    const XMLDataNode*                          BuildDataNode(XMLReaderPtr &xmlReader);

    const wchar_t                               *m_Filename;
    const XMLDataNode                           *m_Root;
};

