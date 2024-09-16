#include <algorithm>
#include <iostream>
#include <spdlog/spdlog.h>
#include <core/helpers/time_measuring.hpp>
#include "Agent.hpp"
#include "testers/HelloWorld.hpp"

using namespace std::literals;

struct TestCase {
  GeneManager::Genes genes = {};
  ITester::Result result = {};
};

std::vector<TestCase> generate_tests(GeneManager& gene_manager, std::size_t size) {
  std::vector<GeneManager::Genes> genes;
  genes.reserve(size);

  gene_manager.create(std::back_inserter(genes), size, {
    .cells_size = 10,
    .program_size = 100
  });

  std::vector<TestCase> tests;
  tests.reserve(genes.size());

  for (auto& gene: genes) {
    tests.push_back({.genes = std::move(gene), .result = {}});
  }

  return tests;
}

void print_first(const std::vector<TestCase>& tests, std::size_t n) {
  n = std::min(n, tests.size());
  for (std::size_t i = 0; i < n; ++i) {
    SPDLOG_INFO("{}) Score - {}, Used Quota - {}", i + 1, tests[i].result.score, tests[i].result.used_quota);
  }
}

std::string random_string(const std::size_t len) {
  thread_local std::mt19937 random_generator = []() {
    std::random_device rd;
    return std::mt19937(rd());
  }();

  const std::string_view alphanum =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"sv;

  std::string str(len, 0);
  std::uniform_int_distribution<std::size_t> dist(0, alphanum.size() - 1);
  std::generate(str.begin(), str.end(), [alphanum, &dist]() {
    return alphanum[dist(random_generator)];
  });

  return str;
}

void delete_and_mutate(GeneManager& gene_manager, std::vector<TestCase>& tests) {
  tests.resize(tests.size() / 2);

  std::vector<TestCase> to_mutate;
  to_mutate.reserve(tests.size());
  std::copy(tests.begin(), tests.end(), std::back_inserter(to_mutate));
  for (TestCase& test: to_mutate) {
    gene_manager.mutate(test.genes);
    test.result = {};
  }
  std::move(to_mutate.begin(), to_mutate.end(), std::back_inserter(tests));


}

int some_function(int* arr)
{
  int a = arr[0];

  if(arr != nullptr)
  {
    return a + arr[1];
  }

  return 0;
}


int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif

  GeneManager gene_manager;
  std::vector tests = generate_tests(gene_manager, 100);
  const std::size_t subtest_count = 1;

  for (std::size_t iteration = 1; iteration <= 1000; ++iteration) {
    const core::helpers::TimeMeasuring execituon_time;
    for (TestCase& test: tests) {
      test.result = {.score = 0, .used_quota = 0};
    }

    for (std::size_t subtest_i = 0; subtest_i < subtest_count; ++subtest_i) {
      const testers::HelloWorld hw_tester(random_string(subtest_i + 3));

      for (TestCase& test: tests) {
        const ITester::Result result = hw_tester.test(test.genes);
        test.result.score += result.score;
        test.result.used_quota += result.used_quota;
      }
    }

    // normalise
    for (TestCase& test: tests) {
      test.result.score /= subtest_count;
      test.result.used_quota /= subtest_count;
    }

    SPDLOG_INFO(
      "----- ITERATION {} (execution time {:.2f}s) -----",
      iteration,
      execituon_time.measure<std::chrono::duration<float>>().count()
    );

    std::sort(tests.begin(), tests.end(), [](const TestCase& a, const TestCase& b) {
      return a.result.score > b.result.score;
    });
    print_first(tests, 5);
    std::cout << std::endl;
    delete_and_mutate(gene_manager, tests);
  }

//  int keks = 123;
//  some_function(&keks);

  return 0;
}

