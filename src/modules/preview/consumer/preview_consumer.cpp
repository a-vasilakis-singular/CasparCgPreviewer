/*
 * Copyright (c) 2026
 *
 * CasparCG Preview Consumer
 */

#include "preview_consumer.h"

#include "../publisher/frame_publisher.h"

#include <common/future.h>
#include <common/log.h>

#include <core/consumer/channel_info.h>
#include <core/consumer/frame_consumer.h>
#include <core/frame/frame.h>
#include <core/video_format.h>

#include <boost/algorithm/string.hpp>

namespace caspar::preview
{

struct preview_consumer_proxy final : public core::frame_consumer
{
private:
    core::video_format_desc format_desc_;

    int channel_index_ = -1;

    frame_publisher publisher_;

public:
    preview_consumer_proxy() = default;

    //
    // frame_consumer
    //

    void initialize(const core::video_format_desc& format_desc,
                    const core::channel_info& channel_info,
                    int /*port_index*/) override
    {
        format_desc_  = format_desc;
        channel_index_ = channel_info.index;

        CASPAR_LOG(info)
            << L"[Preview] Initialized on channel "
            << channel_index_
            << L" ("
            << format_desc_.name
            << L")";
    }

    std::future<bool> send(core::video_field /*field*/,
                           core::const_frame frame) override
    {
        publisher_.publish(frame);
        auto count = publisher_.frame_count();

        if ((count % 250) == 0)
        {
            CASPAR_LOG(trace)
                << L"[Preview] Received "
                << count
                << L" frames on channel "
                << channel_index_;
        }

        return make_ready_future(true);
    }

    std::wstring print() const override
    {
        return L"Preview Consumer";
    }

    std::wstring name() const override
    {
        return L"preview";
    }

    bool has_synchronization_clock() const override
    {
        return false;
    }

    int index() const override
    {
        return 900;
    }

    core::monitor::state state() const override
    {
        core::monitor::state state;

        state["preview/channel"] = channel_index_;
        state["preview/frames"]  = publisher_.frame_count();

        return state;
    }
};

spl::shared_ptr<core::frame_consumer>
create_consumer(
    const std::vector<std::wstring>& params,
    const core::video_format_repository&,
    const std::vector<spl::shared_ptr<core::video_channel>>&,
    const core::channel_info&)
{
    if (params.empty() || !boost::iequals(params.at(0), L"PREVIEW"))
        return core::frame_consumer::empty();

    CASPAR_LOG(info) << L"Creating Preview consumer.";

    return spl::make_shared<preview_consumer_proxy>();
}

spl::shared_ptr<core::frame_consumer>
create_preconfigured_consumer(
    const boost::property_tree::wptree&,
    const core::video_format_repository&,
    const std::vector<spl::shared_ptr<core::video_channel>>&,
    const core::channel_info&)
{
    CASPAR_LOG(info) << L"Creating preconfigured Preview consumer.";

    return spl::make_shared<preview_consumer_proxy>();
}

} // namespace caspar::preview
