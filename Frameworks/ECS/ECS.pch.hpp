#pragma once

#include <Graphics.pch.hpp>

#include "ECSUtils.hpp"
#include "System/System.hpp"
#include "Scene/EScene.hpp"
#include "Scene/Entity.hpp"
#include "Scene/EntityComponent.hpp"
#include "Scene/PersistentComponent.hpp"
#include "Scene/SceneUtils.hpp"
#include "Scene/EntityComponentAllocation.hpp"

#include "Utils/MovementComponent.hpp"
#include "Utils/MovementSystem.hpp"

#include "Utils/PawnComponent.hpp"
#include "Utils/PawnSystem.hpp"

#include "Graphics/PostProcess/PostProcessStep.hpp"
#include "Graphics/PostProcess/GlowPostProcessStep.hpp"

#include "Graphics/MeshComponent.hpp"
#include "Graphics/TransformComponent.hpp"
#include "Graphics/GraphicsSystem.hpp"
#include "Graphics/CameraComponent.hpp"

#include "UI/UIUtils.hpp"
#include "UI/Layout/Layout.hpp"
#include "UI/Layout/LayoutSystem.hpp"
#include "UI/Layout/ImageLayout.hpp"
#include "UI/Layout/TextLayout.hpp"
#include "UI/Layout/AbsoluteLayout.hpp"
#include "UI/Layout/FlexBoxLayout.hpp"
#include "UI/Layout/UIFlexBoxItemComponent.hpp"
#include "UI/Layout/UIFlexBoxLayoutComponent.hpp"
#include "UI/ImGuiSystem.hpp"
#include "UI/UIImageComponent.hpp"
#include "UI/UITextComponent.hpp"
#include "UI/UIViewComponent.hpp"

#include "Utils/HirerachyComponent.hpp"
#include "Utils/HirerachyFunctions.hpp"
#include "Utils/RootComponent.hpp"

#include "ECSReflection.hpp"
