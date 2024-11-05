import re

def extract_times(filename):
    times = []
    with open(filename, 'r') as file:
        for line in file:
            # Use regex to find lines that contain the time in the specified format
            match = re.search(r'Time: ([\d.]+)s', line)
            if match:
                times.append(float(match.group(1)))  # Convert matched time to float and add to list
    return times

# Example usage
filename = 'KeySchedTime.txt'
time_values = extract_times(filename)
for t in time_values:
    print(f"{t}")
