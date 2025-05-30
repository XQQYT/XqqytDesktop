// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_ANDROID_ANDROID_INPUT_EVENT_CONFIG_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_ANDROID_ANDROID_INPUT_EVENT_CONFIG_PROTO_H_

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
class AndroidInputEventConfig_TraceRule;
namespace perfetto_pbzero_enum_AndroidInputEventConfig {
enum TraceLevel : int32_t;
}  // namespace perfetto_pbzero_enum_AndroidInputEventConfig
using AndroidInputEventConfig_TraceLevel = perfetto_pbzero_enum_AndroidInputEventConfig::TraceLevel;
namespace perfetto_pbzero_enum_AndroidInputEventConfig {
enum TraceMode : int32_t;
}  // namespace perfetto_pbzero_enum_AndroidInputEventConfig
using AndroidInputEventConfig_TraceMode = perfetto_pbzero_enum_AndroidInputEventConfig::TraceMode;
} // Namespace pbzero.
} // Namespace protos.
} // Namespace perfetto.

namespace perfetto {
namespace protos {
namespace pbzero {

namespace perfetto_pbzero_enum_AndroidInputEventConfig {
enum TraceMode : int32_t {
  TRACE_MODE_TRACE_ALL = 0,
  TRACE_MODE_USE_RULES = 1,
};
} // namespace perfetto_pbzero_enum_AndroidInputEventConfig
using AndroidInputEventConfig_TraceMode = perfetto_pbzero_enum_AndroidInputEventConfig::TraceMode;


constexpr AndroidInputEventConfig_TraceMode AndroidInputEventConfig_TraceMode_MIN = AndroidInputEventConfig_TraceMode::TRACE_MODE_TRACE_ALL;
constexpr AndroidInputEventConfig_TraceMode AndroidInputEventConfig_TraceMode_MAX = AndroidInputEventConfig_TraceMode::TRACE_MODE_USE_RULES;


PERFETTO_PROTOZERO_CONSTEXPR14_OR_INLINE
const char* AndroidInputEventConfig_TraceMode_Name(::perfetto::protos::pbzero::AndroidInputEventConfig_TraceMode value) {
  switch (value) {
  case ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceMode::TRACE_MODE_TRACE_ALL:
    return "TRACE_MODE_TRACE_ALL";

  case ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceMode::TRACE_MODE_USE_RULES:
    return "TRACE_MODE_USE_RULES";
  }
  return "PBZERO_UNKNOWN_ENUM_VALUE";
}

namespace perfetto_pbzero_enum_AndroidInputEventConfig {
enum TraceLevel : int32_t {
  TRACE_LEVEL_NONE = 0,
  TRACE_LEVEL_REDACTED = 1,
  TRACE_LEVEL_COMPLETE = 2,
};
} // namespace perfetto_pbzero_enum_AndroidInputEventConfig
using AndroidInputEventConfig_TraceLevel = perfetto_pbzero_enum_AndroidInputEventConfig::TraceLevel;


constexpr AndroidInputEventConfig_TraceLevel AndroidInputEventConfig_TraceLevel_MIN = AndroidInputEventConfig_TraceLevel::TRACE_LEVEL_NONE;
constexpr AndroidInputEventConfig_TraceLevel AndroidInputEventConfig_TraceLevel_MAX = AndroidInputEventConfig_TraceLevel::TRACE_LEVEL_COMPLETE;


PERFETTO_PROTOZERO_CONSTEXPR14_OR_INLINE
const char* AndroidInputEventConfig_TraceLevel_Name(::perfetto::protos::pbzero::AndroidInputEventConfig_TraceLevel value) {
  switch (value) {
  case ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceLevel::TRACE_LEVEL_NONE:
    return "TRACE_LEVEL_NONE";

  case ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceLevel::TRACE_LEVEL_REDACTED:
    return "TRACE_LEVEL_REDACTED";

  case ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceLevel::TRACE_LEVEL_COMPLETE:
    return "TRACE_LEVEL_COMPLETE";
  }
  return "PBZERO_UNKNOWN_ENUM_VALUE";
}

class AndroidInputEventConfig_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  AndroidInputEventConfig_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit AndroidInputEventConfig_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit AndroidInputEventConfig_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_mode() const { return at<1>().valid(); }
  int32_t mode() const { return at<1>().as_int32(); }
  bool has_rules() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> rules() const { return GetRepeated<::protozero::ConstBytes>(2); }
  bool has_trace_dispatcher_input_events() const { return at<3>().valid(); }
  bool trace_dispatcher_input_events() const { return at<3>().as_bool(); }
  bool has_trace_dispatcher_window_dispatch() const { return at<4>().valid(); }
  bool trace_dispatcher_window_dispatch() const { return at<4>().as_bool(); }
};

class AndroidInputEventConfig : public ::protozero::Message {
 public:
  using Decoder = AndroidInputEventConfig_Decoder;
  enum : int32_t {
    kModeFieldNumber = 1,
    kRulesFieldNumber = 2,
    kTraceDispatcherInputEventsFieldNumber = 3,
    kTraceDispatcherWindowDispatchFieldNumber = 4,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.AndroidInputEventConfig"; }

  using TraceRule = ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceRule;

  using TraceMode = ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceMode;
  static inline const char* TraceMode_Name(TraceMode value) {
    return ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceMode_Name(value);
  }

  using TraceLevel = ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceLevel;
  static inline const char* TraceLevel_Name(TraceLevel value) {
    return ::perfetto::protos::pbzero::AndroidInputEventConfig_TraceLevel_Name(value);
  }
  static inline const TraceMode TRACE_MODE_TRACE_ALL = TraceMode::TRACE_MODE_TRACE_ALL;
  static inline const TraceMode TRACE_MODE_USE_RULES = TraceMode::TRACE_MODE_USE_RULES;
  static inline const TraceLevel TRACE_LEVEL_NONE = TraceLevel::TRACE_LEVEL_NONE;
  static inline const TraceLevel TRACE_LEVEL_REDACTED = TraceLevel::TRACE_LEVEL_REDACTED;
  static inline const TraceLevel TRACE_LEVEL_COMPLETE = TraceLevel::TRACE_LEVEL_COMPLETE;

  using FieldMetadata_Mode =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kEnum,
      AndroidInputEventConfig_TraceMode,
      AndroidInputEventConfig>;

  static constexpr FieldMetadata_Mode kMode{};
  void set_mode(AndroidInputEventConfig_TraceMode value) {
    static constexpr uint32_t field_id = FieldMetadata_Mode::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kEnum>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_Rules =
    ::protozero::proto_utils::FieldMetadata<
      2,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kMessage,
      AndroidInputEventConfig_TraceRule,
      AndroidInputEventConfig>;

  static constexpr FieldMetadata_Rules kRules{};
  template <typename T = AndroidInputEventConfig_TraceRule> T* add_rules() {
    return BeginNestedMessage<T>(2);
  }


  using FieldMetadata_TraceDispatcherInputEvents =
    ::protozero::proto_utils::FieldMetadata<
      3,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kBool,
      bool,
      AndroidInputEventConfig>;

  static constexpr FieldMetadata_TraceDispatcherInputEvents kTraceDispatcherInputEvents{};
  void set_trace_dispatcher_input_events(bool value) {
    static constexpr uint32_t field_id = FieldMetadata_TraceDispatcherInputEvents::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kBool>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_TraceDispatcherWindowDispatch =
    ::protozero::proto_utils::FieldMetadata<
      4,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kBool,
      bool,
      AndroidInputEventConfig>;

  static constexpr FieldMetadata_TraceDispatcherWindowDispatch kTraceDispatcherWindowDispatch{};
  void set_trace_dispatcher_window_dispatch(bool value) {
    static constexpr uint32_t field_id = FieldMetadata_TraceDispatcherWindowDispatch::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kBool>
        ::Append(*this, field_id, value);
  }
};

class AndroidInputEventConfig_TraceRule_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  AndroidInputEventConfig_TraceRule_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit AndroidInputEventConfig_TraceRule_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit AndroidInputEventConfig_TraceRule_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_trace_level() const { return at<1>().valid(); }
  int32_t trace_level() const { return at<1>().as_int32(); }
  bool has_match_all_packages() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> match_all_packages() const { return GetRepeated<::protozero::ConstChars>(2); }
  bool has_match_any_packages() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> match_any_packages() const { return GetRepeated<::protozero::ConstChars>(3); }
  bool has_match_secure() const { return at<4>().valid(); }
  bool match_secure() const { return at<4>().as_bool(); }
  bool has_match_ime_connection_active() const { return at<5>().valid(); }
  bool match_ime_connection_active() const { return at<5>().as_bool(); }
};

class AndroidInputEventConfig_TraceRule : public ::protozero::Message {
 public:
  using Decoder = AndroidInputEventConfig_TraceRule_Decoder;
  enum : int32_t {
    kTraceLevelFieldNumber = 1,
    kMatchAllPackagesFieldNumber = 2,
    kMatchAnyPackagesFieldNumber = 3,
    kMatchSecureFieldNumber = 4,
    kMatchImeConnectionActiveFieldNumber = 5,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.AndroidInputEventConfig.TraceRule"; }


  using FieldMetadata_TraceLevel =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kEnum,
      AndroidInputEventConfig_TraceLevel,
      AndroidInputEventConfig_TraceRule>;

  static constexpr FieldMetadata_TraceLevel kTraceLevel{};
  void set_trace_level(AndroidInputEventConfig_TraceLevel value) {
    static constexpr uint32_t field_id = FieldMetadata_TraceLevel::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kEnum>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_MatchAllPackages =
    ::protozero::proto_utils::FieldMetadata<
      2,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kString,
      std::string,
      AndroidInputEventConfig_TraceRule>;

  static constexpr FieldMetadata_MatchAllPackages kMatchAllPackages{};
  void add_match_all_packages(const char* data, size_t size) {
    AppendBytes(FieldMetadata_MatchAllPackages::kFieldId, data, size);
  }
  void add_match_all_packages(::protozero::ConstChars chars) {
    AppendBytes(FieldMetadata_MatchAllPackages::kFieldId, chars.data, chars.size);
  }
  void add_match_all_packages(std::string value) {
    static constexpr uint32_t field_id = FieldMetadata_MatchAllPackages::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kString>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_MatchAnyPackages =
    ::protozero::proto_utils::FieldMetadata<
      3,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kString,
      std::string,
      AndroidInputEventConfig_TraceRule>;

  static constexpr FieldMetadata_MatchAnyPackages kMatchAnyPackages{};
  void add_match_any_packages(const char* data, size_t size) {
    AppendBytes(FieldMetadata_MatchAnyPackages::kFieldId, data, size);
  }
  void add_match_any_packages(::protozero::ConstChars chars) {
    AppendBytes(FieldMetadata_MatchAnyPackages::kFieldId, chars.data, chars.size);
  }
  void add_match_any_packages(std::string value) {
    static constexpr uint32_t field_id = FieldMetadata_MatchAnyPackages::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kString>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_MatchSecure =
    ::protozero::proto_utils::FieldMetadata<
      4,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kBool,
      bool,
      AndroidInputEventConfig_TraceRule>;

  static constexpr FieldMetadata_MatchSecure kMatchSecure{};
  void set_match_secure(bool value) {
    static constexpr uint32_t field_id = FieldMetadata_MatchSecure::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kBool>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_MatchImeConnectionActive =
    ::protozero::proto_utils::FieldMetadata<
      5,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kBool,
      bool,
      AndroidInputEventConfig_TraceRule>;

  static constexpr FieldMetadata_MatchImeConnectionActive kMatchImeConnectionActive{};
  void set_match_ime_connection_active(bool value) {
    static constexpr uint32_t field_id = FieldMetadata_MatchImeConnectionActive::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kBool>
        ::Append(*this, field_id, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
