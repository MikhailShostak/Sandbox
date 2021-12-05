#pragma once

extern void RegisterStaticAsset_consola();
extern void RegisterStaticAsset_NotoSans_Bold();
extern void RegisterStaticAsset_NotoSans_BoldItalic();
extern void RegisterStaticAsset_NotoSans_Italic();
extern void RegisterStaticAsset_NotoSans_Regular();
extern void RegisterStaticAsset_NotoSansUI_Bold();
extern void RegisterStaticAsset_NotoSansUI_BoldItalic();
extern void RegisterStaticAsset_NotoSansUI_Italic();
extern void RegisterStaticAsset_NotoSansUI_Regular();

inline void LoadBundle_fonts_build()
{
    RegisterStaticAsset_consola();
    RegisterStaticAsset_NotoSans_Bold();
    RegisterStaticAsset_NotoSans_BoldItalic();
    RegisterStaticAsset_NotoSans_Italic();
    RegisterStaticAsset_NotoSans_Regular();
    RegisterStaticAsset_NotoSansUI_Bold();
    RegisterStaticAsset_NotoSansUI_BoldItalic();
    RegisterStaticAsset_NotoSansUI_Italic();
    RegisterStaticAsset_NotoSansUI_Regular();
}
