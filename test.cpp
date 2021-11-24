#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


class Process;

class System {
public:
    System() {}
    System(std::ifstream);

    int getAvailableResourceAmount(std::string resource) { return available[resource]; }
    std::map<std::string, int> getAvailableResources() { return available; }

    std::vector<std::string> getSafeSequence();

    Process* getProcess(std::string p_id) { return processes[p_id]; }
    std::map<std::string, Process*> getAllProcesses() { return processes; }

private:
    std::map<std::string, int> available;
    std::map<std::string, Process*> processes;

    std::ifstream fin;
}

class Process {
public:
    Process() {};

    void addToAllocation(std::string resource, int resource_amount) { allocation.emplace(resource, resource_amount); }
    void addToMax(std::string resource, int resource_amount) { max.emplace(resource, resource_amount); }

    int getAllocatedAmount(std::string resource) { return allocation[resource]; }
    int getMaxAmount(std::string resource) { return max[resource]; }
    int getNeededAmount(std::string resource) { return (max[resource] - allocation[resource]); }

    std::map<std::string, int> getAllocationVector() { return allocation; }
    std::map<std::string, int> getMaxVector() { return max; }
    std::map<std::string, int> getNeededVector() {
        std::map<std::string, int> needed;
        for (auto p: allocation)
            needed.emplace(p.first, (max[p.first] - p.second));
        return needed;
    }
private:
    std::map<std::string, int> allocation;
    std::map<std::string, int> max;
}

std::vector<std::string> getSafeSequence() {
}
