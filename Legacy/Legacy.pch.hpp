#pragma once

#include <Frameworks.pch.hpp>

#include "Assets/Interface/AssetsRepository.h"
#include "Assets/Interface/Includes/AssetManager.h"
#include "BuildSystem/Interface/ArchiverSettings.gen.h"
#include "BuildSystem/Interface/BuildingSettings.gen.h"
#include "BuildSystem/Interface/CompilationSettings.gen.h"
#include "BuildSystem/Interface/CompilerSettings.gen.h"
#include "BuildSystem/Interface/FilesSettings.gen.h"
#include "BuildSystem/Interface/LinkageSettings.gen.h"
#include "BuildSystem/Interface/LinkerSettings.gen.h"
#include "BuildSystem/Interface/Toolchain.hpp"
#include "Console/Interface/Console.h"
#include "Data/Interface/AJSON.h"
#include "Data/Interface/AJSONArray.h"
#include "Data/Interface/AJSONError.h"
#include "Data/Interface/AJSONObject.h"
#include "Data/Interface/AJSONParser.h"
#include "Data/Interface/AJSONSerializedObject.h"
#include "Data/Interface/AJSONValue.h"
#include "Data/Interface/MetaObjectSerializationHelper.h"
#include "Data/Interface/XML.h"
#include "Data/Interface/XMLNode.h"
#include "Data/Interface/XMLParser.h"
#include "Experimental/Classes.h"
#include "Experimental/Interface/SuggestionsModel.h"
#include "Experimental/Interface/ViewFactory.h"
#include "Experimental/Interface/Includes/ApplicationHeader.gen.h"
#include "Experimental/Interface/Includes/CommandShortcut.gen.h"
#include "Experimental/Interface/Includes/Renderer.gen.h"
#include "Experimental/Interface/Includes/Space.gen.h"
#include "Experimental/Interface/Includes/SplineComponent.gen.h"
#include "Experimental/Interface/Includes/SystemFunctions.h"
#include "ExperimentalClasses/Textures.h"
//#include "Extensions/Interface/Includes/ExtensionsComponent.gen.h"
#include "Flow/Interface/Includes/FlowState.gen.h"
#include "Flow/Interface/Includes/WindowFlowState.gen.h"
#include "Fonts/Interface/AFont.h"
#include "Fonts/Interface/AFontEngine.h"
#include "Fonts/Interface/Includes/TextAlign.gen.h"
#include "Fonts/Interface/Includes/TextWrapping.gen.h"
#include "Foundation/Interface/AApplication.h"
#include "Foundation/Interface/AApplicationContext.h"
#include "Foundation/Interface/AApplicationPlugin.h"
//#include "Foundation/Interface/Array.h"
#include "Foundation/Interface/AAssert.h"
#include "Foundation/Interface/AColor.h"
#include "Foundation/Interface/ADelegate.h"
#include "Foundation/Interface/ADirectory.h"
#include "Foundation/Interface/AError.h"
#include "Foundation/Interface/AEvent.h"
#include "Foundation/Interface/AFactoryList.h"
#include "Foundation/Interface/AFactoryMap.h"
#include "Foundation/Interface/AFile.h"
#include "Foundation/Interface/AGreekAlphabet.h"
//#include "Foundation/Interface/Map.h"
//#include "Foundation/Interface/AHashSet.h"
#include "Foundation/Interface/AInitializerList.h"
#include "Foundation/Interface/AInteger.h"
//#include "Foundation/Interface/Array.h"
#include "Foundation/Interface/ALog.h"
//#include "Foundation/Interface/AMap.h"
#include "Foundation/Interface/AMemory.h"
#include "Foundation/Interface/AMemoryManager.h"
#include "Foundation/Interface/AMeta.h"
#include "Foundation/Interface/AMIMEType.h"
#include "Foundation/Interface/AObject.h"
#include "Foundation/Interface/AOperation.h"
#include "Foundation/Interface/APair.h"
#include "Foundation/Interface/APath.h"
#include "Foundation/Interface/APathInfo.h"
#include "Foundation/Interface/APixmap.h"
#include "Foundation/Interface/APlatform.h"
#include "Foundation/Interface/APlugin.h"
#include "Foundation/Interface/AProcess.h"
//#include "Foundation/Interface/AQueue.h"
#include "Foundation/Interface/ARunLoop.h"
//#include "Foundation/Interface/ASet.h"
#include "Foundation/Interface/ASharedData.h"
#include "Foundation/Interface/ASingleton.h"
//#include "Foundation/Interface/Stack.h"
#include "Foundation/Interface/AStaticInteger.h"
#include "Foundation/Interface/AThread.h"
#include "Foundation/Interface/ATime.h"
#include "Foundation/Interface/AType.h"
#include "Foundation/Interface/AUtf.h"
#include "Foundation/Interface/AVariant.h"
#include "Foundation/Interface/AVersion.h"
#include "Foundation/Interface/AVirtualCopyable.h"
#include "Foundation/Interface/Blending.h"
#include "Foundation/Interface/CommandManager.h"
#include "Foundation/Interface/DrawingAlgorithms.h"
#include "Foundation/Interface/Foundation.pch.hpp"
#include "Foundation/Interface/Serializable.h"
#include "Foundation/Interface/StaticArray.h"
#include "Foundation/Interface/Containers/Array.gen.h"
#include "Foundation/Interface/Containers/ArrayWithSharedData.gen.h"
#include "Foundation/Interface/Containers/OrderedDictionary.gen.h"
#include "Foundation/Interface/Containers/OrderedSet.gen.h"
#include "Foundation/Interface/Containers/Queue.gen.h"
#include "Foundation/Interface/Containers/Range.gen.h"
#include "Foundation/Interface/Containers/Stack.gen.h"
#include "Foundation/Interface/Containers/UnorderedDictionary.gen.h"
#include "Foundation/Interface/Containers/UnorderedSet.gen.h"
#include "Foundation/Interface/Memory/PlainReference.gen.h"
#include "Foundation/Interface/Memory/SharedReference.gen.h"
#include "Foundation/Interface/Memory/UniqueReference.gen.h"
#include "Foundation/Interface/Memory/WeakReference.gen.h"
#include "Foundation/Interface/Strings/Path.gen.h"
#include "Foundation/Interface/Strings/String.gen.h"
#include "Foundation/Interface/Strings/Text.gen.h"
#include "Graphics/Interface/GraphicsMath.h"
//#include "Graphics/Interface/InplaceStorage.gen.h"
#include "Graphics/Interface/TextureAsset.h"
#include "Graphics/Interface/Core/AApplication.h"
#include "Graphics/Interface/Core/AAssets.h"
#include "Graphics/Interface/Core/ACommonEvents.h"
#include "Graphics/Interface/Core/AComponent.h"
#include "Graphics/Interface/Core/AController.h"
#include "Graphics/Interface/Core/AEntity.h"
#include "Graphics/Interface/Core/AEntityEvents.h"
#include "Graphics/Interface/Core/AEventLoop.h"
#include "Graphics/Interface/Core/AFirstPersonInputController.h"
#include "Graphics/Interface/Core/AFlags.h"
#include "Graphics/Interface/Core/AFreeCameraInputController.h"
#include "Graphics/Interface/Core/AInputController.h"
#include "Graphics/Interface/Core/AKeyboardEvent.h"
#include "Graphics/Interface/Core/AMouseEvent.h"
#include "Graphics/Interface/Core/AOBJLoader.h"
#include "Graphics/Interface/Core/APlatformInegration.h"
#include "Graphics/Interface/Core/Application2.gen.h"
#include "Graphics/Interface/Core/ApplicationComponent2.gen.h"
#include "Graphics/Interface/Core/ASpace.h"
#include "Graphics/Interface/Core/ASpaceEvents.h"
#include "Graphics/Interface/Core/Assets.h"
#include "Graphics/Interface/Core/AStyle.h"
#include "Graphics/Interface/Core/AVisualComponent.h"
#include "Graphics/Interface/Core/AWindow.h"
#include "Graphics/Interface/Core/AWindowEvents.h"
#include "Graphics/Interface/Core/BundleSingleton.h"
#include "Graphics/Interface/Core/Clipboard.h"
#include "Graphics/Interface/Core/FrameClock.h"
#include "Graphics/Interface/Core/FunctionPointer.h"
#include "Graphics/Interface/Core/LaunchComponent.gen.h"
#include "Graphics/Interface/Core/StateMachine.h"
#include "Graphics/Interface/Core/TemplateWindow.h"
#include "Graphics/Interface/Core/Window2.gen.h"
#include "Graphics/Interface/Core/Components/AStaticMeshComponent.h"
#include "Graphics/Interface/Core/Controllers/AConsoleController.h"
#include "Graphics/Interface/Core/Controllers/AEntityPickerController.h"
#include "Graphics/Interface/Core/Controllers/Controller.h"
#include "Graphics/Interface/Core/Controllers/ControllerState.h"
#include "Graphics/Interface/Core/Controllers/WindowController.h"
#include "Graphics/Interface/Graphics/ACamera.h"
#include "Graphics/Interface/Graphics/AFace.h"
#include "Graphics/Interface/Graphics/AForwardRenderer.h"
#include "Graphics/Interface/Graphics/AGraphicsContext.h"
#include "Graphics/Interface/Graphics/AGraphicsEvents.h"
#include "Graphics/Interface/Graphics/AMaterial.h"
#include "Graphics/Interface/Graphics/AMesh.h"
#include "Graphics/Interface/Graphics/AParticleEmitter.h"
#include "Graphics/Interface/Graphics/APerspectiveCamera.h"
#include "Graphics/Interface/Graphics/ARenderer.h"
#include "Graphics/Interface/Graphics/AVertex.h"
#include "Graphics/Interface/Graphics/Canvas.h"
#include "Graphics/Interface/Graphics/Graphics.h"
#include "Graphics/Interface/Graphics/GraphicsComponent.gen.h"
#include "Graphics/Interface/Graphics/GraphicsContext.h"
#include "Graphics/Interface/Graphics/HardwareHandle.h"
#include "Graphics/Interface/Graphics/MeshGenerator.h"
#include "Graphics/Interface/Graphics/Texture.h"
#include "Graphics/Interface/Graphics/VisualDebug.h"
/*#include "Graphics/Interface/Graphics/GraphicsComponents/Camera2.gen.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/Composition.gen.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/DrawBatch.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/Material3.gen.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/Mesh3.gen.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/PipelineState.gen.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/RenderBuffer.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/Shader2.gen.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/SwapChain.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/Implementation/Implementation.h"
#include "Graphics/Interface/Graphics/GraphicsComponents/Implementation/ShaderHelper.h"*/
#include "Graphics/Interface/Graphics/OpenGL/OpenGLGraphicsContext.h"
#include "Graphics/Interface/Graphics/OpenGL/OpenGLImplementation.h"
#include "Graphics/Interface/Graphics/OpenGL/OpenGLParticleEmitterHandle.h"
#include "Graphics/Interface/Graphics/OpenGL/OpenGLPlatform.h"
#include "Graphics/Interface/Includes/Alignment.gen.h"
#include "Graphics/Interface/Includes/Camera.gen.h"
#include "Graphics/Interface/Includes/CameraComponent.gen.h"
#include "Graphics/Interface/Includes/Color.gen.h"
#include "Graphics/Interface/Includes/Component.gen.h"
#include "Graphics/Interface/Includes/DirectionalLightComponent.gen.h"
#include "Graphics/Interface/Includes/Entity.gen.h"
#include "Graphics/Interface/Includes/KeyModifier.gen.h"
#include "Graphics/Interface/Includes/LightComponent.gen.h"
#include "Graphics/Interface/Includes/Material2.gen.h"
#include "Graphics/Interface/Includes/Mesh2.gen.h"
#include "Graphics/Interface/Includes/Object.gen.h"
#include "Graphics/Interface/Includes/PBRMaterial2.gen.h"
#include "Graphics/Interface/Includes/PhysicsComponent.gen.h"
#include "Graphics/Interface/Includes/PointLightComponent.gen.h"
#include "Graphics/Interface/Includes/Shortcut.gen.h"
#include "Graphics/Interface/Includes/SoundComponent.gen.h"
#include "Graphics/Interface/Includes/StaticMeshComponent.gen.h"
#include "Graphics/Interface/Includes/Texture.gen.h"
#include "Graphics/Interface/Includes/TextureFiltration.gen.h"
#include "Graphics/Interface/Includes/TextureWrapping.gen.h"
#include "Graphics/Interface/Includes/TriggerComponent.gen.h"
#include "Graphics/Interface/Includes/VisualComponent.gen.h"
#include "Graphics/Interface/Includes/Window.gen.h"
#include "Graphics/Interface/Materials/DebugMaterial.g.h"
#include "Graphics/Interface/Materials/FoliageMaterial.g.h"
#include "Graphics/Interface/Materials/ModelMaterial.g.h"
#include "Graphics/Interface/Materials/PBRMaterial.g.h"
#include "Graphics/Interface/Materials/SpriteMaterial.g.h"
#include "Graphics/Interface/Materials/UIImageMaterial.g.h"
#include "Graphics/Interface/Materials/UILabelMaterial.g.h"
#include "ImageFormats/Interface/APixmapFormat.h"
#include "ImageFormats/Interface/APixmapLoader.h"
#include "ImageFormats/Interface/Formats/AJpegFormat.h"
#include "ImageFormats/Interface/Formats/APngFormat.h"
#include "Math/Classes/Math/IntegerRectangle.gen.h"
#include "Math/Classes/Math/IntegerVector.gen.h"
#include "Math/Classes/Math/Matrix.gen.h"
#include "Math/Classes/Math/Offsets.gen.h"
#include "Math/Classes/Math/Quaternion.gen.h"
#include "Math/Classes/Math/Rectangle.gen.h"
//#include "Math/Classes/Math/RotationOrder.gen.h"
#include "Math/Classes/Math/Transform.gen.h"
#include "Math/Classes/Math/Vector.gen.h"
#include "Math/Interface/Algorithm.h"
#include "Math/Interface/BasicConstants.h"
#include "Math/Interface/BoundingVolume.h"
#include "Math/Interface/Box.h"
#include "Math/Interface/Intersect.h"
#include "Math/Interface/Math.pch.hpp"
#include "Math/Interface/Matrix.h"
#include "Math/Interface/Offsets.h"
#include "Math/Interface/Quaternion.h"
#include "Math/Interface/Range.h"
#include "Math/Interface/Rectangle.h"
#include "Math/Interface/RotationOrder.h"
#include "Math/Interface/Transform.h"
#include "Math/Interface/TrigonometricTable.h"
#include "Math/Interface/Vector.h"
#include "Math/Interface/VectorConstants.h"
#include "Math/Interface/BasicTypes/Boolean.gen.h"
#include "Math/Interface/BasicTypes/ByteInteger.gen.h"
#include "Math/Interface/BasicTypes/Float.gen.h"
#include "Math/Interface/BasicTypes/Serializable.gen.h"
#include "Math/Interface/BasicTypes/SignedInteger.gen.h"
#include "Math/Interface/BasicTypes/SizeInteger.gen.h"
#include "Math/Interface/BasicTypes/UnsignedInteger.gen.h"
#include "Platform/Interface/Windows/AWindowsPlatform.h"
#include "Platform/Interface/Windows/AWindowsWindow.h"
#include "Reflection/Interface/MetaObject.h"
#include "System/Interface/Log.hpp"
#include "System/Interface/Process.hpp"
#include "System/Interface/StackTrace.hpp"
#include "System/Interface/Str.hpp"
#include "System/Interface/System.hpp"
#include "System/Interface/System.pch.hpp"
#include "UI/Interface/LayoutUtils.h"
#include "UI/Interface/UI.pch.hpp"
#include "UI/Interface/UIMath.h"
#include "UI/Interface/WindowFlowState.h"
#include "UI/Interface/Includes/BorderImageView.gen.h"
#include "UI/Interface/Includes/Button.gen.h"
#include "UI/Interface/Includes/CanvasView.gen.h"
#include "UI/Interface/Includes/ColorPicker.gen.h"
#include "UI/Interface/Includes/Connection.gen.h"
#include "UI/Interface/Includes/ContentFit.gen.h"
#include "UI/Interface/Includes/DefaultExpandableItemView.gen.h"
#include "UI/Interface/Includes/DefaultIconItemView.gen.h"
#include "UI/Interface/Includes/DefaultTabItemView.gen.h"
#include "UI/Interface/Includes/DefaultTextItemView.gen.h"
#include "UI/Interface/Includes/Direction.gen.h"
#include "UI/Interface/Includes/DockView.gen.h"
#include "UI/Interface/Includes/DockViewArea.gen.h"
#include "UI/Interface/Includes/DockViewTab.gen.h"
#include "UI/Interface/Includes/DropDown.gen.h"
#include "UI/Interface/Includes/DropDownList.gen.h"
#include "UI/Interface/Includes/FlexBox.gen.h"
#include "UI/Interface/Includes/FlexBoxData.gen.h"
#include "UI/Interface/Includes/GraphAdapter.gen.h"
#include "UI/Interface/Includes/GraphProxy.gen.h"
#include "UI/Interface/Includes/GraphView.gen.h"
#include "UI/Interface/Includes/GridView.gen.h"
#include "UI/Interface/Includes/GroupHeader.gen.h"
#include "UI/Interface/Includes/GroupPanel.gen.h"
#include "UI/Interface/Includes/GroupView.gen.h"
#include "UI/Interface/Includes/ImageView.gen.h"
#include "UI/Interface/Includes/InvertedPanel.gen.h"
#include "UI/Interface/Includes/ItemView.gen.h"
#include "UI/Interface/Includes/KeyBindingView.gen.h"
#include "UI/Interface/Includes/Label.gen.h"
#include "UI/Interface/Includes/ListView.gen.h"
#include "UI/Interface/Includes/NamedNodeView.gen.h"
#include "UI/Interface/Includes/NodeView.gen.h"
#include "UI/Interface/Includes/Overlay.gen.h"
#include "UI/Interface/Includes/OverlayData.gen.h"
#include "UI/Interface/Includes/PageView.gen.h"
#include "UI/Interface/Includes/Panel.gen.h"
#include "UI/Interface/Includes/PathDialog.gen.h"
#include "UI/Interface/Includes/PathField.gen.h"
#include "UI/Interface/Includes/Pin.gen.h"
#include "UI/Interface/Includes/PinNodeView.gen.h"
#include "UI/Interface/Includes/PinNodeViewWithPreview.gen.h"
#include "UI/Interface/Includes/PinType.gen.h"
#include "UI/Interface/Includes/PopupView.gen.h"
#include "UI/Interface/Includes/ProgressBar.gen.h"
#include "UI/Interface/Includes/RelativeLayout.gen.h"
#include "UI/Interface/Includes/ScrollBarVisibility.gen.h"
#include "UI/Interface/Includes/ScrollView.gen.h"
#include "UI/Interface/Includes/SizePolicy.gen.h"
#include "UI/Interface/Includes/Slider.gen.h"
#include "UI/Interface/Includes/SplitView.gen.h"
#include "UI/Interface/Includes/SplitViewLayoutData.gen.h"
#include "UI/Interface/Includes/Switch.gen.h"
#include "UI/Interface/Includes/TabItem.gen.h"
#include "UI/Interface/Includes/TableView.gen.h"
#include "UI/Interface/Includes/TabView.gen.h"
#include "UI/Interface/Includes/TextButton.gen.h"
#include "UI/Interface/Includes/TextField.gen.h"
#include "UI/Interface/Includes/ToolTipView.gen.h"
#include "UI/Interface/Includes/TreeView.gen.h"
#include "UI/Interface/Includes/View.gen.h"
#include "UI/Interface/Includes/ViewComponent.gen.h"
#include "UI/Interface/Includes/ViewWindow.gen.h"
#include "UI/Interface/Includes/Visibility.gen.h"
#include "UI/Interface/UI/UIApplication.h"
#include "UI/Interface/UI/UIComponent.h"
#include "UI/Interface/UI/UIDialogLayout.g.h"
#include "UI/Interface/UI/UILayout.h"
#include "UI/Interface/UI/UIPerspectiveCamera.h"
#include "UI/Interface/UI/UISuggsetionsAdapter.h"
#include "UI/Interface/UI/GestureRecognizers/UIDragAndDropGestureRecognizer.h"
#include "UI/Interface/UI/GestureRecognizers/UIDraggingGestureRecognizer.h"
#include "UI/Interface/UI/GestureRecognizers/UIGestureRecognizer.h"
#include "UI/Interface/UI/GestureRecognizers/UIItemReorderingGestureRecognizer.h"
#include "UI/Interface/UI/GestureRecognizers/UILinkingGestureRecognizer.h"
#include "UI/Interface/UI/GestureRecognizers/UIMoveGestureRecognizer.h"
#include "UI/Interface/UI/GestureRecognizers/UINewGestureRecognizers.h"
#include "UI/Interface/UI/GestureRecognizers/UIResizeGestureRecognizer.h"
#include "UI/Interface/UI/GestureRecognizers/UITouchGestureRecognizer.h"
#include "UI/Interface/UI/Views/UIDataView.h"
#include "UI/Interface/UI/Views/UIDialog.h"
#include "UI/Interface/UI/Views/UIGroupAdapter.h"
#include "UI/Interface/UI/Views/UIGroupProxy.h"
#include "UI/Interface/UI/Views/UILabelListController.h"
#include "UI/Interface/UI/Views/UILine.h"
#include "UI/Interface/UI/Views/UIMenu.h"
#include "UI/Interface/UI/Views/UIPathComponent.h"
#include "UI/Source/UI/UIBundle.h"
#include "UI/Source/UI/Assets/fonts-build.h"
#include "UI/Source/UI/Assets/ui-build.h"
#include "UI2/Interface/Includes/LegacyApplication.gen.h"
#include "UI2/Interface/Includes/Raycast.h"
#include "UI2/Interface/Includes/UIComponent.gen.h"
//#include "UI2/Interface/Includes/UIComposition.gen.h"
#include "UIDarkTheme/Interface/UIDarkThemeTextures.h"
