#pragma once

class XMLDataNode
{
public:
    struct Attribute
    {
        std::wstring name;
        std::wstring value;
    };

    //default constructor/destructor
    XMLDataNode();
    ~XMLDataNode();

    const wchar_t*       GetName() const;
    const wchar_t*       GetInnerText() const;
    bool                 HasChildren() const;

    const XMLDataNode*   GetDataNode(const wchar_t *element, unsigned int index = 0) const;
    const XMLDataNode*   GetDataNode(const wchar_t *category, const wchar_t *element, unsigned int index = 0) const;
    const XMLDataNode*   GetDataNode(const wchar_t *category, const wchar_t *section, const wchar_t *element, unsigned int index = 0) const;
    
    const std::vector<const XMLDataNode*>& GetChildren() const;
    unsigned int                        GetNumDataNodes(const wchar_t *element) const;

    void                                AddChild(const XMLDataNode *child);
    void                                AddAttribute(const Attribute &attribute);
    void                                SetName(const wchar_t *name);
    void                                SetInnerText(const wchar_t *text);

private:
    // Disable the copy constructors and assignment operator
    XMLDataNode(XMLDataNode &copy);
    XMLDataNode& operator=(XMLDataNode &copy);

    std::vector<const XMLDataNode *>        *m_Children;
    std::vector<Attribute>                  *m_Attributes;
    std::wstring                            m_Name;
    std::wstring                            m_InnerText;
};



