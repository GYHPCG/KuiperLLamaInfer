#include <glog/logging.h>
#include <gtest/gtest.h>
#include "base/buffer.h"
#include "tensor/tensor.h"
#include "../kuiper/source/op/kernels/add_kernel.h"

TEST(test_op, op_add) {
  using namespace base;
  auto allocate_cu = base::CPUDeviceAllocatorFactory::get_instance();
  int32_t size  = 32 * 151;
  
  tensor::Tensor t1(base::DataType::kDataTypeFp32, size, true, allocate_cu);
  tensor::Tensor t2(base::DataType::kDataTypeFp32, size, true, allocate_cu);
  tensor::Tensor t3(base::DataType::kDataTypeFp32, size, true, allocate_cu);
  
  //初始化
  for (auto i = 0; i < t1.size(); i++) {
    t1.index<float>(i) = 1;
    t2.index<float>(i) = 2;
  }
  kernel::get_add_kernel(base::DeviceType::kDeviceCPU)(t1,t2,t3);

  for (auto i = 0; i < t1.size(); i++) {
    ASSERT_EQ(t3.index<float>(i),3.f);
  }






}