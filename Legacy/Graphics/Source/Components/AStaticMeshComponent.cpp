#include "AStaticMeshComponent.h"
#include "AEntity.h"
#include "GraphicsContext.h"

void AStaticMeshComponent::onLoad(ALoadEvent &event)
{
    AVisualComponent::onLoad(event);
    material->load();
    if (material->ColorMap && !material->ColorMap->isLoaded())
    {
        material->ColorMap->load();
        if (material->ColorMap->getFormat() == APixmapDataFormat::RGBA || material->ColorMap->getFormat() == APixmapDataFormat::GrayAlpha)
        {
            material->setOpaque(false);
        }
    }
    if (material->NormalMap && !material->ColorMap->isLoaded())
    {
        material->NormalMap->load();
    }
    mesh->load();
}

void AStaticMeshComponent::onUnload(AUnloadEvent &event)
{
    AVisualComponent::onUnload(event);
}

void AStaticMeshComponent::onDraw(AUpdateEvent &event)
{
    if(!mesh)
    {
        return;
    }

    material->ModelViewProjectionMatrix = getOwner().getTransform().getMatrix() * ACamera::getCurrentCamera()->getMatrix();
    Legacy::Graphics::GraphicsContext::getCurrent().draw(mesh, material);
    update();
}

/*#include "AOBJLoader.h"

AList<::SharedReference<AMesh>> meshes;

void load(::SharedReference<AMesh> &mesh)
{*/
    /*if(!mesh)
    {
        Map<String, ::SharedReference<AMesh>> map = import(AAsset("Meshes/bone.obj"));
        for(auto &pair : map)
        {
            meshes.append(pair.second);
        }
        mesh = meshes.first();
    }*/
/*}

struct ABone
{
    Math::Quaternion rotation;
    Math::Vector position;
};

using BoneIterator = Array<ABone>::Iterator;

struct AJoint
{
    String name;

    ABone *parent = nullptr;
    ABone *bone = nullptr;
    AList<ABone *> bones;

};

void AStaticMeshComponent::onCreate(ACreateEvent *event)
{
    auto context = event->getGraphicsContext();
    load(mesh);

    context->load(material.weak());
    context->load(mesh.weak());
}

void AStaticMeshComponent::onUpdate(AUpdateEvent *event)
{
    auto context = event->getGraphicsContext();
*/
    /*AList<AJoint> joints;
    AList<ABone> bones;

    ABone *parent = nullptr;
    AJoint joint;

    bones.append(ABone({Math::Quaternion::rotationXYZ(0, 0, 0), Math::Vector(0, 1, 0)}));
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append(ABone({Math::Quaternion::rotationXYZ(0, 0, 0), Math::Vector(0, 2, 0)}));
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append(ABone({Math::Quaternion::rotationXYZ(0, 0, 0), Math::Vector(0, 3, 0)}));
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    ABone *neck = joint.bone;

    bones.append(ABone({Math::Quaternion::rotationXYZ(0, 0, 0), Math::Vector(0, 3.5, 0)}));
    joint = AJoint();
    joint.parent = neck;
    joint.bone = &bones.last();
    joints.append(joint);

    bones.append(ABone({Math::Quaternion::rotationXYZ(0, 0, 90), Math::Vector(-1, 3, 0)}));
    joint = AJoint();
    joint.parent = neck;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append(ABone({Math::Quaternion::rotationXYZ(180, 0, 0), Math::Vector(-1, 2, 0)}));
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append(ABone({Math::Quaternion::rotationXYZ(180, 0, 0), Math::Vector(-1, 1, 0)}));
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    bones.append(ABone({Math::Quaternion::rotationXYZ(0, 0, -90), Math::Vector(1, 3, 0)}));
    joint = AJoint();
    joint.parent = neck;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append(ABone({Math::Quaternion::rotationXYZ(180, 0, 0), Math::Vector(1, 2, 0)}));
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append(ABone({Math::Quaternion::rotationXYZ(180, 0, 0), Math::Vector(1, 1, 0)}));
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = nullptr;

    bones.append({Math::Quaternion::rotationXYZ(0, 0, 90), Math::Vector(0.5, 0, 0)});
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append({Math::Quaternion::rotationXYZ(180, 0, 0), Math::Vector(0.5, -2, 0)});
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append({Math::Quaternion::rotationXYZ(180, 0, 0), Math::Vector(0.5, -4, 0)});
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append({Math::Quaternion::rotationXYZ(90, 0, 0), Math::Vector(0.5, -4, -1)});
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = nullptr;

    bones.append({Math::Quaternion::rotationXYZ(0, 0, -90), Math::Vector(-0.5, 0, 0)});
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append({Math::Quaternion::rotationXYZ(180, 0, 0), Math::Vector(-0.5, -2, 0)});
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append({Math::Quaternion::rotationXYZ(180, 0, 0), Math::Vector(-0.5, -4, 0)});
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    parent = joint.bone;

    bones.append({Math::Quaternion::rotationXYZ(90, 0, 0), Math::Vector(-0.5, -4, -1)});
    joint = AJoint();
    joint.parent = parent;
    joint.bone = &bones.last();
    joints.append(joint);

    auto getMatrix = [](const Math::Transform &t){
        Math::Matrix matrix;
        matrix.translate(t.position);
        matrix.translate(t.rotationPivot);
        matrix = matrix * t.rotation.toMatrix();
        matrix.translate(-t.rotationPivot);
        matrix.translate(t.scalePivot);
        matrix.scale(t.scale);
        matrix.translate(-t.scalePivot);
        return matrix;
    };

    for(auto &joint : joints)
    {
        Math::Transform transform = Math::Transform();
        Math::Vector delta = joint.bone->position;
        if(joint.parent)
        {
            transform.position = joint.parent->position;
            delta -= transform.position;
        }
        transform.scale = Math::Vector(sqrt(pow(delta.x, 2) + pow(delta.y, 2) + pow(delta.z, 2)));
        transform.rotation = joint.bone->rotation;
        context->getRenderer()->addMesh(getMatrix(transform), mesh, material);
    }*/

/*    Math::Vector p(0, 0, -1);

    auto m = context->getCamera()->getViewMatrix();
    auto i = m;
    i.inverse();
    i.transpose();

    p.x = i[0][0] * p.x + i[1][0] * p.y + i[2][0] * p.z + i[3][0];
    p.y = i[0][1] * p.x + i[1][1] * p.y + i[2][1] * p.z + i[3][1];
    p.z = i[0][2] * p.x + i[1][2] * p.y + i[2][2] * p.z + i[3][2];

    std::cout << p.x << " " << p.y << " " << p.z << "\n" << std::flush;

    context->getRenderer()->addMesh(getOwner()->transform.getMatrix(), mesh, material);
}
*/
