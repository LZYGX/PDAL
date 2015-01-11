/******************************************************************************
* Copyright (c) 2014, Hobu Inc. (hobu@hobu.co)
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/

#pragma once

#include <pdal/Filter.hpp>
#include <pdal/PointBufferIter.hpp>

namespace pdal
{

class PDAL_DLL SortFilter : public Filter
{
public:
    SET_STAGE_NAME("filters.sort", "Sort data based on a given dimension.")
    SET_STAGE_LINK("http://www.pdal.io/stages/filters.sort.html")

    SortFilter()
    {}

private:
    // Dimension on which to sort.
    Dimension::Id::Enum m_dim;
    // Dimension name.
    std::string m_dimName;

    virtual void processOptions(const Options& options)
        { m_dimName = options.getValueOrThrow<std::string>("dimension"); }

    virtual void ready(PointContext ctx)
        { m_dim = ctx.findDim(m_dimName); }

    virtual void filter(PointBuffer& buf)
    {
        if (m_dim == Dimension::Id::Unknown)
            return;

        auto cmp = [this](const PointRef& p1, const PointRef& p2)
            { return p1.compare(m_dim, p2); };

        std::sort(buf.begin(), buf.end(), cmp);
    }

    SortFilter& operator=(const SortFilter&); // not implemented
    SortFilter(const SortFilter&); // not implemented
};

} // namespace pdal
