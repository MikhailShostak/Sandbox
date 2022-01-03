namespace Graphics
{

MaterialRenderingSettings::MaterialRenderingSettings() :
    StencilReadMask(0xFF),
    StencilWriteMask(0xFF),
    StencilEnabled(false),
    DepthTestEnabled(true),
    DepthWriteEnabled(true),
    Wireframe(false),
    Cullback(true)
{

}

}
