// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_GPU_GPU_RENDERSTAGES_CONFIG_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_GPU_GPU_RENDERSTAGES_CONFIG_PROTO_H_

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

class GpuRenderStagesConfig_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  GpuRenderStagesConfig_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GpuRenderStagesConfig_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GpuRenderStagesConfig_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_full_loadstore() const { return at<1>().valid(); }
  bool full_loadstore() const { return at<1>().as_bool(); }
  bool has_low_overhead() const { return at<2>().valid(); }
  bool low_overhead() const { return at<2>().as_bool(); }
  bool has_trace_metrics() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> trace_metrics() const { return GetRepeated<::protozero::ConstChars>(3); }
};

class GpuRenderStagesConfig : public ::protozero::Message {
 public:
  using Decoder = GpuRenderStagesConfig_Decoder;
  enum : int32_t {
    kFullLoadstoreFieldNumber = 1,
    kLowOverheadFieldNumber = 2,
    kTraceMetricsFieldNumber = 3,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.GpuRenderStagesConfig"; }


  using FieldMetadata_FullLoadstore =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kBool,
      bool,
      GpuRenderStagesConfig>;

  static constexpr FieldMetadata_FullLoadstore kFullLoadstore{};
  void set_full_loadstore(bool value) {
    static constexpr uint32_t field_id = FieldMetadata_FullLoadstore::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kBool>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_LowOverhead =
    ::protozero::proto_utils::FieldMetadata<
      2,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kBool,
      bool,
      GpuRenderStagesConfig>;

  static constexpr FieldMetadata_LowOverhead kLowOverhead{};
  void set_low_overhead(bool value) {
    static constexpr uint32_t field_id = FieldMetadata_LowOverhead::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kBool>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_TraceMetrics =
    ::protozero::proto_utils::FieldMetadata<
      3,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kString,
      std::string,
      GpuRenderStagesConfig>;

  static constexpr FieldMetadata_TraceMetrics kTraceMetrics{};
  void add_trace_metrics(const char* data, size_t size) {
    AppendBytes(FieldMetadata_TraceMetrics::kFieldId, data, size);
  }
  void add_trace_metrics(::protozero::ConstChars chars) {
    AppendBytes(FieldMetadata_TraceMetrics::kFieldId, chars.data, chars.size);
  }
  void add_trace_metrics(std::string value) {
    static constexpr uint32_t field_id = FieldMetadata_TraceMetrics::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kString>
        ::Append(*this, field_id, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
