#include <glog/logging.h>
#include <gtest/gtest.h>
#include "base/buffer.h"
// 拥有所有权
TEST(test_buffer, allocate) {
  using namespace base;
  auto alloc = base::CPUDeviceAllocatorFactory::get_instance();
  Buffer buffer(32, alloc);
  ASSERT_NE(buffer.ptr(), nullptr);
}
// 没有所有权
TEST(test_buffer, use_external) {
  using namespace base;
  auto alloc = base::CPUDeviceAllocatorFactory::get_instance();
  float* ptr = new float[32];
  Buffer buffer(32, nullptr, ptr, true);
  ASSERT_EQ(buffer.is_external(), true);
  delete[] ptr;
}

// 对于局部生命周期的测试
TEST(test_buffer, local_memory) {
  using namespace base;
  auto alloc = base::CPUDeviceAllocatorFactory::get_instance();
  {
    Buffer buffer(32, alloc);
    ASSERT_NE(buffer.ptr(), nullptr);
    LOG(INFO) << "Here1";
  }
  LOG(INFO) << "Here2";
}

// 对于局部内存有外部引用，不能释放
TEST(test_buffer, local_memory2) {
  using namespace base;
  auto alloc = base::CPUDeviceAllocatorFactory::get_instance();
  std::shared_ptr<Buffer> buffer;
  { buffer = std::make_shared<Buffer>(32, alloc); }
  ASSERT_NE(buffer->ptr(), nullptr);
  LOG(INFO) << "Here3";
}
