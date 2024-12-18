#pragma once

/// @file userver/formats/serialize/to.hpp
/// @brief Helper for serializers.
/// @ingroup userver_universal userver_formats_serialize

namespace formats::serialize {

/// @ingroup userver_universal userver_formats_serialize
///
/// An ADL helper that allows searching for `Serialize` functions in namespace
/// `formats::serialize` additionally to the namespace of `T`.
template <class T>
struct To {};

}  // namespace formats::serialize
