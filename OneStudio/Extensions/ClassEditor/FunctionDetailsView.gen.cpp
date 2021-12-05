//CLASSGEN GENERATED REGION: Includes
#include "FunctionDetailsView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FunctionDetailsView::FunctionDetailsView()
{
    UI::FlexBoxData item_39_0;
    UI::FlexBoxData item_40_1;
    UI::FlexBoxData item_41_2;
    UI::FlexBoxData item_42_3;
    UI::FlexBoxData item_43_4;
    UI::FlexBoxData item_44_5;
    UI::FlexBoxData item_45_6;
    UI::FlexBoxData item_46_7;
    (*this).setData({item_39_0,item_40_1,item_41_2,item_42_3,item_43_4,item_44_5,item_45_6,item_46_7,});
    (*this).setDirection(UI::Direction::Vertical);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FunctionDetailsView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void FunctionDetailsView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
LegacyClassGen::FunctionInfo FunctionDetailsView::getFunction() const
{
    return this->Function;
}
void FunctionDetailsView::setFunction(LegacyClassGen::FunctionInfo const &Function)
{
    this->Function = Function;
}
void FunctionDetailsView::setFunction(LegacyClassGen::FunctionInfo &&Function)
{
    this->Function = std::move(Function);
}
void FunctionDetailsView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("FunctionDetailsView");
    SharedReference<UI::Label> nameLabel = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*nameLabel).setName("NameLabel");
    {
    }
    (*nameLabel).setText("Name");
    (*this).addView(nameLabel);
    nameView = CreateShared<UI::TextField>([this](UI::TextField *v)
    {
    }
);
    (*nameView).setName("NameView");
    {
    }
    (*this).addView(nameView);
    SharedReference<UI::Label> inputArgumentsLabel = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*inputArgumentsLabel).setName("InputArgumentsLabel");
    {
    }
    (*inputArgumentsLabel).setText("InputArguments");
    (*this).addView(inputArgumentsLabel);
    inputArgumentsAddButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*inputArgumentsAddButton).setName("InputArgumentsAddButton");
    {
    }
    (*inputArgumentsAddButton).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*inputArgumentsAddButton).setText("Add");
    (*this).addView(inputArgumentsAddButton);
    inputArgumentsView = CreateShared<UI::ListView>([this](UI::ListView *v)
    {
    }
);
    (*inputArgumentsView).setName("InputArgumentsView");
    {
        (*inputArgumentsView).CountItems = [this]()        {
            return Function.InputArguments.size();
        };
;
        (*inputArgumentsView).Item = [this](SizeInteger const& Index) -> SharedReference<UI::View>         {
            auto instance = CreateShared<UI::TextField>();
            instance->setText(writeRecursively(Function.InputArguments[Index].Type) + " " + Function.InputArguments[Index].Name);
            return instance;
        };
;
    }
    (*inputArgumentsView).setAffectsParentLayout(true);
    (*this).addView(inputArgumentsView);
    SharedReference<UI::Label> outputArgumentsLabel = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*outputArgumentsLabel).setName("OutputArgumentsLabel");
    {
    }
    (*outputArgumentsLabel).setText("OutputArguments");
    (*this).addView(outputArgumentsLabel);
    outputArgumentsAddButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*outputArgumentsAddButton).setName("OutputArgumentsAddButton");
    {
    }
    (*outputArgumentsAddButton).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*outputArgumentsAddButton).setText("Add");
    (*this).addView(outputArgumentsAddButton);
    outputArgumentsView = CreateShared<UI::ListView>([this](UI::ListView *v)
    {
    }
);
    (*outputArgumentsView).setName("OutputArgumentsView");
    {
        (*outputArgumentsView).CountItems = [this]()        {
            return Function.OutputArguments.size();
        };
;
        (*outputArgumentsView).Item = [this](SizeInteger const& Index) -> SharedReference<UI::View>         {
            auto instance = CreateShared<UI::TextField>();
            instance->setText(writeRecursively(Function.OutputArguments[Index].Type) + " " + Function.OutputArguments[Index].Name);
            return instance;
        };
;
    }
    (*outputArgumentsView).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*outputArgumentsView).setAffectsParentLayout(true);
    (*this).addView(outputArgumentsView);
}
//CLASSGEN END REGION

void FunctionDetailsView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    
    nameView->eventChannel.registerDelegate([&](UI::TextEditFinishedEvent &event) {
        String oldName = Function.Identifier;
        String newName = event.getText();
        if (onNameChanged)
        {
            if (onNameChanged(oldName, newName))
            {
                this->Function.Identifier = newName;
                if (onChanged)
                {
                    onChanged(Function);
                    return;
                }
            }
        }
    });

    inputArgumentsAddButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
        LegacyClassGen::Parameter p;
        p.Name = "NewArgument";
        p.Type.Name = "Boolean";

        this->Function.InputArguments.push_back(p);
        onChanged(Function);
        inputArgumentsView->notifyUpdateAllItems();
    });

    outputArgumentsAddButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
        LegacyClassGen::Parameter p;
        p.Name = "NewArgument";
        p.Type.Name = "Boolean";

        this->Function.OutputArguments.push_back(p);
        onChanged(Function);
        outputArgumentsView->notifyUpdateAllItems();
    });
}

void FunctionDetailsView::setFunctionInfo(const LegacyClassGen::FunctionInfo &data)
{
    nameView->setText(data.Identifier);

    Function = data;

    inputArgumentsView->notifyUpdateAllItems();
    outputArgumentsView->notifyUpdateAllItems();
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
