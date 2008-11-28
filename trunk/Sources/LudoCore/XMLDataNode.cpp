///////////////////////////////
// Filename: XMLDataNode.cpp
// Description: Node in an XML file with possible attributes
// Creation Date: 04/04/2008
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "XMLDataNode.h"
#include "LudoCore/LudoUtilities.h"

using std::vector;

XMLDataNode::XMLDataNode() :
    m_Children(NULL),
    m_Attributes(NULL),
    m_Name(L""),
    m_InnerText(L"")
{
    m_Attributes = LUDO_NEW vector<Attribute>;
    m_Children = LUDO_NEW vector<const XMLDataNode *>;
}

XMLDataNode::~XMLDataNode()
{
    if (m_Children != NULL)
    {
        for (unsigned int i = 0; i < m_Children->size(); ++i)
        {
            LUDO_SAFE_DELETE((*m_Children)[i]);
        }
    }

    LUDO_SAFE_DELETE(m_Children);
    LUDO_SAFE_DELETE(m_Attributes);
}

const XMLDataNode* XMLDataNode::GetDataNode(const wchar_t*element, unsigned int index) const
{
    if (m_Children == NULL || index > m_Children->size())
    {
        return NULL;
    }

    unsigned int current = 0;
    const XMLDataNode *child;
    for (unsigned int i = 0; i < m_Children->size(); ++i)
    {
        child = (*m_Children)[i];
        if (LudoUtilities::AreStringsEqual(child->GetName(), element))
        {
            if (current == index)
            {
                return child;
            }
            ++current;
        }
    }

    return NULL;
}

const XMLDataNode* XMLDataNode::GetDataNode(const wchar_t *category, const wchar_t *element, unsigned int index) const
{
    const XMLDataNode *node = GetDataNode(category, (unsigned int)0);
    return (node != NULL) ? node->GetDataNode(element, index) : NULL;
}

const XMLDataNode* XMLDataNode::GetDataNode(const wchar_t *category, const wchar_t *section, const wchar_t *element, unsigned int index) const
{
    const XMLDataNode *node = GetDataNode(category, section, (unsigned int)0);
    return (node != NULL) ? node->GetDataNode(element, index) : NULL;
}

unsigned int XMLDataNode::GetNumDataNodes(const wchar_t *element) const
{
    if (m_Children == NULL)
    {
        return 0;
    }

    unsigned int numNodes = 0;
    for (unsigned int i = 0; i < m_Children->size(); ++i)
    {
        if (LudoUtilities::AreStringsEqual((*m_Children)[i]->GetName(), element))
        {
            ++numNodes;
        }
    }

    return numNodes;
}

void XMLDataNode::AddChild(const XMLDataNode *child)
{
    if (m_Children != NULL)
    {
        m_Children->push_back(child);
    }
}

void XMLDataNode::AddAttribute(const Attribute &attribute)
{
    if (m_Attributes != NULL)
    {
        m_Attributes->push_back(attribute);
    }
}

const wchar_t* XMLDataNode::GetName() const
{
    return m_Name.c_str();
}

const wchar_t* XMLDataNode::GetInnerText() const
{
    return m_InnerText.c_str();
}

bool XMLDataNode::HasChildren() const
{
    return (!m_Children->empty());
}

const vector<const XMLDataNode*>& XMLDataNode::GetChildren() const
{
    return *m_Children;
}

void XMLDataNode::SetName(const wchar_t *name)
{
    m_Name = name;
}

void XMLDataNode::SetInnerText(const wchar_t *text)
{
    m_InnerText = text;
}