#include <gtest/gtest.h>

#include <algorithm>  // для std::ranges::sort
#include <cstddef>
#include <cstdint>
#include <memory>
#include <random>
#include <vector>

#include "all/fyodorov_m_shell_sort_with_even_odd_batcher_merge/include/ops_mpi.hpp"
#include "core/task/include/task.hpp"

TEST(fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi, test_small_array) {
  std::vector<int> input = {35, 33, 42, 10, 14, 19, 27, 44};
  std::vector<int> expected_output = {10, 14, 19, 27, 33, 35, 42, 44};

  std::vector<int> output(input.size(), 0);

  auto task_data_mpi = std::make_shared<ppc::core::TaskData>();
  task_data_mpi->inputs.emplace_back(reinterpret_cast<uint8_t *>(input.data()));
  task_data_mpi->inputs_count.emplace_back(input.size());
  task_data_mpi->outputs.emplace_back(reinterpret_cast<uint8_t *>(output.data()));
  task_data_mpi->outputs_count.emplace_back(output.size());

  fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi::TestTaskMPI test_task_mpi(task_data_mpi);
  ASSERT_EQ(test_task_mpi.Validation(), true);
  test_task_mpi.PreProcessing();
  test_task_mpi.Run();
  test_task_mpi.PostProcessing();

  EXPECT_EQ(output, expected_output);
}

TEST(fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi, test_small_array_with_negative_values) {
  std::vector<int> input = {35, 33, 42, -10, -14, 19, 27, 44};
  std::vector<int> expected_output = {-14, -10, 19, 27, 33, 35, 42, 44};

  std::vector<int> output(input.size(), 0);

  auto task_data_mpi = std::make_shared<ppc::core::TaskData>();
  task_data_mpi->inputs.emplace_back(reinterpret_cast<uint8_t *>(input.data()));
  task_data_mpi->inputs_count.emplace_back(input.size());
  task_data_mpi->outputs.emplace_back(reinterpret_cast<uint8_t *>(output.data()));
  task_data_mpi->outputs_count.emplace_back(output.size());

  fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi::TestTaskMPI test_task_mpi(task_data_mpi);
  ASSERT_EQ(test_task_mpi.Validation(), true);
  test_task_mpi.PreProcessing();
  test_task_mpi.Run();
  test_task_mpi.PostProcessing();

  EXPECT_EQ(output, expected_output);
}

TEST(fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi, test_random_sequence) {
  std::mt19937 gen(42);
  std::uniform_int_distribution<> distrib(-100, 100);

  const size_t size = 10;
  std::vector<int> input(size);
  for (auto &num : input) {
    num = distrib(gen);
  }

  std::vector<int> expected_output = input;
  std::ranges::sort(expected_output);

  std::vector<int> output(input.size(), 0);

  auto task_data_mpi = std::make_shared<ppc::core::TaskData>();
  task_data_mpi->inputs.emplace_back(reinterpret_cast<uint8_t *>(input.data()));
  task_data_mpi->inputs_count.emplace_back(input.size());
  task_data_mpi->outputs.emplace_back(reinterpret_cast<uint8_t *>(output.data()));
  task_data_mpi->outputs_count.emplace_back(output.size());

  fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi::TestTaskMPI test_task_mpi(task_data_mpi);
  ASSERT_EQ(test_task_mpi.Validation(), true);
  test_task_mpi.PreProcessing();
  test_task_mpi.Run();
  test_task_mpi.PostProcessing();

  EXPECT_EQ(output, expected_output);
}

TEST(fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi, test_sorted_array) {
  std::vector<int> input = {10, 14, 19, 27, 33, 35, 42, 44};

  std::vector<int> expected_output = {10, 14, 19, 27, 33, 35, 42, 44};

  std::vector<int> output(input.size(), 0);

  auto task_data_mpi = std::make_shared<ppc::core::TaskData>();
  task_data_mpi->inputs.emplace_back(reinterpret_cast<uint8_t *>(input.data()));
  task_data_mpi->inputs_count.emplace_back(input.size());
  task_data_mpi->outputs.emplace_back(reinterpret_cast<uint8_t *>(output.data()));
  task_data_mpi->outputs_count.emplace_back(output.size());

  fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi::TestTaskMPI test_task_mpi(task_data_mpi);
  ASSERT_EQ(test_task_mpi.Validation(), true);
  test_task_mpi.PreProcessing();
  test_task_mpi.Run();
  test_task_mpi.PostProcessing();

  EXPECT_EQ(output, expected_output);
}

TEST(fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi, reverse_pozitive_array) {
  int arrsize = 12;
  std::vector<int> in = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> out(arrsize, 0);

  auto task_data_mpi = std::make_shared<ppc::core::TaskData>();
  task_data_mpi->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_mpi->inputs_count.emplace_back(in.size());
  task_data_mpi->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_mpi->outputs_count.emplace_back(out.size());

  fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi::TestTaskMPI test_task_mpi(task_data_mpi);
  ASSERT_EQ(test_task_mpi.Validation(), true);
  test_task_mpi.PreProcessing();
  test_task_mpi.Run();
  test_task_mpi.PostProcessing();
  std::ranges::sort(in);
  EXPECT_EQ(in, out);
}

TEST(fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi, reverse_pozitive_double) {
  int arrsize = 10;
  std::vector<int> in = {5, 4, 3, 2, 1, 5, 4, 3, 2, 1};
  std::vector<int> out(arrsize, 0);
  auto task_data_mpi = std::make_shared<ppc::core::TaskData>();
  task_data_mpi->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_mpi->inputs_count.emplace_back(in.size());
  task_data_mpi->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_mpi->outputs_count.emplace_back(out.size());
  fyodorov_m_shell_sort_with_even_odd_batcher_merge_mpi::TestTaskMPI test_task_mpi(task_data_mpi);
  ASSERT_EQ(test_task_mpi.Validation(), true);
  test_task_mpi.PreProcessing();
  test_task_mpi.Run();
  test_task_mpi.PostProcessing();
  std::ranges::sort(in);
  EXPECT_EQ(in, out);
}