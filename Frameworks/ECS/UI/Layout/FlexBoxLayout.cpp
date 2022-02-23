namespace UI
{

bool/*Success*/ FlexBoxLayout::OnPrePass(ECS::Entity &Entity)
{
    auto [parent, hirerachy, layout] = Entity.FindComponents<ECS::UIViewComponent, ECS::HirerachyComponent, ECS::UIFlexBoxLayoutComponent>();
    if (!layout || !hirerachy)
    {
        return false;
    }


    hlslpp::int2 size = {};
    size_t i = 0;
    if (layout->Direction == UI::Direction::Vertical)
    {
        i = 1;
    }
    else
    {
        i = 0;
    }
    auto j = 1 - i;

    size = layout->StartPadding + layout->EndPadding;
    for (auto &e : hirerachy->Children)
    {
        auto [child, item] = e.GetComponents<ECS::UIViewComponent, ECS::UIFlexBoxItemComponent>();
        size.i32[i] += child.Size.i32[i];
        size.i32[i] += layout->Spacing;
        size.i32[j] = std::max(size.i32[j], child.Size.i32[j]);
    }

    parent->PreferedSize = size;

    return true;
}

bool/*Success*/ FlexBoxLayout::OnLayout(ECS::Entity &Entity)
{
    auto [parent, hirerachy, layout] = Entity.FindComponents<ECS::UIViewComponent, ECS::HirerachyComponent, ECS::UIFlexBoxLayoutComponent>();
    if (!layout || !hirerachy)
    {
        return false;
    }

    hlslpp::int2 offset = {};
    size_t i = 0;
    if (layout->Direction == UI::Direction::Vertical)
    {
        i = 1;
    }
    else
    {
        i = 0;
    }

    offset = layout->StartPadding;
    for (auto &e : hirerachy->Children)
    {
        auto [child, item] = e.GetComponents<ECS::UIViewComponent, ECS::UIFlexBoxItemComponent>();
        if (child.HorizontalSizePolicy == UI::SizePolicy::ContentWrapped)
        {
            child.Size.x = child.PreferedSize.x;
        }
        if (child.VerticalSizePolicy == UI::SizePolicy::ContentWrapped)
        {
            child.Size.y = child.PreferedSize.y;
        }

        child.Position.xy = offset;

        offset.i32[i] += child.Size.i32[i];
        offset.i32[i] += layout->Spacing;

        child.GlobalPosition = parent->GlobalPosition + child.Position;
    }

    return true;
};

}
