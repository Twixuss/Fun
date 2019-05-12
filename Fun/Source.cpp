#include <iostream>
#include <random>
#include <chrono>
struct TimeLogger
{
   const char*   m_blockName;
   const clock_t m_start;

   TimeLogger(const char* blockName) : m_blockName(blockName), m_start(clock()) {}
   ~TimeLogger()
   {
      clock_t finish = clock();
      std::cout << "Done: " << m_blockName << " in " << (finish - m_start) * 1000.0 / CLOCKS_PER_SEC << " ms" << std::endl;
   }
};

const size_t k_ITERATIONS = 16;
const size_t k_SIZE = 1024 * 1024;

uint64_t test(const char* name, const std::vector<int64_t>& data, const std::vector<size_t>& indexes)
{
   TimeLogger log = name;

   uint64_t sum = 0;
   for (size_t i = 0; i < k_ITERATIONS; ++i)
      for (size_t index : indexes)
         sum += data[index];

   return sum;
}

// return shuffled sequences of consecutive numbers like [0,1,2, 6,7,8, 3,4,5, ...]
std::vector<size_t> fillSequences(size_t size, size_t seriesSize, std::mt19937 g)
{
   std::vector<size_t> semiRandIdx;
   semiRandIdx.reserve(size);

   size_t i = 0;
   auto semiRandSequences = std::vector<size_t>(size / seriesSize, 0);
   std::generate(semiRandSequences.begin(), semiRandSequences.end(), [&i]() { return i++; });
   std::shuffle(semiRandSequences.begin(), semiRandSequences.end(), g);

   for (size_t seqNumber : semiRandSequences)
      for (size_t i = seqNumber * seriesSize; i < (seqNumber + 1) * seriesSize; ++i)
         semiRandIdx.push_back(i);

   return semiRandIdx;
}

int main()
{
   std::random_device rd;
   std::mt19937 g(rd());

   auto intData = std::vector<int64_t>(k_SIZE, 0);
   std::generate(intData.begin(), intData.end(), g);

   // [0, 1, 2, ... N]
   auto idx = std::vector<size_t>(k_SIZE, 0);
   std::generate(idx.begin(), idx.end(), []() {static size_t i = 0; return i++; });

   // [N, N-1, ... 0]
   auto reverseIdx = std::vector<size_t>(idx.rbegin(), idx.rend());

   // random permutation of [0, 1, ... N]
   auto randIdx = idx;
   std::shuffle(randIdx.begin(), randIdx.end(), g);

   // random permutations of 32, 64, 128-byte sequences
   auto seq32Idx = fillSequences(idx.size(), 32 / sizeof(int64_t), g);
   auto seq64Idx = fillSequences(idx.size(), 64 / sizeof(int64_t), g);
   auto seq128Idx = fillSequences(idx.size(), 128 / sizeof(int64_t), g);

   size_t dataSize = intData.size() * sizeof(int64_t);
   size_t indexSize = idx.size() * sizeof(int64_t);
   std::cout << "vectors filled, data (MB): " << dataSize / 1024 / 1024.0 << "; index (MB): " << indexSize / 1024 / 1024.0
      << "; total (MB): " << (dataSize + indexSize) / 1024 / 1024.0 << std::endl << "Loops: " << k_ITERATIONS << std::endl;

   uint64_t sum1 = test("regular access", intData, idx);
   uint64_t sum2 = test("reverse access", intData, reverseIdx);
   uint64_t sum3 = test("random access", intData, randIdx);
   uint64_t sum4 = test("random 32-byte sequences", intData, seq32Idx);
   uint64_t sum5 = test("random 64-byte sequences", intData, seq64Idx);
   uint64_t sum6 = test("random 128-byte sequences", intData, seq128Idx);

   std::cout << sum1 << ", " << sum2 << ", " << sum3 << ", " << sum4 << ", " << sum5 << ", " << sum6 << std::endl;
   return 0;
}