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

/*!\cond DEV
 * \file
 * \author Hannes Hauswedell <hannes.hauswedell AT fu-berlin.de>
 * \brief Provides seqan3::detail::convert_through_char_representation.
 * \endcond
 */

#pragma once

#include <algorithm>
#include <array>

#include <seqan3/alphabet/concept.hpp>
#include <seqan3/alphabet/quality/concept.hpp>

// ============================================================================
// conversion to/from char/rank types
// ============================================================================

namespace seqan3::detail
{

/*!\brief A precomputed conversion table for two alphabets based on their char representations.
 * \ingroup alphabet
 * \tparam out_t The type of the output, must satisfy seqan3::alphabet_concept.
 * \tparam in_t The type of the input, must satisfy seqan3::alphabet_concept.
 * \hideinitializer
 */
template <alphabet_concept out_t, alphabet_concept in_t>
constexpr std::array<out_t, alphabet_size_v<in_t>> convert_through_char_representation
{
    [] () constexpr
    {
        std::array<out_t, alphabet_size_v<in_t>> ret{};
        for (typename in_t::rank_type i = 0; i < alphabet_size_v<in_t>; ++i)
            assign_char(ret[i], to_char(assign_rank(in_t{}, i)));
        return ret;
    }()
};

/*!\brief A precomputed conversion table for two alphabets based on their phred representations.
 * \ingroup alphabet
 * \tparam out_t The type of the output, must satisfy seqan3::quality_concept.
 * \tparam in_t The type of the input, must satisfy seqan3::quality_concept.
 * \hideinitializer
 */
template <quality_concept out_t, quality_concept in_t>
constexpr std::array<out_t, alphabet_size_v<in_t>> convert_through_phred_representation
{
    [] () constexpr
    {
        std::array<out_t, alphabet_size_v<in_t>> ret{};
        typename in_t::rank_type table_size = std::min<typename in_t::rank_type>(in_t::value_size, out_t::value_size);
        for (typename in_t::rank_type i = 0; i < table_size; ++i)
            assign_phred(ret[i], std::max<typename in_t::phred_type>(0, to_phred(assign_rank(in_t{}, i))));
        return ret;
    }()
};

} // namespace seqan3::detail
