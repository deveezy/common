#pragma once

namespace formats::parse {

/// @ingroup userver_universal userver_formats_parse
///
/// An ADL helper that allows searching for `Parse` functions in namespace
/// `formats::parse` additionally to the namespace of `T`.
///
/// @see @ref scripts/docs/en/userver/formats.md
template <class T>
struct To {};

}  // namespace formats::parse
