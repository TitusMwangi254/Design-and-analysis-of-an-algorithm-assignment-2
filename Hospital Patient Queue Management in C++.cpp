#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

class EmergencyStack {
private:
    std::vector<std::string> stack; // Using vector as a stack

public:
    void push(const std::string& patient) {
        stack.push_back(patient);
    }

    std::string pop() {
        if (is_empty()) {
            throw std::out_of_range("Emergency stack is empty");
        }
        std::string patient = stack.back();
        stack.pop_back();
        return patient;
    }

    bool is_empty() const {
        return stack.empty();
    }

    std::string peek() const {
        if (is_empty()) {
            throw std::out_of_range("Emergency stack is empty");
        }
        return stack.back();
    }
};

class PatientQueue {
private:
    std::vector<std::string> queue;
    EmergencyStack emergency_stack;

public:
    void enqueue(const std::string& patient) {
        queue.push_back(patient);
    }

    std::string dequeue() {
        if (is_empty()) {
            throw std::out_of_range("Patient queue is empty");
        }
        std::string patient = queue.front();
        queue.erase(queue.begin());
        return patient;
    }

    bool is_empty() const {
        return queue.empty();
    }

    void emergency_add(const std::string& patient) {
        emergency_stack.push(patient);
    }

    std::string emergency_pop() {
        if (!emergency_stack.is_empty()) {
            return emergency_stack.pop();
        } else if (!is_empty()) {
            return dequeue();
        } else {
            throw std::out_of_range("No patients available");
        }
    }
};

// Example usage
int main() {
    PatientQueue pq;
    pq.enqueue("Patient A");
    pq.enqueue("Patient B");
    pq.emergency_add("Emergency Patient 1");

    std::cout << pq.emergency_pop() << std::endl; // Should return "Emergency Patient 1"
    std::cout << pq.dequeue() << std::endl;       // Should return "Patient A"

    return 0;
}
