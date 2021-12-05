#pragma once

extern void RegisterStaticAsset_background_black();
extern void RegisterStaticAsset_background();
extern void RegisterStaticAsset_button();
extern void RegisterStaticAsset_buttonOld();
extern void RegisterStaticAsset_controlpoint();
extern void RegisterStaticAsset_debug();
extern void RegisterStaticAsset_debug2();
extern void RegisterStaticAsset_dialog_outline();
extern void RegisterStaticAsset_dialog();
extern void RegisterStaticAsset_field();
extern void RegisterStaticAsset_header();
extern void RegisterStaticAsset_line();
extern void RegisterStaticAsset_list_highlighting();
extern void RegisterStaticAsset_list();
extern void RegisterStaticAsset_placeholder();
extern void RegisterStaticAsset_progress();
extern void RegisterStaticAsset_slider();

inline void LoadBundle_ui_build()
{
    RegisterStaticAsset_background_black();
    RegisterStaticAsset_background();
    RegisterStaticAsset_button();
    RegisterStaticAsset_buttonOld();
    RegisterStaticAsset_controlpoint();
    RegisterStaticAsset_debug();
    RegisterStaticAsset_debug2();
    RegisterStaticAsset_dialog_outline();
    RegisterStaticAsset_dialog();
    RegisterStaticAsset_field();
    RegisterStaticAsset_header();
    RegisterStaticAsset_line();
    RegisterStaticAsset_list_highlighting();
    RegisterStaticAsset_list();
    RegisterStaticAsset_placeholder();
    RegisterStaticAsset_progress();
    RegisterStaticAsset_slider();
}
