import matplotlib.pyplot as plt
import numpy as np

with open('cycle_single.txt', 'r') as file:
    data = file.readlines()

function1_speeds = [float(data[i].strip()) for i in range(0, len(data), 1)]

# Calculate the averages
average_function1 = np.mean(function1_speeds)

# Rolling mean for smoothing
window_size = 1000
function1_smooth = np.convolve(function1_speeds, np.ones(window_size)/window_size, mode='valid')

# Find the lowest and highest points of the smoothed data
lowest_point_smooth = min(function1_smooth)
highest_point_smooth = max(function1_smooth)
lowest_index_smooth = np.argmin(function1_smooth)
highest_index_smooth = np.argmax(function1_smooth)

# Set up the figure and axes for a prettier graph
fig, ax1 = plt.subplots(figsize=(14, 7), dpi=100)

# Plot the smoothed data with distinct designs
ax1.plot(function1_smooth, color='dodgerblue', label='Cycles', alpha=0.9, linewidth=2, linestyle='-', marker='o', markevery=100)

# Mark and directly annotate the lowest and highest points of the smoothed data
# Mark the lowest point
ax1.plot(lowest_index_smooth, lowest_point_smooth, 'v', color='green', markersize=10)
ax1.text(lowest_index_smooth, lowest_point_smooth, f'Lowest: {lowest_point_smooth:.2f}', color='green', va='top', ha='center')

# Mark the highest point
ax1.plot(highest_index_smooth, highest_point_smooth, '^', color='red', markersize=10)
ax1.text(highest_index_smooth, highest_point_smooth, f'Highest: {highest_point_smooth:.2f}', color='red', va='bottom', ha='center')

# Add horizontal line to indicate the average value
ax1.axhline(average_function1, color='dodgerblue', linestyle='dashdot', linewidth=2, label=f'Avg Cycles: {average_function1:.2f}')

# Setting labels, titles, and legends
ax1.set_ylabel('Total Cycles', fontsize=16, fontweight='bold', color='dodgerblue')
ax1.set_xlabel('Run Number', fontsize=16, fontweight='bold')
ax1.set_title('Measurement of Cycles: 64-bit Multiplication', fontsize=18, fontweight='bold')

# Combine legends
lines, labels = ax1.get_legend_handles_labels()
ax1.legend(lines, labels, loc='upper left', frameon=True, framealpha=0.9, shadow=True, fancybox=True, fontsize=12)

# Customizing the grid and layout
ax1.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
plt.tight_layout()

# Enhancing the overall look
fig.patch.set_facecolor('white')
fig.patch.set_edgecolor('lightgrey')

# Show the plot
plt.show()