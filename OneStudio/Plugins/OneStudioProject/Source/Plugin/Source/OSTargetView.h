#pragma once

#include <Foundation>
#include <Experimental>

#include <OneStudioProjectLibrary>

namespace Ui {
class OSTargetView;
}

class OSTargetView : public UI::View
{
    SharedReference<OSProjectTargetInfoDataObject> currentTargetInfo;
    Array<SharedReference<OSProjectTargetInfoDataObject>> targetInfos;

public:
    explicit OSTargetView();
    ~OSTargetView();

    const SharedReference<OSProjectTargetInfoDataObject> &getCurrentTargetInfo()
    {
        return currentTargetInfo;
    }

    const Array<SharedReference<OSProjectTargetInfoDataObject>> &getTargetInfos() const
    {
        return this->targetInfos;
    }

    void setTargetInfos(const Array<SharedReference<OSProjectTargetInfoDataObject>> &targetInfos)
    {
        this->targetInfos = targetInfos;
        update();
    }

private:

    void update();

};
