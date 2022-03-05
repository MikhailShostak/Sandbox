namespace
{

struct ECSReflectionType
{
    ECSReflectionType()
    {
        Reflection::Add<ECS::EntityComponent>("ECS.EntityComponent");
        Reflection::Add<ECS::PersistentComponent>("ECS.PersistentComponent");

        Reflection::Add<ECS::HirerachyComponent>("ECS.HirerachyComponent");
        Reflection::Add<ECS::RootComponent>("ECS.RootComponent");

        Reflection::Add<ECS::MovementComponent>("ECS.MovementComponent");
        Reflection::Add<ECS::MovementSystem>("ECS.MovementSystem");
        Reflection::Add<ECS::PawnComponent>("ECS.PawnComponent");
        Reflection::Add<ECS::PawnSystem>("ECS.PawnSystem");

        Reflection::Add<ECS::CameraComponent>("ECS.CameraComponent");
        Reflection::Add<ECS::MeshComponent>("ECS.MeshComponent");
        Reflection::Add<ECS::TransformComponent>("ECS.TransformComponent");

        Reflection::Add<ECS::PostProcessStep>("ECS.PostProcessStep");
        Reflection::Add<ECS::GlowPostProcessStep>("ECS.GlowPostProcessStep");

        Reflection::Add<ECS::GraphicsSystem>("ECS.GraphicsSystem");
        Reflection::Add<ECS::LayoutSystem>("ECS.LayoutSystem");
        Reflection::Add<ECS::ImGuiSystem>("ECS.ImGuiSystem");

        Reflection::Add<ECS::UIViewComponent>("ECS.UIViewComponent");
        Reflection::Add<ECS::UIImageComponent>("ECS.UIImageComponent");
        Reflection::Add<ECS::UITextComponent>("ECS.UITextComponent");
        Reflection::Add<ECS::UIFlexBoxItemComponent>("ECS.UIFlexBoxItemComponent");
        Reflection::Add<ECS::UIFlexBoxLayoutComponent>("ECS.UIFlexBoxLayoutComponent");

        Reflection::Add<UI::AbsoluteLayout>("UI.AbsoluteLayout");
        Reflection::Add<UI::TextLayout>("UI.TextLayout");
        Reflection::Add<UI::ImageLayout>("UI.ImageLayout");
        Reflection::Add<UI::FlexBoxLayout>("UI.FlexBoxLayout");
    }
} inline ECSReflection;

}
