#include "OSSettings.h"

#include "Main.h"

String OSSettings::processWithEnvironment(const String &string, SizeType groupIndex, SizeType rowIndex, SizeType columnIndex) const
{
    if(getParent())
    {
        return OSSettings::processWithEnvironment(string, {{"Inherits", parent->getItemValue(groupIndex, rowIndex, columnIndex)}});
    }
    else
    {
        return OSSettings::processWithEnvironment(string);
    }
}

String OSSettings::processWithEnvironment(const String &string, const StringsHashMap &additionalValues)
{
    String result;
    for(String::SizeType index = 0; index < string.size(); ++index)
    {
        if(string[index] == '$')
        {
            ++index;
            if(index < string.size() && string[index] == '(')
            {
                ++index;
                auto end = string.indexOf(')', index);
                if(end == String::InvalidSize)
                {
                    result.append(string.mid(index - 2));
                }
                else
                {
                    String variable = string.mid(index, end - index);
                    auto it = additionalValues.find(variable);
                    if(it != additionalValues.end())
                    {
                        result.append(it->second);
                    }
                    else
                    {
                        auto it = ProjectContext->environment.last().find(variable);
                        if(it != ProjectContext->environment.last().end())
                        {
                            result.append(it->second);
                        }
                    }
                    index = end;
                }
            }
        }
        else
        {
            /*if(string[index] == '/')
            {
                result.append(APathSeparator);
            }
            else*/
            {
                result.append(string.at(index));
            }
        }
    }

    return result;
}
