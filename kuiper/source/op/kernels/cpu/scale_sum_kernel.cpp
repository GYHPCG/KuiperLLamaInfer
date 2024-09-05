#include "scale_sum_kernel.h"
#include <armadillo>
#include "base/base.h"
namespace kernel {
void scale_sum_kernel_cpu(const tensor::Tensor& value, const tensor::Tensor& scale, 
                          const tensor::Tensor& output, int pos, int size, int stride,
                          void* stream) {
  UNUSED(stream);
  CHECK_EQ(value.is_empty(), false);
  CHECK_EQ(scale.is_empty(), false);
  CHECK_EQ(output.is_empty(), false);
  CHECK_EQ(size, value.size());
  CHECK_GE(size, scale.size());
  CHECK_EQ(size, output.size());
  arma::fvec value_vec(const_cast<float*>(value.ptr<float>()), value.size(), false, true);
  arma::fvec scale_vec(const_cast<float*>(scale.ptr<float>()), scale.size(), false, true);
  arma::fvec output_vec(const_cast<float*>(output.ptr<float>()), output.size(), false, true);

  for (int i = 0; i <= pos; ++i) {
    for (int j = 0; j < size; ++j) {
      output_vec[j] += scale_vec[i] * value_vec[i * stride + j];
    }
  }
}
}  // namespace kernel
