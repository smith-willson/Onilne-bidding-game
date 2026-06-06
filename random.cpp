#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <set>

int randomIndex(int size, std::mt19937& rng)
{
    std::uniform_int_distribution<int> dist(0, size - 1);
    return dist(rng);
}

std::vector<std::string> pickNames(const std::vector<std::string>& pool,
                                   int count,
                                   std::mt19937& rng)
{
    std::vector<int> indices;
    std::set<int>    used;

    while ((int)indices.size() < count)
    {
        int idx = randomIndex((int)pool.size(), rng);
        if (used.find(idx) == used.end())   
        {
            used.insert(idx);
            indices.push_back(idx);
        }
    }

    std::vector<std::string> result;
    result.reserve(count);
    for (int i : indices)
        result.push_back(pool[i]);

    return result;
}


int main()
{
    
    const std::vector<std::string> names = {
        "Alice", "Bob",     "Charlie", "Diana",  "Eve",
        "Frank", "Grace",   "Henry",   "Isla",   "Jack",
        "Karen", "Liam",    "Mia",     "Noah",   "Olivia",
        "Paul",  "Quinn",   "Rachel",  "Sam",    "Tina"
    };


    std::random_device rd;
    std::mt19937       rng(rd());

    const int MAX_ROUNDS  = 10;     
    const int CYCLE_RESET = 15;     
    const int STEP        = 3;      

    int multiplier = 1;             

    std::cout << "=== Name Picker  (pool: " << names.size() << " names) ===\n\n";

    for (int round = 1; round <= MAX_ROUNDS; ++round)
    {
        int pickCount = STEP * multiplier;

        
        if (pickCount > (int)names.size())
        {
            std::cout << "Round " << round
                      << ": pick count (" << pickCount
                      << ") exceeds pool size — skipping.\n";
            multiplier = 1;
            continue;
        }

        std::vector<std::string> picked = pickNames(names, pickCount, rng);

        
        bool isStar = (pickCount == CYCLE_RESET);

        std::cout << "Round " << round
                  << "  [pick " << pickCount << "]"
                  << (isStar ? "  ★ STAR ROUND — resetting cycle" : "")
                  << "\n";

        for (int i = 0; i < (int)picked.size(); ++i)
            std::cout << "  " << (i + 1) << ". " << picked[i] << "\n";

        std::cout << "\n";

        
        if (pickCount >= CYCLE_RESET)
            multiplier = 1;     
        else
            ++multiplier;       
    }

    return 0;
}