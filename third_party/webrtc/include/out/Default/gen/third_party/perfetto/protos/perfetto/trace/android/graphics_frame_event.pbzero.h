// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_ANDROID_GRAPHICS_FRAME_EVENT_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_ANDROID_GRAPHICS_FRAME_EVENT_PROTO_H_

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
class GraphicsFrameEvent_BufferEvent;
namespace perfetto_pbzero_enum_GraphicsFrameEvent {
enum BufferEventType : int32_t;
}  // namespace perfetto_pbzero_enum_GraphicsFrameEvent
using GraphicsFrameEvent_BufferEventType = perfetto_pbzero_enum_GraphicsFrameEvent::BufferEventType;
} // Namespace pbzero.
} // Namespace protos.
} // Namespace perfetto.

namespace perfetto {
namespace protos {
namespace pbzero {

namespace perfetto_pbzero_enum_GraphicsFrameEvent {
enum BufferEventType : int32_t {
  UNSPECIFIED = 0,
  DEQUEUE = 1,
  QUEUE = 2,
  POST = 3,
  ACQUIRE_FENCE = 4,
  LATCH = 5,
  HWC_COMPOSITION_QUEUED = 6,
  FALLBACK_COMPOSITION = 7,
  PRESENT_FENCE = 8,
  RELEASE_FENCE = 9,
  MODIFY = 10,
  DETACH = 11,
  ATTACH = 12,
  CANCEL = 13,
};
} // namespace perfetto_pbzero_enum_GraphicsFrameEvent
using GraphicsFrameEvent_BufferEventType = perfetto_pbzero_enum_GraphicsFrameEvent::BufferEventType;


constexpr GraphicsFrameEvent_BufferEventType GraphicsFrameEvent_BufferEventType_MIN = GraphicsFrameEvent_BufferEventType::UNSPECIFIED;
constexpr GraphicsFrameEvent_BufferEventType GraphicsFrameEvent_BufferEventType_MAX = GraphicsFrameEvent_BufferEventType::CANCEL;


PERFETTO_PROTOZERO_CONSTEXPR14_OR_INLINE
const char* GraphicsFrameEvent_BufferEventType_Name(::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType value) {
  switch (value) {
  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::UNSPECIFIED:
    return "UNSPECIFIED";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::DEQUEUE:
    return "DEQUEUE";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::QUEUE:
    return "QUEUE";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::POST:
    return "POST";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::ACQUIRE_FENCE:
    return "ACQUIRE_FENCE";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::LATCH:
    return "LATCH";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::HWC_COMPOSITION_QUEUED:
    return "HWC_COMPOSITION_QUEUED";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::FALLBACK_COMPOSITION:
    return "FALLBACK_COMPOSITION";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::PRESENT_FENCE:
    return "PRESENT_FENCE";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::RELEASE_FENCE:
    return "RELEASE_FENCE";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::MODIFY:
    return "MODIFY";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::DETACH:
    return "DETACH";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::ATTACH:
    return "ATTACH";

  case ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType::CANCEL:
    return "CANCEL";
  }
  return "PBZERO_UNKNOWN_ENUM_VALUE";
}

class GraphicsFrameEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/1, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  GraphicsFrameEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GraphicsFrameEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GraphicsFrameEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_buffer_event() const { return at<1>().valid(); }
  ::protozero::ConstBytes buffer_event() const { return at<1>().as_bytes(); }
};

class GraphicsFrameEvent : public ::protozero::Message {
 public:
  using Decoder = GraphicsFrameEvent_Decoder;
  enum : int32_t {
    kBufferEventFieldNumber = 1,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.GraphicsFrameEvent"; }

  using BufferEvent = ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEvent;

  using BufferEventType = ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType;
  static inline const char* BufferEventType_Name(BufferEventType value) {
    return ::perfetto::protos::pbzero::GraphicsFrameEvent_BufferEventType_Name(value);
  }
  static inline const BufferEventType UNSPECIFIED = BufferEventType::UNSPECIFIED;
  static inline const BufferEventType DEQUEUE = BufferEventType::DEQUEUE;
  static inline const BufferEventType QUEUE = BufferEventType::QUEUE;
  static inline const BufferEventType POST = BufferEventType::POST;
  static inline const BufferEventType ACQUIRE_FENCE = BufferEventType::ACQUIRE_FENCE;
  static inline const BufferEventType LATCH = BufferEventType::LATCH;
  static inline const BufferEventType HWC_COMPOSITION_QUEUED = BufferEventType::HWC_COMPOSITION_QUEUED;
  static inline const BufferEventType FALLBACK_COMPOSITION = BufferEventType::FALLBACK_COMPOSITION;
  static inline const BufferEventType PRESENT_FENCE = BufferEventType::PRESENT_FENCE;
  static inline const BufferEventType RELEASE_FENCE = BufferEventType::RELEASE_FENCE;
  static inline const BufferEventType MODIFY = BufferEventType::MODIFY;
  static inline const BufferEventType DETACH = BufferEventType::DETACH;
  static inline const BufferEventType ATTACH = BufferEventType::ATTACH;
  static inline const BufferEventType CANCEL = BufferEventType::CANCEL;

  using FieldMetadata_BufferEvent =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kMessage,
      GraphicsFrameEvent_BufferEvent,
      GraphicsFrameEvent>;

  static constexpr FieldMetadata_BufferEvent kBufferEvent{};
  template <typename T = GraphicsFrameEvent_BufferEvent> T* set_buffer_event() {
    return BeginNestedMessage<T>(1);
  }

};

class GraphicsFrameEvent_BufferEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  GraphicsFrameEvent_BufferEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GraphicsFrameEvent_BufferEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GraphicsFrameEvent_BufferEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_frame_number() const { return at<1>().valid(); }
  uint32_t frame_number() const { return at<1>().as_uint32(); }
  bool has_type() const { return at<2>().valid(); }
  int32_t type() const { return at<2>().as_int32(); }
  bool has_layer_name() const { return at<3>().valid(); }
  ::protozero::ConstChars layer_name() const { return at<3>().as_string(); }
  bool has_duration_ns() const { return at<4>().valid(); }
  uint64_t duration_ns() const { return at<4>().as_uint64(); }
  bool has_buffer_id() const { return at<5>().valid(); }
  uint32_t buffer_id() const { return at<5>().as_uint32(); }
};

class GraphicsFrameEvent_BufferEvent : public ::protozero::Message {
 public:
  using Decoder = GraphicsFrameEvent_BufferEvent_Decoder;
  enum : int32_t {
    kFrameNumberFieldNumber = 1,
    kTypeFieldNumber = 2,
    kLayerNameFieldNumber = 3,
    kDurationNsFieldNumber = 4,
    kBufferIdFieldNumber = 5,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.GraphicsFrameEvent.BufferEvent"; }


  using FieldMetadata_FrameNumber =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kUint32,
      uint32_t,
      GraphicsFrameEvent_BufferEvent>;

  static constexpr FieldMetadata_FrameNumber kFrameNumber{};
  void set_frame_number(uint32_t value) {
    static constexpr uint32_t field_id = FieldMetadata_FrameNumber::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kUint32>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_Type =
    ::protozero::proto_utils::FieldMetadata<
      2,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kEnum,
      GraphicsFrameEvent_BufferEventType,
      GraphicsFrameEvent_BufferEvent>;

  static constexpr FieldMetadata_Type kType{};
  void set_type(GraphicsFrameEvent_BufferEventType value) {
    static constexpr uint32_t field_id = FieldMetadata_Type::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kEnum>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_LayerName =
    ::protozero::proto_utils::FieldMetadata<
      3,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kString,
      std::string,
      GraphicsFrameEvent_BufferEvent>;

  static constexpr FieldMetadata_LayerName kLayerName{};
  void set_layer_name(const char* data, size_t size) {
    AppendBytes(FieldMetadata_LayerName::kFieldId, data, size);
  }
  void set_layer_name(::protozero::ConstChars chars) {
    AppendBytes(FieldMetadata_LayerName::kFieldId, chars.data, chars.size);
  }
  void set_layer_name(std::string value) {
    static constexpr uint32_t field_id = FieldMetadata_LayerName::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kString>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_DurationNs =
    ::protozero::proto_utils::FieldMetadata<
      4,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kUint64,
      uint64_t,
      GraphicsFrameEvent_BufferEvent>;

  static constexpr FieldMetadata_DurationNs kDurationNs{};
  void set_duration_ns(uint64_t value) {
    static constexpr uint32_t field_id = FieldMetadata_DurationNs::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kUint64>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_BufferId =
    ::protozero::proto_utils::FieldMetadata<
      5,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kUint32,
      uint32_t,
      GraphicsFrameEvent_BufferEvent>;

  static constexpr FieldMetadata_BufferId kBufferId{};
  void set_buffer_id(uint32_t value) {
    static constexpr uint32_t field_id = FieldMetadata_BufferId::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kUint32>
        ::Append(*this, field_id, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
