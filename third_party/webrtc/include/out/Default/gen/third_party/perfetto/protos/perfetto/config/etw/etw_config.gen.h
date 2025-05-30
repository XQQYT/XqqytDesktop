// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_ETW_ETW_CONFIG_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_ETW_ETW_CONFIG_PROTO_CPP_H_

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
class EtwConfig;
enum EtwConfig_KernelFlag : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {
enum EtwConfig_KernelFlag : int {
  EtwConfig_KernelFlag_CSWITCH = 0,
  EtwConfig_KernelFlag_DISPATCHER = 1,
};

class PERFETTO_EXPORT_COMPONENT EtwConfig : public ::protozero::CppMessageObj {
 public:
  using KernelFlag = EtwConfig_KernelFlag;
  static constexpr auto CSWITCH = EtwConfig_KernelFlag_CSWITCH;
  static constexpr auto DISPATCHER = EtwConfig_KernelFlag_DISPATCHER;
  static constexpr auto KernelFlag_MIN = EtwConfig_KernelFlag_CSWITCH;
  static constexpr auto KernelFlag_MAX = EtwConfig_KernelFlag_DISPATCHER;
  enum FieldNumbers {
    kKernelFlagsFieldNumber = 1,
  };

  EtwConfig();
  ~EtwConfig() override;
  EtwConfig(EtwConfig&&) noexcept;
  EtwConfig& operator=(EtwConfig&&);
  EtwConfig(const EtwConfig&);
  EtwConfig& operator=(const EtwConfig&);
  bool operator==(const EtwConfig&) const;
  bool operator!=(const EtwConfig& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  const std::vector<EtwConfig_KernelFlag>& kernel_flags() const { return kernel_flags_; }
  std::vector<EtwConfig_KernelFlag>* mutable_kernel_flags() { return &kernel_flags_; }
  int kernel_flags_size() const { return static_cast<int>(kernel_flags_.size()); }
  void clear_kernel_flags() { kernel_flags_.clear(); }
  void add_kernel_flags(EtwConfig_KernelFlag value) { kernel_flags_.emplace_back(value); }
  EtwConfig_KernelFlag* add_kernel_flags() { kernel_flags_.emplace_back(); return &kernel_flags_.back(); }

 private:
  std::vector<EtwConfig_KernelFlag> kernel_flags_;

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<2> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_ETW_ETW_CONFIG_PROTO_CPP_H_
