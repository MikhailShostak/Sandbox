#pragma  once

#include "XMLNode.h"

class Parser
{
public:
    virtual bool atBegin() const = 0;
    virtual bool atEnd() const = 0;
    virtual char get() = 0;
    virtual char read() = 0;
    virtual void next() = 0;
    virtual void back() = 0;
    
    bool readToken(char token)
    {
        if (atEnd())
        {
            return false;
        }

        if (get() == token)
        {
            next();
            return true;
        }

        return false;
    }

    template<typename ArrayType>
    bool readTokens(const ArrayType &tokens)
    {
        for (const auto &token : tokens)
        {
            if (!readToken(token))
            {
                return false;
            }
        }
        return true;
    }

    template<typename ArrayType>
    bool skipUntilEndOf(const ArrayType &tokens)
    {
        while (!atEnd())
        {
            if (readTokens(tokens))
            {
                return true;
            }
            next();
        }
        return false;
    }

    template<typename ArrayType>
    void skip(const ArrayType &tokens)
    {
        auto has = [](const auto &checkedToken, const auto &tokens) {
            for (auto &token : tokens)
            {
                if (checkedToken == token)
                {
                    return true;
                }
            }
            return false;
        };
        while (!atEnd())
        {
            if (has(get(), tokens))
            {
                next();
            }
            else
            {
                break;
            }
        }
    }

    void skipWhiteSpaces()
    {
        skip(std::array<char, 4>{ ' ', '\t', '\n', '\r' });
    }
};

template<typename NodeType>
class XMLParser : public Parser
{
public:
    /*bool hasError() const { return e != AJSONErrorCode::Null; }
    AJSONErrorCode error() const { return e; }*/
    uint64_t errorLine() const { return line; }
    uint64_t errorOffset() const { return offset; }
    NodeType parse();

private:

    uint64_t line = 0;
    uint64_t offset = 0;

    template<typename SparatorArrayType>
    bool parseString(String &string, const SparatorArrayType &sperators, bool isData = false);
    bool parseNode(NodeType &node);
    bool parseName(NodeType &node);
    bool parseAttributes(NodeType &node);
    bool parseContent(NodeType &node);
};

template<typename NodeType>
template<typename SparatorArrayType>
inline bool XMLParser<NodeType>::parseString(String &string, const SparatorArrayType &sperators, bool isData)
{
    while (!atEnd())
    {
        char token = get();
        for (const auto &separator : sperators)
        {
            if (token == separator)
            {
                return !string.empty();
            }
        }

        if (('a' <= token && token <= 'z') || ('A' <= token && token <= 'Z') || ('0' <= token && token <= '9') ||
            token == '_' || token == '-' || token == '=' || token == '.' || token == ':' || token == ';' || token == '!' || token == '@' || token == '#' || token == '$' || token == '%' || token == '^' || token == '+' || token == '*' || token == '\'' || token == '|' || token == '(' || token == ')' ||
            (isData && (token == '/' || token == '\\' || token == ' ' || token == '{' || token == '}')))
        {
            string.push_back(token);
            next();
            continue;
        }

        return false;
    }
    return false;
};

template<typename NodeType>
class XMLStringParser : public XMLParser<NodeType>
{
public:
    XMLStringParser(const String &data) : data(data) {}
    bool hasSymbol() const { return position < data.size(); }
    bool atBegin() const { return position == 0; }
    bool atEnd() const { return position == data.size(); }
    char get() { return data[position]; }
    char read() { ++position; return data[position - 1]; }
    void next() { ++position; }
    void back() { --position; }
private:
    const String &data;
    String::size_type position = 0;
};

template<typename NodeType>
class XMLFileParser : public XMLParser<NodeType>
{
public:
    template<typename PathType>
    XMLFileParser(PathType &&path) : file() { file.open(std::forward<PathType>(path), AFileOpenMode::ReadBinary); skipBOM(); }
    ~XMLFileParser() { if (file.isOpen()) file.close(); }
    bool hasSymbol() const { return !file.atEnd(); }
    bool atBegin() const { return file.atBegin(); }
    bool atEnd() const { return file.atEnd(); }
    char get() { return file.peek(); }
    char read() { return file.take(); }
    void next() { file.skip(); }
    void back() { file.back(); }
    void skipBOM()
    {
        this->readTokens(std::array<uint8_t, 3>{0xEF, 0xBB, 0xBF});
    }
private:
    AFile file;
};

template<typename NodeType>
inline NodeType XMLParser<NodeType>::parse()
{
    NodeType document = NodeType();

    skipWhiteSpaces();
    if (atEnd())
    {
        return document;
    }
    if (readTokens(std::array<uint8_t, 5>{'<', '?', 'x', 'm', 'l'}))
    {
        NodeType processingInstruction = NodeType();
        if (readTokens(std::array<uint8_t, 3>{}))
        {

        }
        parseAttributes(processingInstruction);
        skipWhiteSpaces();
        if (!readTokens(std::array<uint8_t, 2>{'?', '>'}))
        {
            //error: the processing instruction is not closed, expected "?>"
        }
        processingInstruction;
    }

    NodeType rootNode = NodeType();
    parseNode(rootNode);
    return rootNode;
}

template<typename NodeType>
inline bool XMLParser<NodeType>::parseNode(NodeType &node)
{
    skipWhiteSpaces();
    if (atEnd())
    {
        return false;
    }
    if (!readToken('<'))
    {
        //error: extra symbols before node
        return false;
    }

    switch (get())
    {
    case '!':
        next();
        if (readTokens(std::array<uint8_t, 2>{ '-', '-'}))
        {
            if (skipUntilEndOf(std::array<uint8_t, 3>{ '-', '-', '>'}))
            {
                //error: the comment is not closed, expected "-->"
            }
        }
        break;
    default:
        if (!parseName(node))
        {
            return false;
        }
        parseAttributes(node);
        skipWhiteSpaces();

        if (readTokens(std::array<uint8_t, 2>{ '/', '>'}))
        {
            return true;
        }

        if (!readToken('>'))
        {
            return false;
        }

        if (parseContent(node))
        {
            if (readTokens(String("</") + node.name + ">"))
            {
                return true;
            }
        }

        while (!atEnd())
        {
            skipWhiteSpaces();
            NodeType child = NodeType();
            if (parseNode(child))
            {
                node.nodes.push_back(child);
            }
            else
            {
                return readTokens("/" + node.name + ">");
            }
        }
        break;
    }

    //error: unexpected symbol
    return false;
}

template<typename NodeType>
inline bool XMLParser<NodeType>::parseName(NodeType &node)
{
    if (atEnd())
    {
        return false;
    }

    return parseString(node.name, std::array<uint8_t, 6>{ ' ', '\t', '\r', '\n', '/', '>'});
}

template<typename NodeType>
inline bool XMLParser<NodeType>::parseAttributes(NodeType &node)
{
    while (!atEnd())
    {
        skipWhiteSpaces();
        String key;
        if (!parseString(key, std::array<uint8_t, 5>{ ' ', '\t', '\r', '\n', '=' }))
        {
            return false;
        }
        skipWhiteSpaces();
        if (!readToken('='))
        {
            return false;
        }
        skipWhiteSpaces();
        if (!readToken('"'))
        {
            return false;
        }
        String value;
        if (!parseString(value, std::array<uint8_t, 1>{'"'}, true))
        {
            return false;
        }
        if (!readToken('"'))
        {
            return false;
        }
        node.attributes.insert({ key, value });
    }
    return true;
}

template<typename NodeType>
inline bool XMLParser<NodeType>::parseContent(NodeType &node)
{
    if (atEnd())
    {
        return false;
    }

    return parseString(node.content, std::array<uint8_t, 1>{'<'}, true);
}

namespace XML
{
    inline XMLNode loadFromFile(const APath &path)
    {
        XMLFileParser<XMLNode> parser(path);
        return parser.parse();
    }

    inline bool saveToFile(const XMLNode &node, const APath &path, const String &indent = String("    "))
    {
        ADelegate<String(const XMLNode &, const String &, const String &)> XMLNodeToString = [&XMLNodeToString](const XMLNode &node, const String &currentIndent = String(), const String &indent = String())
        {
            auto XMLNodesToString = [&XMLNodeToString](const Array<XMLNode> &nodes, const String &currentIndent, const String &indent)
            {
                String data;
                for (auto &node : nodes)
                {
                    data += XMLNodeToString(node, currentIndent, indent);
                }
                return data;
            };

            auto XMLAttributesToString = [](const Map<String, String> &attributes)
            {
                String data;
                for (auto &attribute : attributes)
                {
                    data += " " + attribute.first + "=\"" + attribute.second + "\"";
                }
                return data;
            };

            String data;
            if (!node.nodes.empty())
            {
                data = currentIndent + "<" + node.name + XMLAttributesToString(node.attributes) + ">\r\n" + XMLNodesToString(node.nodes, currentIndent + indent, indent) + currentIndent + "</" + node.name + ">\r\n";
            }
            else if (!node.content.empty())
            {
                data = currentIndent + "<" + node.name + XMLAttributesToString(node.attributes) + ">" + node.content + "</" + node.name + ">\r\n";
            }
            else
            {
                data = currentIndent + "<" + node.name + XMLAttributesToString(node.attributes) + "/>\r\n";
            }
            return data;
        };

        AFile file;
        file.setPath(path);
        if (file.open(AFileOpenMode::WriteBinary))
        {
            file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n";
            std::string data = XMLNodeToString(node, String(), indent);
            file.write(data.data(), data.size());
            return true;
        }
        return false;
    }
}
