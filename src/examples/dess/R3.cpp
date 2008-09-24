/**
 * @file src/examples/dess/R3.cpp
 * @author The VLE Development Team
 */

/*
 * VLE Environment - the multimodeling and simulation environment
 * This file is a part of the VLE environment (http://vle.univ-littoral.fr)
 * Copyright (C) 2003 - 2008 The VLE Development Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "R3.hpp"
#include <vle/utils/Debug.hpp>
#include <cmath>

namespace vle { namespace examples { namespace dess {

R3::R3(const graph::AtomicModel& model,
       const devs::InitEventList& events):
    extension::qss(model, events)
{
    a = value::toDouble(events.get("a"));
}

double R3::compute(const vle::devs::Time& /* time */) const
{    
    return a * getValue("I");
} 

DECLARE_NAMED_DYNAMICS(R3, R3)

}}} // namespace vle examples dess