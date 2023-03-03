cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "C:/VST_make/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(MeowMu
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "MeowMu VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(MeowMu
    source/version.h
    source/MeowMucids.h
    source/MeowMuprocessor.h
    source/MeowMuprocessor.cpp
    source/MeowMucontroller.h
    source/MeowMucontroller.cpp
    source/MeowMuentry.cpp
    ${vst3sdk_SOURCE_DIR}/public.sdk/source/vst/vst2wrapper/vst2wrapper.sdk.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
    target_sources(MeowMu
        PRIVATE
            resource/MeowMueditor.uidesc
    )
    target_link_libraries(MeowMu
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(MeowMu
        RESOURCES
            "resource/MeowMueditor.uidesc"
    )
endif(SMTG_ADD_VSTGUI)
# -------------------

smtg_target_add_plugin_snapshots (MeowMu
    RESOURCES
        resource/B09AE2D476BD551181B88EC4658C521C_snapshot.png
        resource/B09AE2D476BD551181B88EC4658C521C_snapshot_2.0x.png
)

target_link_libraries(MeowMu
    PRIVATE
        sdk
)

smtg_target_configure_version_file(MeowMu)

if(SMTG_WIN)
    target_sources(MeowMu PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MeowMu)
    endif()
endif(SMTG_WIN)

if(SMTG_WIN)
    if(NOT MINGW)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    endif(NOT MINGW)
endif(SMTG_WIN)