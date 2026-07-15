cmake_minimum_required(VERSION 3.28)

project(preview)

set(SOURCES
    consumer/preview_consumer.cpp
    consumer/preview_consumer.h

    preview.cpp
    preview.h
)

casparcg_add_module_project(preview
    SOURCES ${SOURCES}
    INIT_FUNCTION "preview::init"
)

set_target_properties(preview PROPERTIES
    FOLDER modules
)

source_group(sources\\consumer consumer/*)
source_group(sources ./*)