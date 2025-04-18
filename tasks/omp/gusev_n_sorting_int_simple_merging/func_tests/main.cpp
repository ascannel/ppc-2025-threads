#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <random>
#include <vector>

#include "core/task/include/task.hpp"
#include "omp/gusev_n_sorting_int_simple_merging/include/ops_omp.hpp"

namespace {
ppc::core::TaskDataPtr CreateTaskData(std::vector<int> &input, std::vector<int> &output) {
  auto task_data_omp = std::make_shared<ppc::core::TaskData>();

  task_data_omp->inputs.emplace_back(reinterpret_cast<uint8_t *>(input.data()));
  task_data_omp->inputs_count.emplace_back(input.size());
  task_data_omp->outputs.emplace_back(reinterpret_cast<uint8_t *>(output.data()));
  task_data_omp->outputs_count.emplace_back(output.size());

  return task_data_omp;
}

void RunT(ppc::core::TaskDataPtr &task_data) {
  gusev_n_sorting_int_simple_merging_omp::TestTaskOpenMP task(task_data);
  ASSERT_TRUE(task.Validation());
  ASSERT_TRUE(task.PreProcessing());
  ASSERT_TRUE(task.Run());
  ASSERT_TRUE(task.PostProcessing());
}
}  // namespace
TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_basic) {
  std::vector<int> in = {170, 45, 75, 90, 802, 24, 2, 66};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);

  RunT(task_data_omp);
  std::vector<int> expected = in;
  std::ranges::sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_empty) {
  std::vector<int> in = {};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);

  RunT(task_data_omp);

  EXPECT_EQ(out.size(), 0U);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_single_element) {
  std::vector<int> in = {42};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);

  RunT(task_data_omp);

  EXPECT_EQ(in, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_negative_numbers) {
  std::vector<int> in = {3, -1, 0, -5, 2, -3};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);

  RunT(task_data_omp);

  std::vector<int> expected = in;
  std::ranges::sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_random) {
  size_t size = 1000;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-10000, 10000);

  std::vector<int> in(size);
  std::ranges::generate(in, [&]() { return dist(gen); });
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);
  RunT(task_data_omp);

  std::vector<int> expected = in;
  std::ranges::sort(expected);
  EXPECT_EQ(expected, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_duplicates) {
  std::vector<int> in = {5, 3, 5, -2, 3, -2, -2, 5, 0, 0, -0, 7, 7, -7};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);
  RunT(task_data_omp);

  std::vector<int> expected = in;
  std::ranges::sort(expected);

  EXPECT_EQ(expected, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_reversed_random) {
  size_t size = 1000;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-100000, 100000);

  std::vector<int> in(size);
  std::ranges::generate(in, [&]() { return dist(gen); });
  std::ranges::sort(in, std::greater{});

  std::vector<int> out(in.size());
  auto task_data_omp = CreateTaskData(in, out);
  RunT(task_data_omp);

  std::vector<int> expected = in;
  std::ranges::sort(expected);

  EXPECT_EQ(expected, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_already_sorted) {
  std::vector<int> in = {1, 2, 3, 4, 5};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);
  RunT(task_data_omp);

  std::vector<int> expected = in;
  std::ranges::sort(expected);
  EXPECT_EQ(expected, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_all_negative) {
  std::vector<int> in = {-5, -3, -1, -10, -2};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);
  RunT(task_data_omp);

  std::vector<int> expected = in;
  std::ranges::sort(expected);
  EXPECT_EQ(expected, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_all_same) {
  std::vector<int> in = {5, 5, 5, 5, 5};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);
  RunT(task_data_omp);

  std::vector<int> expected = in;
  std::ranges::sort(expected);
  EXPECT_EQ(expected, out);
}

TEST(gusev_n_sorting_int_simple_merging_omp, test_radix_sort_all_same_negative) {
  std::vector<int> in = {-3, -3, -3, -3};
  std::vector<int> out(in.size());

  auto task_data_omp = CreateTaskData(in, out);
  RunT(task_data_omp);

  std::vector<int> expected = in;
  std::ranges::sort(expected);
  EXPECT_EQ(expected, out);
}
