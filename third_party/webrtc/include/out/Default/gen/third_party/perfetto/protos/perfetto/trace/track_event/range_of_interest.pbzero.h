// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_RANGE_OF_INTEREST_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_RANGE_OF_INTEREST_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/field_writer.h"
#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"


namespace perfetto {
namespace protos {
namespace pbzero {

class TrackEventRangeOfInterest_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/1, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  TrackEventRangeOfInterest_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit TrackEventRangeOfInterest_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit TrackEventRangeOfInterest_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_start_us() const { return at<1>().valid(); }
  int64_t start_us() const { return at<1>().as_int64(); }
};

class TrackEventRangeOfInterest : public ::protozero::Message {
 public:
  using Decoder = TrackEventRangeOfInterest_Decoder;
  enum : int32_t {
    kStartUsFieldNumber = 1,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.TrackEventRangeOfInterest"; }


  using FieldMetadata_StartUs =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kInt64,
      int64_t,
      TrackEventRangeOfInterest>;

  static constexpr FieldMetadata_StartUs kStartUs{};
  void set_start_us(int64_t value) {
    static constexpr uint32_t field_id = FieldMetadata_StartUs::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kInt64>
        ::Append(*this, field_id, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
