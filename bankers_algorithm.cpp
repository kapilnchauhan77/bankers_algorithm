// Bankers Algorithm
// Kapil Chauhan
// 11/24/21

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>


class Process;

class System {
public:
    System() {}
    System(std::string);
    System(std::map<char, int> avail, std::map<std::string, Process*> proc):
        available(avail), processes(proc) {}

    int getAvailableResourceAmount(char resource) { return available[resource]; }
    std::map<char, int> getAvailableResources() { return available; }

    std::vector<std::string> getSafeSequence();

    Process* getProcess(std::string p_id) { return processes[p_id]; }
    std::map<std::string, Process*> getAllProcesses() { return processes; }

private:
    std::map<char, int> available;
    std::map<std::string, Process*> processes;

    std::vector<std::string> safe_sequence;

    std::ifstream fin;
};

class Process {
public:
    Process() {};
    Process(std::map<char, int> alloc, std::map<char, int> m):
        allocation(alloc), max(m) {}

    void addToAllocation(char resource, int resource_amount) { allocation.emplace(resource, resource_amount); }
    void addToMax(char resource, int resource_amount) { max.emplace(resource, resource_amount); }

    int getAllocatedAmount(char resource) { return allocation[resource]; }
    int getMaxAmount(char resource) { return max[resource]; }
    int getNeededAmount(char resource) { return (max[resource] - allocation[resource]); }

    std::map<char, int> getAllocationVector() { return allocation; }
    std::map<char, int> getMaxVector() { return max; }
    std::map<char, int> getNeededVector() {
        std::map<char, int> needed;
        for (auto p: allocation)
            needed.emplace(p.first, (max[p.first] - p.second));
        return needed;
    }
private:
    std::map<char, int> allocation;
    std::map<char, int> max;
};

std::vector<std::string> System::getSafeSequence() {
    if (safe_sequence.size() != 0) return safe_sequence;

    std::map<std::string, bool> finishes = {};
    bool go_to_step_4;
    bool go_to_step_3;

    std::map<std::string, Process*>::iterator it = processes.begin();

    for (std::pair<std::string, Process*> process_: processes)
        finishes.emplace(process_.first, false);

    int tries = 0;
    while (true) {

        go_to_step_3 = false;
        go_to_step_4 = true;
        if (finishes[it->first] == false) {
            go_to_step_3 = true;
            go_to_step_4 = false;
            for (std::pair<char, int> resource_available: available) {
                if ((it->second)->getNeededAmount(resource_available.first) > resource_available.second) {
                    go_to_step_3 = false;
                    go_to_step_4 = true;
                    break;
                }
            }
        }

        if (go_to_step_4) {
            if (finishes[it->first] == true) return safe_sequence;
            std::advance(it, 1);
        } else if (go_to_step_3) {
            for (std::pair<char, int> resource_available: available)
                available[resource_available.first] = resource_available.second + (it->second)->getAllocatedAmount(resource_available.first);

            safe_sequence.push_back(it->first);
            finishes[it->first] = true;

            processes.erase(it);

            if (processes.size() == 0) break;

            std::advance(it, 1);
            if (it->second == 0) it = processes.begin();
        }

        tries += 1;
        if (tries > (finishes.size() * finishes.size())) break;
    }

    return safe_sequence;
}

System::System(std::string file_name) {
    fin.open(file_name);
    std::vector<char> resources_;

    std::string line;

    std::getline(fin, line);
    std::getline(fin, line);
    for (char c: line) {
        if (std::find(resources_.begin(), resources_.end(), c) == resources_.end()) {
            if (c != ',' && c != ' ')
                resources_.push_back(c);
        } else break;
    }

    std::map<char, int> alloc;
    std::map<char, int> m;
    std::string process_name;
    size_t temp_position;
    Process* p;

    std::getline(fin, line);
    temp_position = line.find(',');
    process_name = line.substr(0, temp_position);
    line = line.substr(temp_position+1, line.size()-1);

    for (char resource_: resources_) {
        temp_position = line.find(',');
        alloc[resource_] = std::stoi(line.substr(0, temp_position));
        line = line.substr(temp_position+1, line.size()-1);
    }

    for (char resource_: resources_) {
        temp_position = line.find(',');
        m[resource_] = std::stoi(line.substr(0, temp_position));
        line = line.substr(temp_position+1, line.size()-1);
    }

    for (char resource_: resources_) {
        temp_position = line.find(',');
        available[resource_] = std::stoi(line.substr(0, temp_position));
        line = line.substr(temp_position+1, line.size()-1);
    }

    p = new Process(alloc, m);
    processes[process_name] = p;

    while (fin) {
        std::getline(fin, line);
        if (line == "") break;

        temp_position = line.find(',');
        process_name = line.substr(0, temp_position);
        line = line.substr(temp_position+1, line.size()-1);

        for (char resource_: resources_) {
            temp_position = line.find(',');
            alloc[resource_] = std::stoi(line.substr(0, temp_position));
            line = line.substr(temp_position+1, line.size()-1);
        }

        for (char resource_: resources_) {
            temp_position = line.find(',');
            m[resource_] = std::stoi(line.substr(0, temp_position));
            line = line.substr(temp_position+1, line.size()-1);
        }

        p = new Process(alloc, m);
        processes[process_name] = p;
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No input file provided" << std::endl;
        return(1);
    }

    System sys(argv[1]);

    std::vector<std::string> safe_sequence = sys.getSafeSequence();
    std::cout << "Safety Sequence: < ";
    for (auto s: safe_sequence)
        std::cout << s << ' ';
    std::cout << ">" << std::endl;
}
