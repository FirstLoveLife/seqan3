// ============================================================================
//                 SeqAn - The Library for Sequence Analysis
// ============================================================================
//
// Copyright (c) 2006-2018, Knut Reinert & Freie Universitaet Berlin
// Copyright (c) 2016-2018, Knut Reinert & MPI Molekulare Genetik
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ============================================================================

/*!\file
 * \brief Provides seqan3::detail::execution_handler_sequential.
 * \author Rene Rahn <rene.rahn AT fu-berlin.de>
 */

#pragma once

#include <functional>

#include <seqan3/core/platform.hpp>

namespace seqan3::detail
{

/*!\brief Handles the sequential execution of alignments.
 * \ingroup execution
 */
class execution_handler_sequential
{
public:
    /*!\name Constructors, destructor and assignment
     * \{
     */
    execution_handler_sequential()                                                 = default;
    execution_handler_sequential(execution_handler_sequential const &)             = default;
    execution_handler_sequential(execution_handler_sequential &&)                  = default;
    execution_handler_sequential & operator=(execution_handler_sequential const &) = default;
    execution_handler_sequential & operator=(execution_handler_sequential &&)      = default;
    ~execution_handler_sequential()                                                = default;
    //!}

    /*!\name Execution
     * \{
     */
    //!\brief Invokes the passed alignment instance in a blocking manner.
    template <typename func_result_t>
    void execute(std::function<func_result_t(func_result_t &)> func,
                 func_result_t & res,
                 std::function<void(decltype(func(res)))> delegate)
    {
        delegate(func(res));
    }
    //!\}
};

} // namespace seqan3
