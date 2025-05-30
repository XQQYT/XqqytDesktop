// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_ANDROID_PROTOLOG_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_ANDROID_PROTOLOG_PROTO_H_

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
class ProtoLogViewerConfig_Group;
class ProtoLogViewerConfig_MessageData;
enum ProtoLogLevel : int32_t;
} // Namespace pbzero.
} // Namespace protos.
} // Namespace perfetto.

namespace perfetto {
namespace protos {
namespace pbzero {

class ProtoLogViewerConfig_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  ProtoLogViewerConfig_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ProtoLogViewerConfig_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ProtoLogViewerConfig_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_messages() const { return at<1>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> messages() const { return GetRepeated<::protozero::ConstBytes>(1); }
  bool has_groups() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> groups() const { return GetRepeated<::protozero::ConstBytes>(2); }
};

class ProtoLogViewerConfig : public ::protozero::Message {
 public:
  using Decoder = ProtoLogViewerConfig_Decoder;
  enum : int32_t {
    kMessagesFieldNumber = 1,
    kGroupsFieldNumber = 2,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.ProtoLogViewerConfig"; }

  using MessageData = ::perfetto::protos::pbzero::ProtoLogViewerConfig_MessageData;
  using Group = ::perfetto::protos::pbzero::ProtoLogViewerConfig_Group;

  using FieldMetadata_Messages =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kMessage,
      ProtoLogViewerConfig_MessageData,
      ProtoLogViewerConfig>;

  static constexpr FieldMetadata_Messages kMessages{};
  template <typename T = ProtoLogViewerConfig_MessageData> T* add_messages() {
    return BeginNestedMessage<T>(1);
  }


  using FieldMetadata_Groups =
    ::protozero::proto_utils::FieldMetadata<
      2,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kMessage,
      ProtoLogViewerConfig_Group,
      ProtoLogViewerConfig>;

  static constexpr FieldMetadata_Groups kGroups{};
  template <typename T = ProtoLogViewerConfig_Group> T* add_groups() {
    return BeginNestedMessage<T>(2);
  }

};

class ProtoLogViewerConfig_Group_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ProtoLogViewerConfig_Group_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ProtoLogViewerConfig_Group_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ProtoLogViewerConfig_Group_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_id() const { return at<1>().valid(); }
  uint32_t id() const { return at<1>().as_uint32(); }
  bool has_name() const { return at<2>().valid(); }
  ::protozero::ConstChars name() const { return at<2>().as_string(); }
  bool has_tag() const { return at<3>().valid(); }
  ::protozero::ConstChars tag() const { return at<3>().as_string(); }
};

class ProtoLogViewerConfig_Group : public ::protozero::Message {
 public:
  using Decoder = ProtoLogViewerConfig_Group_Decoder;
  enum : int32_t {
    kIdFieldNumber = 1,
    kNameFieldNumber = 2,
    kTagFieldNumber = 3,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.ProtoLogViewerConfig.Group"; }


  using FieldMetadata_Id =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kUint32,
      uint32_t,
      ProtoLogViewerConfig_Group>;

  static constexpr FieldMetadata_Id kId{};
  void set_id(uint32_t value) {
    static constexpr uint32_t field_id = FieldMetadata_Id::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kUint32>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_Name =
    ::protozero::proto_utils::FieldMetadata<
      2,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kString,
      std::string,
      ProtoLogViewerConfig_Group>;

  static constexpr FieldMetadata_Name kName{};
  void set_name(const char* data, size_t size) {
    AppendBytes(FieldMetadata_Name::kFieldId, data, size);
  }
  void set_name(::protozero::ConstChars chars) {
    AppendBytes(FieldMetadata_Name::kFieldId, chars.data, chars.size);
  }
  void set_name(std::string value) {
    static constexpr uint32_t field_id = FieldMetadata_Name::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kString>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_Tag =
    ::protozero::proto_utils::FieldMetadata<
      3,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kString,
      std::string,
      ProtoLogViewerConfig_Group>;

  static constexpr FieldMetadata_Tag kTag{};
  void set_tag(const char* data, size_t size) {
    AppendBytes(FieldMetadata_Tag::kFieldId, data, size);
  }
  void set_tag(::protozero::ConstChars chars) {
    AppendBytes(FieldMetadata_Tag::kFieldId, chars.data, chars.size);
  }
  void set_tag(std::string value) {
    static constexpr uint32_t field_id = FieldMetadata_Tag::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kString>
        ::Append(*this, field_id, value);
  }
};

class ProtoLogViewerConfig_MessageData_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ProtoLogViewerConfig_MessageData_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ProtoLogViewerConfig_MessageData_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ProtoLogViewerConfig_MessageData_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_message_id() const { return at<1>().valid(); }
  uint64_t message_id() const { return at<1>().as_uint64(); }
  bool has_message() const { return at<2>().valid(); }
  ::protozero::ConstChars message() const { return at<2>().as_string(); }
  bool has_level() const { return at<3>().valid(); }
  int32_t level() const { return at<3>().as_int32(); }
  bool has_group_id() const { return at<4>().valid(); }
  uint32_t group_id() const { return at<4>().as_uint32(); }
  bool has_location() const { return at<5>().valid(); }
  ::protozero::ConstChars location() const { return at<5>().as_string(); }
};

class ProtoLogViewerConfig_MessageData : public ::protozero::Message {
 public:
  using Decoder = ProtoLogViewerConfig_MessageData_Decoder;
  enum : int32_t {
    kMessageIdFieldNumber = 1,
    kMessageFieldNumber = 2,
    kLevelFieldNumber = 3,
    kGroupIdFieldNumber = 4,
    kLocationFieldNumber = 5,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.ProtoLogViewerConfig.MessageData"; }


  using FieldMetadata_MessageId =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kFixed64,
      uint64_t,
      ProtoLogViewerConfig_MessageData>;

  static constexpr FieldMetadata_MessageId kMessageId{};
  void set_message_id(uint64_t value) {
    static constexpr uint32_t field_id = FieldMetadata_MessageId::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kFixed64>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_Message =
    ::protozero::proto_utils::FieldMetadata<
      2,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kString,
      std::string,
      ProtoLogViewerConfig_MessageData>;

  static constexpr FieldMetadata_Message kMessage{};
  void set_message(const char* data, size_t size) {
    AppendBytes(FieldMetadata_Message::kFieldId, data, size);
  }
  void set_message(::protozero::ConstChars chars) {
    AppendBytes(FieldMetadata_Message::kFieldId, chars.data, chars.size);
  }
  void set_message(std::string value) {
    static constexpr uint32_t field_id = FieldMetadata_Message::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kString>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_Level =
    ::protozero::proto_utils::FieldMetadata<
      3,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kEnum,
      ProtoLogLevel,
      ProtoLogViewerConfig_MessageData>;

  static constexpr FieldMetadata_Level kLevel{};
  void set_level(ProtoLogLevel value) {
    static constexpr uint32_t field_id = FieldMetadata_Level::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kEnum>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_GroupId =
    ::protozero::proto_utils::FieldMetadata<
      4,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kUint32,
      uint32_t,
      ProtoLogViewerConfig_MessageData>;

  static constexpr FieldMetadata_GroupId kGroupId{};
  void set_group_id(uint32_t value) {
    static constexpr uint32_t field_id = FieldMetadata_GroupId::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kUint32>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_Location =
    ::protozero::proto_utils::FieldMetadata<
      5,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kString,
      std::string,
      ProtoLogViewerConfig_MessageData>;

  static constexpr FieldMetadata_Location kLocation{};
  void set_location(const char* data, size_t size) {
    AppendBytes(FieldMetadata_Location::kFieldId, data, size);
  }
  void set_location(::protozero::ConstChars chars) {
    AppendBytes(FieldMetadata_Location::kFieldId, chars.data, chars.size);
  }
  void set_location(std::string value) {
    static constexpr uint32_t field_id = FieldMetadata_Location::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kString>
        ::Append(*this, field_id, value);
  }
};

class ProtoLogMessage_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/6, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  ProtoLogMessage_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ProtoLogMessage_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ProtoLogMessage_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_message_id() const { return at<1>().valid(); }
  uint64_t message_id() const { return at<1>().as_uint64(); }
  bool has_str_param_iids() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<uint32_t> str_param_iids() const { return GetRepeated<uint32_t>(2); }
  bool has_sint64_params() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<int64_t> sint64_params() const { return GetRepeated<int64_t>(3); }
  bool has_double_params() const { return at<4>().valid(); }
  ::protozero::RepeatedFieldIterator<double> double_params() const { return GetRepeated<double>(4); }
  bool has_boolean_params() const { return at<5>().valid(); }
  ::protozero::RepeatedFieldIterator<int32_t> boolean_params() const { return GetRepeated<int32_t>(5); }
  bool has_stacktrace_iid() const { return at<6>().valid(); }
  uint32_t stacktrace_iid() const { return at<6>().as_uint32(); }
};

class ProtoLogMessage : public ::protozero::Message {
 public:
  using Decoder = ProtoLogMessage_Decoder;
  enum : int32_t {
    kMessageIdFieldNumber = 1,
    kStrParamIidsFieldNumber = 2,
    kSint64ParamsFieldNumber = 3,
    kDoubleParamsFieldNumber = 4,
    kBooleanParamsFieldNumber = 5,
    kStacktraceIidFieldNumber = 6,
  };
  static constexpr const char* GetName() { return ".perfetto.protos.ProtoLogMessage"; }


  using FieldMetadata_MessageId =
    ::protozero::proto_utils::FieldMetadata<
      1,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kFixed64,
      uint64_t,
      ProtoLogMessage>;

  static constexpr FieldMetadata_MessageId kMessageId{};
  void set_message_id(uint64_t value) {
    static constexpr uint32_t field_id = FieldMetadata_MessageId::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kFixed64>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_StrParamIids =
    ::protozero::proto_utils::FieldMetadata<
      2,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kUint32,
      uint32_t,
      ProtoLogMessage>;

  static constexpr FieldMetadata_StrParamIids kStrParamIids{};
  void add_str_param_iids(uint32_t value) {
    static constexpr uint32_t field_id = FieldMetadata_StrParamIids::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kUint32>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_Sint64Params =
    ::protozero::proto_utils::FieldMetadata<
      3,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kSint64,
      int64_t,
      ProtoLogMessage>;

  static constexpr FieldMetadata_Sint64Params kSint64Params{};
  void add_sint64_params(int64_t value) {
    static constexpr uint32_t field_id = FieldMetadata_Sint64Params::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kSint64>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_DoubleParams =
    ::protozero::proto_utils::FieldMetadata<
      4,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kDouble,
      double,
      ProtoLogMessage>;

  static constexpr FieldMetadata_DoubleParams kDoubleParams{};
  void add_double_params(double value) {
    static constexpr uint32_t field_id = FieldMetadata_DoubleParams::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kDouble>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_BooleanParams =
    ::protozero::proto_utils::FieldMetadata<
      5,
      ::protozero::proto_utils::RepetitionType::kRepeatedNotPacked,
      ::protozero::proto_utils::ProtoSchemaType::kInt32,
      int32_t,
      ProtoLogMessage>;

  static constexpr FieldMetadata_BooleanParams kBooleanParams{};
  void add_boolean_params(int32_t value) {
    static constexpr uint32_t field_id = FieldMetadata_BooleanParams::kFieldId;
    // Call the appropriate protozero::Message::Append(field_id, ...)
    // method based on the type of the field.
    ::protozero::internal::FieldWriter<
      ::protozero::proto_utils::ProtoSchemaType::kInt32>
        ::Append(*this, field_id, value);
  }

  using FieldMetadata_StacktraceIid =
    ::protozero::proto_utils::FieldMetadata<
      6,
      ::protozero::proto_utils::RepetitionType::kNotRepeated,
      ::protozero::proto_utils::ProtoSchemaType::kUint32,
      uint32_t,
      ProtoLogMessage>;

  static constexpr FieldMetadata_StacktraceIid kStacktraceIid{};
  void set_stacktrace_iid(uint32_t value) {
    static constexpr uint32_t field_id = FieldMetadata_StacktraceIid::kFieldId;
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
