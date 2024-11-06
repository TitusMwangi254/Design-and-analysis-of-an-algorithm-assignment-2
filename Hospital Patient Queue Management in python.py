class EmergencyStack:
    def __init__(self):
        self.stack = []

    def push(self, patient):
        """Add an emergency patient to the stack."""
        self.stack.append(patient)

    def pop(self):
        """Remove and return the top emergency patient."""
        if self.is_empty():
            raise IndexError("Emergency stack is empty")
        return self.stack.pop()

    def is_empty(self):
        """Check if the emergency stack is empty."""
        return len(self.stack) == 0

    def peek(self):
        """Return the top emergency patient without removing it."""
        if self.is_empty():
            raise IndexError("Emergency stack is empty")
        return self.stack[-1]


class PatientQueue:
    def __init__(self):
        self.queue = []
        self.emergency_stack = EmergencyStack()

    def enqueue(self, patient):
        """Add a patient to the end of the queue."""
        self.queue.append(patient)

    def dequeue(self):
        """Remove and return the next patient from the queue."""
        if self.is_empty():
            raise IndexError("Patient queue is empty")
        return self.queue.pop(0)

    def is_empty(self):
        """Check if the patient queue is empty."""
        return len(self.queue) == 0

    def emergency_add(self, patient):
        """Add a patient to the emergency stack."""
        self.emergency_stack.push(patient)

    def emergency_pop(self):
        """Pop a patient from the emergency stack if not empty, else dequeue."""
        if not self.emergency_stack.is_empty():
            return self.emergency_stack.pop()
        elif not self.is_empty():
            return self.dequeue()
        else:
            raise IndexError("No patients available")


# Example usage
if __name__ == "__main__":
    pq = PatientQueue()
    pq.enqueue("Patient A")
    pq.enqueue("Patient B")
    pq.emergency_add("Emergency Patient 1")

    print(pq.emergency_pop())  # Should return "Emergency Patient 1"
    print(pq.dequeue())        # Should return "Patient A"
