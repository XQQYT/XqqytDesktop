// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_CHROME_FRAME_REPORTER_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_CHROME_FRAME_REPORTER_PROTO_CPP_H_

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
class ChromeFrameReporter;
enum ChromeFrameReporter_State : int;
enum ChromeFrameReporter_FrameDropReason : int;
enum ChromeFrameReporter_ScrollState : int;
enum ChromeFrameReporter_FrameType : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {
enum ChromeFrameReporter_State : int {
  ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED = 0,
  ChromeFrameReporter_State_STATE_PRESENTED_ALL = 1,
  ChromeFrameReporter_State_STATE_PRESENTED_PARTIAL = 2,
  ChromeFrameReporter_State_STATE_DROPPED = 3,
};
enum ChromeFrameReporter_FrameDropReason : int {
  ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED = 0,
  ChromeFrameReporter_FrameDropReason_REASON_DISPLAY_COMPOSITOR = 1,
  ChromeFrameReporter_FrameDropReason_REASON_MAIN_THREAD = 2,
  ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR = 3,
};
enum ChromeFrameReporter_ScrollState : int {
  ChromeFrameReporter_ScrollState_SCROLL_NONE = 0,
  ChromeFrameReporter_ScrollState_SCROLL_MAIN_THREAD = 1,
  ChromeFrameReporter_ScrollState_SCROLL_COMPOSITOR_THREAD = 2,
  ChromeFrameReporter_ScrollState_SCROLL_RASTER = 3,
  ChromeFrameReporter_ScrollState_SCROLL_UNKNOWN = 4,
};
enum ChromeFrameReporter_FrameType : int {
  ChromeFrameReporter_FrameType_FORKED = 0,
  ChromeFrameReporter_FrameType_BACKFILL = 1,
};

class PERFETTO_EXPORT_COMPONENT ChromeFrameReporter : public ::protozero::CppMessageObj {
 public:
  using State = ChromeFrameReporter_State;
  static constexpr auto STATE_NO_UPDATE_DESIRED = ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED;
  static constexpr auto STATE_PRESENTED_ALL = ChromeFrameReporter_State_STATE_PRESENTED_ALL;
  static constexpr auto STATE_PRESENTED_PARTIAL = ChromeFrameReporter_State_STATE_PRESENTED_PARTIAL;
  static constexpr auto STATE_DROPPED = ChromeFrameReporter_State_STATE_DROPPED;
  static constexpr auto State_MIN = ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED;
  static constexpr auto State_MAX = ChromeFrameReporter_State_STATE_DROPPED;
  using FrameDropReason = ChromeFrameReporter_FrameDropReason;
  static constexpr auto REASON_UNSPECIFIED = ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED;
  static constexpr auto REASON_DISPLAY_COMPOSITOR = ChromeFrameReporter_FrameDropReason_REASON_DISPLAY_COMPOSITOR;
  static constexpr auto REASON_MAIN_THREAD = ChromeFrameReporter_FrameDropReason_REASON_MAIN_THREAD;
  static constexpr auto REASON_CLIENT_COMPOSITOR = ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR;
  static constexpr auto FrameDropReason_MIN = ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED;
  static constexpr auto FrameDropReason_MAX = ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR;
  using ScrollState = ChromeFrameReporter_ScrollState;
  static constexpr auto SCROLL_NONE = ChromeFrameReporter_ScrollState_SCROLL_NONE;
  static constexpr auto SCROLL_MAIN_THREAD = ChromeFrameReporter_ScrollState_SCROLL_MAIN_THREAD;
  static constexpr auto SCROLL_COMPOSITOR_THREAD = ChromeFrameReporter_ScrollState_SCROLL_COMPOSITOR_THREAD;
  static constexpr auto SCROLL_RASTER = ChromeFrameReporter_ScrollState_SCROLL_RASTER;
  static constexpr auto SCROLL_UNKNOWN = ChromeFrameReporter_ScrollState_SCROLL_UNKNOWN;
  static constexpr auto ScrollState_MIN = ChromeFrameReporter_ScrollState_SCROLL_NONE;
  static constexpr auto ScrollState_MAX = ChromeFrameReporter_ScrollState_SCROLL_UNKNOWN;
  using FrameType = ChromeFrameReporter_FrameType;
  static constexpr auto FORKED = ChromeFrameReporter_FrameType_FORKED;
  static constexpr auto BACKFILL = ChromeFrameReporter_FrameType_BACKFILL;
  static constexpr auto FrameType_MIN = ChromeFrameReporter_FrameType_FORKED;
  static constexpr auto FrameType_MAX = ChromeFrameReporter_FrameType_BACKFILL;
  enum FieldNumbers {
    kStateFieldNumber = 1,
    kReasonFieldNumber = 2,
    kFrameSourceFieldNumber = 3,
    kFrameSequenceFieldNumber = 4,
    kAffectsSmoothnessFieldNumber = 5,
    kScrollStateFieldNumber = 6,
    kHasMainAnimationFieldNumber = 7,
    kHasCompositorAnimationFieldNumber = 8,
    kHasSmoothInputMainFieldNumber = 9,
    kHasMissingContentFieldNumber = 10,
    kLayerTreeHostIdFieldNumber = 11,
    kHasHighLatencyFieldNumber = 12,
    kFrameTypeFieldNumber = 13,
    kHighLatencyContributionStageFieldNumber = 14,
    kCheckerboardedNeedsRasterFieldNumber = 15,
    kCheckerboardedNeedsRecordFieldNumber = 16,
    kSurfaceFrameTraceIdFieldNumber = 17,
    kDisplayTraceIdFieldNumber = 18,
  };

  ChromeFrameReporter();
  ~ChromeFrameReporter() override;
  ChromeFrameReporter(ChromeFrameReporter&&) noexcept;
  ChromeFrameReporter& operator=(ChromeFrameReporter&&);
  ChromeFrameReporter(const ChromeFrameReporter&);
  ChromeFrameReporter& operator=(const ChromeFrameReporter&);
  bool operator==(const ChromeFrameReporter&) const;
  bool operator!=(const ChromeFrameReporter& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_state() const { return _has_field_[1]; }
  ChromeFrameReporter_State state() const { return state_; }
  void set_state(ChromeFrameReporter_State value) { state_ = value; _has_field_.set(1); }

  bool has_reason() const { return _has_field_[2]; }
  ChromeFrameReporter_FrameDropReason reason() const { return reason_; }
  void set_reason(ChromeFrameReporter_FrameDropReason value) { reason_ = value; _has_field_.set(2); }

  bool has_frame_source() const { return _has_field_[3]; }
  uint64_t frame_source() const { return frame_source_; }
  void set_frame_source(uint64_t value) { frame_source_ = value; _has_field_.set(3); }

  bool has_frame_sequence() const { return _has_field_[4]; }
  uint64_t frame_sequence() const { return frame_sequence_; }
  void set_frame_sequence(uint64_t value) { frame_sequence_ = value; _has_field_.set(4); }

  bool has_affects_smoothness() const { return _has_field_[5]; }
  bool affects_smoothness() const { return affects_smoothness_; }
  void set_affects_smoothness(bool value) { affects_smoothness_ = value; _has_field_.set(5); }

  bool has_scroll_state() const { return _has_field_[6]; }
  ChromeFrameReporter_ScrollState scroll_state() const { return scroll_state_; }
  void set_scroll_state(ChromeFrameReporter_ScrollState value) { scroll_state_ = value; _has_field_.set(6); }

  bool has_has_main_animation() const { return _has_field_[7]; }
  bool has_main_animation() const { return has_main_animation_; }
  void set_has_main_animation(bool value) { has_main_animation_ = value; _has_field_.set(7); }

  bool has_has_compositor_animation() const { return _has_field_[8]; }
  bool has_compositor_animation() const { return has_compositor_animation_; }
  void set_has_compositor_animation(bool value) { has_compositor_animation_ = value; _has_field_.set(8); }

  bool has_has_smooth_input_main() const { return _has_field_[9]; }
  bool has_smooth_input_main() const { return has_smooth_input_main_; }
  void set_has_smooth_input_main(bool value) { has_smooth_input_main_ = value; _has_field_.set(9); }

  bool has_has_missing_content() const { return _has_field_[10]; }
  bool has_missing_content() const { return has_missing_content_; }
  void set_has_missing_content(bool value) { has_missing_content_ = value; _has_field_.set(10); }

  bool has_layer_tree_host_id() const { return _has_field_[11]; }
  uint64_t layer_tree_host_id() const { return layer_tree_host_id_; }
  void set_layer_tree_host_id(uint64_t value) { layer_tree_host_id_ = value; _has_field_.set(11); }

  bool has_has_high_latency() const { return _has_field_[12]; }
  bool has_high_latency() const { return has_high_latency_; }
  void set_has_high_latency(bool value) { has_high_latency_ = value; _has_field_.set(12); }

  bool has_frame_type() const { return _has_field_[13]; }
  ChromeFrameReporter_FrameType frame_type() const { return frame_type_; }
  void set_frame_type(ChromeFrameReporter_FrameType value) { frame_type_ = value; _has_field_.set(13); }

  const std::vector<std::string>& high_latency_contribution_stage() const { return high_latency_contribution_stage_; }
  std::vector<std::string>* mutable_high_latency_contribution_stage() { return &high_latency_contribution_stage_; }
  int high_latency_contribution_stage_size() const { return static_cast<int>(high_latency_contribution_stage_.size()); }
  void clear_high_latency_contribution_stage() { high_latency_contribution_stage_.clear(); }
  void add_high_latency_contribution_stage(std::string value) { high_latency_contribution_stage_.emplace_back(value); }
  std::string* add_high_latency_contribution_stage() { high_latency_contribution_stage_.emplace_back(); return &high_latency_contribution_stage_.back(); }

  bool has_checkerboarded_needs_raster() const { return _has_field_[15]; }
  bool checkerboarded_needs_raster() const { return checkerboarded_needs_raster_; }
  void set_checkerboarded_needs_raster(bool value) { checkerboarded_needs_raster_ = value; _has_field_.set(15); }

  bool has_checkerboarded_needs_record() const { return _has_field_[16]; }
  bool checkerboarded_needs_record() const { return checkerboarded_needs_record_; }
  void set_checkerboarded_needs_record(bool value) { checkerboarded_needs_record_ = value; _has_field_.set(16); }

  bool has_surface_frame_trace_id() const { return _has_field_[17]; }
  int64_t surface_frame_trace_id() const { return surface_frame_trace_id_; }
  void set_surface_frame_trace_id(int64_t value) { surface_frame_trace_id_ = value; _has_field_.set(17); }

  bool has_display_trace_id() const { return _has_field_[18]; }
  int64_t display_trace_id() const { return display_trace_id_; }
  void set_display_trace_id(int64_t value) { display_trace_id_ = value; _has_field_.set(18); }

 private:
  ChromeFrameReporter_State state_{};
  ChromeFrameReporter_FrameDropReason reason_{};
  uint64_t frame_source_{};
  uint64_t frame_sequence_{};
  bool affects_smoothness_{};
  ChromeFrameReporter_ScrollState scroll_state_{};
  bool has_main_animation_{};
  bool has_compositor_animation_{};
  bool has_smooth_input_main_{};
  bool has_missing_content_{};
  uint64_t layer_tree_host_id_{};
  bool has_high_latency_{};
  ChromeFrameReporter_FrameType frame_type_{};
  std::vector<std::string> high_latency_contribution_stage_;
  bool checkerboarded_needs_raster_{};
  bool checkerboarded_needs_record_{};
  int64_t surface_frame_trace_id_{};
  int64_t display_trace_id_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<19> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_CHROME_FRAME_REPORTER_PROTO_CPP_H_
