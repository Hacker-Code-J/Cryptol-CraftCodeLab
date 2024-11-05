import matplotlib.pyplot as plt
import numpy as np

with open('TimeMeasure.txt', 'r') as file:
    data = file.readlines()

function1_speeds = [float(data[i].strip()) for i in range(0, len(data), 1)]

# Calculate the averages
average_function1 = np.mean(function1_speeds)

# Rolling mean for smoothing
window_size = 10
function1_smooth = np.convolve(function1_speeds, np.ones(window_size)/window_size, mode='valid')

# Find the lowest and highest points of the smoothed data
lowest_point_smooth = min(function1_smooth)
highest_point_smooth = max(function1_smooth)
lowest_index_smooth = np.argmin(function1_smooth)
highest_index_smooth = np.argmax(function1_smooth)

# Set up the figure and axes for a prettier graph
fig, ax1 = plt.subplots(figsize=(9.8, 4.9), dpi=100)

# Plot the smoothed data with distinct designs
ax1.plot(function1_smooth, color='dodgerblue', label='Verification Time', alpha=0.9, linewidth=2, linestyle='-', marker='o', markevery=100)

# Mark and directly annotate the lowest and highest points of the smoothed data
# Mark the lowest point
ax1.plot(lowest_index_smooth, lowest_point_smooth, 'v', color='green', markersize=10)
ax1.text(lowest_index_smooth, lowest_point_smooth, f'Lowest: {lowest_point_smooth:.5f}', color='green', va='top', ha='center')

# Mark the highest point
ax1.plot(highest_index_smooth, highest_point_smooth, '^', color='red', markersize=10)
ax1.text(highest_index_smooth, highest_point_smooth, f'Highest: {highest_point_smooth:.5f}', color='red', va='bottom', ha='center')

# Add horizontal line to indicate the average value
ax1.axhline(average_function1, color='dodgerblue', linestyle='dashdot', linewidth=2, label=f'Avg. of Verification Time: {average_function1:.5f}')

# Setting labels, titles, and legends
ax1.set_ylabel('Verification Time (seconds)', fontsize=12, fontweight='bold', color='dodgerblue')
ax1.set_xlabel('Verification Run Number', fontsize=12, fontweight='bold')
ax1.set_title('Verification Time for [HIGHT_KeySched]', fontsize=14, fontweight='bold')

# Combine legends
lines, labels = ax1.get_legend_handles_labels()
ax1.legend(lines, labels, loc='upper left', frameon=True, framealpha=0.9, shadow=True, fancybox=True, fontsize=10)

# Customizing the grid and layout
ax1.grid(True, linestyle='--', linewidth=0.5, alpha=0.7)
plt.tight_layout()

# Enhancing the overall look
fig.patch.set_facecolor('white')
fig.patch.set_edgecolor('lightgrey')

# Show the plot
plt.show()