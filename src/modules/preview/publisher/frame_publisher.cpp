/*
 * Copyright (c) 2026
 *
 * CasparCG Preview Consumer
 */

#include "frame_publisher.h"

namespace caspar::preview
{

void frame_publisher::publish(core::const_frame /*frame*/)
{
    // The transport is intentionally deferred. A following change will
    // publish the frame through shared memory.
    ++frame_count_;
}

std::uint64_t frame_publisher::frame_count() const noexcept
{
    return frame_count_.load();
}

} // namespace caspar::preview
