//CLASSGEN GENERATED REGION: Includes
#include "ProjectSettingsView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION
#include "OSTaskItemView.h"
#include "TaskView.gen.h"
#include "Main.h"
#include "OSPlatformPlugin.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ProjectSettingsView::ProjectSettingsView()
{
    Math::Transform transform_242;
    Math::Vector position_243;
    position_243.X = 0.000000;
    position_243.Y = 0.000000;
    position_243.Z = 0.000000;
    position_243.W = 0.000000;
    transform_242.Position = position_243;
    Math::Quaternion rotation_248;
    rotation_248.X = 0.000000;
    rotation_248.Y = 0.000000;
    rotation_248.Z = 0.000000;
    rotation_248.W = 1.000000;
    transform_242.Rotation = rotation_248;
    (*this).setTransform(transform_242);
    Math::IntegerVector size_253;
    size_253.X = 800.000000;
    size_253.Y = 800.000000;
    size_253.Z = 0.000000;
    size_253.W = 0.000000;
    (*this).setSize(size_253);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::SplitViewLayoutData item_266_0;
    item_266_0.PrimaryAlignment = Core::Alignment::Start;
    item_266_0.SecondaryAlignment = Core::Alignment::Start;
    UI::SplitViewLayoutData item_269_1;
    item_269_1.PrimaryAlignment = Core::Alignment::Start;
    item_269_1.SecondaryAlignment = Core::Alignment::Start;
    (*this).setData({item_266_0,item_269_1,});
    (*this).setDirection(UI::Direction::Horizontal);
    (*this).setSpacing(0.000000);
    Math::Offsets padding_274;
    padding_274.Top = 0.000000;
    padding_274.Right = 0.000000;
    padding_274.Bottom = 0.000000;
    padding_274.Left = 0.000000;
    (*this).setPadding(padding_274);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ProjectSettingsView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ProjectSettingsView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ProjectSettingsView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ProjectSettingsView");
    SharedReference<UI::FlexBox> sidebar = Create<UI::FlexBox>();
    (*sidebar).setName("Sidebar");
    Math::Transform transform_0;
    Math::Vector position_1;
    position_1.X = 0.000000;
    position_1.Y = 0.000000;
    position_1.Z = 0.000000;
    position_1.W = 0.000000;
    transform_0.Position = position_1;
    Math::Quaternion rotation_6;
    rotation_6.X = 0.000000;
    rotation_6.Y = 0.000000;
    rotation_6.Z = 0.000000;
    rotation_6.W = 1.000000;
    transform_0.Rotation = rotation_6;
    (*sidebar).setTransform(transform_0);
    Math::IntegerVector size_11;
    size_11.X = 0.000000;
    size_11.Y = 0.000000;
    size_11.Z = 0.000000;
    size_11.W = 0.000000;
    (*sidebar).setSize(size_11);
    (*sidebar).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*sidebar).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*sidebar).setAffectsParentLayout(false);
    UI::FlexBoxData item_20_0;
    item_20_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_22_1;
    item_22_1.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_24_2;
    item_24_2.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_26_3;
    item_26_3.Alignment = Core::Alignment::Start;
    (*sidebar).setData({item_20_0,item_22_1,item_24_2,item_26_3,});
    (*sidebar).setDirection(UI::Direction::Vertical);
    (*sidebar).setSpacing(0.000000);
    Math::Offsets padding_30;
    padding_30.Top = 0.000000;
    padding_30.Right = 0.000000;
    padding_30.Bottom = 0.000000;
    padding_30.Left = 0.000000;
    (*sidebar).setPadding(padding_30);
    SharedReference<UI::Label> targetsLabel = Create<UI::Label>();
    (*targetsLabel).setName("TargetsLabel");
    Math::Transform transform_35;
    Math::Vector position_36;
    position_36.X = 0.000000;
    position_36.Y = 0.000000;
    position_36.Z = 0.000000;
    position_36.W = 0.000000;
    transform_35.Position = position_36;
    Math::Quaternion rotation_41;
    rotation_41.X = 0.000000;
    rotation_41.Y = 0.000000;
    rotation_41.Z = 0.000000;
    rotation_41.W = 1.000000;
    transform_35.Rotation = rotation_41;
    (*targetsLabel).setTransform(transform_35);
    Math::IntegerVector size_46;
    size_46.X = 0.000000;
    size_46.Y = 0.000000;
    size_46.Z = 0.000000;
    size_46.W = 0.000000;
    (*targetsLabel).setSize(size_46);
    (*targetsLabel).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*targetsLabel).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*targetsLabel).setAffectsParentLayout(false);
    (*targetsLabel).setText("Targets");
    (*targetsLabel).setTextAlign(Core::TextAlign::Start);
    (*targetsLabel).setTextWrapping(Core::TextWrapping::Inline);
    (*sidebar).addView(targetsLabel);
    targetsListView = Create<UI::ListView>();
    (*targetsListView).setName("TargetsListView");
    Math::Transform transform_57;
    Math::Vector position_58;
    position_58.X = 0.000000;
    position_58.Y = 0.000000;
    position_58.Z = 0.000000;
    position_58.W = 0.000000;
    transform_57.Position = position_58;
    Math::Quaternion rotation_63;
    rotation_63.X = 0.000000;
    rotation_63.Y = 0.000000;
    rotation_63.Z = 0.000000;
    rotation_63.W = 1.000000;
    transform_57.Rotation = rotation_63;
    (*targetsListView).setTransform(transform_57);
    Math::IntegerVector size_68;
    size_68.X = 0.000000;
    size_68.Y = 0.000000;
    size_68.Z = 0.000000;
    size_68.W = 0.000000;
    (*targetsListView).setSize(size_68);
    (*targetsListView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*targetsListView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*targetsListView).setAffectsParentLayout(false);
    (*sidebar).addView(targetsListView);
    SharedReference<UI::Label> configurationsLabel = Create<UI::Label>();
    (*configurationsLabel).setName("ConfigurationsLabel");
    Math::Transform transform_76;
    Math::Vector position_77;
    position_77.X = 0.000000;
    position_77.Y = 0.000000;
    position_77.Z = 0.000000;
    position_77.W = 0.000000;
    transform_76.Position = position_77;
    Math::Quaternion rotation_82;
    rotation_82.X = 0.000000;
    rotation_82.Y = 0.000000;
    rotation_82.Z = 0.000000;
    rotation_82.W = 1.000000;
    transform_76.Rotation = rotation_82;
    (*configurationsLabel).setTransform(transform_76);
    Math::IntegerVector size_87;
    size_87.X = 0.000000;
    size_87.Y = 0.000000;
    size_87.Z = 0.000000;
    size_87.W = 0.000000;
    (*configurationsLabel).setSize(size_87);
    (*configurationsLabel).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*configurationsLabel).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*configurationsLabel).setAffectsParentLayout(false);
    (*configurationsLabel).setText("Configurations");
    (*configurationsLabel).setTextAlign(Core::TextAlign::Start);
    (*configurationsLabel).setTextWrapping(Core::TextWrapping::Inline);
    (*sidebar).addView(configurationsLabel);
    configurationsListView = Create<UI::ListView>();
    (*configurationsListView).setName("ConfigurationsListView");
    Math::Transform transform_98;
    Math::Vector position_99;
    position_99.X = 0.000000;
    position_99.Y = 0.000000;
    position_99.Z = 0.000000;
    position_99.W = 0.000000;
    transform_98.Position = position_99;
    Math::Quaternion rotation_104;
    rotation_104.X = 0.000000;
    rotation_104.Y = 0.000000;
    rotation_104.Z = 0.000000;
    rotation_104.W = 1.000000;
    transform_98.Rotation = rotation_104;
    (*configurationsListView).setTransform(transform_98);
    Math::IntegerVector size_109;
    size_109.X = 0.000000;
    size_109.Y = 0.000000;
    size_109.Z = 0.000000;
    size_109.W = 0.000000;
    (*configurationsListView).setSize(size_109);
    (*configurationsListView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*configurationsListView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*configurationsListView).setAffectsParentLayout(false);
    (*sidebar).addView(configurationsListView);
    (*this).addView(sidebar);
    contentView = Create<UI::PageView>();
    (*contentView).setName("ContentView");
    Math::Transform transform_117;
    Math::Vector position_118;
    position_118.X = 0.000000;
    position_118.Y = 0.000000;
    position_118.Z = 0.000000;
    position_118.W = 0.000000;
    transform_117.Position = position_118;
    Math::Quaternion rotation_123;
    rotation_123.X = 0.000000;
    rotation_123.Y = 0.000000;
    rotation_123.Z = 0.000000;
    rotation_123.W = 1.000000;
    transform_117.Rotation = rotation_123;
    (*contentView).setTransform(transform_117);
    Math::IntegerVector size_128;
    size_128.X = 0.000000;
    size_128.Y = 0.000000;
    size_128.Z = 0.000000;
    size_128.W = 0.000000;
    (*contentView).setSize(size_128);
    (*contentView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*contentView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*contentView).setAffectsParentLayout(false);
    UI::OverlayData item_137_0;
    Math::Offsets padding_138;
    padding_138.Top = 0.000000;
    padding_138.Right = 0.000000;
    padding_138.Bottom = 0.000000;
    padding_138.Left = 0.000000;
    item_137_0.Padding = padding_138;
    item_137_0.HorizontalAlignment = Core::Alignment::Start;
    item_137_0.VerticalAlignment = Core::Alignment::Start;
    UI::OverlayData item_145_1;
    Math::Offsets padding_146;
    padding_146.Top = 0.000000;
    padding_146.Right = 0.000000;
    padding_146.Bottom = 0.000000;
    padding_146.Left = 0.000000;
    item_145_1.Padding = padding_146;
    item_145_1.HorizontalAlignment = Core::Alignment::Start;
    item_145_1.VerticalAlignment = Core::Alignment::Start;
    (*contentView).setData({item_137_0,item_145_1,});
    (*contentView).setCurrentPage(0.000000);
    SharedReference<UI::FlexBox> targetSettingsContainer = Create<UI::FlexBox>();
    (*targetSettingsContainer).setName("TargetSettingsContainer");
    Math::Transform transform_154;
    Math::Vector position_155;
    position_155.X = 0.000000;
    position_155.Y = 0.000000;
    position_155.Z = 0.000000;
    position_155.W = 0.000000;
    transform_154.Position = position_155;
    Math::Quaternion rotation_160;
    rotation_160.X = 0.000000;
    rotation_160.Y = 0.000000;
    rotation_160.Z = 0.000000;
    rotation_160.W = 1.000000;
    transform_154.Rotation = rotation_160;
    (*targetSettingsContainer).setTransform(transform_154);
    Math::IntegerVector size_165;
    size_165.X = 0.000000;
    size_165.Y = 0.000000;
    size_165.Z = 0.000000;
    size_165.W = 0.000000;
    (*targetSettingsContainer).setSize(size_165);
    (*targetSettingsContainer).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*targetSettingsContainer).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*targetSettingsContainer).setAffectsParentLayout(false);
    UI::FlexBoxData item_174_0;
    item_174_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_176_1;
    item_176_1.Alignment = Core::Alignment::Start;
    (*targetSettingsContainer).setData({item_174_0,item_176_1,});
    (*targetSettingsContainer).setDirection(UI::Direction::Vertical);
    (*targetSettingsContainer).setSpacing(0.000000);
    Math::Offsets padding_180;
    padding_180.Top = 0.000000;
    padding_180.Right = 0.000000;
    padding_180.Bottom = 0.000000;
    padding_180.Left = 0.000000;
    (*targetSettingsContainer).setPadding(padding_180);
    stepsSettingsView = Create<UI::GroupView>();
    (*stepsSettingsView).setName("StepsSettingsView");
    Math::Transform transform_185;
    Math::Vector position_186;
    position_186.X = 0.000000;
    position_186.Y = 0.000000;
    position_186.Z = 0.000000;
    position_186.W = 0.000000;
    transform_185.Position = position_186;
    Math::Quaternion rotation_191;
    rotation_191.X = 0.000000;
    rotation_191.Y = 0.000000;
    rotation_191.Z = 0.000000;
    rotation_191.W = 1.000000;
    transform_185.Rotation = rotation_191;
    (*stepsSettingsView).setTransform(transform_185);
    Math::IntegerVector size_196;
    size_196.X = 0.000000;
    size_196.Y = 0.000000;
    size_196.Z = 0.000000;
    size_196.W = 0.000000;
    (*stepsSettingsView).setSize(size_196);
    (*stepsSettingsView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*stepsSettingsView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*stepsSettingsView).setAffectsParentLayout(false);
    (*targetSettingsContainer).addView(stepsSettingsView);
    targetSettingsView = Create<UI::GroupView>();
    (*targetSettingsView).setName("TargetSettingsView");
    Math::Transform transform_204;
    Math::Vector position_205;
    position_205.X = 0.000000;
    position_205.Y = 0.000000;
    position_205.Z = 0.000000;
    position_205.W = 0.000000;
    transform_204.Position = position_205;
    Math::Quaternion rotation_210;
    rotation_210.X = 0.000000;
    rotation_210.Y = 0.000000;
    rotation_210.Z = 0.000000;
    rotation_210.W = 1.000000;
    transform_204.Rotation = rotation_210;
    (*targetSettingsView).setTransform(transform_204);
    Math::IntegerVector size_215;
    size_215.X = 0.000000;
    size_215.Y = 0.000000;
    size_215.Z = 0.000000;
    size_215.W = 0.000000;
    (*targetSettingsView).setSize(size_215);
    (*targetSettingsView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*targetSettingsView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*targetSettingsView).setAffectsParentLayout(false);
    (*targetSettingsContainer).addView(targetSettingsView);
    (*contentView).addView(targetSettingsContainer);
    configurationsSettingsView = Create<UI::GroupView>();
    (*configurationsSettingsView).setName("ConfigurationsSettingsView");
    Math::Transform transform_223;
    Math::Vector position_224;
    position_224.X = 0.000000;
    position_224.Y = 0.000000;
    position_224.Z = 0.000000;
    position_224.W = 0.000000;
    transform_223.Position = position_224;
    Math::Quaternion rotation_229;
    rotation_229.X = 0.000000;
    rotation_229.Y = 0.000000;
    rotation_229.Z = 0.000000;
    rotation_229.W = 1.000000;
    transform_223.Rotation = rotation_229;
    (*configurationsSettingsView).setTransform(transform_223);
    Math::IntegerVector size_234;
    size_234.X = 0.000000;
    size_234.Y = 0.000000;
    size_234.Z = 0.000000;
    size_234.W = 0.000000;
    (*configurationsSettingsView).setSize(size_234);
    (*configurationsSettingsView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*configurationsSettingsView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*configurationsSettingsView).setAffectsParentLayout(false);
    (*contentView).addView(configurationsSettingsView);
    (*this).addView(contentView);
}
//CLASSGEN END REGION



/*ProjectSettingsView::ProjectSettingsView()
{
    if (!getName())
    {
        setName("ProjectSettingsView");
    }
    setSizePolicy(UI::SizePolicy::Expanded);

    targetsListView->setName("TargetsListView");
    targetsListView->setSizePolicy(UI::SizePolicy::ContentWrapped, UI::SizePolicy::ContentWrapped);
    addView(targetsListView);

    configurationsListView->setName("ConfigurationsListView");
    configurationsListView->setSizePolicy(UI::SizePolicy::ContentWrapped, UI::SizePolicy::ContentWrapped);
    addView(configurationsListView);

    stepsSettingsView->setName("stepsSettingsView");
    stepsSettingsView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
    addView(stepsSettingsView);

    targetSettingsView->setName("TargetSettingsView");
    targetSettingsView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
    addView(targetSettingsView);

    configurationsSettingsView->setName("configurationsSettingsView");
    configurationsSettingsView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
    addView(configurationsSettingsView);

    RelativeLayout* relativeLayout = new RelativeLayout();
    relativeLayout->addConstraint(*targetsListView, ConstraintAnchor::Left, *this, ConstraintAnchor::Left);
    relativeLayout->addConstraint(*targetsListView, ConstraintAnchor::Top, *this, ConstraintAnchor::Top);

    relativeLayout->addConstraint(*configurationsListView, ConstraintAnchor::Left, *this, ConstraintAnchor::Left);
    relativeLayout->addConstraint(*configurationsListView, ConstraintAnchor::Top, *targetsListView, ConstraintAnchor::Bottom);

    relativeLayout->addConstraint(*stepsSettingsView, ConstraintAnchor::Right, *this, ConstraintAnchor::Right);
    relativeLayout->addConstraint(*stepsSettingsView, ConstraintAnchor::Top, *this, ConstraintAnchor::Top);
    relativeLayout->addConstraint(*stepsSettingsView, ConstraintAnchor::Left, *targetsListView, ConstraintAnchor::Right);

    relativeLayout->addConstraint(*targetSettingsView, ConstraintAnchor::Right, *this, ConstraintAnchor::Right);
    relativeLayout->addConstraint(*targetSettingsView, ConstraintAnchor::Top, *stepsSettingsView, ConstraintAnchor::Bottom);
    relativeLayout->addConstraint(*targetSettingsView, ConstraintAnchor::Left, *targetsListView, ConstraintAnchor::Right);

    relativeLayout->addConstraint(*configurationsSettingsView, ConstraintAnchor::Right, *this, ConstraintAnchor::Right);
    relativeLayout->addConstraint(*configurationsSettingsView, ConstraintAnchor::Top, *targetSettingsView, ConstraintAnchor::Bottom);
    relativeLayout->addConstraint(*configurationsSettingsView, ConstraintAnchor::Left, *targetsListView, ConstraintAnchor::Right);
    setLayout(relativeLayout);
}

ProjectSettingsView::~ProjectSettingsView()
{
    closeAllViews();
}*/

void ProjectSettingsView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    this->primaryNodes = {
        { 200, 200 },
        { 0, 0 },
    };
    this->secondaryNodes = {
        { 0, 0 },
    };

    targetsListView->setAdapter(this);
    SharedReference<UI::MenuView> targetsListMenu = Create<UI::MenuView>();
    targetsListMenu->addAction({ "Add New Target", [this](UI::TapGestureEvent &event) {
        auto index = project->ProjectData.Targets.size();
        project->addTarget(index);
        targetsListView->notifyInsertItems(index);
    } });
    AttachMenuToView(targetsListView, targetsListMenu);

    configurationsListView->setAdapter(this);
    SharedReference<UI::MenuView> configurationsListMenu = Create<UI::MenuView>();
    configurationsListMenu->addAction({ "Add New Configuration", [this](UI::TapGestureEvent &event) {
        auto index = project->ProjectData.Configurations.size();
        project->addConfiguration(index);
        configurationsListView->notifyInsertItems(index);
    } });
    AttachMenuToView(configurationsListView, configurationsListMenu);

    stepsSettingsView->setProxyAdapter(this);
    targetSettingsView->setProxyAdapter(this);
    configurationsSettingsView->setProxyAdapter(this);
}

UI::SizeType ProjectSettingsView::getCountItems(const AObject &sender) const
{
    if (!project)
    {
        return 0;
    }
    return &sender == targetsListView.data() ? project->getTargetData().size() : project->getCountConfigurations();
}

SharedReference<UI::View> ProjectSettingsView::provideViewForItem(const AObject &sender, UI::SizeType index)
{
    if (&sender == targetsListView.data())
    {
        auto label = Create<UI::DefaultTextItemView>();
        label->setText(project->getTargetData()[index].Name);
        label->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        SharedReference<UI::MenuView> menu = Create<UI::MenuView>();
        menu->addAction({ "Add Before", [this, label](UI::TapGestureEvent &event) {
            auto index = targetsListView->getIndexForItemView(*label);
            project->addTarget(index);
            targetsListView->notifyInsertItems(index);
        } });
        menu->addAction({ "Add After", [this, label](UI::TapGestureEvent &event) {
            auto index = targetsListView->getIndexForItemView(*label) + 1;
            project->addTarget(index);
            targetsListView->notifyInsertItems(index);
        } });
        menu->addAction({ "Remove", [this, label](UI::TapGestureEvent &event) {
            auto index = targetsListView->getIndexForItemView(*label);
            project->removeTarget(index);
            targetsListView->notifyRemoveItems(index);
        } });

        SharedReference<UI::DefaultTextItemView> sharedLabel = label;
        AttachMenuToView(sharedLabel, menu);
        return sharedLabel;
    }
    else
    {
        auto label = Create<UI::DefaultTextItemView>();
        label->setText(project->getConfigurationName(index));
        label->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        SharedReference<UI::MenuView> menu = Create<UI::MenuView>();
        menu->addAction({ "Add Before", [this, label](UI::TapGestureEvent &event) {
            auto index = configurationsListView->getIndexForItemView(*label);
            project->addConfiguration(index);
            configurationsListView->notifyInsertItems(index);
        } });
        menu->addAction({ "Add After", [this, label](UI::TapGestureEvent &event) {
            auto index = configurationsListView->getIndexForItemView(*label) + 1;
            project->addConfiguration(index);
            configurationsListView->notifyInsertItems(index);
        } });
        menu->addAction({ "Remove", [this, label](UI::TapGestureEvent &event) {
            auto index = configurationsListView->getIndexForItemView(*label);
            project->removeConfiguration(index);
            configurationsListView->notifyRemoveItems(index);
        } });

        SharedReference<UI::DefaultTextItemView> sharedLabel = label;
        AttachMenuToView(sharedLabel, menu);
        return sharedLabel;
    }
}

size_t ProjectSettingsView::getCountGroups(const AObject &sender) const
{
    if (&sender == stepsSettingsView.data())
    {
        return currentTargetData.Actions.size() + 1; //+1 For running step
    }
    else
    {
        return &sender == targetSettingsView.data() ? currentTargetSettings.size() : currentConfigurationSettings.size();
    }
}

size_t ProjectSettingsView::getCountItems(const AObject &sender, UI::SizeType groupIndex) const
{
    if (&sender == stepsSettingsView.data())
    {
        if (groupIndex == currentTargetData.Actions.size()) //For running step
        {
            return 2;
        }

        return currentTargetData.Actions[groupIndex].Tasks.size();
    }
    else
    {
        return 1;
    }
}

SharedReference<UI::View> ProjectSettingsView::provideViewForGroup(const AObject &sender, UI::SizeType groupIndex)
{
    if (&sender == stepsSettingsView.data())
    {
        if (groupIndex == currentTargetData.Actions.size()) //For running step
        {
            auto v = Create<UI::DefaultTextItemView>();
            v->setText("Running");
            return v;
        }

        UI::TextButton *header = Create<UI::TextButton>();
        header->setText(currentTargetData.Actions[groupIndex].Name);
        header->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        header->eventChannel.registerDelegate<UI::TapGestureEvent>([this, header](UI::TapGestureEvent &event) {
            size_t groupIndex = stepsSettingsView->getGroupIndexForItemView(*header);
            auto &targetTasks = currentTargetData.Actions[groupIndex].Tasks;
            size_t newIndex = targetTasks.size();

            OneStudioProject2::Task task;
            task.Type = "com.InsaneTeam.OneStudio.Project.TargetTasks.Extecute";
            task.Title = "New Task";
            targetTasks.append(task);

            stepsSettingsView->notifyInsertItemsInGroup(groupIndex, newIndex, 1);
        });
        return header;
    }
    else
    {
        APair<String, SharedReference<OSSettings>> settings = &sender == targetSettingsView.data() ? currentTargetSettings[groupIndex] : currentConfigurationSettings[groupIndex];
        auto v = Create<UI::DefaultTextItemView>();
        v->setText(settings.first);
        return v;
    }
}

SharedReference<UI::View> ProjectSettingsView::provideViewForItem(const AObject &sender, UI::SizeType groupIndex, UI::SizeType itemIndex)
{
    if (&sender == stepsSettingsView.data())
    {
        if (groupIndex == currentTargetData.Actions.size())//For running step
        {
            UI::Overlay *overlay = Create<UI::Overlay>();
            auto label = Create<UI::DefaultTextItemView>();
            label->setText(itemIndex == 0 ? "Command" : "Arguments");
            label->setSize(Math::IntegerVector{ 200, 0 });
            label->setSizePolicy(UI::SizePolicy::Fixed, UI::SizePolicy::ContentWrapped);
            overlay->addView(label);
            UI::TextField *textField = Create<UI::TextField>();
            textField->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
            if (currentTargetData.Name)
            {
                if (itemIndex == 0)
                {
                    textField->setText(currentTargetData.Run.Command);
                    textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                        currentTargetData.Run.Command = event.getText();
                    });
                }
                else
                {
                    textField->setText(String::join(currentTargetData.Run.Arguments, ';'));
                    textField->eventChannel.registerDelegate([this](UI::TextEditFinishedEvent &event) {
                        currentTargetData.Run.Arguments = event.getText().split(';');
                    });
                }
            }
            overlay->addView(textField);
            overlay->addData(UI::OverlayData{ UIOffsets{ 0, 0, 0, 0 }, { Core::Alignment::Start, Core::Alignment::Center } });
            overlay->addData(UI::OverlayData{ UIOffsets{ 0, 0, 0, 200 }, { Core::Alignment::Start, Core::Alignment::Center } });
            overlay->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
            return overlay;
        }

        TaskView *taskView = Create<TaskView>();
		//UI::OSTaskItemView *taskView = Create<UI::OSTaskItemView>();
        const OneStudioProject2::Task &taskData = currentTargetData.Actions[groupIndex].Tasks[itemIndex];
        for (OSTargetTask *task : tasks)
        {
            if (task->getPackage() == taskData.Type)
            {
                taskView->setTask(task);
                break;
            }
        }
        taskView->setTaskData(taskData);
        taskView->TaskChanged = [this, taskView]() {
            size_t groupIndex = stepsSettingsView->getGroupIndexForItemView(*taskView);
            size_t itemIndex = stepsSettingsView->getGroupItemIndexForItemView(*taskView);
            currentTargetData.Actions[groupIndex].Tasks[itemIndex] = taskView->getTaskData();
            project->ProjectData.Targets[currentTarget2] = currentTargetData;//TODO:temp
        };
        return taskView;
    }
    else
    {
        struct OSSettingsController : public UI::GroupView, public UI::GroupAdapter
        {
            SharedReference<OSSettings> settings;

            bool shouldAddTouchGestureRecognizerToItem(UI::SizeType groupIndex, UI::SizeType itemIndex) const override { return false; }
            bool shouldReceiveInputFromItem(UI::SizeType groupIndex, UI::SizeType itemIndex) const override { return false; }
            UI::SizeType getCountGroups(const AObject &sender) const override { return settings->getGroupsCount(); }
            UI::SizeType getCountItems(const AObject &sender, UI::SizeType groupIndex) const override { return settings->getRowsCount(groupIndex); }
            SharedReference<UI::View> provideViewForGroup(const AObject &sender, UI::SizeType groupIndex) override
            {
                UI::Label* b = Create<UI::Label>(settings->getGroupTitle(groupIndex));
                b->setSize(Math::IntegerVector{ 780, 16 }); //TODO: Fix expanded layout
                b->setSizePolicy(UI::SizePolicy::Fixed, UI::SizePolicy::Fixed);
                auto v = Create<UI::DefaultTextItemView>();
                v->setText(settings->getGroupTitle(groupIndex));
                return v;
            }
            SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType groupIndex, UI::SizeType itemIndex) override
            {
                UI::FlexBox *itemView = Create<UI::FlexBox>();
                itemView->setData({ {}, {} });
                itemView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);

                auto nameView = Create<UI::DefaultTextItemView>();
                nameView->setText(settings->getItem(groupIndex, itemIndex, 0));
                nameView->setSizePolicy(UI::SizePolicy::Fixed, UI::SizePolicy::ContentWrapped);
                nameView->setSize(Math::IntegerVector{ 200, 20 });
                itemView->addView(nameView);

                SharedReference<UI::TextField> view = Create<UI::TextField>(settings->getItem(groupIndex, itemIndex, 1));
                view->setPlaceholder(settings->getItemPlaceholder(groupIndex, itemIndex, 1));
                view->eventChannel.registerDelegate<UI::TextEditFinishedEvent>([this, itemView](UI::TextEditFinishedEvent &event) {
                    settings->onItemChange(getGroupIndexForItemView(*itemView), getGroupItemIndexForItemView(*itemView), 1, event.getText());
                });
                itemView->addView(view);

                return itemView;
            }
        };

        OSSettingsController *settingsView = Create<OSSettingsController>();
        settingsView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
        settingsView->settings = &sender == targetSettingsView.data() ? currentTargetSettings[groupIndex].second : currentConfigurationSettings[groupIndex].second;
        settingsView->setProxyAdapter(settingsView);

        return settingsView;
    }
}

void ProjectSettingsView::updateTaskData()
{

}

void ProjectSettingsView::updateProjectData()
{
    targetsListView->notifyUpdateAllItems();
    configurationsListView->notifyUpdateAllItems();
    /*ui->projectSettingsListView->clear();
    ui->targetListView->clear();

    if(!project)
    {
        return;
    }

    for(auto &settingsPair : project->getSettings())
    {
        ui->projectSettingsListView->addItem(settingsPair.first.toUtf8().data());
    }

    for(auto &target : project->getTargetInfos())
    {
        ui->targetListView->addItem(target->getName().toUtf8().data());
    }

    ui->targetListView->setCurrentRow(0);*/
}

void ProjectSettingsView::onItemSelected(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType index)
{
    if (&sender == targetsListView.data())
    {
        currentTarget2 = index;

        currentTargetData = project->getTargetData()[index];

        stepsSettingsView->notifyUpdateAllItems();

        currentTargetSettings.clear();
        for (auto &settingsPair : currentTargetData.settings)
        {
            currentTargetSettings.append(settingsPair);
        }

        ProjectContext->updateRootEnvironment(TaskData{ project, currentTargetData }, currentTargetData);
        targetSettingsView->notifyUpdateAllItems();
        contentView->setCurrentPage(0);
    }
    else
    {
        currentConfigurationSettings.clear();
        for (auto &settingsPair : project->getConfigurationSettings(index))
        {
            currentConfigurationSettings.append(settingsPair);
        }

        configurationsSettingsView->notifyUpdateAllItems();
        contentView->setCurrentPage(1);
    }

    event.accept();
}

void ProjectSettingsView::selectProjectSettings(int index)
{
    if (!project)
    {
        return;
    }

    if ((index < 0) || (index >= int(project->getSettings().size())))
    {
        return;
    }

    /*ui->projectSettingsView->setData(project->getSettings().at(ui->projectSettingsListView->currentItem()->text().toUtf8().data()));*/
}

void ProjectSettingsView::selectTargetSettings(int index)
{
    if (!project)
    {
        return;
    }

    if ((index < 0) || (index >= int(currentTargetData.settings.size())))
    {
        return;
    }

    /*ui->targetSettingsView->setData(currentTargetData.settings.at(ui->targetSettingsListView->currentItem()->text().toUtf8().data()));*/
}

// *** Targets *** //

/*void ProjectSettingsView::addTarget(size_t index)
{
    if(!project)
    {
        return;
    }

    if(index == 0)
    {
        return;
    }

    String nextTargetName;
    int number = 0;
    bool exists;
    do
    {
        exists = false;
        nextTargetName = number == 0 ? "New Target" : fmt::format("New Target {}", number);
        for(auto i = 0; i < ui->targetListView->count(); ++i)
        {
            if(ui->targetListView->item(i)->text().toUtf8().data() == nextTargetName)
            {
                exists = true;
                break;
            }
        }
        ++number;
    }
    while(exists);

    auto targetInfo = project->createTargetInfo(nextTargetName);
    ui->targetListView->addItem(targetInfo->getName().toUtf8().data());
    ui->targetListView->setCurrentRow(ui->targetListView->count() - 1);
    ui->addTargetComboBox->setCurrentIndex(0);
}

void ProjectSettingsView::removeTarget(size_t index)
{
    if(!ui->targetListView->currentItem())
    {
        return;
    }

    closeAllViews();

    project->removeTargetInfo(ui->targetListView->currentRow());
    int index = ui->targetListView->currentRow();
    ui->targetListView->setCurrentRow(-1);
    delete ui->targetListView->item(index);
}*/

void ProjectSettingsView::addTargetDependence(size_t index)
{
    /*if(!project)
    {
        return;
    }

    if(index == 0 || index == -1)
    {
        return;
    }

    ui->addTargetDependenceComboBox->setCurrentIndex(0);*/
}

void ProjectSettingsView::updateTargetDependencies(size_t index)
{
    /*if(!project)
    {
        return;
    }

    ui->addTargetDependenceComboBox->clear();
    ui->addTargetDependenceComboBox->addItem("Add target");

    if(index == -1)
    {
        return;
    }

    for(auto i = 0; i < project->getTargetInfos().size(); ++i)
    {
        if(i == index)
        {
            continue;
        }

        ui->addTargetDependenceComboBox->addItem(project->getTargetInfos().at(i)->getName().toUtf8().data());
    };*/
}

void ProjectSettingsView::selectTarget(size_t index)
{
    //     if(!project)
    //     {
    //         return;
    //     }
    // 
    //     index = ui->targetListView->currentRow();
    // 
    //     updateTargetDependencies(index);
    //     closeAllViews();
    // 
    //     if(index == -1)
    //     {
    //         ui->targetNameLabel->clear();
    //         return;
    //     }
    // 
    //     if(index >= project->getTargetInfos().size())
    //     {
    //         ui->targetNameLabel->clear();
    //         return;
    //     }
    // 
    //     auto targetInfo = project->getTargetInfos().at(index);
    // 
    //     /*auto it = PlatformPlugins.find(targetInfo->getPackage());
    //     if(it == PlatformPlugins.end())
    //     {
    //         ui->targetNameLabel->clear();
    //         return;
    //     }
    // 
    //     auto targetSettingsView = it->second->getTargetSettingsView();
    // 
    //     if(!targetSettingsView)
    //     {
    //         ui->targetNameLabel->clear();
    //         return;
    //     }*/
    // 
    //     ui->targetNameLabel->setText(targetInfo->getName().toUtf8().data());
    // 
    //     /*ui->targetSettingsView->layout()->addWidget(targetSettingsView.data());
    //     targetSettingsView->setParent(ui->targetSettingsView);
    //     targetSettingsView->show();*/
    // 
    //     currentTarget = project->findTarget(targetInfo);
    // 
    //     ProjectContext->updateRootEnvironment(*project, *targetInfo, *currentTarget);
    // 
    //     ui->buildStepTaskView->setTarget(currentTarget);
    //     ui->cleanStepTaskView->setTarget(currentTarget);
    //     ui->installStepTaskView->setTarget(currentTarget);
    //     ui->uninstallStepTaskView->setTarget(currentTarget);
    // 
    //     ui->targetSettingsListView->clear();
    //     for(auto &settingsPair : currentTarget->settings)
    //     {
    //         ui->targetSettingsListView->addItem(settingsPair.first.toUtf8().data());
    //     }
}

void ProjectSettingsView::closeAllViews()
{
    //ui->targetSettingsView->setData(nullptr);
}



//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
