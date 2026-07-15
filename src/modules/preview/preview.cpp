#include "preview.h"

#include "consumer/preview_consumer.h"

#include <core/consumer/frame_consumer.h>

namespace caspar::preview
{

void init(const core::module_dependencies& dependencies)
{
    dependencies.consumer_registry
        ->register_consumer_factory(
            L"Preview Consumer",
            create_consumer);

    dependencies.consumer_registry
        ->register_preconfigured_consumer_factory(
            L"preview",
            create_preconfigured_consumer);
}

}