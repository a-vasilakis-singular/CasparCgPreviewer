/*
 * Copyright (c) 2026
 *
 * CasparCG Preview Consumer
 */

#pragma once

#include <core/frame/frame.h>

#include <atomic>
#include <cstdint>

namespace caspar::preview
{

/// Receives frames from the CasparCG consumer.
///
/// The publisher deliberately does not expose a transport yet. A future
/// shared-memory transport will consume frames from this boundary without
/// changing the consumer integration.
class frame_publisher final
{
public:
    void publish(core::const_frame frame);

    std::uint64_t frame_count() const noexcept;

private:
    std::atomic_uint64_t frame_count_{0};
};

} // namespace caspar::preview
