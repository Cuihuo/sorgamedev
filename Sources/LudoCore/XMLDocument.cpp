///////////////////////////////
// Filename: XMLDocument.cpp
// Description: Representation of a parsed XML file
// Creation Date: 18/07/2008
///////////////////////////////

#include "LudoCore/LudoGlobal.h"
#include "LudoCore/ErrorLogger.h"
#include "XMLDocument.h"
#include "LudoCore/FileReader.h"
#include "LudoCore/LudoUtilities.h"

using std::wstring;
XMLDocument::XMLDocument(const wchar_t *filename) :
    m_Root(NULL)
{
    m_Filename = filename;

    FileReader fr(m_Filename);
    int size = 0;
    wchar_t *memblock = (wchar_t *)fr.GetFileData(size);
    
    if (size != 0)
    {
        BuildDocument(memblock, size);
    }
    LUDO_SAFE_DELETE(memblock);
}

// virtual
XMLDocument::~XMLDocument()
{
    LUDO_SAFE_DELETE(m_Root);
}

void XMLDocument::BuildDocument(const void *buffer, int size)
{
    // Should a document previously exist, destroy it
    LUDO_SAFE_DELETE(m_Root);

    // Create the XML reader using <xmllite.h>
    XMLReaderPtr xmlReader = CreateXMLReader(buffer, size);

    // Build the XMLDataNodes (recursively)
    if (xmlReader != NULL)
    {
        HRESULT hr;
        XmlNodeType nodeType;

        while (S_OK == (hr = xmlReader->Read(&nodeType)))
        {
            if (nodeType == XmlNodeType_Element)
            {
                m_Root = BuildDataNode(xmlReader);
                break;
            }
        }

        if ( (int)hr == WC_E_ROOTELEMENT )
        {
            return;
        }
        else if (FAILED(hr))
        {
            return;
        }
    }
}

XMLDocument::XMLReaderPtr XMLDocument::CreateXMLReader(const void *buffer, int size)
{
    if ((buffer == NULL) || (size <= 0))
    {
        return NULL;
    }

    XMLReaderPtr xmlReader = NULL;
    XMLFileStream fileStream;
    HRESULT hr;

    if ( FAILED(hr = CreateStreamOnHGlobal(NULL, TRUE, &fileStream)) )
    {
        ErrorLogger::GetInstance()->LogError(L"Cannot create stream on global", true);
        return NULL;
    }

    // TODO: CreateXmlReaderInputWithEncodingName() and specify our own allocator!
    ULONG ulBytesWritten = 0;
    fileStream->Write(buffer, size, &ulBytesWritten);

    if ( FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &xmlReader, NULL)) )
    {
        ErrorLogger::GetInstance()->LogError(L"Cannot create XML Reader", true);
        fileStream.Release();
        return NULL;
    }

    if ( FAILED(hr = xmlReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)) )
    {
        ErrorLogger::GetInstance()->LogError(L"Error setting properties", true);
        fileStream.Release();
        xmlReader.Release();
        return NULL;
    }

    // Reset the file stream to the beginning
    LARGE_INTEGER li;
    li.QuadPart = 0;
    fileStream->Seek(li, 0, NULL);

    if ( FAILED(hr = xmlReader->SetInput(fileStream)) )
    {
        ErrorLogger::GetInstance()->LogError(L"Error setting input for XML Reader", true);
        fileStream.Release();
        xmlReader.Release();
        return NULL;
    }

    return xmlReader;
}

const XMLDataNode* XMLDocument::BuildDataNode(XMLReaderPtr &xmlReader)
{
    // Create a new data node
    XMLDataNode *dataNode = LUDO_NEW XMLDataNode();

    XmlNodeType nodeType;
    const WCHAR *readBuffer = NULL;
    HRESULT hr;

    // Get the local name of this element
    if ( FAILED(hr = xmlReader->GetLocalName(&readBuffer, NULL)) )
    {
        return NULL;
    }
    dataNode->SetName(readBuffer);

    // We must call this before reading the attributes because the call will fail afterwards
    bool isEmptyElement = (xmlReader->IsEmptyElement() != FALSE);

    // Get all the attributes and add them to the XML node
    if ( S_OK == (hr = xmlReader->MoveToFirstAttribute()) )
    {
        do
        {
            XMLDataNode::Attribute attribute;
            if ( FAILED(hr = xmlReader->GetLocalName(&readBuffer, NULL)) )
            {
                LUDO_SAFE_DELETE(dataNode);
                return NULL;
            }
            attribute.name = readBuffer;

            if ( FAILED(hr = xmlReader->GetValue(&readBuffer, NULL)) )
            {
                LUDO_SAFE_DELETE(dataNode);
                return NULL;
            }
            attribute.value = readBuffer;

            dataNode->AddAttribute(attribute);
        }
        while ( S_OK == (hr = xmlReader->MoveToNextAttribute()) );
    }

    // Stop immediately if the element is empty (i.e. <MyTag Attr="value"/>)
    if (isEmptyElement)
    {
        return dataNode;
    }

    // Find the children or inner text if the element is not empty
    while (S_OK == (hr = xmlReader->Read(&nodeType)))
    {
        // Found child, add it and keep looking for more
        if (nodeType == XmlNodeType_Element)
        {
            const XMLDataNode *child = BuildDataNode(xmlReader);
            if (child != NULL)
            {
                dataNode->AddChild(child);
            }
        }
        // Found inner text, but continue to look for the end element tag
        else if (nodeType == XmlNodeType_Text)
        {
            if ( !FAILED(hr = xmlReader->GetValue(&readBuffer, NULL)) && readBuffer[0] != L'\0' )
            {
                dataNode->SetInnerText(readBuffer);
            }
        }
        // Found the end element tag, we can stop
        else if (nodeType == XmlNodeType_EndElement)
        {
            return dataNode;
        }
    }

    // Error:  Invalid tag? (or maybe end of file?)
    return dataNode;
}


const XMLDataNode* XMLDocument::GetDataNode(const wchar_t *element, int index) const
{
    return (m_Root != NULL) ? m_Root->GetDataNode(element, index) : NULL;
}

const XMLDataNode* XMLDocument::GetDataNode(const wchar_t *category, const wchar_t *element, int index) const
{
    return (m_Root != NULL) ? m_Root->GetDataNode(category, element, index) : NULL;
}

const XMLDataNode* XMLDocument::GetDataNode(const wchar_t *category, const wchar_t *section, const wchar_t *element, int index) const
{
    return (m_Root != NULL) ? m_Root->GetDataNode(category, section, element, index) : NULL;
}

unsigned int XMLDocument::GetNumDataNodes(const wchar_t *element) const
{
    return (m_Root != NULL) ? m_Root->GetNumDataNodes(element) : 0;
}

const XMLDataNode* XMLDocument::GetRoot() const
{
    return m_Root;
}

bool XMLDocument::IsValid() const
{
    return (m_Root != NULL);
}
