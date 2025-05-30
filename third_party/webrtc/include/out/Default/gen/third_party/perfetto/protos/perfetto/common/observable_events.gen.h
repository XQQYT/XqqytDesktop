// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_COMMON_OBSERVABLE_EVENTS_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_COMMON_OBSERVABLE_EVENTS_PROTO_CPP_H_

#include <stdint.h>
#include <bitset>
#include <vector>
#include <string>
#include <type_traits>

#include "perfetto/protozero/cpp_message_obj.h"
#include "perfetto/protozero/copyable_ptr.h"
#include "perfetto/base/export.h"

namespace perfetto {
namespace protos {
namespace gen {
class ObservableEvents;
class ObservableEvents_CloneTriggerHit;
class ObservableEvents_DataSourceInstanceStateChange;
enum ObservableEvents_Type : int;
enum ObservableEvents_DataSourceInstanceState : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {
enum ObservableEvents_Type : int {
  ObservableEvents_Type_TYPE_UNSPECIFIED = 0,
  ObservableEvents_Type_TYPE_DATA_SOURCES_INSTANCES = 1,
  ObservableEvents_Type_TYPE_ALL_DATA_SOURCES_STARTED = 2,
  ObservableEvents_Type_TYPE_CLONE_TRIGGER_HIT = 4,
};
enum ObservableEvents_DataSourceInstanceState : int {
  ObservableEvents_DataSourceInstanceState_DATA_SOURCE_INSTANCE_STATE_STOPPED = 1,
  ObservableEvents_DataSourceInstanceState_DATA_SOURCE_INSTANCE_STATE_STARTED = 2,
};

class PERFETTO_EXPORT_COMPONENT ObservableEvents : public ::protozero::CppMessageObj {
 public:
  using DataSourceInstanceStateChange = ObservableEvents_DataSourceInstanceStateChange;
  using CloneTriggerHit = ObservableEvents_CloneTriggerHit;
  using Type = ObservableEvents_Type;
  static constexpr auto TYPE_UNSPECIFIED = ObservableEvents_Type_TYPE_UNSPECIFIED;
  static constexpr auto TYPE_DATA_SOURCES_INSTANCES = ObservableEvents_Type_TYPE_DATA_SOURCES_INSTANCES;
  static constexpr auto TYPE_ALL_DATA_SOURCES_STARTED = ObservableEvents_Type_TYPE_ALL_DATA_SOURCES_STARTED;
  static constexpr auto TYPE_CLONE_TRIGGER_HIT = ObservableEvents_Type_TYPE_CLONE_TRIGGER_HIT;
  static constexpr auto Type_MIN = ObservableEvents_Type_TYPE_UNSPECIFIED;
  static constexpr auto Type_MAX = ObservableEvents_Type_TYPE_CLONE_TRIGGER_HIT;
  using DataSourceInstanceState = ObservableEvents_DataSourceInstanceState;
  static constexpr auto DATA_SOURCE_INSTANCE_STATE_STOPPED = ObservableEvents_DataSourceInstanceState_DATA_SOURCE_INSTANCE_STATE_STOPPED;
  static constexpr auto DATA_SOURCE_INSTANCE_STATE_STARTED = ObservableEvents_DataSourceInstanceState_DATA_SOURCE_INSTANCE_STATE_STARTED;
  static constexpr auto DataSourceInstanceState_MIN = ObservableEvents_DataSourceInstanceState_DATA_SOURCE_INSTANCE_STATE_STOPPED;
  static constexpr auto DataSourceInstanceState_MAX = ObservableEvents_DataSourceInstanceState_DATA_SOURCE_INSTANCE_STATE_STARTED;
  enum FieldNumbers {
    kInstanceStateChangesFieldNumber = 1,
    kAllDataSourcesStartedFieldNumber = 2,
    kCloneTriggerHitFieldNumber = 3,
  };

  ObservableEvents();
  ~ObservableEvents() override;
  ObservableEvents(ObservableEvents&&) noexcept;
  ObservableEvents& operator=(ObservableEvents&&);
  ObservableEvents(const ObservableEvents&);
  ObservableEvents& operator=(const ObservableEvents&);
  bool operator==(const ObservableEvents&) const;
  bool operator!=(const ObservableEvents& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  const std::vector<ObservableEvents_DataSourceInstanceStateChange>& instance_state_changes() const { return instance_state_changes_; }
  std::vector<ObservableEvents_DataSourceInstanceStateChange>* mutable_instance_state_changes() { return &instance_state_changes_; }
  int instance_state_changes_size() const;
  void clear_instance_state_changes();
  ObservableEvents_DataSourceInstanceStateChange* add_instance_state_changes();

  bool has_all_data_sources_started() const { return _has_field_[2]; }
  bool all_data_sources_started() const { return all_data_sources_started_; }
  void set_all_data_sources_started(bool value) { all_data_sources_started_ = value; _has_field_.set(2); }

  bool has_clone_trigger_hit() const { return _has_field_[3]; }
  const ObservableEvents_CloneTriggerHit& clone_trigger_hit() const { return *clone_trigger_hit_; }
  ObservableEvents_CloneTriggerHit* mutable_clone_trigger_hit() { _has_field_.set(3); return clone_trigger_hit_.get(); }

 private:
  std::vector<ObservableEvents_DataSourceInstanceStateChange> instance_state_changes_;
  bool all_data_sources_started_{};
  ::protozero::CopyablePtr<ObservableEvents_CloneTriggerHit> clone_trigger_hit_;

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<4> _has_field_{};
};


class PERFETTO_EXPORT_COMPONENT ObservableEvents_CloneTriggerHit : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kTracingSessionIdFieldNumber = 1,
    kTriggerNameFieldNumber = 2,
    kProducerNameFieldNumber = 3,
    kProducerUidFieldNumber = 4,
    kBootTimeNsFieldNumber = 5,
  };

  ObservableEvents_CloneTriggerHit();
  ~ObservableEvents_CloneTriggerHit() override;
  ObservableEvents_CloneTriggerHit(ObservableEvents_CloneTriggerHit&&) noexcept;
  ObservableEvents_CloneTriggerHit& operator=(ObservableEvents_CloneTriggerHit&&);
  ObservableEvents_CloneTriggerHit(const ObservableEvents_CloneTriggerHit&);
  ObservableEvents_CloneTriggerHit& operator=(const ObservableEvents_CloneTriggerHit&);
  bool operator==(const ObservableEvents_CloneTriggerHit&) const;
  bool operator!=(const ObservableEvents_CloneTriggerHit& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_tracing_session_id() const { return _has_field_[1]; }
  int64_t tracing_session_id() const { return tracing_session_id_; }
  void set_tracing_session_id(int64_t value) { tracing_session_id_ = value; _has_field_.set(1); }

  bool has_trigger_name() const { return _has_field_[2]; }
  const std::string& trigger_name() const { return trigger_name_; }
  void set_trigger_name(const std::string& value) { trigger_name_ = value; _has_field_.set(2); }

  bool has_producer_name() const { return _has_field_[3]; }
  const std::string& producer_name() const { return producer_name_; }
  void set_producer_name(const std::string& value) { producer_name_ = value; _has_field_.set(3); }

  bool has_producer_uid() const { return _has_field_[4]; }
  uint32_t producer_uid() const { return producer_uid_; }
  void set_producer_uid(uint32_t value) { producer_uid_ = value; _has_field_.set(4); }

  bool has_boot_time_ns() const { return _has_field_[5]; }
  uint64_t boot_time_ns() const { return boot_time_ns_; }
  void set_boot_time_ns(uint64_t value) { boot_time_ns_ = value; _has_field_.set(5); }

 private:
  int64_t tracing_session_id_{};
  std::string trigger_name_{};
  std::string producer_name_{};
  uint32_t producer_uid_{};
  uint64_t boot_time_ns_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<6> _has_field_{};
};


class PERFETTO_EXPORT_COMPONENT ObservableEvents_DataSourceInstanceStateChange : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kProducerNameFieldNumber = 1,
    kDataSourceNameFieldNumber = 2,
    kStateFieldNumber = 3,
  };

  ObservableEvents_DataSourceInstanceStateChange();
  ~ObservableEvents_DataSourceInstanceStateChange() override;
  ObservableEvents_DataSourceInstanceStateChange(ObservableEvents_DataSourceInstanceStateChange&&) noexcept;
  ObservableEvents_DataSourceInstanceStateChange& operator=(ObservableEvents_DataSourceInstanceStateChange&&);
  ObservableEvents_DataSourceInstanceStateChange(const ObservableEvents_DataSourceInstanceStateChange&);
  ObservableEvents_DataSourceInstanceStateChange& operator=(const ObservableEvents_DataSourceInstanceStateChange&);
  bool operator==(const ObservableEvents_DataSourceInstanceStateChange&) const;
  bool operator!=(const ObservableEvents_DataSourceInstanceStateChange& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_producer_name() const { return _has_field_[1]; }
  const std::string& producer_name() const { return producer_name_; }
  void set_producer_name(const std::string& value) { producer_name_ = value; _has_field_.set(1); }

  bool has_data_source_name() const { return _has_field_[2]; }
  const std::string& data_source_name() const { return data_source_name_; }
  void set_data_source_name(const std::string& value) { data_source_name_ = value; _has_field_.set(2); }

  bool has_state() const { return _has_field_[3]; }
  ObservableEvents_DataSourceInstanceState state() const { return state_; }
  void set_state(ObservableEvents_DataSourceInstanceState value) { state_ = value; _has_field_.set(3); }

 private:
  std::string producer_name_{};
  std::string data_source_name_{};
  ObservableEvents_DataSourceInstanceState state_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<4> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_COMMON_OBSERVABLE_EVENTS_PROTO_CPP_H_
