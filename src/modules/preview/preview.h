/*
 * Copyright (c) 2026
 *
 * CasparCgPreviewer
 */

#pragma once

#include <core/module_dependencies.h>

namespace caspar::preview
{

/// Registers the Preview module with CasparCG.
///
/// Called automatically by CasparCG during module initialization.
void init(const core::module_dependencies& dependencies);

} // namespace caspar::preview